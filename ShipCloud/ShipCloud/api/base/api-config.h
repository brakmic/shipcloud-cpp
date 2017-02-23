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
				std::wstring activeApiKey() const;
				void setSandboxKey(const std::wstring& key);
				void setProductionKey(const std::wstring& key);
				void setDebug(bool val);
				bool isDebug();
				std::map<std::wstring, ApiCall>& apiCalls() const;
				const ApiCall apiCall(const std::wstring& name) const;
			protected:
				bool debug = true;
				std::wstring sandboxApiKey;
				std::wstring productionApiKey;
				mutable std::map<std::wstring, ApiCall> calls_;
			};
		}
	}
}
#endif // __API_CONFIG_H__