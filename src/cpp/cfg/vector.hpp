/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_vector_hpp__
#define __c0de4un_vector_hpp__

// Include std::vector
#include <vector>

// Include std::algorithm
#include <algorithm>

namespace c0de4un
{

	///*
	// * Swap & pop_back vector item.
	// *
	// * @thread_safety - not thread-safe.
	// * @param pVector - std::vector to modify.
	// * @param pItem - Item to remove.
	//*/
	//template <typename T>
	//static void swap_pop( std::vector<T> & pVector, T pItem ) noexcept
	//{

	//	// Search Item
	//	const std::vector<T>::iterator position_ = std::find( pVector.begin( ), pVector.end( ), pItem );

	//	// Cancel
	//	if ( position_ == pVector.end( ) )
	//		return;

	//	// Swap
	//	if ( pVector.size( ) > 2 )
	//	{
	//		// Swap
	//		std::swap( *position_, pVector.back( ) );

	//		// Pop
	//		pVector.pop_back( );
	//	}
	//	else
	//		pVector.erase( position_ );

	//}

	///*
	// * Swap & pop_back vector item.
	// *
	// * @thread_safety - not thread-safe.
	// * @param position_ - std::vector const iterator with position of item.
	// * @param pItem - Item to remove.
	//*/
	//template <typename T>
	//static void swap_pop( std::vector<T> & pVector, const std::vector<T>::iterator & position_ ) noexcept
	//{

	//	// Swap
	//	if ( pVector.size( ) > 2 )
	//	{
	//		// Swap
	//		std::swap( *position_, pVector.back( ) );

	//		// Pop
	//		pVector.pop_back( );
	//	}
	//	else
	//		pVector.erase( position_ );

	//}

}

#endif // !__c0de4un_vector_hpp__