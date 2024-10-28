/**
 *	@file	inplace_vector_base.hpp
 *
 *	@brief	inplace_vector_base の定義
 */

#ifndef HAMON_INPLACE_VECTOR_DETAIL_INPLACE_VECTOR_BASE_HPP
#define HAMON_INPLACE_VECTOR_DETAIL_INPLACE_VECTOR_BASE_HPP

#include <hamon/config.hpp>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

#include <hamon/algorithm/min.hpp>
#include <hamon/algorithm/ranges/copy_n.hpp>
#include <hamon/algorithm/ranges/fill_n.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/make_move_iterator.hpp>
#include <hamon/memory/construct_at.hpp>
#include <hamon/memory/destroy.hpp>
#include <hamon/memory/detail/uninitialized_value_construct_n_impl.hpp>
#include <hamon/memory/detail/uninitialized_fill_n_impl.hpp>
#include <hamon/memory/detail/uninitialized_copy_n_impl.hpp>
#include <hamon/type_traits/is_nothrow_move_assignable.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_trivially_copy_assignable.hpp>
#include <hamon/type_traits/is_trivially_copy_constructible.hpp>
#include <hamon/type_traits/is_trivially_default_constructible.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include <hamon/type_traits/is_trivially_move_assignable.hpp>
#include <hamon/type_traits/is_trivially_move_constructible.hpp>
#include <hamon/utility/forward.hpp>

namespace hamon
{

namespace detail
{

template <typename T, hamon::size_t N,
	bool = hamon::is_trivially_default_constructible<T>::value>
struct inplace_vector_value
{
private:
	T	m_value[N]{};

protected:
	HAMON_CXX14_CONSTEXPR T*       Begin()       HAMON_NOEXCEPT { return &m_value[0]; }
	HAMON_CXX11_CONSTEXPR T const* Begin() const HAMON_NOEXCEPT { return &m_value[0]; }
};

template <typename T, hamon::size_t N>
struct inplace_vector_value<T, N, false>
{
private:
	alignas(T) char	m_value[sizeof(T) * N]{};

protected:
	T*       Begin()       HAMON_NOEXCEPT { return reinterpret_cast<T*      >(&m_value[0]); }
	T const* Begin() const HAMON_NOEXCEPT { return reinterpret_cast<T const*>(&m_value[0]); }
};

template <typename T, hamon::size_t N>
struct inplace_vector_common : public inplace_vector_value<T, N>
{
private:
	hamon::size_t m_size{};

protected:
	HAMON_CXX11_CONSTEXPR
	hamon::size_t Size() const HAMON_NOEXCEPT
	{
		return m_size;
	}

	HAMON_CXX14_CONSTEXPR T* End() HAMON_NOEXCEPT
	{
		return this->Begin() + this->Size();
	}

	HAMON_CXX11_CONSTEXPR T const* End() const HAMON_NOEXCEPT
	{
		return this->Begin() + this->Size();
	}

	HAMON_CXX14_CONSTEXPR void UncheckedAppendN(hamon::size_t n)
	{
		hamon::detail::uninitialized_value_construct_n_impl(this->End(), n);	// may throw
		m_size += n;
	}

	HAMON_CXX14_CONSTEXPR void UncheckedAppendN(hamon::size_t n, T const& value)
	{
		hamon::detail::uninitialized_fill_n_impl(this->End(), n, value);	// may throw
		m_size += n;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR void UncheckedAppendN(hamon::size_t n, InputIterator first)
	{
		hamon::detail::uninitialized_copy_n_impl(first, n, this->End());	// may throw
		m_size += n;
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR void UncheckedEmplaceBack(Args&&... args)
	{
		hamon::construct_at(this->End(), hamon::forward<Args>(args)...);	// may throw
		m_size += 1;
	}

	HAMON_CXX14_CONSTEXPR void PopBackN(hamon::size_t n) HAMON_NOEXCEPT
	{
		hamon::destroy(this->End() - n, this->End());
		m_size -= n;
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR void UncheckedResize(hamon::size_t sz, Args&&... args)
	{
		// [inplace.vector.capacity]/3,6
		if (sz < m_size)
		{
			this->PopBackN(m_size - sz);
		}
		else if (sz > m_size)
		{
			this->UncheckedAppendN(sz - m_size, hamon::forward<Args>(args)...);	// may throw
		}
	}

	HAMON_CXX14_CONSTEXPR void UncheckedAssignN(hamon::size_t n, T const& value)
	{
		auto const m = hamon::min(n, this->Size());
		using D = hamon::iter_difference_t<T*>;
		hamon::ranges::fill_n(this->Begin(), static_cast<D>(m), value);	// may throw
		this->UncheckedResize(n, value);	// may throw
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR void UncheckedAssignN(hamon::size_t n, InputIterator first)
	{
		auto const m = hamon::min(n, this->Size());
		using D = hamon::iter_difference_t<InputIterator>;
		auto ret = hamon::ranges::copy_n(first, static_cast<D>(m), this->Begin());	// may throw
		this->UncheckedResize(n, ret.in);	// may throw
	}
};

template <typename T, hamon::size_t N,
	bool = hamon::is_trivially_destructible<T>::value>
struct inplace_vector_dtor : public inplace_vector_common<T, N>
{
};

template <typename T, hamon::size_t N>
struct inplace_vector_dtor<T, N, false> : public inplace_vector_common<T, N>
{
	HAMON_CXX20_CONSTEXPR
	~inplace_vector_dtor() HAMON_NOEXCEPT
	{
		if (this->Size() > 0)
		{
			this->PopBackN(this->Size());
		}
	}
};

// [inplace.vector.overview]/6.1
template <typename T, hamon::size_t N,
	bool = hamon::is_trivially_copy_constructible<T>::value>
struct inplace_vector_copy_ctor
	: public inplace_vector_dtor<T, N>
{
	using base = inplace_vector_dtor<T, N>;
	using base::base;

	inplace_vector_copy_ctor()                                           = default;
	inplace_vector_copy_ctor(inplace_vector_copy_ctor &&)                = default;
	inplace_vector_copy_ctor& operator=(inplace_vector_copy_ctor &&)     = default;
	inplace_vector_copy_ctor& operator=(inplace_vector_copy_ctor const&) = default;

	inplace_vector_copy_ctor(inplace_vector_copy_ctor const&)            = default;
};

template <typename T, hamon::size_t N>
struct inplace_vector_copy_ctor<T, N, false>
	: public inplace_vector_dtor<T, N>
{
	using base = inplace_vector_dtor<T, N>;
	using base::base;

	inplace_vector_copy_ctor()                                           = default;
	inplace_vector_copy_ctor(inplace_vector_copy_ctor &&)                = default;
	inplace_vector_copy_ctor& operator=(inplace_vector_copy_ctor &&)     = default;
	inplace_vector_copy_ctor& operator=(inplace_vector_copy_ctor const&) = default;

	HAMON_CXX14_CONSTEXPR
	inplace_vector_copy_ctor(inplace_vector_copy_ctor const& x)
	{
		this->UncheckedAppendN(x.Size(), x.Begin());
	}
};

// [inplace.vector.overview]/6.2
template <typename T, hamon::size_t N,
	bool = hamon::is_trivially_move_constructible<T>::value>
struct inplace_vector_move_ctor
	: public inplace_vector_copy_ctor<T, N>
{
	using base = inplace_vector_copy_ctor<T, N>;
	using base::base;

	inplace_vector_move_ctor()                                           = default;
	inplace_vector_move_ctor(inplace_vector_move_ctor const&)            = default;
	inplace_vector_move_ctor& operator=(inplace_vector_move_ctor &&)     = default;
	inplace_vector_move_ctor& operator=(inplace_vector_move_ctor const&) = default;

	inplace_vector_move_ctor(inplace_vector_move_ctor&&)                 = default;
};

template <typename T, hamon::size_t N>
struct inplace_vector_move_ctor<T, N, false>
	: public inplace_vector_copy_ctor<T, N>
{
	using base = inplace_vector_copy_ctor<T, N>;
	using base::base;

	inplace_vector_move_ctor()                                           = default;
	inplace_vector_move_ctor(inplace_vector_move_ctor const&)            = default;
	inplace_vector_move_ctor& operator=(inplace_vector_move_ctor &&)     = default;
	inplace_vector_move_ctor& operator=(inplace_vector_move_ctor const&) = default;

	HAMON_CXX14_CONSTEXPR
	inplace_vector_move_ctor(inplace_vector_move_ctor&& x)
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_move_constructible<T>::value)
	{
		this->UncheckedAppendN(x.Size(), hamon::make_move_iterator(x.Begin()));
	}
};

// [inplace.vector.overview]/6.3.2
template <typename T, hamon::size_t N,
	bool = hamon::is_trivially_destructible<T>::value &&
	       hamon::is_trivially_copy_constructible<T>::value &&
	       hamon::is_trivially_copy_assignable<T>::value>
struct inplace_vector_copy_assign
	: public inplace_vector_move_ctor<T, N>
{
	using base = inplace_vector_move_ctor<T, N>;
	using base::base;

	inplace_vector_copy_assign()                                             = default;
	inplace_vector_copy_assign(inplace_vector_copy_assign&&)                 = default;
	inplace_vector_copy_assign(inplace_vector_copy_assign const&)            = default;
	inplace_vector_copy_assign& operator=(inplace_vector_copy_assign &&)     = default;

	inplace_vector_copy_assign& operator=(inplace_vector_copy_assign const&) = default;
};

template <typename T, hamon::size_t N>
struct inplace_vector_copy_assign<T, N, false>
	: public inplace_vector_move_ctor<T, N>
{
	using base = inplace_vector_move_ctor<T, N>;
	using base::base;

	inplace_vector_copy_assign()                                             = default;
	inplace_vector_copy_assign(inplace_vector_copy_assign&&)                 = default;
	inplace_vector_copy_assign(inplace_vector_copy_assign const&)            = default;
	inplace_vector_copy_assign& operator=(inplace_vector_copy_assign &&)     = default;

	HAMON_CXX14_CONSTEXPR inplace_vector_copy_assign&
	operator=(inplace_vector_copy_assign const& x)
	{
		this->UncheckedAssignN(x.Size(), x.Begin());
		return *this;
	}
};

// [inplace.vector.overview]/6.3.3
template <typename T, hamon::size_t N,
	bool = hamon::is_trivially_destructible<T>::value &&
	       hamon::is_trivially_move_constructible<T>::value &&
	       hamon::is_trivially_move_assignable<T>::value>
struct inplace_vector_move_assign
	: public inplace_vector_copy_assign<T, N>
{
	using base = inplace_vector_copy_assign<T, N>;
	using base::base;

	inplace_vector_move_assign()                                             = default;
	inplace_vector_move_assign(inplace_vector_move_assign&&)                 = default;
	inplace_vector_move_assign(inplace_vector_move_assign const&)            = default;
	inplace_vector_move_assign& operator=(inplace_vector_move_assign const&) = default;

	inplace_vector_move_assign& operator=(inplace_vector_move_assign &&)     = default;
};

template <typename T, hamon::size_t N>
struct inplace_vector_move_assign<T, N, false>
	: public inplace_vector_copy_assign<T, N>
{
	using base = inplace_vector_copy_assign<T, N>;
	using base::base;

	inplace_vector_move_assign()                                             = default;
	inplace_vector_move_assign(inplace_vector_move_assign&&)                 = default;
	inplace_vector_move_assign(inplace_vector_move_assign const&)            = default;
	inplace_vector_move_assign& operator=(inplace_vector_move_assign const&) = default;

	HAMON_CXX14_CONSTEXPR inplace_vector_move_assign&
	operator=(inplace_vector_move_assign && x) HAMON_NOEXCEPT_IF(
		hamon::is_nothrow_move_assignable<T>::value &&
		hamon::is_nothrow_move_constructible<T>::value)
	{
		this->UncheckedAssignN(x.Size(), hamon::make_move_iterator(x.Begin()));
		return *this;
	}
};

template <typename T, hamon::size_t N>
struct inplace_vector_base
	: public inplace_vector_move_assign<T, N>
{
};

// [inplace.vector.overview]/6
template <typename T>
struct inplace_vector_base<T, 0>
{
	static HAMON_CXX11_CONSTEXPR
	T* Begin() HAMON_NOEXCEPT { return nullptr; }

	static HAMON_CXX11_CONSTEXPR
	T* End() HAMON_NOEXCEPT { return nullptr; }

	static HAMON_CXX11_CONSTEXPR
	hamon::size_t Size() HAMON_NOEXCEPT { return 0; }

	template <typename... Args>
	static HAMON_CXX14_CONSTEXPR
	void UncheckedAppendN(Args&&...) HAMON_NOEXCEPT {}

	template <typename... Args>
	static HAMON_CXX14_CONSTEXPR
	void UncheckedEmplaceBack(Args&&...) HAMON_NOEXCEPT {}

	template <typename... Args>
	static HAMON_CXX14_CONSTEXPR
	void PopBackN(Args&&...) HAMON_NOEXCEPT {}

	template <typename... Args>
	static HAMON_CXX14_CONSTEXPR
	void UncheckedResize(Args&&...) HAMON_NOEXCEPT {}

	template <typename... Args>
	static HAMON_CXX14_CONSTEXPR
	void UncheckedAssignN(Args&&...) HAMON_NOEXCEPT {}
};

}	// namespace detail

}	// namespace hamon

HAMON_WARNING_POP()

#endif // HAMON_INPLACE_VECTOR_DETAIL_INPLACE_VECTOR_BASE_HPP
