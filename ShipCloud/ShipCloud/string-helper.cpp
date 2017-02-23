#include "stdafx.h"

std::string shipcloud::api::helpers::StringHelper::to_string(std::wstring wstr)
{
	auto cstr = std::shared_ptr<wchar_t>(wstr.c_str());
	const size_t len = wstr.length();
	auto tp = std::unique_ptr<char>(new char[len]);
	size_t w = wcstombs(tp.get(), cstr.get(), len);
	if (w != len) {
		throw new std::exception("Could not convert to std::string");
	}
	return std::string(tp.release());
}

std::wstring shipcloud::api::helpers::StringHelper::to_wstring(std::string str)
{
	auto pstr = std::shared_ptr<char>(str.c_str());
	size_t size = str.length() * sizeof(wchar_t);
	auto tp = std::unique_ptr<wchar_t>(new wchar_t[size]);
	size_t w = mbstowcs(tp.get(), pstr.get(), size);
	if (w != str.length()) {
		throw new std::exception("Could not convert to std::wstring");
	}
	return std::wstring(tp.release());
}
