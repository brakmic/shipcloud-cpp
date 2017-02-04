#pragma once
namespace shipcloud {
	namespace api {
		namespace v1 {
			namespace types {
				namespace responses {
					class AddressResponse {
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
							static std::string to_string(AddressResponse& r) {
								std::stringstream ss;
								ss << "id: " << r.id << ", company: " << r.company <<
									", first_name: " << r.first_name << ", last_name: " <<
									r.last_name << ", care_of: " << r.care_of << ", street: " <<
									r.street << ", street_no: " << r.street_no << ", zip_code: " <<
									r.zip_code << ", city: " << r.city << ", state: " << r.state <<
									", country: " << r.country << ", phone: " << r.phone;
								return ss.str();
							}
					};
				}
			}
		}
	}
}