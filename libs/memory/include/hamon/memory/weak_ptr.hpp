/**
 *	@file	weak_ptr.hpp
 *
 *	@brief	weak_ptr の定義
 */

#ifndef HAMON_MEMORY_WEAK_PTR_HPP
#define HAMON_MEMORY_WEAK_PTR_HPP

#include <hamon/memory/weak_ptr_fwd.hpp>
#include <hamon/memory/config.hpp>

#if !defined(HAMON_USE_STD_SHARED_PTR)

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/memory/detail/sp_compatible.hpp>
#include <hamon/memory/detail/sp_ref_count.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/remove_extent.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 20.3.2.3 Class template weak_ptr[util.smartptr.weak]
template <typename T>
class weak_ptr
{
public:
	using element_type = hamon::remove_extent_t<T>;

	// [util.smartptr.weak.const], constructors
	HAMON_CXX11_CONSTEXPR weak_ptr() noexcept
	{
		// [util.smartptr.weak.const]/1
	}

	template <typename Y,
		// [util.smartptr.weak.const]/3
		typename = hamon::enable_if_t<
			hamon::detail::sp_compatible<Y, T>::value
		>
	>
	HAMON_CXX14_CONSTEXPR weak_ptr(shared_ptr<Y> const& r) noexcept
	{
		// [util.smartptr.weak.const]/4
		if (r.m_ref_count)
		{
			m_ptr = r.m_ptr;
			m_ref_count = r.m_ref_count;
			m_ref_count->increment_weak_count();
		}
	}

	HAMON_CXX14_CONSTEXPR weak_ptr(weak_ptr const& r) noexcept
	{
		// [util.smartptr.weak.const]/4
		if (r.m_ref_count)
		{
			m_ptr = r.m_ptr;
			m_ref_count = r.m_ref_count;
			m_ref_count->increment_weak_count();
		}
	}

	template <typename Y,
		// [util.smartptr.weak.const]/3
		typename = hamon::enable_if_t<
			hamon::detail::sp_compatible<Y, T>::value
		>
	>
	HAMON_CXX14_CONSTEXPR weak_ptr(weak_ptr<Y> const& r) noexcept
	{
		// [util.smartptr.weak.const]/4
		if (r.m_ref_count)
		{
			m_ptr = r.m_ptr;
			m_ref_count = r.m_ref_count;
			m_ref_count->increment_weak_count();
		}
	}

	HAMON_CXX14_CONSTEXPR weak_ptr(weak_ptr&& r) noexcept
	{
		// [util.smartptr.weak.const]/7
		m_ptr = r.m_ptr;
		m_ref_count = r.m_ref_count;

		r.m_ptr = nullptr;
		r.m_ref_count = nullptr;
	}

	template <typename Y,
		// [util.smartptr.weak.const]/6
		typename = hamon::enable_if_t<
			hamon::detail::sp_compatible<Y, T>::value
		>
	>
	HAMON_CXX14_CONSTEXPR weak_ptr(weak_ptr<Y>&& r) noexcept
	{
		// [util.smartptr.weak.const]/7
		m_ptr = r.m_ptr;
		m_ref_count = r.m_ref_count;

		r.m_ptr = nullptr;
		r.m_ref_count = nullptr;
	}

	// [util.smartptr.weak.dest], destructor
	HAMON_CXX20_CONSTEXPR ~weak_ptr()
	{
		// [util.smartptr.weak.dest]/1
		if (m_ref_count)
		{
			m_ref_count->decrement_weak_count();
		}
	}

	// [util.smartptr.weak.assign], assignment
	HAMON_CXX14_CONSTEXPR weak_ptr& operator=(weak_ptr const& r) noexcept
	{
		// [util.smartptr.weak.assign]/1
		weak_ptr(r).swap(*this);

		// [util.smartptr.weak.assign]/2
		return *this;
	}

	template <typename Y,
		typename = hamon::enable_if_t<
			hamon::is_constructible<weak_ptr<T>, weak_ptr<Y> const&>::value
		>
	>
	HAMON_CXX14_CONSTEXPR weak_ptr& operator=(weak_ptr<Y> const& r) noexcept
	{
		// [util.smartptr.weak.assign]/1
		weak_ptr(r).swap(*this);

		// [util.smartptr.weak.assign]/2
		return *this;
	}

	template <typename Y,
		typename = hamon::enable_if_t<
			hamon::is_constructible<weak_ptr<T>, shared_ptr<Y> const&>::value
		>
	>
	HAMON_CXX14_CONSTEXPR weak_ptr& operator=(shared_ptr<Y> const& r) noexcept
	{
		// [util.smartptr.weak.assign]/1
		weak_ptr(r).swap(*this);

		// [util.smartptr.weak.assign]/2
		return *this;
	}

	HAMON_CXX14_CONSTEXPR weak_ptr& operator=(weak_ptr&& r) noexcept
	{
		// [util.smartptr.weak.assign]/4
		weak_ptr(hamon::move(r)).swap(*this);

		// [util.smartptr.weak.assign]/5
		return *this;
	}

	template <typename Y,
		typename = hamon::enable_if_t<
			hamon::is_constructible<weak_ptr<T>, weak_ptr<Y>&&>::value
		>
	>
	HAMON_CXX14_CONSTEXPR weak_ptr& operator=(weak_ptr<Y>&& r) noexcept
	{
		// [util.smartptr.weak.assign]/4
		weak_ptr(hamon::move(r)).swap(*this);

		// [util.smartptr.weak.assign]/5
		return *this;
	}

	// [util.smartptr.weak.mod], modifiers
	HAMON_CXX14_CONSTEXPR void swap(weak_ptr& r) noexcept
	{
		// [util.smartptr.weak.mod]/1
		using hamon::swap;
		swap(m_ptr, r.m_ptr);
		swap(m_ref_count, r.m_ref_count);
	}

	HAMON_CXX14_CONSTEXPR void reset() noexcept
	{
		// [util.smartptr.weak.mod]/2
		weak_ptr().swap(*this);
	}

	// [util.smartptr.weak.obs], observers
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	long use_count() const noexcept
	{
		// [util.smartptr.weak.obs]/1
		return m_ref_count ? m_ref_count->use_count() : 0;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	bool expired() const noexcept
	{
		// [util.smartptr.weak.obs]/2
		return use_count() == 0;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	shared_ptr<T> lock() const noexcept
	{
		// [util.smartptr.weak.obs]/3
		shared_ptr<T> sp;
		if (m_ref_count &&
			m_ref_count->increment_use_count_if_not_zero())
		{
			sp.m_ptr = m_ptr;
			sp.m_ref_count = m_ref_count;
		}
		return sp;
	}

	template <typename U>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	bool owner_before(shared_ptr<U> const& b) const noexcept
	{
		return m_ref_count < b.m_ref_count;
	}

	template <typename U>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	bool owner_before(weak_ptr<U> const& b) const noexcept
	{
		return m_ref_count < b.m_ref_count;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	hamon::size_t owner_hash() const noexcept
	{
		return std::hash<void*>{}(m_ref_count);
	}

	template <typename U>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	bool owner_equal(shared_ptr<U> const& b) const noexcept
	{
		return m_ref_count == b.m_ref_count;
	}

	template <typename U>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	bool owner_equal(weak_ptr<U> const& b) const noexcept
	{
		return m_ref_count == b.m_ref_count;
	}

private:
	element_type*	m_ptr{};
	hamon::detail::sp_ref_count_base*	m_ref_count{};

private:
	template <typename U>
	friend class weak_ptr;

	template <typename U>
	friend class shared_ptr;
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename T>
weak_ptr(shared_ptr<T>) -> weak_ptr<T>;

#endif

// 20.3.2.3.7 Specialized algorithms[util.smartptr.weak.spec]
template <typename T>
HAMON_CXX14_CONSTEXPR void
swap(weak_ptr<T>& a, weak_ptr<T>& b) noexcept
{
	// [util.smartptr.weak.spec]/1
	a.swap(b);
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_WEAK_PTR_HPP
