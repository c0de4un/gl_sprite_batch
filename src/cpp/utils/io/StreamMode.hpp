/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_stream_mode_hpp__
#define __c0de4un_stream_mode_hpp__

// Encoding declared
#define __c0de4un_stream_mode_decl__

namespace c0de4un
{

	/*
	 * StreamMode - stream modes enum.
	 *
	 * @version 1.0.0
	*/
	class StreamMode final
	{

	public:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Constants
		// ===========================================================

		/* Read chars (strings, lines). */
		static constexpr unsigned char READ_CHARS = 0;

		/* Read bytes (signed || unsigned). Binary read-mode. */
		static constexpr unsigned char READ_BYTES = 1;

		/* Write chars (strings, lines). */
		static constexpr unsigned char WRITE_CHARS = 2;

		/* Write bytes (signed || unsigned). Binary write-mode. */
		static constexpr unsigned char WRITE_BYTES = 3;

		// -------------------------------------------------------- \\

	};

}

#endif // !__c0de4un_stream_mode_hpp__