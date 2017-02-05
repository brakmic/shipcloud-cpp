#include "stdafx.h"

namespace api = shipcloud::api::v1;
// JSON for Modern C++
using modernJson = nlohmann::json;

std::unique_ptr<api::types::Address> getDummyAddress() {
	auto adr = std::unique_ptr<api::types::Address>(new api::types::Address());
	adr->company = "John Doe Company";
	adr->care_of = "Max Mustermann";
	adr->first_name = "Max";
	adr->last_name = "Mustermann";
	adr->city = "Troisdorf";
	adr->street = "Musterstrasse";
	adr->street_no = "42";
	adr->zip_code = "53840";
	adr->country = "DE";
	adr->state = "NRW";
	adr->phone = "555-123";
	return adr;
}

int main()
{
	Config cfg;
	cfg.read("config.json");
	// your API key (register here for a free version: https://developers.shipcloud.io/)
	std::string apiKey = cfg.get("sandboxApiKey");
	// initialize ShipCloud helper class
	auto shipCloud = std::unique_ptr<ShipCloud>(new ShipCloud(apiKey));
	// create a test address
	//auto adr = getDummyAddress();
	// use async method `createAddress` to send a POST request containing above address
	//shipCloud->createAddress(*adr).then([=](types::responses::AddressResponse& response) -> void {
	//	// print response in the console
	//	std::cout << "Response: " << types::responses::AddressResponse::to_string(response) << "\r\n";
	//}).wait();
	shipCloud->readAllAddresses().then([=](std::vector<types::responses::AddressResponse> addresses) -> void {
		for (auto& a : addresses) {
			std::cout << a.to_string() << "\r\n";
		}
	}).wait();

	system("PAUSE");
    return 0;
}

