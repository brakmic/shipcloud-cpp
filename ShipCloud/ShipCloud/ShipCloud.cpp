#include "stdafx.h"

// Casablanca C++ SDK name spaces
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


ShipCloud::ShipCloud()
{
}

ShipCloud::ShipCloud(base::AppConfig& cfg)
	: cfg(cfg)
{}

ShipCloud::~ShipCloud()
{
}
/*
* Send asynchronous POST request to create a new Address
*/
pplx::task<responses::AddressResponse> ShipCloud::createAddress(types::Address& address) {
	std::wstring endpoint(L"addresses");
	std::wstring mime(L"application/json");
	auto req = this->createPostRequest(endpoint, this->cfg.apiCfg.getApiCall(conversions::to_utf8string("addresses")),
									   this->get_auth_data(), mime,
									   this->address_to_string(address));

	uri _uri(conversions::to_string_t(std::move(this->cfg.getServerUrl())));
	http_client client(_uri);
	
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
* Send asynchronous GET request to query all known Addresses
*/
pplx::task<std::vector<responses::AddressResponse>> ShipCloud::readAllAddresses() {
	std::wstring endpoint(L"addresses");
	std::wstring mime(L"application/json");
	auto req = this->createGetRequest(endpoint, this->cfg.apiCfg.getApiCall(conversions::to_utf8string("addresses")), 
									  this->get_auth_data(), mime);
	
	uri _uri(conversions::to_string_t(this->cfg.getServerUrl()));
	http_client client(_uri);

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
* Convert Address into a JSON
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

types::responses::AddressResponse ShipCloud::parse_address_string(std::string& response) {
	std::stringstream ss;
	ss << response;
	auto val = json::value::parse(ss);
	return ShipCloud::parse_address_response(val);
}
std::wstring ShipCloud::composeApiCallUrl(std::wstring callName)
{	
	auto version = this->cfg.apiCfg.getApiCalls()[conversions::to_utf8string(callName)].version;
	std::wstringstream ss;
	ss << "/" << version << "/" << callName;
	return ss.str();
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
	for (auto& d : p) {
		if(d.is_null()) 
			d = std::string("");
	}
	r.id = p.value("id", std::string());
	r.care_of = p.value("care_of", std::string());
	r.company = p.value("company", std::string());
	r.first_name = p.value("first_name", std::string());
	r.last_name = p.value("last_name", std::string());
	r.phone = p.value("phone", std::string());
	r.street = p.value("street", std::string());
	r.street_no = p.value("street_no", std::string());
	r.city = p.value("city", std::string());
	r.state = p.value("state", std::string());
	r.zip_code = p.value("zip_code", std::string());
	return r;
}

/*
* Convert authorization data into base64 string
*/
std::wstring ShipCloud::get_auth_data()
{
	auto strKey = conversions::to_utf8string(this->cfg.apiCfg.getApiKey());
	const std::vector<uint8_t> data(strKey.begin(), strKey.end());
	auto base64Key = conversions::to_base64(data);

	std::wstringstream ss;
	ss << L"Basic " << conversions::to_string_t(base64Key);
	return ss.str();
}

http_request ShipCloud::createGetRequest(std::wstring& endpoint, base::ApiCall& call, 
										 std::wstring& authData, std::wstring& contentType) {
	std::wstringstream ss;
	ss << U("/") << call.version << U("/") << endpoint;

	http_request req(methods::GET);
	req.headers().add(U("Authorization"), authData);
	req.set_request_uri(ss.str());
	req.headers().set_content_type(contentType);
	return req;
}

http_request ShipCloud::createPostRequest(std::wstring& endpoint, base::ApiCall& call, 
										  std::wstring& authData, std::wstring& contentType, 
										  std::string& data) {
	std::wstringstream ss;
	ss << U("/") << call.version << U("/") << endpoint;

	http_request req(methods::POST);
	req.headers().add(U("Authorization"), authData);
	req.set_request_uri(ss.str());
	req.headers().set_content_type(contentType);
	req.set_body(data);

	return req;
}

