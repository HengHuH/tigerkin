#pragma once

/* configuration check. */
#if defined(DEBUG)
#	if defined(_FINAL) || defined(_INHOUSE)
#		error Duplicate configuration!
#	endif /*defined(_FINAL) || defined(_INHOUSE)*/
#endif /*defined(DEBUG)*/

#if defined(_INHOUSE)
#   if defined(DEBUG) || defined(_FINAL)
#		error Duplicate configuration!
#   endif /*defined(DEBUG) || defined(_FINAL)*/
#endif

#if defined(_FINAL)
#	if defined(DEBUG) || defined(_INHOUSE)
#		error Duplicate configuration!
#	endif /*defined(DEBUG) || defined(_INHOUSE)*/
#endif /*defined(_FINAL)*/


// compiler
#if defined(_MSC_VER)

#define	DLLEXPORT									__declspec(dllexport)
#define	DLLIMPORT									__declspec(dllimport)

#endif

#if TIGER_INONE
#   define __import_if_dynamic
#   define __export_if_dynamic
#else
#   define __import_if_dynamic DLLIMPORT
#   define __export_if_dynamic DLLEXPORT
#endif /*TIGER_INONE*/

#if defined(TIGER_RUNTIME_SOURCE)
#	define TIGER_API								__export_if_dynamic
#else
#	define TIGER_API								__import_if_dynamic
#endif /*defined(TIGER_RUNTIME_SOURCE)*/

#ifndef TIGER_API
#define TIGER_API
#endif