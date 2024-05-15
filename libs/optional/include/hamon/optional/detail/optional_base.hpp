/**
 *	@file	optional_base.hpp
 *
 *	@brief	optional_base の定義
 */

#ifndef HAMON_OPTIONAL_DETAIL_OPTIONAL_BASE_HPP
#define HAMON_OPTIONAL_DETAIL_OPTIONAL_BASE_HPP

#include <hamon/optional/detail/construct_from_invoke_tag.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/construct_at.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_assignable.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_assignable.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_trivially_copy_assignable.hpp>
#include <hamon/type_traits/is_trivially_copy_constructible.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include <hamon/type_traits/is_trivially_move_assignable.hpp>
#include <hamon/type_traits/is_trivially_move_constructible.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

namespace hamon
{

namespace optional_detail
{

template <typename T,
	bool = hamon::is_trivially_destructible<T>::value,
	bool = hamon::is_default_constructible<T>::value>
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

// TriviallyDestructible な場合は、デストラクタを定義する必要がないので、
// C++20でなくてもconstexprにすることができる。
template <typename T, bool B>
struct optional_dtor<T, true, B>
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

#if !defined(HAMON_HAS_CXX20_CONSTEXPR_UNION)
// TriviallyDestructible かつ DefaultConstructible な場合は、
// unionを使う必要がないので、C++20でなくてもconstexprにすることができる。
//
// ただし、ユーザー定義のデフォルトコンストラクタが非constexprな場合、
// optional<T>のコンストラクタも非constexprになってしまう。
// これは仕様に反している ([optional.ctor]/3) ので、
// C++20の場合はこの特殊化は定義しない。
template <typename T>
struct optional_dtor<T, true, true>
{
	T		m_value;
	bool	m_has_value;

	HAMON_CXX11_CONSTEXPR
	optional_dtor() HAMON_NOEXCEPT
		: m_value()
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
#endif

template <typename T, typename = void>
struct construct_impl
{
	template <typename... Args>
	static HAMON_CXX14_CONSTEXPR void
	invoke(T& obj, Args&&... args)
	{
		hamon::construct_at(
			hamon::addressof(obj),
			hamon::forward<Args>(args)...);
	}
};

// construct_at()はC++20以降でのみconstexpr。
// C++17までの場合でも、できるだけconstexprにするように頑張る。
#if !defined(HAMON_HAS_CONSTEXPR_CONSTRUCT_AT)
template <typename T>
struct construct_impl<T, hamon::enable_if_t<
	hamon::is_default_constructible<T>::value &&
	hamon::is_move_assignable<T>::value &&
	hamon::is_trivially_destructible<T>::value>>
{
	template <typename... Args>
	static HAMON_CXX14_CONSTEXPR void
	invoke(T& obj, Args&&... args)
	{
		obj = T(hamon::forward<Args>(args)...);
	}
};
#endif

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
		construct_impl<T>::invoke(
			this->m_value,
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

}	// namespace optional_detail

}	// namespace hamon

HAMON_WARNING_POP()

#endif // HAMON_OPTIONAL_DETAIL_OPTIONAL_BASE_HPP
