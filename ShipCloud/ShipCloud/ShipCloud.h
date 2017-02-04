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

#include "stdafx.h"
namespace api = shipcloud::api::v1;
namespace types = shipcloud::api::v1::types;
namespace responses = shipcloud::api::v1::types::responses;

// This class is exported from the ShipCloud.dll
class SHIPCLOUD_API ShipCloud {
public:
	ShipCloud(std::wstring apiKey);
	~ShipCloud();
	ShipCloud(const ShipCloud& other) = delete;
	ShipCloud(ShipCloud&& other) = delete;
	ShipCloud& operator=(const ShipCloud& other) = delete;
	pplx::task<responses::AddressResponse> ShipCloud::createAddress(types::Address& address);
	static std::string address_to_string(types::Address& address);
	static types::responses::AddressResponse parse_address_response(web::json::value& response);
private:
	std::wstring get_auth_data();
	std::wstring apiKey;
	std::wstring apiUrl;
};
