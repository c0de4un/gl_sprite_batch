/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_opengl_hpp__
#define __c0de4un_opengl_hpp__

// Include platform
#ifndef __c0de4un_platform_hpp__
#include "platform.hpp"
#endif // !__c0de4un_platform_hpp__

// PC
#if defined( WIN32 ) || defined( LINUX )

// Include GLEW
#ifndef _glew_h_
#define GLEW_STATIC
#include <glew.h>
#endif

// Include GLFW
#ifndef _glfw3_h_
#include <glfw3.h>
#endif

#else // !PC
#error "opengl.hpp - configuration required"
#endif // PC

#endif // !__c0de4un_opengl_hpp__