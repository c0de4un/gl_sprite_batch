/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

// HEADER
#ifndef __c0de4un_gl_texture_2D_hpp__
#include "GLTexture2D.hpp"
#endif // !__c0de4un_gl_texture_2D_hpp__

// Include GLRenderer
#ifndef __c0de4un_gl_renderer_hpp__
#include "../../renderer/GLRenderer.hpp"
#endif // !__c0de4un_gl_renderer_hpp__

// Include PNGImage
#ifndef __c0de4un_png_image_hpp__
#include "../image/PNGImage.hpp"
#endif // !__c0de4un_png_image_hpp__

// Include Log
#ifndef __c0de4un_log_hpp__
#include "../../utils/log/Log.hpp"
#endif // !__c0de4un_log_hpp__

namespace c0de4un
{

	// -------------------------------------------------------- \\

	// ===========================================================
	// Constructor & destructor
	// ===========================================================

	/*
	 * GLTexture2D constructor
	 *
	 * @param pName - Name.
	 * @param pFile - Image-file path.
	*/
	GLTexture2D::GLTexture2D( const std::string & pName, const std::string & pFile )
		: mName( pName ),
		mFile( pFile ),
		mTextureObject( 0 ),
		mImage( nullptr )
	{

#ifdef DEBUG // DEBUG
		// Check Name
		if ( mName.empty( ) )
			throw std::exception( "GLTexture2D::constructor - Name is null" );

		// Check Image file path
		if ( pFile.empty( ) )
			throw std::exception( "GLTexture2D::constructor - Path to the image is null" );
#endif // DEBUG

		// Log
		std::string logMsg( "GLTexture2D#" );
		logMsg += mName;
		logMsg += "::constructor";
		Log::printDebug( logMsg.c_str( ) );

	}

	/* GLTexture2D destructor */
	GLTexture2D::~GLTexture2D( )
	{

		// Log
		std::string logMsg( "GLTexture2D#" );
		logMsg += mName;
		logMsg += "::destructor";
		Log::printDebug( logMsg.c_str( ) );

		// Release PNG Image
		if ( mImage )
		{

			// Delete PNGImage instance
			delete mImage;

			// Reset pointer-value
			mImage = nullptr;

		}

	}

	// ===========================================================
	// Getter & Setter
	// ===========================================================

	/* Returns 2D Texture Object ID */
	const GLuint & GLTexture2D::getTextureObject( ) const noexcept
	{ return( mTextureObject ); }

	// ===========================================================
	// Methods
	// ===========================================================

	/*
	 * Load this 2D Texture.
	 *
	 * @thread_safety - render-thread only.
	 * @return - 'true' if OK.
	 * @throws - can throw exception.
	*/
	const bool GLTexture2D::Load( )
	{

		// Cancel
		if ( mTextureObject > 0 )
			return( true );

		// Log
		std::string logMsg( "GLTexture2D#" );
		logMsg += mName;
		logMsg += "::Load";
		Log::printDebug( logMsg.c_str( ) );

		// Create PNGImage instance
		if ( mImage == nullptr )
			mImage = new PNGImage( mFile );

		// Load PNG Image
		if ( !mImage->Load( ) )
		{

			// Log
			logMsg = "GLTexture2D#";
			logMsg += mName;
			logMsg += "::Load - failed to load PNG Image #";
			logMsg += mFile;
			Log::printDebug( logMsg.c_str( ) );

			// Unload
			Unload( );

			// Cancel
			return( false );

		}

		// Create 2D-Texture Object
		glCreateTextures( GL_TEXTURE_2D, 1, &mTextureObject );

		// Bind 2D-Texture Object
		glBindTexture( GL_TEXTURE_2D, mTextureObject );

		// Mark that Texture Image Data is Tightly Packed (1 byte stride)
		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

		// OpenGL Color Format
		const GLenum & glColorForamt_ = mImage->mColorFormat;

		// Upload Image bytes from Local Memory (App Space) to OpenGL Memory (GPU/VRAM)
		glTexImage2D( GL_TEXTURE_2D, 0, glColorForamt_, mImage->mSize[0], mImage->mSize[1], 0, glColorForamt_, GL_UNSIGNED_BYTE, mImage->mBytes );

		// Set Texture Min. Filter to Nearest, cause smoothing not required (zooming, etc)
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

		// Set Texture Mag. Filter to Nearest, cause smoothing not required (zooming, etc)
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		// Set Texture S (U/X) Wrap-Method to Clamp to edge (repeat and others not required)
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );

		// Set Texture T (V/Y) Wrap-Method to Clamp to edge (repeat and others not required)
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );

		// Unbind Texture
		glBindTexture( GL_TEXTURE_2D, 0 );

		// Unload & release PNGImage
		//delete mImage;
		//mImage = nullptr;

		// Return TRUE
		return( true );

	}

	/*
	 * Unload 2D Texture.
	 *
	 * @thread_safety - render-thread only.
	 * @throws - can throw exception.
	*/
	void GLTexture2D::Unload( )
	{

		// Log
		std::string logMsg( "GLTexture2D#" );
		logMsg += mName;
		logMsg += "::Unload";
		Log::printDebug( logMsg.c_str( ) );

		// Delete OpenGL 2D-Texture Object
		glDeleteTextures( 1, &mTextureObject );

		// Reset 2D-Texture Object ID
		mTextureObject = 0;

		// Release PNGImage
		if ( mImage != nullptr )
		{

			// Delete PNGImage instance
			delete mImage;

			// Reset pointer-value
			mImage = nullptr;

		}

	}

	// -------------------------------------------------------- \\

}