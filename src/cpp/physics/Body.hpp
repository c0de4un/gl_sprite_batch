/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_body_hpp__
#define __c0de4un_body_hpp__

// Include mutex
#ifndef __c0de4un_mutex_hpp__
#include "../cfg/mutex.hpp" // std::mutex, std::unique_lock
#endif // !__c0de4un_mutex_hpp__

// Body declared
#define __c0de4un_body_decl__

namespace c0de4un
{

	/*
	 * Body - physical body data.
	 * 
	 * @version 1.0
	*/
	struct Body final
	{
		
		/* Thread-Lock */
		std::unique_lock<std::mutex> * lock_;

		/* Position-vector */

		/* Position changed-flag */
		bool * positionChanged_;

		/* Velocity-vector */

		/* Rotation-speed vector */

		/* Rotation-vector */

		/* Rotation changed-flag */
		bool * rotationChanged_;

		/* Size (scale) vector */

	};

}

#endif // !__c0de4un_body_hpp__