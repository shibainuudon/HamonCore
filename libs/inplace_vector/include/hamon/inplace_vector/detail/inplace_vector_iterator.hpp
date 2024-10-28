/**
 *	@file	inplace_vector_iterator.hpp
 *
 *	@brief	inplace_vector_iterator の定義
 */

#ifndef HAMON_INPLACE_VECTOR_DETAIL_INPLACE_VECTOR_ITERATOR_HPP
#define HAMON_INPLACE_VECTOR_DETAIL_INPLACE_VECTOR_ITERATOR_HPP

#include <hamon/inplace_vector/inplace_vector_fwd.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/contiguous_iterator_tag.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/integral_constant.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

// TODO: デバッグビルドかどうかで切り替える
#define HAMON_INPLACE_VECTOR_ITERATOR_DEBUG

#if defined(HAMON_INPLACE_VECTOR_ITERATOR_DEBUG)

// 一部のstd::pointer_traitsの実装に合わせるため、テンプレート引数を全て型にしなければならない
template <typename T, typename N, typename Const>
struct inplace_vector_iterator
{
public:
	using iterator_concept  = hamon::contiguous_iterator_tag;
	using iterator_category = hamon::random_access_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = hamon::conditional_t<Const::value, T const*, T*>;
	using reference         = hamon::conditional_t<Const::value, T const&, T&>;

private:
	pointer         m_begin;
	difference_type m_offset;

	HAMON_CXX11_CONSTEXPR
	inplace_vector_iterator(pointer ptr, difference_type offset) HAMON_NOEXCEPT
		: m_begin(ptr)
		, m_offset(offset)
	{}

public:
	HAMON_CXX11_CONSTEXPR
	inplace_vector_iterator() HAMON_NOEXCEPT
		: m_begin()
		, m_offset()
	{}

	template <typename C,
		typename = hamon::enable_if_t<C::value == Const::value || Const::value>>
	HAMON_CXX11_CONSTEXPR
	inplace_vector_iterator(inplace_vector_iterator<T, N, C> const& i) HAMON_NOEXCEPT
		: m_begin(const_cast<pointer>(i.m_begin))
		, m_offset(i.m_offset)
	{}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	reference operator*() const HAMON_NOEXCEPT
	{
		return HAMON_ASSERT(0 <= m_offset && m_offset < static_cast<difference_type>(N::value)),
			*(m_begin + m_offset);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	pointer operator->() const HAMON_NOEXCEPT
	{
		return m_begin + m_offset;
	}

	HAMON_CXX14_CONSTEXPR inplace_vector_iterator&
	operator++() HAMON_NOEXCEPT
	{
		++m_offset;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR inplace_vector_iterator
	operator++(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;
		++*this;
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR inplace_vector_iterator&
	operator--() HAMON_NOEXCEPT
	{
		--m_offset;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR inplace_vector_iterator
	operator--(int) HAMON_NOEXCEPT
	{
		auto tmp = *this;
		--*this;
		return tmp;
	}

	HAMON_CXX14_CONSTEXPR inplace_vector_iterator&
	operator+=(difference_type n) HAMON_NOEXCEPT
	{
		m_offset += n;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR inplace_vector_iterator&
	operator-=(difference_type n) HAMON_NOEXCEPT
	{
		m_offset -= n;
		return *this;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR reference
	operator[](difference_type n) const HAMON_NOEXCEPT
	{
		return *(*this + n);
	}

private:
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR inplace_vector_iterator
	operator+(inplace_vector_iterator const& i, difference_type n) HAMON_NOEXCEPT
	{
		return inplace_vector_iterator(i.m_begin, i.m_offset + n);
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR inplace_vector_iterator
	operator+(difference_type n, inplace_vector_iterator const& i) HAMON_NOEXCEPT
	{
		return inplace_vector_iterator(i.m_begin, i.m_offset + n);
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR inplace_vector_iterator
	operator-(inplace_vector_iterator const& i, difference_type n) HAMON_NOEXCEPT
	{
		return inplace_vector_iterator(i.m_begin, i.m_offset - n);
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR difference_type
	operator-(inplace_vector_iterator const& lhs, inplace_vector_iterator const& rhs) HAMON_NOEXCEPT
	{
		return HAMON_ASSERT(lhs.m_begin == rhs.m_begin),
			lhs.m_offset - rhs.m_offset;
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator==(inplace_vector_iterator const& lhs, inplace_vector_iterator const& rhs) HAMON_NOEXCEPT
	{
		return HAMON_ASSERT(lhs.m_begin == rhs.m_begin),
			lhs.m_offset == rhs.m_offset;
	}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR hamon::strong_ordering
	operator<=>(inplace_vector_iterator const& lhs, inplace_vector_iterator const& rhs) HAMON_NOEXCEPT
	{
		return HAMON_ASSERT(lhs.m_begin == rhs.m_begin),
			lhs.m_offset <=> rhs.m_offset;
	}
#else
	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator!=(inplace_vector_iterator const& lhs, inplace_vector_iterator const& rhs) HAMON_NOEXCEPT
	{
		return !(lhs == rhs);
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator<(inplace_vector_iterator const& lhs, inplace_vector_iterator const& rhs) HAMON_NOEXCEPT
	{
		return HAMON_ASSERT(lhs.m_begin == rhs.m_begin),
			lhs.m_offset < rhs.m_offset;
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator>(inplace_vector_iterator const& lhs, inplace_vector_iterator const& rhs) HAMON_NOEXCEPT
	{
		return rhs < lhs;
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator<=(inplace_vector_iterator const& lhs, inplace_vector_iterator const& rhs) HAMON_NOEXCEPT
	{
		return !(rhs < lhs);
	}

	HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
	operator>=(inplace_vector_iterator const& lhs, inplace_vector_iterator const& rhs) HAMON_NOEXCEPT
	{
		return !(lhs < rhs);
	}
#endif
private:
	friend struct hamon::detail::inplace_vector_iterator<T, N, hamon::true_type>;
	friend class hamon::inplace_vector<T, N::value>;
};

#endif

template <typename T, hamon::size_t N, bool Const>
using inplace_vector_iterator_t =
#if defined(HAMON_INPLACE_VECTOR_ITERATOR_DEBUG)
	inplace_vector_iterator<T, hamon::integral_constant<hamon::size_t, N>, hamon::bool_constant<Const>>;
#else
	hamon::conditional_t<Const, T const*, T*>;
#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_INPLACE_VECTOR_DETAIL_INPLACE_VECTOR_ITERATOR_HPP
