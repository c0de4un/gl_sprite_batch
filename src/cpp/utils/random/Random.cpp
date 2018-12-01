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
		: mGenerator( std::time( nullptr ) ),
		mUID( )
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
	const int Random::getUint32( const int & pMin, const int & pMax )
	{

		// Check range
		if ( pMin >= pMax )
			throw std::exception( "Random::getUint32 - min >= max !" );

		// Change number distribution range (same as creating new instance)
		mUID.param( std::uniform_int_distribution<int>::param_type( pMin, pMax ) );
		
		// Return result
		return( mUID( mGenerator ) );

	}

	/*
	 * Generates pseudo random float number in the given range.
	*/
	const float Random::getFloat( const float & pMin, const float & pMax )
	{

		// Check range
		if ( pMin >= pMax )
			throw std::exception( "Random::getUint32 - min >= max !" );

		//return( pMin );
		return( std::uniform_real_distribution<float>{ pMin, pMax }( mGenerator ) );
	}

	// -------------------------------------------------------- \\

}