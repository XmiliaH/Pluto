#include "netConfig.hpp"
#if !SOUP_WASM

#include "dnsSmartResolver.hpp"
#include "Socket.hpp"

NAMESPACE_SOUP
{
	static thread_local netConfig netConfig_inst;

	netConfig& netConfig::get()
	{
		return netConfig_inst;
	}

	netConfig::netConfig() :
		// Reasons for not defaulting to dnsOsResolver:
		// - Android doesn't have libresolv
		// - Many ISPs provide disingenuous DNS servers, even blocking sites like pastebin.com
		dns_resolver(soup::make_unique<dnsSmartResolver>()),
		certchain_validator(&Socket::certchain_validator_default)
	{
	}
}

#endif
