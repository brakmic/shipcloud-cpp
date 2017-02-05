#pragma once
namespace shipcloud {
	namespace api {
		namespace base {
			// JSON for Modern C++
			using modernJson = nlohmann::json;

			class SHIPCLOUD_API AppConfig {
			public:
				AppConfig();
				explicit AppConfig(std::wstring& config_path);
				explicit AppConfig(wchar_t* config_path);
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