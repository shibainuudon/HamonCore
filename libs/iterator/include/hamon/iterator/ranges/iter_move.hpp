/**
 *	@file	iter_move.hpp
 *
 *	@brief	iter_move の定義
 */

#ifndef HAMON_ITERATOR_RANGES_ITER_MOVE_HPP
#define HAMON_ITERATOR_RANGES_ITER_MOVE_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{
namespace ranges
{

using std::ranges::iter_move;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/concepts/detail/dereferenceable.hpp>
#include <hamon/iterator/concepts/detail/is_void_pointer.hpp>
#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/is_lvalue_reference.hpp>
#include <hamon/config.hpp>
#include <utility>

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

namespace hamon
{

namespace ranges
{

namespace iter_move_detail
{

void iter_move();

struct iter_move_fn
{
private:
	// (1) if remove_cvref_t<T> is a class or enumeration type and
	//        iter_move(forward<T>(t)) is well-formed in unevaluated context
	template <typename T
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, typename = hamon::enable_if_t<hamon::detail::class_or_enum<hamon::remove_reference_t<T>>::value>
#endif
	>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires hamon::detail::class_or_enum<hamon::remove_reference_t<T>>
#endif
	static HAMON_CXX14_CONSTEXPR auto impl(hamon::detail::overload_priority<2>, T&& t)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(iter_move(std::forward<T>(t)))

	// (2) otherwise, if *forward<T>(t) is well-formed and is an lvalue
	template <typename T
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, typename = hamon::enable_if_t<hamon::is_lvalue_reference<hamon::iter_reference_t<T>>::value>
#endif
	>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires hamon::is_lvalue_reference<hamon::iter_reference_t<T>>::value
#endif
	static HAMON_CXX14_CONSTEXPR auto impl(hamon::detail::overload_priority<1>, T&& t)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(std::move(*std::forward<T>(t)))

	// (3) otherwise, if *forward<T>(t) is well-formed and is an rvalue
	template <typename T
		, typename = hamon::enable_if_t<!hamon::detail::is_void_pointer<T>::value>
	>
//	requires hamon::is_rvalue_reference<hamon::iter_reference_t<T>>::value
	static HAMON_CXX14_CONSTEXPR auto impl(hamon::detail::overload_priority<0>, T&& t)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(*std::forward<T>(t))

public:
	template <typename T>
	HAMON_CXX14_CONSTEXPR auto operator()(T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(hamon::detail::overload_priority<2>{}, std::forward<T>(t)))
};

}	// namespace iter_move_detail

inline namespace cpo
{

// Customization point object
HAMON_INLINE_VAR HAMON_CONSTEXPR
iter_move_detail::iter_move_fn iter_move{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

#endif

#endif // HAMON_ITERATOR_RANGES_ITER_MOVE_HPP
