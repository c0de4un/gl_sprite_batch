/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_sprite_hpp__
#define __c0de4un_sprite_hpp__

// Include GameObject
#ifndef __c0de4un_game_object_hpp__
#include "../GameObject.hpp"
#endif // !__c0de4un_game_object_hpp__

// Sprite declared
#define __c0de4un_sprite_decl__

namespace c0de4un
{

	/*
	 * Sprite - sprite game object.
	 *
	 * @version 1.0
	*/
	class Sprite final : public c0de4un::GameObject
	{

	private:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Fields
		// ===========================================================



		// ===========================================================
		// Deleted
		// ===========================================================

		/* @deleted Sprite const copy constructor */
		explicit Sprite( const Sprite & ) noexcept = delete;

		/* @deleted Sprite const copy assignment operator */
		Sprite & operator=( const Sprite & ) noexcept = delete;

		/* @deleted Sprite move constructor */
		explicit Sprite( Sprite && ) noexcept = delete;

		/* @deleted Sprite move assignment operator */
		Sprite && operator=( Sprite && ) noexcept = delete;

		// -------------------------------------------------------- \\

	public:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Constructor & destructor
		// ===========================================================

		/*
		 * Sprite constructor
		*/
		explicit Sprite( );

		/* Sprite destructor */
		virtual ~Sprite( );

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
		virtual void *const getComponent( const ComponentType pTypeID = 0 ) const noexcept final;

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
		virtual void attachComponent( const ComponentType pTypeID = 0, void *const pComponent = nullptr ) final;

		/*
		 * Detaches component of the given type.
		 *
		 * @thread_safety - thread-safe, synchronization (thread-lock) used.
		 * @param pTypeID - component type.
		 * @throws - no exceptions.
		*/
		virtual void detachComponent( const ComponentType pTypeID = 0 ) noexcept final;

		// -------------------------------------------------------- \\

	};

}

#endif // !__c0de4un_sprite_hpp__