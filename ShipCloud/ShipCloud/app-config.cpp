#include "stdafx.h"
using namespace utility;

namespace shipcloud {
	namespace api {
		namespace base {
			AppConfig::AppConfig(const std::wstring configPath)
				: configPath_(std::move(configPath))
			{
				this->read();
			}

			AppConfig::~AppConfig()
			{
			}

			AppConfig::AppConfig(const AppConfig& other)
			{
				if (&other != this) {
					this->configPath_ = other.configPath_;
					this->json_ = other.json_;
					this->apiCfg_ = other.apiCfg_;
					this->serverUrl_ = other.serverUrl_;
				}
			}

			AppConfig::AppConfig(AppConfig&& other)
			{
				if (&other != this) {
					this->configPath_ = std::move(other.configPath_);
					this->json_ = std::move(other.json_);
					this->apiCfg_ = std::move(other.apiCfg_);
					this->serverUrl_ = std::move(other.serverUrl_);
				}
			}

			AppConfig& AppConfig::operator=(const AppConfig& other)
			{
				if (&other != this) {
					this->configPath_ = other.configPath_;
					this->json_ = other.json_;
					this->apiCfg_ = other.apiCfg_;
					this->serverUrl_ = other.serverUrl_;
				}
				return *this;
			}

			AppConfig& AppConfig::operator=(AppConfig&& other)
			{
				if (&other != this) {
					this->configPath_ = std::move(other.configPath_);
					this->json_ = std::move(other.json_);
					this->apiCfg_ = std::move(other.apiCfg_);
					this->serverUrl_ = std::move(other.serverUrl_);
				}
				return *this;
			}

			void AppConfig::read() {
				std::ifstream i(this->configPath_);
				i >> this->json_;
				this->init();
			}
			const std::wstring AppConfig::get(const std::wstring& key) {
				std::string key_(key.begin(), key.end());
				if (!this->json_[key_].is_null()) {
					if (this->json_[key_].is_object()) {
						auto obj = this->json_.find(key_);
						return conversions::to_string_t(obj.value().dump());
					}
					else if (this->json_[key_].is_boolean()) {
						auto v = this->json_.value(key_, true);
						return v ? conversions::to_string_t("true") : 
								   conversions::to_string_t("false");
					}
				}
				return conversions::to_string_t(this->json_.value(key_, std::string()));
			}
			std::wstring AppConfig::serverUrl() const
			{
				return this->serverUrl_;
			}

			api::base::ApiConfig AppConfig::apiConfig() const
			{
				return this->apiCfg_;
			}

			modernJson AppConfig::json() const
			{
				return this->json_;
			}

			std::wstring AppConfig::configPath() const
			{
				return this->configPath_;
			}

			void AppConfig::init()
			{
				this->apiCfg_.setSandboxKey(this->get(U("sandboxApiKey")));
				this->apiCfg_.setProductionKey(this->get(U("productionApiKey")));
				this->apiCfg_.setDebug(this->get(U("debugMode")) == U("true") ? true : false);

				auto apiJson = this->json_.find("api");
				auto dump = apiJson.value().dump();
				std::stringstream ss;
				ss << dump;

				auto json = modernJson::parse(ss);
				auto serverUrl = conversions::to_string_t(json.value("server", std::string()));
				this->serverUrl_ = conversions::to_string_t("https://") + serverUrl;

				this->initApiCalls(json);
			}

			void AppConfig::initApiCalls(modernJson& json)
			{
				auto endpoints = json.value("endpoints", std::vector<std::string>());
				auto server = json.value("server", std::string());
				auto version = json.value("version", std::string());
				for (const auto& e : endpoints) {
					std::pair<std::wstring, ApiCall> entry;
					std::wstring e_(e.begin(), e.end());
					this->apiCfg_.apiCalls().emplace(e_, ApiCall(utility::conversions::to_utf16string(version), 
						utility::conversions::to_utf16string(server)));
				}
			}
		}
	}
}