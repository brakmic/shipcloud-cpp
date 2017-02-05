#include "stdafx.h"
Config::Config()
{
}

Config::~Config()
{
}

void Config::read(std::string config_path) {
	std::ifstream i(config_path);
	i >> this->json;
}

std::string Config::get(std::string key) {
	return this->json.value(key, "");
}
