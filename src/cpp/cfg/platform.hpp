/*
 * Copyright © 2018 Denis Zyamaev. Email: (code4un@yandex.ru)
 * License: see "LICENSE" file
 * Author: Denis Zyamaev (code4un@yandex.ru)
 * API: C++ 11
*/

#ifndef __c0de4un_platform_hpp__
#define __c0de4un_platform_hpp__

// Windows
#if !defined( __c0de4un_platform_detected__ ) && ( defined( WIN32 ) || defined( _WIN32 ) || defined(  __WIN32 ) || defined( __WIN32__ ) )
#define __c0de4un_platform_detected__
#ifndef WIN32
#define WIN32 1
#endif // !WIN32
#endif // WIN32

// Android
#if !defined( __c0de4un_platform_detected__ ) && ( defined( __android__ ) || defined( _android_ ) || defined(  android ) || defined( ANDROID ) || defined( __android ) )
#define __c0de4un_platform_detected__
#ifndef ANDROID
#define ANDROID 1
#endif // !ANDROID
#endif // ANDROID

// Linux
#if !defined( __c0de4un_platform_detected__ ) && ( defined( __linux__ ) || defined( __linux ) || defined(  linux ) || defined( _linux ) || defined( LINUX ) )
#define __c0de4un_platform_detected__
#ifndef LINUX
#define LINUX 1
#endif // !LINUX
#endif // Linux

#ifndef __c0de4un_platform_detected__
#error "platform.hpp - unknown platform ! Configuration required."
#endif // !FX_ENGINE_CONFIG_PLATFORM_DETECTED

// Undef temp.
#undef __c0de4un_platform_detected__

#endif // !__c0de4un_platform_hpp__