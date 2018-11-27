/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

// HEADER
#ifndef __c0de4un_sprite_hpp__
#include "Sprite.hpp"
#endif // !__c0de4un_sprite_hpp__

// Include GLShaderProgram
#ifndef __c0de4un_gl_shader_program_hpp__
#include "../../assets/shader/GLShaderProgram.hpp"
#endif // !__c0de4un_gl_shader_program_hpp__

// Include GLTexture2D
#ifndef __c0de4un_gl_texture_2D_hpp__
#include "../../assets/texture/GLTexture2D.hpp"
#endif // !__c0de4un_gl_texture_2D_hpp__

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
	 * Sprite constructor
	 *
	 * @param pName - Name.
	 * @param shaderProgram_ - Shader Program.
	 * @param texture2D_ - 2D Texture.
	*/
	Sprite::Sprite( const std::string & pName, GLShaderProgram & shaderprogram_, GLTexture2D & texture2D_ )
		: GameObject( pName ),
		mShaderProgram( shaderprogram_ ),
		mGLTexture2D( texture2D_ ),
		mVisible( false ),
		mDrawable( ),
		mLock( mMutex, std::defer_lock ),
		mPosition { false, glm::vec3( 0.0f, 0.0f, 0.0f ), &mLock },
		mRotation { false, glm::vec3( 0.0f, 0.0f, 0.0f ), &mLock },
		mScale { false, glm::vec3( 0.0f, 0.0f, 0.0f ), &mLock }
	{

		// Log
		std::string logMsg( "Sprite#" );
		logMsg += mName;
		logMsg += "::constructor";
		Log::printDebug( logMsg.c_str( ) );

	}

	/* Sprite destructor */
	Sprite::~Sprite( )
	{

		// Log
		std::string logMsg( "Sprite#" );
		logMsg += mName;
		logMsg += "::destructor";
		Log::printDebug( logMsg.c_str( ) );

	}

	// ===========================================================
	// Getter & Setter
	// ===========================================================

	/* Returns 'TRUE' if visible (added in Sprite-Batching) */
	const bool Sprite::isVisible( ) const noexcept
	{ return( mVisible ); }

	// ===========================================================
	// Methods
	// ===========================================================

	/*
	 * Make this Sprite visible.
	 * Also load texture & shaders if required.
	 *
	 * @thread_safety - render-thread only.
	 * @param renderSystem_ - GLRenderer. Used for Sprite-Batching.
	 * @return - 'true' if OK.
	 * @throws - can throw exception.
	*/
	const bool Sprite::Show( GLRenderer *const renderSystem_ )
	{// TODO Sprite::Show

		// Cancel
		if ( mVisible )
			return( true );

		// Lock
		mLock.lock( );

		// Log
		std::string logMsg( "Sprite#" );
		logMsg += mName;
		logMsg += "::Show";
		Log::printDebug( logMsg.c_str( ) );

		// Set Drawable Position
		mDrawable.position_ = &mPosition;

		// Unlock
		mLock.unlock( );

	}

	/*
	 * Hide this Sprite (remove from batching-system).
	 *
	 * @thread_safety - render-thread only.
	 * @param renderSystem_ - GLRenderer. Used for Sprite-Batching.
	 * @throws - can throw exception.
	*/
	void Sprite::Hide( GLRenderer *const renderSystem_ )
	{// TODO Sprite::Hide

		// Cancel
		if ( !mVisible )
			return;

		// Log
		std::string logMsg( "Sprite#" );
		logMsg += mName;
		logMsg += "::Hide";
		Log::printDebug( logMsg.c_str( ) );

	}

	// -------------------------------------------------------- \\

}