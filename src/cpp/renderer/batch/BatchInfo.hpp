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
		GLuint vertexPosAttrIndex_;

		/* Vertex Texture Coordinates */
		GLuint texCoordsAttrIndex_;

		/* Vertices Color */
		GLuint colorAttrIndex_;

		/* MVP (Model View Projection) Matrix Uniform (global) index */
		GLuint mvpUniformIndex_;

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

	};

}

// Restore structure-data alignment to default (8-byte on MSVC)
#pragma pack( pop )

#endif // !__c0de4un_batch_info_hpp__