/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_color_types_hpp__
#define __c0de4un_color_types_hpp__

// ColorTypes declared
#define __c0de4un_color_types_decl__

namespace c0de4un
{

	/*
	 * ColorTypes - color types.
	*/
	class ColorTypes final
	{

	public:

		// -------------------------------------------------------- \\

		// ===========================================================
		// Constants
		// ===========================================================

		/* RGBA 8 */
		static constexpr unsigned char RGBA = 0;

		/* RGB 8 */
		static constexpr unsigned char RGB = 1;

		/* GREY */
		static constexpr unsigned char LUMINANCE = 5;

		/* GREY ALPHA */
		static constexpr unsigned char LUMINANCE_ALPHA = 6;

		// -------------------------------------------------------- \\

	};

}

#endif // !__c0de4un_color_types_hpp__