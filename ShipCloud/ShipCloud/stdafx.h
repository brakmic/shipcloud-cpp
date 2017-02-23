// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifndef __STDAFX_H__
#define __STDAFX_H__

#include "targetver.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

	// The following ifdef block is the standard way of creating macros which make exporting 
	// from a DLL simpler. All files within this DLL are compiled with the SHIPCLOUD_EXPORTS
	// symbol defined on the command line. This symbol should not be defined on any project
	// that uses this DLL. This way any other project whose source files include this file see 
	// SHIPCLOUD_API functions as being imported from a DLL, whereas this DLL sees symbols
	// defined with this macro as being exported.
	#ifdef SHIPCLOUD_EXPORTS
	#define SHIPCLOUD_API __declspec(dllexport)
	#else
	#define SHIPCLOUD_API __declspec(dllimport)
	#endif

	#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
	// Windows Header Files:
	#include <windows.h>
	#include <tchar.h>

#endif // _WINDOWS

#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <memory>

// TODO: reference additional headers your program requires here
// JSON for Modern C : https://nlohmann.github.io/json/
#include "vendors/json.hpp"
// Casablanca C++ SDK APIs
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/http_listener.h>              // HTTP server
#include <cpprest/json.h>                       // JSON library
#include <cpprest/uri.h>                        // URI library
#include <cpprest/ws_client.h>                  // WebSocket client
#include <cpprest/containerstream.h>            // Async streams backed by STL containers
#include <cpprest/interopstream.h>              // Bridges for integrating Async streams with STL and WinRT streams
#include <cpprest/rawptrstream.h>               // Async streams backed by raw pointer to memory
#include <cpprest/producerconsumerstream.h>     // Async streams for producer consumer scenarios
// ShipCloud APIs
#include "api/helpers/string-helper.h"
#include "api/v1/types/address/address.h"
#include "api/v1/types/responses/address-response.h"
#include "api/base/api-call.h"
#include "api/base/api-config.h"
#include "api/base/app-config.h"
#include "ShipCloud.h"


#endif // __STDAFX_H__