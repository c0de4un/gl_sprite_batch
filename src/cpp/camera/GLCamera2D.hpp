/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_gl_camera_2D_hpp__
#define __c0de4un_gl_camera_2D_hpp__

// Include mutex
#ifndef __c0de4un_mutex_hpp__
#include "../cfg/mutex.hpp" // unique_lock, mutex
#endif // !__c0de4un_mutex_hpp__

// Include glm
#ifndef __c0de4un_glm_hpp__
#include "../cfg/glm.hpp"
#endif // !__c0de4un_glm_hpp__

// GLCamera2D
#define __c0de4un_gl_camera_2D_decl__

// Enable structure-data (fields, variables) alignment (by compilator) to 1 byte
#pragma pack( push, 1 )

namespace c0de4un
{

	/*
	 * GLCamera2D - 2D camera for OpenGL.
	 *
	 * @version 1.0.0
	*/
	class GLCamera2D final
	{

	public:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Fields
		// ===========================================================

		/* Matrix updated flag */
		bool updated_;

		/* Thread-Lock */
		std::unique_lock<std::mutex> lock_;

		/* Position */
		glm::vec3 position_;

		/*
		 * Frustum
		 * 0 - Left (X)
		 * 1 - Right (Width)
		 * 2 - Bottom (Y)
		 * 3 - Top (Height)
		 * 4 - Z-Near (0)
		 * 5 - Z-Far (1)
		*/
		float frustum_[6];

		/* View Matrix */
		glm::mat4 viewMat_;

		/* Projection Matrix */
		glm::mat4 projectionMat_;

		// ===========================================================
		// Constructor & destructor
		// ===========================================================

		/*
		 * GLCamera2D constructor
		 *
		 * @param pX - Viewport X (Left).
		 * @param pY - Viewport Y (Bottom).
		 * @param pWidth - Viewport & Frustum Width (Right).
		 * @param pHeight - Viewport & Frustum Height (Top).
		 * @param zNear - Frustum Near-Plane.
		 * @param zFar - Frustum Far-Plane.
		*/
		explicit GLCamera2D( const float & pX, const float & pY, const float & pWidth, const float & pHeight, const float & zNear_, const float & zFar_ );

		/* GLCamera2D destructor */
		~GLCamera2D( );

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

		/* @deleted GLCamera2D const copy constructor */
		GLCamera2D( const GLCamera2D & ) = delete;

		/* @deleted GLCamera2D const cop assignment operator */
		GLCamera2D & operator=( const GLCamera2D & ) = delete;

		/* @deleted GLCamera2D move constructor */
		GLCamera2D( GLCamera2D && ) = delete;

		/* @deleted GLCamera2D move assignment operator */
		GLCamera2D & operator=( GLCamera2D && ) = delete;

		// -------------------------------------------------------- \\

	};

}

// Restore structure-data alignment to default (8-byte on MSVC)
#pragma pack( pop )

#endif // !__c0de4un_gl_camera_2D_hpp__