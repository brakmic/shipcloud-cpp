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

namespace api = shipcloud::api::v1;
namespace types = shipcloud::api::v1::types;
namespace responses = shipcloud::api::v1::types::responses;
// JSON for Modern C++
using modernJson = nlohmann::json;

// This class is exported from the ShipCloud.dll
class SHIPCLOUD_API ShipCloud {
public:
	ShipCloud(std::string apiKey);
	virtual ~ShipCloud();
	ShipCloud(const ShipCloud& other) = delete;
	ShipCloud(ShipCloud&& other) = delete;
	ShipCloud& operator=(const ShipCloud& other) = delete;
	ShipCloud& operator=(ShipCloud&& other) = delete;
	pplx::task<responses::AddressResponse> createAddress(types::Address& address);
	pplx::task<std::vector<responses::AddressResponse>> readAllAddresses();
	static std::string address_to_string(types::Address& address);
	static types::responses::AddressResponse parse_address_response(web::json::value& response);
	static types::responses::AddressResponse ShipCloud::parse_address_string(std::string response);
private:
	std::wstring get_auth_data();
	std::string apiKey;
	std::wstring apiUrl;
};

class SHIPCLOUD_API Config {
public:
	Config();
	virtual ~Config();
	virtual void read(std::string config_path);
	virtual std::string get(std::string key);
protected:
	modernJson json;
};
