/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_scale_hpp__
#define __c0de4un_scale_hpp__

// Include mutex
#ifndef __c0de4un_mutex_hpp__
#include "../cfg/mutex.hpp"
#endif // !__c0de4un_mutex_hpp__

// Include glm
#ifndef __c0de4un_glm_hpp__
#include "../cfg/glm.hpp"
#endif // !__c0de4un_glm_hpp__

// Scale declared
#define __c0de4un_scale_decl__

namespace c0de4un
{

	/*
	 * Scale - scale data component.
	 *
	 * @version 1.0
	*/
	struct Scale final
	{

		/* Data changed flag */
		bool changed_;

		/* Scale vector */
		glm::vec3 vec3_;

		/* Shared (between systems) Thread-Lock */
		std::unique_lock<std::mutex> * lock_;

	};

}

#endif // !__c0de4un_scale_hpp__