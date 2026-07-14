/**
 *	@file	size0_empty.hpp
 *
 *	@brief	size0_empty の定義
 */

#ifndef HAMON_RANGES_DETAIL_SIZE0_EMPTY_HPP
#define HAMON_RANGES_DETAIL_SIZE0_EMPTY_HPP

#include <hamon/ranges/size.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

// [range.prim.empty]/2.3

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
HAMON_CONCEPT_OR_BOOL size0_empty =
	requires(T&& t)
	{
		ranges::size(t) == 0;
	};

#else

template <typename T>
struct size0_empty_impl
{
private:
	template <typename U,
		typename = decltype(ranges::size(hamon::declval<U&>()) == 0)
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
HAMON_CONCEPT_OR_BOOL size0_empty =
	size0_empty_impl<T>::type::value;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_SIZE0_EMPTY_HPP
