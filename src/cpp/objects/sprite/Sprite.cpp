/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

// HEADER
#ifndef __c0de4un_sprite_hpp__
#include "Sprite.hpp"
#endif // !__c0de4un_sprite_hpp__

namespace c0de4un
{

	// -------------------------------------------------------- \\

	// ===========================================================
	// Constructor & destructor
	// ===========================================================

	/*
	 * Sprite constructor
	*/
	Sprite::Sprite( )
		: GameObject( )
	{// TODO Sprite::constructor
	}

	/* Sprite destructor */
	Sprite::~Sprite( )
	{// TODO Sprite::destructor
	}

	// ===========================================================
	// Getter & Setter
	// ===========================================================

	/*
	 * Returns for component of the given type.
	 *
	 * @thread_safety - not thread-safe.
	 * @param pTypeID - component type.
	 * @return - pointer to the component, or null if don't have one.
	*/
	void *const Sprite::getComponent( const ComponentType pTypeID ) const noexcept
	{// TODO Sprite::getComponent

		// Return null
		return( nullptr );

	}

	// ===========================================================
	// Methods
	// ===========================================================

	/*
	 * Attaches the given component.
	 *
	 * @thread_safety - thread-safe, synchronization (thread-lock) used.
	 * @param pTypeID - component type.
	 * @param pComponent - pointer to the component.
	 * @throws - can throw std::bad_alloc.
	*/
	void Sprite::attachComponent( const ComponentType pTypeID, void *const pComponent )
	{// TODO Sprite::attachComponent

	}

	/*
	 * Detaches component of the given type.
	 *
	 * @thread_safety - thread-safe, synchronization (thread-lock) used.
	 * @param pTypeID - component type.
	 * @throws - no exceptions.
	*/
	void Sprite::detachComponent( const ComponentType pTypeID ) noexcept
	{// TODO Sprite::detachComponent

	}

	// -------------------------------------------------------- \\

}