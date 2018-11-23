/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_game_object_hpp__
#define __c0de4un_game_object_hpp__

// Include Components
#ifndef __c0de4un_components_hpp__
#include "../utils/components/Components.hpp"
#endif // !__c0de4un_components_hpp__

// GameObject declared
#define __c0de4un_game_object_decl__

namespace c0de4un
{

	/*
	 * GameObject - base game object class.
	 *
	 * @version 1.0
	*/
	class GameObject
	{

	public:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Destructor
		// ===========================================================

		/* GameObject destructor */
		virtual ~GameObject( );

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
		virtual void *const getComponent( const ComponentType pTypeID = 0 ) const noexcept = 0;

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
		virtual void attachComponent( const ComponentType pTypeID = 0, void *const pComponent = nullptr ) = 0;

		/*
		 * Detaches component of the given type.
		 *
		 * @thread_safety - thread-safe, synchronization (thread-lock) used.
		 * @param pTypeID - component type.
		 * @throws - no exceptions.
		*/
		virtual void detachComponent( const ComponentType pTypeID = 0 ) noexcept = 0;

		// -------------------------------------------------------- \\

	protected:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Constructors
		// ===========================================================

		/*
		 * GameObject constructor
		*/
		explicit GameObject( );

		// ===========================================================
		// Deleted
		// ===========================================================

		/* @deleted GameObject const copy constructor */
		explicit GameObject( const GameObject & ) noexcept = delete;

		/* @deleted GameObject const copy assignment operator */
		GameObject & operator=( const GameObject & ) noexcept = delete;

		/* @deleted GameObject move constructor */
		explicit GameObject( GameObject && ) noexcept = delete;

		/* @deleted GameObject move assignment operator */
		GameObject && operator=( GameObject && ) noexcept = delete;

		// -------------------------------------------------------- \\

	};

}

#endif // !__c0de4un_game_object_hpp__