#ifndef __SHIPCLOUD_H__
#define __SHIPCLOUD_H__

namespace api = shipcloud::api::v1;
namespace base = shipcloud::api::base;
namespace types = shipcloud::api::v1::types;
namespace responses = shipcloud::api::v1::types::responses;
// JSON for Modern C++
using modernJson = nlohmann::json;
// C++ REST SDK
using namespace web;
using namespace web::http;

// This class is exported from the ShipCloud.dll
class SHIPCLOUD_API ShipCloud {
public:
	ShipCloud();
	ShipCloud(base::AppConfig cfg);
	virtual ~ShipCloud();
	ShipCloud(const ShipCloud& other);
	ShipCloud(ShipCloud&& other);
	ShipCloud& operator=(const ShipCloud& other);
	ShipCloud& operator=(ShipCloud&& other);
	pplx::task<responses::AddressResponse> createAddress(const types::Address& address);
	pplx::task<std::vector<responses::AddressResponse>> readAllAddresses();
	const std::wstring ShipCloud::get_auth_data();
	const std::wstring composeApiCallUrl(const std::wstring callName);
	// static
	static const std::string address_to_string(const types::Address& address);
	static const responses::AddressResponse parse_address_response(const json::value& response);
	static const responses::AddressResponse parse_address_string(const std::string& response);
	static http_request createGetRequest(const std::wstring& endpoint, const base::ApiCall& call, 
											   const std::wstring& authData, const std::wstring& contentType);
	static http_request createPostRequest(const std::wstring& endpoint, const base::ApiCall& call, 
												const std::wstring& authData, const std::wstring& contentType, 
												const std::string& data);
private:
	base::AppConfig cfg;
};

#endif // __SHIPCLOUD_H__