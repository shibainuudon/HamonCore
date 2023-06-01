/**
 *	@file	cpp17_copy_constructible.hpp
 *
 *	@brief	cpp17_copy_constructible の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_CPP17_COPY_CONSTRUCTIBLE_HPP
#define HAMON_CONCEPTS_DETAIL_CPP17_COPY_CONSTRUCTIBLE_HPP

#include <hamon/concepts/detail/cpp17_move_constructible.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept cpp17_copy_constructible =
	hamon::detail::cpp17_move_constructible<T> &&
	requires(T const& v)
	{
		{ T(v) };
	};

#else

template <typename T>
struct cpp17_copy_constructible_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<hamon::detail::cpp17_move_constructible<U>::value>,
		typename = decltype(U(hamon::declval<U const&>()))
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using cpp17_copy_constructible =
	typename cpp17_copy_constructible_impl<T>::type;

#endif

template <typename T>
using cpp17_copy_constructible_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::detail::cpp17_copy_constructible<T>>;
#else
	hamon::detail::cpp17_copy_constructible<T>;
#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_CPP17_COPY_CONSTRUCTIBLE_HPP
