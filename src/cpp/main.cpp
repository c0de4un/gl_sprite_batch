/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

// Include STL
#include <iostream> // cout, cin, cin.get
#include <cstdlib> // std

// Include opengl
#ifndef __c0de4un_opengl_hpp__
#include "cfg/opengl.hpp"
#endif // !__c0de4un_opengl_hpp__

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

// Include Sprite
#ifndef __c0de4un_sprite_hpp__
#include "objects/sprite/Sprite.hpp"
#endif // !__c0de4un_sprite_hpp__

// Include GLCamera2D
#ifndef __c0de4un_gl_camera_2D_hpp__
#include "camera/GLCamera2D.hpp"
#endif // !__c0de4un_gl_camera_2D_hpp__

// Include GLTexture2D
#ifndef __c0de4un_gl_texture_2D_hpp__
#include "assets/texture/GLTexture2D.hpp"
#endif // !__c0de4un_gl_texture_2D_hpp__

// Include Random
#ifndef __c0de4un_random_hpp__
#include "utils/random/Random.hpp"
#endif // !__c0de4un_random_hpp__

// Include SpriteSystem
#ifndef __c0de4un_sprite_system_hpp__
#include "systems/SpriteSystem.hpp"
#endif // !__c0de4un_sprite_system_hpp__

/* Window & Viewport & Back Buffer Size */
static const GLuint WINDOW_WIDTH = 1280, WINDOW_HEIGHT = 720;

/* GLFW Window */
static GLFWwindow *mGLFWWindow = nullptr;

/* Random numbers generator (wrapper) */
c0de4un::Random * randomizer;

/*
 * 2D Camera
*/
c0de4un::GLCamera2D * glCamera2D;

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
c0de4un::GLTexture2D * texture2D;

/*
 * SpriteSystem - handles (manages) sprites.
*/
c0de4un::SpriteSystem * spritesSystem;

/*
 * Sprites
*/
//c0de4un::Sprite * sprite_;

/*
 * GLRenderer - used for drawing (rendering) drawable-objects,
 * load & compile shaders, texture to the OpenGL memory-space (GPU).
*/
static c0de4un::GLRenderer * glRenderer( nullptr );

/* GLFW Errors Callback */
void glfwErrorCallback( int errorCode, const char* errorDescription ) noexcept
{

	// ERROR--message
	std::string errMsg_( errorDescription );

	// Cancel
	if ( errMsg_.length( ) < 3 )
		return;

	// Log
	errMsg_ = "main::glfwErrorCallback - ERROR: ";
	errMsg_ += errorDescription;
	c0de4un::Log::printError( errMsg_.c_str( ) );

	// Guarded-Block
	try
	{

		// Stop
		glfwSetWindowShouldClose( mGLFWWindow, true );

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


/* GLFW Mouse Position CallBack */
void glfwMousePositionCallback( GLFWwindow *const window, const double & pX, const double & pY )
{// TODO main::glfwMousePositionCallback

	// 

}

/*
 * GLFW Mouse Buttons CallBack.
 *
 * @param pWindow - GLFW Window.
 * @param pButton - Button-Key.
 * @param pAction - Action ( GLFW_PRESS || GLFW_RELEASE ).
 * @param pModes - Input Mode ( GLFW_STICKY_MOUSE_BUTTONS , GLFW_MOUSE_BUTTON_LAST ).
*/
void glfwMouseButtonCallback( GLFWwindow * pWindow, int pButton, int pAction, int pMods )
{

	// Cancel
	if ( mGLFWWindow == nullptr || spritesSystem == nullptr )
		return;

	// Log
	std::string logMsg( "main::glfwMouseButtonCallback - KEY=" );
	logMsg += std::to_string( pButton );
	logMsg += ", action=";
	logMsg += std::to_string( pAction );
	c0de4un::Log::printDebug( logMsg.c_str( ) );

	// Guarded-Block
	try
	{

		// Left
		if ( pButton == GLFW_MOUSE_BUTTON_LEFT && pAction == GLFW_RELEASE )
			spritesSystem->addSprite( *shaderProgram, texture2D, glRenderer );

	}
	catch ( const std::exception & exception_ )
	{

		// Log-message
		logMsg = "main::glfwKeyInputCallback - ERROR: ";
		logMsg += exception_.what( );

		// Print to the Log
		c0de4un::Log::printError( logMsg.c_str( ) );

		// Close GLFW Window
		glfwSetWindowShouldClose( mGLFWWindow, true );

	}
	catch ( ... )
	{

		// Print to the Log
		c0de4un::Log::printError( "main::glfwKeyInputCallback - unknown error !" );

		// Close GLFW Window
		glfwSetWindowShouldClose( mGLFWWindow, true );

	}

}

/* GLFW Key-Input Callback */
void glfwKeyInputCallback( GLFWwindow* const pWindow, const int pKey, const int scanCode, const int pAction, const int pMode ) noexcept
{

	// Log
	std::string logMsg( "main::glfwKeyInputCallback - KEY=" );
	logMsg += std::to_string( pKey );
	logMsg += ", scan_code=";
	logMsg += std::to_string( scanCode );
	logMsg += ", action=";
	logMsg += std::to_string( pAction );
	logMsg += ", mode=";
	logMsg += pMode;
	c0de4un::Log::printDebug( logMsg.c_str( ) );

	// Guarded-Block
	try
	{

		// ESC
		if ( pKey == GLFW_KEY_ESCAPE && pAction == 1 )
			glfwSetWindowShouldClose( mGLFWWindow, true );

	}
	catch ( const std::exception & exception_ )
	{

		// Log-message
		logMsg = "main::glfwKeyInputCallback - ERROR: ";
		logMsg += exception_.what( );

		// Print to the Log
		c0de4un::Log::printError( logMsg.c_str( ) );

		// Close GLFW Window
		glfwSetWindowShouldClose( mGLFWWindow, true );

	}
	catch ( ... )
	{

		// Print to the Log
		c0de4un::Log::printError( "main::glfwKeyInputCallback - unknown error !" );

		// Close GLFW Window
		glfwSetWindowShouldClose( mGLFWWindow, true );

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

		// Stop SpriteSystem
		if ( spritesSystem != nullptr )
			spritesSystem->Stop( glRenderer );

		// Unload 2D-Texture
		if ( texture2D != nullptr )
			texture2D->Unload( );

		// Unload Sprite
		//if ( sprite_ )
			//sprite_->Hide( glRenderer );

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
void Stop( ) noexcept
{

	// Print to the Log
	c0de4un::Log::printInfo( "main::Stop" );

	// Guarded-Block
	try
	{

		// Close GLFW
		glfwSetWindowShouldClose( mGLFWWindow, true );

		// Release Randomizer
		if ( randomizer != nullptr )
		{

			// Delete Random instance
			delete randomizer;

			// Reset pointer-value
			randomizer = nullptr;

		}

		// Release SpriteSystem
		if ( spritesSystem != nullptr )
		{

			// Delete SpriteSystem
			delete spritesSystem;

			// Reset pointer-value
			spritesSystem = nullptr;

		}

		// Release 2D-Camera
		if ( glCamera2D )
		{

			// Delete 2D Camera
			delete glCamera2D;

			// Reset pointer-value
			glCamera2D = nullptr;

		}

		// Release 2D-Texture
		if ( texture2D != nullptr )
		{

			// Delete 2D-Texture instance
			delete texture2D;

			// Reset pointer-value
			texture2D = nullptr;

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

		// Release GLRenderer
		if ( glRenderer )
		{

			// Delete GLRenderer
			delete glRenderer;

			// Reset pointer-value
			glRenderer = nullptr;

		}

		// Terminate GLFW
		glfwTerminate( );

		// Reset GLFWWindow pointer-value
		mGLFWWindow = nullptr;

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
 * Main-Loop
*/
void mainLoop( )
{

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

			// Update SpriteSystem
			if ( spritesSystem != nullptr )
				spritesSystem->Update( 0.016 );

			// Draw Sprite-Batch
			if ( glRenderer )
				glRenderer->Draw( glCamera2D );

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
 * Loads assets & objects, prepares data.
 *
 * @thread_safety - main (system, ui) thread-only.
 * @return - 'true' if OK.
*/
const bool Load( ) noexcept
{// TODO main::Load

	// Print to the Log
	c0de4un::Log::printInfo( "main::Load" );

	// Guarded-Block
	try
	{

		// Create 2D-Camera
		if ( !glCamera2D )
			glCamera2D = new c0de4un::GLCamera2D( 0, 0, 1280, 720, 0, 1 );

		// Create Randomizer
		if ( randomizer == nullptr )
			randomizer = new c0de4un::Random( );

		// Create Vertex Shader
		if ( vertexShader == nullptr )
		{

			///*
			// * Vertex Shader Source-Code
			// * No texture, no position & matrices.
			// * 
			// * @attribute 
			//*/
			//const std::string glslCode_(
			//"#version 330 \n"
			//"attribute vec4 a_Position; \n"
			//"attribute vec4 a_Color; \n"
			//"varying vec4 v_Color; \n"
			//"void main() \n"
			//"{ \n"
			//"gl_Position = a_Position; \n"
			//"v_Color = a_Color; \n"
			//"} \n" );

			/*
			 * Vertex Shader Source-Code
			 * No texture
			 *
			 * @attribute a_Position - vertex position.
			 * @attribute a_Color - primitive color.
			 * @attribute a_MVP - Model View Projection Matrix.
			*/
			const std::string glslCode_(
				"#version 330 \n"
				"in vec4 a_Position; \n"
				"in vec2 a_TexCoord; \n"
				"uniform mat4 u_MVP; \n"
				"out vec2 v_TexCoord; \n"
				"void main() \n"
				"{ \n"
				"gl_Position = ( u_MVP * a_Position ); \n"
				"v_TexCoord = a_TexCoord; \n"
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

			///*
			// * Fragment Shader Source-Code
			// * No texture, no color, no position & matrices.
			// *
			//*/
			//const std::string glslCode_(
			//	"#version 330 \n"
			//	"precision mediump float; \n"
			//	"varying vec4 v_Color; \n"
			//	"out vec4 fragColor; \n"
			//	"void main() \n"
			//	"{ \n"
			//	"fragColor = v_Color; \n"
			//	"} \n" );

			/*
			 * Fragment Shader Source-Code
			 * No texture
			 *
			*/
			const std::string glslCode_(
				"#version 330 \n"
				"precision mediump float; \n"
				"in vec2 v_TexCoord; \n"
				"out vec4 fragColor; \n"
				"uniform sampler2D s_texture; \n"
				"void main() \n"
				"{ \n"
				"fragColor = texture(s_texture, v_TexCoord); \n"
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
			shaderProgram = new c0de4un::GLShaderProgram( "shaderProgram", *vertexShader, *fragmentShader, "a_Position", "a_TexCoord", "", "s_texture", "u_MVP" );

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

		// Create 2D-Texture
		if ( texture2D == nullptr )
			texture2D = new c0de4un::GLTexture2D( "smile", "../../../assets/smiley_PNG188.png" );

		// Load 2D-Texture
		if ( !texture2D->Load( ) )
		{

			// Print to the Log
			std::string logMsg( "main::Load - failed to load 2D Texture#" );
			logMsg += texture2D->mName;
			c0de4un::Log::printWarning( logMsg.c_str( ) );

			// Cancel
			return( false );

		}

		// Create Sprite
		//if ( !sprite_ )
			//sprite_ = new c0de4un::Sprite( "rectangle", *shaderProgram, texture2D );

		//sprite_->mScale.vec3_ = glm::vec3( 64.0f, 64.0f, 0.0f );
		//sprite_->mPosition.vec3_ = glm::vec3( 256.0f, 256.0f, 0.0f );

		// Show Sprite
		//sprite_->Show( glRenderer );

		// Create SpriteSystem
		if ( spritesSystem == nullptr )
			spritesSystem = new c0de4un::SpriteSystem( randomizer, WINDOW_WIDTH, WINDOW_HEIGHT, 10 );

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
const bool Initialize( ) noexcept
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

		// Set Mouse Buttons Input Callback
		glfwSetMouseButtonCallback( mGLFWWindow, glfwMouseButtonCallback );

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
		if ( !glRenderer )
			glRenderer = new c0de4un::GLRenderer( );

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