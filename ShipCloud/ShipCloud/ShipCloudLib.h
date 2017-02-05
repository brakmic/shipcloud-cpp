// Include this file in your apps.
#pragma once
#include <windows.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <memory>
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
#include "api/v1/types/address/address.h"
#include "api/v1/types/responses/address-response.h"
#include "ShipCloud.h"