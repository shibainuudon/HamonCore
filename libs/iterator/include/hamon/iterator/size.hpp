/**
 *	@file	size.hpp
 *
 *	@brief	size 関数の定義
 */

#ifndef HAMON_ITERATOR_SIZE_HPP
#define HAMON_ITERATOR_SIZE_HPP

#include <iterator>

#if defined(__cpp_lib_nonmember_container_access) && (__cpp_lib_nonmember_container_access >= 201411)

namespace hamon
{

using std::size;

}	// namespace hamon

#else

#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename Container>
HAMON_NODISCARD HAMON_CONSTEXPR auto
size(Container const& c) -> decltype(c.size())
{
	return c.size();
}

template <typename T, hamon::size_t N>
HAMON_NODISCARD HAMON_CONSTEXPR hamon::size_t
size(T const (&)[N]) HAMON_NOEXCEPT
{
	return N;
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_SIZE_HPP
