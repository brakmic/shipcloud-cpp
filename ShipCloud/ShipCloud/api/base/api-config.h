#ifndef __API_CONFIG_H__
#define __API_CONFIG_H__

namespace shipcloud {
	namespace api {
		namespace base {
			class SHIPCLOUD_API ApiConfig {
			public:
				ApiConfig() = default;
				~ApiConfig();
				ApiConfig(const ApiConfig& other);
				ApiConfig(ApiConfig&& other);
				ApiConfig& operator=(const ApiConfig& other);
				ApiConfig& operator=(ApiConfig&& other);
				const std::string getApiKey();
				void setSandboxKey(const std::string& key);
				void setProductionKey(const std::string& key);
				void setDebug(bool val);
				bool isDebug();
				std::map<std::string, ApiCall>& getApiCalls();
				ApiCall getApiCall(const std::string name);
			protected:
				bool debug = true;
				std::string sandboxApiKey;
				std::string productionApiKey;
				std::map<std::string, ApiCall> calls;
			};
		}
	}
}
#endif // __API_CONFIG_H__