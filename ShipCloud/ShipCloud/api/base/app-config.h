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
				explicit AppConfig(std::wstring config_path);
				virtual ~AppConfig();
				AppConfig(const AppConfig& other);
				AppConfig(AppConfig&& other);
				AppConfig& operator=(const AppConfig& other);
				AppConfig& operator=(AppConfig&& other);
				virtual std::string get(std::string key);
				virtual std::string getServerUrl();
				api::base::ApiConfig apiCfg;
				modernJson json;
				std::wstring config_path;
			protected:
				void read();
				void init();
				void initApiCalls();
			};
		}
	}
}
#endif // __APP_CONFIG_H__