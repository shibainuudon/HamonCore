/**
 *	@file	predicate.hpp
 *
 *	@brief	predicate の定義
 */

#ifndef HAMON_CONCEPTS_PREDICATE_HPP
#define HAMON_CONCEPTS_PREDICATE_HPP

#include <hamon/concepts/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/regular_invocable.hpp>
#include <hamon/concepts/detail/boolean_testable.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/invoke_result.hpp>
#endif

namespace hamon
{

// 18.7.4 Concept predicate	[concept.predicate]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::predicate;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Fn, typename... Args>
concept predicate =
	hamon::regular_invocable<Fn, Args...> &&
	detail::boolean_testable<hamon::invoke_result_t<Fn, Args...>>;

#else

namespace detail
{

template <typename Fn, typename... Args>
struct predicate_impl
{
private:
	template <typename U, typename... As>
	static auto test(int) -> hamon::conjunction<
		hamon::regular_invocable<U, As...>,
		detail::boolean_testable<hamon::invoke_result_t<U, As...>>
	>;

	template <typename U, typename... As>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Fn, Args...>(0));
};

}	// namespace detail

template <typename Fn, typename... Args>
using predicate = typename detail::predicate_impl<Fn, Args...>::type;

#endif

template <typename Fn, typename... Args>
using predicate_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::predicate<Fn, Args...>>;
#else
	hamon::predicate<Fn, Args...>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_PREDICATE_HPP
