/**
 *	@file	valarray.hpp
 *
 *	@brief	valarray の定義
 */

#ifndef HAMON_VALARRAY_VALARRAY_HPP
#define HAMON_VALARRAY_VALARRAY_HPP

#include <hamon/valarray/valarray_fwd.hpp>
#include <hamon/valarray/config.hpp>

#if !defined(HAMON_USE_STD_VALARRAY)

#include <hamon/valarray/detail/valarray_class.hpp>

// 29.6.3.1 Binary operators[valarray.binary]
#include <hamon/valarray/detail/valarray_binary.hpp>

// 29.6.3.2 Logical operators[valarray.comparison]
#include <hamon/valarray/detail/valarray_comparison.hpp>

// 29.6.3.3 Transcendentals[valarray.transcend]
#include <hamon/valarray/detail/valarray_transcend.hpp>

// 29.6.10 valarray range access[valarray.range]
#include <hamon/valarray/detail/valarray_range.hpp>

#include <hamon/valarray/slice.hpp>
#include <hamon/valarray/slice_array.hpp>
#include <hamon/valarray/gslice.hpp>
#include <hamon/valarray/gslice_array.hpp>
#include <hamon/valarray/mask_array.hpp>
#include <hamon/valarray/indirect_array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename T>
HAMON_CXX20_CONSTEXPR valarray<T>&
valarray<T>::operator=(slice_array<T> const& slicearr)
{
	hamon::size_t const size = slicearr.size();
	this->resize(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		m_data[i] = slicearr.data(i);
	}
	return *this;
}

template <typename T>
HAMON_CXX20_CONSTEXPR valarray<T>&
valarray<T>::operator=(gslice_array<T> const& gslicearr)
{
	hamon::size_t const size = gslicearr.size();
	this->resize(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		m_data[i] = gslicearr.data(i);
	}
	return *this;
}

template <typename T>
HAMON_CXX20_CONSTEXPR valarray<T>&
valarray<T>::operator=(mask_array<T> const& maskarr)
{
	hamon::size_t const size = maskarr.size();
	this->resize(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		m_data[i] = maskarr.data(i);
	}
	return *this;
}

template <typename T>
HAMON_CXX20_CONSTEXPR valarray<T>&
valarray<T>::operator=(indirect_array<T> const& indarr)
{
	hamon::size_t const size = indarr.size();
	this->resize(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		m_data[i] = indarr.data(i);
	}
	return *this;
}

template <typename T>
HAMON_NODISCARD
HAMON_CXX20_CONSTEXPR valarray<T>
valarray<T>::operator[](slice slicearr) const
{
	return valarray<T>(slice_array<T>(slicearr.start(), slicearr.size(), slicearr.stride(), m_data));
}

template <typename T>
HAMON_NODISCARD
HAMON_CXX20_CONSTEXPR slice_array<T>
valarray<T>::operator[](slice slicearr) HAMON_NOEXCEPT // noexcept as an extension
{
	return slice_array<T>(slicearr.start(), slicearr.size(), slicearr.stride(), m_data);
}

template <typename T>
HAMON_NODISCARD
HAMON_CXX20_CONSTEXPR valarray<T>
valarray<T>::operator[](gslice const& gslicearr) const
{
	return valarray<T>(gslice_array<T>(gslicearr.start(), gslicearr.size(), gslicearr.stride(), m_data));
}

template <typename T>
HAMON_NODISCARD
HAMON_CXX20_CONSTEXPR gslice_array<T>
valarray<T>::operator[](gslice const& gslicearr)
{
	return gslice_array<T>(gslicearr.start(), gslicearr.size(), gslicearr.stride(), m_data);
}

template <typename T>
HAMON_NODISCARD
HAMON_CXX20_CONSTEXPR valarray<T>
valarray<T>::operator[](valarray<bool> const& boolarr) const
{
	return valarray<T>(mask_array<T>(boolarr, m_data));
}

template <typename T>
HAMON_NODISCARD
HAMON_CXX20_CONSTEXPR mask_array<T>
valarray<T>::operator[](valarray<bool> const& boolarr)
{
	return mask_array<T>(boolarr, m_data);
}

template <typename T>
HAMON_NODISCARD
HAMON_CXX20_CONSTEXPR valarray<T>
valarray<T>::operator[](valarray<hamon::size_t> const& indarr) const
{
	return valarray<T>(indirect_array<T>(indarr, m_data));
}

template <typename T>
HAMON_NODISCARD
HAMON_CXX20_CONSTEXPR indirect_array<T>
valarray<T>::operator[](valarray<hamon::size_t> const& indarr)
{
	return indirect_array<T>(indarr, m_data);
}

}	// namespace hamon

#endif

#endif // HAMON_VALARRAY_VALARRAY_HPP
