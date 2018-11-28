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
	 * @param colorType_ - Color-Type, @see ColorTypes.hpp.
	*/
	PNGImage::PNGImage( const std::string & pFile, const unsigned char colorType_ )
		: mFile( pFile ),
		mColorType( colorType_ )
	{
	}

	/* PNGImage destructor */
	PNGImage::~PNGImage( )
	{

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
	}

	/*
	 * Unload PNG Image.
	 *
	 * @thread_safety - not thread-safe.
	 * @throws - can throw exception (io-exception, access-exception, png-exception, etc).
	*/
	void PNGImage::Unload( )
	{
	}

	// -------------------------------------------------------- \\

}