/**
 *	@file	mask_array.hpp
 *
 *	@brief	mask_array の定義
 */

#ifndef HAMON_VALARRAY_MASK_ARRAY_HPP
#define HAMON_VALARRAY_MASK_ARRAY_HPP

#include <hamon/valarray/mask_array_fwd.hpp>
#include <hamon/valarray/config.hpp>

#if !defined(HAMON_USE_STD_VALARRAY)

#include <hamon/valarray/detail/valarray_class.hpp>
#include <hamon/valarray/detail/valarray_range.hpp>
#include <hamon/algorithm/ranges/count.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 29.6.8 Class template mask_array[template.mask.array]

template <typename T>
class mask_array
{
public:
	using value_type = T;

	HAMON_CXX20_CONSTEXPR void
	operator=(valarray<T> const& v) const
	{
		// [mask.array.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) = v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator*=(valarray<T> const& v) const
	{
		// [mask.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) *= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator/=(valarray<T> const& v) const
	{
		// [mask.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) /= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator%=(valarray<T> const& v) const
	{
		// [mask.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) %= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator+=(valarray<T> const& v) const
	{
		// [mask.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) += v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator-=(valarray<T> const& v) const
	{
		// [mask.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) -= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator^=(valarray<T> const& v) const
	{
		// [mask.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) ^= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator&=(valarray<T> const& v) const
	{
		// [mask.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) &= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator|=(valarray<T> const& v) const
	{
		// [mask.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) |= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator<<=(valarray<T> const& v) const
	{
		// [mask.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) <<= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator>>=(valarray<T> const& v) const
	{
		// [mask.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) >>= v[i];
		}
	}

	mask_array(mask_array const&) = default;

	//~mask_array();

	HAMON_CXX20_CONSTEXPR mask_array const&
	operator=(mask_array const& v) const HAMON_NOEXCEPT // noexcept as an extension
	{
		// [mask.array.assign]/1
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
		// [mask.array.fill]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) = v;
		}
	}

	mask_array() = delete;

private:
	friend valarray<T>;

	HAMON_CXX20_CONSTEXPR
	mask_array(valarray<bool> const& maskarr, T* ptr)
		: m_indarr(static_cast<hamon::size_t>(hamon::ranges::count(maskarr, true)))
		, m_ptr(ptr)
	{
		hamon::size_t count = 0;
		hamon::size_t const size = maskarr.size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			if (maskarr[i])
			{
				m_indarr[count] = i;
				++count;
			}
		}
	}

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

private:
	valarray<hamon::size_t> m_indarr;
	T* m_ptr;
};

}	// namespace hamon

#endif

#endif // HAMON_VALARRAY_MASK_ARRAY_HPP
