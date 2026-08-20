/**
 *	@file	default_initializable.hpp
 *
 *	@brief	default_initializable の定義
 */

#ifndef HAMON_CONCEPTS_DEFAULT_INITIALIZABLE_HPP
#define HAMON_CONCEPTS_DEFAULT_INITIALIZABLE_HPP

#include <hamon/concepts/constructible_from.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 18.4.12 Concept default_initializable	[concept.default.init]

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
HAMON_CONCEPT_OR_BOOL default_initializable =
	hamon::constructible_from<T> &&
	requires
	{
		T{};
		(void) ::new T;
	};

#else

namespace detail
{

template <typename T>
struct default_initializable_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<hamon::constructible_from<U>>,
		typename = decltype(U{}),
		typename = decltype((void) ::new U)
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
HAMON_CONCEPT_OR_BOOL default_initializable =
	detail::default_initializable_impl<T>::type::value;

#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_DEFAULT_INITIALIZABLE_HPP
