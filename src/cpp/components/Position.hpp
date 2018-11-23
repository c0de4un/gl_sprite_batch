/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_position_hpp__
#define __c0de4un_position_hpp__

// Include mutex
#ifndef __c0de4un_mutex_hpp__
#include "../cfg/mutex.hpp"
#endif // !__c0de4un_mutex_hpp__

// Include glm
#ifndef __c0de4un_glm_hpp__
#include "../cfg/glm.hpp"
#endif // !__c0de4un_glm_hpp__

// Position declared
#define __c0de4un_position_decl__

// Pack structure data
#pragma pack( push, 1 )

namespace c0de4un
{

	/*
	 * Position - position data component.
	*/
	struct Position final
	{

		/* Data changed flag */
		bool changed_;

		/* vector */
		glm::vec3 vec3_;

		/* Shared (between systems) Thread-Lock */
		std::unique_lock<std::mutex> * lock_;

	};

}

// Restore data alignment
#pragma pack( pop )

#endif // !__c0de4un_position_hpp__