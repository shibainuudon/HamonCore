﻿/**
 *	@file	xorshift_base.hpp
 *
 *	@brief	xorshift_base の定義
 */

#ifndef HAMON_RANDOM_ENGINES_DETAIL_XORSHIFT_BASE_HPP
#define HAMON_RANDOM_ENGINES_DETAIL_XORSHIFT_BASE_HPP

#include <hamon/random/engines/detail/split_mix64.hpp>
#include <hamon/ios/flags_saver.hpp>
#include <hamon/config.hpp>
#include <limits>
#include <istream>
#include <ostream>
#include <cstddef>

namespace hamon
{

template <typename UIntType, std::size_t N, typename Derived>
class xorshift_base
{
public:
	using result_type = UIntType;

	static HAMON_CONSTEXPR result_type const default_seed = 2463534242UL;

	static HAMON_CONSTEXPR result_type min() { return std::numeric_limits<result_type>::min(); }
	static HAMON_CONSTEXPR result_type max() { return std::numeric_limits<result_type>::max(); }

	explicit xorshift_base(result_type sd = default_seed)
	{
		seed(sd);
	}

	template <typename Sseq>
	explicit xorshift_base(Sseq& q)
	{
		seed(q);
	}

	void seed(result_type sd = default_seed)
	{
		split_mix64 sm(sd);

		for (std::size_t i = 0; i < N; ++i)
		{
			m_state[i] = static_cast<result_type>(sm());
		}
	}

	template <typename Sseq>
	void seed(Sseq& q)
	{
		typename Sseq::result_type ar[N];
		q.generate(ar, ar + N);
		for (std::size_t i = 0; i < N; ++i)
		{
			m_state[i] = ar[i];
		}
	}

	void discard(unsigned long long z)
	{
		auto derived = static_cast<Derived*>(this);
		for (; z; --z)
		{
			derived->operator()();
		}
	}

	bool operator==(xorshift_base const& rhs) const
	{
		for (std::size_t i = 0; i < N; ++i)
		{
			if (m_state[i] != rhs.m_state[i])
			{
				return false;
			}
		}
		return true;
	}

	bool operator!=(xorshift_base const& rhs) const
	{
		return !(*this == rhs);
	}

protected:
	result_type m_state[N];

private:
	template <
		typename CharT, typename Traits,
		typename U, std::size_t M, typename D
	>
	friend std::basic_ostream<CharT, Traits>&
	operator<<(
		std::basic_ostream<CharT, Traits>& os,
		xorshift_base<U, M, D> const& e);

	template <
		typename CharT, typename Traits,
		typename U, std::size_t M, typename D
	>
	friend std::basic_istream<CharT, Traits>&
	operator>>(
		std::basic_istream<CharT, Traits>& is,
		xorshift_base<U, M, D>& e);
};

template <
	typename CharT, typename Traits,
	typename UIntType, std::size_t N, typename Derived
>
inline std::basic_ostream<CharT, Traits>&
operator<<(
	std::basic_ostream<CharT, Traits>& os,
	xorshift_base<UIntType, N, Derived> const& e)
{
	hamon::ios::flags_saver lx(os);
	os.flags(
		std::ios_base::dec |
		std::ios_base::left |
		std::ios_base::fixed |
		std::ios_base::scientific);
	CharT sp = os.widen(' ');

	for (std::size_t i = 0; i < N; ++i)
	{
		os << sp << e.m_state[i];
	}

	return os;
}

template <
	typename CharT, typename Traits,
	typename UIntType, std::size_t N, typename Derived
>
inline std::basic_istream<CharT, Traits>&
operator>>(
	std::basic_istream<CharT, Traits>& is,
	xorshift_base<UIntType, N, Derived>& e)
{
	hamon::ios::flags_saver lx(is);
	is.flags(
		std::ios_base::dec |
		std::ios_base::skipws |
		std::ios_base::fixed |
		std::ios_base::scientific);

	UIntType tbl[N];
	for (std::size_t i = 0; i < N; ++i)
	{
		is >> tbl[i];
	}

	if (!is.fail())
	{
		for (std::size_t i = 0; i < N; ++i)
		{
			e.m_state[i] = tbl[i];
		}
	}

	return is;
}

}	// namespace hamon

#endif // HAMON_RANDOM_ENGINES_DETAIL_XORSHIFT_BASE_HPP
