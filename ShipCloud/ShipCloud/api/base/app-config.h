#ifndef __APP_CONFIG_H__
#define __APP_CONFIG_H__

namespace shipcloud {
	namespace api {
		namespace base {
			// JSON for Modern C++
			using modernJson = nlohmann::json;

			class SHIPCLOUD_API AppConfig {
			public:
				AppConfig() = default;
				explicit AppConfig(std::wstring configPath);
				virtual ~AppConfig();
				AppConfig(const AppConfig& other);
				AppConfig(AppConfig&& other);
				AppConfig& operator=(const AppConfig& other);
				AppConfig& operator=(AppConfig&& other);
				virtual std::string get(std::string key);
				virtual std::string& getServerUrl();
				api::base::ApiConfig apiCfg;
				modernJson json;
				std::wstring configPath;
			protected:
				std::string serverUrl;
				void read();
				void init();
				void initApiCalls(modernJson& json);
			};
		}
	}
}
#endif // __APP_CONFIG_H__