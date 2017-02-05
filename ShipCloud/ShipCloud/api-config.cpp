#include "stdafx.h"
namespace base = shipcloud::api::base;

base::ApiConfig::ApiConfig()
	: debug(true)
{

}

base::ApiConfig::~ApiConfig()
{
	this->calls.clear();
}

base::ApiConfig::ApiConfig(ApiConfig&& other)
{
	if (&other != this) {
		this->calls = std::move(other.calls);
		this->productionApiKey = std::move(other.productionApiKey);
		this->sandboxApiKey = std::move(other.sandboxApiKey);
	}
}

base::ApiConfig::ApiConfig(const ApiConfig& other)
{
	if (&other != this) {
		this->calls = other.calls;
		this->productionApiKey = other.productionApiKey;
		this->sandboxApiKey = other.sandboxApiKey;
	}
}

base::ApiConfig & base::ApiConfig::operator=(const ApiConfig & other)
{
	if (&other != this) {
		this->calls = other.calls;
		this->productionApiKey = other.productionApiKey;
		this->sandboxApiKey = other.sandboxApiKey;
	}
	return *this;
}

base::ApiConfig & base::ApiConfig::operator=(ApiConfig && other)
{
	if (&other != this) {
		this->calls = std::move(other.calls);
		this->productionApiKey = std::move(other.productionApiKey);
		this->sandboxApiKey = std::move(other.sandboxApiKey);
	}
	return *this;
}

std::string base::ApiConfig::getApiKey()
{
	return this->debug ? this->sandboxApiKey : this->productionApiKey;
}

void base::ApiConfig::setSandboxKey(std::string& key)
{
	this->sandboxApiKey = key;
}

void base::ApiConfig::setProductionKey(std::string& key)
{
	this->productionApiKey = key;
}

void base::ApiConfig::setDebug(bool val)
{
	this->debug = val;
}

bool base::ApiConfig::isDebug()
{
	return this->debug;
}

std::map<std::string, base::ApiCall>& base::ApiConfig::getApiCalls()
{
	return this->calls;
}

base::ApiCall& base::ApiConfig::getApiCall(std::string name)
{
	return this->calls[name];
}
