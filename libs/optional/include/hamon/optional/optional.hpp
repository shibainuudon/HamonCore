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
using std::nullopt_t;
using std::nullopt;
using std::bad_optional_access;
using std::make_optional;

}	// namespace hamon

#else

#include <hamon/compare.hpp>
#include <hamon/concepts/detail/cpp17_destructible.hpp>
#include <hamon/concepts/detail/cpp17_hash.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/functional/detail/disabled_hash.hpp>
#include <hamon/memory.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/assert.hpp>
#include <initializer_list>
#include <exception>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

namespace hamon
{

template <typename T>
class optional;

// [optional.nullopt], no-value state indicator
struct nullopt_t
{
	// [optional.nullopt]/1
	// [optional.nullopt]/2
	struct CtorTag {};
	explicit HAMON_CXX11_CONSTEXPR nullopt_t(CtorTag) HAMON_NOEXCEPT {}
};

HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
nullopt_t nullopt{nullopt_t::CtorTag{}};

// [optional.bad.access], class bad_optional_access
class bad_optional_access : public std::exception
{
public:
	bad_optional_access() = default;
	virtual ~bad_optional_access() = default;

	char const* what() const HAMON_NOEXCEPT override
	{
		// [optional.bad.access]/2
		return "bad optional access";
	}
};

namespace optional_detail
{

template <typename T>
struct is_specialization_of_optional
	: public hamon::false_type {};

template <typename T>
struct is_specialization_of_optional<hamon::optional<T>>
	: public hamon::true_type {};

// [optional.ctor]/1
template <typename T, typename W>
using converts_from_any_cvref = hamon::disjunction<
	hamon::is_constructible<T, W&>, hamon::is_convertible<W&, T>,
	hamon::is_constructible<T, W>,  hamon::is_convertible<W,  T>,
	hamon::is_constructible<T, W const&>, hamon::is_convertible<W const&, T>,
	hamon::is_constructible<T, W const>,  hamon::is_convertible<W const,  T>
>;

struct construct_from_invoke_tag{};

template <typename T, bool = hamon::is_trivially_destructible<T>::value>
struct optional_dtor
{
	union
	{
		char	m_empty;
		T		m_value;
	};

	bool	m_has_value;

	HAMON_CXX11_CONSTEXPR
	optional_dtor() HAMON_NOEXCEPT
		: m_empty()
		, m_has_value(false)
	{}

	template <typename... Args>
	HAMON_CXX11_CONSTEXPR
	optional_dtor(hamon::in_place_t, Args&&... args)
		: m_value(hamon::forward<Args>(args)...)
		, m_has_value(true)
	{}
	
	template <typename F, typename Arg>
	HAMON_CXX11_CONSTEXPR
	optional_dtor(optional_detail::construct_from_invoke_tag, F&& f, Arg&& arg)
		: m_value(hamon::invoke(hamon::forward<F>(f), hamon::forward<Arg>(arg)))
		, m_has_value(true)
	{}

	HAMON_CXX14_CONSTEXPR
	void reset()
	{
		m_has_value = false;
	}
};

template <typename T>
struct optional_dtor<T, false>
{
	union
	{
		char	m_empty;
		T		m_value;
	};

	bool	m_has_value;

	HAMON_CXX11_CONSTEXPR
	optional_dtor() HAMON_NOEXCEPT
		: m_empty()
		, m_has_value(false)
	{}

	template <typename... Args>
	HAMON_CXX11_CONSTEXPR
	optional_dtor(hamon::in_place_t, Args&&... args)
		: m_value(hamon::forward<Args>(args)...)
		, m_has_value(true)
	{}

	template <typename F, typename Arg>
	HAMON_CXX11_CONSTEXPR
	optional_dtor(optional_detail::construct_from_invoke_tag, F&& f, Arg&& arg)
		: m_value(hamon::invoke(hamon::forward<F>(f), hamon::forward<Arg>(arg)))
		, m_has_value(true)
	{}

	HAMON_CXX20_CONSTEXPR
	~optional_dtor()
	{
		reset();
	}

	HAMON_CXX20_CONSTEXPR
	void reset()
	{
		if (m_has_value)
		{
			m_value.~T();
		}

		m_has_value = false;
	}
};

template <typename T>
struct optional_impl
	: public optional_detail::optional_dtor<T>
{
	using base_type = optional_detail::optional_dtor<T>;
	using base_type::base_type;

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR void
	construct(Args&&... args)
	{
		hamon::construct_at(
			hamon::addressof(this->m_value),
			hamon::forward<Args>(args)...);
		this->m_has_value = true;
	}

	template <typename Optional>
	HAMON_CXX14_CONSTEXPR void
	construct_from(Optional&& rhs)
	{
		if (rhs.has_value())
		{
			construct(*hamon::forward<Optional>(rhs));
		}
	}

	template <typename U>
	HAMON_CXX14_CONSTEXPR void
	assign(U&& v)
	{
		if (this->has_value())
		{
			this->m_value = hamon::forward<U>(v);
		}
		else
		{
			construct(hamon::forward<U>(v));
		}
	}

	template <typename Optional>
	HAMON_CXX14_CONSTEXPR void
	assign_from(Optional&& rhs)
	{
		if (rhs.has_value())
		{
			assign(*hamon::forward<Optional>(rhs));
		}
		else
		{
			this->reset();
		}
	}

	HAMON_CXX11_CONSTEXPR bool
	has_value() const HAMON_NOEXCEPT
	{
		return this->m_has_value;
	}

	HAMON_CXX14_CONSTEXPR T&
	operator*() & HAMON_NOEXCEPT
	{
		return this->m_value;
	}

	HAMON_CXX11_CONSTEXPR T const&
	operator*() const& HAMON_NOEXCEPT
	{
		return this->m_value;
	}

	HAMON_CXX14_CONSTEXPR T&&
	operator*() && HAMON_NOEXCEPT
	{
		return hamon::move(this->m_value);
	}

	HAMON_CXX11_CONSTEXPR T const&&
	operator*() const&& HAMON_NOEXCEPT
	{
		return hamon::move(this->m_value);
	}
};

template <typename T,
	bool = hamon::is_copy_constructible<T>::value,
	bool = hamon::is_trivially_copy_constructible<T>::value>
struct optional_ctor_copy
	: public optional_detail::optional_impl<T>
{
	using base_type = optional_detail::optional_impl<T>;
	using base_type::base_type;

	optional_ctor_copy()                                     = default;
	optional_ctor_copy(optional_ctor_copy &&)                = default;
	optional_ctor_copy& operator=(optional_ctor_copy &&)     = default;
	optional_ctor_copy& operator=(optional_ctor_copy const&) = default;

	// [optional.ctor]/7
	// This constructor is defined as deleted unless is_copy_constructible_v<T> is true.
	optional_ctor_copy(optional_ctor_copy const&) = delete;
};

template <typename T>
struct optional_ctor_copy<T, true, true>
	: public optional_detail::optional_impl<T>
{
	using base_type = optional_detail::optional_impl<T>;
	using base_type::base_type;

	optional_ctor_copy()                                     = default;
	optional_ctor_copy(optional_ctor_copy &&)                = default;
	optional_ctor_copy& operator=(optional_ctor_copy &&)     = default;
	optional_ctor_copy& operator=(optional_ctor_copy const&) = default;

	// [optional.ctor]/7
	// If is_trivially_copy_constructible_v<T> is true, this constructor is trivial.
	optional_ctor_copy(optional_ctor_copy const&) = default;
};

template <typename T>
struct optional_ctor_copy<T, true, false>
	: public optional_detail::optional_impl<T>
{
	using base_type = optional_detail::optional_impl<T>;
	using base_type::base_type;

	optional_ctor_copy()                                     = default;
	optional_ctor_copy(optional_ctor_copy &&)                = default;
	optional_ctor_copy& operator=(optional_ctor_copy &&)     = default;
	optional_ctor_copy& operator=(optional_ctor_copy const&) = default;

	// [optional.ctor]/4
	// If rhs contains a value, direct-non-list-initializes the contained value with *rhs.
	HAMON_CXX14_CONSTEXPR
	optional_ctor_copy(optional_ctor_copy const& rhs)
		HAMON_NOEXCEPT_IF((hamon::is_nothrow_copy_constructible<T>::value))
		: base_type()
	{
		base_type::construct_from(rhs);
	}
};

template <typename T,
	bool = hamon::is_move_constructible<T>::value,
	bool = hamon::is_trivially_move_constructible<T>::value>
struct optional_ctor_move
	: public optional_detail::optional_ctor_copy<T>
{
	using base_type = optional_detail::optional_ctor_copy<T>;
	using base_type::base_type;

	optional_ctor_move()                                     = default;
	optional_ctor_move(optional_ctor_move const&)            = default;
	optional_ctor_move& operator=(optional_ctor_move &&)     = default;
	optional_ctor_move& operator=(optional_ctor_move const&) = default;

	// [optional.ctor]/8
	// Constraints: is_move_constructible_v<T> is true.
	optional_ctor_move(optional_ctor_move &&) = delete;
};

template <typename T>
struct optional_ctor_move<T, true, true>
	: public optional_detail::optional_ctor_copy<T>
{
	using base_type = optional_detail::optional_ctor_copy<T>;
	using base_type::base_type;

	optional_ctor_move()                                     = default;
	optional_ctor_move(optional_ctor_move const&)            = default;
	optional_ctor_move& operator=(optional_ctor_move &&)     = default;
	optional_ctor_move& operator=(optional_ctor_move const&) = default;

	// [optional.ctor]/12
	// If is_trivially_move_constructible_v<T> is true, this constructor is trivial.
	optional_ctor_move(optional_ctor_move &&) = default;
};

template <typename T>
struct optional_ctor_move<T, true, false>
	: public optional_detail::optional_ctor_copy<T>
{
	using base_type = optional_detail::optional_ctor_copy<T>;
	using base_type::base_type;

	optional_ctor_move()                                     = default;
	optional_ctor_move(optional_ctor_move const&)            = default;
	optional_ctor_move& operator=(optional_ctor_move &&)     = default;
	optional_ctor_move& operator=(optional_ctor_move const&) = default;

	// [optional.ctor]/9
	// If rhs contains a value, direct-non-list-initializes the contained value with std​::​move(*rhs).
	// rhs.has_value() is unchanged.
	HAMON_CXX14_CONSTEXPR
	optional_ctor_move(optional_ctor_move && rhs)
		// [optional.ctor]/12
		// The exception specification is equivalent to is_nothrow_move_constructible_v<T>.
		HAMON_NOEXCEPT_IF((hamon::is_nothrow_move_constructible<T>::value))
		: base_type()
	{
		base_type::construct_from(hamon::move(rhs));
	}
};

template <typename T,
	bool = hamon::is_copy_constructible<T>::value &&
		hamon::is_copy_assignable<T>::value,
	bool = hamon::is_trivially_copy_constructible<T>::value &&
		hamon::is_trivially_copy_assignable<T>::value &&
		hamon::is_trivially_destructible<T>::value
>
struct optional_assign_copy
	: public optional_detail::optional_ctor_move<T>
{
	using base_type = optional_detail::optional_ctor_move<T>;
	using base_type::base_type;

	optional_assign_copy()                                       = default;
	optional_assign_copy(optional_assign_copy &&)                = default;
	optional_assign_copy(optional_assign_copy const&)            = default;
	optional_assign_copy& operator=(optional_assign_copy &&)     = default;

	// [optional.assign]/7
	// This operator is defined as deleted unless is_copy_constructible_v<T> is true and
	// is_copy_assignable_v<T> is true.
	optional_assign_copy& operator=(optional_assign_copy const&) = delete;
};

template <typename T>
struct optional_assign_copy<T, true, true>
	: public optional_detail::optional_ctor_move<T>
{
	using base_type = optional_detail::optional_ctor_move<T>;
	using base_type::base_type;

	optional_assign_copy()                                       = default;
	optional_assign_copy(optional_assign_copy &&)                = default;
	optional_assign_copy(optional_assign_copy const&)            = default;
	optional_assign_copy& operator=(optional_assign_copy &&)     = default;

	// [optional.assign]/7
	// If is_trivially_copy_constructible_v<T> && is_trivially_copy_assignable_v<T> &&
	// is_trivially_destructible_v<T> is true, this assignment operator is trivial.
	optional_assign_copy& operator=(optional_assign_copy const&) = default;
};

template <typename T>
struct optional_assign_copy<T, true, false>
	: public optional_detail::optional_ctor_move<T>
{
	using base_type = optional_detail::optional_ctor_move<T>;
	using base_type::base_type;

	optional_assign_copy()                                       = default;
	optional_assign_copy(optional_assign_copy &&)                = default;
	optional_assign_copy(optional_assign_copy const&)            = default;
	optional_assign_copy& operator=(optional_assign_copy &&)     = default;

	HAMON_CXX14_CONSTEXPR optional_assign_copy& operator=(optional_assign_copy const& rhs)
		HAMON_NOEXCEPT_IF((
			hamon::is_nothrow_copy_assignable<T>::value &&
			hamon::is_nothrow_copy_constructible<T>::value))
	{
		this->assign_from(rhs);
		return *this;
	}
};

template <typename T,
	bool = hamon::is_move_constructible<T>::value &&
		hamon::is_move_assignable<T>::value,
	bool = hamon::is_trivially_move_constructible<T>::value &&
		hamon::is_trivially_move_assignable<T>::value &&
		hamon::is_trivially_destructible<T>::value
>
struct optional_assign_move
	: public optional_detail::optional_assign_copy<T>
{
	using base_type = optional_detail::optional_assign_copy<T>;
	using base_type::base_type;

	optional_assign_move()                                       = default;
	optional_assign_move(optional_assign_move &&)                = default;
	optional_assign_move(optional_assign_move const&)            = default;
	optional_assign_move& operator=(optional_assign_move const&) = default;

	optional_assign_move& operator=(optional_assign_move &&)     = delete;
};

template <typename T>
struct optional_assign_move<T, true, true>
	: public optional_detail::optional_assign_copy<T>
{
	using base_type = optional_detail::optional_assign_copy<T>;
	using base_type::base_type;

	optional_assign_move()                                       = default;
	optional_assign_move(optional_assign_move &&)                = default;
	optional_assign_move(optional_assign_move const&)            = default;
	optional_assign_move& operator=(optional_assign_move const&) = default;

	optional_assign_move& operator=(optional_assign_move &&)     = default;
};

template <typename T>
struct optional_assign_move<T, true, false>
	: public optional_detail::optional_assign_copy<T>
{
	using base_type = optional_detail::optional_assign_copy<T>;
	using base_type::base_type;

	optional_assign_move()                                       = default;
	optional_assign_move(optional_assign_move &&)                = default;
	optional_assign_move(optional_assign_move const&)            = default;
	optional_assign_move& operator=(optional_assign_move const&) = default;

	HAMON_CXX14_CONSTEXPR optional_assign_move& operator=(optional_assign_move && rhs)
		// [optional.assign]/12
		HAMON_NOEXCEPT_IF((
			hamon::is_nothrow_move_assignable<T>::value &&
			hamon::is_nothrow_move_constructible<T>::value))
	{
		this->assign_from(hamon::move(rhs));
		return *this;
	}
};

template <typename T>
using optional_base = optional_assign_move<T>;

struct transform_impl
{
	template <typename F, typename Optional>
	HAMON_CXX11_CONSTEXPR auto operator()(F&& f, Optional&& opt) const
	-> optional<hamon::remove_cv_t<hamon::invoke_result_t<F, decltype(hamon::forward<Optional>(opt).value())>>>
	{
		// [optional.monadic]/7
		using U = hamon::remove_cv_t<hamon::invoke_result_t<F, decltype(hamon::forward<Optional>(opt).value())>>;

		// [optional.monadic]/8
		static_assert(!hamon::is_array<U>::value, "");
		static_assert(!hamon::is_same<U, hamon::in_place_t>::value, "");
		static_assert(!hamon::is_same<U, hamon::nullopt_t>::value, "");

		// TODO
		// The declaration
		// U u(invoke(std::forward<F>(f), value()));
		// is well-formed for some invented variable u.

		// [optional.monadic]/9
		return hamon::forward<Optional>(opt).has_value() ?
			optional<U>(optional_detail::construct_from_invoke_tag{},
				hamon::forward<F>(f), hamon::forward<Optional>(opt).value()) :
			optional<U>();
	}
};

}	// namespace optional_detail

// [optional.optional], class template optional
template <typename T>
class optional
	: private optional_detail::optional_base<T>
{
private:
	using base_type = optional_detail::optional_base<T>;

	// [optional.optional.general]/3
	// T shall be a type other than cv in_place_t or cv nullopt_t that
	// meets the Cpp17Destructible requirements (Table 35).
	static_assert(!hamon::is_same<hamon::remove_cv_t<T>, hamon::in_place_t>::value, "");
	static_assert(!hamon::is_same<hamon::remove_cv_t<T>, hamon::nullopt_t>::value, "");
	static_assert(hamon::detail::cpp17_destructible_t<T>::value, "");

	template <typename U>
	struct UTypeCtor
	{
		using V = hamon::remove_cvref_t<U>;

		// [optional.ctor]/23
		static const bool constructible = hamon::conjunction<
			hamon::is_constructible<T, U>,							// [optional.ctor]/23.1
			hamon::negation<hamon::is_same<V, hamon::in_place_t>>,	// [optional.ctor]/23.2
			hamon::negation<hamon::is_same<V, optional>>,			// [optional.ctor]/23.3
			hamon::negation<hamon::conjunction<						// [optional.ctor]/23.4
				hamon::is_same<hamon::remove_cv_t<T>, bool>,
				optional_detail::is_specialization_of_optional<V>
			>>
		>::value;

		// [optional.ctor]/27
		static const bool implicitly = hamon::is_convertible<U, T>::value;

		static const bool nothrow = hamon::is_nothrow_constructible<T, U>::value;
	};

	template <typename UOptional>
	struct UOptionalCtor;

	template <typename U>
	struct UOptionalCtor<optional<U> const&>
	{
		// [optional.ctor]/28
		static const bool constructible = hamon::conjunction<
			hamon::is_constructible<T, U const&>,		// [optional.ctor]/28.1
			hamon::negation<hamon::conjunction<			// [optional.ctor]/28.2
				hamon::negation<hamon::is_same<hamon::remove_cv_t<T>, bool>>,
				optional_detail::converts_from_any_cvref<T, optional<U>>
			>>
		>::value;

		// [optional.ctor]/32
		static const bool implicitly = hamon::is_convertible<U const&, T>::value;

		static const bool nothrow = hamon::is_nothrow_constructible<T, U const&>::value;
	};

	template <typename U>
	struct UOptionalCtor<optional<U>&&>
	{
		// [optional.ctor]/33
		static const bool constructible = hamon::conjunction<
			hamon::is_constructible<T, U>,				// [optional.ctor]/33.1
			hamon::negation<hamon::conjunction<			// [optional.ctor]/33.2
				hamon::negation<hamon::is_same<hamon::remove_cv_t<T>, bool>>,
				optional_detail::converts_from_any_cvref<T, optional<U>>
			>>
		>::value;

		// [optional.ctor]/37
		static const bool implicitly = hamon::is_convertible<U, T>::value;

		static const bool nothrow = hamon::is_nothrow_constructible<T, U>::value;
	};

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

	// [optional.monadic], monadic operations
	template <typename F>
	HAMON_CXX14_CONSTEXPR auto and_then(F&& f) &
	-> hamon::remove_cvref_t<hamon::invoke_result_t<F, decltype(value())>>
	{
		// [optional.monadic]/1
		using U = hamon::invoke_result_t<F, decltype(value())>;

		using V = hamon::remove_cvref_t<U>;

		// [optional.monadic]/2
		static_assert(optional_detail::is_specialization_of_optional<V>::value, "");

		// [optional.monadic]/3
		return *this ?
			hamon::invoke(hamon::forward<F>(f), value()) :
			V();
	}

	template <typename F>
	HAMON_CXX14_CONSTEXPR auto and_then(F&& f) &&
	-> hamon::remove_cvref_t<hamon::invoke_result_t<F, decltype(hamon::move(value()))>>
	{
		// [optional.monadic]/4
		using U = hamon::invoke_result_t<F, decltype(hamon::move(value()))>;

		using V = hamon::remove_cvref_t<U>;

		// [optional.monadic]/5
		static_assert(optional_detail::is_specialization_of_optional<V>::value, "");

		// [optional.monadic]/6
		return *this ?
			hamon::invoke(hamon::forward<F>(f), hamon::move(value())) :
			V();
	}

	template <typename F>
	HAMON_CXX11_CONSTEXPR auto and_then(F&& f) const&
	-> hamon::remove_cvref_t<hamon::invoke_result_t<F, decltype(value())>>
	{
		// [optional.monadic]/1
		using U = hamon::invoke_result_t<F, decltype(value())>;

		using V = hamon::remove_cvref_t<U>;

		// [optional.monadic]/2
		static_assert(optional_detail::is_specialization_of_optional<V>::value, "");

		// [optional.monadic]/3
		return *this ?
			hamon::invoke(hamon::forward<F>(f), value()) :
			V();
	}

	template <typename F>
	HAMON_CXX11_CONSTEXPR auto and_then(F&& f) const&&
	-> hamon::remove_cvref_t<hamon::invoke_result_t<F, decltype(hamon::move(value()))>>
	{
		// [optional.monadic]/4
		using U = hamon::invoke_result_t<F, decltype(hamon::move(value()))>;

		using V = hamon::remove_cvref_t<U>;

		// [optional.monadic]/5
		static_assert(optional_detail::is_specialization_of_optional<V>::value, "");

		// [optional.monadic]/6
		return *this ?
			hamon::invoke(hamon::forward<F>(f), hamon::move(value())) :
			V();
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

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename T>
optional(T) -> optional<T>;

#endif

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

template <typename T>
inline HAMON_CXX11_CONSTEXPR optional<hamon::decay_t<T>>
make_optional(T&& v)
{
	return optional<hamon::decay_t<T>>(hamon::forward<T>(v));
}

template <typename T, typename... Args>
inline HAMON_CXX11_CONSTEXPR optional<T>
make_optional(Args&&... args)
{
	return optional<T>(hamon::in_place, hamon::forward<Args>(args)...);
}

template <typename T, typename U, typename... Args>
inline HAMON_CXX14_CONSTEXPR optional<T>
make_optional(std::initializer_list<U> il, Args&&... args)
{
	return optional<T>(hamon::in_place, il, hamon::forward<Args>(args)...);
}

namespace optional_detail
{

template <typename T, typename U, typename = void>
struct hash_impl : public hamon::detail::disabled_hash
{};

template <typename T, typename U>
struct hash_impl<T, U,
	hamon::enable_if_t<hamon::detail::cpp17_hash_t<std::hash<U>, U>::value>>
{
	std::size_t operator()(hamon::optional<T> const& opt) const
	HAMON_NOEXCEPT_IF_EXPR((std::hash<U>{}(*opt)))
	{
		return opt.has_value() ? std::hash<U>{}(*opt) : 0;
	}
};

}	// namespace optional_detail

}	// namespace hamon

#include <functional>

namespace std
{

// [optional.hash], hash support
template <typename T>
struct hash<hamon::optional<T>>
	: public hamon::optional_detail::hash_impl<T, hamon::remove_const_t<T>>
{};

}	// namespace std

HAMON_WARNING_POP()

#endif

#endif // HAMON_OPTIONAL_OPTIONAL_HPP
