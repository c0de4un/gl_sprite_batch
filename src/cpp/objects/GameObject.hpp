/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_game_object_hpp__
#define __c0de4un_game_object_hpp__

// Include string
#ifndef __c0de4un_string_hpp__
#include "../cfg/string.hpp"
#endif // !__c0de4un_string_hpp__

// Include Components
#ifndef __c0de4un_components_hpp__
#include "../components/Components.hpp"
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
		// Constants
		// ===========================================================

		/* Name */
		const std::string mName;

		// ===========================================================
		// Destructor
		// ===========================================================

		/* GameObject destructor */
		virtual ~GameObject( );

		// -------------------------------------------------------- \\

	protected:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Constructor
		// ===========================================================

		/*
		 * GameObject constructor
		 *
		 * @param pName - Name.
		*/
		explicit GameObject( const std::string & pName );

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