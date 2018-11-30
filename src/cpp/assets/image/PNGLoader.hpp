/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_png_loader_hpp__
#define __c0de4un_png_loader_hpp__

// Include png
#include <png.h>

// Forward-declaration of PNGImage
#ifndef __c0de4un_png_image_decl__
#define __c0de4un_png_image_decl__
namespace c0de4un { class PNGImage; }
#endif // !__c0de4un_png_image_decl__

// Forward-declaration of InputFile
#ifndef __c0de4un_input_file_decl__
#define __c0de4un_input_file_decl__
namespace c0de4un { class InputFile; }
#endif // !__c0de4un_input_file_decl__

// PNGLoader declared
#define __c0de4un_png_loader_decl__

namespace c0de4un
{

	/*
	 * PNGLoader - utility to make easier PNG-image loading using libPNG.
	 *
	 * @version 1.0.0
	*/
	class PNGLoader final
	{

	public:

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
		static void pngCallback_onRead( png_structp pStruct, png_bytep pData, png_size_t pSize );

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
		static void pngCallback_onError( png_structp png_ptr, png_const_charp error_msg );

		/*
		 * Callback for libPNG warnings.
		 *
		 * (!) Replaces built-int/default warnings reporting method/function.
		 *
		 * @thread_safety obviously, called from png-thread.
		 * @param png_ptr - png structure.
		 * @param warning_msg - warning message.
		*/
		static void pngCallback_onWarning( png_structp png_ptr, png_const_charp warning_msg );

		/*
		 * Load PNG-image.
		 *
		 * @thread_safety - not thread-safe.
		 * @param pngImage_ - PNGImage to store loaded data.
		 * @param inputFile_ - input stream.
		 * @return - 'true' if OK.
		 * @throws - can throw exceptions (png-exception, io-exception, etc).
		*/
		static const bool loadImage( PNGImage *const pngImage_, InputFile *const inputFile_ );

		// -------------------------------------------------------- \\

	};

}

#endif // !__c0de4un_png_loader_hpp__