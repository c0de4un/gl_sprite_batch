/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_gl_renderer_hpp__
#define __c0de4un_gl_renderer_hpp__

// Include std::map
#ifndef __c0de4un_map_hpp__
#include "../cfg/map.hpp"
#endif // !__c0de4un_map_hpp__

// Include std::vector
#ifndef __c0de4un_vector_hpp__
#include "../cfg/vector.hpp"
#endif // !__c0de4un_vector_hpp__

// Include Drawable
#ifndef __c0de4un_drawable_hpp__
#include "batch/Drawable.hpp"
#endif // !__c0de4un_drawable_hpp__

// GLRenderer declared
#define __c0de4un_gl_renderer_decl__

namespace c0de4un
{

	/*
	 * GLRenderer - renderer for OpenGL 3+ API.
	 * 
	 * @features
	 * - sprite-batching ;
	 * - OpenGL 3+ API (VAO, VBO, instancing) ;
	 * 
	 * @version 1.0
	*/
	class GLRenderer final
	{

	private:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Types
		// ===========================================================

		/* Type-alias for Drawable pointer */
		using drawable_ptr_t = Drawable *const;

		/* Type-alias for vector with Drawable-Objects */
		using drawables_vector_t = std::vector<drawable_ptr_t>;

		/* Type-alias for map of vectors with Drawable-Objects */
		using textures_map_t = std::map<const GLuint, drawables_vector_t>;

		/* Type-alias for map to sort drawable-objects by their shader program id */
		using programs_map_t = std::map<const GLuint, textures_map_t>;

		// ===========================================================
		// Constants
		// ===========================================================

		/* Shader Program Sampler */
		static constexpr const char *const TEXTURE_2D_SAMPLER = "";

		/* Vertices Attributes */

		// ===========================================================
		// Fields
		// ===========================================================

		/* Map to sort Drawable-Objects by Shader Programs & Textures */
		programs_map_t mPrograms;

		/* Thread-Lock to synchronize access */
		std::unique_lock<std::mutex> mLock;

		/* Mutex */
		std::mutex mMutex_;

		// ===========================================================
		// Deleted
		// ===========================================================

		/* @deleted GLRenderer const copy constructor */
		explicit GLRenderer( const GLRenderer & ) = delete;

		/* @deleted GLRenderer copy assignment operator */
		GLRenderer & operator=( const GLRenderer & ) = delete;

		/* @deleted GLRenderer move constructor */
		explicit GLRenderer( GLRenderer && ) = delete;

		/* @deleted GLRenderer move assignment operator */
		GLRenderer & operator=( GLRenderer && ) = delete;

		// ===========================================================
		// Methods
		// ===========================================================

		/*
		 * Draws given Drawable-Object (Sprite).
		 *
		 * @thread_safety - render-thread only.
		 * @param pDrawable - Drawable-Component.
		*/
		inline void drawSprite( drawable_ptr_t const pDrawable );

		// -------------------------------------------------------- \\

	public:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Constructor & destructor
		// ===========================================================

		/*
		 * GLRenderer constructor.
		 *
		 * @throws - std::bad_alloc.
		*/
		explicit GLRenderer( );

		/* GLRenderer destructor */
		~GLRenderer( );

		// ===========================================================
		// Methods
		// ===========================================================

		/*
		 * Compile & upload Shader Program with Vertex Shader & Fragment Shader
		 * to the OpenGL memory-space (GPU).
		 *
		 * @thread_safety - render-thread only.
		 * @return - 'TRUE' if OK, false if failed.
		*/
		const bool loadShader( );

		/*
		 * Upload 2D Texture data to the OpenGL memory-space (GPU).
		 *
		 * @thread_safety - render-thread only.
		 * @return - 'TRUE' if OK, false if failed.
		*/
		const bool loadTexture2D( );

		/*
		 * 
		 * 
		 * @thread_safety - thread-lock used.
		*/
		void addDrawable( );

		/*
		 * 
		 * 
		 * @thread_safety - thread-lock used.
		*/
		void removeDrawable( );

		/*
		 * Draw (render).
		*/
		inline void Draw( );

		// -------------------------------------------------------- \\

	};

}

#endif // !__c0de4un_gl_renderer_hpp__