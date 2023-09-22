/**
 *	@file	indirectly_readable.hpp
 *
 *	@brief	indirectly_readable の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_INDIRECTLY_READABLE_HPP
#define HAMON_ITERATOR_CONCEPTS_INDIRECTLY_READABLE_HPP

#include <hamon/iterator/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_USE_STD_RANGES_ITERATOR)
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/iter_rvalue_reference_t.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/common_reference_with.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/enable_if.hpp>
#endif

namespace hamon
{

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

using std::indirectly_readable;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

namespace detail
{

template <typename In>
concept indirectly_readable_impl =
	requires
	{
		typename hamon::iter_value_t<In>;
		typename hamon::iter_reference_t<In>;
		typename hamon::iter_rvalue_reference_t<In>;
		requires hamon::same_as<hamon::iter_reference_t<In const>, hamon::iter_reference_t<In>>;
		requires hamon::same_as<hamon::iter_rvalue_reference_t<In const>, hamon::iter_rvalue_reference_t<In>>;
	} &&
	hamon::common_reference_with<hamon::iter_reference_t<In>&&, hamon::iter_value_t<In>&> &&
	hamon::common_reference_with<hamon::iter_reference_t<In>&&, hamon::iter_rvalue_reference_t<In>&&> &&
	hamon::common_reference_with<hamon::iter_rvalue_reference_t<In>&&, hamon::iter_value_t<In> const&>;

}	// namespace detail

template <typename In>
concept indirectly_readable =
	detail::indirectly_readable_impl<hamon::remove_cvref_t<In>>;

#else

namespace detail
{

template <typename In>
struct indirectly_readable_impl
{
private:
	template <typename U,
		typename V   = hamon::iter_value_t<U>,
		typename R   = hamon::iter_reference_t<U>,
		typename RR  = hamon::iter_rvalue_reference_t<U>,
		typename RC  = hamon::iter_reference_t<U const>,
		typename RRC = hamon::iter_rvalue_reference_t<U const>,
		typename = hamon::enable_if_t<hamon::same_as<RC, R>::value>,
		typename = hamon::enable_if_t<hamon::same_as<RRC, RR>::value>,
		typename = hamon::enable_if_t<hamon::common_reference_with<R&&, V&>::value>,
		typename = hamon::enable_if_t<hamon::common_reference_with<R&&, RR&&>::value>,
		typename = hamon::enable_if_t<hamon::common_reference_with<RR&&, V const&>::value>
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<In>(0));
};

}	// namespace detail

template <typename In>
using indirectly_readable =
	typename detail::indirectly_readable_impl<hamon::remove_cvref_t<In>>::type;

#endif

template <typename In>
using indirectly_readable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::indirectly_readable<In>>;
#else
	hamon::indirectly_readable<In>;
#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_INDIRECTLY_READABLE_HPP
