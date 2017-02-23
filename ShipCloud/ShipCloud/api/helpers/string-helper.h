#pragma once
namespace shipcloud {
	namespace api {
		namespace helpers {
			class StringHelper {
			public:
				static const std::string to_string(const std::wstring& wstr);
				static const std::wstring to_wstring(const std::string& str);
			};
		}
	}
}