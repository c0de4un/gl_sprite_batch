/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_batch_request_hpp__
#define __c0de4un_batch_request_hpp__

// Include opengl
#ifndef __c0de4un_opengl_hpp__
#include "../../cfg/opengl.hpp"
#endif // !__c0de4un_opengl_hpp__

// Forward-declaration of Drawable
#ifndef __c0de4un_drawable_decl__
#define __c0de4un_drawable_decl__
namespace c0de4un { struct Drawable; }
#endif // !__c0de4un_drawable_decl__

// BatchRequest declared
#define __c0de4un_batch_request_decl__

// Enable structure-data (fields, variables) alignment (by compilator) to 1 byte
#pragma pack( push, 1 )

namespace c0de4un
{

	/*
	 * BatchRequest - allows to transfer key-information to the Sprite-Batching System.
	 * 
	 * @version 1.0.0
	*/
	struct BatchRequest final
	{

		/* OpenGL Shader Program Object ID */
		GLuint shaderProgram_;

		/* Vertex Position Attribute Index (ID) */
		GLint vertexPosAttrIndex_;

		/* Vertex Texture Coordinates */
		GLint texCoordsAttrIndex_;

		/* Vertices Color */
		GLint colorAttrIndex_;

		/* OpenGL 2D Texture Object ID */
		GLuint textureObject_;

		/* Model View Projection (MVP) Uniform index */
		GLint mvpMatUniformIndex_;

		/* Drawable-Object */
		Drawable * drawable_;

		/* BatchRequest default constructor */
		BatchRequest( )
			: shaderProgram_( 0 ),
			vertexPosAttrIndex_( -1 ),
			texCoordsAttrIndex_( -1 ),
			colorAttrIndex_( -1 ),
			textureObject_( 0 ),
			mvpMatUniformIndex_( -1 ),
			drawable_( nullptr )
		{
		}

		/* BatchRequest destructor */
		~BatchRequest( )
		{
		}

		/* @deleted BatchRequest const copy constructor */
		BatchRequest( const BatchRequest & ) = delete;

		/* @deleted BatchRequest copy assignment operator */
		BatchRequest & operator=( const BatchRequest & ) = delete;

		/* @deleted BatchRequest move constructor */
		BatchRequest( BatchRequest && ) = delete;

		/* @deleted BatchRequest move assignment operator */
		BatchRequest & operator=( BatchRequest && ) = delete;

	};

}

// Restore structure-data alignment to default (8-byte on MSVC)
#pragma pack( pop )

#endif // !__c0de4un_batch_request_hpp__