/**
 *	@file	never_stop_token.hpp
 *
 *	@brief	never_stop_token の定義
 */

#ifndef HAMON_STOP_TOKEN_NEVER_STOP_TOKEN_HPP
#define HAMON_STOP_TOKEN_NEVER_STOP_TOKEN_HPP

#include <hamon/config.hpp>

namespace hamon
{

// 32.3.7 Class never_stop_token[stoptoken.never]

class never_stop_token
{
private:
	struct callback_type_t
	{
#if defined(HAMON_HAS_CXX20_ABBREVIATED_FUNCTION_TEMPLATE)
		explicit callback_type_t(never_stop_token, auto&&) noexcept {}
#else
		template <typename T>
		explicit callback_type_t(never_stop_token, T&&) noexcept {}
#endif
	};

public:
	template <typename>
	using callback_type = callback_type_t;

	static constexpr bool stop_requested() noexcept { return false; }
	static constexpr bool stop_possible() noexcept { return false; }

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	bool operator==(never_stop_token const&) const = default;
#else
	bool operator==(never_stop_token const&) const
	{
		return true;
	}
	bool operator!=(never_stop_token const&) const
	{
		return false;
	}
#endif
};

}	// namespace hamon

#endif // HAMON_STOP_TOKEN_NEVER_STOP_TOKEN_HPP
