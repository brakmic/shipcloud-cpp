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
				explicit AppConfig(const std::wstring configPath);
				virtual ~AppConfig();
				AppConfig(const AppConfig& other);
				AppConfig(AppConfig&& other);
				AppConfig& operator=(const AppConfig& other);
				AppConfig& operator=(AppConfig&& other);
				virtual const std::wstring get(const std::wstring& key);
				std::wstring serverUrl() const;
				api::base::ApiConfig apiConfig() const;
				modernJson json() const;
				std::wstring configPath() const;
			protected:
				mutable std::wstring configPath_;
				mutable std::wstring serverUrl_;
				mutable api::base::ApiConfig apiCfg_;
				mutable modernJson json_;

				virtual void initApiCalls(modernJson& json);
				virtual void read();
				virtual void init();
			};
		}
	}
}
#endif // __APP_CONFIG_H__