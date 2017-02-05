#pragma once
namespace shipcloud {
	namespace api {
		namespace v1 {
			namespace types {
				namespace responses {
					class SHIPCLOUD_API AddressResponse {
						public:
							std::string id;
							std::string company;
							std::string first_name;
							std::string last_name;
							std::string care_of;
							std::string street;
							std::string	street_no;
							std::string	zip_code;
							std::string	city;
							std::string	state;
							std::string	country;
							std::string	phone;
							std::string to_string() {
								std::stringstream ss;
								ss << "id: " << id << ", company: " << company <<
									", first_name: " << first_name << ", last_name: " <<
									last_name << ", care_of: " << care_of << ", street: " <<
									street << ", street_no: " << street_no << ", zip_code: " <<
									zip_code << ", city: " << city << ", state: " << state <<
									", country: " << country << ", phone: " << phone;
								return ss.str();
							}
					};
				}
			}
		}
	}
}