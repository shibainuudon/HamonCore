/**
 *	@file	has_member_empty.hpp
 *
 *	@brief	has_member_empty の定義
 */

#ifndef HAMON_RANGES_DETAIL_HAS_MEMBER_EMPTY_HPP
#define HAMON_RANGES_DETAIL_HAS_MEMBER_EMPTY_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_member_empty =
	requires(T& t)
	{
		bool(t.empty());
	};

#else

template <typename T>
struct has_member_empty_impl
{
private:
	template <typename U,
		typename = decltype(bool(std::declval<U&>().empty()))
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_member_empty = typename has_member_empty_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_HAS_MEMBER_EMPTY_HPP
