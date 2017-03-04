#include "stdafx.h"
namespace base = shipcloud::api::base;
using namespace utility;

base::ApiConfig::~ApiConfig()
{
	calls_.clear();
}

base::ApiConfig::ApiConfig(ApiConfig&& other)
{
	if (&other != this) {
		calls_ = std::move(other.calls_);
		productionApiKey = std::move(other.productionApiKey);
		sandboxApiKey = std::move(other.sandboxApiKey);
	}
}

base::ApiConfig::ApiConfig(const ApiConfig& other)
{
	if (&other != this) {
		calls_ = other.calls_;
		productionApiKey = other.productionApiKey;
		sandboxApiKey = other.sandboxApiKey;
	}
}

base::ApiConfig& base::ApiConfig::operator=(const ApiConfig & other)
{
	if (&other != this) {
		calls_ = other.calls_;
		productionApiKey = other.productionApiKey;
		sandboxApiKey = other.sandboxApiKey;
	}
	return *this;
}

base::ApiConfig& base::ApiConfig::operator=(ApiConfig && other)
{
	if (&other != this) {
		calls_ = std::move(other.calls_);
		productionApiKey = std::move(other.productionApiKey);
		sandboxApiKey = std::move(other.sandboxApiKey);
	}
	return *this;
}

std::wstring base::ApiConfig::activeApiKey() const
{
	return debug ?sandboxApiKey : productionApiKey;
}

void base::ApiConfig::setSandboxKey(const std::wstring& key)
{
	sandboxApiKey = key;
}

void base::ApiConfig::setProductionKey(const std::wstring& key)
{
	productionApiKey = key;
}

void base::ApiConfig::setDebug(bool val)
{
	debug = val;
}

bool base::ApiConfig::isDebug()
{
	return debug;
}

std::map<std::wstring, base::ApiCall>& base::ApiConfig::apiCalls() const
{
	return calls_;
}

const base::ApiCall base::ApiConfig::apiCall(const std::wstring& name) const
{
	return calls_[name];
}
