/**
 *	@file	slice.hpp
 *
 *	@brief	slice の定義
 */

#ifndef HAMON_VALARRAY_SLICE_HPP
#define HAMON_VALARRAY_SLICE_HPP

#include <hamon/valarray/slice_fwd.hpp>
#include <hamon/valarray/config.hpp>

#if !defined(HAMON_USE_STD_VALARRAY)

#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 29.6.4 Class slice[class.slice]

class slice
{
public:
	HAMON_CXX11_CONSTEXPR
	slice() HAMON_NOEXCEPT // noexcept as an extension
		// [cons.slice]/1
		: slice(0, 0, 0)
	{}

	HAMON_CXX11_CONSTEXPR
	slice(hamon::size_t start, hamon::size_t length, hamon::size_t stride) HAMON_NOEXCEPT // noexcept as an extension
		// [cons.slice]/1
		: m_start(start), m_size(length), m_stride(stride)
	{}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR hamon::size_t
	start() const HAMON_NOEXCEPT // noexcept as an extension
	{
		// [slice.access]/1
		return m_start;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR hamon::size_t
	size() const HAMON_NOEXCEPT // noexcept as an extension
	{
		// [slice.access]/1
		return m_size;
	}

	HAMON_NODISCARD // nodiscard as an extension
	HAMON_CXX11_CONSTEXPR hamon::size_t
	stride() const HAMON_NOEXCEPT // noexcept as an extension
	{
		// [slice.access]/1
		return m_stride;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR friend bool
	operator==(slice const& x, slice const& y) HAMON_NOEXCEPT // noexcept as an extension
	{
		// [slice.ops]/1
		return x.start() == y.start() && x.size() == y.size() && x.stride() == y.stride();
	}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR friend bool
	operator!=(slice const& x, slice const& y) HAMON_NOEXCEPT
	{
		return !(x == y);
	}
#endif

private:
	hamon::size_t m_start;
	hamon::size_t m_size;
	hamon::size_t m_stride;
};

}	// namespace hamon

#endif

#endif // HAMON_VALARRAY_SLICE_HPP
