/**
 *	@file	empty.hpp
 *
 *	@brief	empty 関数の定義
 */

#ifndef HAMON_ITERATOR_EMPTY_HPP
#define HAMON_ITERATOR_EMPTY_HPP

#include <iterator>

#if defined(__cpp_lib_nonmember_container_access) && (__cpp_lib_nonmember_container_access >= 201411)

namespace hamon
{

using std::empty;

}	// namespace hamon

#else

#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <initializer_list>

namespace hamon
{

template <typename Container>
HAMON_NODISCARD HAMON_CONSTEXPR auto empty(Container const& c) -> decltype(c.empty())
{
	return c.empty();
}

template <typename T, hamon::size_t N>
HAMON_NODISCARD HAMON_CONSTEXPR bool empty(T const (&)[N]) HAMON_NOEXCEPT
{
	return false;
}

template <typename E>
HAMON_NODISCARD HAMON_CONSTEXPR bool empty(std::initializer_list<E> il) HAMON_NOEXCEPT
{
	return il.size() == 0;
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_EMPTY_HPP
