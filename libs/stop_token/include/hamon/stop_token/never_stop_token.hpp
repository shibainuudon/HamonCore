/**
 *	@file	never_stop_token.hpp
 *
 *	@brief	never_stop_token の定義
 */

#ifndef HAMON_STOP_TOKEN_NEVER_STOP_TOKEN_HPP
#define HAMON_STOP_TOKEN_NEVER_STOP_TOKEN_HPP

namespace hamon
{

// 32.3.7 Class never_stop_token[stoptoken.never]

class never_stop_token
{
private:
	struct callback_type_t
	{
//		explicit callback_type_t(never_stop_token, auto&&) noexcept {}
	};

public:
	template <typename>
	using callback_type = callback_type_t;

	static constexpr bool stop_requested() noexcept { return false; }
	static constexpr bool stop_possible() noexcept { return false; }

//	bool operator==(never_stop_token const&) const = default;
};

}	// namespace hamon

#endif // HAMON_STOP_TOKEN_NEVER_STOP_TOKEN_HPP
