#ifndef __API_CONFIG_H__
#define __API_CONFIG_H__

namespace shipcloud {
	namespace api {
		namespace base {
			class SHIPCLOUD_API ApiConfig {
			public:
				ApiConfig();
				~ApiConfig();
				ApiConfig(const ApiConfig& other);
				ApiConfig(ApiConfig&& other);
				ApiConfig& operator=(const ApiConfig& other);
				ApiConfig& operator=(ApiConfig&& other);
				std::string getApiKey();
				void setSandboxKey(std::string& key);
				void setProductionKey(std::string& key);
				void setDebug(bool val);
				bool isDebug();
				std::map<std::string, ApiCall>& getApiCalls();
				ApiCall& getApiCall(std::string name);
			protected:
				std::string sandboxApiKey;
				std::string productionApiKey;
				bool debug;
				std::map<std::string, ApiCall> calls;
			};
		}
	}
}
#endif // __API_CONFIG_H__