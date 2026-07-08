/**
 *	@file	uniform_random_bit_generator.hpp
 *
 *	@brief	uniform_random_bit_generator の定義
 */

#ifndef HAMON_RANDOM_CONCEPTS_UNIFORM_RANDOM_BIT_GENERATOR_HPP
#define HAMON_RANDOM_CONCEPTS_UNIFORM_RANDOM_BIT_GENERATOR_HPP

#include <hamon/concepts/invocable.hpp>
#include <hamon/concepts/unsigned_integral.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/invoke_result.hpp>
#include <hamon/config.hpp>

namespace hamon
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Gen>
concept uniform_random_bit_generator =
	hamon::invocable<Gen&> &&
	hamon::unsigned_integral<hamon::invoke_result_t<Gen&>> &&
	requires
	{
		{ Gen::min() } -> hamon::same_as<hamon::invoke_result_t<Gen&>>;
		{ Gen::max() } -> hamon::same_as<hamon::invoke_result_t<Gen&>>;
		requires hamon::bool_constant<(Gen::min() < Gen::max())>::value;
	};

#else

template <typename Gen>
struct uniform_random_bit_generator_impl
{
private:
	template <typename G,
		typename = hamon::enable_if_t<hamon::invocable<G&>>,
		typename = hamon::enable_if_t<hamon::unsigned_integral<hamon::invoke_result_t<G&>>>,
		typename = hamon::enable_if_t<hamon::same_as<decltype(G::min()), hamon::invoke_result_t<G&>>>,
		typename = hamon::enable_if_t<hamon::same_as<decltype(G::max()), hamon::invoke_result_t<G&>>>,
		typename = hamon::enable_if_t<hamon::bool_constant<(G::min() < G::max())>::value>
	>
	static auto test(int) -> hamon::true_type;

	template <typename G>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Gen>(0));
};

template <typename Gen>
using uniform_random_bit_generator =
	typename uniform_random_bit_generator_impl<Gen>::type;

#endif

}	// namespace hamon

#endif // HAMON_RANDOM_CONCEPTS_UNIFORM_RANDOM_BIT_GENERATOR_HPP
