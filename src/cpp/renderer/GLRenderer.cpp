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

// Include BatchInfo
#ifndef __c0de4un_batch_info_hpp__
#include "batch/BatchInfo.hpp"
#endif // !__c0de4un_batch_info_hpp__

// Include BatchRequest
#ifndef __c0de4un_batch_request_hpp__
#include "batch/BatchRequest.hpp"
#endif // !__c0de4un_batch_request_hpp__

// Include GLCamera2D
#ifndef __c0de4un_gl_camera_2D_hpp__
#include "../camera/GLCamera2D.hpp"
#endif // !__c0de4un_gl_camera_2D_hpp__

// Include Log
#ifndef __c0de4un_log_hpp__
#include "../utils/log/Log.hpp"
#endif // !__c0de4un_log_hpp__

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
		//: mVerticesPosition
		//{
		//	-1.0f, -1.0f, 0.0f, 1.0f,
		//	1.0f, -1.0f, 0.0f, 1.0f,
		//	1.0f, 1.0f, 0.0f, 1.0f,
		//	-1.0f, 1.0f, 0.0f, 1.0f
		//},
		: mVerticesPosition
	{
		-1.0f, -1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 1.0f
	},
		mVerticesIndices{ 0, 1, 2, 2, 3, 0 },
		mVerticesTextureCoords{ 0.0f, 0.0f, 1.0f, 1.0f }
	{

		// Log
		Log::printDebug( "GLRenderer::constructor" );

	}

	/* GLRenderer destructor */
	GLRenderer::~GLRenderer( )
	{

		// Log
		Log::printDebug( "GLRenderer::destructor" );

	}

	// ===========================================================
	// Methods
	// ===========================================================

	/*
	 * Load Sprite-Batch.
	 * Allocates buffers, writes mesh data (vertices positions, indices),
	 * creates & fills OpenGL Buffers (VBOs, VAO).
	 *
	 * @thread_safety - render-thread only.
	 * @param batchInfo - Sprite-Batching component.
	 * @return - 'true' if OK, false if failed.
	 * @throws - can throw exception.
	*/
	const bool GLRenderer::loadSpriteBatch( const bool hasTexture, BatchInfo & batchInfo )
	{

#ifdef DEBUG // DEBUG
		assert( batchInfo.vaoID_ < 1 ); // Already Loaded
#endif // DEBUG

		// Create OpenGL Vertex Buffer Objects (VBOs)
		glGenBuffers( 3, &batchInfo.vboIDs_[0] );

		// Check VBOs
		if ( batchInfo.vboIDs_[2] < 1 )
			throw std::exception( "GLRenderer::loadSpriteBatch - failed to create VBO !" );

		// Create OpenGL Vertex Array Object
		glGenVertexArrays( 1, &batchInfo.vaoID_ );

		// Check VAO
		if ( batchInfo.vaoID_ < 1 )
		{

			// Delete VBOs
			glDeleteBuffers( 3, &batchInfo.vboIDs_[0] );

			// Throw exception
			throw std::exception( "GLRenderer::loadSpriteBatch - failed to create VAO !" );

		}

		// Bind Vertex Position Buffer Object
		glBindBuffer( GL_ARRAY_BUFFER, batchInfo.vboIDs_[BatchInfo::POSITION_VBO] );

		// Upload Vertices Positions data to the OpenGL (GPU) Buffer Object
		glBufferData( GL_ARRAY_BUFFER, VERTICES_COUNT * VERTEX_POSITION_LENGTH, &mVerticesPosition[0], GL_STATIC_DRAW ); // STATIC_DRAW, because buffer data not changed.

		// Unbind Vertex Position Buffer Objects
		glBindBuffer( GL_ARRAY_BUFFER, 0 );

		// Bind Indices Buffer Object ('IBO')
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, batchInfo.vboIDs_[BatchInfo::INDICES_VBO] );

		// Upload 
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, INDICES_COUNT * sizeof( GLushort ), &mVerticesIndices[0], GL_STATIC_DRAW ); // STATIC_DRAW, because buffer data not changed.

		// Unbind Indices Buffer Object
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

		// 2D-Texture
		if ( hasTexture )
		{

			// Bind 2D-Texture Coordinates Buffer Object
			glBindBuffer( GL_ARRAY_BUFFER, batchInfo.vboIDs_[BatchInfo::TEXTURE_COORDS_VBO] );

			// Upload Vertices 2D-Texture Coordinates data to the OpenGL Buffer Object (GPU)
			glBufferData( GL_ARRAY_BUFFER, ( TEXTURE_COORDS_COUNT * TEXTURE_COORD_SIZE ) * sizeof( GLfloat ), &mVerticesTextureCoords[0], GL_STATIC_DRAW ); // STATIC_DRAW, because buffer data not changed.

			// Unbind 2D-Texture Coordinates Buffer Object
			glBindBuffer( GL_ARRAY_BUFFER, 0 );

		}

		// Bind VAO (OpenGL Vertex Array Object)
		glBindVertexArray( batchInfo.vaoID_ );

		// 2D-Texture
		if ( hasTexture )
		{

			// Bind 2D-Texture Coordinates Buffer Object
			glBindBuffer( GL_ARRAY_BUFFER, batchInfo.vboIDs_[BatchInfo::TEXTURE_COORDS_VBO] );

			// Enable 'Texture Coordinates' Attribute Array
			glEnableVertexAttribArray( batchInfo.texCoordsAttrIndex_ );

			// Point OpenGL to 'Vertex Texture Coordinates' data
			glVertexAttribPointer( batchInfo.texCoordsAttrIndex_, TEXTURE_COORD_SIZE, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0 ); // (GLvoid*) 0 - to use binded Buffer Object.

		}

		// Bind Vertex Position Buffer Object
		glBindBuffer( GL_ARRAY_BUFFER, batchInfo.vboIDs_[BatchInfo::POSITION_VBO] );

		// Enable "Vertex Position" Attribute Array
		glEnableVertexAttribArray( batchInfo.vertexPosAttrIndex_ );

		// Point OpenGL to 'Vertex Position' data
		glVertexAttribPointer( batchInfo.vertexPosAttrIndex_, VERTEX_POSITION_SIZE, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0 ); // (GLvoid*) 0 - to use binded Buffer Object.

		// Bind Indices Buffer Object ('IBO')
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, batchInfo.vboIDs_[BatchInfo::INDICES_VBO] );

		// Unbind VAO
		glBindVertexArray( 0 );

		// Return OK
		return( true );

	}

	/*
	 * Unloads Sprite-Batch.
	 * Deletes OpenGL Buffer Objects (VBOs, VAO).
	 *
	 * @thread_safety - render-thread only.
	 * @param batchInfo - Sprite-Batching component.
	 * @throws - can throw exception.
	*/
	void GLRenderer::unloadSpriteBatch( BatchInfo & batchInfo )
	{

#ifdef DEBUG // DEBUG
		assert( batchInfo.vboIDs_[0] > 0 ); // Not Loaded ?
#endif // DEBUG

		// Delete VAO
		glDeleteVertexArrays( 1, &batchInfo.vaoID_ );

		// Delete VBOs
		glDeleteBuffers( 3, &batchInfo.vboIDs_[0] );

	}

	/*
	 * Compile & upload Shader Program with Vertex Shader & Fragment Shader
	 * to the OpenGL memory-space (GPU).
	 *
	 * @thread_safety - render-thread only.
	 * @param shaderObject_ - Shader Object ID.
	 * @param sourceCode_ - RAW GLSL source-code.
	 * @param shaderType_ - shader type.
	 * @return - 'TRUE' if OK, false if failed.
	 * @throws - can throw exception.
	*/
	const bool GLRenderer::loadShader( GLuint & shaderObject_, const char *const sourceCode_, const GLenum & shaderType_ )
	{

#ifdef DEBUG // DEBUG
		assert( shaderObject_ == 0 );
		assert( sourceCode_ != nullptr );
#endif // DEBUG

		// Log-message
		std::string logMsg( "GLRenderer::loadShader - source-code=" );
		logMsg += sourceCode_;

		// Print to the Log
		Log::printDebug( logMsg.c_str( ) );

		// Create Shader Object
		shaderObject_ = glCreateShader( shaderType_ );

		// Check that Shader Object Pointer/ID is Valid
		if ( shaderObject_ < 1 )
			throw std::exception( "GLRenderer::loadShader - failed to create Shader Object !" );

		// Upload Shader Source Code
		glShaderSource( shaderObject_, 1, &sourceCode_, nullptr );

		// Compile Shader Source-Code
		glCompileShader( shaderObject_ );

		// Shader Compile Status
		GLint compileStatus( 0 );

		// Get Shader Compile Status
		glGetShaderiv( shaderObject_, GL_COMPILE_STATUS, &compileStatus );

		// Handle Failed Compilation
		if ( !compileStatus )
		{
			// Log Info Length
			GLint infoLen;

			// Get Log Info Length
			glGetShaderiv( shaderObject_, GL_INFO_LOG_LENGTH, &infoLen );

			// Handle Log Info
			if ( infoLen > 1 )
			{
				// Allocate C-string (char[])
				char* infoString( static_cast<char*>( std::malloc( sizeof( char ) * infoLen ) ) );

				// Get Shader-Object Compilation Status Info
				glGetShaderInfoLog( shaderObject_, infoLen, nullptr, infoString );

				// Error Details
				std::string errMsg( "GLRenderer::loadShader - compilation failed, details: \n" );

				// Append Log-Info
				errMsg += infoString;

				// Free/Release Info
				std::free( infoString );

				// Delete Shader Object
				glDeleteShader( shaderObject_ );

				// Reset Shader Object Pointer/ID
				shaderObject_ = 0;

				// Print Error to Log
				Log::printError( errMsg.c_str( ) );

				// Throw Exception
				throw std::exception( errMsg.c_str( ), 5 );
			}
			else // Throw Exception
			{
				// Delete Shader Object
				glDeleteShader( shaderObject_ );

				// Reset Shader Object Pointer/ID
				shaderObject_ = 0;

				// Print Error to Log
				Log::printError( "GLRenderer::loadShader - compilation failed, no log-info !" );

				// Throw Exception
				throw std::exception( "GLRenderer::loadShader - compilation failed, no log-info !", 4 );
			}

			// Return FALSE
			return( false );
		}

		// Return 'TRUE'
		return( true );

	}

	/*
	 * Create & link Shader Program with Shaders.
	 *
	 * @thread_safety - render-thread only.
	 * @param shaderProgram_ - Shader Program Object ID.
	 * @param vertexShader_ - Vertex Shader Object ID.
	 * @param fragmentShader_ - Fragment Shader Object ID.
	 * @return - 'true' if OK.
	 * @throws - can throw exception.
	*/
	const bool GLRenderer::loadProgram( GLuint & shaderProgram_, const GLuint & vertexShader_, const GLuint & fragmentShader_ )
	{

#ifdef DEBUG // DEBUG
		assert( vertexShader_ > 0 );
		assert( fragmentShader_ > 0 );
#endif // DEBUG

		// Create OpenGL Shader Program Object
		shaderProgram_ = glCreateProgram( );

		// Check Shader Program Object ID
		if ( shaderProgram_ < 1 )
			throw std::exception( "GLRenderer::loadProgram - failed to create Shader Program Object !" );

		// Attach Vertex Shader
		glAttachShader( shaderProgram_, vertexShader_ );

		// Attach Fragment Shader
		glAttachShader( shaderProgram_, fragmentShader_ );

		// Link Shader Program
		glLinkProgram( shaderProgram_ );

		// Link Status
		GLint linkStatus;

		// Get Link Status
		glGetProgramiv( shaderProgram_, GL_LINK_STATUS, &linkStatus );

		// Handle failed link
		if ( !linkStatus )
		{
			// Log Info length
			GLint infoLen( 0 );

			// Get Log Info Length
			glGetProgramiv( shaderProgram_, GL_INFO_LOG_LENGTH, &infoLen );

			// Handle Log Info
			if ( infoLen > 0 )
			{
				// Allocate c-string for Log Info
				char *logStr( static_cast<char*>( malloc( sizeof( char ) * infoLen ) ) );

				// Get Log-Info in c-string
				glGetProgramInfoLog( shaderProgram_, infoLen, nullptr, logStr );

				// Error Message
				std::string errMsg( "GLRenderer::loadProgram - Failed to link shader program object, \nDetails: " );

				// Append Details
				errMsg += logStr;

				// Free Log-Info c-string
				free( logStr );

				// Print Error
				Log::printError ( errMsg.c_str( ) );

				// Throw ShaderException
				throw std::exception( errMsg.c_str( ) );
			}

			// Return FALSE
			return( false );

		}

		// Return TRUE
		return( true );

	}

	/*
	 * Add Drawable-Object to the Sprite Batching.
	 *
	 * @thread_safety - render-thread only.
	 * @param batchRequest - Batch Request.
	 * @throws - can throw exception.
	*/
	void GLRenderer::addDrawable( BatchRequest & batchRequest )
	{

#ifdef DEBUG // DEBUG
		assert( batchRequest.drawable_ != nullptr );
		assert( batchRequest.shaderProgram_ > 0 );
#endif // DEBUG

		// Search BatchInfo
		programs_map_t::const_iterator programsIterator_ = mPrograms.find( batchRequest.shaderProgram_ );
		
		// Get BatchInfo
		BatchInfo & batchInfo_ = mPrograms[batchRequest.shaderProgram_];

		// SpriteBatch empty
		if ( batchInfo_.vboIDs_[0] < 1 && batchInfo_.vertexPosAttrIndex_ < 0 )
		{

			// Set SpriteBatch 'Vertex Position' attribute index
			batchInfo_.vertexPosAttrIndex_ = batchRequest.vertexPosAttrIndex_;

			// Set SpriteBatch 'Vertex Color' attribute index
			batchInfo_.colorAttrIndex_ = batchRequest.colorAttrIndex_;

			// Set SpriteBatch 'Texture Coordinates' attribute index
			batchInfo_.texCoordsAttrIndex_ = batchRequest.texCoordsAttrIndex_;

			// MVP (Model View Projection) Matrix uniform location/index
			batchInfo_.mvpMatUniformLoc_ = batchRequest.mvpMatUniformIndex_;

			// Load Sprite-Batch
			loadSpriteBatch( batchRequest.textureObject_ > 0, batchInfo_ );

		}

		// Add Drawable
		batchInfo_.textureObjects_[batchRequest.textureObject_].push_back( batchRequest.drawable_ );

	}

	/*
	 * Remove Drawable-Object form the Sprite Batching.
	 *
	 * @thread_safety - render-thread only.
	 * @param pDrawable - Drawable-Object.
	 * @param shaderProgram_ - OpenGL Shader Program ID (Pointer).
	 * @param texture2D_ - OpenGL 2D Texture Object ID/Pointer.
	 * @throws - can throw exception.
	*/
	void GLRenderer::removeDrawable( const Drawable *const pDrawable, const GLuint & shaderProgram_, const GLuint & texture2D_ )
	{

#ifdef DEBUG // DEBUG
		assert( pDrawable != nullptr );
		assert( shaderProgram_ > 0 );
#endif // DEBUG

		// Search BatchInfo
		programs_map_t::iterator batchInfoPos_ = mPrograms.find( shaderProgram_ );

		// Cancel if not found
		if ( batchInfoPos_ == mPrograms.end( ) )
			return;

		// Get BatchInfo
		BatchInfo & batchInfo_ = batchInfoPos_->second;

		// Search Drawable-Objects vector
		std::map<const GLuint, std::vector<Drawable*>>::iterator drawableObjectsPos_ = batchInfo_.textureObjects_.find( texture2D_ );

		// Cancel if not found
		if ( drawableObjectsPos_ == batchInfo_.textureObjects_.end( ) )
		{

			// Check BatchInfo size
			if ( batchInfo_.textureObjects_.empty( ) )
				unloadSpriteBatch( batchInfo_ ); // mPrograms.erase( shaderProgram_ );

			// Return
			return;

		}

		// Get 'reference' to the Drawable-Objects vector
		std::vector<Drawable*> & drawableObjects_ = drawableObjectsPos_->second;

		// Search Drawable
		std::vector<Drawable*>::iterator drawableIterator_ = std::find( drawableObjects_.begin( ), drawableObjects_.end( ), pDrawable );

		// Cancel if not found
		if ( drawableIterator_ == drawableObjects_.end( ) )
		{

			// Remove Drawable-Objects vector
			if ( batchInfo_.textureObjects_.size( ) > 1 )
				batchInfo_.textureObjects_.erase( texture2D_ );
			else // Remove BatchInfo
				unloadSpriteBatch( batchInfo_ );  // mPrograms.erase( shaderProgram_ );

			// Return
			return;

		}

		// Swap & pop
		if ( drawableObjects_.size( ) > 2 )
		{
			// Swap
			std::swap( *drawableIterator_, drawableObjects_.back( ) );
			//std::iter_swap( drawableIterator_, drawableObjects_.back( ) );

			// Pop
			drawableObjects_.pop_back( );
		}
		else
			drawableObjects_.erase( drawableIterator_ );

		// Remove Drawable-Objects vector
		if ( drawableObjects_.empty( ) )
		{

			// Remove Drawable-Objects vector
			if ( batchInfo_.textureObjects_.size( ) > 1 )
				batchInfo_.textureObjects_.erase( texture2D_ );
			else // Remove BatchInfo
				unloadSpriteBatch( batchInfo_ );  // mPrograms.erase( shaderProgram_ );

		}

	}

	/*
	 * Draws given Drawable-Object (Sprite).
	 *
	 * @thread_safety - render-thread only.
	 * @param pDrawable - Drawable-Component.
	 * @param mvpMatUniformIndex_ - Model View Projection Matrix location/index.
	 * @param pCamera2D - 2D Camera.
	*/
	void GLRenderer::drawSprite( Drawable *const pDrawable, const GLuint & mvpMatUniformIndex_, const GLCamera2D *const pCamera2D )
	{

#ifdef DEBUG // DEBUG
		assert( pDrawable != nullptr );
		assert( mvpMatUniformIndex_ >= 0 );
#endif // DEBUG

		// Update Matrices
		if ( !pCamera2D->updated_ || pDrawable->stateChanged_ )
		{

			// Model Identity-Matrix
			glm::mat4 modelMat_( 1.0f );

			// Translate Model Matrix
			glm::translate( modelMat_, pDrawable->position_->vec3_ );

			// Rotate Model Matrix
			modelMat_ = glm::rotate( modelMat_, glm::radians( pDrawable->rotation_->vec3_.x ), glm::vec3( 1.0f, 0.0f, 0.0f ) ); // X
			modelMat_ = glm::rotate( modelMat_, glm::radians( pDrawable->rotation_->vec3_.y ), glm::vec3( 0.0f, 1.0f, 0.0f ) ); // Y
			modelMat_ = glm::rotate( modelMat_, glm::radians( pDrawable->rotation_->vec3_.z ), glm::vec3( 0.0f, 0.0f, 1.0f ) ); // Z

			// Scale Model Matrix
			modelMat_ = glm::scale( modelMat_, pDrawable->scale_->vec3_ );

			// Model-View-Projection Matrix (MVP)
			pDrawable->mvpMat_ = pCamera2D->projectionMat_ * pCamera2D->viewMat_ * modelMat_;

			// Set Drawable state changed flag
			pDrawable->stateChanged_ = false;

		}

		// Upload Mesh (Sprite) Model-View-Projection Matrix to the Vertex Shader
		glUniformMatrix4fv( mvpMatUniformIndex_, 1, GL_FALSE, glm::value_ptr( pDrawable->mvpMat_ ) );

		//// Model Matrix
		//glm::mat4 modelMat_( 1.0f );
		//modelMat_ = glm::translate( modelMat_, glm::vec3( 0.0f, 0.0f, 0.0f ) );
		//modelMat_ = glm::rotate( modelMat_, glm::radians(0.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) );
		//modelMat_ = glm::rotate( modelMat_, glm::radians( 0.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
		//modelMat_ = glm::rotate( modelMat_, glm::radians( 0.0f ), glm::vec3( 0.0f, 0.0f, 1.0f ) );
		//modelMat_ = glm::scale( modelMat_, glm::vec3( 100.0f, 100.0f, 0.0f ) );
		//
		//// View Matrix
		//glm::vec3 camPos_( 0.0f, 0.0f, 0.0f );
		//glm::vec3 camUp_( 0.0f, 1.0f, 0.0f );
		//glm::vec3 camFront_( 0.0f, 0.0f, -1.0f );
		//glm::mat4 viewMat_( 1.0f );
		//viewMat_ = glm::lookAt( camPos_, camPos_ + camFront_, camUp_ );
		//
		//// Projection Matrix
		//const float nearZ = 0.01f;
		//const float farZ = 2.0f;
		//glm::mat4 projectionMat_( 1.0f );
		//projectionMat_ = glm::ortho( 0.0f, 1280.0f, 0.0f, 720.0f, 0.f, 1.f );

		//// View & Projection
		//const glm::mat4 mvpMat_ = projectionMat_ * viewMat_ * modelMat_;

		//// Upload Mesh (Sprite) Model-View-Projection Matrix to the Vertex Shader
		//glUniformMatrix4fv( mvpMatUniformIndex_, 1, GL_FALSE, glm::value_ptr( mvpMat_ ) );

		// Draw Elements (render with indices)
		glDrawElements( GL_TRIANGLES, INDICES_COUNT, GL_UNSIGNED_SHORT, (const void *) 0 );

	}

	/*
	 * Draw (render).
	 *
	 * @thread_safety - render-thread only.
	 * @param pCamera - 2D-Camera.
	 * @throws - can throw exception.
	*/
	void GLRenderer::Draw( GLCamera2D *const pCamera2D )
	{

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

			// Get BatchInfo
			BatchInfo & batchInfo_ = programsIterator_->second;

			// Bind VAO
			glBindVertexArray( batchInfo_.vaoID_ );

			// Get Textures map iterator
			std::map<const GLuint, std::vector<Drawable*>>::iterator texturesIterator_ = batchInfo_.textureObjects_.begin( );

			// Get Textures map end-iterator
			std::map<const GLuint, std::vector<Drawable*>>::const_iterator texturesEnd_ = batchInfo_.textureObjects_.cend( );

			// Lock the Camera thread-lock
			pCamera2D->lock_.lock( );

			// Update Camera View & Projection Matrices
			if ( !pCamera2D->updated_ )
			{

				// Calculate View Matrix
				const glm::vec3 cameraUp_( 0.0f, 1.0f, 0.0f );
				const glm::vec3 cameraFront_( 0.0f, 0.0f, -1.0f );
				pCamera2D->viewMat_ = glm::lookAt( pCamera2D->position_, pCamera2D->position_ + cameraFront_, cameraUp_ );

				// Calculate Projection Matrix
				pCamera2D->projectionMat_ = glm::ortho( pCamera2D->frustum_[0], pCamera2D->frustum_[1], pCamera2D->frustum_[2], pCamera2D->frustum_[3], pCamera2D->frustum_[4], pCamera2D->frustum_[5] );

			}

			// Textures
			while ( texturesIterator_ != texturesEnd_ )
			{

				// Bind Texture
				if ( texturesIterator_->first > 0 )
					glBindTexture( GL_TEXTURE_2D, texturesIterator_->first );

				// Get Drawable-Objects vector
				std::vector<Drawable*> & drawableObjects_ = texturesIterator_->second;

				// Drawable-Object
				for ( Drawable *const drawable_ : drawableObjects_ )
				{

					// Lock Drawable
					drawable_->lock_->lock( );

					// Transfer (Upload) current Color-values (same color for all vertices)
					if ( batchInfo_.colorAttrIndex_ >= 0 )
						glVertexAttrib4fv( batchInfo_.colorAttrIndex_, drawable_->color_ );

					// Draw Sprite
					drawSprite( drawable_, batchInfo_.mvpMatUniformLoc_, pCamera2D );

					// Unlock Drawable
					drawable_->lock_->unlock( );

				}

				// Unbind Texture
				if ( texturesIterator_->first > 0 )
					glBindTexture( GL_TEXTURE_2D, 0 );

				// Next
				texturesIterator_++;

			}

			// Reset Camera Matrices Update flag
			pCamera2D->updated_ = true;

			// Unlock the Camera thread-lock
			pCamera2D->lock_.unlock( );

			// Unbind (bind the default) VAO
			glBindVertexArray( 0 );

			// Reset current OpenGL Shader Program
			glUseProgram( 0 );

			// Next
			programsIterator_++;

		}

		// Disable Blending
		glDisable( GL_BLEND );

	}

	// -------------------------------------------------------- \\

}