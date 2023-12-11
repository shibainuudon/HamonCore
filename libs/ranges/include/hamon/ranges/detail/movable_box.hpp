/**
 *	@file	movable_box.hpp
 *
 *	@brief	movable_box の定義
 *	
 *	26.7.3 Movable wrapper[range.move.wrap]
 *	
 *	T をmove可能にするためのクラステンプレート。
 *	ほとんどの場合、optional<T>と同じように働く。
 */

#ifndef HAMON_RANGES_DETAIL_MOVABLE_BOX_HPP
#define HAMON_RANGES_DETAIL_MOVABLE_BOX_HPP

#include <hamon/concepts/move_constructible.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/copyable.hpp>
#include <hamon/concepts/movable.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/type_traits/is_object.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/construct_at.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/optional.hpp>

namespace hamon {
namespace ranges {
namespace detail {

#if defined(HAMON_HAS_CXX20_CONCEPTS)

// [range.move.wrap]/1.1
template <typename T>
concept boxable = hamon::move_constructible<T> && hamon::is_object_v<T>;

// [range.move.wrap]/2.1
template <typename T>
concept boxable_copyable = hamon::copy_constructible<T> &&
	(hamon::copyable<T> || (hamon::is_nothrow_move_constructible_v<T> && hamon::is_nothrow_copy_constructible_v<T>));

// [range.move.wrap]/2.2
template <typename T>
concept boxable_movable = (!hamon::copy_constructible<T>) &&
	(hamon::movable<T> || hamon::is_nothrow_move_constructible_v<T>);

template <typename T>
using boxable_t = hamon::bool_constant<boxable<T>>;

template <typename T>
using boxable_copyable_t = hamon::bool_constant<boxable_copyable<T>>;

template <typename T>
using boxable_movable_t = hamon::bool_constant<boxable_movable<T>>;

#else

template <typename T>
using boxable_t =
	hamon::conjunction<
		hamon::move_constructible_t<T>,
		hamon::is_object<T>>;

template <typename T>
using boxable_copyable_t =
	hamon::conjunction<
		hamon::copy_constructible_t<T>,
		hamon::disjunction<
			hamon::copyable_t<T>,
			hamon::conjunction<
				hamon::is_nothrow_move_constructible<T>,
				hamon::is_nothrow_copy_constructible<T>
			>
		>
	>;

template <typename T>
using boxable_movable_t =
	hamon::conjunction<
		hamon::negation<hamon::copy_constructible_t<T>>,
		hamon::disjunction<
			hamon::movable_t<T>,
			hamon::is_nothrow_move_constructible<T>
		>
	>;

#endif

template <typename T,
	bool = boxable_copyable_t<T>::value || boxable_movable_t<T>::value,
	bool = boxable_t<T>::value
>
struct movable_box;

template <typename T>
struct movable_box<T, false, true> : hamon::optional<T>
{
	// [range.move.wrap]/1
	using hamon::optional<T>::optional;
	using hamon::optional<T>::operator=;

	// [range.move.wrap]/1.2
	HAMON_CXX11_CONSTEXPR movable_box()
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_default_constructible<T>::value)
#if defined(HAMON_HAS_CXX20_CONCEPTS)	// TODO
		requires hamon::default_initializable<T>
#endif
		: movable_box{hamon::in_place_t{}}
	{}

	// [range.move.wrap]/1.3
	HAMON_CXX14_CONSTEXPR movable_box&
	operator=(movable_box const& that)
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_copy_constructible<T>::value)
#if defined(HAMON_HAS_CXX20_CONCEPTS)	// TODO
		requires (!hamon::copyable<T>) && hamon::copy_constructible<T>
#endif
	{
		if (this != hamon::addressof(that))
		{
			if (that)
			{
				this->emplace(*that);
			}
			else
			{
				this->reset();
			}
		}

		return *this;
	}

	// [range.move.wrap]/1.4
	HAMON_CXX14_CONSTEXPR movable_box&
	operator=(movable_box&& that)
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_move_constructible<T>::value)
#if defined(HAMON_HAS_CXX20_CONCEPTS)	// TODO
		requires (!hamon::movable<T>)
#endif
	{
		if (this != hamon::addressof(that))
		{
			if (that)
			{
				this->emplace(hamon::move(*that));
			}
			else	
			{
				this->reset();
			}
		}

		return *this;
	}
};

// [range.move.wrap]/2
// もしTが既にcopyableやmovableなときは、Tを直接保持する
template <typename T>
struct movable_box<T, true, true>
{
private:
	HAMON_NO_UNIQUE_ADDRESS T m_value = T();

public:
	HAMON_CXX11_CONSTEXPR movable_box()
//		requires hamon::default_initializable<T>	// TODO
	= default;

	HAMON_CXX11_CONSTEXPR explicit
	movable_box(T const& t)
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_copy_constructible<T>::value)
//		requires hamon::copy_constructible<T>	// TODO
		: m_value(t)
	{}

	HAMON_CXX11_CONSTEXPR explicit
	movable_box(T&& t)
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_move_constructible<T>::value)
		: m_value(hamon::move(t))
	{}

	template <typename... Args,
		typename = hamon::enable_if_t<hamon::constructible_from_t<T, Args...>::value>>
//		requires hamon::constructible_from<T, Args...>
	HAMON_CXX11_CONSTEXPR explicit
	movable_box(hamon::in_place_t, Args&&... args)
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_constructible<T, Args...>::value)
		: m_value(hamon::forward<Args>(args)...)
	{}

	movable_box(movable_box const&) = default;
	movable_box(movable_box&&) = default;
	
	movable_box& operator=(movable_box const&)
//		requires hamon::copyable<T>	// TODO
	= default;
	
	movable_box& operator=(movable_box&&)
//		requires hamon::movable<T>	// TODO
	= default;

#if 0	// TODO
	HAMON_CXX14_CONSTEXPR movable_box&
	operator=(movable_box const& that) HAMON_NOEXCEPT
		requires (!hamon::copyable<T>) && hamon::copy_constructible<T>
	{
		static_assert(hamon::is_nothrow_copy_constructible<T>::value);
		if (this != hamon::addressof(that))
		{
			m_value.~T();
			hamon::construct_at(hamon::addressof(m_value), *that);
		}
		return *this;
	}

	HAMON_CXX14_CONSTEXPR movable_box&
	operator=(movable_box&& that) HAMON_NOEXCEPT
		requires (!hamon::movable<T>)
	{
		static_assert(hamon::is_nothrow_move_constructible<T>::value);
		if (this != hamon::addressof(that))
		{
			m_value.~T();
			hamon::construct_at(hamon::addressof(m_value), hamon::move(*that));
		}
		return *this;
	}
#endif

	HAMON_CXX11_CONSTEXPR bool
	has_value() const HAMON_NOEXCEPT
	{
		return true;
	};

	HAMON_CXX14_CONSTEXPR T&
	operator*() & HAMON_NOEXCEPT
	{
		return m_value;
	}

	HAMON_CXX11_CONSTEXPR T const&
	operator*() const & HAMON_NOEXCEPT
	{
		return m_value;
	}

	HAMON_CXX14_CONSTEXPR T&&
	operator*() && HAMON_NOEXCEPT
	{
		return hamon::move(m_value);
	}

	HAMON_CXX11_CONSTEXPR T const&&
	operator*() const && HAMON_NOEXCEPT
	{
		return hamon::move(m_value);
	}

	HAMON_CXX14_CONSTEXPR T*
	operator->() HAMON_NOEXCEPT
	{
		return hamon::addressof(m_value);
	}

	HAMON_CXX11_CONSTEXPR T const*
	operator->() const HAMON_NOEXCEPT
	{
		return hamon::addressof(m_value);
	}
};

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_MOVABLE_BOX_HPP
