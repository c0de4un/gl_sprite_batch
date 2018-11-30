/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

// HEADER
#ifndef __c0de4un_png_image_hpp__
#include "PNGImage.hpp"
#endif // !__c0de4un_png_image_hpp__

// Include PNGLoader
#ifndef __c0de4un_png_loader_hpp__
#include "PNGLoader.hpp"
#endif // !__c0de4un_png_loader_hpp__

// Include InputFile
#ifndef __c0de4un_input_file_hpp__
#include "../../utils/io/InputFile.hpp"
#endif // !__c0de4un_input_file_hpp__

// Include Log
#ifndef __c0de4un_log_hpp__
#include "../../utils/log/Log.hpp"
#endif // !__c0de4un_log_hpp__

namespace c0de4un
{

	// -------------------------------------------------------- \\

	// ===========================================================
	// Constructor & destructor
	// ===========================================================

	/*
	 * PNGImage constructor
	 *
	 * @param pFile - path to the PNG-image.
	*/
	PNGImage::PNGImage( const std::string & pFile )
		: mFile( pFile ),
		mColorFormat( GL_RGBA ),
		mSize{ 0, 0 },
		mBytes( nullptr ),
		mDataLength( 0 ),
		mBitDepth( 0 ),
		mChannelsCount( 0 )
	{

		// Log
		std::string logMsg( "PNGImage#" );
		logMsg += mFile;
		logMsg += "::constructor";
		Log::printDebug( logMsg.c_str( ) );

	}

	/* PNGImage destructor */
	PNGImage::~PNGImage( )
	{

		// Log
		std::string logMsg( "PNGImage#" );
		logMsg += mFile;
		logMsg += "::destructor";
		Log::printDebug( logMsg.c_str( ) );

		// Release PNG bytes
		if ( mBytes != nullptr )
		{

			// Delete bytes-array
			delete[] mBytes;

			// Reset pointer-value
			mBytes = nullptr;

		}

	}

	// ===========================================================
	// Getter & Setter
	// ===========================================================

	/*
	 * Returns RAW PNG Image bytes, or null.
	 *
	 * @thread_safety - not thread-safe.
	 * @return - 'unsigned chars' array.
	*/
	const unsigned char *const PNGImage::getBytes( ) const noexcept
	{ return( mBytes ); }

	/*
	 * Returns data length in bytes.
	 *
	 * @thread_safety - not thread-safe.
	 * @return - data length in bytes.
	*/
	const unsigned int PNGImage::getLength( ) const noexcept
	{ return( mDataLength ); }

	// ===========================================================
	// Methods
	// ===========================================================

	/*
	 * Load PNG Image.
	 *
	 * @thread_safety - not thread-safe.
	 * @return - 'true' if OK.
	 * @throws - can throw exception (io-exception, access-exception, png-exception, etc).
	*/
	const bool PNGImage::Load( )
	{

		// Cancel
		if ( mBytes != nullptr )
			return( true );

		// Log
		std::string logMsg( "PNGImage#" );
		logMsg += mFile;
		logMsg += "::Load";
		Log::printDebug( logMsg.c_str( ) );

		// InputFile
		InputFile inputFile;

		// Load PNG-data
		if ( !PNGLoader::loadImage( this, &inputFile ) )
		{

			// Log
			logMsg = "PNGImage::Load - failed to load";
			Log::printWarning( logMsg.c_str( ) );

			// Return FALSE
			return( false );

		}

		// Return TRUE
		return( true );

	}

	/*
	 * Unload PNG Image.
	 *
	 * @thread_safety - not thread-safe.
	 * @throws - can throw exception (io-exception, access-exception, png-exception, etc).
	*/
	void PNGImage::Unload( )
	{

		// Log
		std::string logMsg( "PNGImage#" );
		logMsg += mFile;
		logMsg += "::Unload";
		Log::printDebug( logMsg.c_str( ) );

		// Release PNG bytes
		if ( mBytes != nullptr )
		{

			// Delete bytes-array
			delete[] mBytes;

			// Reset pointer-value
			mBytes = nullptr;

		}

	}

	// -------------------------------------------------------- \\

}