/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_batch_info_hpp__
#define __c0de4un_batch_info_hpp__

// Include opengl
#ifndef __c0de4un_opengl_hpp__
#include "../../cfg/opengl.hpp"
#endif // !__c0de4un_opengl_hpp__

// Include std::map
#ifndef __c0de4un_map_hpp__
#include "../../cfg/map.hpp"
#endif // !__c0de4un_map_hpp__

// Include std::vector
#ifndef __c0de4un_vector_hpp__
#include "../../cfg/vector.hpp"
#endif // !__c0de4un_vector_hpp__

// Forward-declaration of Drawable
#ifndef __c0de4un_drawable_decl__
#define __c0de4un_drawable_decl__
namespace c0de4un { struct Drawable; }
#endif // !__c0de4un_drawable_decl__

// BatchInfo declared
#define __c0de4un_batch_info_decl__

// Enable structure-data (fields, variables) alignment (by compilator) to 1 byte
#pragma pack( push, 1 )

namespace c0de4un
{

	/*
	 * BatchInfo - allows to pass several key-arguments (shader program attributes, 
	 * texture sampler id, etc) to sprite-batching system.
	 *
	 * @version 1.0
	*/
	struct BatchInfo final
	{

		/* ID of Vertex Position Buffer Object */
		static constexpr unsigned char POSITION_VBO = 0;

		/* ID for Vertices Indices Buffer Object */
		static constexpr unsigned char INDICES_VBO = 1;

		/* ID for Vertices 2D-Texture Coordinates Buffer Object */
		static constexpr unsigned char TEXTURE_COORDS_VBO = 2;

		/* Vertex Position Attribute Index (ID) */
		GLint vertexPosAttrIndex_;

		/* Vertex Texture Coordinates */
		GLint texCoordsAttrIndex_;

		/* Vertices Color */
		GLint colorAttrIndex_;

		/* MVP (Model View Projection) Matrix uniform index */
		GLint mvpMatUniformLoc_;

		/*
		 * Vertex Buffer Objects
		*/
		GLuint vboIDs_[3];

		/*
		 * Vertex Array Object
		*/
		GLuint vaoID_;

		/*
		 * 2D Texture Objects IDs map.
		 * Used to sort Drawable-Objects by 2D-Texture.
		*/
		std::map<const GLuint, std::vector<Drawable*>> textureObjects_;

		/* BatchInfo default constructor */
		BatchInfo( )
			: vertexPosAttrIndex_( -1 ),
			texCoordsAttrIndex_( -1 ),
			colorAttrIndex_( -1 ),
			mvpMatUniformLoc_( -1 ),
			vboIDs_{ 0, 0, 0 },
			vaoID_( 0 ),
			textureObjects_( )
		{
		}

		/* BatchInfo destructor */
		~BatchInfo( )
		{
		}

		/* @deleted BatchInfo const copy constructor */
		BatchInfo( const BatchInfo & ) = delete;

		/* @deleted BatchInfo copy assignment operator */
		BatchInfo & operator=( const BatchInfo & ) = delete;

		/* @deleted BatchInfo move constructor */
		BatchInfo( BatchInfo && ) = delete;

		/* @deleted BatchInfo move assignment operator */
		BatchInfo & operator=( BatchInfo && ) = delete;

	};

}

// Restore structure-data alignment to default (8-byte on MSVC)
#pragma pack( pop )

#endif // !__c0de4un_batch_info_hpp__