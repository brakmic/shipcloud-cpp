#ifndef __SHIPCLOUD_H__
#define __SHIPCLOUD_H__

namespace api = shipcloud::api::v1;
namespace base = shipcloud::api::base;
namespace types = shipcloud::api::v1::types;
namespace responses = shipcloud::api::v1::types::responses;
// JSON for Modern C++
using modernJson = nlohmann::json;

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
	pplx::task<responses::AddressResponse> createAddress(types::Address& address);
	pplx::task<std::vector<responses::AddressResponse>> readAllAddresses();
	std::wstring ShipCloud::get_auth_data();
	std::wstring composeApiCallUrl(std::wstring callName);
	// static
	static std::string address_to_string(types::Address& address);
	static types::responses::AddressResponse parse_address_response(web::json::value& response);
	static types::responses::AddressResponse parse_address_string(std::string& response);
	static web::http::http_request createGetRequest(std::wstring& endpoint, base::ApiCall& call, 
													std::wstring& authData, std::wstring& contentType);
	static web::http::http_request createPostRequest(std::wstring& endpoint, base::ApiCall& call, 
												     std::wstring& authData, std::wstring& contentType, std::string& data);
private:
	base::AppConfig cfg;
};

#endif // __SHIPCLOUD_H__