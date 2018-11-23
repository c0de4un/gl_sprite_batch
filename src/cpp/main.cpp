/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

// Include STL
#include <iostream> // cout, cin, cin.get
#include <cstdlib> // std

// Include GLRenderer
#ifndef __c0de4un_gl_renderer_hpp__
#include "renderer/GLRenderer.hpp"
#endif // !__c0de4un_gl_renderer_hpp__

/*
 * PNG Image
*/

/*
 * Texture 2D
*/

/*
 * Sprites
*/

/*
 * GLRenderer - used for drawing (rendering) drawable-objects,
 * load & compile shaders, texture to the OpenGL memory-space (GPU).
*/
static c0de4un::GLRenderer * glRenderer( nullptr );

/*
 * Stop all operations, terminate objects, release memory, etc.
 *
 * @thread_safety - not thread-safe, can be called from any thread.
*/
static void Stop( ) noexcept
{

	// Guarded-Block
	try
	{

		// 

	}
	catch ( const std::exception & exception_ )
	{

		// 

	}
	catch ( ... )
	{

		// 

	}

}

/*
 * Loads assets & objects, prepares data.
 *
 * @thread_safety - main (system, ui) thread-only.
 * @return - 'true' if OK.
*/
static const bool Load( ) noexcept
{

	// Guarded-Block
	try
	{

		// 

	}
	catch ( const std::exception & exception_ )
	{

		// Return FALSE
		return( false );

	}
	catch ( ... )
	{

		// Return FALSE
		return( false );

	}

	// Return TRUE
	return( true );

}

/*
 * Initialize GLFW, GLEW, create windows, OpenGL surface, etc.
 *
 * @thread_safety - main (system, ui) thread-only.
 * @return - 'true' if OK.
*/
static const bool Initialize( ) noexcept
{

	// Guarded-Block
	try
	{

		// 

	}
	catch ( const std::exception & exception_ )
	{

		// Return FALSE
		return( false );

	}
	catch ( ... )
	{

		// Return FALSE
		return( false );

	}

	// Return OK
	return( true );

}

/* MAIN */
int main( int argC, char** argV )
{

	// Print "Hello World !"
	std::cout << "Hello World !" << std::endl;

	// Pause Console-Window
	std::cin.get( );

	// Return OK
	return( 0 );

}