/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_input_file_hpp__
#define __c0de4un_input_file_hpp__

// Include std::istream
#ifndef __c0de4un_inputStream_hpp__
#include "../../cfg/istream.hpp"
#endif // !__c0de4un_inputStream_hpp__

// Include StreamMode
#ifndef __c0de4un_stream_mode_hpp__
#include "StreamMode.hpp"
#endif // !__c0de4un_stream_mode_hpp__

// InputFile declared
#define __c0de4un_input_file_decl__

namespace c0de4un
{

	/*
	 * InputFile - utility class for the input-stream reading from the file.
	 *
	 * @version 1.0.0
	*/
	class InputFile final
	{

	public:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Constructor & destructor
		// ===========================================================

		/* InputFile constructor */
		explicit InputFile( );

		/* InputFile destructor */
		~InputFile( );

		// ===========================================================
		// Getter & Setter
		// ===========================================================

		///*
		// * Converts input stream mode & encoding to system-specific (Windows, Unix)
		// * attributes for input-stream.
		// *
		// * (?) Used for FILE.
		// * (!) Do not use for wchars (& wstring).
		// *
		// * @param pEncoding - Encoding, default is ANSI.
		// * @param pMode - stream-mode, default is reading-bytes.
		// * @return - string with attributes for input-stream.
		// * @throws - can throw exception.
		//*/
		//static const std::string getFileAccessMode_A( const unsigned char pEncoding, const unsigned char pMode );

		/*
		 * Converts stream-mode to STL stream-mode.
		 *
		 * @param pMode - stream-mode, default is reading-bytes.
		 * @return - attributes for input-stream.
		*/
		static const int getStreamAccessMode_A( const unsigned char pMode ) noexcept;

		// ===========================================================
		// Methods
		// ===========================================================

		/*
		 * Open input stream to the given file with given params.
		 *
		 * @thread_safety - not thread-safe.
		 * @param filePath_ - path to the file.
		 * @param pMode - Stream-Mode (chars, bytes).
		 * @param bufferSize_ - Buffer size. 0 - to not allocate buffer.
		 * Requires pointer to the write-buffer on every read-call.
		 * @return - 'true' if OK, false if failed.
		 * @throws - can throw exception.
		*/
		const bool openStream_A( const std::string & filePath_, const unsigned char pMode, const std::uint32_t & buffSize );

		/*
		 * Read bytes (signed or unsigned chars, 1-2 or 2-4 bytes each).
		 *
		 * (?) For 1-2 bytes chars, not for wchars.
		 * 
		 * @thread_safety - not thread-safe.
		 * @param pBuffer_ - buffer to store readed data. Required only if 
		 * buffer size not set on open.
		 * @param pCount_ - number of bytes to read. 0 to use buffer-size, if buffer used. Must be < then total file length.
		 * @return - true if OK, false if failed or end of file.
		 * @throws - can throw exception.
		*/
		const bool readBytes_A( char * pBuffer_, std::uint32_t & pCount_ );

		/*
		 * Close input stream.
		 *
		 * @thread_safety - not thread-safe.
		 * @throws - can throw exception.
		*/
		void close( );

		// -------------------------------------------------------- \\

	private:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Fields
		// ===========================================================

		/* std::ifstream */
		std::ifstream * inputStream_;

		/* Buffer */
		char * buffer_;

		/* Buffer Size */
		std::uint32_t bufferSize_;

		/* Readed count */
		std::streamsize readedTotal_;

		/* Last call readed */
		std::uint32_t readedCount_;

		// ===========================================================
		// Deleted
		// ===========================================================

		/* @deleted InputFile const copy constructor */
		InputFile( const InputFile & ) = delete;

		/* @deleted InputFile const copy assignment operator */
		InputFile operator=( const InputFile & ) = delete;

		/* @deleted InputFile move constructor */
		InputFile( InputFile && ) = delete;

		/* @deleted InputFile move assignment operator */
		InputFile & operator=( InputFile && ) = delete;

		// -------------------------------------------------------- \\

	};

}

#endif // !__c0de4un_input_file_hpp__