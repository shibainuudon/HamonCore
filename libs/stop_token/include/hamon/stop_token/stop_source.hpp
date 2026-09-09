/**
 *	@file	stop_source.hpp
 *
 *	@brief	stop_source の定義
 */

#ifndef HAMON_STOP_TOKEN_STOP_SOURCE_HPP
#define HAMON_STOP_TOKEN_STOP_SOURCE_HPP

#include <hamon/stop_token/nostopstate_t.hpp>
#include <hamon/stop_token/stop_token.hpp>
#include <hamon/stop_token/detail/stop_state.hpp>
#include <hamon/memory/shared_ptr.hpp>

namespace hamon
{

// 32.3.5 Class stop_source[stopsource]

class stop_source
{
public:
	// [stopsource.cons], constructors, copy, and assignment
	stop_source()
		// [stopsource.cons]/1
		: stop_state_(new hamon::detail::stop_state())
	{
		stop_state_->__increment_stop_source_counter();
	}

	explicit stop_source(hamon::nostopstate_t) noexcept {}

	// [stopsource.mem], member functions
	void swap(stop_source& rhs) noexcept
	{
		// [stopsource.mem]/1
		stop_state_.swap(rhs.stop_state_);
	}

	hamon::stop_token get_token() const noexcept
	{
		// [stopsource.mem]/2
		if (!stop_possible())
		{
			return stop_token();
		}
		return hamon::stop_token(stop_state_);
	}

	bool stop_possible() const noexcept
	{
		// [stopsource.mem]/3
		return stop_state_ != nullptr;
	}

	bool stop_requested() const noexcept
	{
		// [stopsource.mem]/4
		return stop_state_ != nullptr && stop_state_->__stop_requested();
	}

	bool request_stop() noexcept
	{
		// [stopsource.mem]/5
		return stop_state_ != nullptr && stop_state_->__request_stop();
	}

//	bool operator==(stop_source const& rhs) noexcept = default;

private:
	hamon::shared_ptr<hamon::detail::stop_state> stop_state_;
};

}	// namespace hamon

#endif // HAMON_STOP_TOKEN_STOP_SOURCE_HPP
