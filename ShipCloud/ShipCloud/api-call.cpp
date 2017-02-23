#include "stdafx.h"
namespace shipcloud {
	namespace api {
		namespace base {

			ApiCall::ApiCall(std::wstring version, std::wstring server)
				: version_(std::move(version)),
				server_(std::move(server))
			{
			}

			ApiCall::~ApiCall()
			{
			}

			ApiCall::ApiCall(const ApiCall& other)

				: version_(other.version_),
				server_(other.server_)
			{
			}

			ApiCall::ApiCall(ApiCall&& other)
				: version_(std::move(other.version_)),
				server_(std::move(other.server_))
			{
			}


			ApiCall& ApiCall::operator=(const ApiCall& other)
			{
				if (&other != this) {
					this->version_ = other.version_;
					this->server_ = other.server_;
				}
				return *this;
			}

			ApiCall& ApiCall::operator=(ApiCall&& other)
			{
				if (&other != this) {
					this->version_ = std::move(other.version_);
					this->server_ = std::move(other.server_);
				}
				return *this;
			}

			std::wstring ApiCall::version() const
			{
				return this->version_;
			}

			std::wstring ApiCall::server() const
			{
				return this->server_;
			}

		}
	}
}