/**
 *	@file	shared_ptr.hpp
 *
 *	@brief	shared_ptr の定義
 */

#ifndef HAMON_MEMORY_SHARED_PTR_HPP
#define HAMON_MEMORY_SHARED_PTR_HPP

#include <hamon/memory/shared_ptr_fwd.hpp>
#include <hamon/memory/weak_ptr_fwd.hpp>
#include <hamon/memory/enable_shared_from_this_fwd.hpp>
#include <hamon/memory/config.hpp>

#if !defined(HAMON_USE_STD_SHARED_PTR)

#include <hamon/memory/bad_weak_ptr.hpp>
#include <hamon/memory/default_delete.hpp>
#include <hamon/memory/unique_ptr.hpp>
#include <hamon/memory/detail/sp_invocable_default_delete.hpp>
#include <hamon/memory/detail/sp_invocable_deleter.hpp>
#include <hamon/memory/detail/sp_convertible.hpp>
#include <hamon/memory/detail/sp_compatible.hpp>
#include <hamon/memory/detail/sp_ref_count.hpp>
#include <hamon/compare/compare_three_way.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/functional/ref.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_reference.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/type_traits/remove_extent.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/config.hpp>
#include <functional>	// std::hash
#include <ostream>

// 20.3.2 Shared-ownership pointers[util.sharedptr]

// TODO:
// * 例外が投げられたときの対応

namespace hamon
{

namespace detail
{

struct sp_access;

}	// namespace detail

// 20.3.2.2 Class template shared_ptr[util.smartptr.shared]
template <typename T>
class shared_ptr
{
public:
	using element_type = hamon::remove_extent_t<T>;
	using weak_type    = weak_ptr<T>;

private:
	template <typename U, typename Y,
		typename = hamon::enable_if_t<
			hamon::is_convertible<
				U*,
				hamon::enable_shared_from_this<Y> const*
			>::value
		>
	>
	HAMON_CXX14_CONSTEXPR void
	EnableWeakThis(hamon::enable_shared_from_this<Y> const* e, U* ptr) noexcept
	{
		using RawY = hamon::remove_cv_t<Y>;
		if (e && e->weak_this.expired())
		{
			e->weak_this = shared_ptr<RawY>(
				*this, const_cast<RawY*>(static_cast<Y const*>(ptr)));
		}
	}

	HAMON_CXX14_CONSTEXPR void
	EnableWeakThis(...) noexcept
	{}

	template <typename U, typename D>
	HAMON_CXX14_CONSTEXPR void Construct(U p, D d)
	{
		using RefCount = hamon::detail::sp_ref_count<U, D>;
		m_ref_count = RefCount::create(p, hamon::move(d));
		m_ptr = p;
		EnableWeakThis(p, p);
	}

	template <typename U, typename D, typename A>
	HAMON_CXX14_CONSTEXPR void Construct(U p, D d, A const& a)
	{
		using RefCount = hamon::detail::sp_ref_count_alloc<U, D, A>;
		m_ref_count = RefCount::create(p, hamon::move(d), a);
		m_ptr = p;
		EnableWeakThis(p, p);
	}

	template <typename Y>
	HAMON_CXX14_CONSTEXPR void
	CopyConstruct(shared_ptr<Y> const& r, element_type* p) noexcept
	{
		m_ptr = p;
		m_ref_count = r.m_ref_count;

		if (m_ref_count)
		{
			m_ref_count->increment_use_count();
		}
	}

	template <typename Y>
	HAMON_CXX14_CONSTEXPR void
	MoveConstruct(shared_ptr<Y>&& r, element_type* p) noexcept
	{
		m_ptr = p;
		m_ref_count = r.m_ref_count;

		r.m_ptr = nullptr;
		r.m_ref_count = nullptr;
	}

	template <typename Y, typename D,
		hamon::enable_if_t<
			hamon::is_reference<D>::value
		>* = nullptr
	>
	HAMON_CXX14_CONSTEXPR void
	ConstructFromUniquePtr(hamon::unique_ptr<Y, D>&& r)
	{
		Construct(r.release(), hamon::ref(r.get_deleter()));
	}

	template <typename Y, typename D,
		hamon::enable_if_t<
			!hamon::is_reference<D>::value
		>* = nullptr
	>
	HAMON_CXX14_CONSTEXPR void
	ConstructFromUniquePtr(hamon::unique_ptr<Y, D>&& r)
	{
		Construct(r.release(), hamon::move(r.get_deleter()));
	}

	template <typename U, typename A>
	void ConstructStorage(A const& a, hamon::size_t n)
	{
		using RefCount = hamon::detail::sp_ref_count_storage<U, A>;
		auto r = RefCount::create(a, n);
		auto p = r->ptr();
		m_ref_count = r;
		m_ptr = p;
		EnableWeakThis(p, p);
	}

public:
	// [util.smartptr.shared.const], constructors
	HAMON_CXX11_CONSTEXPR
	shared_ptr() noexcept
	{}

	HAMON_CXX11_CONSTEXPR
	shared_ptr(hamon::nullptr_t) noexcept
		: shared_ptr()
	{}

	template <
		typename Y,
		// [util.smartptr.shared.const]/4
		typename = hamon::enable_if_t<!hamon::is_void<Y>::value>,
		// [util.smartptr.shared.const]/3
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::detail::sp_invocable_default_delete<T, Y>,
			hamon::detail::sp_convertible<Y, T>
		>::value>
	>
	HAMON_CXX14_CONSTEXPR explicit
	shared_ptr(Y* p)
	{
		using Deleter = hamon::conditional_t<
			hamon::is_array<T>::value,
			hamon::default_delete<Y[]>,
			hamon::default_delete<Y>
		>;
		Construct(p, Deleter{});
	}

	template <typename Y, typename D,
		// [util.smartptr.shared.const]/9
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_move_constructible<D>,
			hamon::detail::sp_invocable_deleter<D, Y*>,
			hamon::detail::sp_convertible<Y, T>
		>::value>
	>
	HAMON_CXX14_CONSTEXPR
	shared_ptr(Y* p, D d)
	{
		Construct(p, hamon::move(d));
	}

	template <typename Y, typename D, typename A,
		// [util.smartptr.shared.const]/9
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_move_constructible<D>,
			hamon::detail::sp_invocable_deleter<D, Y*>,
			hamon::detail::sp_convertible<Y, T>
		>::value>
	>
	HAMON_CXX14_CONSTEXPR
	shared_ptr(Y* p, D d, A a)
	{
		Construct(p, hamon::move(d), a);
	}

	template <typename D,
		// [util.smartptr.shared.const]/9
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_move_constructible<D>,
			hamon::detail::sp_invocable_deleter<D, hamon::nullptr_t>
		>::value>
	>
	HAMON_CXX14_CONSTEXPR
	shared_ptr(hamon::nullptr_t p, D d)
	{
		Construct(p, hamon::move(d));
	}

	template <typename D, typename A,
		// [util.smartptr.shared.const]/9
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_move_constructible<D>,
			hamon::detail::sp_invocable_deleter<D, hamon::nullptr_t>
		>::value>
	>
	HAMON_CXX14_CONSTEXPR
	shared_ptr(hamon::nullptr_t p, D d, A a)
	{
		Construct(p, hamon::move(d), a);
	}

	template <typename Y>
	HAMON_CXX14_CONSTEXPR
	shared_ptr(shared_ptr<Y> const& r, element_type* p) noexcept
	{
		CopyConstruct(r, p);
	}

	template <typename Y>
	HAMON_CXX14_CONSTEXPR
	shared_ptr(shared_ptr<Y>&& r, element_type* p) noexcept
	{
		MoveConstruct(hamon::move(r), p);
	}

	HAMON_CXX14_CONSTEXPR
	shared_ptr(shared_ptr const& r) noexcept
	{
		// [util.smartptr.shared.const]/19
		CopyConstruct(r, r.m_ptr);
	}

	template <typename Y,
		// [util.smartptr.shared.const]/18
		typename = hamon::enable_if_t<
			hamon::detail::sp_compatible<Y, T>::value
		>
	>
	HAMON_CXX14_CONSTEXPR
	shared_ptr(shared_ptr<Y> const& r) noexcept
	{
		// [util.smartptr.shared.const]/19
		CopyConstruct(r, r.m_ptr);
	}

	HAMON_CXX14_CONSTEXPR
	shared_ptr(shared_ptr&& r) noexcept
	{
		// [util.smartptr.shared.const]/22
		MoveConstruct(hamon::move(r), r.m_ptr);
	}

	template <typename Y,
		// [util.smartptr.shared.const]/21
		typename = hamon::enable_if_t<
			hamon::detail::sp_compatible<Y, T>::value
		>
	>
	HAMON_CXX14_CONSTEXPR
	shared_ptr(shared_ptr<Y>&& r) noexcept
	{
		// [util.smartptr.shared.const]/22
		MoveConstruct(hamon::move(r), r.m_ptr);
	}

	template <typename Y,
		// [util.smartptr.shared.const]/24
		typename = hamon::enable_if_t<
			hamon::detail::sp_compatible<Y, T>::value
		>
	>
	HAMON_CXX14_CONSTEXPR explicit
	shared_ptr(weak_ptr<Y> const& r)
	{
		// [util.smartptr.shared.const]/27
		if (r.m_ref_count &&
			r.m_ref_count->increment_use_count_if_not_zero())
		{
			m_ptr = r.m_ptr;
			m_ref_count = r.m_ref_count;
		}
		else
		{
			hamon::detail::throw_bad_weak_ptr();
		}
	}

	template <typename Y, typename D,
		// [util.smartptr.shared.const]/28
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::detail::sp_compatible<Y, T>,
			hamon::is_convertible<
				typename hamon::unique_ptr<Y, D>::pointer,
				element_type*>
		>::value>
	>
	HAMON_CXX14_CONSTEXPR
	shared_ptr(hamon::unique_ptr<Y, D>&& r)
	{
		// [util.smartptr.shared.const]/29
		if (r.get() == nullptr)
		{
			return;
		}

		ConstructFromUniquePtr(hamon::move(r));
	}

	// [util.smartptr.shared.dest], destructor
	HAMON_CXX20_CONSTEXPR ~shared_ptr()
	{
		// [util.smartptr.shared.dest]/1
		if (m_ref_count)
		{
			m_ref_count->decrement_use_count();
		}
	}

	// [util.smartptr.shared.assign], assignment
	HAMON_CXX14_CONSTEXPR
	shared_ptr& operator=(shared_ptr const& r) noexcept
	{
		// [util.smartptr.shared.assign]/1
		shared_ptr(r).swap(*this);

		// [util.smartptr.shared.assign]/2
		return *this;
	}

	template <typename Y,
		typename = hamon::enable_if_t<
			hamon::is_constructible<
				shared_ptr<T>,
				shared_ptr<Y> const&
			>::value
		>
	>
	HAMON_CXX14_CONSTEXPR
	shared_ptr& operator=(shared_ptr<Y> const& r) noexcept
	{
		// [util.smartptr.shared.assign]/1
		shared_ptr(r).swap(*this);

		// [util.smartptr.shared.assign]/2
		return *this;
	}

	HAMON_CXX14_CONSTEXPR
	shared_ptr& operator=(shared_ptr&& r) noexcept
	{
		// [util.smartptr.shared.assign]/4
		shared_ptr(hamon::move(r)).swap(*this);

		// [util.smartptr.shared.assign]/5
		return *this;
	}

	template <typename Y,
		typename = hamon::enable_if_t<
			hamon::is_constructible<
				shared_ptr<T>,
				shared_ptr<Y>&&
			>::value
		>
	>
	HAMON_CXX14_CONSTEXPR
	shared_ptr& operator=(shared_ptr<Y>&& r) noexcept
	{
		// [util.smartptr.shared.assign]/4
		shared_ptr(hamon::move(r)).swap(*this);

		// [util.smartptr.shared.assign]/5
		return *this;
	}

	template <typename Y, typename D,
		typename = hamon::enable_if_t<
			hamon::is_constructible<
				shared_ptr<T>,
				hamon::unique_ptr<Y, D>&&
			>::value
		>
	>
	HAMON_CXX14_CONSTEXPR
	shared_ptr& operator=(hamon::unique_ptr<Y, D>&& r)
	{
		// [util.smartptr.shared.assign]/6
		shared_ptr(hamon::move(r)).swap(*this);

		// [util.smartptr.shared.assign]/7
		return *this;
	}

	// [util.smartptr.shared.mod], modifiers
	HAMON_CXX14_CONSTEXPR void swap(shared_ptr& r) noexcept
	{
		// [util.smartptr.shared.mod]/1
		using std::swap;
		swap(m_ptr, r.m_ptr);
		swap(m_ref_count, r.m_ref_count);
	}

	HAMON_CXX14_CONSTEXPR void reset() noexcept
	{
		// [util.smartptr.shared.mod]/2
		shared_ptr().swap(*this);
	}

	template <typename Y,
		typename = hamon::enable_if_t<
			hamon::is_constructible<shared_ptr<T>, Y*>::value
		>
	>
	HAMON_CXX14_CONSTEXPR void reset(Y* p)
	{
		// [util.smartptr.shared.mod]/3
		shared_ptr(p).swap(*this);
	}

	template <typename Y, typename D,
		typename = hamon::enable_if_t<
			hamon::is_constructible<shared_ptr<T>, Y*, D>::value
		>
	>
	HAMON_CXX14_CONSTEXPR void reset(Y* p, D d)
	{
		// [util.smartptr.shared.mod]/4
		shared_ptr(p, d).swap(*this);
	}

	template <typename Y, typename D, typename A,
		typename = hamon::enable_if_t<
			hamon::is_constructible<shared_ptr<T>, Y*, D, A>::value
		>
	>
	HAMON_CXX14_CONSTEXPR void reset(Y* p, D d, A a)
	{
		// [util.smartptr.shared.mod]/5
		shared_ptr(p, d, a).swap(*this);
	}

	// [util.smartptr.shared.obs], observers
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	element_type* get() const noexcept
	{
		// [util.smartptr.shared.obs]/1
		return m_ptr;
	}

	template <typename T2 = T,
		// [util.smartptr.shared.obs]/4
		typename = hamon::enable_if_t<!hamon::disjunction<
			hamon::is_array<T2>,
			hamon::is_void<T2>
		>::value>
	>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	T2& operator*() const noexcept
	{
		// [util.smartptr.shared.obs]/3
		return *get();
	}

	template <typename T2 = T,
		// [util.smartptr.shared.obs]/7
		typename = hamon::enable_if_t<!hamon::is_array<T2>::value>
	>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	T2* operator->() const noexcept
	{
		// [util.smartptr.shared.obs]/6
		return get();
	}

	template <typename T2 = T,
		typename Elem = element_type,
		// [util.smartptr.shared.obs]/11
		typename = hamon::enable_if_t<hamon::is_array<T2>::value>
	>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	Elem& operator[](hamon::ptrdiff_t i) const noexcept	// noexcept as an extension
	{
		// [util.smartptr.shared.obs]/9
		return get()[i];
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	long use_count() const noexcept
	{
		// [util.smartptr.shared.obs]/13
		return m_ref_count ? m_ref_count->use_count() : 0;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	explicit operator bool() const noexcept
	{
		// [util.smartptr.shared.obs]/17
		return get() != nullptr;
	}

	template <typename U>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	bool owner_before(shared_ptr<U> const& b) const noexcept
	{
		// [util.smartptr.shared.obs]/18
		return m_ref_count < b.m_ref_count;
	}

	template <typename U>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	bool owner_before(weak_ptr<U> const& b) const noexcept
	{
		// [util.smartptr.shared.obs]/18
		return m_ref_count < b.m_ref_count;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	hamon::size_t owner_hash() const noexcept
	{
		// [util.smartptr.shared.obs]/19
		return std::hash<void*>{}(m_ref_count);
	}

	template <typename U>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	bool owner_equal(shared_ptr<U> const& b) const noexcept
	{
		// [util.smartptr.shared.obs]/20
		return m_ref_count == b.m_ref_count;
	}

	template <typename U>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	bool owner_equal(weak_ptr<U> const& b) const noexcept
	{
		// [util.smartptr.shared.obs]/20
		return m_ref_count == b.m_ref_count;
	}

private:
	element_type*	m_ptr{};
	hamon::detail::sp_ref_count_base*	m_ref_count{};

private:
	template <typename U>
	friend class shared_ptr;

	template <typename U>
	friend class weak_ptr;

	friend struct hamon::detail::sp_access;
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename T>
shared_ptr(weak_ptr<T>) -> shared_ptr<T>;

template <typename T, typename D>
shared_ptr(unique_ptr<T, D>) -> shared_ptr<T>;

#endif

// 20.3.2.2.8 Comparison[util.smartptr.shared.cmp]
template <typename T, typename U>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator==(shared_ptr<T> const& a, shared_ptr<U> const& b) noexcept
{
	// [util.smartptr.shared.cmp]/1
	return a.get() == b.get();
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename T, typename U>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::strong_ordering	// nodiscard as an extension
operator<=>(shared_ptr<T> const& a, shared_ptr<U> const& b) noexcept
{
	// [util.smartptr.shared.cmp]/3
	return hamon::compare_three_way()(a.get(), b.get());
}

#else

template <typename T, typename U>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator!=(shared_ptr<T> const& a, shared_ptr<U> const& b) noexcept
{
	return !(a == b);
}

template <typename T, typename U>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator<(shared_ptr<T> const& a, shared_ptr<U> const& b) noexcept
{
	using CT = hamon::common_type_t<
		typename shared_ptr<T>::element_type*,
		typename shared_ptr<U>::element_type*>;
	return hamon::less<CT>()(a.get(), b.get());
}

template <typename T, typename U>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator>(shared_ptr<T> const& a, shared_ptr<U> const& b) noexcept
{
	return b < a;
}

template <typename T, typename U>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator<=(shared_ptr<T> const& a, shared_ptr<U> const& b) noexcept
{
	return !(b < a);
}

template <typename T, typename U>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator>=(shared_ptr<T> const& a, shared_ptr<U> const& b) noexcept
{
	return !(a < b);
}

#endif

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator==(shared_ptr<T> const& a, hamon::nullptr_t) noexcept
{
	// [util.smartptr.shared.cmp]/2
	return !a;
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::strong_ordering	// nodiscard as an extension
operator<=>(shared_ptr<T> const& a, hamon::nullptr_t) noexcept
{
	// [util.smartptr.shared.cmp]/5
	return hamon::compare_three_way()(a.get(),
		static_cast<typename shared_ptr<T>::element_type*>(nullptr));
}

#else

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator!=(shared_ptr<T> const& a, hamon::nullptr_t b) noexcept
{
	return !(a == b);
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator<(shared_ptr<T> const& a, hamon::nullptr_t b) noexcept
{
	return hamon::less<typename shared_ptr<T>::element_type*>()(a.get(), b);
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator>(shared_ptr<T> const& a, hamon::nullptr_t b) noexcept
{
	return b < a;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator<=(shared_ptr<T> const& a, hamon::nullptr_t b) noexcept
{
	return !(b < a);
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator>=(shared_ptr<T> const& a, hamon::nullptr_t b) noexcept
{
	return !(a < b);
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator==(hamon::nullptr_t a, shared_ptr<T> const& b) noexcept
{
	return b == a;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator!=(hamon::nullptr_t a, shared_ptr<T> const& b) noexcept
{
	return !(a == b);
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator<(hamon::nullptr_t a, shared_ptr<T> const& b) noexcept
{
	return hamon::less<typename shared_ptr<T>::element_type*>()(a, b.get());
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator>(hamon::nullptr_t a, shared_ptr<T> const& b) noexcept
{
	return b < a;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator<=(hamon::nullptr_t a, shared_ptr<T> const& b) noexcept
{
	return !(b < a);
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator>=(hamon::nullptr_t a, shared_ptr<T> const& b) noexcept
{
	return !(a < b);
}

#endif

// 20.3.2.2.9 Specialized algorithms[util.smartptr.shared.spec]
template <typename T>
HAMON_CXX14_CONSTEXPR void
swap(shared_ptr<T>& a, shared_ptr<T>& b) noexcept
{
	// [util.smartptr.shared.spec]/1
	a.swap(b);
}

// 20.3.2.2.12 I/O[util.smartptr.shared.io]
template <typename E, typename T, typename Y>
std::basic_ostream<E, T>&
operator<<(std::basic_ostream<E, T>& os, shared_ptr<Y> const& p)
{
	// [util.smartptr.shared.io]/1
	os << p.get();

	// [util.smartptr.shared.io]/2
	return os;
}


// 20.3.3 Smart pointer hash support[util.smartptr.hash]
//template <typename T> struct hash<shared_ptr<T>>;


//// [util.smartptr.atomic], atomic smart pointers
//template <typename T> struct atomic;
//template <typename T> struct atomic<shared_ptr<T>>;
//template <typename T> struct atomic<weak_ptr<T>>;

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_SHARED_PTR_HPP
