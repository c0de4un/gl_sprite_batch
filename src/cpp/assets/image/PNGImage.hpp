/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_png_image_hpp__
#define __c0de4un_png_image_hpp__

// Include string
#ifndef __c0de4un_string_hpp__
#include "../../cfg/string.hpp"
#endif // !__c0de4un_string_hpp__

// Include OpenGL
#include "../../cfg/opengl.hpp"

// PNGImage declared
#define __c0de4un_png_image_decl__

namespace c0de4un
{

	/*
	 * PNGImage - png image asset.
	 * 
	 * @version 1.0.0
	*/
	class PNGImage final
	{

	public:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Constants
		// ===========================================================

		/* Path to the PNG Image */
		const std::string mFile;

		// ===========================================================
		// Fields
		// ===========================================================

		/* Width & Height */
		unsigned int mSize[2];

		/* Image RAW Data (Bytes) */
		unsigned char * mBytes;

		/* Data Length in bytes */
		unsigned int mDataLength;

		/* Color Format */
		GLenum mColorFormat;

		/* Bit depth */
		unsigned char mBitDepth;

		/* Channels count */
		unsigned char mChannelsCount;

		// ===========================================================
		// Constructor & destructor
		// ===========================================================

		/*
		 * PNGImage constructor
		 *
		 * @param pFile - path to the PNG-image.
		*/
		explicit PNGImage( const std::string & pFile );

		/* PNGImage destructor */
		~PNGImage( );

		// ===========================================================
		// Getter & Setter
		// ===========================================================

		/*
		 * Returns RAW PNG Image bytes, or null.
		 *
		 * @thread_safety - not thread-safe.
		 * @return - 'unsigned chars' array.
		*/
		const unsigned char *const getBytes( ) const noexcept;

		/*
		 * Returns data length in bytes.
		 *
		 * @thread_safety - not thread-safe.
		 * @return - data length in bytes.
		*/
		const unsigned int getLength( ) const noexcept;

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
		const bool Load( );

		/*
		 * Unload PNG Image.
		 * 
		 * @thread_safety - not thread-safe.
		 * @throws - can throw exception (io-exception, access-exception, png-exception, etc).
		*/
		void Unload( );

		// -------------------------------------------------------- \\

	private:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Deleted
		// ===========================================================

		/* @deleted PNGImage const copy constructor */
		explicit PNGImage( const PNGImage & ) noexcept = delete;

		/* @deleted PNGImage const copy assignment operator */
		PNGImage & operator=( const PNGImage & ) noexcept = delete;

		/* @deleted PNGImage move constructor */
		explicit PNGImage( PNGImage && ) noexcept = delete;

		/* @deleted PNGImage move assignment operator */
		PNGImage && operator=( PNGImage && ) noexcept = delete;

		// -------------------------------------------------------- \\

	};

}

#endif // !__c0de4un_png_image_hpp__