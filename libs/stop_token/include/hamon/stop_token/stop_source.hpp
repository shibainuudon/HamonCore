/**
 *	@file	stop_source.hpp
 *
 *	@brief	stop_source の定義
 */

#ifndef HAMON_STOP_TOKEN_STOP_SOURCE_HPP
#define HAMON_STOP_TOKEN_STOP_SOURCE_HPP

#include <hamon/stop_token/nostopstate_t.hpp>
#include <hamon/stop_token/stop_token.hpp>
#include <hamon/memory/shared_ptr.hpp>

namespace hamon
{

// 32.3.5 Class stop_source[stopsource]

class stop_source
{
public:
	// [stopsource.cons], constructors, copy, and assignment
	stop_source();

	explicit stop_source(hamon::nostopstate_t) noexcept {}

	// [stopsource.mem], member functions
	void swap(stop_source&) noexcept;

	hamon::stop_token get_token() const noexcept;
	bool stop_possible() const noexcept;
	bool stop_requested() const noexcept;
	bool request_stop() noexcept;

//	bool operator==(stop_source const& rhs) noexcept = default;

private:
	//hamon::shared_ptr<unspecified> stop_state_;
};

}	// namespace hamon

#endif // HAMON_STOP_TOKEN_STOP_SOURCE_HPP
