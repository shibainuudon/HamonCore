/**
 *	@file	simple_array.hpp
 *
 *	@brief	simple_array の定義
 */

#ifndef HAMON_DETAIL_SIMPLE_ARRAY_HPP
#define HAMON_DETAIL_SIMPLE_ARRAY_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

// シンプル版のhamon::array
//
// 一時的なバッファが必要な場合、生配列を使いたいところだが
// 関数から生配列を返すことはできない等の理由から、
// hamon::arrayを使わざるを得ない時がある。
// そうすると、hamon::arrayは結構色んなものに依存しているので、
// 余計な依存関係を持ち込んでしまう。
// このクラスはそれを避けるための簡易版array。
template <typename T, hamon::size_t N>
struct simple_array
{
	T	m_elems[N];

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR T*
	begin() HAMON_NOEXCEPT
	{
		return data();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T const*
	begin() const HAMON_NOEXCEPT
	{
		return data();
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR T*
	end() HAMON_NOEXCEPT
	{
		return data() + N;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T const*
	end() const HAMON_NOEXCEPT
	{
		return data() + N;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T const*
	cbegin() const HAMON_NOEXCEPT
	{
		return data();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T const*
	cend() const HAMON_NOEXCEPT
	{
		return data() + N;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
	empty() const HAMON_NOEXCEPT
	{
		return N == 0;
	}
	
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::size_t
	size() const HAMON_NOEXCEPT
	{
		return N;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::size_t
	max_size() const HAMON_NOEXCEPT
	{
		return N;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR T&
	operator[](hamon::size_t n) HAMON_NOEXCEPT
	{
		return m_elems[n];
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T const&
	operator[](hamon::size_t n) const HAMON_NOEXCEPT
	{
		return m_elems[n];
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR T&
	front() HAMON_NOEXCEPT
	{
		return (*this)[0];
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T const&
	front() const HAMON_NOEXCEPT
	{
		return (*this)[0];
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR T&
	back() HAMON_NOEXCEPT
	{
		return (*this)[N-1];
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T const&
	back() const HAMON_NOEXCEPT
	{
		return (*this)[N-1];
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR T*
	data() HAMON_NOEXCEPT
	{
		return &m_elems[0];
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T const*
	data() const HAMON_NOEXCEPT
	{
		return &m_elems[0];
	}
};

template <typename T, hamon::size_t N>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR bool
operator==(simple_array<T, N> const& lhs, simple_array<T, N> const& rhs)
{
	auto first1 = lhs.begin();
	auto last1  = lhs.end();
	auto first2 = rhs.begin();
	auto last2  = rhs.end();

	// equal(first1, last1, first2, last2)
	for (; first1 != last1 && first2 != last2; ++first1, ++first2)
	{
		if (!(*first1 < *first2))
		{
			return false;
		}
	}

	return first1 == last1 && first2 == last2;
}

template <typename T, hamon::size_t N>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR bool
operator!=(simple_array<T, N> const& lhs, simple_array<T, N> const& rhs)
{
	return !(lhs == rhs);
}

template <typename T, hamon::size_t N>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR bool
operator<(simple_array<T, N> const& lhs, simple_array<T, N> const& rhs)
{
	auto first1 = lhs.begin();
	auto last1  = lhs.end();
	auto first2 = rhs.begin();
	auto last2  = rhs.end();

	// lexicographical_compare(first1, last1, first2, last2)
	for (; first2 != last2; ++first1, (void) ++first2)
	{
		if (first1 == last1 || *first1 < *first2)
		{
			return true;
		}

		if (*first2 < *first1)
		{
			return false;
		}
	}

	return false;
}

template <typename T, hamon::size_t N>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR bool
operator>(simple_array<T, N> const& lhs, simple_array<T, N> const& rhs)
{
	return rhs < lhs;
}

template <typename T, hamon::size_t N>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR bool
operator<=(simple_array<T, N> const& lhs, simple_array<T, N> const& rhs)
{
	return !(lhs > rhs);
}

template <typename T, hamon::size_t N>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR bool
operator>=(simple_array<T, N> const& lhs, simple_array<T, N> const& rhs)
{
	return !(lhs < rhs);
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_DETAIL_SIMPLE_ARRAY_HPP
