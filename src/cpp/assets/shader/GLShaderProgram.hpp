/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_gl_shader_program_hpp__
#define __c0de4un_gl_shader_program_hpp__

// Include string
#ifndef __c0de4un_string_hpp__
#include "../../cfg/string.hpp"
#endif // !__c0de4un_string_hpp__

// Include opengl
#ifndef __c0de4un_opengl_hpp__
#include "../../cfg/opengl.hpp"
#endif // !__c0de4un_opengl_hpp__

// Forward-declare GLShader
#ifndef __c0de4un_gl_shader_decl__
#define __c0de4un_gl_shader_decl__
namespace c0de4un { class GLShader; }
#endif // !__c0de4un_gl_shader_decl__

// GLShaderProgram declared
#define __c0de4un_gl_shader_program_decl__

namespace c0de4un
{

	/*
	 * GLShaderProgram - shader program asset (game resource) class for OpenGL API 3+.
	*/
	class GLShaderProgram final
	{

	public:

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
		explicit GLShaderProgram( const std::string & pName, GLShader & vertexShader_, GLShader & fragmentShader_ );

		/* GLShaderProgram destructor */
		~GLShaderProgram( );

		// ===========================================================
		// Getter & Setter
		// ===========================================================

		/* Returns OpenGL Shader Program Object */
		const GLuint & getProgramObject( ) const noexcept;

		/* Returns Name */
		const std::string & getName( ) const noexcept;

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
		const bool Load( );

		/*
		 * Unload Shaders & Program (remove from OpenGL).
		*/
		void Unload( );

		// -------------------------------------------------------- \\

	private:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Constants
		// ===========================================================

		/* Name */
		const std::string mName;

		// ===========================================================
		// Fields
		// ===========================================================

		/* Vertex Shader */
		GLShader & mVertexShader;

		/* Fragment Shader */
		GLShader & mFragmentShader;

		/* OpenGL Shader Program Object ID */
		GLuint mProgramObject;

		// ===========================================================
		// Deleted
		// ===========================================================

		/* @deleted GLShaderProgram const copy constructor */
		GLShaderProgram( const GLShaderProgram & ) = delete;

		/* @deleted GLShaderProgram const copy assignment operator */
		GLShaderProgram operator=( const GLShaderProgram & ) = delete;

		/* @deleted GLShaderProgram move constructor */
		GLShaderProgram( GLShaderProgram && ) = delete;

		/* @deleted GLShaderProgram move assignment operator */
		GLShaderProgram & operator=( GLShaderProgram && ) = delete;

		// -------------------------------------------------------- \\

	};

}

#endif // !__c0de4un_gl_shader_program_hpp__