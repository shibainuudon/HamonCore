/**
 *	@file	cpp17_move_assignable.hpp
 *
 *	@brief	cpp17_move_assignable の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_CPP17_MOVE_ASSIGNABLE_HPP
#define HAMON_CONCEPTS_DETAIL_CPP17_MOVE_ASSIGNABLE_HPP

#include <hamon/concepts/same_as.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_function.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept cpp17_move_assignable =
#if defined(HAMON_MSVC)
	!hamon::is_function<hamon::remove_reference_t<T>>::value &&
#endif
	requires(T& t, T&& rv)
	{
		{ t = hamon::forward<T>(rv) } -> hamon::same_as<T&>;
	};

#else

template <typename T>
struct cpp17_move_assignable_impl
{
private:
	template <typename U,
		typename R = decltype(hamon::declval<U&>() = hamon::declval<U&&>())
	>
	static auto test(int) -> hamon::same_as<R, U&>;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using cpp17_move_assignable =
	typename cpp17_move_assignable_impl<T>::type;

#endif

template <typename T>
using cpp17_move_assignable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::detail::cpp17_move_assignable<T>>;
#else
	hamon::detail::cpp17_move_assignable<T>;
#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_CPP17_MOVE_ASSIGNABLE_HPP
