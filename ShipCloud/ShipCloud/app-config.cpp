#include "stdafx.h"
namespace shipcloud {
	namespace api {
		namespace base {
			AppConfig::AppConfig(std::wstring config_path)
				: config_path(std::move(config_path))
			{
				this->read();
			}

			AppConfig::~AppConfig()
			{
			}

			AppConfig::AppConfig(const AppConfig & other)
			{
				if (&other != this) {
					this->config_path = other.config_path;
					this->json = other.json;
					this->apiCfg = other.apiCfg;
				}
			}

			AppConfig::AppConfig(AppConfig && other)
			{
				if (&other != this) {
					this->config_path = std::move(other.config_path);
					this->json = std::move(other.json);
					this->apiCfg = std::move(other.apiCfg);
				}
			}

			AppConfig& AppConfig::operator=(const AppConfig & other)
			{
				if (&other != this) {
					this->config_path = other.config_path;
					this->json = other.json;
					this->apiCfg = other.apiCfg;
				}
				return *this;
			}

			AppConfig& AppConfig::operator=(AppConfig && other)
			{
				if (&other != this) {
					this->config_path = std::move(other.config_path);
					this->json = std::move(other.json);
					this->apiCfg = std::move(other.apiCfg);
				}
				return *this;
			}

			void AppConfig::read() {
				std::ifstream i(this->config_path);
				i >> this->json;
				this->init();
			}
			std::string AppConfig::get(std::string key) {
				if (!this->json[key].is_null()) {
					if (this->json[key].is_object()) {
						auto obj = this->json.find(key);
						return obj.value().dump();
					}
					else if (this->json[key].is_boolean()) {
						auto v = this->json.value(key, true);
						return v ? "true" : "false";
					}
				}
				return this->json.value(key, std::string());
			}
			std::string AppConfig::getServerUrl()
			{
				auto api = this->json.find("api");
				auto dump = api.value().dump();
				std::stringstream ss;
				ss << dump;
				auto json = modernJson::parse(ss);
				auto serverUrl = json.value("server", std::string());
				std::stringstream ss2;
				ss2 << "https://" << serverUrl;
				return ss2.str();
			}
			void AppConfig::init()
			{
				this->apiCfg.setSandboxKey(this->get("sandboxApiKey"));
				this->apiCfg.setProductionKey(this->get("productionApiKey"));
				this->apiCfg.setDebug(this->get("debugMode") == "true" ? true : false);
				this->initApiCalls();
			}

			void AppConfig::initApiCalls()
			{
				auto api = this->get("api");
				std::stringstream ss;
				ss << api;
				auto json = modernJson::parse(ss);
				auto endpoints = json.value("endpoints", std::vector<std::string>());
				auto server = json.value("server", std::string());
				auto version = json.value("version", std::string());
				for (const auto& e : endpoints) {
					std::pair<std::string, ApiCall> entry;
					entry.first = e;
					entry.second = ApiCall(utility::conversions::to_utf16string(version), utility::conversions::to_utf16string(server));
					this->apiCfg.getApiCalls().insert(entry);
				}
			}

		}
	}
}