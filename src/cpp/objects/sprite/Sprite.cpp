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

// Include BatchRequest
#ifndef __c0de4un_batch_request_hpp__
#include "../../renderer/batch/BatchRequest.hpp"
#endif // !__c0de4un_batch_request_hpp__

// Include GLRenderer
#ifndef __c0de4un_gl_renderer_hpp__
#include "../../renderer/GLRenderer.hpp"
#endif // !__c0de4un_gl_renderer_hpp__

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
	Sprite::Sprite( const std::string & pName, GLShaderProgram & shaderprogram_, GLTexture2D *const texture2D_ )
		: GameObject( pName ),
		mShaderProgram( shaderprogram_ ),
		mGLTexture2D( texture2D_ ),
		mVisible( false ),
		mDrawable( ),
		mLock( mMutex, std::defer_lock ),
		mPosition { false, glm::vec3( 0.0f, 0.0f, 0.0f ), &mLock },
		mRotation { false, glm::vec3( 0.0f, 0.0f, 0.0f ), &mLock },
		mScale { false, glm::vec3( 100.0f, 100.0f, 0.0f ), &mLock }
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
	{

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

		// Load Shader Program
		if ( !mShaderProgram.Load( ) )
		{

			// Log
			logMsg = "Sprite#";
			logMsg += mName;
			logMsg += "::Show - failed to load shader program#";
			logMsg += mShaderProgram.getName( );
			Log::printDebug( logMsg.c_str( ) );

			// Cancel
			return( false );

		}

		// Load 2D-Texture
		if ( mGLTexture2D != nullptr && !mGLTexture2D->Load( ) )
		{

			// Log
			logMsg = "Sprite#";
			logMsg += mName;
			logMsg += "::Show - failed to load shader program#";
			logMsg += mShaderProgram.getName( );
			Log::printDebug( logMsg.c_str( ) );

			// Cancel
			return( false );

		}

		// Set OpenGL Texture Object ID
		mDrawable.textureObject_ = mGLTexture2D != nullptr ? mGLTexture2D->getTextureObject( ) : 0;

		// Set OpenGL Shader Program ID
		mDrawable.shaderProgram_ = mShaderProgram.getProgramObject( );

		// Set Drawable Position
		mDrawable.position_ = &mPosition;
		mDrawable.position_->changed_ = true;

		// Set Drawable Rotation
		mDrawable.rotation_ = &mRotation;
		mDrawable.rotation_->changed_ = true;

		// Set Drawable Scale
		mDrawable.scale_ = &mScale;
		mDrawable.scale_->changed_ = true;

		// Set Drawable Lock
		mDrawable.lock_ = &mLock;

		// Set State changed flag
		mDrawable.stateChanged_ = true;

		// Create BatchRequest
		BatchRequest batchRequest_;

		// Set Shader Program Object
		batchRequest_.shaderProgram_ = mDrawable.shaderProgram_;

		// Set Vertex Position attribute location/index
		batchRequest_.vertexPosAttrIndex_ = mShaderProgram.getVertexPosAttrIndex( );

		// Set Vertex Color attribute location/index
		batchRequest_.colorAttrIndex_ = mShaderProgram.getColorAttrIndex( );

		// Set Vertex 2D-Texture Coordinates attribute location/index
		batchRequest_.texCoordsAttrIndex_ = mShaderProgram.getVertexTexCoordsAttrIndex( );

		// Set MVP (Model View Projection) Matrix uniform location/index
		batchRequest_.mvpMatUniformIndex_ = mShaderProgram.getMVPUniform( );

		// Set Drawable
		batchRequest_.drawable_ = &mDrawable;

		// Set 2D-Texture Sampler

		// Add Drawable to batching
		renderSystem_->addDrawable( batchRequest_ );

		// Set Visible flag
		mVisible = true;

		// Unlock
		mLock.unlock( );

		// Return TRUE
		return( true );

	}

	/*
	 * Hide this Sprite (remove from batching-system).
	 *
	 * @thread_safety - render-thread only.
	 * @param renderSystem_ - GLRenderer. Used for Sprite-Batching.
	 * @throws - can throw exception.
	*/
	void Sprite::Hide( GLRenderer *const renderSystem_ )
	{

		// Cancel
		if ( !mVisible )
			return;

		// Log
		std::string logMsg( "Sprite#" );
		logMsg += mName;
		logMsg += "::Hide";
		Log::printDebug( logMsg.c_str( ) );

		// Lock
		mLock.lock( );

		// Remove Drawable
		renderSystem_->removeDrawable( &mDrawable, mShaderProgram.getProgramObject( ), mGLTexture2D != nullptr ? mGLTexture2D->getTextureObject( ) : 0 );

		// Set Visible flag
		mVisible = false;

		// Unlock
		mLock.unlock( );

	}

	// -------------------------------------------------------- \\

}