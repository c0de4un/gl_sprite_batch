/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_view_projection_hpp__
#define __c0de4un_view_projection_hpp__

// Include glm
#ifndef __c0de4un_glm_hpp__
#include "../cfg/glm.hpp"
#endif // !__c0de4un_glm_hpp__

// ViewProjection declared
#define __c0de4un_view_projection_decl__

// Enable structure-data (fields, variables) alignment (by compilator) to 1 byte
#pragma pack( push, 1 )

namespace c0de4un
{

	/*
	 * ViewProjection - stores cached View & Projection Matrices.
	 * Allows to make the recalculation of the MVP (Model View Projection) matrix easier.
	 *
	 * @version 1.0
	*/
	struct ViewProjection final
	{

		/*
		 * View Matrix.
		*/
		glm::mat4 viewMat_;

		/*
		 * Projection Matrix.
		*/
		glm::mat4 projectionMat_;

		/*
		 * View and/or Projection Matrix changed, update required.
		 * Reset after batching complete.
		*/
		bool updated_;

		/* ViewProjection constructor */
		ViewProjection( )
			: viewMat_( 1.0f ),
			projectionMat_( 1.0f ),
			updated_( false )
		{
		}

		/* ViewProjection destructor */
		~ViewProjection( )
		{
		}

		/* @deleted ViewProjection const copy constructor */
		ViewProjection( const ViewProjection & ) = delete;

		/* @deleted ViewProjection const copy assignment operator */
		ViewProjection & operator=( const ViewProjection & ) = delete;

		/* @deleted ViewProjection move constructor */
		ViewProjection( ViewProjection && ) = delete;

		/* @deleted ViewProjection move assignment operator */
		ViewProjection & operator=( ViewProjection && ) = delete;

	};

}

// Restore structure-data alignment to default (8-byte on MSVC)
#pragma pack( pop )

#endif // !__c0de4un_view_projection_hpp__