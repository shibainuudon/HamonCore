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
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept begin_data =
	hamon::contiguous_iterator<decltype(ranges::begin(hamon::declval<T&>()))>;

#else

template <typename T>
struct begin_data_impl
{
private:
	template <typename U, typename B = decltype(ranges::begin(hamon::declval<U&>()))>
	static auto test(int) -> hamon::contiguous_iterator<B>;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using begin_data = typename begin_data_impl<T>::type;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_BEGIN_DATA_HPP
