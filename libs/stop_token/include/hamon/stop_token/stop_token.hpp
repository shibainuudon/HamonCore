/**
 *	@file	stop_token.hpp
 *
 *	@brief	stop_token の定義
 */

#ifndef HAMON_STOP_TOKEN_STOP_TOKEN_HPP
#define HAMON_STOP_TOKEN_STOP_TOKEN_HPP

#include <hamon/stop_token/stop_callback_fwd.hpp>
#include <hamon/stop_token/detail/stop_state.hpp>
#include <hamon/memory/shared_ptr.hpp>

namespace hamon
{

// 32.3.4 Class stop_token[stoptoken]

class stop_token
{
public:
	template <typename CallbackFn>
	using callback_type = hamon::stop_callback<CallbackFn>;

	stop_token() noexcept = default;

	// [stoptoken.mem], member functions
	void swap(stop_token& rhs) noexcept
	{
		// [stoptoken.mem]/1
		stop_state_.swap(rhs.stop_state_);
	}

	bool stop_requested() const noexcept
	{
		// [stoptoken.mem]/2
		return stop_state_ != nullptr && stop_state_->__stop_requested();
	}

	bool stop_possible() const noexcept
	{
		// [stoptoken.mem]/3
		return stop_state_ != nullptr && stop_state_->__stop_possible_for_stop_token();
	}

//	bool operator==(stop_token const& rhs) noexcept = default;

private:
	explicit stop_token(hamon::shared_ptr<hamon::detail::stop_state> const& state_) : stop_state_(state_) {}

	friend class stop_source;

	hamon::shared_ptr<hamon::detail::stop_state> stop_state_;
};

}	// namespace hamon

#endif // HAMON_STOP_TOKEN_STOP_TOKEN_HPP
