/**
 *	@file	has_member_size.hpp
 *
 *	@brief	has_member_size の定義
 */

#ifndef HAMON_RANGES_DETAIL_HAS_MEMBER_SIZE_HPP
#define HAMON_RANGES_DETAIL_HAS_MEMBER_SIZE_HPP

#include <hamon/ranges/concepts/disable_sized_range.hpp>
#include <hamon/detail/auto_cast.hpp>
#include <hamon/iterator/detail/is_integer_like.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
HAMON_CONCEPT_OR_BOOL has_member_size =
	!hamon::ranges::disable_sized_range<hamon::remove_cvref_t<T>> &&
	requires(T&& t)
	{
		{ HAMON_AUTO_CAST(t.size()) } -> hamon::detail::is_integer_like;
	};

#else

// [range.prim.size]/2.3

template <typename T>
struct has_member_size_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			!hamon::ranges::disable_sized_range<hamon::remove_cvref_t<U>>
		>,
		typename S = decltype(HAMON_AUTO_CAST(hamon::declval<U&>().size())),
		typename = hamon::enable_if_t<hamon::detail::is_integer_like<S>>
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
HAMON_CONCEPT_OR_BOOL has_member_size =
	has_member_size_impl<T>::type::value;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_HAS_MEMBER_SIZE_HPP
