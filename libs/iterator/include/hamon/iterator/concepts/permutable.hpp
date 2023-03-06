/**
 *	@file	permutable.hpp
 *
 *	@brief	permutable の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_PERMUTABLE_HPP
#define HAMON_ITERATOR_CONCEPTS_PERMUTABLE_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

using std::permutable;

}	// namespace hamon

#else

#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/concepts/indirectly_movable_storable.hpp>
#include <hamon/iterator/concepts/indirectly_swappable.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept permutable =
	hamon::forward_iterator<Iter> &&
	hamon::indirectly_movable_storable<Iter, Iter> &&
	hamon::indirectly_swappable<Iter, Iter>;

#else

namespace detail
{

template <typename Iter>
struct permutable_impl
{
private:
	template <typename I2,
		typename = hamon::enable_if_t<hamon::forward_iterator<I2>::value>,
		typename = hamon::enable_if_t<hamon::indirectly_movable_storable<I2, I2>::value>,
		typename = hamon::enable_if_t<hamon::indirectly_swappable<I2, I2>::value>
	>
	static auto test(int) -> hamon::true_type;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace detail

template <typename Iter>
using permutable =
	typename detail::permutable_impl<Iter>::type;

#endif

}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename Iter>
using permutable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::permutable<Iter>>;
#else
	hamon::permutable<Iter>;
#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_PERMUTABLE_HPP
