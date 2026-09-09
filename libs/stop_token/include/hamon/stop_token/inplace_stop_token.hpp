/**
 *	@file	inplace_stop_token.hpp
 *
 *	@brief	inplace_stop_token の定義
 */

#ifndef HAMON_STOP_TOKEN_INPLACE_STOP_TOKEN_HPP
#define HAMON_STOP_TOKEN_INPLACE_STOP_TOKEN_HPP

#include <hamon/stop_token/inplace_stop_token_fwd.hpp>
#include <hamon/stop_token/inplace_stop_callback_fwd.hpp>
#include <hamon/stop_token/inplace_stop_source.hpp>

namespace hamon
{

// 32.3.8 Class inplace_stop_token[stoptoken.inplace]

class inplace_stop_token
{
public:
	template <typename CallbackFn>
	using callback_type = hamon::inplace_stop_callback<CallbackFn>;

	inplace_stop_token() = default;

//	bool operator==(inplace_stop_token const&) const = default;

	// [stoptoken.inplace.mem], member functions
	bool stop_requested() const noexcept;
	bool stop_possible() const noexcept;

	void swap(inplace_stop_token&) noexcept;

private:
	hamon::inplace_stop_source const* stop_source_ = nullptr;
};

}	// namespace hamon

#endif // HAMON_STOP_TOKEN_INPLACE_STOP_TOKEN_HPP
