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
	 * @param vertexPosAttrName_ - Vertex Position attribute Name.
	 * @param vertexTexCoordsAttrName_ - Vertex Texture Coordinates attribute Name.
	 * @param vertexColorAttrName_ - Vertex Color attribute Name.
	 * @param texSamplerName_ - Texture Sampler Name.
	 * @param mvpUniformName_ - Model View Projection Matrix Uniform name.
	*/
	GLShaderProgram::GLShaderProgram( const std::string & pName, GLShader & vertexShader_, GLShader & fragmentShader_,
		const std::string & vertexPosAttrName_,
		const std::string & vertexTexCoordsAttrName_,
		const std::string & vertexColorAttrName_,
		const std::string & texSamplerName_, 
		const std::string & mvpUniformName_ )
		: mName( pName ),
		mVertexShader( vertexShader_ ),
		mFragmentShader( fragmentShader_ ),
		mProgramObject( 0 ),
		mVertexPosAttrName( vertexPosAttrName_ ),
		mVertexTexCoordsAttrName( vertexTexCoordsAttrName_ ),
		mVertexColorAttrName( vertexColorAttrName_ ),
		mTexSamplerName( texSamplerName_ ),
		mMVPUniformName( mvpUniformName_ ),
		mVertexPosAttrIndex( -1 ),
		mVertexColorAttrIndex( -1 ),
		mVertexTexCoordsAttrIndex( -1 ),
		mTexSamplerLoc( -1 )
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

	/* Returns Vertex Position attribute index for OpenGL */
	const GLint & GLShaderProgram::getVertexPosAttrIndex( ) const noexcept
	{ return( mVertexPosAttrIndex ); }

	/* Returns Vertex Texture Coordinates attribute index for OpenGL */
	const GLint & GLShaderProgram::getVertexTexCoordsAttrIndex( ) const noexcept
	{ return( mVertexTexCoordsAttrIndex ); }

	/* Returns Vertex Color attribute index for OpenGL */
	const GLint & GLShaderProgram::getColorAttrIndex( ) const noexcept
	{ return( mVertexColorAttrIndex ); }

	/* Returns OpenGL (GLSL) Texture Sampler #0 location/index */
	const GLint & GLShaderProgram::getTextureSamplerLocation( ) const noexcept
	{ return( mTexSamplerLoc ); }

	/* Returns Model View Projection (MVP) Matrix attribute index */
	const GLint & GLShaderProgram::getMVPUniform( ) const noexcept
	{ return( mMVPMatUniformLoc ); }

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
		if ( !GLRenderer::loadProgram( mProgramObject, mVertexShader.getShaderObject( ), mFragmentShader.getShaderObject( ) ) )
		{

			// Log
			logMsg = "GLShaderProgram#";
			logMsg += mName;
			logMsg += "::Load - failed to link Shader Program";
			Log::printWarning( logMsg.c_str( ) );

			// Return FALSE
			return( false );

		}

		// Search Vertex Position attribute index
		mVertexPosAttrIndex = glGetAttribLocation( mProgramObject, mVertexPosAttrName.c_str( ) );

		// Check if Attribute Location Found
		if ( mVertexPosAttrIndex < 0 )
		{
			// Log Message
			std::string logMsg( "GLShaderProgram#" );
			logMsg += mName;

			// Append Details
			logMsg += "::Load - Vertex Position Attribute Location not found !";

			// Print Message to Log
			Log::printError( logMsg.c_str( ) );

			// Return FALSE
			return( false );
		}

		// Texture Coordinates Attribute
		if ( !mVertexTexCoordsAttrName.empty( ) )
		{

			// Search Vertex Texture Coordinates attribute index
			mVertexTexCoordsAttrIndex = glGetAttribLocation( mProgramObject, mVertexTexCoordsAttrName.c_str( ) );

			// Check if Attribute Location Found
			if ( mVertexTexCoordsAttrIndex < 0 )
			{
				// Log Message
				std::string logMsg( "GLShaderProgram#" );
				logMsg += mName;

				// Append Details
				logMsg += "::Load - Vertex Texture Coordinates Attribute Location not found !";

				// Print Message to Log
				Log::printError( logMsg.c_str( ) );

				// Return FALSE
				return( false );
			}

		}

		// Color Attribute
		if ( !mVertexColorAttrName.empty( ) )
		{

			// Search Vertex Color attribute index
			mVertexColorAttrIndex = glGetAttribLocation( mProgramObject, mVertexColorAttrName.c_str( ) );

			// Check if Attribute Location Found
			if ( mVertexColorAttrIndex < 0 )
			{
				// Log Message
				std::string logMsg( "GLShaderProgram#" );
				logMsg += mName;

				// Append Details
				logMsg += "::Load - Vertex Color Attribute Location not found !";

				// Print Message to Log
				Log::printError( logMsg.c_str( ) );

				// Return FALSE
				return( false );
			}

		}

		// Texture Sampler #0
		if ( mVertexTexCoordsAttrIndex > 0 )
		{

			// Search Texture Sampler #0 location/index
			mTexSamplerLoc = glGetUniformLocation( mProgramObject, mTexSamplerName.c_str( ) );

			// Check if Attribute Location Found
			if ( mTexSamplerLoc < 0 )
			{
				// Log Message
				std::string logMsg( "GLShaderProgram#" );
				logMsg += mName;

				// Append Details
				logMsg += "::Load - Texture Sampler #0 Location not found !";

				// Print Message to Log
				Log::printError( logMsg.c_str( ) );

				// Return FALSE
				return( false );
			}

		}

		// MVP Matrix
		if ( !mMVPUniformName.empty( ) )
		{

			// Search MVP (Model View Projection) Matrix Uniform location/index
			mMVPMatUniformLoc = glGetUniformLocation( mProgramObject, mMVPUniformName.c_str( ) );

			// Check if Location Found
			if ( mMVPMatUniformLoc < 0 )
			{
				// Log Message
				std::string logMsg( "GLShaderProgram#" );
				logMsg += mName;

				// Append Details
				logMsg += "::Load - Model-View-Projection Matrix uniform Location not found !";

				// Print Message to Log
				Log::printError( logMsg.c_str( ) );

				// Return FALSE
				return( false );
			}

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

		// Reset Vertex Position attribute Index
		mVertexPosAttrIndex = -1;

		// Reset Vertex Texture Coordinates attribute Index
		mVertexTexCoordsAttrIndex = -1;

		// Reset Vertex Color attribute Index
		mVertexColorAttrIndex = -1;

		// Reset Texture Uniform #0 Index
		mTexSamplerLoc = -1;

		// Reset Shader Program Object ID
		mProgramObject = 0;

		// Unload Vertex Shader
		mVertexShader.Unload( );

		// Unload Fragment Shader
		mFragmentShader.Unload( );

	}

	// -------------------------------------------------------- \\

}