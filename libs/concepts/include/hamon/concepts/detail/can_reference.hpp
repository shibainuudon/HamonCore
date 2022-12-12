/**
 *	@file	can_reference.hpp
 *
 *	@brief	can_reference の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_CAN_REFERENCE_HPP
#define HAMON_CONCEPTS_DETAIL_CAN_REFERENCE_HPP

#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

namespace detail
{

template <typename T>
using with_ref = T&;

/**
 *	@brief	Tがlvalue referenceを付けられる型であることを要求するコンセプト
 * 
 *	@note	実質的に、Tがvoidでないことを要求している
 */

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept can_reference = requires { typename with_ref<T>; };

#else

template <typename T>
struct can_reference_impl
{
private:
	template <typename U, typename = with_ref<U>>
	static auto test(int) -> std::true_type;

	template <typename U>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using can_reference =
	typename detail::can_reference_impl<T>::type;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_CAN_REFERENCE_HPP
