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

		/* Position changed flag */
		bool positionChanged_;

		/* Rotation changed flag */
		bool rotationChanged_;

		/* Scale changed flag */
		bool scaleChanged_;

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

		/*
		 * Object Position vector.
		 * If changed, translation flag & state flag must be set to notify batching-system.
		*/
		//glm::vec3 position_;

		/*
		 * Object Position component
		*/
		Position * position_;

		/*
		 * Rotation vector in degrees.
		*/
		Rotation * rotation_;
		//glm::vec3 rotation_;

		/*
		 * Scale vector
		*/
		Scale * scale_;
		//glm::vec3 scale_;

		/*
		 * Translation (position) Matrix.
		 *
		 * Calculated only when required.
		*/
		glm::mat4 translationMat_;

		/*
		 * Scale Matrix.
		 * Calculate only when required.
		*/
		glm::mat4 scaleMat_;

		/*
		 * Model Matrix [Translation * Rotation * Scale]
		*/
		glm::mat4 modelMat_;

		/*
		 * Calculated orientation (rotation) quaternion.
		 *
		 * Allows to avoid unnecessary recalculation on each frame.
		 * Also provides faster rotation changes apply then matrix (matrix * vector).
		*/
		glm::quat orientationQuat_;

	};

}

// Restore structure-data alignment to default (8-byte on MSVC)
#pragma pack( pop )

#endif // !__c0de4un_drawable_hpp__