/**
 *	@file	valarray_class.hpp
 *
 *	@brief	valarray の定義
 */

#ifndef HAMON_VALARRAY_DETAIL_VALARRAY_CLASS_HPP
#define HAMON_VALARRAY_DETAIL_VALARRAY_CLASS_HPP

#include <hamon/valarray/gslice_fwd.hpp>
#include <hamon/valarray/slice_fwd.hpp>
#include <hamon/valarray/gslice_array_fwd.hpp>
#include <hamon/valarray/indirect_array_fwd.hpp>
#include <hamon/valarray/mask_array_fwd.hpp>
#include <hamon/valarray/slice_array_fwd.hpp>

#include <hamon/algorithm/copy_n.hpp>
#include <hamon/algorithm/fill_n.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/memory/detail/destroy_impl.hpp>
#include <hamon/memory/detail/uninitialized_value_construct_n_impl.hpp>
#include <hamon/memory/detail/uninitialized_fill_n_impl.hpp>
#include <hamon/memory/detail/uninitialized_copy_n_impl.hpp>
#include <hamon/utility/exchange.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>
#include <initializer_list>

namespace hamon
{

// 29.6.2 Class template valarray[template.valarray]

template <typename T>
class valarray
{
private:
	using Allocator = hamon::allocator<T>;
	using AllocTraits = hamon::allocator_traits<Allocator>;

	HAMON_CXX20_CONSTEXPR
	void allocate(hamon::size_t n)
	{
		if (n != 0)
		{
			Allocator allocator;
			m_data = AllocTraits::allocate(allocator, n);
			m_size = n;
		}
	}

	HAMON_CXX20_CONSTEXPR
	void clear()
	{
		if (m_data)
		{
			Allocator allocator;
			hamon::detail::destroy_impl(allocator, m_data, m_data + m_size);
			AllocTraits::deallocate(allocator, m_data, m_size);

			m_data = nullptr;
			m_size = 0;
		}
	}

public:
	using value_type = T;

	// [valarray.cons], construct/destroy
	HAMON_CXX20_CONSTEXPR
	valarray() HAMON_NOEXCEPT // noexcept as an extension
	{
		// [valarray.cons]/1
	}

	HAMON_CXX20_CONSTEXPR explicit
	valarray(hamon::size_t n)
	{
		// [valarray.cons]/2
		this->allocate(n);
		hamon::detail::uninitialized_value_construct_n_impl(this->m_data, n);
	}

	HAMON_CXX20_CONSTEXPR
	valarray(T const& v, hamon::size_t n)
	{
		// [valarray.cons]/3
		this->allocate(n);
		hamon::detail::uninitialized_fill_n_impl(this->m_data, n, v);
	}

	HAMON_CXX20_CONSTEXPR
	valarray(T const* p, hamon::size_t n)
	{
		// [valarray.cons]/5
		this->allocate(n);
		hamon::detail::uninitialized_copy_n_impl(p, n, this->m_data);
	}

	HAMON_CXX20_CONSTEXPR
	valarray(valarray const& v)
		// [valarray.cons]/6
		: valarray(v.m_data, v.m_size)
	{}

	HAMON_CXX20_CONSTEXPR
	valarray(valarray&& v) HAMON_NOEXCEPT
		// [valarray.cons]/7
		: m_data(hamon::exchange(v.m_data, nullptr))
		, m_size(hamon::exchange(v.m_size, 0u))
	{}

	HAMON_CXX20_CONSTEXPR
	valarray(slice_array<T> const& slicearr)
	{
		*this = slicearr;
	}

	HAMON_CXX20_CONSTEXPR
	valarray(gslice_array<T> const& gslicearr)
	{
		*this = gslicearr;
	}

	HAMON_CXX20_CONSTEXPR
	valarray(mask_array<T> const& maskarr)
	{
		*this = maskarr;
	}

	HAMON_CXX20_CONSTEXPR
	valarray(indirect_array<T> const& indarr)
	{
		*this = indarr;
	}

	HAMON_CXX20_CONSTEXPR
	valarray(std::initializer_list<T> il)
		: valarray(il.begin(), il.size())	// [valarray.cons]/9
	{}

	HAMON_CXX20_CONSTEXPR
	~valarray()
	{
		// [valarray.cons]/11
		this->clear();
	}

	// [valarray.assign], assignment
	HAMON_CXX20_CONSTEXPR valarray&
	operator=(valarray const& v)
	{
		if (hamon::addressof(v) == this)
		{
			return *this;
		}

		// [valarray.assign]/1
		if (this->size() != v.size())
		{
			this->clear();
			this->allocate(v.size());
			hamon::detail::uninitialized_copy_n_impl(v.m_data, v.m_size, this->m_data);
		}
		else
		{
			hamon::copy_n(v.m_data, v.m_size, this->m_data);
		}

		// [valarray.assign]/3
		return *this;
	}

	HAMON_CXX20_CONSTEXPR valarray&
	operator=(valarray&& v) HAMON_NOEXCEPT
	{
		if (hamon::addressof(v) == this)
		{
			return *this;
		}

		// [valarray.assign]/4
		this->clear();
		m_data = hamon::exchange(v.m_data, nullptr);
		m_size = hamon::exchange(v.m_size, 0u);

		// [valarray.assign]/5
		return *this;
	}

	HAMON_CXX20_CONSTEXPR valarray&
	operator=(std::initializer_list<T> il)
	{
		// [valarray.assign]/7
		return *this = valarray(il);
	}

	HAMON_CXX20_CONSTEXPR valarray&
	operator=(T const& v)
	{
		// [valarray.assign]/8
		hamon::fill_n(this->m_data, this->m_size, v);

		// [valarray.assign]/9
		return *this;
	}

	HAMON_CXX20_CONSTEXPR valarray&
	operator=(slice_array<T> const& slicearr);

	HAMON_CXX20_CONSTEXPR valarray&
	operator=(gslice_array<T> const& gslicearr);

	HAMON_CXX20_CONSTEXPR valarray&
	operator=(mask_array<T> const& maskarr);

	HAMON_CXX20_CONSTEXPR valarray&
	operator=(indirect_array<T> const& indarr);

	// [valarray.access], element access
	HAMON_NODISCARD HAMON_CXX20_CONSTEXPR T const&
	operator[](hamon::size_t n) const HAMON_NOEXCEPT // noexcept as an extension
	{
		// [valarray.access]/1
		HAMON_ASSERT(n < this->m_size);

		// [valarray.access]/2
		return m_data[n];
	}

	HAMON_NODISCARD HAMON_CXX20_CONSTEXPR T&
	operator[](hamon::size_t n) HAMON_NOEXCEPT // noexcept as an extension
	{
		// [valarray.access]/1
		HAMON_ASSERT(n < this->m_size);

		// [valarray.access]/2
		return m_data[n];
	}

	// [valarray.sub], subset operations
	HAMON_NODISCARD
	HAMON_CXX20_CONSTEXPR valarray
	operator[](slice slicearr) const;

	HAMON_NODISCARD
	HAMON_CXX20_CONSTEXPR slice_array<T>
	operator[](slice slicearr) HAMON_NOEXCEPT; // noexcept as an extension

	HAMON_NODISCARD
	HAMON_CXX20_CONSTEXPR valarray
	operator[](gslice const& gslicearr) const;

	HAMON_NODISCARD
	HAMON_CXX20_CONSTEXPR gslice_array<T>
	operator[](gslice const& gslicearr);

	HAMON_NODISCARD
	HAMON_CXX20_CONSTEXPR valarray
	operator[](valarray<bool> const& boolarr) const;

	HAMON_NODISCARD
	HAMON_CXX20_CONSTEXPR mask_array<T>
	operator[](valarray<bool> const& boolarr);

	HAMON_NODISCARD
	HAMON_CXX20_CONSTEXPR valarray
	operator[](valarray<hamon::size_t> const& indarr) const;

	HAMON_NODISCARD
	HAMON_CXX20_CONSTEXPR indirect_array<T>
	operator[](valarray<hamon::size_t> const& indarr);

	// [valarray.unary], unary operators
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX20_CONSTEXPR valarray
	operator+() const
	{
		hamon::size_t const size = m_size;
		valarray<T> result(size);
		for (hamon::size_t i = 0; i < size; ++i)
		{
			result[i] = +m_data[i];
		}
		return result;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX20_CONSTEXPR valarray
	operator-() const
	{
		hamon::size_t const size = m_size;
		valarray<T> result(size);
		for (hamon::size_t i = 0; i < size; ++i)
		{
			result[i] = -m_data[i];
		}
		return result;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX20_CONSTEXPR valarray
	operator~() const
	{
		hamon::size_t const size = m_size;
		valarray<T> result(size);
		for (hamon::size_t i = 0; i < size; ++i)
		{
			result[i] = ~m_data[i];
		}
		return result;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX20_CONSTEXPR valarray<bool>
	operator!() const
	{
		hamon::size_t const size = m_size;
		valarray<bool> result(size);
		for (hamon::size_t i = 0; i < size; ++i)
		{
			result[i] = !m_data[i];
		}
		return result;
	}

	// [valarray.cassign], compound assignment
	HAMON_CXX20_CONSTEXPR valarray&
	operator*=(T const& v)
	{
		hamon::size_t const size = m_size;
		for (hamon::size_t i = 0; i < size; ++i)
		{
			m_data[i] *= v;
		}
		return *this;
	}

	HAMON_CXX20_CONSTEXPR valarray&
	operator/=(T const& v)
	{
		hamon::size_t const size = m_size;
		for (hamon::size_t i = 0; i < size; ++i)
		{
			m_data[i] /= v;
		}
		return *this;
	}

	HAMON_CXX20_CONSTEXPR valarray&
	operator%=(T const& v)
	{
		hamon::size_t const size = m_size;
		for (hamon::size_t i = 0; i < size; ++i)
		{
			m_data[i] %= v;
		}
		return *this;
	}

	HAMON_CXX20_CONSTEXPR valarray&
	operator+=(T const& v)
	{
		hamon::size_t const size = m_size;
		for (hamon::size_t i = 0; i < size; ++i)
		{
			m_data[i] += v;
		}
		return *this;
	}

	HAMON_CXX20_CONSTEXPR valarray&
	operator-=(T const& v)
	{
		hamon::size_t const size = m_size;
		for (hamon::size_t i = 0; i < size; ++i)
		{
			m_data[i] -= v;
		}
		return *this;
	}

	HAMON_CXX20_CONSTEXPR valarray&
	operator^=(T const& v)
	{
		hamon::size_t const size = m_size;
		for (hamon::size_t i = 0; i < size; ++i)
		{
			m_data[i] ^= v;
		}
		return *this;
	}

	HAMON_CXX20_CONSTEXPR valarray&
	operator&=(T const& v)
	{
		hamon::size_t const size = m_size;
		for (hamon::size_t i = 0; i < size; ++i)
		{
			m_data[i] &= v;
		}
		return *this;
	}

	HAMON_CXX20_CONSTEXPR valarray&
	operator|=(T const& v)
	{
		hamon::size_t const size = m_size;
		for (hamon::size_t i = 0; i < size; ++i)
		{
			m_data[i] |= v;
		}
		return *this;
	}

	HAMON_CXX20_CONSTEXPR valarray&
	operator<<=(T const& v)
	{
		hamon::size_t const size = m_size;
		for (hamon::size_t i = 0; i < size; ++i)
		{
			m_data[i] <<= v;
		}
		return *this;
	}

	HAMON_CXX20_CONSTEXPR valarray&
	operator>>=(T const& v)
	{
		hamon::size_t const size = m_size;
		for (hamon::size_t i = 0; i < size; ++i)
		{
			m_data[i] >>= v;
		}
		return *this;
	}

	HAMON_CXX20_CONSTEXPR valarray&
	operator*=(valarray const& v)
	{
		hamon::size_t const size = m_size;
		for (hamon::size_t i = 0; i < size; ++i)
		{
			m_data[i] *= v[i];
		}
		return *this;
	}

	HAMON_CXX20_CONSTEXPR valarray&
	operator/=(valarray const& v)
	{
		hamon::size_t const size = m_size;
		for (hamon::size_t i = 0; i < size; ++i)
		{
			m_data[i] /= v[i];
		}
		return *this;
	}

	HAMON_CXX20_CONSTEXPR valarray&
	operator%=(valarray const& v)
	{
		hamon::size_t const size = m_size;
		for (hamon::size_t i = 0; i < size; ++i)
		{
			m_data[i] %= v[i];
		}
		return *this;
	}

	HAMON_CXX20_CONSTEXPR valarray&
	operator+=(valarray const& v)
	{
		hamon::size_t const size = m_size;
		for (hamon::size_t i = 0; i < size; ++i)
		{
			m_data[i] += v[i];
		}
		return *this;
	}

	HAMON_CXX20_CONSTEXPR valarray&
	operator-=(valarray const& v)
	{
		hamon::size_t const size = m_size;
		for (hamon::size_t i = 0; i < size; ++i)
		{
			m_data[i] -= v[i];
		}
		return *this;
	}

	HAMON_CXX20_CONSTEXPR valarray&
	operator^=(valarray const& v)
	{
		hamon::size_t const size = m_size;
		for (hamon::size_t i = 0; i < size; ++i)
		{
			m_data[i] ^= v[i];
		}
		return *this;
	}

	HAMON_CXX20_CONSTEXPR valarray&
	operator|=(valarray const& v)
	{
		hamon::size_t const size = m_size;
		for (hamon::size_t i = 0; i < size; ++i)
		{
			m_data[i] |= v[i];
		}
		return *this;
	}

	HAMON_CXX20_CONSTEXPR valarray&
	operator&=(valarray const& v)
	{
		hamon::size_t const size = m_size;
		for (hamon::size_t i = 0; i < size; ++i)
		{
			m_data[i] &= v[i];
		}
		return *this;
	}

	HAMON_CXX20_CONSTEXPR valarray&
	operator<<=(valarray const& v)
	{
		hamon::size_t const size = m_size;
		for (hamon::size_t i = 0; i < size; ++i)
		{
			m_data[i] <<= v[i];
		}
		return *this;
	}

	HAMON_CXX20_CONSTEXPR valarray&
	operator>>=(valarray const& v)
	{
		hamon::size_t const size = m_size;
		for (hamon::size_t i = 0; i < size; ++i)
		{
			m_data[i] >>= v[i];
		}
		return *this;
	}

	// [valarray.members], member functions
	HAMON_CXX20_CONSTEXPR void
	swap(valarray& v) HAMON_NOEXCEPT
	{
		// [valarray.members]/1
		hamon::swap(m_data, v.m_data);
		hamon::swap(m_size, v.m_size);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX20_CONSTEXPR hamon::size_t
	size() const HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [valarray.members]/3
		return m_size;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX20_CONSTEXPR T
	sum() const
	{
		// [valarray.members]/6
		HAMON_ASSERT(this->size() > 0u);

		// [valarray.members]/7
		hamon::size_t const size = m_size;
		T result = m_data[0];
		for (hamon::size_t i = 1; i < size; ++i)
		{
			result += m_data[i];
		}

		return result;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX20_CONSTEXPR T
	min() const
	{
		// [valarray.members]/8
		HAMON_ASSERT(this->size() > 0u);

		// [valarray.members]/9
		hamon::size_t const size = m_size;
		T result = m_data[0];
		for (hamon::size_t i = 1; i < size; ++i)
		{
			if (m_data[i] < result)
			{
				result = m_data[i];
			}
		}

		return result;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX20_CONSTEXPR T
	max() const
	{
		// [valarray.members]/10
		HAMON_ASSERT(this->size() > 0u);

		// [valarray.members]/11
		hamon::size_t const size = m_size;
		T result = m_data[0];
		for (hamon::size_t i = 1; i < size; ++i)
		{
			if (result < m_data[i])
			{
				result = m_data[i];
			}
		}

		return result;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX20_CONSTEXPR valarray
	shift(int n) const
	{
		hamon::size_t const size = m_size;
		valarray<T> result(size);
		hamon::size_t min = 0;
		hamon::size_t max = size;

		if (n < 0)
		{
			hamon::size_t const skip = static_cast<hamon::size_t>(-n);
			min += skip;
		}
		else
		{
			hamon::size_t const skip = static_cast<hamon::size_t>(n);
			if (skip < size)
			{
				max -= skip;
			}
			else
			{
				max = 0;
			}
		}

		for (hamon::size_t i = min; i < max; ++i)
		{
			result[i] = m_data[i + static_cast<hamon::size_t>(n)];
		}

		return result;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX20_CONSTEXPR valarray
	cshift(int n) const
	{
		hamon::size_t const size = m_size;
		if (size != 0)
		{
			if (n < 0)
			{
				// right shift
				if (size < static_cast<hamon::size_t>(-n))
				{
					n = static_cast<int>(size - (static_cast<hamon::size_t>(-n) - size) % size);
				}
				else
				{
					n = static_cast<int>(size - static_cast<hamon::size_t>(-n));
				}
			}
			else if (size <= static_cast<hamon::size_t>(n))
			{
				n %= static_cast<int>(size);
			}
		}

		valarray<T> result(size);
		for (hamon::size_t i = 0; i < size; ++i)
		{
			result[i] = size - i <= static_cast<hamon::size_t>(n) ?
				m_data[i - size + static_cast<hamon::size_t>(n)] :
				m_data[i + static_cast<hamon::size_t>(n)];
		}

		return result;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX20_CONSTEXPR valarray
	apply(T func(T)) const
	{
		hamon::size_t const size = m_size;
		valarray<T> result(size);
		for (hamon::size_t i = 0; i < size; ++i)
		{
			result[i] = func(m_data[i]);
		}
		return result;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX20_CONSTEXPR valarray
	apply(T func(T const&)) const
	{
		hamon::size_t const size = m_size;
		valarray<T> result(size);
		for (hamon::size_t i = 0; i < size; ++i)
		{
			result[i] = func(m_data[i]);
		}
		return result;
	}

	HAMON_CXX20_CONSTEXPR void
	resize(hamon::size_t sz, T c = T())
	{
		// [valarray.members]/16
		this->clear();
		if (sz != 0)
		{
			this->allocate(sz);
			hamon::detail::uninitialized_fill_n_impl(this->m_data, sz, c);
		}
	}

private:
	T* m_data = nullptr;
	hamon::size_t m_size = 0;

private:
	template <typename T2>
	friend HAMON_CXX20_CONSTEXPR T2* begin(valarray<T2>& v) HAMON_NOEXCEPT; // noexcept as an extension
	template <typename T2>
	friend HAMON_CXX20_CONSTEXPR T2 const* begin(valarray<T2> const& v) HAMON_NOEXCEPT; // noexcept as an extension
	template <typename T2>
	friend HAMON_CXX20_CONSTEXPR T2* end(valarray<T2>& v) HAMON_NOEXCEPT; // noexcept as an extension
	template <typename T2>
	friend HAMON_CXX20_CONSTEXPR T2 const* end(valarray<T2> const& v) HAMON_NOEXCEPT; // noexcept as an extension
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename T, hamon::size_t cnt>
valarray(const T(&)[cnt], hamon::size_t)->valarray<T>;

#endif

// 29.6.3.4 Specialized algorithms[valarray.special]

template <typename T>
HAMON_CXX20_CONSTEXPR void
swap(valarray<T>& x, valarray<T>& y) HAMON_NOEXCEPT
{
	// [valarray.special]/1
	x.swap(y);
}

}	// namespace hamon

#endif // HAMON_VALARRAY_DETAIL_VALARRAY_CLASS_HPP
