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
	{// TODO GLTexture2D::Load

		// Cancel
		if ( mTextureObject > 0 )
			return( true );

		// Log
		std::string logMsg( "GLTexture2D#" );
		logMsg += mName;
		logMsg += "::Load";
		Log::printDebug( logMsg.c_str( ) );

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
	{// TODO GLTexture2D::Unload

		// Cancel
		if ( mTextureObject < 1 )
			return;

		// Log
		std::string logMsg( "GLTexture2D#" );
		logMsg += mName;
		logMsg += "::Unload";
		Log::printDebug( logMsg.c_str( ) );

	}

	// -------------------------------------------------------- \\

}