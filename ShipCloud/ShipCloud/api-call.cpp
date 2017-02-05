#include "stdafx.h"
namespace shipcloud {
	namespace api {
		namespace base {

			ApiCall::ApiCall()
			{

			}

			ApiCall::ApiCall(std::wstring version, std::wstring server)
				: version(version),
				server(server)
			{
			}

			ApiCall::~ApiCall()
			{
			}

			ApiCall::ApiCall(const ApiCall& other)

				: version(other.version),
				server(other.server)
			{
			}

			ApiCall::ApiCall(ApiCall&& other)
				: version(std::move(other.version)),
				server(std::move(other.server))
			{
			}


			ApiCall& ApiCall::operator=(const ApiCall& other)
			{
				if (&other != this) {
					this->version = other.version;
					this->server = other.server;
				}
				return *this;
			}

			ApiCall& ApiCall::operator=(ApiCall&& other)
			{
				if (&other != this) {
					this->version = std::move(other.version);
					this->server = std::move(other.server);
				}
				return *this;
			}

		}
	}
}