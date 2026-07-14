/**
 *	@file	begin_data.hpp
 *
 *	@brief	begin_data の定義
 */

#ifndef HAMON_RANGES_DETAIL_BEGIN_DATA_HPP
#define HAMON_RANGES_DETAIL_BEGIN_DATA_HPP

#include <hamon/ranges/begin.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

// [range.prim.data]/2.4

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
HAMON_CONCEPT_OR_BOOL begin_data =
	hamon::contiguous_iterator<decltype(ranges::begin(hamon::declval<T&>()))>;

#else

template <typename T>
struct begin_data_impl
{
private:
	template <typename U,
		typename I = decltype(ranges::begin(hamon::declval<U&>())),
		typename = hamon::enable_if_t<hamon::contiguous_iterator<I>>
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
HAMON_CONCEPT_OR_BOOL begin_data =
	begin_data_impl<T>::type::value;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_BEGIN_DATA_HPP
