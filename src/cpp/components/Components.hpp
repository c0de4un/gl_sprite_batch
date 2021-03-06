/*
 * Copyright � 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_components_hpp__
#define __c0de4un_components_hpp__

namespace c0de4un
{

	/* Component Type-ID */
	using ComponentType = unsigned char;

	/* Drawable Component Type-ID */
	static constexpr ComponentType DRAWABLE_COMPONENT = 1;

	/* Position Component Type-ID */
	static constexpr ComponentType POSITION_COMPONENT = 2;

	/* Rotation Component Type-ID */
	static constexpr ComponentType ROTATION_COMPONENT = 3;

	/* Scale Component Type-ID */
	static constexpr ComponentType SCALE_COMPONENT = 4;

	/* Velocity Component Type-ID */
	static constexpr ComponentType VELOCITY_COMPONENT = 5;

}

#endif // !__c0de4un_components_hpp__