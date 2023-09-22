/**
 *	@file	eq_iter_empty.hpp
 *
 *	@brief	eq_iter_empty の定義
 */

#ifndef HAMON_RANGES_DETAIL_EQ_ITER_EMPTY_HPP
#define HAMON_RANGES_DETAIL_EQ_ITER_EMPTY_HPP

#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_unbounded_array.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept eq_iter_empty =
	requires(T& t)
	{
		requires (!hamon::is_unbounded_array<hamon::remove_reference_t<T>>::value);
		{ ranges::begin(t) } -> hamon::forward_iterator;
		bool(ranges::begin(t) == ranges::end(t));
	};

#else

template <typename T>
struct eq_iter_empty_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			!hamon::is_unbounded_array<hamon::remove_reference_t<U>>::value
		>,
		typename B = decltype(ranges::begin(hamon::declval<U&>())),
		typename = hamon::enable_if_t<hamon::forward_iterator<B>::value>,
		typename = decltype(bool(ranges::begin(hamon::declval<U&>()) == ranges::end(hamon::declval<U&>())))
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using eq_iter_empty = typename eq_iter_empty_impl<T>::type;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_EQ_ITER_EMPTY_HPP
