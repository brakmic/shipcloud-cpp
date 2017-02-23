#pragma once
namespace shipcloud {
	namespace api {
		namespace helpers {
			class StringHelper {
			public:
				static std::string to_string(std::wstring wstr);
				static std::wstring to_wstring(std::string str);
			};
		}
	}
}