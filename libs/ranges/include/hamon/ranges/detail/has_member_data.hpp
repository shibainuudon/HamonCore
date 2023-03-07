/**
 *	@file	has_member_data.hpp
 *
 *	@brief	has_member_data の定義
 */

#ifndef HAMON_RANGES_DETAIL_HAS_MEMBER_DATA_HPP
#define HAMON_RANGES_DETAIL_HAS_MEMBER_DATA_HPP

#include <hamon/detail/decay_copy.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/remove_pointer.hpp>
#include <hamon/type_traits/is_pointer.hpp>
#include <hamon/type_traits/is_object.hpp>
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
concept pointer_to_object =
	hamon::is_pointer<T>::value &&
	hamon::is_object<hamon::remove_pointer_t<T>>::value;

template <typename T>
concept has_member_data =
	requires(T& t)
	{
		{ hamon::detail::decay_copy(t.data()) } -> pointer_to_object;
	};

#else

template <typename T>
struct has_member_data_impl
{
private:
	template <typename U,
		typename P = decltype(hamon::detail::decay_copy(hamon::declval<U&>().data()))>
	static auto test(int) -> hamon::conjunction<
		hamon::is_pointer<P>,
		hamon::is_object<hamon::remove_pointer_t<P>>
	>;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_member_data = typename has_member_data_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_HAS_MEMBER_DATA_HPP
