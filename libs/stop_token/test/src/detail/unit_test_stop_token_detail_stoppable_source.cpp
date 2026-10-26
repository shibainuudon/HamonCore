/**
 *	@file	unit_test_stop_token_detail_stoppable_source.cpp
 *
 *	@brief	detail::stoppable_source のテスト
 *
 */

#include <hamon/stop_token/detail/stoppable_source.hpp>
#include <hamon/stop_token/stop_token.hpp>

namespace hamon_stop_token_test
{

namespace stoppable_source_test
{

struct StopSource1
{
	hamon::stop_token get_token() const;
	bool stop_possible() const noexcept;
	bool stop_requested() const noexcept;
	bool request_stop();
};

struct StopSource2
{
//	hamon::stop_token get_token() const;
	bool stop_possible() const noexcept;
	bool stop_requested() const noexcept;
	bool request_stop();
};

struct StopSource3
{
	/*hamon::stop_token*/int get_token() const;
	bool stop_possible() const noexcept;
	bool stop_requested() const noexcept;
	bool request_stop();
};

struct StopSource4
{
	hamon::stop_token get_token() /*const*/;
	bool stop_possible() const noexcept;
	bool stop_requested() const noexcept;
	bool request_stop();
};

struct StopSource5
{
	hamon::stop_token get_token() const;
//	bool stop_possible() const noexcept;
	bool stop_requested() const noexcept;
	bool request_stop();
};

struct StopSource6
{
	hamon::stop_token get_token() const;
	/*bool*/int stop_possible() const noexcept;
	bool stop_requested() const noexcept;
	bool request_stop();
};

struct StopSource7
{
	hamon::stop_token get_token() const;
	bool stop_possible() /*const*/ noexcept;
	bool stop_requested() const noexcept;
	bool request_stop();
};

struct StopSource8
{
	hamon::stop_token get_token() const;
	bool stop_possible() const /*noexcept*/;
	bool stop_requested() const noexcept;
	bool request_stop();
};

struct StopSource9
{
	hamon::stop_token get_token() const;
	bool stop_possible() const noexcept;
//	bool stop_requested() const noexcept;
	bool request_stop();
};

struct StopSource10
{
	hamon::stop_token get_token() const;
	bool stop_possible() const noexcept;
	/*bool*/int stop_requested() const noexcept;
	bool request_stop();
};

struct StopSource11
{
	hamon::stop_token get_token() const;
	bool stop_possible() const noexcept;
	bool stop_requested() /*const*/ noexcept;
	bool request_stop();
};

struct StopSource12
{
	hamon::stop_token get_token() const;
	bool stop_possible() const noexcept;
	bool stop_requested() const /*noexcept*/;
	bool request_stop();
};

struct StopSource13
{
	hamon::stop_token get_token() const;
	bool stop_possible() const noexcept;
	bool stop_requested() const noexcept;
//	bool request_stop();
};

struct StopSource14
{
	hamon::stop_token get_token() const;
	bool stop_possible() const noexcept;
	bool stop_requested() const noexcept;
	/*bool*/int request_stop();
};

static_assert( hamon::detail::stoppable_source<StopSource1>, "");
static_assert(!hamon::detail::stoppable_source<StopSource2>, "");
static_assert(!hamon::detail::stoppable_source<StopSource3>, "");
static_assert(!hamon::detail::stoppable_source<StopSource4>, "");
static_assert(!hamon::detail::stoppable_source<StopSource5>, "");
static_assert(!hamon::detail::stoppable_source<StopSource6>, "");
static_assert(!hamon::detail::stoppable_source<StopSource7>, "");
static_assert(!hamon::detail::stoppable_source<StopSource8>, "");
static_assert(!hamon::detail::stoppable_source<StopSource9>, "");
static_assert(!hamon::detail::stoppable_source<StopSource10>, "");
static_assert(!hamon::detail::stoppable_source<StopSource11>, "");
static_assert(!hamon::detail::stoppable_source<StopSource12>, "");
static_assert(!hamon::detail::stoppable_source<StopSource13>, "");
static_assert(!hamon::detail::stoppable_source<StopSource14>, "");

}	// namespace stoppable_source_test

}	// namespace hamon_stop_token_test
