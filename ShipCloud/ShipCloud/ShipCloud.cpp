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
// ShipCloud API												
namespace types = shipcloud::api::v1::types;
namespace responses = shipcloud::api::v1::types::responses;
namespace helpers = shipcloud::api::helpers;
// JSON for Modern C++
using modernJson = nlohmann::json;


ShipCloud::ShipCloud()
{
}

ShipCloud::ShipCloud(base::AppConfig cfg)
	: cfg(std::move(cfg))
{}

ShipCloud::~ShipCloud()
{
}

ShipCloud::ShipCloud(const ShipCloud& other) {
	if (&other != this) {
		this->cfg = other.cfg;
	}
}

ShipCloud::ShipCloud(ShipCloud&& other) {
	if (&other != this) {
		this->cfg = std::move(other.cfg);
	}
}

ShipCloud& ShipCloud::operator=(const ShipCloud& other) {
	if (&other != this) {
		this->cfg = other.cfg;
	}
	return *this;
}

ShipCloud& ShipCloud::operator=(ShipCloud&& other) {
	if (&other != this) {
		this->cfg = std::move(other.cfg);
	}
	return *this;
}
/*
* Send asynchronous POST request to create a new Address
*/
pplx::task<responses::AddressResponse> ShipCloud::createAddress(const types::Address& address) {
	auto req = this->createPostRequest(U("addresses"),
									   this->cfg.apiConfig().apiCall(U("addresses")),
									   this->getAuthData(), U("application/json"),
									   this->addressToString(address));

	uri _uri(std::move(this->cfg.serverUrl()));
	http_client client(_uri);
	
	return client.request(req).then([=](http_response response) -> pplx::task<json::value>
	{
		if (response.status_code() == status_codes::OK)
		{
		    return response.extract_json();
		}
		return pplx::task_from_result(json::value(U("error")));
	}).then([](json::value json) -> responses::AddressResponse {
		return ShipCloud::parse_address_response(json);
	});;
}

/*
* Send asynchronous GET request to query all known Addresses
*/
pplx::task<std::vector<responses::AddressResponse>> ShipCloud::readAllAddresses() {
	auto req = this->createGetRequest(U("addresses"), 
									  this->cfg.apiConfig().apiCall(U("addresses")), 
									  this->getAuthData(), U("application/json"));
	
	uri _uri(this->cfg.serverUrl());
	http_client client(_uri);

	return client.request(req).then([=](http_response response) -> pplx::task<json::value>
	{
		if (response.status_code() == status_codes::OK)
		{
			return response.extract_json();
		}
		return pplx::task_from_result(json::value(U("error")));
	}).then([](json::value json) -> std::vector<responses::AddressResponse> {
		std::stringstream ss;
		auto s = json.serialize();
		ss << utility::conversions::to_utf8string(json.serialize());
		auto p = modernJson::parse(ss);
		std::vector<responses::AddressResponse> vec;
		for (auto& v : p.front()) {
			vec.emplace_back(ShipCloud::parse_address_string(helpers::StringHelper::to_wstring(v.dump())));
		}
		return vec;
	});;
}

/*
* Convert Address into a JSON
*/
const std::wstring ShipCloud::addressToString(const types::Address& address)
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
	
	return helpers::StringHelper::to_wstring(j.dump());
}

const types::responses::AddressResponse ShipCloud::parseAddressString(const std::wstring& response) {
	std::stringstream ss;
	ss << helpers::StringHelper::to_string(response);
	auto val = json::value::parse(ss);
	return ShipCloud::parseAddressResponse(val);
}
const std::wstring ShipCloud::composeApiCallUrl(const std::wstring callName)
{	
	auto version = this->cfg.apiConfig().apiCalls()[callName].version();
	std::wstringstream ss;
	ss << U("/") << version << U("/") << callName;

	return ss.str();
}
/*
* Convert JSON response into AddressResponse
*/
const types::responses::AddressResponse ShipCloud::parseAddressResponse(const json::value& response)
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
const std::wstring ShipCloud::getAuthData()
{
	auto strKey = conversions::to_utf8string(this->cfg.apiConfig().activeApiKey());
	const std::vector<uint8_t> data(strKey.begin(), strKey.end());
	auto base64Key = conversions::to_base64(data);

	std::wstringstream ss;
	ss << U("Basic ") << conversions::to_string_t(base64Key);

	return ss.str();
}

http_request ShipCloud::createGetRequest(const std::wstring& endpoint, const base::ApiCall& call, 
										 const std::wstring& authData, const std::wstring& contentType) {
	std::wstringstream ss;
	ss << U("/") << call.version() << U("/") << endpoint;

	http_request req(methods::GET);
	req.headers().add(U("Authorization"), authData);
	req.set_request_uri(ss.str());
	req.headers().set_content_type(contentType);

	return req;
}

http_request ShipCloud::createPostRequest(const std::wstring& endpoint, const base::ApiCall& call, 
										  const std::wstring& authData, const std::wstring& contentType, 
										  const std::wstring& data) {
	std::wstringstream ss;
	ss << U("/") << call.version() << U("/") << endpoint;

	http_request req(methods::POST);
	req.headers().add(U("Authorization"), authData);
	req.set_request_uri(ss.str());
	req.headers().set_content_type(contentType);
	req.set_body(data);

	return req;
}

