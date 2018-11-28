/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

// HEADER
#ifndef __c0de4un_gl_camera_2D_hpp__
#include "GLCamera2D.hpp"
#endif // !__c0de4un_gl_camera_2D_hpp__

namespace c0de4un
{

	// -------------------------------------------------------- \\

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
	GLCamera2D::GLCamera2D( const float & pX, const float & pY, const float & pWidth, const float & pHeight, const float & zNear_, const float & zFar_ )
		: mutex_( ),
		lock_( mutex_, std::defer_lock ),
		position_( 0.0f, 0.0f, 0.0f ),
		frustum_{ pX, pWidth, pY, pHeight, zNear_, zFar_ },
		viewMat_( 1.0f ),
		projectionMat_( 1.0f ),
		updated_( false )
	{
	}

	/* GLCamera2D destructor */
	GLCamera2D::~GLCamera2D( )
	{
	}

	// -------------------------------------------------------- \\

}