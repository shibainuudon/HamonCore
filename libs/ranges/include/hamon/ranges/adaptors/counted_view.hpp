/**
 *	@file	counted_view.hpp
 *
 *	@brief	views::counted の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_COUNTED_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_COUNTED_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {
namespace views {

using std::ranges::views::counted;

}	// namespace views
}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/iterator/counted_iterator.hpp>
#include <hamon/iterator/make_counted_iterator.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/memory/to_address.hpp>
#include <hamon/span.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_pointer.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <memory>

namespace hamon {
namespace ranges {
namespace views {

namespace detail {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

// 26.7.18 Counted view[range.counted]

struct counted_fn
{
private:
	template <typename T, typename = void>
	struct has_pointer_traits_to_address
		: public hamon::false_type {};

	template <typename T>
	struct has_pointer_traits_to_address<T,
		hamon::void_t<
			decltype(std::pointer_traits<T>::to_address(hamon::declval<T const&>()))
		>
	> : public hamon::true_type {};

	template <typename T, typename = void>
	struct has_operator_arrow
		: public hamon::false_type {};

	template <typename T>
	struct has_operator_arrow<T,
		hamon::void_t<
			decltype(hamon::declval<T const&>().operator->())
		>
	> : public hamon::true_type {};

	template <typename T>
	using is_invocable_to_address =
		hamon::disjunction<
			hamon::is_pointer<T>,
			has_pointer_traits_to_address<T>,
			has_operator_arrow<T>
		>;

	// std::to_address は標準の実装だとSFINAE-friendlyでないので、
	// 先に、呼び出し可能かどうか判定する必要がある。

	// [range.counted]/2.1
	template <HAMON_CONSTRAINED_PARAM(hamon::contiguous_iterator, It),
		typename = hamon::enable_if_t<is_invocable_to_address<It>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(It it, hamon::iter_difference_t<It> n, hamon::detail::overload_priority<2>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::make_span(hamon::to_address(it), static_cast<hamon::size_t>(n)))

	// [range.counted]/2.2
	template <HAMON_CONSTRAINED_PARAM(hamon::random_access_iterator, It)>
	static HAMON_CXX11_CONSTEXPR auto
	impl(It it, hamon::iter_difference_t<It> n, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::ranges::make_subrange(it, it + n))

	// [range.counted]/2.3
	template <typename It>
	static HAMON_CXX11_CONSTEXPR auto
	impl(It it, hamon::iter_difference_t<It> n, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::ranges::make_subrange(
				hamon::make_counted_iterator(hamon::move(it), n),
				hamon::default_sentinel_t{}))

public:
	template <typename E, typename F,
		typename T = hamon::decay_t<E>,
		typename D = hamon::iter_difference_t<T>,
		typename = hamon::enable_if_t<
			hamon::input_or_output_iterator_t<T>::value &&
			hamon::convertible_to_t<F, D>::value
		>
	>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(E&& e, F&& f) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(impl(
			hamon::forward<E>(e),
			hamon::forward<F>(f),
			hamon::detail::overload_priority<2>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

} // namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::counted_fn counted{};

}	// inline namespace cpo

}	// namespace views
}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ADAPTORS_COUNTED_VIEW_HPP
