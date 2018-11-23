/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

// HEADER
#ifndef __c0de4un_gl_renderer_hpp__
#include "GLRenderer.hpp"
#endif // !__c0de4un_gl_renderer_hpp__

namespace c0de4un
{

	// -------------------------------------------------------- \\


	// ===========================================================
	// Constructor & destructor
	// ===========================================================

	/*
	 * GLRenderer constructor.
	 *
	 * @throws - std::bad_alloc.
	*/
	GLRenderer::GLRenderer( )
		: mPrograms( ),
		mMutex_( ),
		mLock( mMutex_, std::defer_lock )
	{
	}

	/* GLRenderer destructor */
	GLRenderer::~GLRenderer( )
	{
	}

	// ===========================================================
	// Methods
	// ===========================================================

	/*
	 * Draws given Drawable-Object (Sprite).
	 *
	 * @thread_safety - render-thread only.
	 * @param pDrawable - Drawable-Component.
	*/
	void GLRenderer::drawSprite( drawable_ptr_t pDrawable )
	{

	}

	/*
	 * Draw (render).
	*/
	void GLRenderer::Draw( )
	{// TODO GLRenderer::Draw

		// Lock
		mLock.lock( );

		// Get Shader Programs map iterator
		programs_map_t::iterator programsIterator_ = mPrograms.begin( );

		// Get Shader Programs map end-iterator
		const programs_map_t::iterator programsEnd_ = mPrograms.end( );

		// Enable Blending
		glEnable( GL_BLEND );

		// Shader Programs
		while ( programsIterator_ != programsEnd_ )
		{

			// Use OpenGL Shader Program
			glUseProgram( programsIterator_->first );

			// Get Texture Objects IDs map
			textures_map_t & texturesMap_ = programsIterator_->second;

			// Get Textures map iterator
			textures_map_t::iterator texturesIterator_ = texturesMap_.begin( );

			// Get Textures map end-iterator
			const textures_map_t::iterator texturesEnd_ = texturesMap_.end( );

			// Textures
			while ( texturesIterator_ != texturesEnd_ )
			{

				// Bind Texture
				glBindTexture( GL_TEXTURE_2D, texturesIterator_->first );

				// Get Drawable-Objects vector
				drawables_vector_t & drawableObjects_ = texturesIterator_->second;

				// Drawable-Object
				for ( drawable_ptr_t drawable_ : drawableObjects_ )
				{

					// Draw Sprite
					drawSprite( drawable_ );

				}

				// Unbind Texture
				glBindTexture( GL_TEXTURE_2D, 0 );

				// Next
				texturesIterator_++;

			}

			// Reset current OpenGL Shader Program
			glUseProgram( 0 );

			// Next
			programsIterator_++;

		}

		// Disable Blending
		glDisable( GL_BLEND );

		// Unlock
		mLock.unlock( );

	}

	// -------------------------------------------------------- \\

}