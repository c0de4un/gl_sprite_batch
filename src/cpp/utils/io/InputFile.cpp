/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

// HEADER
#ifndef __c0de4un_input_file_hpp__
#include "InputFile.hpp"
#endif // !__c0de4un_input_file_hpp__

// Include Log
#ifndef __c0de4un_log_hpp__
#include "../log/Log.hpp"
#endif // !__c0de4un_log_hpp__

namespace c0de4un
{

	// -------------------------------------------------------- \\

	// ===========================================================
	// Constructor & destructor
	// ===========================================================

	/* InputFile constructor */
	InputFile::InputFile( )
		: buffer_( nullptr ),
		inputStream_( nullptr ),
		readedTotal_( 0 ),
		readedCount_( 0 ),
		bufferSize_( 0 )
	{

		// Log
		Log::printDebug( "InputFile::constructor" );

	}

	/* InputFile destructor */
	InputFile::~InputFile( )
	{

		// Log
		Log::printDebug( "InputFile::destructor" );

		// Close
		this->close( );

	}

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
	//const std::string InputFile::getFileAccessMode_A( const unsigned char pEncoding, const unsigned char pMode )
	//{

	//	// Access Mode Attributes
	//	std::string accessAttribs( "" );

	//	// Mode
	//	switch ( pMode )
	//	{
	//	case StreamMode::READ_CHARS:
	//		accessAttribs += "r";
	//		break;
	//	case StreamMode::READ_BYTES:
	//		accessAttribs += "rb";
	//		break;
	//	case StreamMode::WRITE_CHARS:
	//		accessAttribs += "w";
	//		break;
	//	case StreamMode::WRITE_BYTES:
	//		accessAttribs += "wb";
	//		break;
	//	default: // Error
	//		throw std::exception( "InputFile::getAccessMode_A - invalid access mode", 3 );
	//	}

	//	// Encoding
	//	switch ( pEncoding )
	//	{
	//	case Encoding::ANSI: // Default on Windows
	//		break;
	//	case Encoding::UNICODE:
	//		accessAttribs += ", css=UNICODE";
	//		break;
	//	case Encoding::UTF_8_LE:
	//		accessAttribs += ", css=UTF-8";
	//		break;
	//	case Encoding::UTF_16_LE:
	//		accessAttribs += ", css=UTF-16LE";
	//		break;
	//	default:// Error
	//		throw std::exception( "InputFile::getAccessMode_A - invalid access mode", 4 );
	//		break;
	//	}

	//	// Return Access Mode Params
	//	return( accessAttribs );

	//}

	/*
	 * Converts stream-mode to STL stream-mode.
	 *
	 * @param pMode - stream-mode, default is reading-bytes.
	 * @return - attributes for input-stream.
	*/
	const int InputFile::getStreamAccessMode_A( const unsigned char pMode ) noexcept
	{

		// Mode
		switch ( pMode )
		{
		case StreamMode::READ_CHARS:
			return( std::istream::in );
		case StreamMode::READ_BYTES:
			return( std::istream::in | std::istream::binary );
		}

		// Return default
		return( std::istream::in );

	}

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
	const bool InputFile::openStream_A( const std::string & filePath_, const unsigned char pMode, const std::uint32_t & buffSize )
	{

		// Cancel
		if ( inputStream_ != nullptr )
			throw std::exception( "InputFile::openStream_A - already opened !" );

		// Log
		std::string logMsg( "InputFile::openStream_A - file path=" );
		logMsg += filePath_;
		Log::printDebug( logMsg.c_str( ) );

		// Get Input-Stream access-mode
		const int mode_ = getStreamAccessMode_A( pMode );

		// Try-catch Block
		try
		{

			// Open ifstream
			inputStream_ = new std::ifstream( filePath_.c_str( ), mode_ );

			// Check stream status
			if ( !inputStream_->is_open( ) )
			{// Failed to open

				// Log
				logMsg = "InputFile::openStream_A - failed to open file #";
				logMsg += filePath_;
				Log::printWarning( logMsg.c_str( ) );
				
				// Close
				this->close( );

				// Return FALSE
				return( false );

			}

			// Allocate Buffer
			if ( buffSize > 0 )
			{

				// Create Buffer
				buffer_ = new char[static_cast<unsigned int>( buffSize ) * sizeof( char )];

				// Remember buffer size
				this->bufferSize_ = buffSize;

			}

		}
		catch ( const std::exception & exception_ )
		{

			// Log
			logMsg = "InputFile::openStream_A - ERROR: ";
			logMsg += exception_.what( );
			Log::printError( logMsg.c_str( ) );

			// Close
			this->close( );

			// Re-throw
			throw;

		}
		catch ( ... )
		{

			// Log
			Log::printError( "InputFile::openStream_A - unknown error !" );

			// Close
			this->close( );

			// Throw
			throw std::exception( "InputFile::openStream_A - unknown error !" );

		}

		// Return TRUE
		return( true );

	}

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
	const bool InputFile::readBytes_A( char * pBuffer_, std::uint32_t & pCount_ )
	{

		// Check input-stream state
		if ( inputStream_ == nullptr )
			throw std::exception( "InputFile::readBytes_A - not even opened !" );

		// Bytes to read
		if ( buffer_ != nullptr )
		{

			// Set bytes to read
			if ( pCount_ < 1 )
				pCount_ = bufferSize_;

			// Set buffer to use
			pBuffer_ = buffer_;

		}

		// Check byte to read
		if ( pCount_ < 1 )
			throw std::exception( "InputFile::readBytes_A - Illegal arguments, can't read 0 bytes !" );

		// Try-catch Block
		try
		{

			// Read bytes & write them to the buffer
			if ( inputStream_->read( pBuffer_, pCount_ ) )
			{// Normal Reading
				// Get number of chars (symbols, elements) readed
				readedCount_ = static_cast<std::uint32_t>( inputStream_->gcount( ) );

				// Update Total Readed
				readedTotal_ += readedCount_;

				// Return TRUE
				return( true );
			}
			else
			{// EOF || errors
				// Get number of chars (symbols, elements) readed
				readedCount_ = static_cast<std::uint32_t>( inputStream_->gcount( ) );

				// Update Total Readed
				readedTotal_ += readedCount_;

				// Return FALSE
				return( false );
			}

		}
		catch ( const std::exception & exception_ )
		{

			// Log
			std::string logMsg( "InputFile::readBytes_A - ERROR: " );
			logMsg += exception_.what( );
			Log::printError( logMsg.c_str( ) );

			// Close
			this->close( );

			// Re-throw
			throw;

		}
		catch ( ... )
		{

			// Log
			Log::printError( "InputFile::readBytes_A - unknown error !" );

			// Close
			this->close( );

			// Throw
			throw std::exception( "InputFile::readBytes_A - unknown error !" );

		}

		// Return TRUE
		return( true );

	}

	/*
	 * Close input stream.
	 *
	 * @thread_safety - not thread-safe.
	 * @throws - can throw exception.
	*/
	void InputFile::close( )
	{

		// Log
		Log::printDebug( "InputFile::close" );

		// Close std::fistream
		if ( inputStream_ != nullptr )
		{

			// Delete (closed automatically)
			delete inputStream_;

			// Reset pointer-value
			inputStream_ = nullptr;

		}

		// Release Buffer
		if ( buffer_ != nullptr )
		{

			// Delete Buffer
			delete[] buffer_;

			// Reset pointer-value
			buffer_ = nullptr;

		}

		// Reset Total Readed count
		readedTotal_ = 0;

		// Reset last-call readed
		readedCount_ = 0;

	}

	// -------------------------------------------------------- \\

}