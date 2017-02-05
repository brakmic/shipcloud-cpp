// ShipCloud.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"

// Casablanca C++ SDK namespaces
using namespace concurrency;
using namespace concurrency::streams;
using namespace utility;				
using namespace web;					
using namespace web::http;				
using namespace web::http::client;		
using namespace concurrency::streams;	
using namespace web::http::experimental::listener;          
using namespace web::experimental::web_sockets::client;   
using namespace web::json;                               
												
namespace types = shipcloud::api::v1::types;
namespace responses = shipcloud::api::v1::types::responses;
// JSON for Modern C++
using modernJson = nlohmann::json;

//a simple Tracer
#ifdef ENABLE_TRACE
bool _trace(TCHAR *format, ...)
{
	TCHAR buffer[2048];

	va_list argptr;
	va_start(argptr, format);
	wvsprintf(buffer, format, argptr);
	va_end(argptr);

	OutputDebugString(buffer);

	return true;
}
#else 
bool _trace(TCHAR *format, ...)
{
	// do nothing
	return true;
}
#endif

ShipCloud::ShipCloud(std::string apiKey)
	: apiKey(std::move(apiKey)),
	  apiUrl(U("https://api.shipcloud.io"))
{}

ShipCloud::~ShipCloud()
{
}
/*
* Send async POST request to create a new Address
*/
pplx::task<responses::AddressResponse> ShipCloud::createAddress(types::Address& address) {
	//_trace(L"%S %S", L"Connecting web server ", this->apiUrl);
	
	http_request req(methods::POST);
	req.headers().add(U("Authorization"), this->get_auth_data());
	req.set_request_uri(U("/v1/addresses"));
	req.headers().set_content_type(U("application/json"));
	req.set_body(this->address_to_string(address));

	http_client client(uri(this->apiUrl));
	
	return client.request(req).then([=](http_response response) -> pplx::task<json::value>
	{
		if (response.status_code() == status_codes::OK)
		{
		    return response.extract_json();
		}
		return pplx::task_from_result(json::value(U("error")));
	}).then([=](json::value json) -> responses::AddressResponse {
		return ShipCloud::parse_address_response(json);
	});;
}
/*
* Send async GET request to query all known Addresses
*/
pplx::task<std::vector<responses::AddressResponse>> ShipCloud::readAllAddresses() {
	http_request req(methods::GET);
	req.headers().add(U("Authorization"), this->get_auth_data());
	req.set_request_uri(U("/v1/addresses"));
	req.headers().set_content_type(U("application/json"));
	
	http_client client(uri(this->apiUrl));

	return client.request(req).then([=](http_response response) -> pplx::task<json::value>
	{
		if (response.status_code() == status_codes::OK)
		{
			return response.extract_json();
		}
		return pplx::task_from_result(json::value(U("error")));
	}).then([=](json::value json) -> std::vector<responses::AddressResponse> {
		std::stringstream ss;
		auto s = json.serialize();
		ss << utility::conversions::to_utf8string(json.serialize());
		auto p = modernJson::parse(ss);
		std::vector<responses::AddressResponse> vec;
		for (auto& v : p.front()) {
			auto str = v.dump();
			auto a = ShipCloud::parse_address_string(str);
			vec.push_back(std::move(a));
		}
		return vec;
	});;
}

/*
* Convert Address into a JSON-ified string
*/
std::string ShipCloud::address_to_string(types::Address& address)
{
	modernJson j;
	j["id"] = address.id;
	j["care_of"] = address.care_of;
	j["company"] = address.company;
	j["first_name"] = address.first_name;
	j["last_name"] = address.last_name;
	j["street"] = address.street;
	j["street_no"] = address.street_no;
	j["zip_code"] = address.zip_code;
	j["city"] = address.city;
	j["state"] = address.state;
	j["country"] = address.country;
	j["phone"] = address.phone;
	return j.dump();
}

types::responses::AddressResponse ShipCloud::parse_address_string(std::string response) {
	std::stringstream ss;
	ss << response;
	auto val = json::value::parse(ss);
	return ShipCloud::parse_address_response(val);
}
/*
* Convert JSON response into AddressResponse
*/
types::responses::AddressResponse ShipCloud::parse_address_response(json::value& response)
{
	responses::AddressResponse r;
	std::stringstream ss;
	ss << utility::conversions::to_utf8string(response.serialize());
	auto p = modernJson::parse(ss);
	r.id = p.value("id", "");
	r.care_of = !p["care_of"].is_null() ? p.value("care_of", "") : "";
	r.company = p.value("company", "");
	r.first_name = p.value("first_name", "");
	r.last_name = p.value("last_name", "");
	r.phone = !p["phone"].is_null() ? p.value("phone", "") : "";
	r.street = p.value("street", "");
	r.street_no = p.value("street_no", "");
	r.city = p.value("city", "");
	r.state = !p["state"].is_null() ? p.value("state", "") : "";
	r.zip_code = p.value("zip_code", "");
	return r;
}

/*
* Convert auth data into base64 string
*/
std::wstring ShipCloud::get_auth_data()
{
	auto strKey = conversions::to_utf8string(this->apiKey);
	const std::vector<uint8_t> data(strKey.begin(), strKey.end());
	auto base64Key = conversions::to_base64(data);

	std::wstringstream ss;
	ss << L"Basic " << conversions::to_utf16string(base64Key);
	return ss.str();
}

