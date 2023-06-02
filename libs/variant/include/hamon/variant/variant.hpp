/**
 *	@file	variant.hpp
 *
 *	@brief	variant の定義
 */

#ifndef HAMON_VARIANT_VARIANT_HPP
#define HAMON_VARIANT_VARIANT_HPP

#include <hamon/variant/config.hpp>

#if defined(HAMON_USE_STD_VARIANT)

namespace hamon
{

using std::variant;

}	// namespace hamon

#else

#include <hamon/variant/detail/variant_swap.hpp>
#include <hamon/variant/detail/select_overload.hpp>
#include <hamon/variant/detail/find_index.hpp>
#include <hamon/variant/detail/exactly_once.hpp>
#include <hamon/variant/detail/visit_at.hpp>
#include <hamon/variant/variant_fwd.hpp>
#include <hamon/compare/concepts/three_way_comparable.hpp>
#include <hamon/compare/common_comparison_category.hpp>
#include <hamon/compare/compare_three_way_result.hpp>
#include <hamon/compare/compare_three_way.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/concepts/detail/cpp17_destructible.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/functional/ranges/not_equal_to.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <hamon/functional/ranges/less_equal.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <hamon/functional/ranges/greater_equal.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_assignable.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_swappable.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_swappable.hpp>
#include <hamon/type_traits/nth.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/in_place_type.hpp>
#include <hamon/utility/in_place_index.hpp>
#include <hamon/config.hpp>
#include <initializer_list>

namespace hamon
{

template <typename... Types>
class variant
	: private variant_detail::variant_swap<Types...>
{
private:
	using base_type = variant_detail::variant_swap<Types...>;

public:
    static_assert(hamon::conjunction<hamon::detail::cpp17_destructible_t<Types>...>::value,
        "All types in Types shall meet the Cpp17Destructible requirements (Table 36)."
        "[variant.variant]/2.");

    static_assert(sizeof...(Types) != 0,
        "A program that instantiates the definition of variant with no template arguments is ill-formed."
        "[variant.variant]/3.");

	// [variant.ctor], constructors

	template <typename T0 = hamon::nth_t<0, Types...>,
		typename = hamon::enable_if_t<
			hamon::is_default_constructible<T0>::value>						// [variant.ctor]/2
	>
	HAMON_CXX11_CONSTEXPR variant()
		HAMON_NOEXCEPT_IF((hamon::is_nothrow_default_constructible<T0>::value))		// [variant.ctor]/6
		: base_type(hamon::in_place_index_t<0>{})							// [variant.ctor]/3
	{}
	
	HAMON_CXX11_CONSTEXPR variant(variant const&) = default;
	HAMON_CXX11_CONSTEXPR variant(variant&&) = default;

	template <typename T,
		typename = hamon::enable_if_t<sizeof...(Types) != 0>,					// [variant.ctor]/15.1
		typename = hamon::enable_if_t<!hamon::is_same<hamon::remove_cvref_t<T>, variant>::value>,	// [variant.ctor]/15.2
		typename = hamon::enable_if_t<!hamon::is_in_place_type<T>::value>,		// [variant.ctor]/15.3
		typename = hamon::enable_if_t<!hamon::is_in_place_index<T>::value>,		// [variant.ctor]/15.3
		hamon::size_t J = variant_detail::select_overload<T, Types...>::value,	// [variant.ctor]/15.5
		typename Tj = hamon::nth_t<J, Types...>,
		typename = hamon::enable_if_t<
			variant_detail::exactly_once<Tj, Types...>::value>,
		typename = hamon::enable_if_t<hamon::is_constructible<Tj, T>::value>	// [variant.ctor]/15.4
	>
	HAMON_CXX11_CONSTEXPR variant(T&& arg)
		HAMON_NOEXCEPT_IF((hamon::is_nothrow_constructible<Tj, T>::value))		// [variant.ctor]/19
		: base_type(hamon::in_place_index_t<J>{}, hamon::forward<T>(arg))		// [variant.ctor]/16
	{}

	template <typename T, typename... Args,
		typename = hamon::enable_if_t<
			variant_detail::exactly_once<T, Types...>::value>,					// [variant.ctor]/20.1
		typename = hamon::enable_if_t<
			hamon::is_constructible<T, Args...>::value>,						// [variant.ctor]/20.2
		hamon::size_t I = variant_detail::find_index<T, Types...>::value
	>
	HAMON_CXX11_CONSTEXPR explicit
	variant(hamon::in_place_type_t<T>, Args&&... args)
		HAMON_NOEXCEPT_IF((
			hamon::is_nothrow_constructible<T, Args...>::value))	// extension
		: base_type(hamon::in_place_index_t<I>{}, hamon::forward<Args>(args)...)	// [variant.ctor]/21
	{}

	template <typename T, typename U, typename... Args,
		typename = hamon::enable_if_t<
			variant_detail::exactly_once<T, Types...>::value>,						// [variant.ctor]/25.1
		typename = hamon::enable_if_t<
			hamon::is_constructible<T, std::initializer_list<U>&, Args...>::value>,	// [variant.ctor]/25.2
		hamon::size_t I = variant_detail::find_index<T, Types...>::value
	>
	HAMON_CXX14_CONSTEXPR explicit
	variant(hamon::in_place_type_t<T>, std::initializer_list<U> il, Args&&... args)
		HAMON_NOEXCEPT_IF((
			hamon::is_nothrow_constructible<T, std::initializer_list<U>&, Args...>::value))	// extension
		: base_type(hamon::in_place_index_t<I>{}, il, hamon::forward<Args>(args)...)		// [variant.ctor]/26
	{}

	template <hamon::size_t I, typename... Args,
		typename = hamon::enable_if_t<(I < sizeof...(Types))>,					// [variant.ctor]/30.1
		typename Ti = hamon::nth_t<I, Types...>,
		typename = hamon::enable_if_t<
			hamon::is_constructible<Ti, Args...>::value>						// [variant.ctor]/30.2
	>
	HAMON_CXX11_CONSTEXPR explicit
	variant(hamon::in_place_index_t<I> tag, Args&&... args)
		HAMON_NOEXCEPT_IF((
			hamon::is_nothrow_constructible<Ti, Args...>::value))				// extension
		: base_type(tag, hamon::forward<Args>(args)...)							// [variant.ctor]/31
	{}

	template <hamon::size_t I, typename U, typename... Args,
		typename = hamon::enable_if_t<(I < sizeof...(Types))>,					// [variant.ctor]/35.1
		typename Ti = hamon::nth_t<I, Types...>,
		typename = hamon::enable_if_t<
			hamon::is_constructible<Ti, std::initializer_list<U>&, Args...>::value>	// [variant.ctor]/35.2
	>
	HAMON_CXX14_CONSTEXPR explicit
	variant(hamon::in_place_index_t<I> tag, std::initializer_list<U> il, Args&&... args)
		HAMON_NOEXCEPT_IF((
			hamon::is_nothrow_constructible<Ti, std::initializer_list<U>&, Args...>::value))	// extension
		: base_type(tag, il, hamon::forward<Args>(args)...)						// [variant.ctor]/36
	{}

	// [variant.dtor], destructor
	~variant() = default;

	// [variant.assign], assignment
	HAMON_CXX14_CONSTEXPR variant& operator=(variant const&) = default;
	HAMON_CXX14_CONSTEXPR variant& operator=(variant&&) = default;

	template <typename T,
		typename = hamon::enable_if_t<
			!hamon::is_same<hamon::remove_cvref_t<T>, variant>::value>,				// [variant.assign]/12.1
		hamon::size_t J = variant_detail::select_overload<T, Types...>::value,		// [variant.assign]/11
		typename Tj = hamon::nth_t<J, Types...>,
		typename = hamon::enable_if_t<
			variant_detail::exactly_once<Tj, Types...>::value>,
		typename = hamon::enable_if_t<												// [variant.assign]/12.2
			hamon::is_assignable<Tj&, T>::value &&
			hamon::is_constructible<Tj, T>::value
		>
	>
	HAMON_CXX14_CONSTEXPR variant& operator=(T&& t)
		HAMON_NOEXCEPT_IF((
			hamon::is_nothrow_assignable<Tj&, T>::value &&							// [variant.assign]/16
			hamon::is_nothrow_constructible<Tj, T>::value))
	{
		base_type::assign(hamon::in_place_index_t<J>{}, hamon::forward<T>(t));
		return *this;
	}

	// [variant.mod], modifiers
	template <typename T, typename... Args,
		typename = hamon::enable_if_t<
			hamon::is_constructible<T, Args...>::value>,			// [variant.mod]/1
		typename = hamon::enable_if_t<
			variant_detail::exactly_once<T, Types...>::value>,		// [variant.mod]/1
		hamon::size_t I = variant_detail::find_index<T, Types...>::value	// [variant.mod]/2
	>
	HAMON_CXX14_CONSTEXPR T&
	emplace(Args&&... args)
	{
		return base_type::emplace(
			hamon::in_place_index_t<I>{}, hamon::forward<Args>(args)...);
	}

	template <typename T, typename U, typename... Args,
		typename = hamon::enable_if_t<
			hamon::is_constructible<T, std::initializer_list<U>&, Args...>::value>,			// [variant.mod]/3
		typename = hamon::enable_if_t<
			variant_detail::exactly_once<T, Types...>::value>,		// [variant.mod]/3
		hamon::size_t I = variant_detail::find_index<T, Types...>::value	// [variant.mod]/4
	>
	HAMON_CXX14_CONSTEXPR T&
	emplace(std::initializer_list<U> il, Args&&... args)
	{
		return base_type::emplace(
			hamon::in_place_index_t<I>{}, il, hamon::forward<Args>(args)...);
	}

	template <hamon::size_t I, typename... Args,
		typename = hamon::enable_if_t<(I < sizeof...(Types))>,		// [variant.mod]/5
		typename Ti = hamon::nth_t<I, Types...>,
		typename = hamon::enable_if_t<
			hamon::is_constructible<Ti, Args...>::value>			// [variant.mod]/6
	>
	HAMON_CXX14_CONSTEXPR
	// hamon::variant_alternative_t<I, variant<Types...>>&
	Ti&	// make SFINAE-friendly
	emplace(Args&&... args)
	{
		return base_type::emplace(
			hamon::in_place_index_t<I>{}, hamon::forward<Args>(args)...);
	}

	template <hamon::size_t I, typename U, typename... Args,
		typename = hamon::enable_if_t<(I < sizeof...(Types))>,		// [variant.mod]/12
		typename Ti = hamon::nth_t<I, Types...>,
		typename = hamon::enable_if_t<
			hamon::is_constructible<Ti, std::initializer_list<U>&, Args...>::value>			// [variant.mod]/13
	>
	HAMON_CXX14_CONSTEXPR
	// hamon::variant_alternative_t<I, variant<Types...>>&
	Ti&	// make SFINAE-friendly
	emplace(std::initializer_list<U> il, Args&&... args)
	{
		return base_type::emplace(
			hamon::in_place_index_t<I>{}, il, hamon::forward<Args>(args)...);
	}

	// [variant.status], value status
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
	valueless_by_exception() const HAMON_NOEXCEPT
	{
		return base_type::valueless_by_exception();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::size_t
	index() const HAMON_NOEXCEPT
	{
		return base_type::index();
	}

	// [variant.swap], swap
	HAMON_CXX14_CONSTEXPR void swap(variant& rhs)
		HAMON_NOEXCEPT_IF((hamon::conjunction<
			// [variant.swap]/5
			hamon::is_nothrow_move_constructible<Types>...,
			hamon::is_nothrow_swappable<Types>...
		>::value))
	{
		// [variant.swap]/1
		static_assert(hamon::conjunction<hamon::is_move_constructible<Types>...>::value, "");
		// [variant.swap]/2
		static_assert(hamon::conjunction<hamon::is_swappable<Types>...>::value, "");

		base_type::swap(rhs);
	}

private:
	friend struct variant_detail::access;
};

// [variant.relops], relational operators
template <typename... Types>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool
operator==(variant<Types...> const& lhs, variant<Types...> const& rhs)
{
	// [variant.relops]/2
	return
		lhs.index() != rhs.index()   ? false :
		lhs.valueless_by_exception() ? true :
		variant_detail::visit_at::invoke<bool>(
			lhs.index(), hamon::ranges::equal_to{}, lhs, rhs);
}

template <typename... Types>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool
operator!=(variant<Types...> const& lhs, variant<Types...> const& rhs)
{
	// [variant.relops]/4
	return
		lhs.index() != rhs.index()   ? true :
		lhs.valueless_by_exception() ? false :
		variant_detail::visit_at::invoke<bool>(
			lhs.index(), hamon::ranges::not_equal_to{}, lhs, rhs);
}

template <typename... Types>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool
operator<(variant<Types...> const& lhs, variant<Types...> const& rhs)
{
	// [variant.relops]/6
	return
		rhs.valueless_by_exception() ? false :
		lhs.valueless_by_exception() ? true :
		lhs.index() < rhs.index()    ? true :
		lhs.index() > rhs.index()    ? false :
		variant_detail::visit_at::invoke<bool>(
			lhs.index(), hamon::ranges::less{}, lhs, rhs);
}

template <typename... Types>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool
operator>(variant<Types...> const& lhs, variant<Types...> const& rhs)
{
	// [variant.relops]/8
	return
		lhs.valueless_by_exception() ? false :
		rhs.valueless_by_exception() ? true :
		lhs.index() > rhs.index()    ? true :
		lhs.index() < rhs.index()    ? false :
		variant_detail::visit_at::invoke<bool>(
			lhs.index(), hamon::ranges::greater{}, lhs, rhs);
}

template <typename... Types>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool
operator<=(variant<Types...> const& lhs, variant<Types...> const& rhs)
{
	// [variant.relops]/10
	return
		lhs.valueless_by_exception() ? true :
		rhs.valueless_by_exception() ? false :
		lhs.index() < rhs.index()    ? true :
		lhs.index() > rhs.index()    ? false :
		variant_detail::visit_at::invoke<bool>(
			lhs.index(), hamon::ranges::less_equal{}, lhs, rhs);
}

template <typename... Types>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool
operator>=(variant<Types...> const& lhs, variant<Types...> const& rhs)
{
	// [variant.relops]/12
	return
		rhs.valueless_by_exception() ? true :
		lhs.valueless_by_exception() ? false :
		lhs.index() > rhs.index()    ? true :
		lhs.index() < rhs.index()    ? false :
		variant_detail::visit_at::invoke<bool>(
			lhs.index(), hamon::ranges::greater_equal{}, lhs, rhs);
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename... Types>
requires (hamon::three_way_comparable<Types> && ...)
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR
hamon::common_comparison_category_t<hamon::compare_three_way_result_t<Types>...>
operator<=>(variant<Types...> const& lhs, variant<Types...> const& rhs)
{
	// [variant.relops]/13

	if (lhs.valueless_by_exception() && rhs.valueless_by_exception())
	{
		return hamon::strong_ordering::equal;
	}

	if (lhs.valueless_by_exception())
	{
		return hamon::strong_ordering::less;
	}
	
	if (rhs.valueless_by_exception())
	{
		return hamon::strong_ordering::greater;
	}
	
	if (auto c = lhs.index() <=> rhs.index(); c != 0)
	{
		return c;
	}

	using result_t = hamon::common_comparison_category_t<
		hamon::compare_three_way_result_t<Types>...>;
	return variant_detail::visit_at::invoke<result_t>(
		lhs.index(), hamon::compare_three_way{}, lhs, rhs);
}

#endif

// [variant.specalg]
template <typename... Types,
	// [variant.specalg]/1
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::is_move_constructible<Types>...,
		hamon::is_swappable<Types>...
	>::value>
>
inline HAMON_CXX14_CONSTEXPR void
swap(variant<Types...>& lhs, variant<Types...>& rhs)
	// [variant.specalg]/3
	HAMON_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
{
	// [variant.specalg]/2
	lhs.swap(rhs);
}

}	// namespace hamon

#include <hamon/variant/detail/hash_impl.hpp>
#include <functional>

namespace std
{

// [variant.hash] hash support
template <typename... Types>
struct hash<hamon::variant<Types...>>
	: public hamon::variant_detail::hash_impl<hamon::variant<Types...>>
{};

}	// namespace std

#endif

#endif // HAMON_VARIANT_VARIANT_HPP
