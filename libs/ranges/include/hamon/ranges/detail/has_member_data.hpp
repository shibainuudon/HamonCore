/**
 *	@file	has_member_data.hpp
 *
 *	@brief	has_member_data の定義
 */

#ifndef HAMON_RANGES_DETAIL_HAS_MEMBER_DATA_HPP
#define HAMON_RANGES_DETAIL_HAS_MEMBER_DATA_HPP

#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/remove_pointer.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

namespace ranges
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept pointer_to_object =
	std::is_pointer<T>::value &&
	std::is_object<hamon::remove_pointer_t<T>>::value;

template <typename T>
concept has_member_data =
	std::is_lvalue_reference<T>::value &&
	requires(T t) { { t.data() } -> pointer_to_object; };

#else

template <typename T>
struct has_member_data_impl
{
private:
	template <typename U, typename P = decltype(std::declval<U&>().data())>
	static auto test(int) -> hamon::conjunction<
		std::is_lvalue_reference<U>,
		std::is_pointer<P>,
		std::is_object<hamon::remove_pointer_t<P>>
	>;

	template <typename U>
	static auto test(...) -> std::false_type;

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
