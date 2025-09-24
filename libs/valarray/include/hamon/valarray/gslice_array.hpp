/**
 *	@file	gslice_array.hpp
 *
 *	@brief	gslice_array の定義
 */

#ifndef HAMON_VALARRAY_GSLICE_ARRAY_HPP
#define HAMON_VALARRAY_GSLICE_ARRAY_HPP

#include <hamon/valarray/gslice_array_fwd.hpp>
#include <hamon/valarray/config.hpp>

#if !defined(HAMON_USE_STD_VALARRAY)

#include <hamon/valarray/detail/valarray_class.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 29.6.7 Class template gslice_array[template.gslice.array]

template <typename T>
class gslice_array
{
public:
	using value_type = T;

	HAMON_CXX20_CONSTEXPR void
	operator=(valarray<T> const& v) const
	{
		// [gslice.array.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) = v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator*=(valarray<T> const& v) const
	{
		// [gslice.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) *= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator/=(valarray<T> const& v) const
	{
		// [gslice.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) /= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator%=(valarray<T> const& v) const
	{
		// [gslice.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) %= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator+=(valarray<T> const& v) const
	{
		// [gslice.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) += v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator-=(valarray<T> const& v) const
	{
		// [gslice.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) -= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator^=(valarray<T> const& v) const
	{
		// [gslice.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) ^= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator&=(valarray<T> const& v) const
	{
		// [gslice.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) &= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator|=(valarray<T> const& v) const
	{
		// [gslice.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) |= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator<<=(valarray<T> const& v) const
	{
		// [gslice.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) <<= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator>>=(valarray<T> const& v) const
	{
		// [gslice.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) >>= v[i];
		}
	}

	gslice_array(gslice_array const&) = default;

//	~gslice_array();

	HAMON_CXX20_CONSTEXPR gslice_array const&
	operator=(gslice_array const& v) const HAMON_NOEXCEPT // noexcept as an extension
	{
		// [gslice.array.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) = v.data(i);
		}
		return *this;
	}

	HAMON_CXX20_CONSTEXPR void
	operator=(T const& v) const
	{
		// [gslice.array.fill]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) = v;
		}
	}

	gslice_array() = delete;

private:
	friend valarray<T>;

	HAMON_CXX20_CONSTEXPR
	gslice_array(
		hamon::size_t start,
		valarray<hamon::size_t> const& lengths,
		valarray<hamon::size_t> const& strides,
		T* ptr) HAMON_NOEXCEPT
		: m_indarr(init(start, lengths, strides))
		, m_ptr(ptr)
	{}

	HAMON_NODISCARD HAMON_CXX20_CONSTEXPR hamon::size_t
	size() const HAMON_NOEXCEPT
	{
		return m_indarr.size();
	}

	HAMON_NODISCARD HAMON_CXX20_CONSTEXPR T&
	data(hamon::size_t i) const HAMON_NOEXCEPT
	{
		return m_ptr[m_indarr[i]];
	}

	static HAMON_CXX20_CONSTEXPR valarray<hamon::size_t>
	init(hamon::size_t start,
		valarray<hamon::size_t> const& lengths,
		valarray<hamon::size_t> const& strides)
	{
		hamon::size_t const size = total_length(lengths);
		valarray<hamon::size_t> indarr(size);

		valarray<hamon::size_t> indexarr(lengths.size());
		for (hamon::size_t i = 0; i < size; ++i)
		{
			indarr[i] = start + calc_offset(indexarr, strides);
			increment(indexarr, lengths);
		}

		return indarr;
	}

	static HAMON_CXX20_CONSTEXPR hamon::size_t
	total_length(valarray<hamon::size_t> const& lengths)
	{
		hamon::size_t const size = lengths.size();
		if (size == 0)
		{
			return 0;
		}

		hamon::size_t count = lengths[0];
		for (hamon::size_t i = 1; i < size; ++i)
		{
			count *= lengths[i];
		}

		return count;
	}

	static HAMON_CXX20_CONSTEXPR hamon::size_t
	calc_offset(valarray<hamon::size_t> const& indexarr,
		valarray<hamon::size_t> const& strides) HAMON_NOEXCEPT
	{
		hamon::size_t result = 0;
		hamon::size_t const size = indexarr.size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			result += indexarr[i] * strides[i];
		}
		return result;
	}

	static HAMON_CXX20_CONSTEXPR void
	increment(valarray<hamon::size_t>& indexarr,
		valarray<hamon::size_t> const& lengths)
	{
		hamon::size_t i = indexarr.size();
		while (0 < i)
		{
			--i;
			++indexarr[i];
			if (indexarr[i] < lengths[i])
			{
				break; // increment done, quit
			}
			else
			{
				indexarr[i] = 0; // carry to more-significant index
			}
		}
	}

private:
	valarray<hamon::size_t> m_indarr;
	T* m_ptr;
};

}	// namespace hamon

#endif

#endif // HAMON_VALARRAY_GSLICE_ARRAY_HPP
