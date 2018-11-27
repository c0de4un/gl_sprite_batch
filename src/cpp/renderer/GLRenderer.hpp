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

// Forward-declaration of BatchInfo
#ifndef __c0de4un_batch_info_decl__
#define __c0de4un_batch_info_decl__
namespace c0de4un { struct BatchInfo; }
#endif // !__c0de4un_batch_info_decl__

// Forward-declaration of BatchRequest
#ifndef __c0de4un_batch_request_decl__
#define __c0de4un_batch_request_decl__
namespace c0de4un { struct BatchRequest; }
#endif // !__c0de4un_batch_request_decl__

// Forward-declaration of ViewProjection
#ifndef __c0de4un_view_projection_decl__
#define __c0de4un_view_projection_decl__
namespace c0de4un { struct ViewProjection; }
#endif // !__c0de4un_view_projection_decl__

// Forward-declare GLCamera
#ifndef __c0de4un_gl_camera_decl__
#define __c0de4un_gl_camera_decl__
namespace c0de4un { class GLCamera; }
#endif // !__c0de4un_gl_camera_decl__

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

		/*
		 * Type-alias for the Shader Program Objects IDs map.
		 * Used to sort Drawable-Objects by Shader Program Object ID.
		*/
		using programs_map_t = std::map<const GLuint, BatchInfo>;

		// ===========================================================
		// Config
		// ===========================================================

		/* Vertices Count */
		static constexpr unsigned char VERTICES_COUNT = 4;

		/* Vertex Size (not length in bytes) */
		static constexpr unsigned char VERTEX_POSITION_SIZE = 4;

		/* Vertex Position Length in bytes */
		static constexpr unsigned char VERTEX_POSITION_LENGTH = VERTEX_POSITION_SIZE * sizeof( float );

		/* Vertices Position Buffer Length */
		static constexpr unsigned char VERTICES_POSITION_LENGTH = VERTICES_COUNT * VERTEX_POSITION_LENGTH;

		/* Indices Count */
		static constexpr unsigned char INDICES_COUNT = 6;

		/* Texture Coordinates Count */
		static constexpr unsigned char TEXTURE_COORDS_COUNT = VERTICES_COUNT;

		/* Texture Coordinates Size (not length, but number of elements) */
		static constexpr unsigned char TEXTURE_COORD_SIZE = 2;

		// ===========================================================
		// Constants
		// ===========================================================

		/* Vertices Position Buffer (local, app-space) */
		float mVerticesPosition[VERTICES_COUNT * VERTEX_POSITION_SIZE]; // 4 float values, 4 vertices

		/* Vertices Indices Buffer (local, app-space) */
		unsigned short mVerticesIndices[INDICES_COUNT];

		/* Vertices Texture Coordinates */
		float mVerticesTextureCoords[TEXTURE_COORDS_COUNT * TEXTURE_COORD_SIZE];

		// ===========================================================
		// Fields
		// ===========================================================

		/* Map to sort Drawable-Objects by Shader Programs & Textures */
		programs_map_t mPrograms;

		/* Thread-Lock to synchronize access */
		std::unique_lock<std::mutex> mLock;

		/* Mutex */
		std::mutex mMutex_;

		/* Vertex Array Object */
		GLuint mVAO_;

		/* Vertex Buffer Object ('VBO') for Vertices-Position data */
		GLuint verticesPosition_VBO_;

		/* Vertex Buffer Object ('VBO', 'IBO') for indices */
		GLuint indices_VBO_;

		/* Vertex Buffer Object ('VBO') for Texture Coordinates */
		GLuint textureCoords_VBO_;

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
		 * @param mvpMatUniformIndex_ - 
		 * @param viewProjection_ - 
		*/
		inline void drawSprite( Drawable *const pDrawable, const GLuint & mvpMatUniformIndex_, const ViewProjection & viewProjection_ );

		/*
		 * Load Sprite-Batch.
		 * Allocates buffers, writes mesh data (vertices positions, indices),
		 * creates & fills OpenGL Buffers (VBOs, VAO).
		 *
		 * @thread_safety - render-thread only.
		 * @param batchInfo - Sprite-Batching component.
		 * @return - 'true' if OK, false if failed.
		 * @throws - can throw exception.
		*/
		const bool loadSpriteBatch( const bool hasTexture, BatchInfo & batchInfo );

		/*
		 * Unloads Sprite-Batch.
		 * Deletes OpenGL Buffer Objects (VBOs, VAO).
		 *
		 * @thread_safety - render-thread only.
		 * @param batchInfo - Sprite-Batching component.
		 * @throws - can throw exception.
		*/
		void unloadSpriteBatch( BatchInfo & batchInfo );

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
		 * @param shaderObject_ - Shader Object ID.
		 * @param sourceCode_ - RAW GLSL source-code.
		 * @param shaderType_ - shader type.
		 * @return - 'TRUE' if OK, false if failed.
		 * @throws - can throw exception.
		*/
		static const bool loadShader( GLuint & shaderObject_, const char *const sourceCode_, const GLenum & shaderType_ );

		/*
		 * Create & link Shader Program with Shaders.
		 * 
		 * @thread_safety - render-thread only.
		 * @param shaderProgram_ - Shader Program Object ID.
		 * @param vertexShader_ - Vertex Shader Object ID.
		 * @param fragmentShader_ - Fragment Shader Object ID.
		 * @return - 'true' if OK.
		 * @throws - can throw exception.
		*/
		static const bool loadProgram( GLuint & shaderProgram_, const GLuint & vertexShader_, const GLuint & fragmentShader_ );

		/*
		 * Add Drawable-Object to the Sprite Batching.
		 * 
		 * @thread_safety - thread-lock used.
		 * @param batchRequest - Batch Request.
		 * @throws - can throw exception.
		*/
		void addDrawable( BatchRequest & batchRequest );

		/*
		 * Remove Drawable-Object form the Sprite Batching.
		 * 
		 * @thread_safety - thread-lock used.
		 * @param pDrawable - Drawable-Object.
		 * @param shaderProgram_ - OpenGL Shader Program ID (Pointer).
		 * @param texture2D_ - OpenGL 2D Texture Object ID/Pointer.
		 * @throws - can throw exception.
		*/
		void removeDrawable( const Drawable *const pDrawable, const GLuint & shaderProgram_, const GLuint & texture2D_ );

		/*
		 * Draw (render).
		 *
		 * @thread_safety - render-thread only.
		 * @param pCamera - 2D-Camera.
		 * @throws - can throw exception.
		*/
		inline void Draw( GLCamera & pCamera );

		// -------------------------------------------------------- \\

	};

}

#endif // !__c0de4un_gl_renderer_hpp__