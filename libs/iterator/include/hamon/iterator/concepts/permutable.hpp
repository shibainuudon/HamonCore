/**
 *	@file	permutable.hpp
 *
 *	@brief	permutable の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_PERMUTABLE_HPP
#define HAMON_ITERATOR_CONCEPTS_PERMUTABLE_HPP

#include <hamon/iterator/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_USE_STD_RANGES_ITERATOR)
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/concepts/indirectly_movable_storable.hpp>
#include <hamon/iterator/concepts/indirectly_swappable.hpp>
#include <hamon/type_traits/enable_if.hpp>
#endif

namespace hamon
{

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

using std::permutable;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Iter>
HAMON_CONCEPT_OR_BOOL permutable =
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
		typename = hamon::enable_if_t<hamon::forward_iterator<I2>>,
		typename = hamon::enable_if_t<hamon::indirectly_movable_storable<I2, I2>>,
		typename = hamon::enable_if_t<hamon::indirectly_swappable<I2, I2>>
	>
	static auto test(int) -> hamon::true_type;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace detail

template <typename Iter>
HAMON_CONCEPT_OR_BOOL permutable =
	detail::permutable_impl<Iter>::type::value;

#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_PERMUTABLE_HPP
