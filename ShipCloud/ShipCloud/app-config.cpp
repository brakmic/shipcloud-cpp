#include "stdafx.h"
using namespace utility;

namespace shipcloud {
	namespace api {
		namespace base {
			AppConfig::AppConfig(const std::wstring configPath)
				: configPath_(std::move(configPath))
			{
				read();
			}

			AppConfig::~AppConfig()
			{
			}

			AppConfig::AppConfig(const AppConfig& other)
			{
				if (&other != this) {
					configPath_ = other.configPath_;
					json_ = other.json_;
					apiCfg_ = other.apiCfg_;
					serverUrl_ = other.serverUrl_;
				}
			}

			AppConfig::AppConfig(AppConfig&& other)
			{
				if (&other != this) {
					configPath_ = std::move(other.configPath_);
					json_ = std::move(other.json_);
					apiCfg_ = std::move(other.apiCfg_);
					serverUrl_ = std::move(other.serverUrl_);
				}
			}

			AppConfig& AppConfig::operator=(const AppConfig& other)
			{
				if (&other != this) {
					configPath_ = other.configPath_;
					json_ = other.json_;
					apiCfg_ = other.apiCfg_;
					serverUrl_ = other.serverUrl_;
				}
				return *this;
			}

			AppConfig& AppConfig::operator=(AppConfig&& other)
			{
				if (&other != this) {
					configPath_ = std::move(other.configPath_);
					json_ = std::move(other.json_);
					apiCfg_ = std::move(other.apiCfg_);
					serverUrl_ = std::move(other.serverUrl_);
				}
				return *this;
			}

			void AppConfig::read() {
				std::ifstream i(this->configPath_);
				i >> json_;
				init();
			}
			const std::wstring AppConfig::get(const std::wstring& key) {
				std::string key_(key.begin(), key.end());
				if (!json_[key_].is_null()) {
					if (json_[key_].is_object()) {
						auto obj = json_.find(key_);
						return conversions::to_string_t(obj.value().dump());
					}
					else if (json_[key_].is_boolean()) {
						auto v = json_.value(key_, true);
						return v ? conversions::to_string_t("true") : 
								   conversions::to_string_t("false");
					}
				}
				return conversions::to_string_t(json_.value(key_, std::string()));
			}
			std::wstring AppConfig::serverUrl() const
			{
				return serverUrl_;
			}

			api::base::ApiConfig AppConfig::apiConfig() const
			{
				return apiCfg_;
			}

			modernJson AppConfig::json() const
			{
				return json_;
			}

			std::wstring AppConfig::configPath() const
			{
				return configPath_;
			}

			void AppConfig::init()
			{
				apiCfg_.setSandboxKey(get(U("sandboxApiKey")));
				apiCfg_.setProductionKey(get(U("productionApiKey")));
				apiCfg_.setDebug(get(U("debugMode")) == U("true") ? true : false);

				auto apiJson = json_.find("api");
				auto dump = apiJson.value().dump();
				std::stringstream ss;
				ss << dump;

				auto json = modernJson::parse(ss);
				auto serverUrl = conversions::to_string_t(json.value("server", std::string()));
				serverUrl_ = conversions::to_string_t("https://") + serverUrl;

				initApiCalls(json);
			}

			void AppConfig::initApiCalls(modernJson& json)
			{
				auto endpoints = json.value("endpoints", std::vector<std::string>());
				auto server = json.value("server", std::string());
				auto version = json.value("version", std::string());
				for (const auto& e : endpoints) {
					std::pair<std::wstring, ApiCall> entry;
					std::wstring e_(e.begin(), e.end());
					apiCfg_.apiCalls().emplace(e_, ApiCall(utility::conversions::to_utf16string(version), 
						utility::conversions::to_utf16string(server)));
				}
			}
		}
	}
}