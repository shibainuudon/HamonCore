/**
 *	@file	concatable.hpp
 *
 *	@brief	concatable の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_DETAIL_CONCATABLE_HPP
#define HAMON_RANGES_ADAPTORS_DETAIL_CONCATABLE_HPP

#include <hamon/ranges/adaptors/detail/concat_reference_t.hpp>
#include <hamon/ranges/adaptors/detail/concat_value_t.hpp>
#include <hamon/ranges/adaptors/detail/concat_rvalue_reference_t.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/concepts/common_reference_with.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/detail/all.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

// [range.concat.view]/1
#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Ref, typename RRef, typename It>
HAMON_CONCEPT_OR_BOOL concat_indirectly_readable_impl =
	requires (const It it)
	{
		{ *it } -> hamon::convertible_to<Ref>;
		{ hamon::ranges::iter_move(it) } -> hamon::convertible_to<RRef>;
	};

template <typename... Rs>
HAMON_CONCEPT_OR_BOOL concat_indirectly_readable =
	hamon::common_reference_with<
		hamon::ranges::detail::concat_reference_t<Rs...>&&,
		hamon::ranges::detail::concat_value_t<Rs...>&> &&
	hamon::common_reference_with<
		hamon::ranges::detail::concat_reference_t<Rs...>&&,
		hamon::ranges::detail::concat_rvalue_reference_t<Rs...>&&> &&
	hamon::common_reference_with<
		hamon::ranges::detail::concat_rvalue_reference_t<Rs...>&&,
		hamon::ranges::detail::concat_value_t<Rs...> const&> &&
	(concat_indirectly_readable_impl<
		hamon::ranges::detail::concat_reference_t<Rs...>,
		hamon::ranges::detail::concat_rvalue_reference_t<Rs...>,
		hamon::ranges::iterator_t<Rs>> && ...);

#else

template <typename Ref, typename RRef, typename It>
struct concat_indirectly_readable_impl
{
private:
	template <typename Ref2, typename RRef2, typename It2,
		typename D = decltype(*hamon::declval<const It2>()),
		typename = hamon::enable_if_t<hamon::convertible_to<D, Ref2>>,
		typename E = decltype(hamon::ranges::iter_move(hamon::declval<const It2>())),
		typename = hamon::enable_if_t<hamon::convertible_to<E, RRef2>>
	>
	static auto test(int) -> hamon::true_type;

	template <typename...>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Ref, RRef, It>(0));
};

template <typename... Rs>
struct concat_indirectly_readable_impl2
{
private:
	template <typename... R2s,
		typename = hamon::enable_if_t<
			hamon::common_reference_with<
				hamon::ranges::detail::concat_reference_t<R2s...>&&,
				hamon::ranges::detail::concat_value_t<R2s...>&> &&
			hamon::common_reference_with<
				hamon::ranges::detail::concat_reference_t<R2s...>&&,
				hamon::ranges::detail::concat_rvalue_reference_t<R2s...>&&> &&
			hamon::common_reference_with<
				hamon::ranges::detail::concat_rvalue_reference_t<R2s...>&&,
				hamon::ranges::detail::concat_value_t<R2s...> const&> &&
			hamon::detail::all_v<concat_indirectly_readable_impl<
				hamon::ranges::detail::concat_reference_t<R2s...>,
				hamon::ranges::detail::concat_rvalue_reference_t<R2s...>,
				hamon::ranges::iterator_t<R2s>>::type::value...>
		>
	>
	static auto test(int) -> hamon::true_type;

	template <typename...>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Rs...>(0));
};

template <typename... Rs>
HAMON_CONCEPT_OR_BOOL concat_indirectly_readable =
	concat_indirectly_readable_impl2<Rs...>::type::value;

#endif


// [range.concat.view]/2
#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename... Rs>
HAMON_CONCEPT_OR_BOOL concatable =
	requires
	{
		typename hamon::ranges::detail::concat_reference_t<Rs...>;
		typename hamon::ranges::detail::concat_value_t<Rs...>;
		typename hamon::ranges::detail::concat_rvalue_reference_t<Rs...>;
	} && hamon::ranges::detail::concat_indirectly_readable<Rs...>;

#else

template <typename... Rs>
struct concatable_impl
{
private:
	template <typename... R2s,
		typename = hamon::ranges::detail::concat_reference_t<R2s...>,
		typename = hamon::ranges::detail::concat_value_t<R2s...>,
		typename = hamon::ranges::detail::concat_rvalue_reference_t<R2s...>,
		typename = hamon::enable_if_t<
			hamon::ranges::detail::concat_indirectly_readable<R2s...>
		>
	>
	static auto test(int) -> hamon::true_type;

	template <typename...>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Rs...>(0));
};

template <typename... Rs>
HAMON_CONCEPT_OR_BOOL concatable = concatable_impl<Rs...>::type::value;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_ADAPTORS_DETAIL_CONCATABLE_HPP
