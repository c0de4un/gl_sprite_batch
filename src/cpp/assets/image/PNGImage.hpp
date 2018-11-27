/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_png_image_hpp__
#define __c0de4un_png_image_hpp__

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