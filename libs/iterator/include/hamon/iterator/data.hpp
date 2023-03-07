/**
 *	@file	data.hpp
 *
 *	@brief	data 関数の定義
 */

#ifndef HAMON_ITERATOR_DATA_HPP
#define HAMON_ITERATOR_DATA_HPP

#include <iterator>

#if defined(__cpp_lib_nonmember_container_access) && (__cpp_lib_nonmember_container_access >= 201411)

namespace hamon
{

using std::data;

}	// namespace hamon

#else

#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <initializer_list>

namespace hamon
{

template <typename Container>
HAMON_NODISCARD HAMON_CONSTEXPR auto data(Container& c) -> decltype(c.data())
{
	return c.data();
}

template <typename Container>
HAMON_NODISCARD HAMON_CONSTEXPR auto data(Container const& c) -> decltype(c.data())
{
	return c.data();
}

template <typename T, hamon::size_t N>
HAMON_NODISCARD HAMON_CONSTEXPR T* data(T (&a)[N]) HAMON_NOEXCEPT
{
	return a;
}

template <typename E>
HAMON_NODISCARD HAMON_CONSTEXPR E const* data(std::initializer_list<E> il) HAMON_NOEXCEPT
{
	return il.begin();
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_DATA_HPP
