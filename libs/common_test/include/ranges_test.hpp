/**
 *	@file	ranges_test.hpp
 *
 *	@brief	
 */

#ifndef UNIT_TEST_COMMON_RANGES_TEST_HPP
#define UNIT_TEST_COMMON_RANGES_TEST_HPP

#include <hamon/ranges/view_base.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/ranges/concepts/enable_view.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include "iterator_test.hpp"

namespace hamon_ranges_test
{

template <typename T, typename Iterator>
struct test_container
{
	T* m_first;
	T* m_last;

	using iterator = Iterator;

	HAMON_CONSTEXPR test_container() : m_first(nullptr), m_last(nullptr) {}
	HAMON_CONSTEXPR test_container(T* first, T* last) : m_first(first), m_last(last) {}

	HAMON_CONSTEXPR test_container(test_container const&) = default;
	HAMON_CONSTEXPR test_container(test_container &&) = default;

	HAMON_CXX14_CONSTEXPR test_container& operator=(test_container const&) = default;
	HAMON_CXX14_CONSTEXPR test_container& operator=(test_container &&) = default;

	template <hamon::size_t N>
	explicit HAMON_CONSTEXPR test_container(T (&arr)[N]) : test_container(arr, arr+N) {}

	HAMON_CONSTEXPR iterator begin() const { return iterator{m_first}; }
	HAMON_CONSTEXPR iterator end()   const { return iterator{m_last}; }
};

template <typename Iterator>
struct test_sentinel
{
	Iterator m_it;

	HAMON_CONSTEXPR bool
	operator==(Iterator const& i) const noexcept
	{
		return base(m_it) == base(i);
	}

	HAMON_CONSTEXPR bool
	operator!=(Iterator const& i) const noexcept
	{
		return !(*this == i);
	}
};

template <typename Iterator>
HAMON_CONSTEXPR bool
operator==(Iterator const& i, test_sentinel<Iterator> const& s) noexcept
{
	return s == i;
}

template <typename Iterator>
HAMON_CONSTEXPR bool
operator!=(Iterator const& i, test_sentinel<Iterator> const& s) noexcept
{
	return !(i == s);
}

template <HAMON_CONSTRAINED_PARAM(hamon::random_access_iterator, Iterator)>
HAMON_CONSTEXPR auto
operator-(test_sentinel<Iterator> const& s, Iterator const& i) noexcept
->decltype(base(s.m_it) - base(i))
{
	return base(s.m_it) - base(i);
}

template <HAMON_CONSTRAINED_PARAM(hamon::random_access_iterator, Iterator)>
HAMON_CONSTEXPR auto
operator-(Iterator const& i, test_sentinel<Iterator> const& s) noexcept
->decltype(base(i) - base(s.m_it))
{
	return base(i) - base(s.m_it);
}

template <typename T, typename Iterator, typename Sentinel = test_sentinel<Iterator>>
struct test_range
{
	T* m_first;
	T* m_last;

	using iterator = Iterator;
	using sentinel = Sentinel;

	HAMON_CONSTEXPR test_range() : m_first(nullptr), m_last(nullptr) {}
	HAMON_CONSTEXPR test_range(T* first, T* last) : m_first(first), m_last(last) {}

	HAMON_CONSTEXPR test_range(test_range const&) = default;
	HAMON_CONSTEXPR test_range(test_range &&) = default;

	HAMON_CXX14_CONSTEXPR test_range& operator=(test_range const&) = default;
	HAMON_CXX14_CONSTEXPR test_range& operator=(test_range &&) = default;

	template <hamon::size_t N>
	explicit HAMON_CONSTEXPR test_range(T (&arr)[N]) : test_range(arr, arr+N) {}

	HAMON_CONSTEXPR iterator begin() const noexcept { return iterator{m_first}; }
	HAMON_CONSTEXPR sentinel end()   const noexcept { return sentinel{iterator{m_last}}; }
};

template <typename T> using test_contiguous_range    = test_range<T, contiguous_iterator_wrapper<T>>;
template <typename T> using test_random_access_range = test_range<T, random_access_iterator_wrapper<T>>;
template <typename T> using test_bidirectional_range = test_range<T, bidirectional_iterator_wrapper<T>>;
template <typename T> using test_forward_range       = test_range<T, forward_iterator_wrapper<T>>;
template <typename T> using test_input_range         = test_range<T, input_iterator_wrapper<T>>;
template <typename T> using test_output_range        = test_range<T, output_iterator_wrapper<T>>;

template <typename T, typename Iterator, typename Sentinel = test_sentinel<Iterator>>
struct test_sized_range : public test_range<T, Iterator, Sentinel>
{
	using base_t = test_range<T, Iterator, Sentinel>;
	using base_t::test_range;

	HAMON_CONSTEXPR hamon::size_t size() const noexcept
	{
		return static_cast<hamon::size_t>(base_t::m_last - base_t::m_first);
	}
};

template <typename T> using test_contiguous_sized_range    = test_sized_range<T, contiguous_iterator_wrapper<T>>;
template <typename T> using test_random_access_sized_range = test_sized_range<T, random_access_iterator_wrapper<T>>;
template <typename T> using test_bidirectional_sized_range = test_sized_range<T, bidirectional_iterator_wrapper<T>>;
template <typename T> using test_forward_sized_range       = test_sized_range<T, forward_iterator_wrapper<T>>;
template <typename T> using test_input_sized_range         = test_sized_range<T, input_iterator_wrapper<T>>;
template <typename T> using test_output_sized_range        = test_sized_range<T, output_iterator_wrapper<T>>;

//template <typename T, hamon::size_t N, template <typename> class Iterator>
//struct test_static_sized_range : public test_range<T, Iterator<T>>
//{
//	using test_range<T, Iterator<T>>::test_range;
//
//	static HAMON_CONSTEXPR hamon::size_t size() noexcept
//	{
//		return N;
//	}
//};
//
//template <typename T, hamon::size_t N> using test_contiguous_static_sized_range    = test_static_sized_range<T, N, contiguous_iterator_wrapper>;
//template <typename T, hamon::size_t N> using test_random_access_static_sized_range = test_static_sized_range<T, N, random_access_iterator_wrapper>;
//template <typename T, hamon::size_t N> using test_bidirectional_static_sized_range = test_static_sized_range<T, N, bidirectional_iterator_wrapper>;
//template <typename T, hamon::size_t N> using test_forward_static_sized_range       = test_static_sized_range<T, N, forward_iterator_wrapper>;
//template <typename T, hamon::size_t N> using test_input_static_sized_range         = test_static_sized_range<T, N, input_iterator_wrapper>;
//template <typename T, hamon::size_t N> using test_output_static_sized_range        = test_static_sized_range<T, N, output_iterator_wrapper>;

//template <typename T, hamon::size_t N, template <typename> class Iterator>
//struct test_static_sized_view : public test_static_sized_range<T, N, Iterator>, hamon::ranges::view_base
//{
//	using test_static_sized_range<T, N, Iterator>::test_static_sized_range;
//};
//
//template <typename T, hamon::size_t N> using test_contiguous_static_sized_view    = test_static_sized_view<T, N, contiguous_iterator_wrapper>;
//template <typename T, hamon::size_t N> using test_random_access_static_sized_view = test_static_sized_view<T, N, random_access_iterator_wrapper>;
//template <typename T, hamon::size_t N> using test_bidirectional_static_sized_view = test_static_sized_view<T, N, bidirectional_iterator_wrapper>;
//template <typename T, hamon::size_t N> using test_forward_static_sized_view       = test_static_sized_view<T, N, forward_iterator_wrapper>;
//template <typename T, hamon::size_t N> using test_input_static_sized_view         = test_static_sized_view<T, N, input_iterator_wrapper>;
//template <typename T, hamon::size_t N> using test_output_static_sized_view        = test_static_sized_view<T, N, output_iterator_wrapper>;

template <typename T, typename Iterator, typename Sentinel = test_sentinel<Iterator>>
struct test_borrowed_range : public test_range<T, Iterator, Sentinel>
{
	using base_t = test_range<T, Iterator, Sentinel>;
	using base_t::test_range;
};

template <typename T> using test_contiguous_borrowed_range    = test_borrowed_range<T, contiguous_iterator_wrapper<T>>;
template <typename T> using test_random_access_borrowed_range = test_borrowed_range<T, random_access_iterator_wrapper<T>>;
template <typename T> using test_bidirectional_borrowed_range = test_borrowed_range<T, bidirectional_iterator_wrapper<T>>;
template <typename T> using test_forward_borrowed_range       = test_borrowed_range<T, forward_iterator_wrapper<T>>;
template <typename T> using test_input_borrowed_range         = test_borrowed_range<T, input_iterator_wrapper<T>>;
template <typename T> using test_output_borrowed_range        = test_borrowed_range<T, output_iterator_wrapper<T>>;

template <typename T, typename Iterator, typename Sentinel = test_sentinel<Iterator>>
struct test_sized_borrowed_range : public test_range<T, Iterator, Sentinel>
{
	using base_t = test_range<T, Iterator, Sentinel>;
	using base_t::test_range;

	HAMON_CONSTEXPR hamon::size_t size() const noexcept
	{
		return static_cast<hamon::size_t>(base_t::m_last - base_t::m_first);
	}
};

template <typename T> using test_contiguous_sized_borrowed_range    = test_sized_borrowed_range<T, contiguous_iterator_wrapper<T>>;
template <typename T> using test_random_access_sized_borrowed_range = test_sized_borrowed_range<T, random_access_iterator_wrapper<T>>;
template <typename T> using test_bidirectional_sized_borrowed_range = test_sized_borrowed_range<T, bidirectional_iterator_wrapper<T>>;
template <typename T> using test_forward_sized_borrowed_range       = test_sized_borrowed_range<T, forward_iterator_wrapper<T>>;
template <typename T> using test_input_sized_borrowed_range         = test_sized_borrowed_range<T, input_iterator_wrapper<T>>;
template <typename T> using test_output_sized_borrowed_range        = test_sized_borrowed_range<T, output_iterator_wrapper<T>>;

template <typename T, typename Iterator, typename Sentinel = test_sentinel<Iterator>>
struct test_view : public test_range<T, Iterator, Sentinel>
{
	using base_t = test_range<T, Iterator, Sentinel>;
	using base_t::base_t;
};

template <typename T> using test_contiguous_view    = test_view<T, contiguous_iterator_wrapper<T>>;
template <typename T> using test_random_access_view = test_view<T, random_access_iterator_wrapper<T>>;
template <typename T> using test_bidirectional_view = test_view<T, bidirectional_iterator_wrapper<T>>;
template <typename T> using test_forward_view       = test_view<T, forward_iterator_wrapper<T>>;
template <typename T> using test_input_view         = test_view<T, input_iterator_wrapper<T>>;
template <typename T> using test_output_view        = test_view<T, output_iterator_wrapper<T>>;

template <typename T> using test_contiguous_common_range    = test_range<T, contiguous_iterator_wrapper<T>, contiguous_iterator_wrapper<T>>;
template <typename T> using test_random_access_common_range = test_range<T, random_access_iterator_wrapper<T>, random_access_iterator_wrapper<T>>;
template <typename T> using test_bidirectional_common_range = test_range<T, bidirectional_iterator_wrapper<T>, bidirectional_iterator_wrapper<T>>;
template <typename T> using test_forward_common_range       = test_range<T, forward_iterator_wrapper<T>, forward_iterator_wrapper<T>>;
template <typename T> using test_input_common_range         = test_range<T, input_iterator_wrapper<T>, input_iterator_wrapper<T>>;
// これはrangeにならないので定義しない
//template <typename T> using test_output_common_range        = test_range<T, output_iterator_wrapper<T>, output_iterator_wrapper<T>>;

template <typename T> using test_contiguous_common_view    = test_view<T, contiguous_iterator_wrapper<T>, contiguous_iterator_wrapper<T>>;
template <typename T> using test_random_access_common_view = test_view<T, random_access_iterator_wrapper<T>, random_access_iterator_wrapper<T>>;
template <typename T> using test_bidirectional_common_view = test_view<T, bidirectional_iterator_wrapper<T>, bidirectional_iterator_wrapper<T>>;
template <typename T> using test_forward_common_view       = test_view<T, forward_iterator_wrapper<T>, forward_iterator_wrapper<T>>;
template <typename T> using test_input_common_view         = test_view<T, input_iterator_wrapper<T>, input_iterator_wrapper<T>>;
// これはrangeにならないので定義しない
//template <typename T> using test_output_common_view        = test_view<T, output_iterator_wrapper<T>, output_iterator_wrapper<T>>;

}	// namespace hamon_ranges_test

using namespace hamon_ranges_test;

HAMON_RANGES_START_NAMESPACE

template <typename T, typename Iterator, typename Sentinel>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true,
	hamon_ranges_test::test_borrowed_range<T, Iterator, Sentinel>);

template <typename T, typename Iterator, typename Sentinel>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true,
	hamon_ranges_test::test_sized_borrowed_range<T, Iterator, Sentinel>);

template <typename T, typename Iterator, typename Sentinel>
HAMON_RANGES_SPECIALIZE_ENABLE_VIEW(true,
	hamon_ranges_test::test_view<T, Iterator, Sentinel>);

HAMON_RANGES_END_NAMESPACE

#endif // UNIT_TEST_COMMON_RANGES_TEST_HPP
