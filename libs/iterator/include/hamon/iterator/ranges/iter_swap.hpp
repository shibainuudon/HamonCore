/**
 *	@file	iter_swap.hpp
 *
 *	@brief	iter_swap の定義
 */

#ifndef HAMON_ITERATOR_RANGES_ITER_SWAP_HPP
#define HAMON_ITERATOR_RANGES_ITER_SWAP_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{
namespace ranges
{

using std::ranges::iter_swap;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/iterator/concepts/indirectly_readable.hpp>
#include <hamon/iterator/concepts/indirectly_movable_storable.hpp>
#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/concepts/swap.hpp>
#include <hamon/concepts/swappable_with.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/config.hpp>
#include <utility>

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

namespace hamon
{

namespace ranges
{

namespace iter_swap_detail
{

#if defined(HAMON_MSVC) && (HAMON_MSVC < 1920)
void iter_swap();
#elif 0
void iter_swap(auto, auto) = delete;
#else
template <typename It1, typename It2>
void iter_swap(It1, It2) = delete;
#endif

template <typename X, typename Y>
HAMON_CXX14_CONSTEXPR hamon::iter_value_t<X>
iter_exchange_move(X&& x, Y&& y)
noexcept(
	noexcept(hamon::iter_value_t<X>(hamon::ranges::iter_move(x))) &&
	noexcept(*x = hamon::ranges::iter_move(y))
)
{
	hamon::iter_value_t<X> old(hamon::ranges::iter_move(x));
	*x = hamon::ranges::iter_move(y);
	return old;
}

struct iter_swap_fn
{
private:
	template <typename I1, typename I2
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<hamon::remove_cvref_t<I1>>::value ||
			hamon::detail::class_or_enum<hamon::remove_cvref_t<I2>>::value
		>
#endif
	>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires
		hamon::detail::class_or_enum<hamon::remove_cvref_t<I1>> ||
		hamon::detail::class_or_enum<hamon::remove_cvref_t<I2>>
#endif
	static HAMON_CXX14_CONSTEXPR auto
	impl(hamon::detail::overload_priority<2>, I1&& i1, I2&& i2)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(iter_swap(std::forward<I1>(i1), std::forward<I2>(i2)))

	template <typename I1, typename I2
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, typename = hamon::enable_if_t<
			hamon::indirectly_readable<I1>::value &&
			hamon::indirectly_readable<I2>::value &&
			hamon::swappable_with<hamon::iter_reference_t<I1>, hamon::iter_reference_t<I2>>::value
		>
#endif
	>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires
		hamon::indirectly_readable<I1> &&
		hamon::indirectly_readable<I2> &&
		hamon::swappable_with<hamon::iter_reference_t<I1>, hamon::iter_reference_t<I2>>
#endif
	static HAMON_CXX14_CONSTEXPR auto
	impl(hamon::detail::overload_priority<1>, I1&& i1, I2&& i2)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(ranges::swap(*i1, *i2))

	template <typename I1, typename I2
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, typename = hamon::enable_if_t<
			hamon::indirectly_movable_storable<I1, I2>::value &&
			hamon::indirectly_movable_storable<I2, I1>::value
		>
#endif
	>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires
		hamon::indirectly_movable_storable<I1, I2> &&
		hamon::indirectly_movable_storable<I2, I1>
#endif
	static HAMON_CXX14_CONSTEXPR void
	impl(hamon::detail::overload_priority<0>, I1&& i1, I2&& i2)
		HAMON_NOEXCEPT_IF_EXPR(*i1 = iter_exchange_move(i2, i1))
	{
		*i1 = iter_exchange_move(i2, i1);
	}

public:
	template <typename I1, typename I2>
	HAMON_CXX14_CONSTEXPR auto operator()(I1&& i1, I2&& i2) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(impl(
			hamon::detail::overload_priority<2>{},
			std::forward<I1>(i1),
			std::forward<I2>(i2)))
};

}	// namespace iter_swap_detail

inline namespace cpo
{

// Customization point object
HAMON_INLINE_VAR HAMON_CONSTEXPR
iter_swap_detail::iter_swap_fn iter_swap{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

#endif

#endif // HAMON_ITERATOR_RANGES_ITER_SWAP_HPP
