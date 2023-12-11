/**
 *	@file	range_adaptor_closure.hpp
 *
 *	@brief	range_adaptor_closure の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_RANGE_ADAPTOR_CLOSURE_HPP
#define HAMON_RANGES_ADAPTORS_RANGE_ADAPTOR_CLOSURE_HPP

#include <hamon/ranges/config.hpp>

#if 0 && defined(HAMON_USE_STD_RANGES) && \
	(defined(__cpp_lib_ranges) && (__cpp_lib_ranges >= 202202L))	// P2387R3

namespace hamon {
namespace ranges {

using std::ranges::range_adaptor_closure;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/concepts/range.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/derived_from.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_class.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

namespace detail {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

template <typename D>
struct range_adaptor_closure_base {};

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept range_adaptor_closure_object =
	!hamon::ranges::range<hamon::remove_cvref_t<T>> &&
	hamon::derived_from<hamon::remove_cvref_t<T>, range_adaptor_closure_base<hamon::remove_cvref_t<T>>>;

template <typename T>
using range_adaptor_closure_object_t = hamon::bool_constant<range_adaptor_closure_object<T>>;

#else

template <typename T>
using range_adaptor_closure_object = hamon::conjunction<
	hamon::negation<hamon::ranges::range<hamon::remove_cvref_t<T>>>,
	hamon::derived_from<hamon::remove_cvref_t<T>, range_adaptor_closure_base<hamon::remove_cvref_t<T>>>
>;

template <typename T>
using range_adaptor_closure_object_t = range_adaptor_closure_object<T>;

#endif

template <typename ClosureLhs, typename ClosureRhs,
	typename = hamon::enable_if_t<hamon::conjunction<
		range_adaptor_closure_object_t<ClosureLhs>,
		range_adaptor_closure_object_t<ClosureRhs>
	>::value>
>
struct range_adaptor_closure_t
	: public range_adaptor_closure_base<range_adaptor_closure_t<ClosureLhs, ClosureRhs>>
{
private:
	HAMON_NO_UNIQUE_ADDRESS ClosureLhs m_lhs;
	HAMON_NO_UNIQUE_ADDRESS ClosureRhs m_rhs;

public:
	template <typename T1, typename T2>
	HAMON_CXX11_CONSTEXPR explicit
	range_adaptor_closure_t(T1&& lhs, T2&& rhs)
		HAMON_NOEXCEPT_IF(
			hamon::is_nothrow_constructible<ClosureLhs, T1>::value &&
			hamon::is_nothrow_constructible<ClosureRhs, T2>::value)
		: m_lhs(hamon::forward<T1>(lhs))
		, m_rhs(hamon::forward<T2>(rhs))
	{}

	template <typename T>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto
	operator()(T&& v) &
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			m_rhs(m_lhs(hamon::forward<T>(v))))

	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(T&& v) const&
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			m_rhs(m_lhs(hamon::forward<T>(v))))

	template <typename T>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto
	operator()(T&& v) &&
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::move(m_rhs)(hamon::move(m_lhs)(hamon::forward<T>(v))))

	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(T&& v) const&&
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::move(m_rhs)(hamon::move(m_lhs)(hamon::forward<T>(v))))
};

template <
	HAMON_CONSTRAINED_PARAM(range_adaptor_closure_object, Lhs),
	HAMON_CONSTRAINED_PARAM(range_adaptor_closure_object, Rhs),
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::constructible_from_t<hamon::remove_cvref_t<Lhs>, Lhs>,
		hamon::constructible_from_t<hamon::remove_cvref_t<Rhs>, Rhs>
	>::value>
>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
operator|(Lhs&& lhs, Rhs&& rhs)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		range_adaptor_closure_t<Lhs, Rhs>{hamon::forward<Lhs>(lhs), hamon::forward<Rhs>(rhs)})

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::range, Lhs),
	HAMON_CONSTRAINED_PARAM(range_adaptor_closure_object, Rhs)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
operator|(Lhs&& lhs, Rhs&& rhs) 
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::invoke(hamon::forward<Rhs>(rhs), hamon::forward<Lhs>(lhs)))

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

// [range.adaptor.object], range adaptor objects

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <typename D>
	requires hamon::is_class_v<D> &&
		hamon::same_as<D, hamon::remove_cv_t<D>>
#else
template <typename D,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::is_class<D>,
		hamon::same_as<D, hamon::remove_cv_t<D>>
	>::value>
>
#endif
class range_adaptor_closure
	: public detail::range_adaptor_closure_base<D>
{};

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ADAPTORS_RANGE_ADAPTOR_CLOSURE_HPP
