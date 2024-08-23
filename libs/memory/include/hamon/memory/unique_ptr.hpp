/**
 *	@file	unique_ptr.hpp
 *
 *	@brief	unique_ptr の定義
 */

#ifndef HAMON_MEMORY_UNIQUE_PTR_HPP
#define HAMON_MEMORY_UNIQUE_PTR_HPP

#include <hamon/memory/config.hpp>

#if defined(HAMON_USE_STD_UNIQUE_PTR)

namespace hamon
{

using std::unique_ptr;

}	// namespace hamon

#else

#include <hamon/memory/default_delete.hpp>
#include <hamon/compare/compare_three_way.hpp>
#include <hamon/compare/compare_three_way_result.hpp>
#include <hamon/compare/concepts/three_way_comparable.hpp>
#include <hamon/compare/concepts/three_way_comparable_with.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/add_lvalue_reference.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_pointer.hpp>
#include <hamon/type_traits/is_reference.hpp>
#include <hamon/type_traits/is_rvalue_reference.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_swappable.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/remove_pointer.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/type_identity.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/exchange.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/config.hpp>
#include <ostream>	// basic_ostream

namespace hamon
{

namespace detail
{

// [unique.ptr.single.general]/3
template <typename T, typename D, typename = void>
struct unique_ptr_pointer
{
	using type = T*;
};

template <typename T, typename D>
struct unique_ptr_pointer<T, D,
	hamon::void_t<typename hamon::remove_reference_t<D>::pointer>>
{
	using type = typename hamon::remove_reference_t<D>::pointer;
};

}	// namespace detail

// 20.3.1.3 unique_ptr for single objects[unique.ptr.single]
template <typename T, typename D = hamon::default_delete<T>>
class unique_ptr
{
public:
	static_assert(!hamon::is_rvalue_reference<D>::value, "[unique.ptr.single.general]/1");

	using pointer      = typename hamon::detail::unique_ptr_pointer<T, D>::type;
	using element_type = T;
	using deleter_type = D;

	// [unique.ptr.single.ctor], constructors

	template <typename D2 = D,
		// [unique.ptr.single.ctor]/1
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::negation<hamon::is_pointer<D2>>,
			hamon::is_default_constructible<D2>
		>::value>>
	HAMON_CXX11_CONSTEXPR
	unique_ptr() HAMON_NOEXCEPT
		// [unique.ptr.single.ctor]/3
		: m_ptr{}, m_deleter{}
	{}

	template <typename D2 = D,
		// [unique.ptr.single.ctor]/5
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::negation<hamon::is_pointer<D2>>,
			hamon::is_default_constructible<D2>
		>::value>>
	HAMON_CXX11_CONSTEXPR explicit
	unique_ptr(hamon::type_identity_t<pointer> p) HAMON_NOEXCEPT
		// [unique.ptr.single.ctor]/7
		: m_ptr{p}, m_deleter{}
	{}

	template <typename D2 = D,
		// [unique.ptr.single.ctor]/9
		typename = hamon::enable_if_t<
			hamon::is_constructible<D2, D2 const&>::value>>
	HAMON_CXX11_CONSTEXPR
	unique_ptr(hamon::type_identity_t<pointer> p, D const& d) HAMON_NOEXCEPT
		// [unique.ptr.single.ctor]/11
		: m_ptr{p}, m_deleter{d}
	{}

	template <typename D2 = D,
		hamon::enable_if_t<hamon::conjunction<
			// [unique.ptr.single.ctor]/9
			hamon::is_constructible<D2, hamon::remove_reference_t<D2>&&>,
			// [unique.ptr.single.ctor]/13
			hamon::negation<hamon::is_reference<D2>>
		>::value>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	unique_ptr(hamon::type_identity_t<pointer> p, hamon::remove_reference_t<D>&& d) HAMON_NOEXCEPT
		// [unique.ptr.single.ctor]/11
		: m_ptr{p}, m_deleter{hamon::move(d)}
	{}

	template <typename D2 = D,
		hamon::enable_if_t<hamon::conjunction<
			// [unique.ptr.single.ctor]/9
			hamon::is_constructible<D2, hamon::remove_reference_t<D2>&&>,
			// [unique.ptr.single.ctor]/13
			hamon::is_reference<D2>
		>::value>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	unique_ptr(hamon::type_identity_t<pointer> p, hamon::remove_reference_t<D>&& d) = delete;

	template <typename D2 = D,
		// [unique.ptr.single.ctor]/15
		typename = hamon::enable_if_t<
			hamon::is_move_constructible<D2>::value>>
	HAMON_CXX11_CONSTEXPR
	unique_ptr(unique_ptr&& u) HAMON_NOEXCEPT
		// [unique.ptr.single.ctor]/17
		: m_ptr(u.release())
		, m_deleter(hamon::forward<D>(u.get_deleter()))
	{}

	template <typename D2 = D,
		// [unique.ptr.single.ctor]/1
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::negation<hamon::is_pointer<D2>>,
			hamon::is_default_constructible<D2>
		>::value>>
	HAMON_CXX11_CONSTEXPR
	unique_ptr(hamon::nullptr_t) HAMON_NOEXCEPT
		// [unique.ptr.single.ctor]/3
		: m_ptr{}, m_deleter{}
	{}

	template <typename U, typename E,
		typename P = typename unique_ptr<U, E>::pointer,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_convertible<P, pointer>,   // [unique.ptr.single.ctor]/19.1
			hamon::negation<hamon::is_array<U>>, // [unique.ptr.single.ctor]/19.2
			hamon::conditional_t<                // [unique.ptr.single.ctor]/19.3
				hamon::is_reference<D>::value,
				hamon::is_same<E, D>,
				hamon::is_convertible<E, D>>
		>::value>>
	HAMON_CXX11_CONSTEXPR
	unique_ptr(unique_ptr<U, E>&& u) HAMON_NOEXCEPT
		// [unique.ptr.single.ctor]/21
		: m_ptr(u.release())
		, m_deleter(hamon::forward<E>(u.get_deleter()))
	{}

	// [unique.ptr.single.dtor], destructor
	HAMON_CXX20_CONSTEXPR
	~unique_ptr()
	{
		// [unique.ptr.single.dtor]/1
		if (get())
		{
			get_deleter()(get());
		}
	}

	// [unique.ptr.single.asgn], assignment
	template <typename D2 = D,
		// [unique.ptr.single.asgn]/1
		typename = hamon::enable_if_t<
			hamon::is_move_assignable<D2>::value>>
	HAMON_CXX14_CONSTEXPR unique_ptr&
	operator=(unique_ptr&& u) HAMON_NOEXCEPT
	{
		// [unique.ptr.single.asgn]/3
		reset(u.release());
		get_deleter() = hamon::forward<D>(u.get_deleter());
		// [unique.ptr.single.asgn]/5
		return *this;
	}

	template <typename U, typename E,
		typename P = typename unique_ptr<U, E>::pointer,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_convertible<P, pointer>,   // [unique.ptr.single.asgn]/6.1
			hamon::negation<hamon::is_array<U>>, // [unique.ptr.single.asgn]/6.2
			hamon::is_assignable<D&, E&&>        // [unique.ptr.single.asgn]/6.3
		>::value>>
	HAMON_CXX14_CONSTEXPR unique_ptr&
	operator=(unique_ptr<U, E>&& u) HAMON_NOEXCEPT
	{
		// [unique.ptr.single.asgn]/8
		reset(u.release());
		get_deleter() = hamon::forward<E>(u.get_deleter());
		// [unique.ptr.single.asgn]/10
		return *this;
	}

	HAMON_CXX14_CONSTEXPR unique_ptr&
	operator=(hamon::nullptr_t) HAMON_NOEXCEPT
	{
		// [unique.ptr.single.asgn]/11
		reset();
		// [unique.ptr.single.asgn]/13
		return *this;
	}

	// [unique.ptr.single.observers], observers
	HAMON_NODISCARD	HAMON_CXX11_CONSTEXPR // nodiscard as an extension
	hamon::add_lvalue_reference_t<T> operator*() const
		HAMON_NOEXCEPT_IF_EXPR(*hamon::declval<pointer>())
	{
		// [unique.ptr.single.observers]/2
		return *get();
	}

	HAMON_NODISCARD	HAMON_CXX11_CONSTEXPR // nodiscard as an extension
	pointer operator->() const HAMON_NOEXCEPT
	{
		// [unique.ptr.single.observers]/4
		return get();
	}

	HAMON_NODISCARD	HAMON_CXX11_CONSTEXPR // nodiscard as an extension
	pointer get() const HAMON_NOEXCEPT
	{
		// [unique.ptr.single.observers]/6
		return m_ptr;
	}

	HAMON_NODISCARD	HAMON_CXX14_CONSTEXPR // nodiscard as an extension
	deleter_type& get_deleter() HAMON_NOEXCEPT
	{
		// [unique.ptr.single.observers]/7
		return m_deleter;
	}

	HAMON_NODISCARD	HAMON_CXX11_CONSTEXPR // nodiscard as an extension
	deleter_type const& get_deleter() const HAMON_NOEXCEPT
	{
		// [unique.ptr.single.observers]/7
		return m_deleter;
	}

	HAMON_CXX11_CONSTEXPR explicit
	operator bool() const HAMON_NOEXCEPT
	{
		// [unique.ptr.single.observers]/8
		return get() != nullptr;
	}

	// [unique.ptr.single.modifiers], modifiers
	HAMON_CXX14_CONSTEXPR pointer
	release() HAMON_NOEXCEPT
	{
		// [unique.ptr.single.modifiers]/2
		return hamon::exchange(m_ptr, nullptr);
	}

	HAMON_CXX14_CONSTEXPR void
	reset(pointer p = pointer()) HAMON_NOEXCEPT
	{
		// [unique.ptr.single.modifiers]/3
		auto old_p = hamon::exchange(m_ptr, p);
		if (old_p)
		{
			get_deleter()(old_p);
		}
	}

	HAMON_CXX14_CONSTEXPR void
	swap(unique_ptr& u) HAMON_NOEXCEPT
	{
		// [unique.ptr.single.modifiers]/7
		using std::swap;
		swap(m_ptr, u.m_ptr);
		swap(m_deleter, u.m_deleter);
	}

	// disable copy from lvalue
	unique_ptr(unique_ptr const&) = delete;
	unique_ptr& operator=(unique_ptr const&) = delete;

private:
	pointer			m_ptr;
	deleter_type	m_deleter;
};

// 20.3.1.4 unique_ptr for array objects with a runtime length[unique.ptr.runtime]
template <typename T, typename D>
class unique_ptr<T[], D>
{
public:
	static_assert(!hamon::is_rvalue_reference<D>::value, "[unique.ptr.single.general]/1");

	using pointer      = typename hamon::detail::unique_ptr_pointer<T, D>::type;
	using element_type = T;
	using deleter_type = D;

	// [unique.ptr.runtime.ctor], constructors

	template <typename D2 = D,
		// [unique.ptr.single.ctor]/1
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::negation<hamon::is_pointer<D2>>,
			hamon::is_default_constructible<D2>
		>::value>>
	HAMON_CXX11_CONSTEXPR
	unique_ptr() HAMON_NOEXCEPT
		: m_ptr{}, m_deleter{}
	{}

	template <typename U, typename D2 = D,
		// [unique.ptr.single.ctor]/5
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::negation<hamon::is_pointer<D2>>,
			hamon::is_default_constructible<D2>
		>::value>,
		// [unique.ptr.runtime.ctor]/2
		typename = hamon::enable_if_t<hamon::disjunction<
			hamon::is_same<U, pointer>,
			hamon::conjunction<
				hamon::is_same<pointer, element_type*>,
				hamon::is_pointer<U>,
				hamon::is_convertible<hamon::remove_pointer_t<U>(*)[], element_type(*)[]>>
		>::value>>
	HAMON_CXX11_CONSTEXPR explicit
	unique_ptr(U p) HAMON_NOEXCEPT
		// [unique.ptr.runtime.ctor]/1
		: m_ptr{p}, m_deleter{}
	{}

	template <typename U, typename D2 = D,
		// [unique.ptr.single.ctor]/9
		typename = hamon::enable_if_t<
			hamon::is_constructible<D2, D2 const&>::value
		>,
		// [unique.ptr.runtime.ctor]/4
		typename = hamon::enable_if_t<hamon::disjunction<
			hamon::is_same<U, pointer>,
			hamon::is_same<U, hamon::nullptr_t>,
			hamon::conjunction<
				hamon::is_same<pointer, element_type*>,
				hamon::is_pointer<U>,
				hamon::is_convertible<hamon::remove_pointer_t<U>(*)[], element_type(*)[]>>
		>::value>>
	HAMON_CXX11_CONSTEXPR
	unique_ptr(U p, D const& d) HAMON_NOEXCEPT
		// [unique.ptr.single.ctor]/11
		: m_ptr{p}, m_deleter{d}
	{}

	template <typename U, typename D2 = D,
		// [unique.ptr.single.ctor]/9
		typename = hamon::enable_if_t<
			hamon::is_constructible<D2, hamon::remove_reference_t<D2>&&>::value
		>,
		// [unique.ptr.runtime.ctor]/4
		typename = hamon::enable_if_t<hamon::disjunction<
			hamon::is_same<U, pointer>,
			hamon::is_same<U, hamon::nullptr_t>,
			hamon::conjunction<
				hamon::is_same<pointer, element_type*>,
				hamon::is_pointer<U>,
				hamon::is_convertible<hamon::remove_pointer_t<U>(*)[], element_type(*)[]>>
		>::value>,
		// [unique.ptr.single.ctor]/13
		hamon::enable_if_t<
			!hamon::is_reference<D2>::value>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	unique_ptr(U p, hamon::remove_reference_t<D>&& d) HAMON_NOEXCEPT
		// [unique.ptr.single.ctor]/11
		: m_ptr{p}, m_deleter{hamon::move(d)}
	{}

	template <typename U, typename D2 = D,
		// [unique.ptr.single.ctor]/9
		typename = hamon::enable_if_t<
			hamon::is_constructible<D2, hamon::remove_reference_t<D2>&&>::value
		>,
		// [unique.ptr.runtime.ctor]/4
		typename = hamon::enable_if_t<hamon::disjunction<
			hamon::is_same<U, pointer>,
			hamon::is_same<U, hamon::nullptr_t>,
			hamon::conjunction<
				hamon::is_same<pointer, element_type*>,
				hamon::is_pointer<U>,
				hamon::is_convertible<hamon::remove_pointer_t<U>(*)[], element_type(*)[]>>
		>::value>,
		// [unique.ptr.single.ctor]/13
		hamon::enable_if_t<
			hamon::is_reference<D2>::value>* = nullptr>
	HAMON_CXX11_CONSTEXPR
	unique_ptr(U p, hamon::remove_reference_t<D>&& d) = delete;

	template <typename D2 = D,
		// [unique.ptr.single.ctor]/15
		typename = hamon::enable_if_t<
			hamon::is_move_constructible<D2>::value>>
	HAMON_CXX11_CONSTEXPR
	unique_ptr(unique_ptr&& u) HAMON_NOEXCEPT
		// [unique.ptr.single.ctor]/17
		: m_ptr(u.release())
		, m_deleter(hamon::forward<D>(u.get_deleter()))
	{}

	template <typename U, typename E,
		typename UP = unique_ptr<U, E>,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_array<U>, // [unique.ptr.runtime.ctor]/6.1
			hamon::is_same<pointer, element_type*>, // [unique.ptr.runtime.ctor]/6.2
			hamon::is_same<typename UP::pointer, typename UP::element_type*>, // [unique.ptr.runtime.ctor]/6.3
			hamon::is_convertible<typename UP::element_type(*)[], element_type(*)[]>, // [unique.ptr.runtime.ctor]/6.4
			hamon::conditional_t< // [unique.ptr.runtime.ctor]/6.5
				hamon::is_reference<D>::value,
				hamon::is_same<E, D>,
				hamon::is_convertible<E, D>
			>
		>::value>>
	HAMON_CXX11_CONSTEXPR
	unique_ptr(unique_ptr<U, E>&& u) HAMON_NOEXCEPT
		// [unique.ptr.runtime.ctor]/5
		: m_ptr(u.release())
		, m_deleter(hamon::forward<E>(u.get_deleter()))
	{}

	template <typename D2 = D,
		// [unique.ptr.single.ctor]/1
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::negation<hamon::is_pointer<D2>>,
			hamon::is_default_constructible<D2>
		>::value>>
	HAMON_CXX11_CONSTEXPR
	unique_ptr(hamon::nullptr_t) HAMON_NOEXCEPT
		// [unique.ptr.single.ctor]/3
		: m_ptr{}, m_deleter{}
	{}

	// destructor
	HAMON_CXX20_CONSTEXPR
	~unique_ptr()
	{
		// [unique.ptr.single.dtor]/1
		if (get())
		{
			get_deleter()(get());
		}
	}

	// assignment
	template <typename D2 = D,
		// [unique.ptr.single.asgn]/1
		typename = hamon::enable_if_t<
			hamon::is_move_assignable<D2>::value>>
	HAMON_CXX14_CONSTEXPR unique_ptr&
	operator=(unique_ptr&& u) HAMON_NOEXCEPT
	{
		// [unique.ptr.single.asgn]/3
		reset(u.release());
		get_deleter() = hamon::forward<D>(u.get_deleter());
		// [unique.ptr.single.asgn]/5
		return *this;
	}

	template <typename U, typename E,
		// [unique.ptr.runtime.asgn]/2
		typename UP = unique_ptr<U, E>,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_array<U>, // [unique.ptr.runtime.asgn]/2.1
			hamon::is_same<pointer, element_type*>, // [unique.ptr.runtime.asgn]/2.2
			hamon::is_same<typename UP::pointer, typename UP::element_type*>, // [unique.ptr.runtime.asgn]/2.3
			hamon::is_convertible<typename UP::element_type(*)[], element_type(*)[]>, // [unique.ptr.runtime.asgn]/2.4
			hamon::is_assignable<D&, E&&> // [unique.ptr.runtime.asgn]/2.5
		>::value>>
	HAMON_CXX14_CONSTEXPR unique_ptr&
	operator=(unique_ptr<U, E>&& u) HAMON_NOEXCEPT
	{
		// [unique.ptr.runtime.asgn]/1
		reset(u.release());
		get_deleter() = hamon::forward<E>(u.get_deleter());
		return *this;
	}

	HAMON_CXX14_CONSTEXPR unique_ptr&
	operator=(hamon::nullptr_t) HAMON_NOEXCEPT
	{
		// [unique.ptr.single.asgn]/11
		reset();
		// [unique.ptr.single.asgn]/13
		return *this;
	}

	// [unique.ptr.runtime.observers], observers
	HAMON_NODISCARD	HAMON_CXX11_CONSTEXPR // nodiscard as an extension
	T& operator[](hamon::size_t i) const HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [unique.ptr.runtime.observers]/2
		return get()[i];
	}

	HAMON_NODISCARD	HAMON_CXX11_CONSTEXPR // nodiscard as an extension
	pointer get() const HAMON_NOEXCEPT
	{
		// [unique.ptr.single.observers]/6
		return m_ptr;
	}

	HAMON_NODISCARD	HAMON_CXX14_CONSTEXPR // nodiscard as an extension
	deleter_type& get_deleter() HAMON_NOEXCEPT
	{
		// [unique.ptr.single.observers]/7
		return m_deleter;
	}

	HAMON_NODISCARD	HAMON_CXX11_CONSTEXPR // nodiscard as an extension
	deleter_type const& get_deleter() const HAMON_NOEXCEPT
	{
		// [unique.ptr.single.observers]/7
		return m_deleter;
	}

	HAMON_CXX11_CONSTEXPR explicit
	operator bool() const HAMON_NOEXCEPT
	{
		// [unique.ptr.single.observers]/8
		return get() != nullptr;
	}

	// [unique.ptr.runtime.modifiers], modifiers
	HAMON_CXX14_CONSTEXPR pointer
	release() HAMON_NOEXCEPT
	{
		// [unique.ptr.single.modifiers]/2
		return hamon::exchange(m_ptr, nullptr);
	}

	template <typename U,
		// [unique.ptr.runtime.modifiers]/3
		typename = hamon::enable_if_t<hamon::disjunction<
			hamon::is_same<U, pointer>,
			hamon::conjunction<
				hamon::is_same<pointer, element_type*>,
				hamon::is_pointer<U>,
				hamon::is_convertible<hamon::remove_pointer_t<U>(*)[], element_type(*)[]>>
		>::value>>
	HAMON_CXX14_CONSTEXPR void
	reset(U p) HAMON_NOEXCEPT
	{
		// [unique.ptr.runtime.modifiers]/2
		auto old_p = hamon::exchange(m_ptr, p);
		if (old_p)
		{
			get_deleter()(old_p);
		}
	}

	HAMON_CXX14_CONSTEXPR void
	reset(hamon::nullptr_t = nullptr) HAMON_NOEXCEPT
	{
		// [unique.ptr.runtime.modifiers]/1
		reset(pointer());
	}

	HAMON_CXX14_CONSTEXPR void
	swap(unique_ptr& u) HAMON_NOEXCEPT
	{
		// [unique.ptr.single.modifiers]/7
		using std::swap;
		swap(m_ptr, u.m_ptr);
		swap(m_deleter, u.m_deleter);
	}

	// disable copy from lvalue
	unique_ptr(unique_ptr const&) = delete;
	unique_ptr& operator=(unique_ptr const&) = delete;

private:
	pointer			m_ptr;
	deleter_type	m_deleter;
};

// 20.3.1.6 Specialized algorithms[unique.ptr.special]

template <typename T, typename D,
	// [unique.ptr.special]/1
	typename = hamon::enable_if_t<
		hamon::is_swappable<D>::value>>
HAMON_CXX14_CONSTEXPR void
swap(unique_ptr<T, D>& x, unique_ptr<T, D>& y) HAMON_NOEXCEPT
{
	// [unique.ptr.special]/2
	x.swap(y);
}

template <typename T1, typename D1, typename T2, typename D2>
HAMON_NODISCARD	HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator==(unique_ptr<T1, D1> const& x, unique_ptr<T2, D2> const& y)
{
	// [unique.ptr.special]/3
	return x.get() == y.get();
}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
template <typename T1, typename D1, typename T2, typename D2>
HAMON_NODISCARD	HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator!=(unique_ptr<T1, D1> const& x, unique_ptr<T2, D2> const& y)
{
	return !(x == y);
}
#endif

template <typename T1, typename D1, typename T2, typename D2>
HAMON_NODISCARD	bool	// nodiscard as an extension
operator<(unique_ptr<T1, D1> const& x, unique_ptr<T2, D2> const& y)
{
	// [unique.ptr.special]/4
	using CT = hamon::common_type_t<
		typename unique_ptr<T1, D1>::pointer,
		typename unique_ptr<T2, D2>::pointer>;
	// [unique.ptr.special]/7
	return hamon::less<CT>()(x.get(), y.get());
}

template <typename T1, typename D1, typename T2, typename D2>
HAMON_NODISCARD	bool	// nodiscard as an extension
operator>(unique_ptr<T1, D1> const& x, unique_ptr<T2, D2> const& y)
{
	// [unique.ptr.special]/8
	return y < x;
}

template <typename T1, typename D1, typename T2, typename D2>
HAMON_NODISCARD	bool	// nodiscard as an extension
operator<=(unique_ptr<T1, D1> const& x, unique_ptr<T2, D2> const& y)
{
	// [unique.ptr.special]/9
	return !(y < x);
}

template <typename T1, typename D1, typename T2, typename D2>
HAMON_NODISCARD	bool	// nodiscard as an extension
operator>=(unique_ptr<T1, D1> const& x, unique_ptr<T2, D2> const& y)
{
	// [unique.ptr.special]/10
	return !(x < y);
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
template <typename T1, typename D1, typename T2, typename D2>
requires hamon::three_way_comparable_with<
	typename unique_ptr<T1, D1>::pointer,
	typename unique_ptr<T2, D2>::pointer>
HAMON_NODISCARD	// nodiscard as an extension
hamon::compare_three_way_result_t<
	typename unique_ptr<T1, D1>::pointer,
	typename unique_ptr<T2, D2>::pointer>
operator<=>(unique_ptr<T1, D1> const& x, unique_ptr<T2, D2> const& y)
{
	// [unique.ptr.special]/11
	return hamon::compare_three_way()(x.get(), y.get());
}
#endif

template <typename T, typename D>
HAMON_NODISCARD	HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator==(unique_ptr<T, D> const& x, hamon::nullptr_t) HAMON_NOEXCEPT
{
	// [unique.ptr.special]/12
	return !x;
}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
template <typename T, typename D>
HAMON_NODISCARD	HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator==(hamon::nullptr_t x, unique_ptr<T, D> const& y) HAMON_NOEXCEPT
{
	return y == x;
}

template <typename T, typename D>
HAMON_NODISCARD	HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator!=(unique_ptr<T, D> const& x, hamon::nullptr_t y) HAMON_NOEXCEPT
{
	return !(x == y);
}

template <typename T, typename D>
HAMON_NODISCARD	HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator!=(hamon::nullptr_t x, unique_ptr<T, D> const& y) HAMON_NOEXCEPT
{
	return !(x == y);
}
#endif

template <typename T, typename D>
HAMON_NODISCARD	HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator<(unique_ptr<T, D> const& x, hamon::nullptr_t)
{
	// [unique.ptr.special]/14
	return hamon::less<typename unique_ptr<T, D>::pointer>()(x.get(), nullptr);
}

template <typename T, typename D>
HAMON_NODISCARD	HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator<(hamon::nullptr_t, unique_ptr<T, D> const& x)
{
	// [unique.ptr.special]/14
	return hamon::less<typename unique_ptr<T, D>::pointer>()(nullptr, x.get());
}

template <typename T, typename D>
HAMON_NODISCARD	HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator>(unique_ptr<T, D> const& x, hamon::nullptr_t)
{
	// [unique.ptr.special]/15
	return nullptr < x;
}

template <typename T, typename D>
HAMON_NODISCARD	HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator>(hamon::nullptr_t, unique_ptr<T, D> const& x)
{
	// [unique.ptr.special]/15
	return x < nullptr;
}

template <typename T, typename D>
HAMON_NODISCARD	HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator<=(unique_ptr<T, D> const& x, hamon::nullptr_t)
{
	// [unique.ptr.special]/16
	return !(nullptr < x);
}

template <typename T, typename D>
HAMON_NODISCARD	HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator<=(hamon::nullptr_t, unique_ptr<T, D> const& x)
{
	// [unique.ptr.special]/16
	return !(x < nullptr);
}

template <typename T, typename D>
HAMON_NODISCARD	HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator>=(unique_ptr<T, D> const& x, hamon::nullptr_t)
{
	// [unique.ptr.special]/17
	return !(x < nullptr);
}

template <typename T, typename D>
HAMON_NODISCARD	HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator>=(hamon::nullptr_t, unique_ptr<T, D> const& x)
{
	// [unique.ptr.special]/17
	return !(nullptr < x);
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
template <typename T, typename D>
requires hamon::three_way_comparable<typename unique_ptr<T, D>::pointer>
HAMON_NODISCARD	HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
hamon::compare_three_way_result_t<typename unique_ptr<T, D>::pointer>
operator<=>(unique_ptr<T, D> const& x, hamon::nullptr_t)
{
	// [unique.ptr.special]/18
	return hamon::compare_three_way()(x.get(), static_cast<typename unique_ptr<T, D>::pointer>(nullptr));
}
#endif

// 20.3.1.7 I/O[unique.ptr.io]

namespace detail
{

template <typename Stream, typename UniquePtr, typename = void>
struct can_ostream_unique_ptr : hamon::false_type {};

template <typename Stream, typename UniquePtr>
struct can_ostream_unique_ptr<Stream, UniquePtr,
	hamon::void_t<decltype(hamon::declval<Stream>() << hamon::declval<UniquePtr>().get())>>
    : hamon::true_type {};

}	// namespace detail

template <typename E, typename T, typename Y, typename D,
	// [unique.ptr.io]/1
	typename = hamon::enable_if_t<
		hamon::detail::can_ostream_unique_ptr<
			std::basic_ostream<E, T>&,
			unique_ptr<Y, D> const&
		>::value>>
std::basic_ostream<E, T>&
operator<<(std::basic_ostream<E, T>& os, unique_ptr<Y, D> const& p)
{
	// [unique.ptr.io]/2
	os << p.get();
	// [unique.ptr.io]/3
	return os;
}

#if 0

// 20.3.3 Smart pointer hash support[util.smartptr.hash]

template <typename T, typename D>
struct hash<unique_ptr<T, D>>;

#endif

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_UNIQUE_PTR_HPP
