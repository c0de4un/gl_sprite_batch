/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
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

	/* Physics Body Component Type-ID */
	static constexpr ComponentType BODY_COMPONENT = 2;

	/* Position Component Type-ID */
	static constexpr ComponentType POSITION_COMPONENT = 3;

	/* Rotation Component Type-ID */
	static constexpr ComponentType ROTATION_COMPONENT = 4;

	/* Scale Component Type-ID */
	static constexpr ComponentType SCALE_COMPONENT = 5;

}

#endif // !__c0de4un_components_hpp__