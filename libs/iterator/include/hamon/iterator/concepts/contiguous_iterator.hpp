/**
 *	@file	contiguous_iterator.hpp
 *
 *	@brief	contiguous_iterator の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_CONTIGUOUS_ITERATOR_HPP
#define HAMON_ITERATOR_CONCEPTS_CONTIGUOUS_ITERATOR_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

using std::contiguous_iterator;

}	// namespace hamon

#else

#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/iterator/concepts/detail/iter_concept.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/contiguous_iterator_tag.hpp>
#include <hamon/concepts/derived_from.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/add_pointer.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/memory/to_address.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept contiguous_iterator =
	hamon::random_access_iterator<Iter> &&
	hamon::derived_from<hamon::detail::iter_concept<Iter>, hamon::contiguous_iterator_tag> &&
	std::is_lvalue_reference<hamon::iter_reference_t<Iter>>::value &&
	hamon::same_as<hamon::iter_value_t<Iter>, hamon::remove_cvref_t<hamon::iter_reference_t<Iter>>> &&
	requires(Iter const& i)
	{
		{ hamon::to_address(i) } -> hamon::same_as<hamon::add_pointer_t<hamon::iter_reference_t<Iter>>>;
	};

#else

namespace detail
{

template <typename Iter>
struct contiguous_iterator_impl
{
private:
	template <typename I2,
		typename = hamon::enable_if_t<
			hamon::random_access_iterator<I2>::value
		>,
		typename = hamon::enable_if_t<
			hamon::derived_from<
				hamon::detail::iter_concept<I2>,
				hamon::contiguous_iterator_tag
			>::value
		>,
		typename R = hamon::iter_reference_t<I2>,
		typename = hamon::enable_if_t<
			std::is_lvalue_reference<R>::value
		>,
		typename = hamon::enable_if_t<
			hamon::same_as<
				hamon::iter_value_t<I2>,
				hamon::remove_cvref_t<R>
			>::value
		>,
		typename P1 = decltype(hamon::to_address(std::declval<I2 const&>()))
	>
	static auto test(int) -> hamon::same_as<P1, hamon::add_pointer_t<R>>;

	template <typename I2>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace detail

template <typename Iter>
using contiguous_iterator =
	typename detail::contiguous_iterator_impl<Iter>::type;

#endif

}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename Iter>
using contiguous_iterator_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::contiguous_iterator<Iter>>;
#else
	hamon::contiguous_iterator<Iter>;
#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_CONTIGUOUS_ITERATOR_HPP
