/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_gl_camera_hpp__
#define __c0de4un_gl_camera_hpp__

// Include mutex
#ifndef __c0de4un_mutex_hpp__
#include "../cfg/mutex.hpp" // unique_lock, mutex
#endif // !__c0de4un_mutex_hpp__

// Include glm
#ifndef __c0de4un_glm_hpp__
#include "../cfg/glm.hpp"
#endif // !__c0de4un_glm_hpp__

// Include ViewProjection
#ifndef __c0de4un_view_projection_hpp__
#include "ViewProjection.hpp"
#endif // !__c0de4un_view_projection_hpp__

// GLCamera declared
#define __c0de4un_gl_camera_decl__

namespace c0de4un
{

	/*
	 * GLCamera - 2D camera (orthographic projection) for OpenGL.
	 *
	 * @usage
	 * - before changing state (position, rotation), lock the thread-lock then set #updated_ flag to 'false' ;
	 * - render-system automatically recalculates view & projection if #updated_ flag is 'false' then resets it to 'true' ;
	 *
	 * @version 1.0.0
	*/
	class GLCamera final
	{

	public:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Constructor & destructor
		// ===========================================================

		/*
		 * GLCamera constructor
		 *
		 * @param pX - Viewport X (Left).
		 * @param pY - Viewport Y (Bottom).
		 * @param pWidth - Viewport & Frustum Width (Right).
		 * @param pHeight - Viewport & Frustum Height (Top).
		 * @param zNear - Frustum Near-Plane.
		 * @param zFar - Frustum Far-Plane.
		*/
		GLCamera( const float & pX, const float & pY, const float & pWidth, const float & pHeight, const float & zNear_, const float & zFar_ );

		/* GLCamera destructor */
		~GLCamera( );

		// ===========================================================
		// Fields
		// ===========================================================

		/* Thread-Lock */
		std::unique_lock<std::mutex> lock_;

		/* View & Projection Matrices */
		ViewProjection viewProjection_;

		/* Position */
		glm::vec3 position_;

		/*
		 * Target (look at)
		*/
		glm::vec3 target_;

		/* Up-direction */
		glm::vec3 up_;

		/* Frustum X */
		float frustumX;

		/* Frustum Y */
		float frustumY;

		/* Frustum Width */
		float frustumWidth;

		/* Frustum Height */
		float frustumHeight;

		/* Z-Near */
		float zNear;

		/* Z-Far */
		float zFar;

		// -------------------------------------------------------- \\

	private:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Fields
		// ===========================================================

		/* Mutex */
		std::mutex mutex_;

		// ===========================================================
		// Deleted
		// ===========================================================

		/* @deleted GLCamera const copy constructor */
		GLCamera( const GLCamera & ) = delete;

		/* @deleted GLCamera const cop assignment operator */
		GLCamera & operator=( const GLCamera & ) = delete;

		/* @deleted GLCamera move constructor */
		GLCamera( GLCamera && ) = delete;

		/* @deleted GLCamera move assignment operator */
		GLCamera & operator=( GLCamera && ) = delete;

		// -------------------------------------------------------- \\

	};

}

#endif // !__c0de4un_gl_camera_hpp__