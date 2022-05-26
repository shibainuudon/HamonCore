/**
 *	@file	sentinel_for.hpp
 *
 *	@brief	sentinel_for の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_SENTINEL_FOR_HPP
#define HAMON_ITERATOR_CONCEPTS_SENTINEL_FOR_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

using std::sentinel_for;

}	// namespace hamon

#else

#include <hamon/concepts/semiregular.hpp>
#include <hamon/concepts/detail/weakly_eq_cmp_with.hpp>
#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Sent, typename Iter>
concept sentinel_for =
	hamon::semiregular<Sent> &&
	hamon::input_or_output_iterator<Iter> &&
	hamon::detail::weakly_eq_cmp_with<Sent, Iter>;

#else

namespace detail
{

template <typename Sent, typename Iter>
struct sentinel_for_impl
{
private:
	template <typename S2, typename I2,
		typename = hamon::enable_if_t<hamon::semiregular<S2>::value>,
		typename = hamon::enable_if_t<hamon::input_or_output_iterator<I2>::value>,
		typename = hamon::enable_if_t<hamon::detail::weakly_eq_cmp_with<S2, I2>::value>
	>
	static auto test(int) -> std::true_type;

	template <typename S2, typename I2>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<Sent, Iter>(0));
};

}	// namespace detail

template <typename Sent, typename Iter>
using sentinel_for =
	typename detail::sentinel_for_impl<Sent, Iter>::type;

#endif

}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename Sent, typename Iter>
using sentinel_for_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::sentinel_for<Sent, Iter>>;
#else
	hamon::sentinel_for<Sent, Iter>;
#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_SENTINEL_FOR_HPP
