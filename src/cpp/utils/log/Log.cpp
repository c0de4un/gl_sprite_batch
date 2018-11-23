/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

// HEADER
#ifndef __c0de4un_log_hpp__
#include "Log.hpp"
#endif // !__c0de4un_log_hpp__

// Include STL
#include <iostream> // cout, cin, cin.get

// Include Windows
#include <Windows.h> // OutputDebugStringA, OutputDebugStringW

namespace c0de4un
{

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
	void Log::printInfo( const char *const pMessage ) noexcept
	{

		// String
		std::string logMsg( "INFO: " );

		// Append Message
		logMsg += pMessage;

		// Print to the console
		std::cout << logMsg.c_str( ) << std::endl;

		// Append endl (Visual Studio Debug-Output Bag)
		logMsg += "\n";

		// Print to the Visual Studio || VSCode Debug-Output
		OutputDebugStringA( logMsg.c_str( ) );

	}

	/*
	 * Print DEBUG-level (normal/gray) message to the log.
	 *
	 * @thread_safety - thread-safe.
	 * @param pMessage - ANSI c-string to print.
	 * @throws - no exceptions are thrown.
	*/
	void Log::printDebug( const char *const pMessage ) noexcept
	{

		// String
		std::string logMsg( "DEBUG: " );

		// Append Message
		logMsg += pMessage;

		// Print to the console
		std::cout << logMsg.c_str( ) << std::endl;

		// Append endl (Visual Studio Debug-Output Bag)
		logMsg += "\n";

		// Print to the Visual Studio || VSCode Debug-Output
		OutputDebugStringA( logMsg.c_str( ) );

	}

	/*
	 * Print WARNING-level (danger/orange) message to the log.
	 *
	 * @thread_safety - thread-safe.
	 * @param pMessage - ANSI c-string to print.
	 * @throws - no exceptions are thrown.
	*/
	void Log::printWarning( const char *const pMessage ) noexcept
	{

		// String
		std::string logMsg( "WARNING: " );

		// Append Message
		logMsg += pMessage;

		// Print to the console
		std::cout << logMsg.c_str( ) << std::endl;

		// Append endl (Visual Studio Debug-Output Bag)
		logMsg += "\n";

		// Print to the Visual Studio || VSCode Debug-Output
		OutputDebugStringA( logMsg.c_str( ) );

	}

	/*
	 * Print ERROR-level (critical/red) message to the log.
	 *
	 * @thread_safety - thread-safe.
	 * @param pMessage - ANSI c-string to print.
	 * @throws - no exceptions are thrown.
	*/
	void Log::printError( const char *const pMessage ) noexcept
	{

		// String
		std::string logMsg( "ERROR: " );

		// Append Message
		logMsg += pMessage;

		// Print to the console
		std::cout << logMsg.c_str( ) << std::endl;

		// Append endl (Visual Studio Debug-Output Bag)
		logMsg += "\n";

		// Print to the Visual Studio || VSCode Debug-Output
		OutputDebugStringA( logMsg.c_str( ) );

	}

	// -------------------------------------------------------- \\

}