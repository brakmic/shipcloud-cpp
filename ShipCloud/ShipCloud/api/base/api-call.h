#ifndef __API_CALL_H__
#define __API_CALL_H__

namespace shipcloud {
	namespace api {
		namespace base {
			class SHIPCLOUD_API ApiCall {
			public:
				ApiCall() = default;
				ApiCall(std::wstring version, std::wstring server);
				virtual ~ApiCall();
				ApiCall(const ApiCall& other);
				ApiCall(ApiCall&& other);
				ApiCall& operator=(const ApiCall& other);
				ApiCall& operator=(ApiCall&& other);
				std::wstring version() const;
				std::wstring server() const;
			protected:
				mutable std::wstring version_;
				mutable std::wstring server_;
			};
		}
	}
}
#endif // __API_CALL_H__