/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_gl_shader_hpp__
#define __c0de4un_gl_shader_hpp__

// Include string
#ifndef __c0de4un_string_hpp__
#include "../../cfg/string.hpp"
#endif // !__c0de4un_string_hpp__

// Include opengl
#ifndef __c0de4un_opengl_hpp__
#include "../../cfg/opengl.hpp"
#endif // !__c0de4un_opengl_hpp__

// GLShader declared
#define __c0de4un_gl_shader_decl__

namespace c0de4un
{

	/*
	 * GLShader - shader for OpenGL API.
	 * 
	 * @version 1.0
	*/
	class GLShader final
	{

	public:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Constants
		// ===========================================================

		/* GL_SHADER_TYPE */
		const GLenum mType;

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
		explicit GLShader( const std::string & pName, const GLenum & shaderType_, const std::string *const sourceCode_, const std::string *const pFile );

		/* GLShader destructor */
		~GLShader( );

		// ===========================================================
		// Getter & Setter
		// ===========================================================

		/* Returns Shader Object ID */
		const GLuint & getShaderObject( ) const noexcept;

		/* Returns Name */
		const std::string & getName( ) const noexcept;

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
		const bool Load( );

		/*
		 * Unload this Shader.
		 *
		 * @inline - no specific reason.
		 * @thread_safety - render-thread-only.
		*/
		void Unload( );

		// -------------------------------------------------------- \\

	private:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Fields
		// ===========================================================

		/* OpenGL Shader Object ID */
		GLuint mShaderObject;

		/* RAW GLSL Source-Code */
		const std::string *const mCode;

		/* GLSL-file path */
		const std::string *const mFile;

		/* Name */
		const std::string mName;

		// ===========================================================
		// Deleted
		// ===========================================================

		/* @deleted GLShader const copy constructor */
		GLShader( const GLShader & ) = delete;

		/* @deleted GLShader const copy assignment operator */
		GLShader operator=( const GLShader & ) = delete;

		/* @deleted GLShader move constructor */
		GLShader( GLShader && ) = delete;

		/* @deleted GLShader move assignment operator */
		GLShader & operator=( GLShader && ) = delete;

		// -------------------------------------------------------- \\

	};

}

#endif // !__c0de4un_gl_shader_hpp__