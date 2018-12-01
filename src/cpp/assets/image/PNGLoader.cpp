/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

// HEADER
#ifndef __c0de4un_png_loader_hpp__
#include "PNGLoader.hpp"
#endif // !__c0de4un_png_loader_hpp__

#include <iostream> // I/O streams

// Include InputFile
#ifndef __c0de4un_input_file_hpp__
#include "../../utils/io/InputFile.hpp"
#endif // !__c0de4un_input_file_hpp__

// Include PNGImage
#ifndef __c0de4un_png_image_hpp__
#include "PNGImage.hpp"
#endif // !__c0de4un_png_image_hpp__

// Include Log
#ifndef __c0de4un_log_hpp__
#include "../../utils/log/Log.hpp"
#endif // !__c0de4un_log_hpp__

namespace c0de4un
{

	// -------------------------------------------------------- \\

	// ===========================================================
	// Methods
	// ===========================================================

	/*
	 * Callback for libPNG reading method.
	 *
	 * (!) It replaces built-in I/O, so no need to call png_init_io.
	 *
	 * (!) Reading depends on platform (Android uses compressed streams
	 * for resources and assets, reading from external sources may be slow).
	 *
	 * (!) If reading failed, stream must be closed.
	 *
	 * @thread_safety called only from png-thread.
	 * @param pStruct - pointer to png structure. Contains
	 * custom object as param/argument.
	 * @param pData - actual bytes buffer. contains binary image data.
	 * @param pSize - amount of data (symbols/chars) to read.
	 * @throws exceptions related to reading the data from stream.
	*/
	void PNGLoader::pngCallback_onRead( png_structp pStruct, png_bytep pData, png_size_t pSize )
	{

		// InputFile
		InputFile *const inputFile_ = static_cast<InputFile*>( png_get_io_ptr( pStruct ) );

		// Read bytes
		inputFile_->readBytes_A( (char*) pData, pSize );

	}

	/*
	 * Callback for libPNG errors.
	 *
	 * (!) Replaces built-in/default error reporting method/function.
	 *
	 * (!) Exception-object can be retrieved (png_voidp error_ptr = png_get_error_ptr(png_ptr)).
	 *
	 * @thread_safety obviously, called from png-thread.
	 * @param png_ptr - png structure.
	 * @param error_msg - error message.
	*/
	void PNGLoader::pngCallback_onError( png_structp png_ptr, png_const_charp error_msg )
	{

		// Log Message
		std::string logMsg( "PNGLoader::pngCallback_onError - CRITICAL_ERROR: " );

		// Append message
		logMsg += error_msg;

		// Print to the Log
		Log::printError( logMsg.c_str( ) );

	}

	/*
	 * Callback for libPNG warnings.
	 *
	 * (!) Replaces built-int/default warnings reporting method/function.
	 *
	 * @thread_safety obviously, called from png-thread.
	 * @param png_ptr - png structure.
	 * @param warning_msg - warning message.
	*/
	void PNGLoader::pngCallback_onWarning( png_structp png_ptr, png_const_charp warning_msg )
	{

		// Log Message
		std::string logMsg( "PNGLoader::pngCallback_onWarning - WARNING: " );

		// Append message
		logMsg += warning_msg;

		// Print to the Log
		Log::printWarning( logMsg.c_str( ) );

	}

	/*
	 * Load PNG-image.
	 *
	 * @thread_safety - not thread-safe.
	 * @param pngImage_ - PNGImage to store loaded data.
	 * @param inputFile_ - input stream.
	 * @return - 'true' if OK.
	 * @throws - can throw exceptions (png-exception, io-exception, etc).
	*/
	const bool PNGLoader::loadImage( PNGImage *const pngImage_, InputFile *const inputFile_ )
	{

		// Open Input Stream
		if ( !inputFile_->openStream_A( pngImage_->mFile, StreamMode::READ_BYTES, 0 ) )
		{

			// Log
			std::string errMsg( "PNGLoader::loadImage - failed to open #" );
			errMsg += pngImage_->mFile;
			Log::printWarning( errMsg.c_str( ) );

			// Cancel
			return( false );

		}

		// Open File
		//std::FILE * filePtr = std::fopen( pngImage_->mFile.c_str( ), "rb" );

		// Cancel if file not opened
		//if ( filePtr == nullptr )
		//{
		//	// Print Error
		//	Log::printError( "PNGLoader::loadImage - failed to open file !" );

		//	// Return FALSE
		//	return( false );
		//}

		// Create PNG Structure
		png_structp pngStruct = png_create_read_struct( PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr );

		// Set Z-LIB Compression Buffer Size to 16 KB (16 * 1024 = 16384). Default is 8192 (8 KB)
		png_set_compression_buffer_size( pngStruct, 16384 );

		// Set CRC & ADLER32 Actions (How to handle them) to PNG_CRC_QUIET_USE (Ignore and try to use broken data)
		png_set_crc_action( pngStruct, PNG_CRC_QUIET_USE, PNG_CRC_QUIET_USE );

		// Cancel if failed to create structure
		if ( !pngStruct )
		{
			// Print Error
			Log::printError( "PNGLoader::loadImage - failed to create png structure !" );

			//// Close File
			//if ( filePtr != nullptr )
			//{
			//	// Close File
			//	fclose( filePtr );

			//	// Delete instance
			//	delete filePtr;

			//	// Reset Pointer
			//	filePtr = nullptr;
			//}

			// Return FALSE
			return( false );
		}

		// PNG Info
		png_infop pngInfo = png_create_info_struct( pngStruct );

		// Cancel if failed to create PNG Info
		if ( !pngInfo )
		{
			// Print Error
			Log::printError( "PNGLoader::loadImage - failed to create png info !" );

			// Destroy PNG Read Structure
			if ( pngStruct != nullptr )
				png_destroy_read_struct( &pngStruct, nullptr, nullptr );

			//// Close File
			//if ( filePtr != nullptr )
			//{
			//	// Close File
			//	fclose( filePtr );

			//	// Delete instance
			//	delete filePtr;

			//	// Reset Pointer
			//	filePtr = nullptr;
			//}

			// Return FALSE
			return( false );
		}

		// Set PNG Jump
		if ( setjmp( png_jmpbuf( pngStruct ) ) )
		{// Failed to set PNG JMP
			// Print Error
			Log::printError( "PNGLoader::loadImage - failed to set png jmp buffer !" );

			// Destroy PNG Read Structure
			if ( pngStruct != nullptr )
				png_destroy_read_struct( &pngStruct, nullptr, nullptr );

			//// Close File
			//if ( filePtr != nullptr )
			//{
			//	// Close File
			//	fclose( filePtr );

			//	// Delete instance
			//	delete filePtr;

			//	// Reset Pointer
			//	filePtr = nullptr;
			//}

			// Return FALSE
			return( false );
		}

		// Initialize PNG IO
		//png_init_io( pngStruct, filePtr );

		// Set Read function
		png_set_read_fn( pngStruct, (png_voidp) inputFile_, pngCallback_onRead );

		// Read PNG Info
		png_read_info( pngStruct, pngInfo );

		// Width
		const unsigned int mTextureWidth = png_get_image_width( pngStruct, pngInfo );

		// Print Debug
		std::cout << "PNGLoader::loadImage - Width = " << mTextureWidth << std::endl;

		// Height
		const unsigned int mTextureHeight = png_get_image_height( pngStruct, pngInfo );

		// Print Debug
		std::cout << "PNGLoader::loadImage - Height = " << mTextureHeight << std::endl;

		// Color Type
		const png_byte colorType = png_get_color_type( pngStruct, pngInfo );

		// Get Color Bit Depth
		const png_byte bitDepth = png_get_bit_depth( pngStruct, pngInfo );

		// Transparency Flag
		bool transparency( false );

		// Get Transparency Value
		if ( png_get_valid( pngStruct, pngInfo, PNG_INFO_tRNS ) )
		{
			// Convert Transparency to Alpha
			png_set_tRNS_to_alpha( pngStruct );

			// Set Transparency Flag
			transparency = true;
		}

		// Convert (expand) depth if its less then 8 bit
		if ( bitDepth < 8 )
			png_set_packing( pngStruct );
		else if ( bitDepth == 16 )// Convert to 16 bit to 8 bit format
			png_set_strip_16( pngStruct );

		// OpenGL Color-Format
		GLenum glFormat( GL_RGB );

		// Get PNG Color Type
		png_byte pngColorType = png_get_color_type( pngStruct, pngInfo );

		// Color Type
		switch ( pngColorType )
		{
		case PNG_COLOR_TYPE_PALETTE:
			// Convert Palette to RGB
			png_set_palette_to_rgb( pngStruct );

			// Set OpenGL Color Format
			glFormat = transparency ? GL_RGBA : GL_RGB;

			// Print Debug
			if ( transparency )
				std::cout << "PNGLoader::loadImage - Color Type is PNG_COLOR_TYPE_PALETTE, GL format is RGBA. Transparency is on" << std::endl;
			else
				std::cout << "PNGLoader::loadImage - Color Type is PNG_COLOR_TYPE_PALETTE, GL format is RGB. Transparency is off" << std::endl;

			break;
		case PNG_COLOR_TYPE_RGB:

			// Set OpenGL Color Format
			glFormat = transparency ? GL_RGBA : GL_RGB;

			// Print Debug
			if ( transparency )
				std::cout << "PNGLoader::loadImage - Color Type is PNG_COLOR_TYPE_RGB, GL format is RGBA. Transparency is on" << std::endl;
			else
				std::cout << "PNGLoader::loadImage - Color Type is PNG_COLOR_TYPE_RGB, GL format is RGB. Transparency is off" << std::endl;

			break;
		case PNG_COLOR_TYPE_RGBA:

			// Set OpenGL Color Format
			glFormat = GL_RGBA;

			// Print Debug
			std::cout << "PNGLoader::loadImage - Color Type is PNG_COLOR_TYPE_RGBA, GL format is RGBA. Transparency is on" << std::endl;

			break;
		case PNG_COLOR_TYPE_GRAY:

			// Convert Grey to 8 bit
			png_set_expand_gray_1_2_4_to_8( pngStruct );

			// Set OpenGL Color Format
			glFormat = transparency ? GL_LUMINANCE_ALPHA : GL_LUMINANCE;

			// Print Debug
			if ( transparency )
				std::cout << "PNGLoader::loadImage - Color Type is PNG_COLOR_TYPE_GRAY, GL format is GL_LUMINANCE_ALPHA. Transparency is on" << std::endl;
			else
				std::cout << "PNGLoader::loadImage - Color Type is PNG_COLOR_TYPE_GRAY, GL format is GL_LUMINANCE. Transparency is off" << std::endl;

			break;
		case PNG_COLOR_TYPE_GA:

			// Convert Grey to 8 bit
			png_set_expand_gray_1_2_4_to_8( pngStruct );

			// Set OpenGL Color Format
			glFormat = GL_LUMINANCE_ALPHA;

			// Print Debug
			if ( transparency )
				std::cout << "PNGLoader::loadImage - Color Type is PNG_COLOR_TYPE_GRAY, GL format is GL_LUMINANCE_ALPHA. Transparency is on" << std::endl;

			break;
		}

		// Apply PNG Configs
		png_read_update_info( pngStruct, pngInfo );

		// Get Row Size in bytes
		png_int_32 rowSize = png_get_rowbytes( pngStruct, pngInfo );

		// By Default, OpenGL glTexImage2d requires rows to be 4-byte aligned. It can be changed with glPixelStorei with argument GL_UNPACK_ALIGNMENT
		rowSize += 3 - ( ( rowSize - 1 ) % 4 );

		// Check if Row Size is Valid
		if ( rowSize < 1 )
		{
			// Print Error
			std::cout << "PNGLoader::loadImage - Failed to retrieve PNG row size !" << std::endl;

			// Destroy PNG Read Structure
			if ( pngStruct != nullptr )
				png_destroy_read_struct( &pngStruct, nullptr, nullptr );

			//// Close File
			//if ( filePtr != nullptr )
			//{
			//	// Close File
			//	fclose( filePtr );

			//	// Delete instance
			//	delete filePtr;

			//	// Reset Pointer
			//	filePtr = nullptr;
			//}

			// Return FALSE
			return( false );
		}

		// Allocate Image Data Buffer for OpenGL
		png_byte *imageData = new png_byte[rowSize * mTextureHeight];

		// Check if Image Data is Valid
		if ( imageData == nullptr )
		{
			// Print Error
			std::cout << "PNGLoader::loadImage - Failed to allocate image buffer !" << std::endl;

			// Destroy PNG Read Structure
			if ( pngStruct != nullptr )
				png_destroy_read_struct( &pngStruct, nullptr, nullptr );

			//// Close File
			//if ( filePtr != nullptr )
			//{
			//	// Close File
			//	fclose( filePtr );

			//	// Delete instance
			//	delete filePtr;

			//	// Reset Pointer
			//	filePtr = nullptr;
			//}

			// Return FALSE
			return( false );
		}

		/*
		 * Pointers to each row of image buffer.
		 * Row order is inverted because differs
		 * in coordinate system (OpenGL & PNG)
		*/
		png_bytep *rowPtrs = new png_bytep[mTextureHeight];

		// Check if Row Pointer is Valid
		if ( rowPtrs == nullptr )
		{
			// Print Error
			std::cout << "PNGLoader::loadImage - Failed to allocate row pointers !" << std::endl;

			// Release Image Data
			if ( imageData != nullptr )
			{
				// Delete
				delete[] imageData;

				// Reset Pointer
				imageData = nullptr;
			}

			// Destroy PNG Read Structure
			if ( pngStruct != nullptr )
				png_destroy_read_struct( &pngStruct, nullptr, nullptr );

			//// Close File
			//if ( filePtr != nullptr )
			//{
			//	// Close File
			//	fclose( filePtr );

			//	// Delete instance
			//	delete filePtr;

			//	// Reset Pointer
			//	filePtr = nullptr;
			//}

			// Return FALSE
			return( false );
		}

		// Set Pointers to Each Row of Image Data in Inverted Order
		for ( unsigned int y = 0; y < mTextureHeight; y++ )
		{
			// Set Pointer to Row (Inverted Order)
			rowPtrs[mTextureHeight - y - 1] = imageData + y * rowSize;
		}

		// Read Image Data from PNG File
		png_read_image( pngStruct, rowPtrs );

		// Set Image Size
		pngImage_->mSize[0] = mTextureWidth;
		pngImage_->mSize[1] = mTextureHeight;

		// Set Image Color-Format
		pngImage_->mColorFormat = glFormat;

		//
		pngImage_->mBitDepth = bitDepth;
		pngImage_->mChannelsCount = 4;

		// Set Image Data
		pngImage_->mBytes = imageData;

		// Close File
		//fclose( filePtr );

		// Reset Pointer
		//filePtr = nullptr;

		// Release PNG resources (structure, info etc)
		png_destroy_read_struct( &pngStruct, &pngInfo, nullptr );

		// Release Raw Pointers
		delete[] rowPtrs;

		// Reset Pointer
		rowPtrs = nullptr;

		// Return TRUE
		return( true );

	}

	// -------------------------------------------------------- \\

}