#include "stdafx.h"

namespace api = shipcloud::api::v1;
// JSON for Modern C++
using modernJson = nlohmann::json;

std::unique_ptr<api::types::Address> getDummyAddress() {
	auto adr = std::unique_ptr<api::types::Address>(new api::types::Address());
	adr->company = "John Doe Company";
	adr->care_of = "John Doe";
	adr->first_name = "John";
	adr->last_name = "Doe";
	adr->city = "Washington D.C.";
	adr->street = "Musterstrasse";
	adr->street_no = "42";
	adr->zip_code = "20002";
	adr->country = "US";
	adr->state = "WA";
	adr->phone = "555-123";
	return adr;
}

int main()
{
	// load app settings
	base::AppConfig cfg(L"config.json");
	
	// your API key must be located in config.json (register here for a free version: https://developers.shipcloud.io/)
	// There are two keys available: sandbox & production. 
	// sandbox    -> debugMode = true
	// production -> debugMode = false
	// The ShipCloud API class will automatically select the right key depending on your debugMode settings.
	
	// initialize ShipCloud API
	auto shipCloud = std::unique_ptr<ShipCloud>(new ShipCloud(cfg));
	
	// create a test address
	//auto adr = getDummyAddress();

	// use async method `createAddress` to send a POST request containing above address
	/*shipCloud->createAddress(*adr).then([=](types::responses::AddressResponse& response) -> void {
		std::cout << "Response: " << response.to_string() << "\r\n";
	}).wait();*/
	
	// get all addresses
	shipCloud->readAllAddresses().then([=](std::vector<types::responses::AddressResponse> addresses) -> void {
		for (auto& a : addresses) {
			std::cout << a.to_string() << "\r\n";
		}
	}).wait();
	
	system("PAUSE");
    return 0;
}

