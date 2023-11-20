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
#include <hamon/span/detail/is_specialization_of_span.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/detail/is_specialization_of_array.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/const_iterator.hpp>
#include <hamon/iterator/data.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/memory/to_address.hpp>
#include <hamon/ranges/concepts/borrowed_range.hpp>
#include <hamon/ranges/concepts/contiguous_range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/data.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/type_traits/is_const.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/remove_pointer.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/type_identity.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/array.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>
#include <array>

namespace hamon
{

namespace detail
{

template <typename ElementType, hamon::size_t Extent>
struct span_impl
{
private:
	ElementType*	m_data;

public:
	HAMON_CXX11_CONSTEXPR
	span_impl(ElementType* data, hamon::size_t size) HAMON_NOEXCEPT
		: m_data(((void)size, HAMON_ASSERT(size == Extent), data))
	{}

	HAMON_CXX11_CONSTEXPR ElementType*
	data() const HAMON_NOEXCEPT
	{
		return m_data;
	}
	
	HAMON_CXX11_CONSTEXPR hamon::size_t
	size() const HAMON_NOEXCEPT
	{
		return Extent;
	}
};

template <typename ElementType>
struct span_impl<ElementType, hamon::dynamic_extent>
{
private:
	ElementType*	m_data;
	hamon::size_t	m_size;

public:
	HAMON_CXX11_CONSTEXPR
	span_impl(ElementType* data, hamon::size_t size) HAMON_NOEXCEPT
		: m_data(data), m_size(size)
	{}

	HAMON_CXX11_CONSTEXPR ElementType*
	data() const HAMON_NOEXCEPT
	{
		return m_data;
	}

	HAMON_CXX11_CONSTEXPR hamon::size_t
	size() const HAMON_NOEXCEPT
	{
		return m_size;
	}
};

}	// namespace detail

template <typename ElementType, hamon::size_t Extent/* = dynamic_extent*/>
class span
{
public:
	// constants and types
	using element_type = ElementType;
	using value_type = hamon::remove_cv_t<ElementType>;
	using size_type = hamon::size_t;
	using difference_type = hamon::ptrdiff_t;
	using pointer = element_type*;
	using const_pointer = element_type const*;
	using reference = element_type&;
	using const_reference = element_type const&;
	using iterator = pointer;//implementation-defined;        // see [span.iterators]
	using const_iterator = hamon::const_iterator<iterator>;
	using reverse_iterator = hamon::reverse_iterator<iterator>;
	using const_reverse_iterator = hamon::const_iterator<reverse_iterator>;

	HAMON_STATIC_CONSTEXPR size_type extent = Extent;

	// [span.cons], constructors, copy, and assignment

	template <hamon::size_t N = Extent,
		typename = hamon::enable_if_t<N == hamon::dynamic_extent || N == 0>>	// [span.cons]/1
	HAMON_CXX11_CONSTEXPR
	span() HAMON_NOEXCEPT
		: m_impl(nullptr, 0)	// [span.cons]/2
	{}

#if defined(HAMON_HAS_CXX20_CONDITIONAL_EXPLICIT)
	template <
		HAMON_CONSTRAINED_PARAM(hamon::contiguous_iterator, It),								// [span.cons]/3.1
		typename U = hamon::remove_reference_t<hamon::iter_reference_t<It>>,					// [span.cons]/3
		typename = hamon::enable_if_t<hamon::is_convertible<U(*)[], element_type(*)[]>::value>	// [span.cons]/3.2
	>
	HAMON_CXX11_CONSTEXPR explicit(extent != hamon::dynamic_extent)
	span(It first, size_type count)	HAMON_NOEXCEPT	// noexcept as an extension
		: m_impl(hamon::to_address(first), count)	// [span.cons]/5
	{
		HAMON_ASSERT(extent == hamon::dynamic_extent || count == extent);	// [span.cons]/4.3
	}
#else
	template <
		HAMON_CONSTRAINED_PARAM(hamon::contiguous_iterator, It),								// [span.cons]/3.1
		typename U = hamon::remove_reference_t<hamon::iter_reference_t<It>>,					// [span.cons]/3
		typename = hamon::enable_if_t<hamon::is_convertible<U(*)[], element_type(*)[]>::value>,	// [span.cons]/3.2
		hamon::size_t N = extent, hamon::enable_if_t<N != hamon::dynamic_extent>* = nullptr
	>
	HAMON_CXX11_CONSTEXPR explicit
	span(It first, size_type count)	HAMON_NOEXCEPT	// noexcept as an extension
		: m_impl(hamon::to_address(first), count)	// [span.cons]/5
	{}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::contiguous_iterator, It),								// [span.cons]/3.1
		typename U = hamon::remove_reference_t<hamon::iter_reference_t<It>>,					// [span.cons]/3
		typename = hamon::enable_if_t<hamon::is_convertible<U(*)[], element_type(*)[]>::value>,	// [span.cons]/3.2
		hamon::size_t N = extent, hamon::enable_if_t<N == hamon::dynamic_extent>* = nullptr
	>
	HAMON_CXX11_CONSTEXPR
	span(It first, size_type count)	HAMON_NOEXCEPT	// noexcept as an extension
		: m_impl(hamon::to_address(first), count)	// [span.cons]/5
	{}
#endif

#if defined(HAMON_HAS_CXX20_CONDITIONAL_EXPLICIT)
	template <
		HAMON_CONSTRAINED_PARAM(hamon::contiguous_iterator, It),								// [span.cons]/7.2
		HAMON_CONSTRAINED_PARAM(hamon::sized_sentinel_for, It, End),							// [span.cons]/7.3
		typename U = hamon::remove_reference_t<hamon::iter_reference_t<It>>,					// [span.cons]/7
		typename = hamon::enable_if_t<hamon::is_convertible<U(*)[], element_type(*)[]>::value>,	// [span.cons]/7.1
		typename = hamon::enable_if_t<!hamon::is_convertible<End, hamon::size_t>::value>		// [span.cons]/7.4
	>
	HAMON_CXX11_CONSTEXPR explicit(extent != hamon::dynamic_extent)
	span(It first, End last) HAMON_NOEXCEPT_IF_EXPR(last - first)	// noexcept as an extension
		: m_impl(hamon::to_address(first), static_cast<size_type>(last - first))	// [span.cons]/9
	{
		HAMON_ASSERT(extent == hamon::dynamic_extent || static_cast<size_type>(last - first) == extent);	// [span.cons]/8.1
	}
#else
	template <
		HAMON_CONSTRAINED_PARAM(hamon::contiguous_iterator, It),								// [span.cons]/7.2
		HAMON_CONSTRAINED_PARAM(hamon::sized_sentinel_for, It, End),							// [span.cons]/7.3
		typename U = hamon::remove_reference_t<hamon::iter_reference_t<It>>,					// [span.cons]/7
		typename = hamon::enable_if_t<hamon::is_convertible<U(*)[], element_type(*)[]>::value>,	// [span.cons]/7.1
		typename = hamon::enable_if_t<!hamon::is_convertible<End, hamon::size_t>::value>,		// [span.cons]/7.4
		hamon::size_t N = extent, hamon::enable_if_t<N != hamon::dynamic_extent>* = nullptr
	>
	HAMON_CXX11_CONSTEXPR explicit
	span(It first, End last) HAMON_NOEXCEPT_IF_EXPR(last - first)	// noexcept as an extension
		: m_impl(hamon::to_address(first), static_cast<size_type>(last - first))	// [span.cons]/9
	{}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::contiguous_iterator, It),								// [span.cons]/7.2
		HAMON_CONSTRAINED_PARAM(hamon::sized_sentinel_for, It, End),							// [span.cons]/7.3
		typename U = hamon::remove_reference_t<hamon::iter_reference_t<It>>,					// [span.cons]/7
		typename = hamon::enable_if_t<hamon::is_convertible<U(*)[], element_type(*)[]>::value>,	// [span.cons]/7.1
		typename = hamon::enable_if_t<!hamon::is_convertible<End, hamon::size_t>::value>,		// [span.cons]/7.4
		hamon::size_t N = extent, hamon::enable_if_t<N == hamon::dynamic_extent>* = nullptr
	>
	HAMON_CXX11_CONSTEXPR
	span(It first, End last) HAMON_NOEXCEPT_IF_EXPR(last - first)	// noexcept as an extension
		: m_impl(hamon::to_address(first), static_cast<size_type>(last - first))	// [span.cons]/9
	{}
#endif

	template <hamon::size_t N,
		typename U = hamon::remove_pointer_t<decltype(hamon::data(hamon::declval<element_type(&)[N]>()))>,	// [span.cons]/11
		typename = hamon::enable_if_t<extent == hamon::dynamic_extent || N == extent>,			// [span.cons]/11.1
		typename = hamon::enable_if_t<hamon::is_convertible<U(*)[], element_type(*)[]>::value>	// [span.cons]/11.2
	>
	HAMON_CXX11_CONSTEXPR
	span(hamon::type_identity_t<element_type> (&arr)[N]) HAMON_NOEXCEPT
		: m_impl(hamon::data(arr), N)		// [span.cons]/12, 13
	{}

	template <typename T, hamon::size_t N,
		typename U = hamon::remove_pointer_t<decltype(hamon::data(hamon::declval<hamon::array<T, N>&>()))>,	// [span.cons]/11
		typename = hamon::enable_if_t<extent == hamon::dynamic_extent || N == extent>,			// [span.cons]/11.1
		typename = hamon::enable_if_t<hamon::is_convertible<U(*)[], element_type(*)[]>::value>	// [span.cons]/11.2
	>
	HAMON_CXX11_CONSTEXPR
	span(hamon::array<T, N>& arr) HAMON_NOEXCEPT
		: m_impl(hamon::data(arr), N)		// [span.cons]/12, 13
	{}

	template <typename T, hamon::size_t N,
		typename U = hamon::remove_pointer_t<decltype(hamon::data(hamon::declval<hamon::array<T, N> const&>()))>,	// [span.cons]/11
		typename = hamon::enable_if_t<extent == hamon::dynamic_extent || N == extent>,			// [span.cons]/11.1
		typename = hamon::enable_if_t<hamon::is_convertible<U(*)[], element_type(*)[]>::value>	// [span.cons]/11.2
	>
	HAMON_CXX11_CONSTEXPR
	span(hamon::array<T, N> const& arr) HAMON_NOEXCEPT
		: m_impl(hamon::data(arr), N)		// [span.cons]/12, 13
	{}

#if !defined(HAMON_USE_STD_ARRAY)
	template <typename T, hamon::size_t N,
		typename U = hamon::remove_pointer_t<decltype(hamon::data(hamon::declval<std::array<T, N>&>()))>,	// [span.cons]/11
		typename = hamon::enable_if_t<extent == hamon::dynamic_extent || N == extent>,			// [span.cons]/11.1
		typename = hamon::enable_if_t<hamon::is_convertible<U(*)[], element_type(*)[]>::value>	// [span.cons]/11.2
	>
	HAMON_CXX11_CONSTEXPR
	span(std::array<T, N>& arr) HAMON_NOEXCEPT
		: m_impl(hamon::data(arr), N)		// [span.cons]/12, 13
	{}

	template <typename T, hamon::size_t N,
		typename U = hamon::remove_pointer_t<decltype(hamon::data(hamon::declval<std::array<T, N> const&>()))>,	// [span.cons]/11
		typename = hamon::enable_if_t<extent == hamon::dynamic_extent || N == extent>,			// [span.cons]/11.1
		typename = hamon::enable_if_t<hamon::is_convertible<U(*)[], element_type(*)[]>::value>	// [span.cons]/11.2
	>
	HAMON_CXX11_CONSTEXPR
	span(std::array<T, N> const& arr) HAMON_NOEXCEPT
		: m_impl(hamon::data(arr), N)		// [span.cons]/12, 13
	{}
#endif

#if defined(HAMON_HAS_CXX20_CONDITIONAL_EXPLICIT)
	template <typename R,
		typename U = hamon::remove_reference_t<ranges::range_reference_t<R>>,	// [span.cons]/14
		typename = hamon::enable_if_t<
			hamon::ranges::contiguous_range_t<R>::value &&	// [span.cons]/14.1
			hamon::ranges::sized_range_t<R>::value &&		// [span.cons]/14.1
			(hamon::ranges::borrowed_range_t<R>::value || hamon::is_const<element_type>::value) &&	// [span.cons]/14.2
			!hamon::detail::is_specialization_of_span<hamon::remove_cvref_t<R>>::value &&	// [span.cons]/14.3
			!hamon::detail::is_specialization_of_array<hamon::remove_cvref_t<R>>::value &&	// [span.cons]/14.4
			!hamon::is_array<hamon::remove_cvref_t<R>>::value &&	// [span.cons]/14.5
			hamon::is_convertible<U(*)[], element_type(*)[]>::value	// [span.cons]/14.6
		>
	>
	HAMON_CXX11_CONSTEXPR explicit(extent != hamon::dynamic_extent)
	span(R&& r)
		: m_impl(ranges::data(r), ranges::size(r))	// [span.cons]/16
	{
		HAMON_ASSERT(extent == hamon::dynamic_extent || ranges::size(r) == extent);	// [span.cons]/15.1
	}
#else
	template <typename R,
		typename U = hamon::remove_reference_t<ranges::range_reference_t<R>>,	// [span.cons]/14
		typename = hamon::enable_if_t<
			hamon::ranges::contiguous_range_t<R>::value &&	// [span.cons]/14.1
			hamon::ranges::sized_range_t<R>::value &&		// [span.cons]/14.1
			(hamon::ranges::borrowed_range_t<R>::value || hamon::is_const<element_type>::value) &&	// [span.cons]/14.2
			!hamon::detail::is_specialization_of_span<hamon::remove_cvref_t<R>>::value &&	// [span.cons]/14.3
			!hamon::detail::is_specialization_of_array<hamon::remove_cvref_t<R>>::value &&	// [span.cons]/14.4
			!hamon::is_array<hamon::remove_cvref_t<R>>::value &&	// [span.cons]/14.5
			hamon::is_convertible<U(*)[], element_type(*)[]>::value	// [span.cons]/14.6
		>,
		hamon::size_t N = extent, hamon::enable_if_t<N != hamon::dynamic_extent>* = nullptr
	>
	HAMON_CXX11_CONSTEXPR explicit
	span(R&& r)
		: m_impl(ranges::data(r), ranges::size(r))	// [span.cons]/16
	{}

	template <typename R,
		typename U = hamon::remove_reference_t<ranges::range_reference_t<R>>,	// [span.cons]/14
		typename = hamon::enable_if_t<
			hamon::ranges::contiguous_range_t<R>::value &&	// [span.cons]/14.1
			hamon::ranges::sized_range_t<R>::value &&		// [span.cons]/14.1
			(hamon::ranges::borrowed_range_t<R>::value || hamon::is_const<element_type>::value) &&	// [span.cons]/14.2
			!hamon::detail::is_specialization_of_span<hamon::remove_cvref_t<R>>::value &&	// [span.cons]/14.3
			!hamon::detail::is_specialization_of_array<hamon::remove_cvref_t<R>>::value &&	// [span.cons]/14.4
			!hamon::is_array<hamon::remove_cvref_t<R>>::value &&	// [span.cons]/14.5
			hamon::is_convertible<U(*)[], element_type(*)[]>::value	// [span.cons]/14.6
		>,
		hamon::size_t N = extent, hamon::enable_if_t<N == hamon::dynamic_extent>* = nullptr
	>
	HAMON_CXX11_CONSTEXPR
	span(R&& r)
		: m_impl(ranges::data(r), ranges::size(r))	// [span.cons]/16
	{}
#endif

	HAMON_CXX11_CONSTEXPR span(span const& other) HAMON_NOEXCEPT = default;

#if defined(HAMON_HAS_CXX20_CONDITIONAL_EXPLICIT)
	template <typename OtherElementType, hamon::size_t OtherExtent,
		typename = hamon::enable_if_t<
			(extent == hamon::dynamic_extent || OtherExtent == hamon::dynamic_extent || extent == OtherExtent) && // [span.cons]/19.1
			hamon::is_convertible<OtherElementType(*)[], element_type(*)[]>::value // [span.cons]/19.2
		>
	>
	HAMON_CXX11_CONSTEXPR explicit(extent != hamon::dynamic_extent && OtherExtent == hamon::dynamic_extent)	// [span.cons]/23
	span(span<OtherElementType, OtherExtent> const& s) HAMON_NOEXCEPT
		: m_impl(s.data(), s.size())	// [span.cons]/21, 22
	{
		HAMON_ASSERT(extent == hamon::dynamic_extent || s.size() == extent);	// [span.cons]/20
	}
#else
	template <typename OtherElementType, hamon::size_t OtherExtent,
		typename = hamon::enable_if_t<
			(extent == hamon::dynamic_extent || OtherExtent == hamon::dynamic_extent || extent == OtherExtent) && // [span.cons]/19.1
			hamon::is_convertible<OtherElementType(*)[], element_type(*)[]>::value // [span.cons]/19.2
		>,
		hamon::size_t N = extent, hamon::enable_if_t<N != hamon::dynamic_extent>* = nullptr
	>
	HAMON_CXX11_CONSTEXPR explicit
	span(span<OtherElementType, OtherExtent> const& s) HAMON_NOEXCEPT
		: m_impl(s.data(), s.size())	// [span.cons]/21, 22
	{}

	template <typename OtherElementType, hamon::size_t OtherExtent,
		typename = hamon::enable_if_t<
			(extent == hamon::dynamic_extent || OtherExtent == hamon::dynamic_extent || extent == OtherExtent) && // [span.cons]/19.1
			hamon::is_convertible<OtherElementType(*)[], element_type(*)[]>::value // [span.cons]/19.2
		>,
		hamon::size_t N = extent, hamon::enable_if_t<N == hamon::dynamic_extent>* = nullptr
	>
	HAMON_CXX11_CONSTEXPR
	span(span<OtherElementType, OtherExtent> const& s) HAMON_NOEXCEPT
		: m_impl(s.data(), s.size())	// [span.cons]/21, 22
	{}
#endif

	HAMON_CXX14_CONSTEXPR span&
	operator=(span const& other) HAMON_NOEXCEPT = default;

	// [span.sub], subviews
	template <hamon::size_t Count>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR span<element_type, Count>	// nodiscard as an extension
	first() const HAMON_NOEXCEPT	// noexcept as an extension
	{
		static_assert(Count <= Extent, "span::first");	// [span.sub]/1
		return HAMON_ASSERT(Count <= size()),			// [span.sub]/2
			span<element_type, Count>{data(), Count};	// [span.sub]/3
	}
	
	template <hamon::size_t Count>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR span<element_type, Count>	// nodiscard as an extension
	last() const HAMON_NOEXCEPT	// noexcept as an extension
	{
		static_assert(Count <= Extent, "span::last");	// [span.sub]/4
		return HAMON_ASSERT(Count <= size()),			// [span.sub]/5
			span<element_type, Count>{data() + (size() - Count), Count};	// [span.sub]/6
	}

	template <hamon::size_t Offset, hamon::size_t Count = hamon::dynamic_extent>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	span<element_type, Count != dynamic_extent ? Count : (Extent != dynamic_extent ? Extent - Offset : dynamic_extent)>
	subspan() const HAMON_NOEXCEPT	// noexcept as an extension
	{
		static_assert(Offset <= Extent && (Count == dynamic_extent || Count <= Extent - Offset), "span::subspan");	// [span.sub]/7
		return HAMON_ASSERT(Offset <= size() && (Count == dynamic_extent || Count <= size() - Offset)),	// [span.sub]/8
			span<element_type, Count != dynamic_extent ? Count : (Extent != dynamic_extent ? Extent - Offset : dynamic_extent)>
			(
				data() + Offset, Count != dynamic_extent ? Count : size() - Offset	// [span.sub]/9
			);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR span<element_type, hamon::dynamic_extent>	// nodiscard as an extension
	first(size_type count) const HAMON_NOEXCEPT	// noexcept as an extension
	{
		return HAMON_ASSERT(count <= size()),	// [span.sub]/11
			span<element_type, hamon::dynamic_extent>{data(), count};	// [span.sub]/12
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR span<element_type, hamon::dynamic_extent>	// nodiscard as an extension
	last(size_type count) const HAMON_NOEXCEPT	// noexcept as an extension
	{
		return HAMON_ASSERT(count <= size()),	// [span.sub]/13
			span<element_type, hamon::dynamic_extent>{data() + (size() - count), count};	// [span.sub]/14
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR span<element_type, hamon::dynamic_extent>	// nodiscard as an extension
	subspan(size_type offset, size_type count = hamon::dynamic_extent) const HAMON_NOEXCEPT	// noexcept as an extension
	{
		return HAMON_ASSERT(offset <= size() && (count == dynamic_extent || count <= size() - offset)),	// [span.sub]/15
			span<element_type, hamon::dynamic_extent>{data() + offset, count == dynamic_extent ? size() - offset : count};	// [span.sub]/16
	}

	// [span.obs], observers
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	size() const HAMON_NOEXCEPT
	{
		// [span.obs]/1
		return m_impl.size();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR size_type	// nodiscard as an extension
	size_bytes() const HAMON_NOEXCEPT
	{
		// [span.obs]/2
		return size() * sizeof(element_type);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
	empty() const HAMON_NOEXCEPT
	{
		// [span.obs]/3
		return size() == 0;
	}

	// [span.elem], element access
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR reference	// nodiscard as an extension
	operator[](size_type idx) const HAMON_NOEXCEPT	// noexcept as an extension
	{
		return HAMON_ASSERT(idx < size()),	// [span.elem]/1
			*(data() + idx);				// [span.elem]/2
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR reference	// nodiscard as an extension
	front() const HAMON_NOEXCEPT					// noexcept as an extension
	{
		return HAMON_ASSERT(!empty()),	// [span.elem]/3
			*data();					// [span.elem]/4
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR reference	// nodiscard as an extension
	back() const HAMON_NOEXCEPT						// noexcept as an extension
	{
		return HAMON_ASSERT(!empty()),	// [span.elem]/5
			*(data() + (size() - 1));	// [span.elem]/6
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR pointer	// nodiscard as an extension
	data() const HAMON_NOEXCEPT
	{
		return m_impl.data();	// [span.elem]/7
	}

	// [span.iterators], iterator support
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR iterator	// nodiscard as an extension
	begin() const HAMON_NOEXCEPT
	{
		return iterator(data());			// [span.iterators]/3
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR iterator	// nodiscard as an extension
	end() const HAMON_NOEXCEPT
	{
		return iterator(data() + size());	// [span.iterators]/4
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR const_iterator	// nodiscard as an extension
	cbegin() const HAMON_NOEXCEPT
	{
		return begin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR const_iterator	// nodiscard as an extension
	cend() const HAMON_NOEXCEPT
	{
		return end();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR reverse_iterator	// nodiscard as an extension
	rbegin() const HAMON_NOEXCEPT
	{
		return reverse_iterator(end());		// [span.iterators]/5
	}
	
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR reverse_iterator	// nodiscard as an extension
	rend() const HAMON_NOEXCEPT
	{
		return reverse_iterator(begin());	// [span.iterators]/6
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR const_reverse_iterator	// nodiscard as an extension
	crbegin() const HAMON_NOEXCEPT
	{
		return rbegin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR const_reverse_iterator	// nodiscard as an extension
	crend() const HAMON_NOEXCEPT
	{
		return rend();
	}

private:
	detail::span_impl<ElementType, Extent>	m_impl;
};

// deduction guides
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

// [span.deduct]

template <
	HAMON_CONSTRAINED_PARAM(hamon::contiguous_iterator, It),	// [span.deduct]/1
	typename EndOrSize>
span(It, EndOrSize)
-> span<hamon::remove_reference_t<hamon::iter_reference_t<It>>>;

template <typename T, hamon::size_t N>
span(T(&)[N])
-> span<T, N>;

template <typename T, hamon::size_t N>
span(hamon::array<T, N>&)
-> span<T, N>;

template <typename T, hamon::size_t N>
span(hamon::array<T, N> const&)
-> span<T const, N>;

#if !defined(HAMON_USE_STD_ARRAY)
template <typename T, hamon::size_t N>
span(std::array<T, N>&)
-> span<T, N>;

template <typename T, hamon::size_t N>
span(std::array<T, N> const&)
-> span<T const, N>;
#endif

template <HAMON_CONSTRAINED_PARAM(ranges::contiguous_range, Range)>	// [span.deduct]/2
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

// [span.syn]

HAMON_RANGES_START_NAMESPACE

template <typename T, hamon::size_t Extent>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon::span<T, Extent>);

template <typename T, hamon::size_t Extent>
HAMON_RANGES_SPECIALIZE_ENABLE_VIEW(true, hamon::span<T, Extent>);

HAMON_RANGES_END_NAMESPACE

#endif

#endif // HAMON_SPAN_SPAN_HPP
