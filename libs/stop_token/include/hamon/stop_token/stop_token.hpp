/**
 *	@file	stop_token.hpp
 *
 *	@brief	stop_token の定義
 */

#ifndef HAMON_STOP_TOKEN_STOP_TOKEN_HPP
#define HAMON_STOP_TOKEN_STOP_TOKEN_HPP

#include <hamon/stop_token/stop_callback_fwd.hpp>
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
	void swap(stop_token&) noexcept;

	bool stop_requested() const noexcept;
	bool stop_possible() const noexcept;

//	bool operator==(stop_token const& rhs) noexcept = default;

private:
	//hamon::shared_ptr<unspecified> stop_state_;
};

}	// namespace hamon

#endif // HAMON_STOP_TOKEN_STOP_TOKEN_HPP
