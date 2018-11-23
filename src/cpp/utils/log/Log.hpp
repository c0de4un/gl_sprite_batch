/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_log_hpp__
#define __c0de4un_log_hpp__

namespace c0de4un
{

	/*
	 * Log - logging utility.
	 *
	 * @features
	 * - Visual Studio & VSCode debug-window output support ;
	 * - output to console ;
	*/
	class Log final
	{

	private:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Deleted
		// ===========================================================

		/* @deleted Log const copy constructor */
		Log( const Log & ) = delete;

		/* @deleted Log const copy assignment operator */
		Log & operator=( const Log & ) = delete;

		/* @deleted Log move constructor */
		Log( Log && ) = delete;

		/* @deleted Log move assignment operator */
		Log & operator=( Log && ) = delete;

		// -------------------------------------------------------- \\

	public:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Methods
		// ===========================================================

		/*
		 * Print INFO-level (good/green) message to the log.
		 *
		 * @thread_safety - thread-safe.
		 * @param pMessage - ANSI c-string to print.
		 * @throws - no exceptions are thrown.
		*/
		static void printInfo( const char *const pMessage ) noexcept;

		/*
		 * Print DEBUG-level (normal/gray) message to the log.
		 *
		 * @thread_safety - thread-safe.
		 * @param pMessage - ANSI c-string to print.
		 * @throws - no exceptions are thrown.
		*/
		static void printDebug( const char *const pMessage ) noexcept;

		/*
		 * Print WARNING-level (danger/orange) message to the log.
		 *
		 * @thread_safety - thread-safe.
		 * @param pMessage - ANSI c-string to print.
		 * @throws - no exceptions are thrown.
		*/
		static void printWarning( const char *const pMessage ) noexcept;

		/*
		 * Print ERROR-level (critical/red) message to the log.
		 *
		 * @thread_safety - thread-safe.
		 * @param pMessage - ANSI c-string to print.
		 * @throws - no exceptions are thrown.
		*/
		static void printError( const char *const pMessage ) noexcept;

		// -------------------------------------------------------- \\

	};

}

#endif // !__c0de4un_log_hpp__