/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

// HEADER
#ifndef __c0de4un_random_hpp__
#include "Random.hpp"
#endif // !__c0de4un_random_hpp__

namespace c0de4un
{

	// -------------------------------------------------------- \\

	// ===========================================================
	// Constructor & destructor
	// ===========================================================

	/* Random constructor */
	Random::Random( )
		: mGenerator( std::time( 0 ) )
	{
	}

	/* Random destructor */
	Random::~Random( )
	{
	}

	// ===========================================================
	// Methods
	// ===========================================================

	/*
	 * Generates pseudo random unsigned int number in the given range.
	*/
	unsigned int Random::getUint32( const unsigned int & pMin, const unsigned int & pMax )
	{

		// Create distribution for uint32
		std::uniform_int_distribution<unsigned int> uid( pMin, pMax );

		// Create random number
		//int randomNumber_ = uid( gen ), x = -1;
		
		// Return result
		return( uid( mGenerator ) );
		//return( randomNumber_ );

	}

	// -------------------------------------------------------- \\

}