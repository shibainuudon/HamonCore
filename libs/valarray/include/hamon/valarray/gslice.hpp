/**
 *	@file	gslice.hpp
 *
 *	@brief	gslice の定義
 */

#ifndef HAMON_VALARRAY_GSLICE_HPP
#define HAMON_VALARRAY_GSLICE_HPP

#include <hamon/valarray/gslice_fwd.hpp>
#include <hamon/valarray/config.hpp>

#if !defined(HAMON_USE_STD_VALARRAY)

#include <hamon/valarray/detail/valarray_class.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 29.6.6 The gslice class[class.gslice]

class gslice
{
public:
	HAMON_CXX20_CONSTEXPR
	gslice()
		// [gslice.cons]/1
		: m_start(0), m_size(), m_stride()
	{}

	HAMON_CXX20_CONSTEXPR
	gslice(hamon::size_t start, valarray<hamon::size_t> const& lengths, valarray<hamon::size_t> const& strides)
		// [gslice.cons]/1
		: m_start(start), m_size(lengths), m_stride(strides)
	{}

	HAMON_NODISCARD // nodiscard as an extension
	HAMON_CXX20_CONSTEXPR hamon::size_t
	start() const HAMON_NOEXCEPT // noexcept as an extension
	{
		// [gslice.access]/1
		return m_start;
	}

	HAMON_NODISCARD // nodiscard as an extension
	HAMON_CXX20_CONSTEXPR valarray<hamon::size_t>
	size() const
	{
		// [gslice.access]/1
		return m_size;
	}

	HAMON_NODISCARD // nodiscard as an extension
	HAMON_CXX20_CONSTEXPR valarray<hamon::size_t>
	stride() const
	{
		// [gslice.access]/1
		return m_stride;
	}

private:
	hamon::size_t m_start;
	valarray<hamon::size_t> m_size;
	valarray<hamon::size_t> m_stride;
};

}	// namespace hamon

#endif

#endif // HAMON_VALARRAY_GSLICE_HPP
