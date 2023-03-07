/**
 *	@file	has_member_rbegin.hpp
 *
 *	@brief	has_member_rbegin の定義
 */

#ifndef HAMON_RANGES_DETAIL_HAS_MEMBER_RBEGIN_HPP
#define HAMON_RANGES_DETAIL_HAS_MEMBER_RBEGIN_HPP

#include <hamon/detail/decay_copy.hpp>
#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_member_rbegin =
	requires(T& t)
	{
		{ hamon::detail::decay_copy(t.rbegin()) } -> hamon::input_or_output_iterator;
	};

#else

template <typename T>
struct has_member_rbegin_impl
{
private:
	template <typename U,
		typename B = decltype(hamon::detail::decay_copy(hamon::declval<U&>().rbegin()))
	>
	static auto test(int) -> hamon::input_or_output_iterator<B>;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_member_rbegin = typename has_member_rbegin_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_HAS_MEMBER_RBEGIN_HPP
