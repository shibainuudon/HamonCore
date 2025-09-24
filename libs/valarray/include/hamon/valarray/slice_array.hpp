/**
 *	@file	slice_array.hpp
 *
 *	@brief	slice_array の定義
 */

#ifndef HAMON_VALARRAY_SLICE_ARRAY_HPP
#define HAMON_VALARRAY_SLICE_ARRAY_HPP

#include <hamon/valarray/slice_array_fwd.hpp>
#include <hamon/valarray/config.hpp>

#if !defined(HAMON_USE_STD_VALARRAY)

#include <hamon/valarray/detail/valarray_class.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 29.6.5 Class template slice_array[template.slice.array]

template <typename T>
class slice_array
{
public:
	using value_type = T;

	HAMON_CXX20_CONSTEXPR void
	operator=(valarray<T> const& v) const
	{
		// [slice.arr.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) = v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator*=(valarray<T> const& v) const
	{
		// [slice.arr.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) *= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator/=(valarray<T> const& v) const
	{
		// [slice.arr.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) /= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator%=(valarray<T> const& v) const
	{
		// [slice.arr.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) %= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator+=(valarray<T> const& v) const
	{
		// [slice.arr.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) += v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator-=(valarray<T> const& v) const
	{
		// [slice.arr.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) -= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator^=(valarray<T> const& v) const
	{
		// [slice.arr.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) ^= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator&=(valarray<T> const& v) const
	{
		// [slice.arr.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) &= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator|=(valarray<T> const& v) const
	{
		// [slice.arr.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) |= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator<<=(valarray<T> const& v) const
	{
		// [slice.arr.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) <<= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator>>=(valarray<T> const& v) const
	{
		// [slice.arr.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) >>= v[i];
		}
	}

	slice_array(slice_array const&) = default;

//	~slice_array();

	HAMON_CXX20_CONSTEXPR slice_array const&
	operator=(slice_array const& v) const HAMON_NOEXCEPT // noexcept as an extension
	{
		// [slice.arr.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) = v.data(i);
		}
		return *this;
	}

	HAMON_CXX20_CONSTEXPR
	void operator=(T const& v) const
	{
		// [slice.arr.fill]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) = v;
		}
	}

	slice_array() = delete;

private:
	friend valarray<T>;

	HAMON_CXX20_CONSTEXPR
	slice_array(hamon::size_t start, hamon::size_t length, hamon::size_t stride, T* ptr) HAMON_NOEXCEPT
		: m_start(start), m_size(length), m_stride(stride), m_ptr(ptr)
	{}

	HAMON_NODISCARD HAMON_CXX20_CONSTEXPR hamon::size_t
	size() const HAMON_NOEXCEPT
	{
		return m_size;
	}

	HAMON_NODISCARD HAMON_CXX20_CONSTEXPR T&
	data(hamon::size_t i) const HAMON_NOEXCEPT
	{
		return m_ptr[m_start + (i * m_stride)];
	}

private:
	hamon::size_t m_start;
	hamon::size_t m_size;
	hamon::size_t m_stride;
	T* m_ptr;
};

}	// namespace hamon

#endif

#endif // HAMON_VALARRAY_SLICE_ARRAY_HPP
