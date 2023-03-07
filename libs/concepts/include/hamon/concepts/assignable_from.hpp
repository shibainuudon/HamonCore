/**
 *	@file	assignable_from.hpp
 *
 *	@brief	assignable_from の定義
 */

#ifndef HAMON_CONCEPTS_ASSIGNABLE_FROM_HPP
#define HAMON_CONCEPTS_ASSIGNABLE_FROM_HPP

#include <hamon/concepts/config.hpp>

#if defined(HAMON_USE_STD_CONCEPTS)

namespace hamon
{

using std::assignable_from;

}	// namespace hamon

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

#include <hamon/concepts/common_reference_with.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/detail/cref.hpp>
#include <hamon/type_traits/is_lvalue_reference.hpp>
#include <hamon/utility/forward.hpp>

namespace hamon
{

template <typename Lhs, typename Rhs>
concept assignable_from =
	hamon::is_lvalue_reference<Lhs>::value &&
	hamon::common_reference_with<detail::cref<Lhs>, detail::cref<Rhs>> &&
	requires(Lhs lhs, Rhs&& rhs)
	{
		{ lhs = hamon::forward<Rhs>(rhs) } -> hamon::same_as<Lhs>;
	};

}	// namespace hamon

#else

#include <hamon/concepts/common_reference_with.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/detail/cref.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_lvalue_reference.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{

namespace detail
{

template <typename Lhs, typename Rhs>
struct assignable_from_impl
{
private:
	template <typename L, typename R,
		typename = hamon::enable_if_t<hamon::is_lvalue_reference<L>::value>,
		typename = hamon::enable_if_t<hamon::common_reference_with<detail::cref<L>, detail::cref<R>>::value>,
		typename T = decltype(hamon::declval<L&>() = hamon::declval<R&&>())
	>
	static auto test(int) -> hamon::same_as<T, L>;

	template <typename L, typename R>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Lhs, Rhs>(0));
};

}	// namespace detail

template <typename Lhs, typename Rhs>
using assignable_from =
	typename detail::assignable_from_impl<Lhs, Rhs>::type;

}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename Lhs, typename Rhs>
using assignable_from_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::assignable_from<Lhs, Rhs>>;
#else
	hamon::assignable_from<Lhs, Rhs>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_ASSIGNABLE_FROM_HPP
