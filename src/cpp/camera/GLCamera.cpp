/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

// HEADER
#ifndef __c0de4un_gl_camera_hpp__
#include "GLCamera.hpp"
#endif // !__c0de4un_gl_camera_hpp__

namespace c0de4un
{

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
	GLCamera::GLCamera( const float & pX, const float & pY, const float & pWidth, const float & pHeight, const float & zNear_, const float & zFar_ )
		: frustumX( pX ), frustumY( pY ), frustumWidth( pWidth ), frustumHeight( pHeight ), zNear( zNear_ ), zFar( zFar_ ),
		lock_( ),
		viewProjection_( ),
		position_( 0.0f, 0.0f, 1.0f ),
		target_( 0.0f, 0.0f, 0.0f ),
		up_( 0.0f, 1.0f, 0.0f )

	{
	}

	/* GLCamera destructor */
	GLCamera::~GLCamera( )
	{
	}

	// -------------------------------------------------------- \\

}