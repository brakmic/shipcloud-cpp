#include "stdafx.h"
namespace base = shipcloud::api::base;
using namespace utility;

base::ApiConfig::~ApiConfig()
{
	this->calls_.clear();
}

base::ApiConfig::ApiConfig(ApiConfig&& other)
{
	if (&other != this) {
		this->calls_ = std::move(other.calls_);
		this->productionApiKey = std::move(other.productionApiKey);
		this->sandboxApiKey = std::move(other.sandboxApiKey);
	}
}

base::ApiConfig::ApiConfig(const ApiConfig& other)
{
	if (&other != this) {
		this->calls_ = other.calls_;
		this->productionApiKey = other.productionApiKey;
		this->sandboxApiKey = other.sandboxApiKey;
	}
}

base::ApiConfig& base::ApiConfig::operator=(const ApiConfig & other)
{
	if (&other != this) {
		this->calls_ = other.calls_;
		this->productionApiKey = other.productionApiKey;
		this->sandboxApiKey = other.sandboxApiKey;
	}
	return *this;
}

base::ApiConfig& base::ApiConfig::operator=(ApiConfig && other)
{
	if (&other != this) {
		this->calls_ = std::move(other.calls_);
		this->productionApiKey = std::move(other.productionApiKey);
		this->sandboxApiKey = std::move(other.sandboxApiKey);
	}
	return *this;
}

std::wstring base::ApiConfig::activeApiKey() const
{
	return this->debug ? this->sandboxApiKey : this->productionApiKey;
}

void base::ApiConfig::setSandboxKey(const std::wstring& key)
{
	this->sandboxApiKey = key;
}

void base::ApiConfig::setProductionKey(const std::wstring& key)
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

std::map<std::wstring, base::ApiCall>& base::ApiConfig::apiCalls() const
{
	return this->calls_;
}

const base::ApiCall base::ApiConfig::apiCall(const std::wstring& name) const
{
	return this->calls_[name];
}
