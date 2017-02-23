#include "stdafx.h"

const std::string shipcloud::api::helpers::StringHelper::to_string(const std::wstring& wstr)
{
	const auto pwstr = wstr.c_str();
	const size_t len = wstr.length();
	auto pstr = new char[len];
	const size_t cplen = wcstombs(pstr, pwstr, len);
	pstr[len] = 0;
	if (cplen != len) {
		throw new std::exception("Could not convert to std::string");
	}
	return std::string(std::move(pstr));
}

const std::wstring shipcloud::api::helpers::StringHelper::to_wstring(const std::string& str)
{
	const auto pstr = str.c_str();
	const size_t len = str.length();
	const size_t size = len * sizeof(wchar_t);
	auto pwstr = new wchar_t[size];
	const size_t cplen = mbstowcs(pwstr, pstr, size);
	pwstr[size] = 0;
	if (cplen != len) {
		throw new std::exception("Could not convert to std::wstring");
	}
	return std::wstring(std::move(pwstr));
}
