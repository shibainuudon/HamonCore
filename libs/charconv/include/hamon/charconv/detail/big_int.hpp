/**
 *	@file	big_int.hpp
 *
 *	@brief	big_int の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_BIG_INT_HPP
#define HAMON_CHARCONV_DETAIL_BIG_INT_HPP

#include <hamon/charconv/detail/pow5_table.hpp>
#include <hamon/bigint.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/cmath/round_up.hpp>
#include <hamon/cstddef.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

namespace from_chars_detail
{

template <hamon::size_t Bits>
struct big_int
{
public:
#if defined(HAMON_HAS_INT128)
	using value_type = hamon::uint64_t;
#else
	using value_type = hamon::uint32_t;
#endif
	using size_type = hamon::size_t;

private:
	static constexpr hamon::size_t N = hamon::round_up(Bits, hamon::bitsof<value_type>()) / hamon::bitsof<value_type>();

	size_type  m_size;
	value_type m_data[N];

public:
	HAMON_CXX14_CONSTEXPR
	big_int()
		: m_size(1)
		, m_data{0}
	{}

	HAMON_CXX14_CONSTEXPR
	big_int(value_type v)
		: m_size(1)
		, m_data{v}
	{}

	HAMON_CXX14_CONSTEXPR
	big_int(value_type const* first, value_type const* last)
		: m_size(static_cast<size_type>(last - first))
		, m_data{}
	{
		auto dst = m_data;
		for (auto src = first; src != last; ++src)
		{
			*dst++ = *src;
		}
	}

	HAMON_CXX11_CONSTEXPR size_type size() const
	{
		return m_size;
	}

	HAMON_CXX11_CONSTEXPR size_type max_size() const
	{
		return N;
	}

	HAMON_CXX14_CONSTEXPR value_type* data()
	{
		return m_data;
	}

	HAMON_CXX11_CONSTEXPR value_type const* data() const
	{
		return m_data;
	}

	HAMON_CXX14_CONSTEXPR void resize(size_type new_size)
	{
		//for (size_type i = m_size; i < new_size; ++i)
		//{
		//	m_data[i] = 0;
		//}

		m_size = new_size;
	}

	HAMON_CXX14_CONSTEXPR hamon::uint64_t to_uint64() const
	{
		hamon::uint64_t result{};
		hamon::bigint_algo::to_uint(result, *this);
		return result;
	}

	HAMON_CXX14_CONSTEXPR big_int& operator*=(big_int const& rhs)
	{
		big_int tmp;
		hamon::bigint_algo::multiply(tmp, *this, rhs);
		*this = tmp;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR big_int& operator<<=(int shift)
	{
		hamon::bigint_algo::bit_shift_left(*this, static_cast<hamon::uintmax_t>(shift));
		return *this;
	}

	HAMON_CXX14_CONSTEXPR big_int& operator>>=(int shift)
	{
		hamon::bigint_algo::bit_shift_right(*this, static_cast<hamon::uintmax_t>(shift));
		return *this;
	}
};

template <hamon::size_t Bits>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR int
bit_width(big_int<Bits> const& x) HAMON_NOEXCEPT
{
	return hamon::bigint_algo::bit_width(x);
}

template <hamon::size_t Bits>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR int
countr_zero(big_int<Bits> const& x) HAMON_NOEXCEPT
{
	return hamon::bigint_algo::countr_zero(x);
}

template <hamon::size_t Bits>
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR bool
is_zero(big_int<Bits> const& x) HAMON_NOEXCEPT
{
	return hamon::bigint_algo::is_zero(x);
}

template <hamon::size_t Bits>
inline HAMON_CXX14_CONSTEXPR big_int<Bits>
div_mod(big_int<Bits> const& lhs, big_int<Bits> const& rhs, big_int<Bits>* quo)
{
	big_int<Bits> rem;
	hamon::bigint_algo::div_mod(*quo, rem, lhs, rhs);
	return rem;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR BigInt pow5(int n)
{
#if 0
	BigInt result;
	hamon::bigint_algo::pow_n(result, BigInt{5}, static_cast<hamon::uintmax_t>(n));
	return result;
#endif

	auto const& tbl = pow5_table[n];
	return BigInt{&tbl.magnitude[0], &tbl.magnitude[tbl.size]};
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR void
unchecked_from_chars_dec(char const* first, char const* last, BigInt& value)
{
	using T = typename BigInt::value_type;

	auto constexpr digits = hamon::numeric_limits<T>::digits10;
	auto constexpr pow10_c = hamon::detail::pow_n(T{10}, digits);

	auto mag_p = value.data();
	auto mag_n = value.size();
	for (auto p = first; p != last;)
	{
		T accum = 0;
		int count = 0;

		while (count < digits && p != last)
		{
			accum = accum * 10 + static_cast<T>(*p - '0');
			++count;
			++p;
		}

		//value *= pow_n(10, count);
		//value += accum;
		{
			auto const pow10 = count == digits ?
				pow10_c : hamon::detail::pow_n(T{10}, count);

			for (hamon::size_t i = 0; i < mag_n; ++i)
			{
				mag_p[i] = bigint_algo::detail::mulc(mag_p[i], pow10, &accum);
			}
			if (accum != 0)
			{
				++mag_n;
				value.resize(mag_n);
				mag_p[mag_n - 1] = accum;
			}
		}
	}
}

}	// namespace from_chars_detail

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_BIG_INT_HPP
