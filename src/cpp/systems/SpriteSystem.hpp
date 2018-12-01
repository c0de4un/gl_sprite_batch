/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_sprite_system_hpp__
#define __c0de4un_sprite_system_hpp__

// Include std::vector
#ifndef __c0de4un_vector_hpp__
#include "../cfg/vector.hpp"
#endif // !__c0de4un_vector_hpp__

// Include mutex
#ifndef __c0de4un_mutex_hpp__
#include "../cfg/mutex.hpp" // std::mutex, std::unique_lock
#endif // !__c0de4un_mutex_hpp__

// Include glm
#ifndef __c0de4un_glm_hpp__
#include "../cfg/glm.hpp"
#endif // !__c0de4un_glm_hpp__

// Forward-declaration of Random
#ifndef __c0de4un_random_decl__
#define __c0de4un_random_decl__
namespace c0de4un { class Random; }
#endif // !__c0de4un_random_decl__

// Forward-declaration of Sprite
#ifndef __c0de4un_sprite_decl__
#define __c0de4un_sprite_decl__
namespace c0de4un { class Sprite; }
#endif // !__c0de4un_sprite_decl__

// Forward-declare GLShaderProgram
#ifndef __c0de4un_gl_shader_program_decl__
#define __c0de4un_gl_shader_program_decl__
namespace c0de4un { class GLShaderProgram; }
#endif // !__c0de4un_gl_shader_program_decl__

// Forward-declared GLTexture2D
#ifndef __c0de4un_gl_texture_2D_decl__
#define __c0de4un_gl_texture_2D_decl__
namespace c0de4un { class GLTexture2D; }
#endif // !__c0de4un_gl_texture_2D_decl__

// Forward-declaration of GLRenderer
#ifndef __c0de4un_gl_renderer_decl__
#define __c0de4un_gl_renderer_decl__
namespace c0de4un { class GLRenderer; }
#endif // !__c0de4un_gl_renderer_decl__

// Forward-declaration of Position
// Forward-declaration of Rotation
// Forward-declaration of Scale

// SpriteSystem declared
#define __c0de4un_sprite_system_decl__

namespace c0de4un
{

	/*
	 * SpriteSystem - handles sprites.
	 * 
	 * @features
	 * - rotation, move (translation), scale modifications ;
	 * - simple 2D physics ;
	 *
	 * @version 1.0.0
	*/
	class SpriteSystem final
	{

	public:

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
		explicit SpriteSystem( Random *const pRandom_, const unsigned int & worldWidth_, const unsigned int & worldHeight_, const unsigned int & maxSprites_ );

		/* SpriteSystem destructor */
		~SpriteSystem( );

		// ===========================================================
		// Methods
		// ===========================================================	

		/*
		 * Update Sprites.
		 *
		 * @param elapsedTime_ - time in seconds elapsed since previous frame (update-call).
		*/
		void Update( const double & elapsedTime_ );

		/*
		 * Stop this SpriteSystem.
		 * Used to remove all Sprites from Sprite-Batching system.
		 *
		 * @thread_safety - thread-safe.
		 * @param renderManager_ - Render system (OpenGL renderer, Sprite-Batching-System).
		*/
		void Stop( GLRenderer *const renderManager_ );

		/*
		 * Add random sprite with random attributes (properties).
		 *
		 * (!) Shader Program & 2D-Texture must be already loaded, to avoid concurrency errors, in case
		 * when loading to GPU (OpenGL memory-space) using not render-thread (or main/ui/system).
		 *
		 * @thread_safety - thread-safe.
		 * @param shaderProgram_ - Shader Program.
		 * @param texture2D_ - 2D-Texture, can be null.
		 * @param renderSystem_ - Renderer (render manager/system).
		*/
		void addSprite( GLShaderProgram & shaderProgram_, GLTexture2D *const texture2D_, GLRenderer *const renderSystem_ );

		// -------------------------------------------------------- \\

	private:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Constants
		// ===========================================================

		/* Random-numbers generator (wrapper). */
		Random *const mRandom;

		/* World Width */
		const unsigned int mWorldWidth;

		/* World Height */
		const unsigned int mWorldHeight;

		/* Max. Sprite size, depends on world width. */
		const unsigned int mSpriteMaxSize;

		/* Min. Sprite size, depends on world height. */
		const unsigned int mSpriteMinSize;

		/* Sprites limit. */
		const unsigned int mMaxSprites;

		// ===========================================================
		// Fields
		// ===========================================================

		/* Sprites */
		std::vector<Sprite*> mSprites;

		/* Mutex */
		std::mutex mMutex;

		/* Thread-lock to synchronize access to the Sprites collection (container) */
		std::unique_lock<std::mutex> mLock;

		// ===========================================================
		// Deleted
		// ===========================================================

		/* @deleted SpriteSystem const copy constructor */
		SpriteSystem( const SpriteSystem & ) = delete;

		/* @deleted SpriteSystem const copy assignment operator */
		SpriteSystem operator=( const SpriteSystem & ) = delete;

		/* @deleted SpriteSystem move constructor */
		SpriteSystem( SpriteSystem && ) = delete;

		/* @deleted SpriteSystem move assignment operator */
		SpriteSystem & operator=( SpriteSystem && ) = delete;

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
		const glm::vec3 getRandomPosition( const unsigned int & pSize_ ) noexcept;

		/*
		 * Generates random size.
		 *
		 * Result depends on world size.
		 *
		 * @thread_safety - not thread-safe.
		 * @return - vec3.
		*/
		const glm::vec3 getRandomSize( ) noexcept;

		/*
		 * Generates random velocity.
		 *
		 * @thread_safety - not thread-safe.
		 * @return - vec3.
		*/
		const glm::vec3 getRandomVelocity( ) noexcept;

		// -------------------------------------------------------- \\

	};

}

#endif // !__c0de4un_sprite_system_hpp__