# // ------------------------------------------------------------------------------ \\
#
# This is CMake-File for 'OpenGL Sprite Batching Example' Project.
#
# About:
# "gl_sprite_batch" - sample project to demonstrate sprite batching using OpenGL 3+ API.
#
# License: see "LICENSE" file.
# API: C++ 11.
# Platforms: Any with C++ 11 support.
#
# // ------------------------------------------------------------------------------ \\

# =================================================================================
# CMake Meta-Data
# =================================================================================

# CMake-Version
cmake_minimum_required ( VERSION 3.8 FATAL_ERROR)

# =================================================================================
# PROJECT
# =================================================================================

# Project Name
set ( ROOT_PROJECT_NAME "gl_sprite_batch" )

# Project Version
set ( ROOT_PROJECT_VERSION 1.0.0 )

# Configure Project
project ( ${ROOT_PROJECT_NAME} VERSION ${ROOT_PROJECT_VERSION} LANGUAGES C CXX )

# Debug-Log for Compiler Configuration
set (CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_CURRENT_LIST_DIR}/CompilerOptions.cmake")

# =================================================================================
# CONFIG
# =================================================================================

# DETECT LINUX
if ( UNIX AND NOT DEFINED LINUX AND NOT APPLE )
		
	# LINUX ON
	set ( LINUX ON )
	
endif ( UNIX AND NOT DEFINED LINUX AND NOT APPLE )

# PLATFORM
if ( ANDROID ) # ANDROID

	# Set Directory Prefix
	set ( PLATFORM_DIR "android" )
	
elseif ( WIN32 ) # WINDOWS

	# Set Directory Prefix
	set ( PLATFORM_DIR "win32" )

elseif ( LINUX ) # LINUX
	
	# Set Directory Prefix
	set ( PLATFORM_DIR "linux" )

elseif ( APPLE ) # APPLE

	# Set Directory Prefix
	set ( PLATFORM_DIR "apple" )

else ( ANDROID ) # ?
	
	# ERROR
	message ( SEND_ERROR "${ROOT_PROJECT_NAME} - unknown platform ! Configuration required." )
	
	# Set Directory Prefix
	set ( PLATFORM_DIR "unix" )
	
endif ( ANDROID )

# Build-Type Sub-Dir
if ( CMAKE_BUILD_TYPE STREQUAL "Debug" )

	# Add Definition
	add_definitions ( -DDEBUG=1 )
	
	# Set Build-Type Dir
	set ( BUILD_TYPE_DIR "debug" )
	
else ( CMAKE_BUILD_TYPE STREQUAL "Debug" )

	# Set Build-Type Dir
	set ( BUILD_TYPE_DIR "release" )
	
endif ( CMAKE_BUILD_TYPE STREQUAL "Debug" )

# Compiler
if ( MSVC ) # MSVC
	# W3 - Display more warning
	# std=c++17 - C++ version
	set ( CMAKE_CXX_FLAGS "/W3 /std:c++17 /Zc:__cplusplus" )
elseif ( UNIX OR CMAKE_COMPILER_IS_GNUCXX ) # Clang || gcc (Linux, Mac OS or Win32 with MingW)

	# Flags
	set ( CMAKE_CXX_FLAGS "-Wall -std=c++17" )

	# Apple
	if ( APPLE ) # Clang / Mac OS only
		set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -mmacosx-version-min=10.7" )
	endif ( APPLE ) # Clang / Mac OS only
endif ( MSVC ) # MSVC

# =================================================================================
# CONSTANTS
# =================================================================================

# Set Sources Dir
set ( SOURCES_DIR "${CMAKE_SOURCE_DIR}/src/cpp" )

# Set Project Bin-Output Dir
set ( ROOT_PROJECT_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/bin/${BUILD_TYPE_DIR}/${PLATFORM_DIR}" )

# Sample-Project Multithreading
set ( ROOT_PROJECT_MULTITHREADING_ENABLED ON )
add_definitions ( -D_C0DE4UN_MULTITHREADING_ENABLED_ )

# Libs Dir
set ( ROOT_PROJECT_LIBS_DIR "${CMAKE_SOURCE_DIR}/libs/lib" )

# Include Dir
set (ROOT_PROJECT_LIBS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libs/include" )

# =================================================================================
# LIBRARIES
# =================================================================================

# =============== GLM ====================

# GLM Include Dir
set ( GLM_LIB_DIR "${ROOT_PROJECT_LIBS_INCLUDE_DIR}/common/glm" )

# Check if path is valid
if ( NOT EXISTS "${GLM_LIB_DIR}/CMakeLists.txt" )
	message ( FATAL_ERROR "${ROOT_PROJECT_NAME} - GLM Not Found at: ${GLM_LIB_DIR}" )
else ( NOT EXISTS "${GLM_LIB_DIR}/CMakeLists.txt" )
	message ( STATUS "${ROOT_PROJECT_NAME} - GLM Found at: ${GLM_LIB_DIR}" )
endif ( NOT EXISTS "${GLM_LIB_DIR}/CMakeLists.txt" )

# Include GLM-root dir (adds glm-headers to relative path)
include_directories( ${GLM_LIB_DIR} )

# INFO GLEW Imported
message ( STATUS "${ROOT_PROJECT_NAME} - GLM Included as Interface (headers-only) Library" )

# =============== OpenGL ====================

# Search for Win32 OpenGL Lib (OpenGL32.Lib)
if ( WIN32 ) # WINDOWS
	# Windows SDK OpenGL32
	find_library( opengl "OpenGL32.lib" )

	# 
elseif ( ANDROID ) # ANDROID
	message( FATAL_ERROR "${ROOT_PROJECT_NAME} - android opengl library search not implemented. Configuration required." )
elseif ( LINUX ) # LINUX
	message( FATAL_ERROR "${ROOT_PROJECT_NAME} - linux opengl library search not implemented. Configuration required." )
else ( WIN32 )
	message( FATAL_ERROR "${ROOT_PROJECT_NAME} - not supported platform-opengl. Configuration required." )
endif ( WIN32 )

# Check
if ( opengl )
	message( STATUS "${ROOT_PROJECT_NAME} - opengl - found at: ${opengl}" )
else ( opengl )
	message( FATAL_ERROR "${ROOT_PROJECT_NAME} - opengl - not found" )
endif ( opengl )

# =============== GLEW (OpenGL Wrapper Library) & GLFW ====================

# PC
if ( WIN32 OR LINUX )
	# Configure GLEW & GLFW
	if ( WIN32 ) # WINDOWS

		# GLEW Lib Location
		set( GLEW_LIB_PATH "${ROOT_PROJECT_LIBS_DIR}/glew/release/${PLATFORM_DIR}/x86_32/glew32s.lib" )

		# GLEW Include Dir
		set ( GLEW_INCLUDE_DIR "${ROOT_PROJECT_LIBS_INCLUDE_DIR}/common/GL" )

		# GLFW Lib Location
		set ( GLFW_LIB_PATH "${ROOT_PROJECT_LIBS_DIR}/glfw/release/${PLATFORM_DIR}/x86_32/glfw3.lib" )

		# GLEW Include Dir
		set ( GLFW_INCLUDE_DIR "${ROOT_PROJECT_LIBS_INCLUDE_DIR}/common/GLFW" )

	elseif ( LINUX ) # LINUX

		# ERROR
		message( FATAL_ERROR "${ROOT_PROJECT_NAME} - linux glew & glfw not implemented. Configuration required." )
	else ( WIN32 )
		# ERROR
		message( FATAL_ERROR "${ROOT_PROJECT_NAME} - unknown platform glew & glfw location. Configuration required." )
	endif ( WIN32 )

	# Check GLEW Lib Location
	if ( NOT EXISTS ${GLEW_LIB_PATH} )
		# ERROR
		message( FATAL_ERROR "${ROOT_PROJECT_NAME} - can't find GLEW at: ${GLEW_LIB_PATH}" )
	else ( NOT EXISTS ${GLEW_LIB_PATH} )
		# INFO
		message ( STATUS "${ROOT_PROJECT_NAME} - GLEW library found at ${GLEW_LIB_PATH}" )
	endif ( NOT EXISTS ${GLEW_LIB_PATH} )

	# Check GLFW Lib Location
	if ( NOT EXISTS ${GLFW_LIB_PATH} )
		# ERROR
		message( FATAL_ERROR "${ROOT_PROJECT_NAME} - can't find GLFW at: ${GLFW_LIB_PATH}" )
	else ( NOT EXISTS ${GLFW_LIB_PATH} )
		# INFO
		message ( STATUS "${ROOT_PROJECT_NAME} - GLFW library found at ${GLFW_LIB_PATH}" )
	endif ( NOT EXISTS ${GLFW_LIB_PATH} )

	# Check GLEW Includes
	if ( NOT DEFINED GLEW_INCLUDE_DIR OR NOT EXISTS "${GLEW_INCLUDE_DIR}/glew.h" )
		# ERROR
		message( FATAL_ERROR "${ROOT_PROJECT_NAME} - can't find GLEW include dir: ${GLEW_INCLUDE_DIR}" )
	endif ( NOT DEFINED GLEW_INCLUDE_DIR OR NOT EXISTS "${GLEW_INCLUDE_DIR}/glew.h" )

	# Check GLFW Includes
	if ( NOT DEFINED GLFW_INCLUDE_DIR OR NOT EXISTS "${GLFW_INCLUDE_DIR}/glfw3.h" )
		# ERROR
		message( FATAL_ERROR "${ROOT_PROJECT_NAME} - can't find GLFW include dir: ${GLFW_INCLUDE_DIR}" )
	endif ( NOT DEFINED GLFW_INCLUDE_DIR OR NOT EXISTS "${GLFW_INCLUDE_DIR}/glfw3.h" )

	# Add STATIC GLEW Library
	add_library( glew STATIC IMPORTED )

	# Set GLEW Library-Object Properties
	set_target_properties( glew PROPERTIES
	IMPORTED_LOCATION "${GLEW_LIB_PATH}" 
	INTERFACE_INCLUDE_DIRECTORIES "${GLEW_INCLUDE_DIR}" )

	# INFO
	message ( STATUS "${ROOT_PROJECT_NAME} - GLEW Imported as STATIC Library" )

	# Add STATIC GLFW Library
	add_library( glfw3 STATIC IMPORTED )

	# Set GLFW Library-Object Properties
	set_target_properties( glfw3 PROPERTIES
	IMPORTED_LOCATION "${GLFW_LIB_PATH}" 
	INTERFACE_INCLUDE_DIRECTORIES "${GLFW_INCLUDE_DIR}" )

	# INFO
	message ( STATUS "${ROOT_PROJECT_NAME} - GLFW Imported as STATIC Library" )

endif ( WIN32 OR LINUX )

# =============== PNG (libPNG + zlib) ====================

# Include CMake-code for libPNG & zlib
#include ( "cmake/libPNG.txt" )

# Platform-specific configs for libPNG & zlib
if ( WIN32 )
	# libPNG Location (*.lib) for Windows
	set ( PNG_LIB_LOCATION "${ROOT_PROJECT_LIBS_DIR}/libpng/release/win32/x86_32/libpng16.lib" )

	# Check if libPNG exists (libpng16.lib)
	if ( NOT EXISTS ${PNG_LIB_LOCATION} )
		# ERROR
		message ( FATAL_ERROR "${ROOT_PROJECT_NAME} - libPNG not found at: ${PNG_LIB_LOCATION}" )
	else ( NOT EXISTS ${PNG_LIB_LOCATION} )
		# INFO
		message ( STATUS "${ROOT_PROJECT_NAME} - libPNG found at ${PNG_LIB_LOCATION}" )
	endif ( NOT EXISTS ${PNG_LIB_LOCATION} )

	# libPNG Include Dir (png.h)
	set ( PNG_LIB_INCLUDE_DIR "${ROOT_PROJECT_LIBS_INCLUDE_DIR}/win32/libpng" )

	# Check libPNG includes path (png.h)
	if ( NOT EXISTS "${PNG_LIB_INCLUDE_DIR}/png.h" )
		# ERROR
		message ( FATAL_ERROR "${ROOT_PROJECT_NAME} - invalid path to the libPNG include dir." )
	else ( NOT EXISTS "${PNG_LIB_INCLUDE_DIR}/png.h" )
		# INFO
		message ( STATUS "${ROOT_PROJECT_NAME} - lbPNG include dir found at ${PNG_LIB_INCLUDE_DIR}" )
	endif ( NOT EXISTS "${PNG_LIB_INCLUDE_DIR}/png.h" )

	# zlib Location (*.lib) for Windows
	set ( ZLIB_LIB_LOCATION "${ROOT_PROJECT_LIBS_DIR}/zlib/release/win32/x86_32/zlib.lib" )

	# Check zlib location
	if ( NOT EXISTS ${ZLIB_LIB_LOCATION} )
		# ERROR
		message ( FATAL_ERROR "${ROOT_PROJECT_NAME} - zlib no found at ${ZLIB_LIB_LOCATION}" )
	else ( NOT EXISTS ${ZLIB_LIB_LOCATION} )
		# INFO
		message ( STATUS "${ROOT_PROJECT_NAME} - zlib found at ${ZLIB_LIB_LOCATION}" )
	endif ( NOT EXISTS ${ZLIB_LIB_LOCATION} )

	# zlib include dir
	set ( ZLIB_INCLUDE_DIR "${ROOT_PROJECT_LIBS_INCLUDE_DIR}/win32/zlib" )

	# Check zlib include dir path
	if ( NOT EXISTS ${ZLIB_INCLUDE_DIR} )
		# ERROR
		message ( FATAL_ERROR "${ROOT_PROJECT_NAME} - zlib include dir not found at ${ZLIB_INCLUDE_DIR}" )
	else ( NOT EXISTS ${ZLIB_INCLUDE_DIR} )
		# INFO
		message ( STATUS "${ROOT_PROJECT_NAME} - zlib include dir found at ${ZLIB_INCLUDE_DIR}" )
	endif ( NOT EXISTS ${ZLIB_INCLUDE_DIR} )

	# Add zlib library object
	add_library ( zlib STATIC IMPORTED )

	# Configure zlib Library Object
	set_target_properties ( zlib  PROPERTIES 
	IMPORTED_LOCATION ${ZLIB_LIB_LOCATION} 
	INTERFACE_INCLUDE_DIRECTORIES ${ZLIB_INCLUDE_DIR} )

	# Add libPNG library object
	add_library ( libPNG STATIC IMPORTED )
	
	# Configure libPNG Library Object
	set_target_properties ( libPNG  PROPERTIES 
	IMPORTED_LOCATION ${PNG_LIB_LOCATION} 
	INTERFACE_INCLUDE_DIRECTORIES ${PNG_LIB_INCLUDE_DIR} )

	# INFO: libPNG & zlib imported
	message ( STATUS "${ROOT_PROJECT_NAME} - libPNG & zlib imported as STATIC libraries" )

elseif ( LINUX )
	# libPNG Location (*.lib) for Linux
	message ( FATAL_ERROR "${ROOT_PROJECT_NAME} - can't import libPNG & zlib for linux, configuration required." )
elseif ( ANDROID )
	# libPNG Location (*.lib) for Android
	message ( FATAL_ERROR "${ROOT_PROJECT_NAME} - can't import libPNG & zlib for android, configuration required." )
else ( WIN32 )
	# ERROR
	message ( FATAL_ERROR "${ROOT_PROJECT_NAME} - libPNG & zlib can't be located for current platform (system), configuration required." )
endif ( WIN32 )

# =================================================================================
# HEADERS
# =================================================================================

# Sample-Project Headers
set ( ROOT_PROJECT_HEADERS
"${SOURCES_DIR}/cfg/platform.hpp"
"${SOURCES_DIR}/cfg/mutex.hpp"
"${SOURCES_DIR}/cfg/map.hpp"
"${SOURCES_DIR}/cfg/vector.hpp"
"${SOURCES_DIR}/cfg/opengl.hpp"
"${SOURCES_DIR}/cfg/glm.hpp"
"${SOURCES_DIR}/cfg/string.hpp"
"${SOURCES_DIR}/cfg/istream.hpp"
"${SOURCES_DIR}/components/Components.hpp"
"${SOURCES_DIR}/components/Position.hpp"
"${SOURCES_DIR}/components/Rotation.hpp"
"${SOURCES_DIR}/components/Scale.hpp"
"${SOURCES_DIR}/camera/GLCamera2D.hpp"
"${SOURCES_DIR}/assets/image/PNGImage.hpp"
"${SOURCES_DIR}/assets/image/PNGLoader.hpp"
"${SOURCES_DIR}/assets/texture/GLTexture2D.hpp"
"${SOURCES_DIR}/assets/shader/GLShader.hpp"
"${SOURCES_DIR}/assets/shader/GLShaderProgram.hpp"
"${SOURCES_DIR}/utils/log/Log.hpp"
"${SOURCES_DIR}/utils/color/ColorTypes.hpp"
"${SOURCES_DIR}/utils/io/InputFile.hpp"
"${SOURCES_DIR}/utils/io/Encoding.hpp"
"${SOURCES_DIR}/utils/io/StreamMode.hpp"
"${SOURCES_DIR}/utils/random/Random.hpp"
"${SOURCES_DIR}/objects/GameObject.hpp"
"${SOURCES_DIR}/objects/sprite/Sprite.hpp"
"${SOURCES_DIR}/physics/Body.hpp"
"${SOURCES_DIR}/renderer/batch/Drawable.hpp"
"${SOURCES_DIR}/renderer/batch/BatchInfo.hpp"
"${SOURCES_DIR}/renderer/batch/BatchRequest.hpp"
"${SOURCES_DIR}/renderer/GLRenderer.hpp" )

# =================================================================================
# SOURCES
# =================================================================================

# Sample-Project Sources
set ( ROOT_PROJECT_SOURCES
"${SOURCES_DIR}/camera/GLCamera2D.cpp"
"${SOURCES_DIR}/utils/log/Log.cpp"
"${SOURCES_DIR}/objects/GameObject.cpp"
"${SOURCES_DIR}/assets/image/PNGImage.cpp"
"${SOURCES_DIR}/assets/image/PNGLoader.cpp"
"${SOURCES_DIR}/assets/texture/GLTexture2D.cpp"
"${SOURCES_DIR}/assets/shader/GLShader.cpp"
"${SOURCES_DIR}/assets/shader/GLShaderProgram.cpp"
"${SOURCES_DIR}/utils/io/InputFile.cpp"
"${SOURCES_DIR}/utils/random/Random.cpp"
"${SOURCES_DIR}/objects/sprite/Sprite.cpp"
"${SOURCES_DIR}/renderer/GLRenderer.cpp"
"${SOURCES_DIR}/main.cpp" )

# =================================================================================
# EXECUTABLE RESOURCES
# =================================================================================

# PLATFORM
if (  WIN32 ) # WINDOWS
	set ( ROOT_PROJECT_RESOURCES "${CMAKE_SOURCE_DIR}/res/win32_resources.rc" )
else ( WIN32 )
	message ( FATAL_ERROR "${ROOT_PROJECT_NAME} - executable resources configuration required !" )
endif ( WIN32 ) # WINDOWS

# =================================================================================
# BUILD EXECUTABLE
# =================================================================================

# PLATFORM
if ( WIN32 ) # WINDOWS
	# Create Executable Object
	add_executable ( gl_sprite_batch ${ROOT_PROJECT_SOURCES} ${ROOT_PROJECT_HEADERS} ${ROOT_PROJECT_RESOURCES} )
	
	# Configure Executable Object
	set_target_properties ( gl_sprite_batch PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED TRUE
	CXX_EXTENSIONS FALSE
	OUTPUT_NAME "${ROOT_PROJECT_NAME}_v${ROOT_PROJECT_VERSION}"
	RUNTIME_OUTPUT_DIRECTORY ${ROOT_PROJECT_OUTPUT_DIR} )
	
	# 
	#set_property ( TARGET gl_sprite_batch PROPERTY CXX_STANDARD 17 )
	#set_property ( TARGET gl_sprite_batch PROPERTY CXX_STANDARD_REQUIRED ON )
	# CXX_STANDARD_REQUIRED

	# Remove Console Window for Release
	if ( CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo" )
		set_target_properties( gl_sprite PROPERTIES 
		LINK_FLAGS "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS" )
	endif ( CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo" )
	
	# Link
	target_link_libraries ( gl_sprite_batch ${opengl} glew glfw3 zlib libPNG )

	# Request features
	target_compile_features ( gl_sprite_batch PRIVATE cxx_std_17 )
else ( WIN32 )
	message ( FATAL_ERROR "${ROOT_PROJECT_NAME} - executable object configuration required !" )
endif ( WIN32 ) # WINDOWS