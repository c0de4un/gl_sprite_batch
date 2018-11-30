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

// Forward-declared PNGImage
#ifndef __c0de4un_png_image_decl__
#define __c0de4un_png_image_decl__
namespace c0de4un { class PNGImage; }
#endif // !__c0de4un_png_image_decl__

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
		// Constants
		// ===========================================================

		/* Name */
		const std::string mName;

		/* Image path*/
		const std::string mFile;

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

		// ===========================================================
		// Getter & Setter
		// ===========================================================

		/* Returns 2D Texture Object ID */
		const GLuint & getTextureObject( ) const noexcept;

		// ===========================================================
		// Methods
		// ===========================================================

		/*
		 * Load this 2D Texture.
		 *
		 * @thread_safety - render-thread only.
		 * @return - 'true' if OK.
		 * @throws - can throw exception.
		*/
		const bool Load( );

		/*
		 * Unload 2D Texture.
		 *
		 * @thread_safety - render-thread only.
		 * @throws - can throw exception.
		*/
		void Unload( );

		// -------------------------------------------------------- \\

	private:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Fields
		// ===========================================================

		/* OpenGL Texture Object ID */
		GLuint mTextureObject;

		/* PNGImage */
		PNGImage * mImage;

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