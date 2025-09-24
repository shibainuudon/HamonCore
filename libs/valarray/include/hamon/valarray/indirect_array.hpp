/**
 *	@file	indirect_array.hpp
 *
 *	@brief	indirect_array の定義
 */

#ifndef HAMON_VALARRAY_INDIRECT_ARRAY_HPP
#define HAMON_VALARRAY_INDIRECT_ARRAY_HPP

#include <hamon/valarray/indirect_array_fwd.hpp>
#include <hamon/valarray/config.hpp>

#if !defined(HAMON_USE_STD_VALARRAY)

#include <hamon/valarray/detail/valarray_class.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 29.6.9 Class template indirect_array[template.indirect.array]

template <typename T>
class indirect_array
{
public:
	using value_type = T;

	HAMON_CXX20_CONSTEXPR void
	operator=(valarray<T> const& v) const
	{
		// [indirect.array.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) = v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator*=(valarray<T> const& v) const
	{
		// [indirect.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) *= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator/=(valarray<T> const& v) const
	{
		// [indirect.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) /= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator%=(valarray<T> const& v) const
	{
		// [indirect.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) %= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator+=(valarray<T> const& v) const
	{
		// [indirect.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) += v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator-=(valarray<T> const& v) const
	{
		// [indirect.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) -= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator^=(valarray<T> const& v) const
	{
		// [indirect.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) ^= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator&=(valarray<T> const& v) const
	{
		// [indirect.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) &= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator|=(valarray<T> const& v) const
	{
		// [indirect.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) |= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator<<=(valarray<T> const& v) const
	{
		// [indirect.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) <<= v[i];
		}
	}

	HAMON_CXX20_CONSTEXPR void
	operator>>=(valarray<T> const& v) const
	{
		// [indirect.array.comp.assign]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) >>= v[i];
		}
	}

	indirect_array(indirect_array const&) = default;

//	~indirect_array();

	HAMON_CXX20_CONSTEXPR indirect_array const&
	operator=(indirect_array const& v) const HAMON_NOEXCEPT // noexcept as an extension
	{
		// [indirect.array.assign]/1
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
		// [indirect.array.fill]/1
		hamon::size_t const size = this->size();
		for (hamon::size_t i = 0; i < size; ++i)
		{
			this->data(i) = v;
		}
	}

	indirect_array() = delete;

private:
	friend valarray<T>;

	HAMON_CXX20_CONSTEXPR
	indirect_array(valarray<hamon::size_t> const& indarr, T* ptr)
		: m_indarr(indarr), m_ptr(ptr)
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

private:
	valarray<hamon::size_t> m_indarr;
	T* m_ptr;
};

}	// namespace hamon

#endif

#endif // HAMON_VALARRAY_INDIRECT_ARRAY_HPP
