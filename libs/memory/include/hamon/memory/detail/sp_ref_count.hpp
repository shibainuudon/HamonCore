/**
 *	@file	sp_ref_count.hpp
 *
 *	@brief	sp_ref_count を定義
 */

#ifndef HAMON_MEMORY_DETAIL_SP_REF_COUNT_HPP
#define HAMON_MEMORY_DETAIL_SP_REF_COUNT_HPP

#include <hamon/memory/addressof.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/atomic_decrement.hpp>
#include <hamon/atomic/detail/atomic_increment.hpp>
#include <hamon/atomic/detail/atomic_load.hpp>
#include <hamon/atomic/detail/atomic_compare_exchange_weak.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/static_typeinfo.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_MSVC)
// MSVCには、constexpr virtual 関数からメンバ変数にアクセスするとconstexprにできないバグがある
// https://developercommunity.visualstudio.com/t/error-C2131-when-calling-constexpr-virtu/10727589
#define HAMON_CONSTEXPR_VIRTUAL_WORKAROUND
#endif

struct sp_ref_count_base
{
private:
	template <typename T>
	static HAMON_CXX14_CONSTEXPR T increment(T& count) noexcept
	{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
		if (hamon::is_constant_evaluated())
		{
			return ++count;
		}
#endif
		return hamon::detail::atomic_increment(&count);
	}

	template <typename T>
	static HAMON_CXX14_CONSTEXPR T decrement(T& count) noexcept
	{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
		if (hamon::is_constant_evaluated())
		{
			return --count;
		}
#endif
		return hamon::detail::atomic_decrement(&count);
	}

	template <typename T>
	static HAMON_CXX14_CONSTEXPR bool increment_if_not_zero(T& count) noexcept
	{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
		if (hamon::is_constant_evaluated())
		{
			if (count == 0)
			{
				return false;
			}

			++count;
			return true;
		}
#endif
		T t = hamon::detail::atomic_load(&count);
		for (;;)
		{
			if (t == 0)
			{
				return false;
			}

			if (hamon::detail::atomic_compare_exchange_weak(
				&count, &t, t + 1,
				hamon::memory_order::acq_rel,
				hamon::memory_order::relaxed))
			{
				return true;
			}
		}
	}

public:
	HAMON_CXX20_CONSTEXPR virtual ~sp_ref_count_base() noexcept {}

	HAMON_CXX14_CONSTEXPR long use_count() const noexcept
	{
		return m_use_count;
	}

	HAMON_CXX14_CONSTEXPR bool increment_use_count_if_not_zero() noexcept
	{
		return increment_if_not_zero(m_use_count);
	}

	HAMON_CXX14_CONSTEXPR void increment_use_count() noexcept
	{
		increment(m_use_count);
	}

	HAMON_CXX14_CONSTEXPR void increment_weak_count() noexcept
	{
		increment(m_weak_count);
	}

	HAMON_CXX14_CONSTEXPR void decrement_use_count() noexcept
	{
		if (decrement(m_use_count) == 0)
		{
			this->destroy();
			this->decrement_weak_count();
		}
	}

	HAMON_CXX14_CONSTEXPR void decrement_weak_count() noexcept
	{
		if (decrement(m_weak_count) == 0)
		{
			this->delete_this();
		}
	}

	template <typename T>
	HAMON_CXX14_CONSTEXPR T* get_deleter() const noexcept
	{
		void* p = this->v_get_deleter(hamon::static_typeid<T>());
		return p ? static_cast<T*>(p) : nullptr;
	}

private:
	HAMON_CXX20_CONSTEXPR void destroy() noexcept
	{
#if defined(HAMON_CONSTEXPR_VIRTUAL_WORKAROUND)
		if (m_destroy_fnp)
		{
			m_destroy_fnp(this);
			return;
		}
#endif
		this->v_destroy();
	}

	HAMON_CXX20_CONSTEXPR void delete_this() noexcept
	{
#if defined(HAMON_CONSTEXPR_VIRTUAL_WORKAROUND)
		if (m_delete_this_fnp)
		{
			m_delete_this_fnp(this);
			return;
		}
#endif
		this->v_delete_this();
	}

	HAMON_CXX20_CONSTEXPR virtual void v_destroy() noexcept = 0;
	HAMON_CXX20_CONSTEXPR virtual void v_delete_this() noexcept = 0;
	HAMON_CXX20_CONSTEXPR virtual void* v_get_deleter(hamon::static_type_info const&) const noexcept
	{
		return nullptr;
	}

protected:
#if defined(HAMON_CONSTEXPR_VIRTUAL_WORKAROUND)
	void (*m_destroy_fnp)(sp_ref_count_base*) = nullptr;
	void (*m_delete_this_fnp)(sp_ref_count_base*) = nullptr;
#endif

private:
	long	m_use_count = 1;
	long	m_weak_count = 1;
};


template <typename T, typename D>
struct sp_ref_count : public sp_ref_count_base
{
private:
#if defined(HAMON_CONSTEXPR_VIRTUAL_WORKAROUND)
	static HAMON_CXX20_CONSTEXPR void s_destroy(sp_ref_count_base* p)
	{
		static_cast<sp_ref_count*>(p)->sp_ref_count::v_destroy();
	}
#endif

public:
	static HAMON_CXX20_CONSTEXPR sp_ref_count* create(T p, D d)
	{
		return new sp_ref_count{p, hamon::move(d)};
	}

public:
	HAMON_CXX14_CONSTEXPR sp_ref_count(T p, D d)
		: m_ptr(p)
		, m_deleter(hamon::move(d))
	{
#if defined(HAMON_CONSTEXPR_VIRTUAL_WORKAROUND)
		m_destroy_fnp = s_destroy;
#endif
	}

private:
	HAMON_CXX20_CONSTEXPR void v_destroy() noexcept override
	{
		m_deleter(m_ptr);
	}

	HAMON_CXX20_CONSTEXPR void v_delete_this() noexcept override
	{
		delete this;
	}

	HAMON_CXX20_CONSTEXPR void* v_get_deleter(hamon::static_type_info const& ti) const noexcept override
	{
		// [util.smartptr.getdeleter]/1
		if (ti == hamon::static_typeid<D>())
		{
			return const_cast<D*>(hamon::addressof(m_deleter));
		}
		return nullptr;
	}

private:
	T m_ptr;
	D m_deleter;
};

template <typename T, typename D, typename A>
struct sp_ref_count_alloc : public sp_ref_count_base
{
private:
	using Alloc  = typename hamon::allocator_traits<A>::template rebind_alloc<sp_ref_count_alloc>;
	using Traits = typename hamon::allocator_traits<A>::template rebind_traits<sp_ref_count_alloc>;

#if defined(HAMON_CONSTEXPR_VIRTUAL_WORKAROUND)
	static HAMON_CXX20_CONSTEXPR void s_destroy(sp_ref_count_base* p)
	{
		static_cast<sp_ref_count_alloc*>(p)->sp_ref_count_alloc::v_destroy();
	}
	static HAMON_CXX20_CONSTEXPR void s_delete_this(sp_ref_count_base* p)
	{
		static_cast<sp_ref_count_alloc*>(p)->sp_ref_count_alloc::v_delete_this();
	}
#endif

public:
	static HAMON_CXX20_CONSTEXPR sp_ref_count_alloc* create(T p, D d, A const& a)
	{
		Alloc alloc(a);
		auto result = Traits::allocate(alloc, 1);
		Traits::construct(alloc, result, p, hamon::move(d), alloc);
		return result;
	}

public:
	HAMON_CXX14_CONSTEXPR sp_ref_count_alloc(T p, D d, Alloc const& a)
		: m_ptr(p)
		, m_deleter(hamon::move(d))
		, m_alloc(a)
	{
#if defined(HAMON_CONSTEXPR_VIRTUAL_WORKAROUND)
		m_destroy_fnp = s_destroy;
		m_delete_this_fnp = s_delete_this;
#endif
	}

private:
	HAMON_CXX20_CONSTEXPR void v_destroy() noexcept override
	{
		m_deleter(m_ptr);
	}

	HAMON_CXX20_CONSTEXPR void v_delete_this() noexcept override
	{
		auto a = m_alloc;	// Traits::destroy()でm_allocは破棄されてしまうので、コピーが必要
		Traits::destroy(a, this);
		Traits::deallocate(a, this, 1);
	}

	HAMON_CXX20_CONSTEXPR void* v_get_deleter(hamon::static_type_info const& ti) const noexcept override
	{
		// [util.smartptr.getdeleter]/1
		if (ti == hamon::static_typeid<D>())
		{
			return const_cast<D*>(hamon::addressof(m_deleter));
		}
		return nullptr;
	}

private:
	T m_ptr;
	D m_deleter;
	Alloc m_alloc;
};

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4324)	// アラインメント指定子のために構造体がパッドされました

template <typename T, typename A>
struct sp_ref_count_storage : public sp_ref_count_base
{
private:
	using StorageAlloc  = typename hamon::allocator_traits<A>::template rebind_alloc<char>;
	using StorageTraits = typename hamon::allocator_traits<A>::template rebind_traits<char>;
	using ThisAlloc  = typename hamon::allocator_traits<A>::template rebind_alloc<sp_ref_count_storage>;
	using ThisTraits = typename hamon::allocator_traits<A>::template rebind_traits<sp_ref_count_storage>;
	using TAlloc  = typename hamon::allocator_traits<A>::template rebind_alloc<T>;
	using TTraits = typename hamon::allocator_traits<A>::template rebind_traits<T>;

private:
	static hamon::size_t calc_storage_bytes(hamon::size_t n)
	{
		return sizeof(sp_ref_count_storage) + (sizeof(T) * (n-1));
	}

public:
	static sp_ref_count_storage* create(A const& a, hamon::size_t n)
	{
		auto const storage_bytes = calc_storage_bytes(n);
		StorageAlloc storage_alloc(a);
		ThisAlloc this_alloc(a);
		auto storage = StorageTraits::allocate(storage_alloc, storage_bytes);
		auto result = reinterpret_cast<sp_ref_count_storage*>(storage);
		ThisTraits::construct(this_alloc, result, a, n);
		return result;
	}

public:
	sp_ref_count_storage(A const& a, hamon::size_t n)
		: m_alloc(a)
		, m_size(n)
	{}

	T* ptr(void) const
	{
		return reinterpret_cast<T*>(const_cast<char*>(m_storage));
	}

private:
	void v_destroy() noexcept override
	{
		TAlloc t_alloc(m_alloc);
		auto p = ptr();
		for (hamon::size_t i = 0; i < m_size; ++i)
		{
			TTraits::destroy(t_alloc, p);
			++p;
		}
	}

	void v_delete_this() noexcept override
	{
		auto const storage_bytes = calc_storage_bytes(m_size);
		StorageAlloc storage_alloc(m_alloc);
		ThisAlloc this_alloc(m_alloc);
		ThisTraits::destroy(this_alloc, this);
		StorageTraits::deallocate(storage_alloc, reinterpret_cast<char*>(this), storage_bytes);
	}

private:
	A	m_alloc;
	hamon::size_t	m_size;
	alignas(T)	char m_storage[sizeof(T)];
};

HAMON_WARNING_POP()

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_SP_REF_COUNT_HPP
