/**
 *	@file	has_adl_rbegin.hpp
 *
 *	@brief	has_adl_rbegin の定義
 */

#ifndef HAMON_RANGES_DETAIL_HAS_ADL_RBEGIN_HPP
#define HAMON_RANGES_DETAIL_HAS_ADL_RBEGIN_HPP

#include <hamon/detail/decay_copy.hpp>
#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

#if 0
void rbegin(auto&) = delete;
void rbegin(const auto&) = delete;
#else
template <typename T> void rbegin(T&) = delete;
template <typename T> void rbegin(const T&) = delete;
#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_adl_rbegin =
	hamon::detail::class_or_enum<hamon::remove_reference_t<T>> &&
	requires(T& t)
	{
		{ hamon::detail::decay_copy(rbegin(t)) } -> hamon::input_or_output_iterator;
	};

#else

template <typename T>
struct has_adl_rbegin_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<
				hamon::remove_reference_t<U>
			>::value>,
		typename B = decltype(hamon::detail::decay_copy(rbegin(hamon::declval<U&>())))
	>
	static auto test(int) -> hamon::input_or_output_iterator<B>;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_adl_rbegin = typename has_adl_rbegin_impl<T>::type;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_HAS_ADL_RBEGIN_HPP
