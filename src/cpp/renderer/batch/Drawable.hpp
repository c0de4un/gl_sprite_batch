/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_drawable_hpp__
#define __c0de4un_drawable_hpp__

// Include opengl
#ifndef __c0de4un_opengl_hpp__
#include "../../cfg/opengl.hpp"
#endif // !__c0de4un_opengl_hpp__

// Include glm
#ifndef __c0de4un_glm_hpp__
#include "../../cfg/glm.hpp"
#endif // !__c0de4un_glm_hpp__

// Include Position
#ifndef __c0de4un_position_hpp__
#include "../../components/Position.hpp"
#endif // !__c0de4un_position_hpp__

// Include Rotation
#ifndef __c0de4un_rotation_hpp__
#include "../../components/Rotation.hpp"
#endif // !__c0de4un_rotation_hpp__

// Include Scale
#ifndef __c0de4un_scale_hpp__
#include "../../components/Scale.hpp"
#endif // !__c0de4un_scale_hpp__

// Drawable declared
#define __c0de4un_drawable_decl__

// Enable structure-data (fields, variables) alignment (by compilator) to 1 byte
#pragma pack( push, 1 )

namespace c0de4un
{

	/*
	 * Drawable - data-structure about drawable-object.
	 * 
	 * Contains position, rotation & scale (size) vectors, matrices & quaternions.
	 * Also stores 'OpenGL 2D Texture Object' id/pointer & 'OpenGL Shader Program' id/pointer.
	 * 
	 * @version 1.0
	*/
	struct Drawable final
	{

		/* State changed flag */
		bool stateChanged_;

		/*
		 * OpenGL 2D Texture Object ID.
		 * #0 - no texture.
		*/
		GLuint textureObject_;

		/*
		 * OpenGL Shader Program ID
		*/
		GLuint shaderProgram_;

		/* 2D-Texture #0 Sampler Location/Index */
		GLint texSamplerLoc_;

		/*
		 * Object Position component
		*/
		Position * position_;

		/*
		 * Rotation vector in degrees.
		*/
		Rotation * rotation_;

		/*
		 * Scale vector
		*/
		Scale * scale_;

		/*
		 * Thread-Lock to synchronize access.
		 * Used shareable between Components thread-lock,
		 * owned by Game Object (Entity, Node, etc).
		*/
		std::unique_lock<std::mutex> * lock_;

		/*
		 * MVP (Model View Projection) Matrix [Projection * View * Model(Translation * Rotation * Scale)]
		 * Used to avoid calculating MVP matrix each frame if not required.
		 * Depends on Camera used for render (draw).
		*/
		glm::mat4 mvpMat_;

		/*
		 * Color values in RGBA format.
		*/
		float color_[4];

		/* Drawable default constructor */
		Drawable( )
			: stateChanged_( false ),
			textureObject_( 0 ),
			shaderProgram_( 0 ),
			position_( nullptr ),
			rotation_( nullptr ),
			scale_( nullptr ),
			lock_( nullptr ),
			mvpMat_( ),
			texSamplerLoc_( -1 ),
			color_{ 1.0f, 1.0f, 1.0f, 1.0f }
		{
		}

		/* Drawable destructor */
		~Drawable( )
		{
		}

		/* @deleted Drawable const copy constructor */
		Drawable( const Drawable & ) = delete;

		/* @deleted Drawable copy assignment operator */
		Drawable & operator=( const Drawable & ) = delete;

		/* @deleted Drawable move constructor */
		Drawable( Drawable && ) = delete;

		/* @deleted Drawable move assignment operator */
		Drawable & operator=( Drawable && ) = delete;

	};

}

// Restore structure-data alignment to default (8-byte on MSVC)
#pragma pack( pop )

#endif // !__c0de4un_drawable_hpp__