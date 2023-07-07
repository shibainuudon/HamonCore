/**
 *	@file	array.hpp
 *
 *	@brief	array の定義
 */

#ifndef HAMON_ARRAY_ARRAY_HPP
#define HAMON_ARRAY_ARRAY_HPP

#include <hamon/array/config.hpp>

#if defined(HAMON_USE_STD_ARRAY)

#include <array>

namespace hamon
{

using std::array;

}	// namespace hamon

#else

#include <hamon/algorithm/equal.hpp>
#include <hamon/algorithm/fill_n.hpp>
#include <hamon/algorithm/lexicographical_compare.hpp>
#include <hamon/algorithm/lexicographical_compare_three_way.hpp>
#include <hamon/algorithm/swap_ranges.hpp>
#include <hamon/compare/detail/synth3way.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_swappable.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_swappable.hpp>
#include <hamon/config.hpp>
#include <stdexcept>	// std::out_of_range

namespace hamon
{

template <typename T, hamon::size_t N>
struct array
{
	// types
	using value_type             = T;
	using pointer                = T*;
	using const_pointer          = T const*;
	using reference              = T&;
	using const_reference        = T const&;
	using size_type              = hamon::size_t;
	using difference_type        = hamon::ptrdiff_t;
	using iterator               = pointer;       //implementation-defined; // see [container.requirements]
	using const_iterator         = const_pointer; //implementation-defined; // see [container.requirements]
	using reverse_iterator       = hamon::reverse_iterator<iterator>;
	using const_reverse_iterator = hamon::reverse_iterator<const_iterator>;

private:
	template <typename U, hamon::size_t M>
	struct array_traits
	{
		using type = U[M];

		static HAMON_CXX11_CONSTEXPR U*
		ptr(type const& t) HAMON_NOEXCEPT
		{
			return const_cast<U*>(t);
		}

		static HAMON_CXX14_CONSTEXPR void
		swap(array<U, M>& lhs, array<U, M>& rhs)
			HAMON_NOEXCEPT_IF(hamon::is_nothrow_swappable<U>::value)
		{
			hamon::swap_ranges(lhs.begin(), lhs.end(), rhs.begin());
		}
	};

	template <typename U>
	struct array_traits<U, 0>
	{
		struct type {};

		static HAMON_CXX11_CONSTEXPR U*
		ptr(type const&) HAMON_NOEXCEPT
		{
			return nullptr;
		}

		static HAMON_CXX14_CONSTEXPR void
		swap(array<U, 0>&, array<U, 0>&) HAMON_NOEXCEPT
		{
			// do nothing
		}
	};

	using traits_type = array_traits<T, N>;

public:
	typename traits_type::type	m_elems;

	// no explicit construct/copy/destroy for aggregate type

	HAMON_CXX14_CONSTEXPR void fill(T const& u)
	{
		hamon::fill_n(begin(), N, u);
	}

	HAMON_CXX14_CONSTEXPR void swap(array& a)
	HAMON_NOEXCEPT_IF_EXPR((
		traits_type::swap(*this, a)))
	{
		traits_type::swap(*this, a);
	}

	// iterators

	HAMON_NODISCARD	// extension
	HAMON_CXX14_CONSTEXPR iterator
	begin() HAMON_NOEXCEPT
	{
		return iterator(data());
	}

	HAMON_NODISCARD	// extension
	HAMON_CXX11_CONSTEXPR const_iterator
	begin() const HAMON_NOEXCEPT
	{
		return const_iterator(data());
	}

	HAMON_NODISCARD	// extension
	HAMON_CXX14_CONSTEXPR iterator
	end() HAMON_NOEXCEPT
	{
		return iterator(data() + N);
	}

	HAMON_NODISCARD	// extension
	HAMON_CXX11_CONSTEXPR const_iterator
	end() const HAMON_NOEXCEPT
	{
		return const_iterator(data() + N);
	}

	HAMON_NODISCARD	// extension
	HAMON_CXX14_CONSTEXPR reverse_iterator
	rbegin() HAMON_NOEXCEPT
	{
		return reverse_iterator(end());
	}

	HAMON_NODISCARD	// extension
	HAMON_CXX11_CONSTEXPR const_reverse_iterator
	rbegin() const HAMON_NOEXCEPT
	{
		return const_reverse_iterator(end());
	}

	HAMON_NODISCARD	// extension
	HAMON_CXX14_CONSTEXPR reverse_iterator
	rend() HAMON_NOEXCEPT
	{
		return reverse_iterator(begin());
	}

	HAMON_NODISCARD	// extension
	HAMON_CXX11_CONSTEXPR const_reverse_iterator
	rend() const HAMON_NOEXCEPT
	{
		return const_reverse_iterator(begin());
	}

	HAMON_NODISCARD	// extension
	HAMON_CXX11_CONSTEXPR const_iterator
	cbegin() const HAMON_NOEXCEPT
	{
		return const_iterator(data());
	}

	HAMON_NODISCARD	// extension
	HAMON_CXX11_CONSTEXPR const_iterator
	cend() const HAMON_NOEXCEPT
	{
		return const_iterator(data() + N);
	}

	HAMON_NODISCARD	// extension
	HAMON_CXX11_CONSTEXPR const_reverse_iterator
	crbegin() const HAMON_NOEXCEPT
	{
		return const_reverse_iterator(end());
	}

	HAMON_NODISCARD	// extension
	HAMON_CXX11_CONSTEXPR const_reverse_iterator
	crend() const HAMON_NOEXCEPT
	{
		return const_reverse_iterator(begin());
	}

	// capacity

	HAMON_NODISCARD
	HAMON_CXX11_CONSTEXPR bool
	empty() const HAMON_NOEXCEPT
	{
		return N == 0;
	}
	
	HAMON_NODISCARD	// extension
	HAMON_CXX11_CONSTEXPR size_type
	size() const HAMON_NOEXCEPT
	{
		// [array.members]/1
		return N;
	}

	HAMON_NODISCARD	// extension
	HAMON_CXX11_CONSTEXPR size_type
	max_size() const HAMON_NOEXCEPT
	{
		return N;
	}

	// element access

	HAMON_NODISCARD	// extension
	HAMON_CXX14_CONSTEXPR reference
	operator[](size_type n) HAMON_NOEXCEPT
	{
		return m_elems[n];
	}

	HAMON_NODISCARD	// extension
	HAMON_CXX11_CONSTEXPR const_reference
	operator[](size_type n) const HAMON_NOEXCEPT
	{
		return m_elems[n];
	}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです

	HAMON_NODISCARD	// extension
	HAMON_CXX14_CONSTEXPR reference
	at(size_type n)
	{
		return
			n < N ?
			(*this)[n] :
			(throw_out_of_range("array::at"), (*this)[n]);
	}

	HAMON_NODISCARD	// extension
	HAMON_CXX11_CONSTEXPR const_reference
	at(size_type n) const
	{
		return
			n < N ?
			(*this)[n] :
			(throw_out_of_range("array::at"), (*this)[n]);
	}

HAMON_WARNING_POP()

	HAMON_NODISCARD	// extension
	HAMON_CXX14_CONSTEXPR reference
	front() HAMON_NOEXCEPT
	{
		return (*this)[0];
	}

	HAMON_NODISCARD	// extension
	HAMON_CXX11_CONSTEXPR const_reference
	front() const HAMON_NOEXCEPT
	{
		return (*this)[0];
	}

	HAMON_NODISCARD	// extension
	HAMON_CXX14_CONSTEXPR reference
	back() HAMON_NOEXCEPT
	{
		return (*this)[N-1];
	}

	HAMON_NODISCARD	// extension
	HAMON_CXX11_CONSTEXPR const_reference
	back() const HAMON_NOEXCEPT
	{
		return (*this)[N-1];
	}

	HAMON_NODISCARD	// extension
	HAMON_CXX14_CONSTEXPR T*
	data() HAMON_NOEXCEPT
	{
		return traits_type::ptr(m_elems);
	}

	HAMON_NODISCARD	// extension
	HAMON_CXX11_CONSTEXPR T const*
	data() const HAMON_NOEXCEPT
	{
		return traits_type::ptr(m_elems);
	}

private:
	HAMON_NORETURN static void
	throw_out_of_range(char const* msg)
	{
#if !defined(HAMON_NO_EXCEPTIONS)
		throw std::out_of_range(msg);
#else
		(void)msg;
		std::abort();
#endif
	}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
template <typename T, typename... U>
array(T, U...)
->array<hamon::enable_if_t<(hamon::is_same<T, U>::value && ...), T>, 1 + sizeof...(U)>;
#endif

template <typename T, hamon::size_t N,
	typename = hamon::enable_if_t<
		N == 0 || hamon::is_swappable<T>::value
	>
>
inline HAMON_CXX14_CONSTEXPR void
swap(array<T, N>& lhs, array<T, N>& rhs)
HAMON_NOEXCEPT_IF_EXPR((
	lhs.swap(rhs)))
{
	lhs.swap(rhs);
}

template <typename T, hamon::size_t N>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR bool
operator==(array<T, N> const& lhs, array<T, N> const& rhs)
{
	return hamon::equal(lhs.begin(), lhs.end(), rhs.begin());
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename T, hamon::size_t N>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR hamon::detail::synth3way_t<T>
operator<=>(array<T, N> const& lhs, array<T, N> const& rhs)
{
	return hamon::lexicographical_compare_three_way(
		lhs.begin(), lhs.end(),
		rhs.begin(), rhs.end(),
		hamon::detail::synth3way);
}

#else

template <typename T, hamon::size_t N>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR bool
operator!=(array<T, N> const& lhs, array<T, N> const& rhs)
{
	return !(lhs == rhs);
}

template <typename T, hamon::size_t N>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR bool
operator<(array<T, N> const& lhs, array<T, N> const& rhs)
{
	return hamon::lexicographical_compare(
		lhs.begin(), lhs.end(),
		rhs.begin(), rhs.end());
}

template <typename T, hamon::size_t N>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR bool
operator>(array<T, N> const& lhs, array<T, N> const& rhs)
{
	return rhs < lhs;
}

template <typename T, hamon::size_t N>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR bool
operator<=(array<T, N> const& lhs, array<T, N> const& rhs)
{
	return !(lhs > rhs);
}

template <typename T, hamon::size_t N>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR bool
operator>=(array<T, N> const& lhs, array<T, N> const& rhs)
{
	return !(lhs < rhs);
}

#endif

}	// namespace hamon

#include <hamon/concepts/detail/is_specialization_of_array.hpp>
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon {
namespace detail {

// is_specialization_of_array の特殊化
template <typename T, hamon::size_t N>
struct is_specialization_of_array<hamon::array<T, N>>
	: public hamon::true_type {};

}	// namespace detail
}	// namespace hamon

#include <hamon/type_traits/integral_constant.hpp>
#include <tuple>

namespace std
{

// tuple_size の特殊化
template <typename T, hamon::size_t N>
struct tuple_size<hamon::array<T, N>>
	: public hamon::integral_constant<hamon::size_t, N> {};

// tuple_element の特殊化
template <hamon::size_t I, typename T, hamon::size_t N>
struct tuple_element<I, hamon::array<T, N>>
{
	// [array.tuple]/1
	static_assert(I < N, "index is out of bounds");
	using type = T;
};

}	// namespace std

#endif

#endif // HAMON_ARRAY_ARRAY_HPP
