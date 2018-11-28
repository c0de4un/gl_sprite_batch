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
		 * @param vertexPosAttrName_ - Vertex Position attribute Name.
		 * @param vertexTexCoordsAttrName_ - Vertex Texture Coordinates attribute Name.
		 * @param vertexColorAttrName_ - Vertex Color attribute Name.
		 * @param texUniformName_ - Texture Uniform Name.
		 * @param mvpUniformName_ - Model View Projection Matrix Uniform name.
		*/
		explicit GLShaderProgram( const std::string & pName, GLShader & vertexShader_, GLShader & fragmentShader_, 
			const std::string & vertexPosAttrName_, 
			const std::string & vertexTexCoordsAttrName_, 
			const std::string & vertexColorAttrName_, 
			const std::string & texUniformName_, 
			const std::string & mvpUniformName_ );

		/* GLShaderProgram destructor */
		~GLShaderProgram( );

		// ===========================================================
		// Getter & Setter
		// ===========================================================

		/* Returns OpenGL Shader Program Object */
		const GLuint & getProgramObject( ) const noexcept;

		/* Returns Name */
		const std::string & getName( ) const noexcept;

		/* Returns Vertex Position attribute index for OpenGL */
		const GLint & getVertexPosAttrIndex( ) const noexcept;

		/* Returns Vertex Texture Coordinates attribute index for OpenGL */
		const GLint & getVertexTexCoordsAttrIndex( ) const noexcept;

		/* Returns Vertex Color attribute index for OpenGL */
		const GLint & getColorAttrIndex( ) const noexcept;

		/* Returns Texture Uniform (public, global) index for OpenGL */
		const GLint & getTexUniformIndex( ) const noexcept;

		/* Returns Model View Projection (MVP) Matrix Uniform location/index */
		const GLint & getMVPUniform( ) const noexcept;

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

		/* Vertex Position attribute Name */
		const std::string mVertexPosAttrName;

		/* Vertex Texture Coordinates attribute Name */
		const std::string mVertexTexCoordsAttrName;

		/* Vertex Color attribute Name */
		const std::string mVertexColorAttrName;

		/* Vertex Texture Uniform Name */
		const std::string mTexUniformName;

		/* Model View Projection Matrix Uniform Name */
		const std::string mMVPUniformName;

		// ===========================================================
		// Fields
		// ===========================================================

		/* Vertex Shader */
		GLShader & mVertexShader;

		/* Fragment Shader */
		GLShader & mFragmentShader;

		/* OpenGL Shader Program Object ID */
		GLuint mProgramObject;

		/* Vertex Position Attribute Index for OpenGL */
		GLint mVertexPosAttrIndex;

		/* Vertex Color Attribute Index for OpenGL */
		GLint mVertexColorAttrIndex;

		/* Vertex Texture Coordinates Attribute Index */
		GLint mVertexTexCoordsAttrIndex;

		/* Texture Uniform Index for OpenGL */
		GLint mTexUniformIndex;

		/* MVP (Model View Projection) Matrix attribute Index for OpenGL */
		GLint mMVPMatUniformLoc;

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