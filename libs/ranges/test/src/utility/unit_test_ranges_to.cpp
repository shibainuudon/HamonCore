/**
 *	@file	unit_test_ranges_to.cpp
 *
 *	@brief	ranges::to のテスト
 */

#include <hamon/ranges/utility/to.hpp>
#include <hamon/ranges/adaptors/split_view.hpp>
#include <hamon/ranges/adaptors/transform_view.hpp>
#include <hamon/ranges/adaptors/take_view.hpp>
#include <hamon/ranges/factories/iota_view.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/list.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/string_view.hpp>
#include <hamon/string.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/vector.hpp>
#include <hamon/array.hpp>
#include <hamon/assert.hpp>
#include <forward_list>
#include <utility>
#include <map>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace to_test
{

template <typename C, typename... Args>
struct has_to_impl
{
private:
	template <typename C2, typename... Args2,
		typename = decltype(hamon::ranges::to<C2>(hamon::declval<Args>()...))>
	static auto test(int) -> hamon::true_type;

	template <typename C2, typename... Args2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<C, Args...>(0));
};
template <typename C, typename... Args>
using has_to = typename has_to_impl<C, Args...>::type;

static_assert( has_to<test_input_range<int>, test_input_range<int>>::value, "");
static_assert( has_to<test_input_range<int>, test_input_range<int>, int>::value, "");
static_assert( has_to<test_input_range<int>, test_output_range<int>>::value, "");
static_assert( has_to<test_input_range<int>>::value, "");
static_assert(!has_to<test_input_view<int>, test_input_range<int>>::value, "");
static_assert(!has_to<test_input_view<int>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
struct DirectConstructible
{
	using value_type = T;

	template <typename R>
	constexpr DirectConstructible(R&& r, int val1 = 0, int val2 = 0)
		: m_first(hamon::ranges::begin(r))
		, m_last(hamon::ranges::end(r))
		, m_value1(val1)
		, m_value2(val2)
	{}

	constexpr T const* begin() const { return m_first; }
	constexpr T const* end() const { return m_last; }

	T const* m_first;
	T const* m_last;
	int m_value1;
	int m_value2;
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
template <typename R, typename... Args>
DirectConstructible(R&&, Args&&...)
	-> DirectConstructible<hamon::ranges::range_value_t<R>>;
#endif

HAMON_CXX14_CONSTEXPR bool direct_construction_test()
{
	{
		int const a[] = {1,2,3};
		using C = DirectConstructible<int>;
		{
			auto c = hamon::ranges::to<C>(a);
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.m_value1 == 0);
			VERIFY(c.m_value2 == 0);
		}
		{
			auto c = a | hamon::ranges::to<C>();
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.m_value1 == 0);
			VERIFY(c.m_value2 == 0);
		}
		{
			auto c = hamon::ranges::to<C>(a, 42);
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.m_value1 == 42);
			VERIFY(c.m_value2 == 0);
		}
		{
			auto c = a | hamon::ranges::to<C>(42, 13);
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.m_value1 == 42);
			VERIFY(c.m_value2 == 13);
		}

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		{
			auto c = hamon::ranges::to<DirectConstructible>(a);
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.m_value1 == 0);
			VERIFY(c.m_value2 == 0);
		}
		{
			auto c = a | hamon::ranges::to<DirectConstructible>(1, 2);
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.m_value1 == 1);
			VERIFY(c.m_value2 == 2);
		}
#endif
	}
	return true;
}

template <typename T>
struct FromRangeConstructible
{
	using value_type = T;

	template <typename R>
	constexpr FromRangeConstructible(hamon::from_range_t, R&& r, int val1 = 0, int val2 = 0)
		: m_first(hamon::ranges::begin(r))
		, m_last(hamon::ranges::end(r))
		, m_value1(val1)
		, m_value2(val2)
	{}

	constexpr T const* begin() const { return m_first; }
	constexpr T const* end() const { return m_last; }

	T const* m_first;
	T const* m_last;
	int m_value1;
	int m_value2;
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
template <typename R, typename... Args>
FromRangeConstructible(hamon::from_range_t, R&&, Args&&...)
	-> FromRangeConstructible<hamon::ranges::range_value_t<R>>;
#endif

HAMON_CXX14_CONSTEXPR bool from_range_construction_test()
{
	{
		int const a[] = {1,2,3};
		using C = FromRangeConstructible<int>;

		{
			auto c = hamon::ranges::to<C>(a);
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.m_value1 == 0);
			VERIFY(c.m_value2 == 0);
		}
		{
			auto c = a | hamon::ranges::to<C>();
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.m_value1 == 0);
			VERIFY(c.m_value2 == 0);
		}
		{
			auto c = hamon::ranges::to<C>(a, 13);
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.m_value1 == 13);
			VERIFY(c.m_value2 == 0);
		}
		{
			auto c = a | hamon::ranges::to<C>(14, 15);
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.m_value1 == 14);
			VERIFY(c.m_value2 == 15);
		}

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		{
			auto c = hamon::ranges::to<FromRangeConstructible>(a);
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.m_value1 == 0);
			VERIFY(c.m_value2 == 0);
		}
		{
			auto c = a | hamon::ranges::to<FromRangeConstructible>(16);
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.m_value1 == 16);
			VERIFY(c.m_value2 == 0);
		}
#endif
	}
	return true;
}

template <typename T>
struct CommonConstructible
{
	using value_type = T;

	template <typename Iterator>
	constexpr CommonConstructible(Iterator first, Iterator last, int val1 = 0, int val2 = 0)
		: m_first(first)
		, m_last(last)
		, m_value1(val1)
		, m_value2(val2)
	{}

	constexpr T const* begin() const { return m_first; }
	constexpr T const* end() const { return m_last; }

	T const* m_first;
	T const* m_last;
	int m_value1;
	int m_value2;
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
template <typename Iterator, typename... Args>
CommonConstructible(Iterator, Iterator, Args&&...)
	-> CommonConstructible<hamon::iter_value_t<Iterator>>;
#endif

HAMON_CXX14_CONSTEXPR bool common_construction_test()
{
	{
		int const a[] = {1,2,3};
		using C = CommonConstructible<int>;

		{
			auto c = hamon::ranges::to<C>(a);
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.m_value1 == 0);
			VERIFY(c.m_value2 == 0);
		}
		{
			auto c = a | hamon::ranges::to<C>();
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.m_value1 == 0);
			VERIFY(c.m_value2 == 0);
		}
		{
			auto c = hamon::ranges::to<C>(a, 13);
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.m_value1 == 13);
			VERIFY(c.m_value2 == 0);
		}
#if !(defined(HAMON_USE_STD_RANGES_TO) && defined(HAMON_STDLIB_DINKUMWARE))	// MSVC-STLの ranges::to は、あるバージョンまでtypoがあった
		{
			auto c = a | hamon::ranges::to<C>(14, 15);
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.m_value1 == 14);
			VERIFY(c.m_value2 == 15);
		}
#endif

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		{
			auto c = hamon::ranges::to<CommonConstructible>(a);
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.m_value1 == 0);
			VERIFY(c.m_value2 == 0);
		}
#if !(defined(HAMON_USE_STD_RANGES_TO) && defined(HAMON_STDLIB_DINKUMWARE))	// MSVC-STLの ranges::to は、あるバージョンまでtypoがあった
		{
			auto c = a | hamon::ranges::to<CommonConstructible>(16, 17);
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.m_value1 == 16);
			VERIFY(c.m_value2 == 17);
		}
#endif
#endif
	}
	return true;
}

template <typename T>
struct Insertable
{
	using value_type = T;

	constexpr Insertable(int val1 = 0, int val2 = 0)
		: m_size(0)
		, m_value1(val1)
		, m_value2(val2)
	{}

	HAMON_CXX14_CONSTEXPR T const* insert(T const* pos, T const& v)
	{
		(void)pos;
		m_buffer[m_size] = v;
		m_size++;
		return end();
	}

	constexpr T const* begin() const { return m_buffer; }
	constexpr T const* end() const { return m_buffer + m_size; }

	T m_buffer[10] {};
	hamon::size_t m_size;
	int m_value1;
	int m_value2;
};

template <typename T>
struct BackInsertable
{
	using value_type = T;

	constexpr BackInsertable(int val1 = 0, int val2 = 0)
		: m_size(0)
		, m_value1(val1)
		, m_value2(val2)
	{}

	HAMON_CXX14_CONSTEXPR void push_back(T const& v)
	{
		m_buffer[m_size] = v;
		m_size++;
	}

	constexpr T const* begin() const { return m_buffer; }
	constexpr T const* end() const { return m_buffer + m_size; }

	T m_buffer[10] {};
	hamon::size_t m_size;
	int m_value1;
	int m_value2;
};

template <typename T>
struct Reservable
{
	using value_type = T;

	constexpr Reservable(int val1 = 0, int val2 = 0)
		: m_capacity(0)
		, m_size(0)
		, m_value1(val1)
		, m_value2(val2)
	{}

	constexpr std::size_t capacity() const
	{
		return m_capacity;
	}

	constexpr std::size_t max_size() const
	{
		return 10;
	}
	
	constexpr std::size_t size() const
	{
		return m_size;
	}
	
	HAMON_CXX14_CONSTEXPR void reserve(std::size_t n)
	{
		m_capacity = n;
	}

	HAMON_CXX14_CONSTEXPR void push_back(T const& v)
	{
		HAMON_ASSERT(m_size < m_capacity);
		m_buffer[m_size] = v;
		m_size++;
	}

	constexpr T const* begin() const { return m_buffer; }
	constexpr T const* end() const { return m_buffer + m_size; }

	T m_buffer[10] {};
	hamon::size_t m_capacity;
	hamon::size_t m_size;
	int m_value1;
	int m_value2;
};

HAMON_CXX14_CONSTEXPR bool insert_construction_test()
{
	{
		int const a[] = {1,2,3};
		using C = Insertable<int>;

		{
			auto c = hamon::ranges::to<C>(a);
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.m_value1 == 0);
			VERIFY(c.m_value2 == 0);
		}
		{
			auto c = a | hamon::ranges::to<C>(42);
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.m_value1 == 42);
			VERIFY(c.m_value2 == 0);
		}
		{
			auto c = a | hamon::ranges::to<C>(1, 2);
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.m_value1 == 1);
			VERIFY(c.m_value2 == 2);
		}
	}
	{
		int const a[] = {1,2,3};
		using C = BackInsertable<int>;

		{
			auto c = hamon::ranges::to<C>(a);
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.m_value1 == 0);
			VERIFY(c.m_value2 == 0);
		}
		{
			auto c = a | hamon::ranges::to<C>(42);
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.m_value1 == 42);
			VERIFY(c.m_value2 == 0);
		}
		{
			auto c = a | hamon::ranges::to<C>(1, 2);
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.m_value1 == 1);
			VERIFY(c.m_value2 == 2);
		}
	}
	{
		int const a[] = {1,2,3};
		using C = Reservable<int>;

		{
			auto c = hamon::ranges::to<C>(a);
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.capacity() == 3);
			VERIFY(c.m_value1 == 0);
			VERIFY(c.m_value2 == 0);
		}
		{
			auto c = a | hamon::ranges::to<C>(42);
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.capacity() == 3);
			VERIFY(c.m_value1 == 42);
			VERIFY(c.m_value2 == 0);
		}
		{
			auto c = a | hamon::ranges::to<C>(1, 2);
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			VERIFY(hamon::ranges::equal(c, a));
			VERIFY(c.capacity() == 3);
			VERIFY(c.m_value1 == 1);
			VERIFY(c.m_value2 == 2);
		}
	}
	return true;
}

template <typename T>
struct MyContainer
{
	using value_type = T;

	constexpr MyContainer() = default;

	template <typename R>
	HAMON_CXX14_CONSTEXPR MyContainer(R&& r)
	{
		for (auto it = hamon::ranges::begin(r); it != hamon::ranges::end(r); ++it)
		{
			m_buf[m_size] = *it;
			++m_size;
		}
	}

	constexpr T const* begin() const { return m_buf; }
	constexpr T const* end() const { return m_buf + m_size; }
	constexpr T const& operator[](hamon::size_t i) const { return m_buf[i]; }
	constexpr hamon::size_t size() const { return m_size; }

	T m_buf[10]{};
	hamon::size_t m_size{};
};

HAMON_CXX14_CONSTEXPR bool nested_construction_test()
{
	{
		hamon::array<hamon::array<int, 3>, 2> a =
		{{
			{{1,2,3}},
			{{4,5,6}},
		}};
		using C = MyContainer<MyContainer<int>>;
		auto c = hamon::ranges::to<C>(a);
		VERIFY(c.size() == 2);
		VERIFY(c[0].size() == 3);
		VERIFY(c[0][0] == 1);
		VERIFY(c[0][1] == 2);
		VERIFY(c[0][2] == 3);
		VERIFY(c[1].size() == 3);
		VERIFY(c[1][0] == 4);
		VERIFY(c[1][1] == 5);
		VERIFY(c[1][2] == 6);
	}
	{
		hamon::array<hamon::array<hamon::array<int, 2>, 3>, 4> a =
		{{
			{{ {{ 1, 2}},{{ 3, 4}},{{ 5, 6}}, }},
			{{ {{11,12}},{{13,14}},{{15,16}}, }},
			{{ {{21,22}},{{23,24}},{{25,26}}, }},
			{{ {{31,32}},{{33,34}},{{35,36}}, }},
		}};
		using C = MyContainer<MyContainer<MyContainer<int>>>;
		auto c = hamon::ranges::to<C>(a);
		VERIFY(c.size() == 4);
		VERIFY(c[0].size() == 3);
		VERIFY(c[0][0].size() == 2);
		VERIFY(c[0][0][0] ==  1);
		VERIFY(c[0][0][1] ==  2);
		VERIFY(c[0][1][0] ==  3);
		VERIFY(c[0][1][1] ==  4);
		VERIFY(c[0][2][0] ==  5);
		VERIFY(c[0][2][1] ==  6);
		VERIFY(c[1][0][0] == 11);
		VERIFY(c[1][0][1] == 12);
		VERIFY(c[1][1][0] == 13);
		VERIFY(c[1][1][1] == 14);
		VERIFY(c[1][2][0] == 15);
		VERIFY(c[1][2][1] == 16);
		VERIFY(c[2][0][0] == 21);
		VERIFY(c[2][0][1] == 22);
		VERIFY(c[2][1][0] == 23);
		VERIFY(c[2][1][1] == 24);
		VERIFY(c[2][2][0] == 25);
		VERIFY(c[2][2][1] == 26);
		VERIFY(c[3][0][0] == 31);
		VERIFY(c[3][0][1] == 32);
		VERIFY(c[3][1][0] == 33);
		VERIFY(c[3][1][1] == 34);
		VERIFY(c[3][2][0] == 35);
		VERIFY(c[3][2][1] == 36);
	}
	return true;
}

#undef VERIFY

template <typename T>
struct myalloc
{
	using value_type = T;

	int state = 42;

	myalloc() = default;
	
	constexpr explicit myalloc(int i) noexcept : state {i} {}
	
	template <typename U>
	constexpr myalloc(const myalloc<U>& that) noexcept : state {that.state} {}

	HAMON_NODISCARD constexpr T* allocate(std::size_t n) const
	{
		return hamon::allocator<T>{}.allocate(n);
	}

	HAMON_CXX14_CONSTEXPR void deallocate(T* const p, const std::size_t n) const noexcept
	{
		hamon::allocator<T>{}.deallocate(p, n);
	}

	template <typename U>
	constexpr bool operator==(const myalloc<U>& that) const noexcept
	{
		return state == that.state;
	}
};

void to_vector_test()
{
	// direct construction
	{
		hamon::vector<int> const a = {1,2,3};
		{
			auto c = hamon::ranges::to<hamon::vector<int>>(a);
			static_assert(hamon::is_same<decltype(c), hamon::vector<int>>::value, "");
			EXPECT_TRUE(hamon::ranges::equal(c, a));
		}
		{
			auto c = a | hamon::ranges::to<hamon::vector<int>>();
			static_assert(hamon::is_same<decltype(c), hamon::vector<int>>::value, "");
			EXPECT_TRUE(hamon::ranges::equal(c, a));
		}
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		{
			auto c = hamon::ranges::to<hamon::vector>(a);
			static_assert(hamon::is_same<decltype(c), hamon::vector<int>>::value, "");
			EXPECT_TRUE(hamon::ranges::equal(c, a));
		}
		{
			auto c = a | hamon::ranges::to<hamon::vector>();
			static_assert(hamon::is_same<decltype(c), hamon::vector<int>>::value, "");
			EXPECT_TRUE(hamon::ranges::equal(c, a));
		}
#endif

		using Alloc = myalloc<int>;
		{
			auto c = hamon::ranges::to<hamon::vector<int, Alloc>>(a, Alloc{1});
			static_assert(hamon::is_same<decltype(c), hamon::vector<int, Alloc>>::value, "");
			EXPECT_TRUE(hamon::ranges::equal(c, a));
			EXPECT_TRUE(c.get_allocator().state == 1);
		}
		{
			auto c = a | hamon::ranges::to<hamon::vector<int, Alloc>>(Alloc{2});
			static_assert(hamon::is_same<decltype(c), hamon::vector<int, Alloc>>::value, "");
			EXPECT_TRUE(hamon::ranges::equal(c, a));
			EXPECT_TRUE(c.get_allocator().state == 2);
		}
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		{
			auto c = hamon::ranges::to<hamon::vector>(a, Alloc{3});
			static_assert(hamon::is_same<decltype(c), hamon::vector<int, Alloc>>::value, "");
			EXPECT_TRUE(hamon::ranges::equal(c, a));
			EXPECT_TRUE(c.get_allocator().state == 3);
		}
		{
			auto c = a | hamon::ranges::to<hamon::vector>(Alloc{4});
			static_assert(hamon::is_same<decltype(c), hamon::vector<int, Alloc>>::value, "");
			EXPECT_TRUE(hamon::ranges::equal(c, a));
			EXPECT_TRUE(c.get_allocator().state == 4);
		}
#endif
	}
	// from_range_t construction (C++23), common construction (C++20)
	{
		int const a[] = {1,2,3};
		{
			auto c = hamon::ranges::to<hamon::vector<int>>(a);
			static_assert(hamon::is_same<decltype(c), hamon::vector<int>>::value, "");
			EXPECT_TRUE(hamon::ranges::equal(c, a));
		}
		{
			auto c = a | hamon::ranges::to<hamon::vector<int>>();
			static_assert(hamon::is_same<decltype(c), hamon::vector<int>>::value, "");
			EXPECT_TRUE(hamon::ranges::equal(c, a));
		}
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		{
			auto c = hamon::ranges::to<hamon::vector>(a);
			static_assert(hamon::is_same<decltype(c), hamon::vector<int>>::value, "");
			EXPECT_TRUE(hamon::ranges::equal(c, a));
		}
		{
			auto c = a | hamon::ranges::to<hamon::vector>();
			static_assert(hamon::is_same<decltype(c), hamon::vector<int>>::value, "");
			EXPECT_TRUE(hamon::ranges::equal(c, a));
		}
#endif

		using Alloc = myalloc<int>;
		{
			auto c = hamon::ranges::to<hamon::vector<int, Alloc>>(a, Alloc{13});
			static_assert(hamon::is_same<decltype(c), hamon::vector<int, Alloc>>::value, "");
			EXPECT_TRUE(hamon::ranges::equal(c, a));
			EXPECT_TRUE(c.get_allocator().state == 13);
		}
		{
			auto c = a | hamon::ranges::to<hamon::vector<int, Alloc>>(Alloc{14});
			static_assert(hamon::is_same<decltype(c), hamon::vector<int, Alloc>>::value, "");
			EXPECT_TRUE(hamon::ranges::equal(c, a));
			EXPECT_TRUE(c.get_allocator().state == 14);
		}
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		{
			auto c = hamon::ranges::to<hamon::vector>(a, Alloc{15});
			static_assert(hamon::is_same<decltype(c), hamon::vector<int, Alloc>>::value, "");
			EXPECT_TRUE(hamon::ranges::equal(c, a));
			EXPECT_TRUE(c.get_allocator().state == 15);
		}
		{
			auto c = a | hamon::ranges::to<hamon::vector>(Alloc{16});
			static_assert(hamon::is_same<decltype(c), hamon::vector<int, Alloc>>::value, "");
			EXPECT_TRUE(hamon::ranges::equal(c, a));
			EXPECT_TRUE(c.get_allocator().state == 16);
		}
#endif
	}
	// nested construction
	{
		int const a[2][3] =
		{
			{1,2,3},
			{4,5,6},
		};
		using C = hamon::vector<hamon::vector<int>>;
		{
			auto c = hamon::ranges::to<C>(a);
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			EXPECT_TRUE(hamon::ranges::equal(c[0], a[0]));
			EXPECT_TRUE(hamon::ranges::equal(c[1], a[1]));
		}
		{
			auto c = a | hamon::ranges::to<C>();
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			EXPECT_TRUE(hamon::ranges::equal(c[0], a[0]));
			EXPECT_TRUE(hamon::ranges::equal(c[1], a[1]));
		}
	}
	{
		int const a[3][2][2] =
		{
			{{0,1},{2,3}},
			{{4,5},{6,7}},
			{{8,9},{10,11}},
		};
		using C = hamon::vector<hamon::vector<hamon::vector<int>>>;
		{
			auto c = hamon::ranges::to<C>(a);
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			EXPECT_TRUE(c.size() == 3);
			EXPECT_TRUE(c[0].size() == 2);
			EXPECT_TRUE(c[0][0].size() == 2);
			EXPECT_TRUE(c[0][0][0] == 0);
			EXPECT_TRUE(c[0][0][1] == 1);
			EXPECT_TRUE(c[0][1][0] == 2);
			EXPECT_TRUE(c[0][1][1] == 3);
			EXPECT_TRUE(c[1][0][0] == 4);
			EXPECT_TRUE(c[1][0][1] == 5);
			EXPECT_TRUE(c[1][1][0] == 6);
			EXPECT_TRUE(c[1][1][1] == 7);
			EXPECT_TRUE(c[2][0][0] == 8);
			EXPECT_TRUE(c[2][0][1] == 9);
			EXPECT_TRUE(c[2][1][0] == 10);
			EXPECT_TRUE(c[2][1][1] == 11);
		}
		{
			auto c = a | hamon::ranges::to<C>();
			static_assert(hamon::is_same<decltype(c), C>::value, "");
			EXPECT_TRUE(c.size() == 3);
			EXPECT_TRUE(c[0].size() == 2);
			EXPECT_TRUE(c[0][0].size() == 2);
			EXPECT_TRUE(c[0][0][0] == 0);
			EXPECT_TRUE(c[0][0][1] == 1);
			EXPECT_TRUE(c[0][1][0] == 2);
			EXPECT_TRUE(c[0][1][1] == 3);
			EXPECT_TRUE(c[1][0][0] == 4);
			EXPECT_TRUE(c[1][0][1] == 5);
			EXPECT_TRUE(c[1][1][0] == 6);
			EXPECT_TRUE(c[1][1][1] == 7);
			EXPECT_TRUE(c[2][0][0] == 8);
			EXPECT_TRUE(c[2][0][1] == 9);
			EXPECT_TRUE(c[2][1][0] == 10);
			EXPECT_TRUE(c[2][1][1] == 11);
		}
	}
}

void to_map_test()
{
	{
		std::pair<std::string, int> a[] =
		{
			{"the",   10},
			{"quick", 31},
			{"brown", -1},
			{"fox",    6},
		};
		using C = std::map<std::string, int>;

		auto c0 = hamon::ranges::to<C>(a);
		static_assert(hamon::is_same<decltype(c0), C>::value, "");
		EXPECT_TRUE(c0.size() == 4);
		EXPECT_TRUE(c0["the"]   == 10);
		EXPECT_TRUE(c0["quick"] == 31);
		EXPECT_TRUE(c0["brown"] == -1);
		EXPECT_TRUE(c0["fox"]   ==  6);
		{
			auto c1 = a | hamon::ranges::to<C>();
			static_assert(hamon::is_same<decltype(c1), C>::value, "");
			EXPECT_TRUE(c1 == c0);
		}
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		{
			auto c2 = hamon::ranges::to<std::map>(a);
			static_assert(hamon::is_same<decltype(c2), C>::value, "");
			EXPECT_TRUE(c2 == c0);
		}
		{
			auto c3 = a | hamon::ranges::to<std::map>();
			static_assert(hamon::is_same<decltype(c3), C>::value, "");
			EXPECT_TRUE(c3 == c0);
		}
#endif
	}
}

GTEST_TEST(RangesTest, ToTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(direct_construction_test());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(from_range_construction_test());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(common_construction_test());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(insert_construction_test());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(nested_construction_test());

	to_vector_test();
	to_map_test();

	{
		// [range.utility.conv.general]/2
		// Example 1:
		hamon::string_view str = "the quick brown fox";
		auto words = hamon::views::split(str, ' ') | hamon::ranges::to<hamon::vector<hamon::string>>();
		// words is vector<string>{"the", "quick", "brown", "fox"}
		static_assert(hamon::is_same<decltype(words), hamon::vector<hamon::string>>::value, "");
		hamon::vector<hamon::string> expected = {"the", "quick", "brown", "fox"};
		EXPECT_TRUE(hamon::ranges::equal(words, expected));
	}
	{
		struct fn
		{
			constexpr int operator()(int v) const { return v * 2; }
		};

		auto vec = hamon::views::iota(1, 5) |
			hamon::views::transform(fn{}) |
			hamon::ranges::to<hamon::vector<int>>();
		static_assert(hamon::is_same<decltype(vec), hamon::vector<int>>::value, "");
		{
			int const expected[] = {2, 4, 6, 8};
			EXPECT_TRUE(hamon::ranges::equal(vec, expected));
		}
		auto lst = vec | hamon::views::take(3) | hamon::ranges::to<hamon::list<int>>();
		static_assert(hamon::is_same<decltype(lst), hamon::list<int>>::value, "");
		{
			int const expected[] = {2, 4, 6};
			EXPECT_TRUE(hamon::ranges::equal(lst, expected));
		}
	}
}

}	// namespace to_test
}	// namespace hamon_ranges_test
