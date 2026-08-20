/**
 *	@file	predicate.hpp
 *
 *	@brief	predicate の定義
 */

#ifndef HAMON_CONCEPTS_PREDICATE_HPP
#define HAMON_CONCEPTS_PREDICATE_HPP

#include <hamon/concepts/regular_invocable.hpp>
#include <hamon/concepts/detail/boolean_testable.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/invoke_result.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 18.7.4 Concept predicate	[concept.predicate]

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Fn, typename... Args>
HAMON_CONCEPT_OR_BOOL predicate =
	hamon::regular_invocable<Fn, Args...> &&
	detail::boolean_testable<hamon::invoke_result_t<Fn, Args...>>;

#else

namespace detail
{

template <typename Fn, typename... Args>
struct predicate_impl
{
private:
	template <typename U, typename... As,
		typename = hamon::enable_if_t<
			hamon::regular_invocable<U, As...> &&
			detail::boolean_testable<hamon::invoke_result_t<U, As...>>
		>
	>
	static auto test(int) -> hamon::true_type;

	template <typename U, typename... As>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Fn, Args...>(0));
};

}	// namespace detail

template <typename Fn, typename... Args>
HAMON_CONCEPT_OR_BOOL predicate =
	detail::predicate_impl<Fn, Args...>::type::value;

#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_PREDICATE_HPP
