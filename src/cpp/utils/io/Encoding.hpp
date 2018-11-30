/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_encoding_hpp__
#define __c0de4un_encoding_hpp__

// Encoding declared
#define __c0de4un_encoding_decl__

namespace c0de4un
{

	/*
	 * Encoding - encoding types enum.
	 *
	 * @version 1.0.0
	*/
	class Encoding final
	{

	public:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Constants
		// ===========================================================

		/* ANSI - default 256-chars encoding. On some platforms can have 2-bytes per char instead of 1. */
		static constexpr unsigned char ANSI = 0;

		/* UNICODE */
		static constexpr unsigned char UNICODE = 1;

		/* UTF-8 */
		static constexpr unsigned char UTF_8_LE = 2;

		/* UTF-16 */
		static constexpr unsigned char UTF_16_LE = 3;

		// -------------------------------------------------------- \\

	};

}

#endif // !__c0de4un_encoding_hpp__