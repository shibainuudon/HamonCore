/**
 *	@file	cpp17_copy_assignable.hpp
 *
 *	@brief	cpp17_copy_assignable の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_CPP17_COPY_ASSIGNABLE_HPP
#define HAMON_CONCEPTS_DETAIL_CPP17_COPY_ASSIGNABLE_HPP

#include <hamon/concepts/detail/cpp17_move_assignable.hpp>
#include <hamon/concepts/same_as.hpp>
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
concept cpp17_copy_assignable =
	hamon::detail::cpp17_move_assignable<T> &&
	requires(T& t, T const& v)
	{
		{ t = v } -> hamon::same_as<T&>;
	};

#else

template <typename T>
struct cpp17_copy_assignable_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<hamon::detail::cpp17_move_assignable<U>::value>,
		typename R = decltype(hamon::declval<U&>() = hamon::declval<U const&>())
	>
	static auto test(int) -> hamon::same_as<R, U&>;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using cpp17_copy_assignable =
	typename cpp17_copy_assignable_impl<T>::type;

#endif

template <typename T>
using cpp17_copy_assignable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::detail::cpp17_copy_assignable<T>>;
#else
	hamon::detail::cpp17_copy_assignable<T>;
#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_CPP17_COPY_ASSIGNABLE_HPP
