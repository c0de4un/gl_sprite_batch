/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_random_hpp__
#define __c0de4un_random_hpp__

// Include std::random
#include <random> // mt19937

// Include std::time
#include <ctime> // time

// Random declared
#define __c0de4un_random_decl__

namespace c0de4un
{

	/*
	 * Random - utility-class to generate random (pseudo) int-values.
	 *
	 * @versnion 1.0
	*/
	class Random final
	{

	public:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Constructor & destructor
		// ===========================================================

		/* Random constructor */
		explicit Random( );

		/* Random destructor */
		~Random( );

		// ===========================================================
		// Methods
		// ===========================================================

		/*
		 * Generates pseudo random unsigned int number in the given range.
		*/
		unsigned int getUint32( const unsigned int & pMin, const unsigned int & pMax );

		// -------------------------------------------------------- \\

	private:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Fields
		// ===========================================================

		/*
		 * Pseudo random number generator.
		 *
		 * mt19937 - 32-bit Mersenne Twister by Matsumoto and Nishimura, 1998.
		*/
		std::mt19937 mGenerator;

		// ===========================================================
		// Deleted
		// ===========================================================

		/* @deleted Random const copy constructor */
		Random( const Random & ) = delete;

		/* @deleted Random const copy assignment operator */
		Random operator=( const Random & ) = delete;

		/* @deleted Random move constructor */
		Random( Random && ) = delete;

		/* @deleted Random move assignment operator */
		Random & operator=( Random && ) = delete;

		// -------------------------------------------------------- \\

	};

}

#endif // !__c0de4un_random_hpp__