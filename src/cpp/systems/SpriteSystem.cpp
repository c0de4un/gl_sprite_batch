/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

// HEADER
#ifndef __c0de4un_sprite_system_hpp__
#include "SpriteSystem.hpp"
#endif // !__c0de4un_sprite_system_hpp__

// Include Random
#ifndef __c0de4un_random_hpp__
#include "../utils/random/Random.hpp"
#endif // !__c0de4un_random_hpp__

// Include Sprite
#ifndef __c0de4un_sprite_hpp__
#include "../objects/sprite/Sprite.hpp"
#endif // !__c0de4un_sprite_hpp__

// Include GLShaderProgram
#ifndef __c0de4un_gl_shader_program_hpp__
#include "../assets/shader/GLShaderProgram.hpp"
#endif // !__c0de4un_gl_shader_program_hpp__

// Include GLTexture2D
#ifndef __c0de4un_gl_texture_2D_hpp__
#include "../assets/texture/GLTexture2D.hpp"
#endif // !__c0de4un_gl_texture_2D_hpp__

// Include Position
// Include Rotation
// Include Scale
// Include Velocity
#ifndef __c0de4un_velocity_hpp__
#include "../components/Velocity.hpp"
#endif // !__c0de4un_velocity_hpp__

// Include Components
#ifndef __c0de4un_components_hpp__
#include "../components/Components.hpp"
#endif // !__c0de4un_components_hpp__

// Include GLRenderer
#ifndef __c0de4un_gl_renderer_hpp__
#include "../renderer/GLRenderer.hpp"
#endif // !__c0de4un_gl_renderer_hpp__

// Include Log
#ifndef __c0de4un_log_hpp__
#include "../utils/log/Log.hpp"
#endif // !__c0de4un_log_hpp__

namespace c0de4un
{

	// -------------------------------------------------------- \\

	// ===========================================================
	// Constructor & destructor
	// ===========================================================

	/*
	 * SpriteSystem constructor
	 *
	 * @param pRandom_ - random numbers generator (wrapper).
	 * @param worldWidth_ - World Width.
	 * @param worldHeight_ - World Height.
	 * @param maxSprites_ - Sprites limit.
	*/
	SpriteSystem::SpriteSystem( Random *const pRandom_, const unsigned int & worldWidth_, const unsigned int & worldHeight_, const unsigned int & maxSprites_ )
		: mRandom( pRandom_ ),
		mSprites( ),
		mWorldWidth( worldWidth_ ),
		mWorldHeight( worldHeight_ ),
		mMaxSprites( maxSprites_ ),
		mSpriteMaxSize( (unsigned int)( (float) worldWidth_ / (float) maxSprites_ ) ),
		mSpriteMinSize( 1 ),
		mMutex( ),
		mLock( mMutex, std::defer_lock )
	{

		// Log
		Log::printDebug( "SpriteSystem::constructor" );

	}

	/* SpriteSystem destructor */
	SpriteSystem::~SpriteSystem( )
	{

		// Log
		Log::printDebug( "SpriteSystem::destructor" );

		// Release Sprites ( delete[] )
		for ( Sprite *const sprite_ : mSprites )
		{

			// Delete Sprite
			delete sprite_;

		}

	}

	// ===========================================================
	// Getter & Setter
	// ===========================================================

	/*
	 * Generates random position.
	 * Result depends on world size.
	 *
	 * @thread_safety - not thread-safe.
	 * @param pSize - size. Used to avoid 'off-screen' position.
	 * @return - vec3.
	*/
	const glm::vec3 SpriteSystem::getRandomPosition( const unsigned int & pSize_ ) noexcept
	{

		// X
		const int x_( mRandom->getUint32( pSize_, mWorldWidth - ( pSize_ ) ) );

		// Y
		const int y_( mRandom->getUint32( pSize_, mWorldHeight - ( pSize_ ) ) );

		// Return result
		return( glm::vec3( static_cast<float>( x_ ), static_cast<float>( y_ ), 0.0f ) );

	}

	/*
	 * Generates random size.
	 *
	 * Result depends on world size.
	 *
	 * @thread_safety - not thread-safe.
	 * @return - vec3.
	*/
	const glm::vec3 SpriteSystem::getRandomSize( ) noexcept
	{

		// Get Random size
		const int size_( mRandom->getUint32( mSpriteMinSize, mSpriteMaxSize ) );
		
		// Create & return vec3
		return( glm::vec3( static_cast<float>( size_ ), static_cast<float>( size_ ), 0.0f ) );

	}

	/*
	 * Generates random velocity.
	 *
	 * @thread_safety - not thread-safe.
	 * @return - vec3.
	*/
	const glm::vec3 SpriteSystem::getRandomVelocity( ) noexcept
	{

		// X-Direction
		const int xDirection_ = mRandom->getUint32( 0, 1 );

		// X-Velocity
		const float xVelocity_( xDirection_ > 0 ? 1.0f : -1.0f );

		// Y-Direction
		const int yDirection_ = mRandom->getUint32( 0, 1 );

		// Y-Velocity
		const float yVelocity_( yDirection_ > 0 ? 1.0f : -1.0f );

		// Return result
		return( glm::vec3( xVelocity_, yVelocity_, 0.0f ) );

	}

	// ===========================================================
	// Methods
	// ===========================================================	

	/*
	 * Update Sprites.
	 *
	 * @param elapsedTime_ - time in seconds elapsed since previous frame (update-call).
	*/
	void SpriteSystem::Update( const double & elapsedTime_ )
	{

		// Update Sprites
		for ( Sprite *const sprite_lp : mSprites )
		{

			// Lock Sprite
			sprite_lp->mLock.lock( );

			// Position-vector
			glm::vec3 & posVec_ = sprite_lp->mPosition.vec3_;

			// Velocity-vector
			glm::vec3 & velVec_ = sprite_lp->mVelocity.vec3_;

			// Size-vector
			glm::vec3 & sizeVec_ = sprite_lp->mScale.vec3_;

			// X-axis
			if ( velVec_.x > 0 )
			{// +X

				// Move right
				if ( ( posVec_.x + velVec_.x ) < ( mWorldWidth - sizeVec_.x ) )
				{

					// Translate (move) by X-axis
					posVec_.x += velVec_.x;

					// Request Sprite-update
					sprite_lp->mDrawable.stateChanged_ = true;

				}
				else // Right Border Reached
				{

					// Invert Velocity by X-axis
					velVec_.x = velVec_.x * -1;

				}
			}
			else
			{// -X

				// Move left
				if ( ( posVec_.x - velVec_.x ) > ( sizeVec_.x ) )
				{

					// Translate (move) by X-axis
					posVec_.x += velVec_.x;

					// Request Sprite-update
					sprite_lp->mDrawable.stateChanged_ = true;

				}
				else // Right Border Reached
				{

					// Invert Velocity by X-axis
					velVec_.x = velVec_.x * -1;

				}

			}
			
			// Y-axis
			if ( velVec_.y > 0 )
			{// +Y

				// Move Up
				if ( ( posVec_.y + velVec_.y ) < ( mWorldHeight - sizeVec_.y ) )
				{

					// Translate (move) by Y-axis
					posVec_.y += velVec_.y;

					// Request Sprite-update
					sprite_lp->mDrawable.stateChanged_ = true;

				}
				else // Top Border Reached
				{

					// Invert Velocity by Y-axis
					velVec_.y = velVec_.y * -1;

				}
			}
			else
			{// -Y (Down)

				// Move down
				if ( ( posVec_.y - velVec_.y ) > ( sizeVec_.y ) )
				{

					// Translate (move) by Y-axis
					posVec_.y += velVec_.y;

					// Request Sprite-update
					sprite_lp->mDrawable.stateChanged_ = true;

				}
				else // Bottom Border Reached
				{

					// Invert Velocity by Y-axis
					velVec_.y = velVec_.y * -1;

				}

			}

			// Unlock Sprite
			sprite_lp->mLock.unlock( );

		} // Update Sprites

	}

	/*
	 * Stop this SpriteSystem.
	 * Used to remove all Sprites from Sprite-Batching system.
	 *
	 * @thread_safety - thread-safe.
	 * @param renderManager_ - Render system (OpenGL renderer, Sprite-Batching-System).
	*/
	void SpriteSystem::Stop( GLRenderer *const renderManager_ )
	{

		// Log
		Log::printDebug( "SpriteSystem::Stop" );

		// Release Sprites ( delete[] )
		for ( Sprite *const sprite_ : mSprites )
		{

			// Hide Sprite
			sprite_->Hide( renderManager_ );

		}

	}

	/*
	 * Add random sprite with random attributes (properties).
	 *
	 * (!) Shader Program & 2D-Texture must be already loaded, to avoid concurrency errors, in case
	 * when loading to GPU (OpenGL memory-space) using not render-thread (or main/ui/system).
	 *
	 * @thread_safety - thread-safe.
	 * @param shaderProgram_ - Shader Program.
	 * @param texture2D_ - 2D-Texture.
	 * @param renderSystem_ - Renderer (render manager/system).
	*/
	void SpriteSystem::addSprite( GLShaderProgram & shaderProgram_, GLTexture2D *const texture2D_, GLRenderer *const renderSystem_ )
	{

		// Lock
		mLock.lock( );

		// Cancel
		if ( mSprites.size( ) >= mMaxSprites )
		{

			// Log
			Log::printDebug( "SpriteSystem::addSprite - limit reached !" );

			// Unlock
			mLock.unlock( );

			// Return
			return;

		}

		// Create Sprite
		const std::string spriteName_( "sprite_" + std::to_string( mSprites.size( ) ) );
		Sprite *const sprite_( new Sprite( spriteName_, shaderProgram_, texture2D_ ) );

		// Random Sprite size
		sprite_->mScale.vec3_ = getRandomSize( );

		// Random Sprite position
		sprite_->mPosition.vec3_ = getRandomPosition( static_cast<const unsigned int>( sprite_->mScale.vec3_.x ) );

		// Random Sprite velocity
		sprite_->mVelocity.vec3_ = getRandomVelocity( );

		// Add Sprite to the collection (Sprites container)
		mSprites.push_back( sprite_ );

		// Unlock
		mLock.unlock( );

		// Add Sprite to the Sprite-Batching system
		sprite_->Show( renderSystem_ );

	}

	// -------------------------------------------------------- \\

}