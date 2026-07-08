/**
 *	@file	cpp17_move_constructible.hpp
 *
 *	@brief	cpp17_move_constructible の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_CPP17_MOVE_CONSTRUCTIBLE_HPP
#define HAMON_CONCEPTS_DETAIL_CPP17_MOVE_CONSTRUCTIBLE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
HAMON_CONCEPT_OR_BOOL cpp17_move_constructible =
	requires(T&& rv)
	{
		{ T(hamon::forward<T>(rv)) };
	};

#else

template <typename T>
struct cpp17_move_constructible_impl
{
private:
	template <typename U,
		typename = decltype(U(hamon::declval<U&&>()))
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
HAMON_CONCEPT_OR_BOOL cpp17_move_constructible =
	cpp17_move_constructible_impl<T>::type::value;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_CPP17_MOVE_CONSTRUCTIBLE_HPP
