/**
 *	@file	vector_base.hpp
 *
 *	@brief	vector_base の定義
 */

#ifndef HAMON_QVM_DETAIL_VECTOR_BASE_HPP
#define HAMON_QVM_DETAIL_VECTOR_BASE_HPP

#include <hamon/algorithm/swap_ranges.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_swappable.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/serialization/access.hpp>
#include <hamon/serialization/nvp.hpp>
#include <hamon/config.hpp>
#include <cstdlib>		// std::abort
#include <stdexcept>	// std::out_of_range

namespace hamon
{

namespace qvm
{

namespace detail
{

template <typename T, hamon::size_t N>
struct array_traits
{
	using type = T[N];

	static HAMON_CONSTEXPR T&
	ref(type const& t, hamon::size_t n) HAMON_NOEXCEPT
	{
		return const_cast<T&>(t[n]);
	}

	static HAMON_CONSTEXPR T*
	ptr(type const& t) HAMON_NOEXCEPT
	{
		return const_cast<T*>(t);
	}
};

template <typename T>
struct array_traits<T, 0>
{
	struct type {};

	static HAMON_CONSTEXPR T&
	ref(type const&, hamon::size_t) HAMON_NOEXCEPT
	{
		return *static_cast<T*>(nullptr);
	}

	static HAMON_CONSTEXPR T*
	ptr(type const&) HAMON_NOEXCEPT
	{
		return nullptr;
	}
};

template <typename T, hamon::size_t N>
class vector_base
{
public:
	using value_type             = T;
	using pointer                = value_type*;
	using const_pointer          = value_type const*;
	using reference              = value_type&;
	using const_reference        = value_type const&;
	using size_type              = hamon::size_t;
	using difference_type        = hamon::ptrdiff_t;
	using iterator               = pointer;
	using const_iterator         = const_pointer;
	using reverse_iterator       = hamon::reverse_iterator<iterator>;
	using const_reverse_iterator = hamon::reverse_iterator<const_iterator>;

private:
	using traits_type = array_traits<T, N>;
	using elems_type = typename traits_type::type;

private:
	HAMON_NO_UNIQUE_ADDRESS elems_type m_elems;

public:
	/**
	 *	@brief	デフォルトコンストラクタ
	 */
	HAMON_CONSTEXPR
	vector_base() HAMON_NOEXCEPT
		: m_elems{}
	{}
	
	/**
	 *	@brief	スカラー型N個のコンストラクタ
	 */
	template <typename... Args,
		typename = hamon::enable_if_t<
			(sizeof...(Args) == N) &&
			hamon::conjunction<
				hamon::is_convertible<Args, T>...
			>::value
		>
	>
	HAMON_CONSTEXPR
	vector_base(Args const&... args) HAMON_NOEXCEPT
		: m_elems{static_cast<T>(args)...}
	{}

	/**
	 *	@brief	vector_base<U, N>からのコンストラクタ
	 */
	template <typename U>
	HAMON_CONSTEXPR
	vector_base(vector_base<U, N> const& rhs) HAMON_NOEXCEPT
		: vector_base{ rhs, hamon::make_index_sequence<N>{} }
	{}

private:
	template <typename U, hamon::size_t... Is>
	HAMON_CONSTEXPR
	vector_base(vector_base<U, N> const& v, hamon::index_sequence<Is...>) HAMON_NOEXCEPT
		: vector_base{ v[Is]... }
	{}

public:
	/**
	 *	@brief	size
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	size() const HAMON_NOEXCEPT
	{
		return N;
	}

	/**
	 *	@brief	max_size
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	max_size() const HAMON_NOEXCEPT
	{
		return N;
	}

	/**
	 *	@brief	empty
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR bool
	empty() const HAMON_NOEXCEPT
	{
		return size() == 0;
	}

	/**
	 *	@brief	operator[]
	 */
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR reference
	operator[](size_type i) HAMON_NOEXCEPT
	{
		return traits_type::ref(m_elems, i);
	}

	/**
	 *	@brief	operator[]
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR const_reference
	operator[](size_type i) const HAMON_NOEXCEPT
	{
		return traits_type::ref(m_elems, i);
	}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// unreachable code

	/**
	 *	@brief	at
	 */
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR reference
	at(size_type i)
	{
		return i < N ?
			traits_type::ref(m_elems, i) :
			(throw_out_of_range("qvm::vector::at"), traits_type::ref(m_elems, 0));
	}

	/**
	 *	@brief	at
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR const_reference
	at(size_type i) const
	{
		return i < N ?
			traits_type::ref(m_elems, i) :
			(throw_out_of_range("qvm::vector::at"), traits_type::ref(m_elems, 0));
	}

HAMON_WARNING_POP()

	/**
	 *	@brief	begin
	 */
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR iterator
	begin() HAMON_NOEXCEPT
	{
		return iterator(data());
	}

	/**
	 *	@brief	begin
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR const_iterator
	begin() const HAMON_NOEXCEPT
	{
		return const_iterator(data());
	}

	/**
	 *	@brief	end
	 */
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR iterator
	end() HAMON_NOEXCEPT
	{
		return iterator(data() + N);
	}

	/**
	 *	@brief	end
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR const_iterator
	end() const HAMON_NOEXCEPT
	{
		return const_iterator(data() + N);
	}

	/**
	 *	@brief	rbegin
	 */
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR reverse_iterator
	rbegin() HAMON_NOEXCEPT
	{
		return reverse_iterator(end());
	}

	/**
	 *	@brief	rbegin
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR const_reverse_iterator
	rbegin() const HAMON_NOEXCEPT
	{
		return const_reverse_iterator(end());
	}

	/**
	 *	@brief	rend
	 */
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR reverse_iterator
	rend() HAMON_NOEXCEPT
	{
		return reverse_iterator(begin());
	}

	/**
	 *	@brief	rend
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR const_reverse_iterator
	rend() const HAMON_NOEXCEPT
	{
		return const_reverse_iterator(begin());
	}

	/**
	 *	@brief	cbegin
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR const_iterator
	cbegin() const HAMON_NOEXCEPT
	{
		return const_iterator(data());
	}

	/**
	 *	@brief	cend
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR const_iterator
	cend() const HAMON_NOEXCEPT
	{
		return const_iterator(data() + N);
	}

	/**
	 *	@brief	crbegin
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR const_reverse_iterator
	crbegin() const HAMON_NOEXCEPT
	{
		return const_reverse_iterator(end());
	}

	/**
	 *	@brief	crend
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR const_reverse_iterator
	crend() const HAMON_NOEXCEPT
	{
		return const_reverse_iterator(begin());
	}

	/**
	 *	@brief	data
	 */
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR pointer
	data(void) HAMON_NOEXCEPT
	{
		return traits_type::ptr(m_elems);
	}

	/**
	 *	@brief	data
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR const_pointer
	data(void) const HAMON_NOEXCEPT
	{
		return traits_type::ptr(m_elems);
	}

	/**
	 *	@brief	swap
	 */
	HAMON_CXX14_CONSTEXPR void
	swap(vector_base& other)
		HAMON_NOEXCEPT_IF(N == 0 || hamon::is_nothrow_swappable<T>::value)
	{
		hamon::swap_ranges(begin(), end(), other.begin());
	}

private:
	HAMON_NORETURN static void throw_out_of_range(char const* msg)
	{
#if !defined(HAMON_NO_EXCEPTIONS)
		throw std::out_of_range(msg);
#else
		(void)msg;
		std::abort();
#endif
	}

private:
	/**
	 *	@brief	シリアライズ
	 */
	friend class hamon::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar)
	{
		ar & HAMON_SERIALIZATION_NVP(m_elems);
	}
};

/**
 *	@brief	swap
 */
template <typename T, hamon::size_t N>
inline HAMON_CXX14_CONSTEXPR void
swap(vector_base<T, N>& lhs, vector_base<T, N>& rhs)
HAMON_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
{
	lhs.swap(rhs);
}

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_DETAIL_VECTOR_BASE_HPP
