/**
 *	@file	span.hpp
 *
 *	@brief	span の定義
 */

#ifndef HAMON_SPAN_SPAN_HPP
#define HAMON_SPAN_SPAN_HPP

#include <hamon/span/config.hpp>

#if defined(HAMON_USE_STD_SPAN)

namespace hamon
{

using std::span;

}	// namespace hamon

#else

#include <hamon/span/span_fwd.hpp>
#include <hamon/span/dynamic_extent.hpp>
#include <hamon/span/detail/span_compatible_iterator.hpp>
#include <hamon/span/detail/span_compatible_sentinel_for.hpp>
#include <hamon/span/detail/span_array_convertible.hpp>
#include <hamon/span/detail/span_compatible_range.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/memory/to_address.hpp>
#include <hamon/ranges/concepts/contiguous_range.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/ranges/data.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/type_identity.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>
#include <array>

namespace hamon
{

template <typename T, hamon::size_t Extent>
class span
{
public:
	// constants and types
	using element_type     = T;
	using value_type       = hamon::remove_cv_t<T>;
	using size_type        = hamon::size_t;
	using difference_type  = hamon::ptrdiff_t;
	using pointer          = T *;
	using const_pointer    = T const*;
	using reference        = T &;
	using const_reference  = T const&;
	using iterator         = pointer;
	using reverse_iterator = hamon::reverse_iterator<iterator>;

	HAMON_STATIC_CONSTEXPR size_type extent = Extent;

	// constructors, copy, and assignment

	// (1)
	template <hamon::size_t N = Extent, typename = hamon::enable_if_t<N == 0>>
	HAMON_CXX11_CONSTEXPR
	span() HAMON_NOEXCEPT
		: m_data{ nullptr }
	{}

	// (2)
	template <HAMON_CONSTRAINED_PARAM(detail::span_compatible_iterator, element_type, It)>
	HAMON_CXX11_CONSTEXPR explicit
	span(It first, size_type count) HAMON_NOEXCEPT
		: m_data{(
			(void)count,
			HAMON_ASSERT(Extent == count),
			hamon::to_address(first))}
	{}

	// (3)
	template <
		HAMON_CONSTRAINED_PARAM(detail::span_compatible_iterator, element_type, It),
		HAMON_CONSTRAINED_PARAM(detail::span_compatible_sentinel_for, It, End)
	>
	HAMON_CXX11_CONSTEXPR explicit
	span(It first, End last) HAMON_NOEXCEPT_IF_EXPR(last - first)
		: m_data{(
			(void)last,
			HAMON_ASSERT((last - first >= 0)),
			HAMON_ASSERT(static_cast<size_type>(last - first) == Extent), 
			hamon::to_address(first))}
	{}

	// (4)
	template <hamon::size_t N, typename = hamon::enable_if_t<N == Extent>>
	HAMON_CXX11_CONSTEXPR
	span(hamon::type_identity_t<element_type>(&arr)[N]) HAMON_NOEXCEPT
		: m_data{ arr }
	{}

	// (5)
	template <HAMON_CONSTRAINED_PARAM(detail::span_array_convertible, element_type, U)>
	HAMON_CXX11_CONSTEXPR
	span(std::array<U, Extent>& arr) HAMON_NOEXCEPT
		: m_data{ arr.data() }
	{}

	// (6)
	template <typename U
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, typename = hamon::enable_if_t<detail::span_array_convertible<U const, element_type>::value>
#endif
	>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires detail::span_array_convertible<U const, element_type>
#endif
	HAMON_CXX11_CONSTEXPR
	span(std::array<U, Extent> const& arr) HAMON_NOEXCEPT
		: m_data{ arr.data() }
	{}

	// (7)
	template <HAMON_CONSTRAINED_PARAM(detail::span_compatible_range, element_type, Range)>
	HAMON_CXX11_CONSTEXPR explicit
	span(Range&& r)
		HAMON_NOEXCEPT_IF(
			HAMON_NOEXCEPT_EXPR(ranges::data(r)) &&
			HAMON_NOEXCEPT_EXPR(ranges::size(r)))
		: m_data{(
			HAMON_ASSERT(ranges::size(r) == Extent),
			ranges::data(r))}
	{}

	// (8)
	template <HAMON_CONSTRAINED_PARAM(detail::span_array_convertible, element_type, U)>
	HAMON_CXX11_CONSTEXPR
	span(span<U, Extent> const& other) HAMON_NOEXCEPT
		: m_data{ other.data() }
	{}

	// (8)
	template <HAMON_CONSTRAINED_PARAM(detail::span_array_convertible, element_type, U)>
	HAMON_CXX11_CONSTEXPR explicit
	span(span<U, hamon::dynamic_extent> const& other) HAMON_NOEXCEPT
		: m_data{(
			HAMON_ASSERT(Extent == other.size()),
			other.data())}
	{}

	// (9)
	HAMON_CXX11_CONSTEXPR span(span const&) HAMON_NOEXCEPT = default;

	// ~span() HAMON_NOEXCEPT = default;

	HAMON_CXX14_CONSTEXPR span& operator=(span const&) HAMON_NOEXCEPT = default;

	// subviews
	template <hamon::size_t Count>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR span<element_type, Count>
	first() const HAMON_NOEXCEPT
	{
		static_assert(Count <= Extent, "span<T, N>::first<Count>(): Count out of range");
		return span<element_type, Count>{data(), Count};
	}

	template <hamon::size_t Count>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR span<element_type, Count>
	last() const HAMON_NOEXCEPT
	{
		static_assert(Count <= Extent, "span<T, N>::last<Count>(): Count out of range");
		return span<element_type, Count>{data() + size() - Count, Count};
	}

	template <hamon::size_t Offset, hamon::size_t Count = hamon::dynamic_extent>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	subspan() const HAMON_NOEXCEPT
	-> span<element_type, Count != hamon::dynamic_extent ? Count : Extent - Offset>
	{
		static_assert(Offset <= Extent, "span<T, N>::subspan<Offset, Count>(): Offset out of range");
		static_assert(Count == hamon::dynamic_extent || Count <= Extent - Offset, "span<T, N>::subspan<Offset, Count>(): Offset + Count out of range");

		using ReturnType = span<element_type, Count != hamon::dynamic_extent ? Count : Extent - Offset>;
		return ReturnType{ data() + Offset, Count != hamon::dynamic_extent ? Count : size() - Offset };
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR span<element_type, hamon::dynamic_extent>
	first(size_type count) const HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT_MSG(count <= size(), "span<T, N>::first(count): count out of range"),
			span<element_type, hamon::dynamic_extent>{ data(), count };
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR span<element_type, hamon::dynamic_extent>
	last(size_type count) const HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT_MSG(count <= size(), "span<T, N>::last(count): count out of range"),
			span<element_type, hamon::dynamic_extent>{ data() + size() - count, count };
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR span<element_type, hamon::dynamic_extent>
	subspan(size_type offset, size_type count = hamon::dynamic_extent) const HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT_MSG(offset <= size(), "span<T, N>::subspan(offset, count): offset out of range"),
			HAMON_ASSERT_MSG(count  <= size() || count == hamon::dynamic_extent, "span<T, N>::subspan(offset, count): count out of range"),
			(count == hamon::dynamic_extent) ?
				span<element_type, hamon::dynamic_extent>{ data() + offset, size() - offset } :
				(HAMON_ASSERT_MSG(count <= size() - offset, "span<T, N>::subspan(offset, count): offset + count out of range"),
				span<element_type, hamon::dynamic_extent>{ data() + offset, count });
	}

	// observers
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type
	size() const HAMON_NOEXCEPT
	{
		return Extent;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type
	size_bytes() const HAMON_NOEXCEPT
	{
		return Extent * sizeof(element_type);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
	empty() const HAMON_NOEXCEPT
	{
		return Extent == 0;
	}

	// element access
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR reference
	operator[](size_type idx) const HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT_MSG(idx < size(), "span<T, N>::operator[](index): index out of range"),
			m_data[idx];
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR reference
	front() const HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT_MSG(!empty(), "span<T, N>::front() on empty span"),
			m_data[0];
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR reference
	back() const HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT_MSG(!empty(), "span<T, N>::back() on empty span"),
			m_data[size() - 1];
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR pointer
	data() const HAMON_NOEXCEPT
	{
		return m_data;
	}

	// iterator support
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR iterator
	begin() const HAMON_NOEXCEPT
	{
		return iterator(data());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR iterator
	end() const HAMON_NOEXCEPT
	{
		return iterator(data() + size());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR reverse_iterator
	rbegin() const HAMON_NOEXCEPT
	{
		return reverse_iterator(end());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR reverse_iterator
	rend() const HAMON_NOEXCEPT
	{
		return reverse_iterator(begin());
	}

private:
	pointer    m_data;
};

template <typename T>
class span<T, hamon::dynamic_extent>
{
public:
	// constants and types
	using element_type     = T;
	using value_type       = hamon::remove_cv_t<T>;
	using size_type        = hamon::size_t;
	using difference_type  = hamon::ptrdiff_t;
	using pointer          = T *;
	using const_pointer    = T const*;
	using reference        = T &;
	using const_reference  = T const&;
	using iterator         = pointer;
	using reverse_iterator = hamon::reverse_iterator<iterator>;

	HAMON_STATIC_CONSTEXPR size_type extent = hamon::dynamic_extent;

	// constructors, copy, and assignment

	// (1)
	HAMON_CXX11_CONSTEXPR
	span() HAMON_NOEXCEPT
		: m_data{ nullptr }
		, m_size{ 0 }
	{}

	// (2)
	template <HAMON_CONSTRAINED_PARAM(detail::span_compatible_iterator, element_type, It)>
	HAMON_CXX11_CONSTEXPR
	span(It first, size_type count) HAMON_NOEXCEPT
		: m_data{ hamon::to_address(first) }
		, m_size{ count }
	{}

	// (3)
	template <
		HAMON_CONSTRAINED_PARAM(detail::span_compatible_iterator, element_type, It),
		HAMON_CONSTRAINED_PARAM(detail::span_compatible_sentinel_for, It, End)
	>
	HAMON_CXX11_CONSTEXPR
	span(It first, End last) HAMON_NOEXCEPT_IF_EXPR(last - first)
		: m_data{(
			HAMON_ASSERT(last - first >= 0),
			hamon::to_address(first))}
		, m_size{ static_cast<size_type>(last - first) }
	{}

	// (4)
	template <hamon::size_t N>
	HAMON_CXX11_CONSTEXPR
	span(hamon::type_identity_t<element_type>(&arr)[N]) HAMON_NOEXCEPT
		: m_data{ arr }
		, m_size{ N }
	{}

	// (5)
	template <HAMON_CONSTRAINED_PARAM(detail::span_array_convertible, element_type, U), hamon::size_t N>
	HAMON_CXX11_CONSTEXPR
	span(std::array<U, N>& arr) HAMON_NOEXCEPT
		: m_data{ arr.data() }
		, m_size{ N }
	{}

	// (6)
	template <typename U, hamon::size_t N
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, typename = hamon::enable_if_t<detail::span_array_convertible<U const, element_type>::value>
#endif
	>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires detail::span_array_convertible<U const, element_type>
#endif
	HAMON_CXX11_CONSTEXPR
	span(std::array<U, N> const& arr) HAMON_NOEXCEPT
		: m_data{ arr.data() }
		, m_size{ N }
	{}

	// (7)
	template <HAMON_CONSTRAINED_PARAM(detail::span_compatible_range, element_type, Range)>
	HAMON_CXX11_CONSTEXPR
	span(Range&& r)
		HAMON_NOEXCEPT_IF(
			HAMON_NOEXCEPT_EXPR(ranges::data(r)) &&
			HAMON_NOEXCEPT_EXPR(ranges::size(r)))
		: m_data{ ranges::data(r) }
		, m_size{ ranges::size(r) }
	{}

	// (8)
	template <HAMON_CONSTRAINED_PARAM(detail::span_array_convertible, element_type, U), hamon::size_t N>
	HAMON_CXX11_CONSTEXPR
	span(span<U, N> const& other)  HAMON_NOEXCEPT
		: m_data{ other.data() }
		, m_size{ other.size() }
	{}

	// (9)
	HAMON_CXX11_CONSTEXPR span(span const&) HAMON_NOEXCEPT = default;

	// ~span() HAMON_NOEXCEPT = default;

	HAMON_CXX14_CONSTEXPR span& operator=(span const&) HAMON_NOEXCEPT = default;

	// subviews
	template <hamon::size_t Count>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR span<element_type, Count>
	first() const HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT_MSG(Count <= size(), "span<T>::first<Count>(): Count out of range"),
			span<element_type, Count>{data(), Count};
	}

	template <hamon::size_t Count>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR span<element_type, Count>
	last() const HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT_MSG(Count <= size(), "span<T>::last<Count>(): Count out of range"),
			span<element_type, Count>{data() + size() - Count, Count};
	}

	template <hamon::size_t Offset, hamon::size_t Count = hamon::dynamic_extent>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR span<element_type, Count>
	subspan() const HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT_MSG(Offset <= size(), "span<T>::subspan<Offset, Count>(): Offset out of range"),
			HAMON_ASSERT_MSG(Count == hamon::dynamic_extent || Count <= size() - Offset, "span<T>::subspan<Offset, Count>(): Offset + Count out of range"),
			span<element_type, Count>{data() + Offset, Count == hamon::dynamic_extent ? size() - Offset : Count};
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR span<element_type, hamon::dynamic_extent>
	first(size_type count) const HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT_MSG(count <= size(), "span<T>::first(count): count out of range"),
			span<element_type, hamon::dynamic_extent>{ data(), count };
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR span<element_type, hamon::dynamic_extent>
	last(size_type count) const HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT_MSG(count <= size(), "span<T>::last(count): count out of range"),
			span<element_type, hamon::dynamic_extent>{ data() + size() - count, count };
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR span<element_type, hamon::dynamic_extent>
	subspan(size_type offset, size_type count = hamon::dynamic_extent) const HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT_MSG(offset <= size(), "span<T>::subspan(offset, count): offset out of range"),
			HAMON_ASSERT_MSG(count <= size() || count == hamon::dynamic_extent, "span<T>::subspan(offset, count): count out of range"),
			(count == hamon::dynamic_extent) ?
				span<element_type, hamon::dynamic_extent>{ data() + offset, size() - offset } :
				(HAMON_ASSERT_MSG(count <= size() - offset, "span<T>::subspan(offset, count): offset + count out of range"),
				span<element_type, hamon::dynamic_extent>{ data() + offset, count });
	}

	// observers
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type
	size() const HAMON_NOEXCEPT
	{
		return m_size;
	}
	
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type
	size_bytes() const HAMON_NOEXCEPT
	{
		return m_size * sizeof(element_type);
	}
	
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
	empty() const HAMON_NOEXCEPT
	{
		return m_size == 0;
	}

	// element access
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR reference
	operator[](size_type idx) const HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT_MSG(idx < size(), "span<T>::operator[](index): index out of range"),
			m_data[idx];
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR reference
	front() const HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT_MSG(!empty(), "span<T>::front() on empty span"),
			m_data[0];
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR reference
	back() const HAMON_NOEXCEPT
	{
		return
			HAMON_ASSERT_MSG(!empty(), "span<T>::back() on empty span"),
			m_data[size() - 1];
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR pointer
	data() const HAMON_NOEXCEPT
	{
		return m_data;
	}

	// iterator support
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR iterator
	begin() const HAMON_NOEXCEPT
	{
		return iterator(data());
	}
	
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR iterator
	end() const HAMON_NOEXCEPT
	{
		return iterator(data() + size());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR reverse_iterator
	rbegin() const HAMON_NOEXCEPT
	{
		return reverse_iterator(end());
	}
	
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR reverse_iterator
	rend() const HAMON_NOEXCEPT
	{
		return reverse_iterator(begin());
	}

private:
	pointer   m_data;
	size_type m_size;
};

// deduction guides
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <HAMON_CONSTRAINED_PARAM(hamon::contiguous_iterator, It), typename EndOrSize>
span(It, EndOrSize)
-> span<hamon::remove_reference_t<hamon::iter_reference_t<It>>>;

template <typename T, hamon::size_t N>
span(T(&)[N])
-> span<T, N>;

template <typename T, hamon::size_t N>
span(std::array<T, N>&)
-> span<T, N>;

template <typename T, hamon::size_t N>
span(std::array<T, N> const&)
-> span<T const, N>;

template <HAMON_CONSTRAINED_PARAM(ranges::contiguous_range, Range)>
span(Range&&)
-> span<hamon::remove_reference_t<ranges::range_reference_t<Range>>>;

#endif

}	// namespace hamon

#endif

#include <hamon/ranges/config.hpp>

#if !(defined(HAMON_USE_STD_SPAN) && defined(HAMON_USE_STD_RANGES))

#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/ranges/concepts/enable_view.hpp>
#include <hamon/cstddef/size_t.hpp>

HAMON_RANGES_START_NAMESPACE

template <typename T, hamon::size_t Extent>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon::span<T, Extent>);

template <typename T, hamon::size_t Extent>
HAMON_RANGES_SPECIALIZE_ENABLE_VIEW(true, hamon::span<T, Extent>);

HAMON_RANGES_END_NAMESPACE

#endif

#endif // HAMON_SPAN_SPAN_HPP
