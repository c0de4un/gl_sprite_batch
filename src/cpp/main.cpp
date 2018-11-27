/*
 * Copyright � 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

// Include STL
#include <iostream> // cout, cin, cin.get
#include <cstdlib> // std

// Include Log
#ifndef __c0de4un_log_hpp__
#include "utils/log/Log.hpp"
#endif // !__c0de4un_log_hpp__

// Include GLRenderer
#ifndef __c0de4un_gl_renderer_hpp__
#include "renderer/GLRenderer.hpp"
#endif // !__c0de4un_gl_renderer_hpp__

// Include GLShader
#ifndef __c0de4un_gl_shader_hpp__
#include "assets/shader/GLShader.hpp"
#endif // !__c0de4un_gl_shader_hpp__

// Include GLShaderProgram
#ifndef __c0de4un_gl_shader_program_hpp__
#include "assets/shader/GLShaderProgram.hpp"
#endif // !__c0de4un_gl_shader_program_hpp__

// Include GLCamera
#ifndef __c0de4un_gl_camera_hpp__
#include "camera/GLCamera.hpp"
#endif // !__c0de4un_gl_camera_hpp__

/* Window & Viewport & Back Buffer Size */
static const GLuint WINDOW_WIDTH = 1280, WINDOW_HEIGHT = 720;

/* GLFW Window */
static GLFWwindow *mGLFWWindow = nullptr;

/*
 * 2D Camera
*/
c0de4un::GLCamera * glCamera2D;

/* Vertex Shader */
c0de4un::GLShader * vertexShader;

/* Fragment Shader */
c0de4un::GLShader * fragmentShader;

/* Shader Program */
c0de4un::GLShaderProgram * shaderProgram;

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

/* GLFW Errors Callback */
static void glfwErrorCallback( int errorCode, const char* errorDescription ) noexcept
{// TODO glfwErrorCallback

	// Guarded-Block
	try
	{

		// 

	}
	catch ( const std::exception & exception_ )
	{

		// Log-message
		std::string logMsg( "main::glfwErrorCallback - ERROR: " );
		logMsg += exception_.what( );

		// Print to the Log
		c0de4un::Log::printError( logMsg.c_str( ) );

	}
	catch ( ... )
	{

		// Print to the Log
		c0de4un::Log::printError( "main::glfwErrorCallback - unknown error !" );

	}

}

/* GLFW Key-Input Callback */
static void glfwKeyInputCallback( GLFWwindow* const pWindow, const int pKey, const int scanCode, const int pAction, const int pMode ) noexcept
{// TODO glfwKeyInputCallback

	// Guarded-Block
	try
	{

		// 

	}
	catch ( const std::exception & exception_ )
	{

		// Log-message
		std::string logMsg( "main::glfwKeyInputCallback - ERROR: " );
		logMsg += exception_.what( );

		// Print to the Log
		c0de4un::Log::printError( logMsg.c_str( ) );

	}
	catch ( ... )
	{

		// Print to the Log
		c0de4un::Log::printError( "main::glfwKeyInputCallback - unknown error !" );

	}

}

/*
 * Main-Loop.
*/
void mainLoop( )
{// TODO main::mainLoop

	// Print to the Log
	c0de4un::Log::printInfo( "main::mainLoop" );

	// Guarded-Block
	try
	{

		// Main-Loop
		while ( !glfwWindowShouldClose( mGLFWWindow ) )
		{

			// Poll Events (Input Key, Mouse etc)
			glfwPollEvents( );

			// Clear Surface
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

			// Swap Buffers
			glfwSwapBuffers( mGLFWWindow );

		}

	}
	catch ( const std::exception & exception_ )
	{

		// Log-message
		std::string logMsg( "main::mainLoop - ERROR: " );
		logMsg += exception_.what( );

		// Print to the Log
		c0de4un::Log::printError( logMsg.c_str( ) );

	}
	catch ( ... )
	{

		// Print to the Log
		c0de4un::Log::printError( "main::mainLoop - unknown error !" );

	}

}

/*
 * Unload resources (textures, vertices, buffers, etc).
*/
void Unload( ) noexcept
{// TODO main::Unload

	// Print to the Log
	c0de4un::Log::printInfo( "main::Unload" );

	// Guarded-Block
	try
	{

		// Unload Shader Program & Shaders
		if ( shaderProgram )
			shaderProgram->Unload( );

	}
	catch ( const std::exception & exception_ )
	{

		// Log-message
		std::string logMsg( "main::Unload - ERROR: " );
		logMsg += exception_.what( );

		// Print to the Log
		c0de4un::Log::printError( logMsg.c_str( ) );

	}
	catch ( ... )
	{

		// Print to the Log
		c0de4un::Log::printError( "main::Unload - unknown error !" );

	}

}

/*
 * Stop all operations, terminate objects, release memory, etc.
 *
 * @thread_safety - not thread-safe, can be called from any thread.
*/
static void Stop( ) noexcept
{// TODO main::Stop

	// Print to the Log
	c0de4un::Log::printInfo( "main::Stop" );

	// Guarded-Block
	try
	{

		// Release 2D-Camera
		if ( glCamera2D )
		{

			// Delete 2D Camera
			delete glCamera2D;

			// Reset pointer-value
			glCamera2D = nullptr;

		}

		// Release Shader Program
		if ( shaderProgram )
		{

			// Delete Shader Program
			delete shaderProgram;

			// Reset pointer-value
			shaderProgram = nullptr;

		}

		// Release Vertex Shader
		if ( vertexShader )
		{

			// Delete Vertex Shader instance
			delete vertexShader;

			// Reset pointer-value
			vertexShader = nullptr;

		}

		// Release Fragment Shader
		if ( fragmentShader )
		{

			// Delete Fragment Shader instance
			delete fragmentShader;

			// Reset pointer-value
			fragmentShader = nullptr;

		}

	}
	catch ( const std::exception & exception_ )
	{

		// Log-message
		std::string logMsg( "main::Stop - ERROR: " );
		logMsg += exception_.what( );

		// Print to the Log
		c0de4un::Log::printError( logMsg.c_str( ) );

	}
	catch ( ... )
	{

		// Print to the Log
		c0de4un::Log::printError( "main::Stop - unknown error !" );

	}

}

/*
 * Loads assets & objects, prepares data.
 *
 * @thread_safety - main (system, ui) thread-only.
 * @return - 'true' if OK.
*/
static const bool Load( ) noexcept
{// TODO main::Load

	// Print to the Log
	c0de4un::Log::printInfo( "main::Load" );

	// Guarded-Block
	try
	{

		// Create 2D-Camera
		if ( !glCamera2D )
			glCamera2D = new c0de4un::GLCamera( 0, 0, 1280, 720, -1, 1 );

		// Create Vertex Shader
		if ( vertexShader == nullptr )
		{

			/*
			 * Vertex Shader Source-Code
			 * No texture, no color, no position & matrices.
			 * 
			 * @attribute 
			*/
			const std::string glslCode_(
			"#version 300 \n"
			"attribute vec4 a_Position; \n"
			"void main() \n"
			"{ \n"
			"gl_Position = a_Position; \n"
			"} \n" );

			// Create Vertex Shader
			vertexShader = new c0de4un::GLShader( "vertexShader", GL_VERTEX_SHADER, &glslCode_, nullptr );

		}

		// Load Vertex Shader
		if ( !vertexShader->Load( ) )
		{

			// Print to the Log
			std::string logMsg( "main::Load - failed to load Vertex Shader#" );
			logMsg += vertexShader->getName( );
			c0de4un::Log::printWarning( logMsg.c_str( ) );

			// Cancel
			return( false );

		}

		// Create Fragment Shader
		if ( fragmentShader == nullptr )
		{

			/*
			 * Fragment Shader Source-Code
			 * No texture, no color, no position & matrices.
			 *
			*/
			const std::string glslCode_(
				"#version 300 \n"
				"precision mediump float; \n"
				"out vec4 fragColor; \n"
				"void main() \n"
				"{ \n"
				"fragColor = vec4( 1.0f, 1.0f, 1.0f, 1.0f ); \n"
				"} \n" );

			// Create Fragment Shader
			fragmentShader = new c0de4un::GLShader( "fragmentShader", GL_FRAGMENT_SHADER, &glslCode_, nullptr );

		}

		// Load Fragment Shader
		if ( !fragmentShader->Load( ) )
		{

			// Print to the Log
			std::string logMsg( "main::Load - failed to load Fragment Shader#" );
			logMsg += fragmentShader->getName( );
			c0de4un::Log::printWarning( logMsg.c_str( ) );

			// Cancel
			return( false );

		}

		// Create Shader Program
		if ( shaderProgram == nullptr )
			shaderProgram = new c0de4un::GLShaderProgram( "shaderProgram", *vertexShader, *fragmentShader );

		// Load Shader Program
		if ( !shaderProgram->Load( ) )
		{

			// Print to the Log
			std::string logMsg( "main::Load - failed to load Shader Program#" );
			logMsg += shaderProgram->getName( );
			c0de4un::Log::printWarning( logMsg.c_str( ) );

			// Cancel
			return( false );

		}

	}
	catch ( const std::exception & exception_ )
	{

		// Log-message
		std::string logMsg( "main::Load - ERROR: " );
		logMsg += exception_.what( );

		// Print to the Log
		c0de4un::Log::printError( logMsg.c_str( ) );

		// Return FALSE
		return( false );

	}
	catch ( ... )
	{

		// Print to the Log
		c0de4un::Log::printError( "main::Load - unknown error !" );

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
{// TODO main::Initialize

	// Print to the Log
	c0de4un::Log::printInfo( "main::Initialize" );

	// Guarded-Block
	try
	{

		// Set GLFW Errors Callback
		glfwSetErrorCallback( glfwErrorCallback );

		// Init GLFW
		if ( glfwInit( ) == GLFW_FALSE )
		{
			// Print Error to Console
			std::cout << "main::Initialize - failed to initialize GLFW !" << std::endl;

			// Return FALSE
			return( false );
		}

		// Set Major OpenGL Version
		glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );

		// Set Minor OpenGL Version
		glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );

		// Crete GLFW Window
		mGLFWWindow = glfwCreateWindow( WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Sprite Batching", nullptr, nullptr );

		// Check if GLFW Window is Valid
		if ( mGLFWWindow == nullptr )
		{
			// Print Error to Console
			std::cout << "main::Initialize - failed to create GLFW Window !" << std::endl;

			// Return FALSE
			return( false );
		}

		// Make OpenGL Context Current for GLFW Window
		glfwMakeContextCurrent( mGLFWWindow );

		// Set Key Input Callback
		glfwSetKeyCallback( mGLFWWindow, glfwKeyInputCallback );

		// Ask GLEW to use Modern OpenGL API pointers and extensions
		glewExperimental = true;

		// Initialize GLEW (OpenGL API extensions wrapper) to make OpenGL API pointers actual
		if ( glewInit( ) != GLEW_OK )
		{
			//Print Console
			std::cout << "main::Initialize - Failed to initialize GLEW !" << std::endl;

			//Return FALSE
			return( false );
		}

		//Get OpenGL Surface Width
		int surfaceWidth, surfaceHeight;

		//Get OpenGL Surface Size
		glfwGetFramebufferSize( mGLFWWindow, &surfaceWidth, &surfaceHeight );

		//Set OpenGL Viewport
		glViewport ( 0, 0, surfaceWidth, surfaceHeight );

		//Set OpenGL Surface Clear Color
		glClearColor( 0.0f, 0.6f, 0.8f, 1.0f );

		// Create GLRenderer

	}
	catch ( const std::exception & exception_ )
	{

		// Log-message
		std::string logMsg( "main::Initialize - ERROR: " );
		logMsg += exception_.what( );

		// Print to the Log
		c0de4un::Log::printError( logMsg.c_str( ) );

		// Return FALSE
		return( false );

	}
	catch ( ... )
	{

		// Print to the Log
		c0de4un::Log::printError( "main::Initialize - unknown error !" );

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

	// Initialize
	if ( !Initialize( ) )
	{

		// Print to the console
		std::cout << "main - failed to initialize." << std::endl;

		// Stop
		Stop( );

		// Pause Console-Window
		std::cin.get( );

		// Return
		return( 0 );

	}

	// Load Resources
	if ( !Load( ) )
	{

		// Print to the console
		std::cout << "main - failed to load resources." << std::endl;

		// Stop
		Stop( );

		// Pause Console-Window
		std::cin.get( );

		// Return
		return( 0 );

	}

	// Main-Loop
	mainLoop( );

	// Unload Resources
	Unload( );

	// Stop
	Stop( );

	// Pause Console-Window
	std::cin.get( );

	// Return OK
	return( 0 );

}