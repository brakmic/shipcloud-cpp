#include "stdafx.h"
namespace shipcloud {
	namespace api {
		namespace base {
			AppConfig::AppConfig(std::wstring configPath)
				: configPath(std::move(configPath))
			{
				this->read();
			}

			AppConfig::~AppConfig()
			{
			}

			AppConfig::AppConfig(const AppConfig & other)
			{
				if (&other != this) {
					this->configPath = other.configPath;
					this->json = other.json;
					this->apiCfg = other.apiCfg;
					this->serverUrl = other.serverUrl;
				}
			}

			AppConfig::AppConfig(AppConfig && other)
			{
				if (&other != this) {
					this->configPath = std::move(other.configPath);
					this->json = std::move(other.json);
					this->apiCfg = std::move(other.apiCfg);
					this->serverUrl = std::move(other.serverUrl);
				}
			}

			AppConfig& AppConfig::operator=(const AppConfig & other)
			{
				if (&other != this) {
					this->configPath = other.configPath;
					this->json = other.json;
					this->apiCfg = other.apiCfg;
					this->serverUrl = other.serverUrl;
				}
				return *this;
			}

			AppConfig& AppConfig::operator=(AppConfig && other)
			{
				if (&other != this) {
					this->configPath = std::move(other.configPath);
					this->json = std::move(other.json);
					this->apiCfg = std::move(other.apiCfg);
					this->serverUrl = std::move(other.serverUrl);
				}
				return *this;
			}

			void AppConfig::read() {
				std::ifstream i(this->configPath);
				i >> this->json;
				this->init();
			}
			const std::string AppConfig::get(std::string key) {
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
			const std::string& AppConfig::getServerUrl()
			{
				return this->serverUrl;
			}

			void AppConfig::init()
			{
				this->apiCfg.setSandboxKey(this->get("sandboxApiKey"));
				this->apiCfg.setProductionKey(this->get("productionApiKey"));
				this->apiCfg.setDebug(this->get("debugMode") == "true" ? true : false);

				auto apiJson = this->json.find("api");
				auto dump = apiJson.value().dump();
				std::stringstream ss;
				ss << dump;

				auto json = modernJson::parse(ss);
				auto serverUrl = json.value("server", std::string());
				this->serverUrl = "https://" + serverUrl;

				this->initApiCalls(json);
			}

			void AppConfig::initApiCalls(modernJson& json)
			{
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