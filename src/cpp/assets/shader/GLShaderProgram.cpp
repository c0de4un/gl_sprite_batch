/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

// HEADER
#ifndef __c0de4un_gl_shader_program_hpp__
#include "GLShaderProgram.hpp"
#endif // !__c0de4un_gl_shader_program_hpp__

// Include GLRenderer
#ifndef __c0de4un_gl_renderer_hpp__
#include "../../renderer/GLRenderer.hpp"
#endif // !__c0de4un_gl_renderer_hpp__

// Include GLShader
#ifndef __c0de4un_gl_shader_hpp__
#include "GLShader.hpp"
#endif // !__c0de4un_gl_shader_hpp__

// Include Log
#ifndef __c0de4un_log_hpp__
#include "../../utils/log/Log.hpp"
#endif // !__c0de4un_log_hpp__

namespace c0de4un
{

	// -------------------------------------------------------- \\

	// ===========================================================
	// Constructor & destructor
	// ===========================================================

	/*
	 * GLShaderProgram constructor
	 *
	 * @param pName - Name.
	 * @param vertexShader_ - Vertex Shader.
	 * @param framgneShader_ - Fragment Shader.
	*/
	GLShaderProgram::GLShaderProgram( const std::string & pName, GLShader & vertexShader_, GLShader & fragmentShader_ )
		: mName( pName ),
		mVertexShader( vertexShader_ ),
		mFragmentShader( fragmentShader_ ),
		mProgramObject( 0 )
	{

		// Log
		std::string logMsg( "GLShaderProgram#" );
		logMsg += mName;
		logMsg += "::constructor";
		Log::printDebug( logMsg.c_str( ) );

	}

	/* GLShaderProgram destructor */
	GLShaderProgram::~GLShaderProgram( )
	{

		// Log
		std::string logMsg( "GLShaderProgram#" );
		logMsg += mName;
		logMsg += "::destructor";
		Log::printDebug( logMsg.c_str( ) );

	}

	// ===========================================================
	// Getter & Setter
	// ===========================================================

	/* Returns OpenGL Shader Program Object */
	const GLuint & GLShaderProgram::getProgramObject( ) const noexcept
	{ return( mProgramObject ); }

	/* Returns Name */
	const std::string & GLShaderProgram::getName( ) const noexcept
	{ return( mName ); }

	// ===========================================================
	// Methods
	// ===========================================================

	/*
	 * Load Shader Program & attached Shaders (upload shaders source code to OpenGL, compile, link with program).
	 *
	 * @thread_safety - render-thread only.
	 * @return - 'TRUE' if OK.
	 * @throws - can throw exception.
	*/
	const bool GLShaderProgram::Load( )
	{

		// Cancel
		if ( mProgramObject > 0 )
			return( true );

		// Log
		std::string logMsg( "GLShaderProgram#" );
		logMsg += mName;
		logMsg += "::Load";
		Log::printDebug( logMsg.c_str( ) );

		// Load Vertex Shader
		if ( !mVertexShader.Load( ) )
		{

			// Log
			logMsg = "GLShaderProgram#";
			logMsg += mName;
			logMsg += "::Load - failed to load vertex shader#";
			logMsg += mVertexShader.getName( );
			Log::printWarning( logMsg.c_str( ) );

			// Return FALSE
			return( false );

		}

		// Load Fragment Shader
		if ( !mFragmentShader.Load( ) )
		{

			// Log
			logMsg = "GLShaderProgram#";
			logMsg += mName;
			logMsg += "::Load - failed to load fragment shader#";
			logMsg += mFragmentShader.getName( );
			Log::printWarning( logMsg.c_str( ) );

			// Return FALSE
			return( false );

		}

		// Create Program Object, attach Shaders & Link
		if ( GLRenderer::loadProgram( mProgramObject, mVertexShader.getShaderObject( ), mFragmentShader.getShaderObject( ) ) )
		{

			// Log
			logMsg = "GLShaderProgram#";
			logMsg += mName;
			logMsg += "::Load - failed to link Shader Program";
			logMsg += mFragmentShader.getName( );
			Log::printWarning( logMsg.c_str( ) );

			// Return FALSE
			return( false );

		}

		// Return TRUE
		return( true );

	}

	/*
	 * Unload Shaders & Program (remove from OpenGL).
	*/
	void GLShaderProgram::Unload( )
	{

		// Cancel
		if ( mProgramObject < 1 )
			return;

		// Log
		std::string logMsg( "GLShaderProgram#" );
		logMsg += mName;
		logMsg += "::Unload";
		Log::printDebug( logMsg.c_str( ) );

		// Delete Shader Program Object
		glDeleteProgram( mProgramObject );

		// Reset Shader Program Object ID
		mProgramObject = 0;

		// Unload Vertex Shader
		mVertexShader.Unload( );

		// Unload Fragment Shader
		mFragmentShader.Unload( );

	}

	// -------------------------------------------------------- \\

}