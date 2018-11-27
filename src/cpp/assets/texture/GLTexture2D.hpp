/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_gl_texture_2D_hpp__
#define __c0de4un_gl_texture_2D_hpp__

// Include string
#ifndef __c0de4un_string_hpp__
#include "../../cfg/string.hpp"
#endif // !__c0de4un_string_hpp__

// Include opengl
#ifndef __c0de4un_opengl_hpp__
#include "../../cfg/opengl.hpp"
#endif // !__c0de4un_opengl_hpp__

// GLTexture2D declared
#define __c0de4un_gl_texture_2D_decl__

namespace c0de4un
{

	/*
	 * GLTexture2D - 2D texture asset (game resource) for OpenGL.
	 *
	 * @version 1.0.0
	*/
	class GLTexture2D final
	{

	public:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Constructor & destructor
		// ===========================================================

		/*
		 * GLTexture2D constructor
		 *
		 * @param pName - Name.
		 * @param pFile - Image-file path.
		*/
		explicit GLTexture2D( const std::string & pName, const std::string & pFile );

		/* GLTexture2D destructor */
		~GLTexture2D( );

		// -------------------------------------------------------- \\

	private:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Constants
		// ===========================================================

		/* Name */
		const std::string mName;

		/* Image path*/
		const std::string mFile;

		// ===========================================================
		// Fields
		// ===========================================================

		/* OpenGL Texture Object ID */
		GLuint mTextureObject;

		// ===========================================================
		// Deleted
		// ===========================================================

		/* @deleted GLTexture2D const copy constructor */
		GLTexture2D( const GLTexture2D & ) = delete;

		/* @deleted GLTexture2D const copy assignment operator */
		GLTexture2D operator=( const GLTexture2D & ) = delete;

		/* @deleted GLTexture2D move constructor */
		GLTexture2D( GLTexture2D && ) = delete;

		/* @deleted GLTexture2D move assignment operator */
		GLTexture2D & operator=( GLTexture2D && ) = delete;

		// -------------------------------------------------------- \\

	};

}

#endif // !__c0de4un_gl_texture_2D_hpp__