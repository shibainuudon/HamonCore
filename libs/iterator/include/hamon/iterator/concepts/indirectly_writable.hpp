/**
 *	@file	indirectly_writable.hpp
 *
 *	@brief	indirectly_writable の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_INDIRECTLY_WRITABLE_HPP
#define HAMON_ITERATOR_CONCEPTS_INDIRECTLY_WRITABLE_HPP

#include <hamon/iterator/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_USE_STD_RANGES_ITERATOR)
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/declval.hpp>
#endif

namespace hamon
{

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

using std::indirectly_writable;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Out, typename T>
concept indirectly_writable =
	requires(Out&& o, T&& t)
	{
		*o = hamon::forward<T>(t);
		*hamon::forward<Out>(o) = hamon::forward<T>(t);
		const_cast<hamon::iter_reference_t<Out> const&&>(*o) = hamon::forward<T>(t);
		const_cast<hamon::iter_reference_t<Out> const&&>(*hamon::forward<Out>(o)) = hamon::forward<T>(t);
	};

#else

namespace detail
{

template <typename Out, typename T>
struct indirectly_writable_impl
{
private:
	template <typename Out2, typename T2,
		typename R = hamon::iter_reference_t<Out2> const&&,
		typename = decltype(*hamon::declval<Out2&>()  = hamon::declval<T2&&>()),
		typename = decltype(*hamon::declval<Out2&&>() = hamon::declval<T2&&>()),
		typename = decltype(const_cast<R>(*hamon::declval<Out2&>())  = hamon::declval<T2&&>()),
		typename = decltype(const_cast<R>(*hamon::declval<Out2&&>()) = hamon::declval<T2&&>())
	>
	static auto test(int) -> hamon::true_type;

	template <typename Out2, typename T2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Out, T>(0));
};

}	// namespace detail

template <typename Out, typename T>
using indirectly_writable =
	typename detail::indirectly_writable_impl<Out, T>::type;

#endif

template <typename Out, typename T>
using indirectly_writable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::indirectly_writable<Out, T>>;
#else
	hamon::indirectly_writable<Out, T>;
#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_INDIRECTLY_WRITABLE_HPP
