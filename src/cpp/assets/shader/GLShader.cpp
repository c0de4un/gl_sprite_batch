/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

// HEADER
#ifndef __c0de4un_gl_shader_hpp__
#include "GLShader.hpp"
#endif // !__c0de4un_gl_shader_hpp__

// Include GLRenderer
#ifndef __c0de4un_gl_renderer_hpp__
#include "../../renderer/GLRenderer.hpp"
#endif // !__c0de4un_gl_renderer_hpp__

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
	 * GLShader constructor.
	 *
	 * @param pName - Name.
	 * @param shaderType_ - GL_SHADER_TYPE
	 * @param sourceCode_ - GLSL Source-Code, optional.
	 * @param pFile - path to the GLSL-file, optional.
	*/
	GLShader::GLShader( const std::string & pName, const GLenum & shaderType_, const std::string *const sourceCode_, const std::string *const pFile )
		: mType( shaderType_ ),
		mShaderObject( 0 ),
		mCode( sourceCode_ != nullptr ? new std::string( *sourceCode_ ) : nullptr ),
		mFile( pFile != nullptr ? new std::string( *pFile ) : nullptr ),
		mName( pName )
	{

		// Log
		std::string logMsg( "GLShader#" );
		logMsg += mName;
		logMsg += "::constructor";
		Log::printDebug( logMsg.c_str( ) );

	}

	/* GLShader destructor */
	GLShader::~GLShader( )
	{

		// Log
		std::string logMsg( "GLShader#" );
		logMsg += mName;
		logMsg += "::destructor";
		Log::printDebug( logMsg.c_str( ) );

		// Delete RAW GLSL Source-Code
		if ( mCode )
			delete mCode;

		// Delete GLSL-file path
		if ( mFile )
			delete mFile;

	}

	// ===========================================================
	// Getter & Setter
	// ===========================================================

		/* Returns Shader Object ID */
	const GLuint & GLShader::getShaderObject( ) const noexcept
	{ return( mShaderObject ); }

	/* Returns Name */
	const std::string & GLShader::getName( ) const noexcept
	{ return( mName ); }

	// ===========================================================
	// Methods
	// ===========================================================

	/*
	 * Load & compile this Shader.
	 *
	 * @inline - no specific reason.
	 * @thread_safety - render-thread-only.
	 * @return 'true' if OK.
	 * @throws - can throw exception.
	*/
	const bool GLShader::Load( )
	{

		// Cancel if loaded
		if ( mShaderObject > 0 )
			return( true );

		// Log
		std::string logMsg( "GLShader#" );
		logMsg += mName;
		logMsg += "::Load";
		Log::printDebug( logMsg.c_str( ) );

		// Load & Compile
		if ( mCode != nullptr )
			GLRenderer::loadShader( mShaderObject, mCode->c_str( ), mType );

		// Return TRUE
		return( true );

	}

	/*
	 * Unload this Shader.
	 *
	 * @inline - no specific reason.
	 * @thread_safety - render-thread-only.
	*/
	void GLShader::Unload( )
	{

		// Cancel
		if ( mShaderObject > 0 )
			return;

		// Log
		std::string logMsg( "GLShader#" );
		logMsg += mName;
		logMsg += "::Unload";
		Log::printDebug( logMsg.c_str( ) );

		// Delete Shader Object
		glDeleteShader( mShaderObject );

		// Reset Shader Object ID
		mShaderObject = 0;

	}

	// -------------------------------------------------------- \\

}