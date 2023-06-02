/**
 *	@file	optional.hpp
 *
 *	@brief	optional の定義
 */

#ifndef HAMON_OPTIONAL_OPTIONAL_HPP
#define HAMON_OPTIONAL_OPTIONAL_HPP

#include <hamon/optional/config.hpp>

#if defined(HAMON_USE_STD_OPTIONAL)

#include <optional>

namespace hamon
{

using std::optional;

}	// namespace hamon

#else

#include <hamon/optional/optional_fwd.hpp>
#include <hamon/optional/nullopt.hpp>
#include <hamon/optional/bad_optional_access.hpp>
#include <hamon/optional/detail/is_specialization_of_optional.hpp>
#include <hamon/optional/detail/converts_from_any_cvref.hpp>
#include <hamon/optional/detail/optional_base.hpp>
#include <hamon/optional/detail/optional_constraint.hpp>
#include <hamon/optional/detail/transform_impl.hpp>
#include <hamon/optional/detail/construct_from_invoke_tag.hpp>
#include <hamon/concepts/detail/cpp17_destructible.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/invocable.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/invoke_result.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_scalar.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_swappable.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/adl_swap.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/in_place.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>
#include <initializer_list>

namespace hamon
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

// [optional.optional], class template optional
template <typename T>
class optional : private optional_detail::optional_base<T>
{
private:
	using base_type = optional_detail::optional_base<T>;

	// [optional.optional.general]/3
	// T shall be a type other than cv in_place_t or cv nullopt_t that
	// meets the Cpp17Destructible requirements (Table 35).
	static_assert(!hamon::is_same<hamon::remove_cv_t<T>, hamon::in_place_t>::value, "");
	static_assert(!hamon::is_same<hamon::remove_cv_t<T>, hamon::nullopt_t>::value, "");
	static_assert(hamon::detail::cpp17_destructible_t<T>::value, "");

	using constraint_type = optional_detail::optional_constraint<T>;

	template <typename U>
	using UTypeCtor = typename constraint_type::template UTypeCtor<U>;

	template <typename UOptional>
	using UOptionalCtor = typename constraint_type::template UOptionalCtor<UOptional>;

public:
	using value_type = T;

	// [optional.ctor], constructors

	// optional()
	HAMON_CXX11_CONSTEXPR
	optional() HAMON_NOEXCEPT
		: base_type()
	{}

	// optional(hamon::nullopt_t)
	HAMON_CXX11_CONSTEXPR
	optional(hamon::nullopt_t) HAMON_NOEXCEPT
		: base_type()
	{}

	optional(optional const&) = default;
	optional(optional&&)  = default;

	// optional(hamon::in_place_t, Args&&... args)
	template <typename... Args,
		// [optional.ctor]/13
		typename = hamon::enable_if_t<
			hamon::is_constructible<T, Args...>::value>>
	explicit HAMON_CXX11_CONSTEXPR
	optional(hamon::in_place_t, Args&&... args)
	HAMON_NOEXCEPT_IF((hamon::is_nothrow_constructible<T, Args...>::value))
		: base_type(hamon::in_place_t{}, hamon::forward<Args>(args)...)
	{}

	// optional(hamon::in_place_t, std::initializer_list<U> il, Args&&... args)
	template <typename U, typename... Args,
		// [optional.ctor]/18
		typename = hamon::enable_if_t<
			hamon::is_constructible<T, std::initializer_list<U>&, Args...>::value>>
	explicit HAMON_CXX14_CONSTEXPR
	optional(hamon::in_place_t, std::initializer_list<U> il, Args&&... args)
	HAMON_NOEXCEPT_IF((
		hamon::is_nothrow_constructible<T, std::initializer_list<U>&, Args...>::value))
		: base_type(hamon::in_place_t{}, il, hamon::forward<Args>(args)...)
	{}

#if defined(HAMON_HAS_CXX20_CONDITIONAL_EXPLICIT)

	// optional(U&& v)
	template <typename U = T,
		typename Constraint = UTypeCtor<U>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX11_CONSTEXPR explicit(!Constraint::implicitly)
	optional(U&& v)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: base_type(hamon::in_place_t{}, hamon::forward<U>(v))
	{}

	// optional(optional<U> const& rhs)
	template <typename U,
		typename Constraint = UOptionalCtor<optional<U> const&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX14_CONSTEXPR explicit(!Constraint::implicitly)
	optional(optional<U> const& rhs)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
	{
		base_type::construct_from(rhs);
	}

	// optional(optional<U>&& rhs)
	template <typename U,
		typename Constraint = UOptionalCtor<optional<U>&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr>
	HAMON_CXX14_CONSTEXPR explicit(!Constraint::implicitly)
	optional(optional<U>&& rhs)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
	{
		base_type::construct_from(hamon::move(rhs));
	}

#else

	// optional(U&& v)
	template <typename U = T,
		typename Constraint = UTypeCtor<U>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX11_CONSTEXPR
	optional(U&& v)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: base_type(hamon::in_place_t{}, hamon::forward<U>(v))
	{}

	template <typename U = T,
		typename Constraint = UTypeCtor<U>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	optional(U&& v)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
		: base_type(hamon::in_place_t{}, hamon::forward<U>(v))
	{}

	// optional(optional<U> const& rhs)
	template <typename U,
		typename Constraint = UOptionalCtor<optional<U> const&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX14_CONSTEXPR
	optional(optional<U> const& rhs)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
	{
		base_type::construct_from(rhs);
	}

	template <typename U,
		typename Constraint = UOptionalCtor<optional<U> const&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX14_CONSTEXPR
	optional(optional<U> const& rhs)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
	{
		base_type::construct_from(rhs);
	}

	// optional(optional<U>&& rhs)
	template <typename U,
		typename Constraint = UOptionalCtor<optional<U>&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<!Constraint::implicitly>* = nullptr>
	explicit HAMON_CXX14_CONSTEXPR
	optional(optional<U>&& rhs)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
	{
		base_type::construct_from(hamon::move(rhs));
	}

	template <typename U,
		typename Constraint = UOptionalCtor<optional<U>&&>,
		hamon::enable_if_t<Constraint::constructible>* = nullptr,
		hamon::enable_if_t<Constraint::implicitly>* = nullptr>
	HAMON_CXX14_CONSTEXPR
	optional(optional<U>&& rhs)
	HAMON_NOEXCEPT_IF((Constraint::nothrow))
	{
		base_type::construct_from(hamon::move(rhs));
	}

#endif

	// [optional.dtor], destructor
	~optional() = default;

	// [optional.assign], assignment
	HAMON_CXX14_CONSTEXPR optional&
	operator=(hamon::nullopt_t) HAMON_NOEXCEPT
	{
		// [optional.assign]/1
		reset();

		// [optional.assign]/3
		return *this;
	}

	optional& operator=(optional const&) = default;
	optional& operator=(optional&&) = default;

	template <typename U = T,
		typename = hamon::enable_if_t<hamon::conjunction<	// [optional.assign]/14
			hamon::negation<hamon::is_same<hamon::remove_cvref_t<U>, optional>>,
			hamon::negation<hamon::conjunction<hamon::is_scalar<T>, hamon::is_same<T, hamon::decay_t<U>>>>,
			hamon::is_constructible<T, U>,
			hamon::is_assignable<T&, U>
		>::value>
	>
	HAMON_CXX14_CONSTEXPR optional&
	operator=(U&& v)
	{
		// [optional.assign]/15
		base_type::assign(hamon::forward<U>(v));

		// [optional.assign]/17
		return *this;
	}

	template <typename U,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_constructible<T, U const&>,							// [optional.assign]/19.1
			hamon::is_assignable<T&, U const&>,								// [optional.assign]/19.2
			hamon::negation<optional_detail::converts_from_any_cvref<T, optional<U>>>,	// [optional.assign]/19.3
			hamon::negation<hamon::is_assignable<T&, optional<U>&>>,		// [optional.assign]/19.4
			hamon::negation<hamon::is_assignable<T&, optional<U>&&>>,		// [optional.assign]/19.5
			hamon::negation<hamon::is_assignable<T&, optional<U> const&>>,	// [optional.assign]/19.6
			hamon::negation<hamon::is_assignable<T&, optional<U> const&&>>	// [optional.assign]/19.7
		>::value>>
	HAMON_CXX14_CONSTEXPR optional&
	operator=(optional<U> const& rhs)
	{
		// [optional.assign]/20
		base_type::assign_from(rhs);

		// [optional.assign]/22
		return *this;
	}

	template <typename U,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_constructible<T, U>,									// [optional.assign]/24.1
			hamon::is_assignable<T&, U>,									// [optional.assign]/24.2
			hamon::negation<optional_detail::converts_from_any_cvref<T, optional<U>>>,// [optional.assign]/24.3
			hamon::negation<hamon::is_assignable<T&, optional<U>&>>,		// [optional.assign]/24.4
			hamon::negation<hamon::is_assignable<T&, optional<U>&&>>,		// [optional.assign]/24.5
			hamon::negation<hamon::is_assignable<T&, optional<U> const&>>,	// [optional.assign]/24.6
			hamon::negation<hamon::is_assignable<T&, optional<U> const&&>>	// [optional.assign]/24.7
		>::value>>
	HAMON_CXX14_CONSTEXPR optional&
	operator=(optional<U>&& rhs)
	{
		// [optional.assign]/25
		base_type::assign_from(hamon::move(rhs));

		// [optional.assign]/27
		return *this;
	}

	template <typename... Args,
		typename = hamon::enable_if_t<	// [optional.assign]/29
			hamon::is_constructible<T, Args...>::value>>
	HAMON_CXX14_CONSTEXPR T&
	emplace(Args&&... args)
	{
		// [optional.assign]/30
		reset();
		base_type::construct(hamon::forward<Args>(args)...);

		// [optional.assign]/32
		return this->m_value;
	}

	template <typename U, typename... Args,
		typename = hamon::enable_if_t<	// [optional.assign]/35
			hamon::is_constructible<T, std::initializer_list<U>&, Args...>::value>>
	HAMON_CXX14_CONSTEXPR T&
	emplace(std::initializer_list<U> il, Args&&... args)
	{
		// [optional.assign]/36
		reset();
		base_type::construct(il, hamon::forward<Args>(args)...);

		// [optional.assign]/38
		return this->m_value;
	}

	// [optional.swap], swap
	HAMON_CXX14_CONSTEXPR void
	swap(optional& rhs)
	HAMON_NOEXCEPT_IF((		// [optional.swap]/5
		hamon::is_nothrow_move_constructible<T>::value &&
		hamon::is_nothrow_swappable<T>::value))
	{
		// [optional.swap]/3

		if (rhs.has_value())
		{
			if (this->has_value())
			{
				hamon::adl_swap(this->m_value, rhs.m_value);
			}
			else
			{
                this->construct(hamon::move(rhs.m_value));
                rhs.reset();
			}
		}
		else
		{
			if (this->has_value())
			{
                rhs.construct(hamon::move(this->m_value));
                this->reset();
			}
			else
			{
				// no effect
			}
		}
	}

	// [optional.observe], observers
	HAMON_CXX14_CONSTEXPR T* operator->() HAMON_NOEXCEPT
	{
		return HAMON_ASSERT(this->has_value()),	// [optional.observe]/1
			hamon::addressof(this->m_value);	// [optional.observe]/2
	}

	HAMON_CXX11_CONSTEXPR T const* operator->() const HAMON_NOEXCEPT
	{
		return HAMON_ASSERT(this->has_value()),	// [optional.observe]/1
			hamon::addressof(this->m_value);	// [optional.observe]/2
	}

	HAMON_CXX14_CONSTEXPR T& operator*() & HAMON_NOEXCEPT
	{
		return HAMON_ASSERT(this->has_value()),	// [optional.observe]/4
			this->m_value;						// [optional.observe]/5
	}

	HAMON_CXX14_CONSTEXPR T&& operator*() && HAMON_NOEXCEPT
	{
		return HAMON_ASSERT(this->has_value()),	// [optional.observe]/7
			hamon::move(this->m_value);			// [optional.observe]/8
	}

	HAMON_CXX11_CONSTEXPR T const& operator*() const& HAMON_NOEXCEPT
	{
		return HAMON_ASSERT(this->has_value()),	// [optional.observe]/4
			this->m_value;						// [optional.observe]/5
	}

	HAMON_CXX11_CONSTEXPR T const&& operator*() const&& HAMON_NOEXCEPT
	{
		return HAMON_ASSERT(this->has_value()),	// [optional.observe]/7
			hamon::move(this->m_value);			// [optional.observe]/8
	}

	HAMON_CXX11_CONSTEXPR explicit operator bool() const HAMON_NOEXCEPT
	{
		// [optional.observe]/9
		return base_type::has_value();
	}

	HAMON_CXX11_CONSTEXPR bool has_value() const HAMON_NOEXCEPT
	{
		// [optional.observe]/11
		return base_type::has_value();
	}

	HAMON_CXX14_CONSTEXPR T& value() &
	{
		// [optional.observe]/13
		return this->has_value() ?
			this->m_value :
			(throw_bad_optional_access(), this->m_value);
	}

	HAMON_CXX14_CONSTEXPR T&& value() &&
	{
		// [optional.observe]/14
		return this->has_value() ?
			hamon::move(this->m_value) :
			hamon::move((throw_bad_optional_access(), this->m_value));
	}

	HAMON_CXX11_CONSTEXPR T const& value() const&
	{
		// [optional.observe]/13
		return this->has_value() ?
			this->m_value :
			(throw_bad_optional_access(), this->m_value);
	}

	HAMON_CXX11_CONSTEXPR T const&& value() const&&
	{
		// [optional.observe]/14
		return this->has_value() ?
			hamon::move(this->m_value) :
			hamon::move((throw_bad_optional_access(), this->m_value));
	}

	template <typename U>
	HAMON_CXX14_CONSTEXPR T value_or(U&& v) &&
	{
		// [optional.observe]/17
		static_assert(
			hamon::is_move_constructible<T>::value &&
			hamon::is_convertible<U&&, T>::value, "");

		// [optional.observe]/18
		return this->has_value() ?
			hamon::move(this->m_value) :
			static_cast<T>(hamon::forward<U>(v));
	}

	template <typename U>
	HAMON_CXX11_CONSTEXPR T value_or(U&& v) const&
	{
		// [optional.observe]/15
		static_assert(
			hamon::is_copy_constructible<T>::value &&
			hamon::is_convertible<U&&, T>::value, "");

		// [optional.observe]/16
		return this->has_value() ?
			this->m_value :
			static_cast<T>(hamon::forward<U>(v));
	}
	
private:
	template <typename F, typename Optional>
	static HAMON_CXX11_CONSTEXPR auto
	and_then_impl(F&& f, Optional&& opt)
	-> hamon::remove_cvref_t<hamon::invoke_result_t<F, decltype(hamon::forward<Optional>(opt).value())>>
	{
		// [optional.monadic]/1,4
		using U = hamon::invoke_result_t<F, decltype(hamon::forward<Optional>(opt).value())>;

		using V = hamon::remove_cvref_t<U>;

		// [optional.monadic]/2,5
		static_assert(optional_detail::is_specialization_of_optional<V>::value, "");

		// [optional.monadic]/3,6
		return hamon::forward<Optional>(opt).has_value() ?
			hamon::invoke(hamon::forward<F>(f), hamon::forward<Optional>(opt).value()) :
			V();
	}

public:
	// [optional.monadic], monadic operations
	template <typename F>
	HAMON_CXX14_CONSTEXPR auto and_then(F&& f) &
	->decltype(and_then_impl(hamon::forward<F>(f), *this))
	{
		return and_then_impl(hamon::forward<F>(f), *this);
	}

	template <typename F>
	HAMON_CXX14_CONSTEXPR auto and_then(F&& f) &&
	->decltype(and_then_impl(hamon::forward<F>(f), hamon::move(*this)))
	{
		return and_then_impl(hamon::forward<F>(f), hamon::move(*this));
	}

	template <typename F>
	HAMON_CXX11_CONSTEXPR auto and_then(F&& f) const&
	->decltype(and_then_impl(hamon::forward<F>(f), *this))
	{
		return and_then_impl(hamon::forward<F>(f), *this);
	}

	template <typename F>
	HAMON_CXX11_CONSTEXPR auto and_then(F&& f) const&&
	->decltype(and_then_impl(hamon::forward<F>(f), hamon::move(*this)))
	{
		return and_then_impl(hamon::forward<F>(f), hamon::move(*this));
	}

private:
	template <typename F, typename Arg>
	HAMON_CXX11_CONSTEXPR
	optional(optional_detail::construct_from_invoke_tag tag, F&& f, Arg&& arg)
		: base_type(tag, hamon::forward<F>(f), hamon::forward<Arg>(arg))
	{}

	friend struct optional_detail::transform_impl;

public:
	template <typename F>
	HAMON_CXX14_CONSTEXPR auto transform(F&& f) &
	->decltype(optional_detail::transform_impl{}(hamon::forward<F>(f), *this))
	{
		return optional_detail::transform_impl{}(hamon::forward<F>(f), *this);
	}

	template <typename F>
	HAMON_CXX14_CONSTEXPR auto transform(F&& f) &&
	->decltype(optional_detail::transform_impl{}(hamon::forward<F>(f), hamon::move(*this)))
	{
		return optional_detail::transform_impl{}(hamon::forward<F>(f), hamon::move(*this));
	}

	template <typename F>
	HAMON_CXX11_CONSTEXPR auto transform(F&& f) const&
	->decltype(optional_detail::transform_impl{}(hamon::forward<F>(f), *this))
	{
		return optional_detail::transform_impl{}(hamon::forward<F>(f), *this);
	}

	template <typename F>
	HAMON_CXX11_CONSTEXPR auto transform(F&& f) const&&
	->decltype(optional_detail::transform_impl{}(hamon::forward<F>(f), hamon::move(*this)))
	{
		return optional_detail::transform_impl{}(hamon::forward<F>(f), hamon::move(*this));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::invocable, F),
		typename U = T,
		typename = hamon::enable_if_t<hamon::is_move_constructible<U>::value>>	// [optional.monadic]/16
	HAMON_CXX14_CONSTEXPR optional or_else(F&& f) &&
	{
		// [optional.monadic]/17
		static_assert(hamon::is_same<hamon::remove_cvref_t<hamon::invoke_result_t<F>>, optional>::value, "");

		// [optional.monadic]/18
		return *this ? hamon::move(*this) : hamon::forward<F>(f)();
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::invocable, F),
		typename U = T,
		typename = hamon::enable_if_t<hamon::is_copy_constructible<U>::value>>	// [optional.monadic]/13
	HAMON_CXX11_CONSTEXPR optional or_else(F&& f) const&
	{
		// [optional.monadic]/14
		static_assert(hamon::is_same<hamon::remove_cvref_t<hamon::invoke_result_t<F>>, optional>::value, "");

		// [optional.monadic]/15
		return *this ? *this : hamon::forward<F>(f)();
	}

	// [optional.mod], modifiers
	HAMON_CXX14_CONSTEXPR void reset() HAMON_NOEXCEPT
	{
		base_type::reset();
	}

private:
	HAMON_NORETURN static void
	throw_bad_optional_access()
	{
#if !defined(HAMON_NO_EXCEPTIONS)
		throw hamon::bad_optional_access();
#else
		std::abort();
#endif
	}
};

HAMON_WARNING_POP()

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename T>
optional(T) -> optional<T>;

#endif

}	// namespace hamon

#include <hamon/compare/concepts/three_way_comparable_with.hpp>
#include <hamon/compare/compare_three_way_result.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [optional.relops], relational operators
template <typename T, typename U,
	typename = hamon::enable_if_t<
		hamon::convertible_to_t<	// [optional.relops]/1
			decltype(hamon::declval<T const&>() == hamon::declval<U const&>()), bool
		>::value>>
inline HAMON_CXX11_CONSTEXPR bool
operator==(optional<T> const& x, optional<U> const& y)
{
	// [optional.relops]/2
	return
		x.has_value() != y.has_value() ? false :
		!x.has_value() ? true : *x == *y;
}

template <typename T, typename U,
	typename = hamon::enable_if_t<
		hamon::convertible_to_t<	// [optional.relops]/4
			decltype(hamon::declval<T const&>() != hamon::declval<U const&>()), bool
		>::value>>
inline HAMON_CXX11_CONSTEXPR bool
operator!=(optional<T> const& x, optional<U> const& y)
{
	// [optional.relops]/5
	return
		x.has_value() != y.has_value() ? true :
		!x.has_value() ? false : *x != *y;
}

template <typename T, typename U,
	typename = hamon::enable_if_t<
		hamon::convertible_to_t<	// [optional.relops]/7
			decltype(hamon::declval<T const&>() < hamon::declval<U const&>()), bool
		>::value>>
inline HAMON_CXX11_CONSTEXPR bool
operator<(optional<T> const& x, optional<U> const& y)
{
	// [optional.relops]/8
	return
		!y.has_value() ? false :
		!x.has_value() ? true : *x < *y;
}

template <typename T, typename U,
	typename = hamon::enable_if_t<
		hamon::convertible_to_t<	// [optional.relops]/10
			decltype(hamon::declval<T const&>() > hamon::declval<U const&>()), bool
		>::value>>
inline HAMON_CXX11_CONSTEXPR bool
operator>(optional<T> const& x, optional<U> const& y)
{
	// [optional.relops]/11
	return
		!x.has_value() ? false :
		!y.has_value() ? true : *x > *y;
}

template <typename T, typename U,
	typename = hamon::enable_if_t<
		hamon::convertible_to_t<	// [optional.relops]/13
			decltype(hamon::declval<T const&>() <= hamon::declval<U const&>()), bool
		>::value>>
inline HAMON_CXX11_CONSTEXPR bool
operator<=(optional<T> const& x, optional<U> const& y)
{
	// [optional.relops]/14
	return
		!x.has_value() ? true :
		!y.has_value() ? false : *x <= *y;
}

template <typename T, typename U,
	typename = hamon::enable_if_t<
		hamon::convertible_to_t<	// [optional.relops]/16
			decltype(hamon::declval<T const&>() >= hamon::declval<U const&>()), bool
		>::value>>
inline HAMON_CXX11_CONSTEXPR bool
operator>=(optional<T> const& x, optional<U> const& y)
{
	// [optional.relops]/17
	return
		!y.has_value() ? true :
		!x.has_value() ? false : *x >= *y;
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename T, hamon::three_way_comparable_with<T> U>
inline HAMON_CXX11_CONSTEXPR hamon::compare_three_way_result_t<T, U>
operator<=>(optional<T> const& x, optional<U> const& y)
{
	// [optional.relops]/19
	if (x.has_value() && y.has_value())
	{
		return *x <=> *y;
	}
	
	return x.has_value() <=> y.has_value();
}

#endif

// [optional.nullops], comparison with nullopt
template <typename T>
inline HAMON_CXX11_CONSTEXPR bool
operator==(optional<T> const& x, hamon::nullopt_t) HAMON_NOEXCEPT
{
	// [optional.nullops]/1
	return !x.has_value();
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename T>
inline HAMON_CXX11_CONSTEXPR hamon::strong_ordering
operator<=>(optional<T> const& x, hamon::nullopt_t) HAMON_NOEXCEPT
{
	// [optional.nullops]/2
	return x.has_value() <=> false;
}

#else

template <typename T>
inline HAMON_CXX11_CONSTEXPR bool
operator==(hamon::nullopt_t, optional<T> const& x) HAMON_NOEXCEPT
{
	return !x.has_value();
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR bool
operator!=(optional<T> const& x, hamon::nullopt_t) HAMON_NOEXCEPT
{
	return x.has_value();
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR bool
operator!=(hamon::nullopt_t, optional<T> const& x) HAMON_NOEXCEPT
{
	return x.has_value();
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR bool
operator<(optional<T> const&, hamon::nullopt_t) HAMON_NOEXCEPT
{
	return false;
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR bool
operator<(hamon::nullopt_t, optional<T> const& x) HAMON_NOEXCEPT
{
	return x.has_value();
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR bool
operator>(optional<T> const& x, hamon::nullopt_t) HAMON_NOEXCEPT
{
	return x.has_value();
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR bool
operator>(hamon::nullopt_t, optional<T> const&) HAMON_NOEXCEPT
{
	return false;
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR bool
operator<=(optional<T> const& x, hamon::nullopt_t) HAMON_NOEXCEPT
{
	return !x.has_value();
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR bool
operator<=(hamon::nullopt_t, optional<T> const&) HAMON_NOEXCEPT
{
	return true;
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR bool
operator>=(optional<T> const&, hamon::nullopt_t) HAMON_NOEXCEPT
{
	return true;
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR bool
operator>=(hamon::nullopt_t, optional<T> const& x) HAMON_NOEXCEPT
{
	return !x.has_value();
}

#endif

// [optional.comp.with.t], comparison with T
template <typename T, typename U,
	typename = hamon::enable_if_t<
		hamon::convertible_to_t<	// [optional.comp.with.t]/1
			decltype(hamon::declval<T const&>() == hamon::declval<U const&>()), bool
		>::value>>
inline HAMON_CXX11_CONSTEXPR bool
operator==(optional<T> const& x, U const& v)
{
	// [optional.comp.with.t]/2
	return x.has_value() ? *x == v : false;
}

template <typename T, typename U,
	typename = hamon::enable_if_t<
		hamon::convertible_to_t<	// [optional.comp.with.t]/3
			decltype(hamon::declval<T const&>() == hamon::declval<U const&>()), bool
		>::value>>
inline HAMON_CXX11_CONSTEXPR bool
operator==(T const& v, optional<U> const& x)
{
	// [optional.comp.with.t]/4
	return x.has_value() ? v == *x : false;
}

template <typename T, typename U,
	typename = hamon::enable_if_t<
		hamon::convertible_to_t<	// [optional.comp.with.t]/5
			decltype(hamon::declval<T const&>() != hamon::declval<U const&>()), bool
		>::value>>
inline HAMON_CXX11_CONSTEXPR bool
operator!=(optional<T> const& x, U const& v)
{
	// [optional.comp.with.t]/6
	return x.has_value() ? *x != v : true;
}

template <typename T, typename U,
	typename = hamon::enable_if_t<
		hamon::convertible_to_t<	// [optional.comp.with.t]/7
			decltype(hamon::declval<T const&>() != hamon::declval<U const&>()), bool
		>::value>>
inline HAMON_CXX11_CONSTEXPR bool
operator!=(T const& v, optional<U> const& x)
{
	// [optional.comp.with.t]/8
	return x.has_value() ? v != *x : true;
}

template <typename T, typename U,
	typename = hamon::enable_if_t<
		hamon::convertible_to_t<	// [optional.comp.with.t]/9
			decltype(hamon::declval<T const&>() < hamon::declval<U const&>()), bool
		>::value>>
inline HAMON_CXX11_CONSTEXPR bool
operator<(optional<T> const& x, U const& v)
{
	// [optional.comp.with.t]/10
	return x.has_value() ? *x < v : true;
}

template <typename T, typename U,
	typename = hamon::enable_if_t<
		hamon::convertible_to_t<	// [optional.comp.with.t]/11
			decltype(hamon::declval<T const&>() < hamon::declval<U const&>()), bool
		>::value>>
inline HAMON_CXX11_CONSTEXPR bool
operator<(T const& v, optional<U> const& x)
{
	// [optional.comp.with.t]/12
	return x.has_value() ? v < *x : false;
}

template <typename T, typename U,
	typename = hamon::enable_if_t<
		hamon::convertible_to_t<	// [optional.comp.with.t]/13
			decltype(hamon::declval<T const&>() > hamon::declval<U const&>()), bool
		>::value>>
inline HAMON_CXX11_CONSTEXPR bool
operator>(optional<T> const& x, U const& v)
{
	// [optional.comp.with.t]/14
	return x.has_value() ? *x > v : false;
}

template <typename T, typename U,
	typename = hamon::enable_if_t<
		hamon::convertible_to_t<	// [optional.comp.with.t]/15
			decltype(hamon::declval<T const&>() > hamon::declval<U const&>()), bool
		>::value>>
inline HAMON_CXX11_CONSTEXPR bool
operator>(T const& v, optional<U> const& x)
{
	// [optional.comp.with.t]/16
	return x.has_value() ? v > *x : true;
}

template <typename T, typename U,
	typename = hamon::enable_if_t<
		hamon::convertible_to_t<	// [optional.comp.with.t]/17
			decltype(hamon::declval<T const&>() <= hamon::declval<U const&>()), bool
		>::value>>
inline HAMON_CXX11_CONSTEXPR bool
operator<=(optional<T> const& x, U const& v)
{
	// [optional.comp.with.t]/18
	return x.has_value() ? *x <= v : true;
}

template <typename T, typename U,
	typename = hamon::enable_if_t<
		hamon::convertible_to_t<	// [optional.comp.with.t]/19
			decltype(hamon::declval<T const&>() <= hamon::declval<U const&>()), bool
		>::value>>
inline HAMON_CXX11_CONSTEXPR bool
operator<=(T const& v, optional<U> const& x)
{
	// [optional.comp.with.t]/20
	return x.has_value() ? v <= *x : false;
}

template <typename T, typename U,
	typename = hamon::enable_if_t<
		hamon::convertible_to_t<	// [optional.comp.with.t]/21
			decltype(hamon::declval<T const&>() >= hamon::declval<U const&>()), bool
		>::value>>
inline HAMON_CXX11_CONSTEXPR bool
operator>=(optional<T> const& x, U const& v)
{
	// [optional.comp.with.t]/22
	return x.has_value() ? *x >= v : false;
}

template <typename T, typename U,
	typename = hamon::enable_if_t<
		hamon::convertible_to_t<	// [optional.comp.with.t]/23
			decltype(hamon::declval<T const&>() >= hamon::declval<U const&>()), bool
		>::value>>
inline HAMON_CXX11_CONSTEXPR bool
operator>=(T const& v, optional<U> const& x)
{
	// [optional.comp.with.t]/24
	return x.has_value() ? v >= *x : true;
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

namespace optional_detail
{

template <typename T>
void is_derived_from_optional_helper(optional<T> const&);

// exposition only
template <typename T>
concept is_derived_from_optional =
	requires(T const& t)
	{
		is_derived_from_optional_helper(t);
	};

}	// namespace optional_detail

template <typename T, typename U>
requires (!optional_detail::is_derived_from_optional<U>) && hamon::three_way_comparable_with<T, U>
inline HAMON_CXX11_CONSTEXPR hamon::compare_three_way_result_t<T, U>
operator<=>(optional<T> const& x, U const& v)
{
	// [optional.comp.with.t]/25
	return x.has_value() ? *x <=> v : hamon::strong_ordering::less;
}

#endif

}	// namespace hamon

#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_swappable.hpp>

namespace hamon
{

// [optional.specalg], specialized algorithms
template <typename T,
	typename = hamon::enable_if_t<hamon::conjunction<	// [optional.specalg]/1
		hamon::is_move_constructible<T>,
		hamon::is_swappable<T>
	>::value>
>
inline HAMON_CXX14_CONSTEXPR void
swap(optional<T>& x, optional<T>& y)
HAMON_NOEXCEPT_IF_EXPR((x.swap(y)))
{
	// [optional.specalg]/2
	x.swap(y);
}

}	// namespace hamon

#include <hamon/optional/detail/hash_impl.hpp>
#include <hamon/type_traits/remove_const.hpp>
#include <functional>

namespace std
{

// [optional.hash], hash support
template <typename T>
struct hash<hamon::optional<T>>
	: public hamon::optional_detail::hash_impl<T, hamon::remove_const_t<T>>
{};

}	// namespace std

#endif

#endif // HAMON_OPTIONAL_OPTIONAL_HPP
