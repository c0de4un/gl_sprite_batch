/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_sprite_hpp__
#define __c0de4un_sprite_hpp__

// Include mutex
#ifndef __c0de4un_mutex_hpp__
#include "../../cfg/mutex.hpp" // std::mutex, std::unique_lock
#endif // !__c0de4un_mutex_hpp__

// Include GameObject
#ifndef __c0de4un_game_object_hpp__
#include "../GameObject.hpp"
#endif // !__c0de4un_game_object_hpp__

// Forward-declaration of GLShaderProgram
#ifndef __c0de4un_gl_shader_program_decl__
#define __c0de4un_gl_shader_program_decl__
namespace c0de4un { class GLShaderProgram; }
#endif // !__c0de4un_gl_shader_program_decl__

// Forward-declaration of  GLTexture2D
#ifndef __c0de4un_gl_texture_2D_decl__
#define __c0de4un_gl_texture_2D_decl__
namespace c0de4un { class GLTexture2D; }
#endif // !__c0de4un_gl_texture_2D_decl__

// Forward-declaration of GLRenderer
#ifndef __c0de4un_gl_renderer_decl__
#define __c0de4un_gl_renderer_decl__
namespace c0de4un { class GLRenderer; }
#endif // !__c0de4un_gl_renderer_decl__

// Include Drawable
#ifndef __c0de4un_drawable_hpp__
#include "../../renderer/batch/Drawable.hpp"
#endif // !__c0de4un_drawable_hpp__

// Include Position
#ifndef __c0de4un_position_hpp__
#include "../../components/Position.hpp"
#endif // !__c0de4un_position_hpp__

// Include Rotation
#ifndef __c0de4un_rotation_hpp__
#include "../../components/Rotation.hpp"
#endif // !__c0de4un_rotation_hpp__

// Include Scale
#ifndef __c0de4un_scale_hpp__
#include "../../components/Scale.hpp"
#endif // !__c0de4un_scale_hpp__

// Include Velocity
#ifndef __c0de4un_velocity_hpp__
#include "../../components/Velocity.hpp"
#endif // !__c0de4un_velocity_hpp__

// Sprite declared
#define __c0de4un_sprite_decl__

namespace c0de4un
{

	/*
	 * Sprite - sprite game object.
	 *
	 * @version 1.0
	*/
	class Sprite final : public c0de4un::GameObject
	{

	private:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Fields
		// ===========================================================

		/* Shader Program */
		GLShaderProgram & mShaderProgram;

		/* GLTexture */
		GLTexture2D *const mGLTexture2D;

		/* Visibility flag */
		bool mVisible;

		/* Mutex */
		std::mutex mMutex;

		// ===========================================================
		// Deleted
		// ===========================================================

		/* @deleted Sprite const copy constructor */
		explicit Sprite( const Sprite & ) noexcept = delete;

		/* @deleted Sprite const copy assignment operator */
		Sprite & operator=( const Sprite & ) noexcept = delete;

		/* @deleted Sprite move constructor */
		explicit Sprite( Sprite && ) noexcept = delete;

		/* @deleted Sprite move assignment operator */
		Sprite && operator=( Sprite && ) noexcept = delete;

		// -------------------------------------------------------- \\

	public:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Fields
		// ===========================================================

		/* Drawable */
		Drawable mDrawable;

		/* Position component. */
		Position mPosition;

		/* Rotation component */
		Rotation mRotation;

		/* Scale component */
		Scale mScale;

		/* Velocity */
		Velocity mVelocity;

		/* Thread-Lock */
		std::unique_lock<std::mutex> mLock;

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
		explicit Sprite( const std::string & pName, GLShaderProgram & shaderprogram_, GLTexture2D *const texture2D_ );

		/* Sprite destructor */
		virtual ~Sprite( );

		// ===========================================================
		// Getter & Setter
		// ===========================================================

		/* Returns 'TRUE' if visible (added in Sprite-Batching) */
		const bool isVisible( ) const noexcept;

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
		const bool Show( GLRenderer *const renderSystem_ );

		/*
		 * Hide this Sprite (remove from batching-system).
		 *
		 * @thread_safety - render-thread only.
		 * @param renderSystem_ - GLRenderer. Used for Sprite-Batching.
		 * @throws - can throw exception.
		*/
		void Hide( GLRenderer *const renderSystem_ );

		// -------------------------------------------------------- \\

	};

}

#endif // !__c0de4un_sprite_hpp__