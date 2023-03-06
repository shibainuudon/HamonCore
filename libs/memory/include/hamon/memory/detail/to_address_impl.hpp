/**
 *	@file	to_address_impl.hpp
 *
 *	@brief	to_address_impl を定義
 */

#ifndef HAMON_MEMORY_DETAIL_TO_ADDRESS_IMPL_HPP
#define HAMON_MEMORY_DETAIL_TO_ADDRESS_IMPL_HPP

#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/type_traits/is_function.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <utility>
#include <memory>

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

namespace hamon
{

namespace detail
{

namespace to_address_detail
{

template <typename T, typename = void>
struct has_pointer_traits_to_address
	: public hamon::false_type {};

template <typename T>
struct has_pointer_traits_to_address<T,
	hamon::void_t<
		decltype(std::pointer_traits<T>::to_address(std::declval<T const&>()))
	>
> : public hamon::true_type {};

template <typename T, typename = void>
struct has_operator_arrow
	: public hamon::false_type {};

template <typename T>
struct has_operator_arrow<T,
	hamon::void_t<
		decltype(std::declval<T const&>().operator->())
	>
> : public hamon::true_type {};

struct to_address_fn
{
private:
	template <typename T, typename = hamon::enable_if_t<!hamon::is_function<T>::value>>
	static HAMON_CONSTEXPR T*
	impl(T* p, hamon::detail::overload_priority<3>) HAMON_NOEXCEPT
	{
		return p;
	}

	template <typename Ptr, typename = hamon::enable_if_t<has_pointer_traits_to_address<Ptr>::value>>
	static HAMON_CONSTEXPR auto
	impl(const Ptr& p, hamon::detail::overload_priority<2>) HAMON_NOEXCEPT
	->decltype(std::pointer_traits<Ptr>::to_address(p))
	{
		return std::pointer_traits<Ptr>::to_address(p);
	}

	template <typename Ptr, typename = hamon::enable_if_t<has_operator_arrow<Ptr>::value>>
	static HAMON_CONSTEXPR auto
	impl(const Ptr& p, hamon::detail::overload_priority<0>) HAMON_NOEXCEPT
	->decltype(impl(p.operator->(), hamon::detail::overload_priority<3>{}))
	{
		return impl(p.operator->(), hamon::detail::overload_priority<3>{});
	}

	template <typename Ptr, typename = hamon::enable_if_t<has_operator_arrow<Ptr>::value>>
	static HAMON_CONSTEXPR auto
	impl(const Ptr& p, hamon::detail::overload_priority<1>) HAMON_NOEXCEPT
	->decltype(impl(p.operator->(), hamon::detail::overload_priority<3>{}))
	{
		return impl(p.operator->(), hamon::detail::overload_priority<3>{});
	}

public:
	template <typename T>
	HAMON_CONSTEXPR auto operator()(T const& p) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(p, hamon::detail::overload_priority<3>{}))
};

}	// namespace to_address_detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
to_address_detail::to_address_fn to_address_impl{};

}	// inline namespace cpo

}	// namespace detail

}	// namespace hamon

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

#endif // HAMON_MEMORY_DETAIL_TO_ADDRESS_IMPL_HPP
