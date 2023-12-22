/**
 *	@file	cached_value.hpp
 *
 *	@brief	cached_value の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_DETAIL_CACHED_VALUE_HPP
#define HAMON_RANGES_ADAPTORS_DETAIL_CACHED_VALUE_HPP

#include <hamon/config.hpp>
#include <hamon/assert.hpp>

namespace hamon {
namespace ranges {
namespace detail {

template <bool, typename T>
struct cached_value
{
private:
	bool	m_has_value;
	T		m_value;

public:
	HAMON_CXX11_CONSTEXPR
	cached_value() HAMON_NOEXCEPT
		: m_has_value(false)
		, m_value()
	{}

	HAMON_CXX11_CONSTEXPR bool
	has_value() const HAMON_NOEXCEPT
	{
		return m_has_value;
	}

	HAMON_CXX11_CONSTEXPR T const&
	value() const HAMON_NOEXCEPT
	{
		return HAMON_ASSERT(m_has_value), m_value;
	}

	HAMON_CXX14_CONSTEXPR cached_value&
	operator=(T const& v) HAMON_NOEXCEPT
	{
		m_has_value = true;
		m_value = v;
		return *this;
	}
};

template <typename T>
struct cached_value<false, T>
{
	HAMON_CXX11_CONSTEXPR bool
	has_value() const HAMON_NOEXCEPT
	{
		return false;
	}

	HAMON_CXX11_CONSTEXPR T
	value() const HAMON_NOEXCEPT
	{
		return T{};
	}

	HAMON_CXX14_CONSTEXPR cached_value&
	operator=(T const&) HAMON_NOEXCEPT
	{
		return *this;
	}
};

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_ADAPTORS_DETAIL_CACHED_VALUE_HPP
