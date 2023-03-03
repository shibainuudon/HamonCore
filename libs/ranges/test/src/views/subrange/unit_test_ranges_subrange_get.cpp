/**
 *	@file	unit_test_ranges_subrange_get.cpp
 *
 *	@brief	ranges::get(subrange) のテスト
 */

#include <hamon/ranges/views/subrange.hpp>
#include <hamon/ranges/views/subrange_kind.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include <iterator>
#include <utility>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace subrange_test
{
namespace get_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <std::size_t I, typename S>
struct HasGetImpl
{
private:
	template <std::size_t I2, typename S2,
		typename = decltype(hamon::ranges::get<I2>(std::declval<S2>())),
		typename = decltype(hamon::get<I2>(std::declval<S2>()))
	>
	static auto test(int) -> hamon::true_type;

	template <std::size_t I2, typename S2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<I, S>(0));
};

template <std::size_t I, typename S>
using HasGet = typename HasGetImpl<I, S>::type;

static_assert( HasGet<0, hamon::ranges::subrange<int*>>::value, "");
static_assert( HasGet<1, hamon::ranges::subrange<int*>>::value, "");
static_assert(!HasGet<2, hamon::ranges::subrange<int*>>::value, "");
static_assert(!HasGet<3, hamon::ranges::subrange<int*>>::value, "");

static_assert( HasGet<0, hamon::ranges::subrange<int*>&>::value, "");
static_assert( HasGet<1, hamon::ranges::subrange<int*>&>::value, "");
static_assert(!HasGet<2, hamon::ranges::subrange<int*>&>::value, "");
static_assert(!HasGet<3, hamon::ranges::subrange<int*>&>::value, "");

static_assert( HasGet<0, hamon::ranges::subrange<int*> const&>::value, "");
static_assert( HasGet<1, hamon::ranges::subrange<int*> const&>::value, "");
static_assert(!HasGet<2, hamon::ranges::subrange<int*> const&>::value, "");
static_assert(!HasGet<3, hamon::ranges::subrange<int*> const&>::value, "");

static_assert( HasGet<0, hamon::ranges::subrange<int*>&&>::value, "");
static_assert( HasGet<1, hamon::ranges::subrange<int*>&&>::value, "");
static_assert(!HasGet<2, hamon::ranges::subrange<int*>&&>::value, "");
static_assert(!HasGet<3, hamon::ranges::subrange<int*>&&>::value, "");

static_assert( HasGet<0, hamon::ranges::subrange<int*> const&&>::value, "");
static_assert( HasGet<1, hamon::ranges::subrange<int*> const&&>::value, "");
static_assert(!HasGet<2, hamon::ranges::subrange<int*> const&&>::value, "");
static_assert(!HasGet<3, hamon::ranges::subrange<int*> const&&>::value, "");

template <typename T>
struct MoveOnlyForwardIterator
{
	T*	m_ptr;
	using iterator_category = std::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = std::ptrdiff_t;
	using reference         = T&;
	HAMON_CXX14_CONSTEXPR MoveOnlyForwardIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR MoveOnlyForwardIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX11_CONSTEXPR T&                       operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const MoveOnlyForwardIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const MoveOnlyForwardIterator& rhs) const { return !(*this == rhs); }

	friend HAMON_CXX11_CONSTEXPR bool operator==(const MoveOnlyForwardIterator& lhs, T* rhs) { return lhs.m_ptr == rhs; }
	friend HAMON_CXX11_CONSTEXPR bool operator!=(const MoveOnlyForwardIterator& lhs, T* rhs) { return !(lhs == rhs); }
	friend HAMON_CXX11_CONSTEXPR bool operator==(T* rhs, const MoveOnlyForwardIterator& lhs) { return lhs.m_ptr == rhs; }
	friend HAMON_CXX11_CONSTEXPR bool operator!=(T* rhs, const MoveOnlyForwardIterator& lhs) { return !(lhs == rhs); }

	MoveOnlyForwardIterator() = default;
	MoveOnlyForwardIterator(MoveOnlyForwardIterator &&) = default;
	MoveOnlyForwardIterator &operator=(MoveOnlyForwardIterator&&) = default;
	MoveOnlyForwardIterator(MoveOnlyForwardIterator const&) = delete;
	HAMON_CXX11_CONSTEXPR MoveOnlyForwardIterator(T* ptr) : m_ptr(ptr) { }
};

using MoveOnlySubrange =
	hamon::ranges::subrange<MoveOnlyForwardIterator<int>, int*>;

static_assert( HasGet<0, MoveOnlySubrange>::value, "");
static_assert( HasGet<1, MoveOnlySubrange>::value, "");
static_assert(!HasGet<2, MoveOnlySubrange>::value, "");
static_assert(!HasGet<3, MoveOnlySubrange>::value, "");

static_assert(!HasGet<0, MoveOnlySubrange&>::value, "");
static_assert( HasGet<1, MoveOnlySubrange&>::value, "");
static_assert(!HasGet<2, MoveOnlySubrange&>::value, "");
static_assert(!HasGet<3, MoveOnlySubrange&>::value, "");

static_assert(!HasGet<0, MoveOnlySubrange const&>::value, "");
static_assert( HasGet<1, MoveOnlySubrange const&>::value, "");
static_assert(!HasGet<2, MoveOnlySubrange const&>::value, "");
static_assert(!HasGet<3, MoveOnlySubrange const&>::value, "");

static_assert( HasGet<0, MoveOnlySubrange&&>::value, "");
static_assert( HasGet<1, MoveOnlySubrange&&>::value, "");
static_assert(!HasGet<2, MoveOnlySubrange&&>::value, "");
static_assert(!HasGet<3, MoveOnlySubrange&&>::value, "");

static_assert(!HasGet<0, MoveOnlySubrange const&&>::value, "");
static_assert( HasGet<1, MoveOnlySubrange const&&>::value, "");
static_assert(!HasGet<2, MoveOnlySubrange const&&>::value, "");
static_assert(!HasGet<3, MoveOnlySubrange const&&>::value, "");

using ForwardRange = test_forward_range<int>;

using ForwardSizedSubrange =
	hamon::ranges::subrange<
		hamon::ranges::iterator_t<ForwardRange>,
		hamon::ranges::sentinel_t<ForwardRange>,
		hamon::ranges::subrange_kind::sized
	>;
using ForwardUnsizedSubrange =
	hamon::ranges::subrange<
		hamon::ranges::iterator_t<ForwardRange>,
		hamon::ranges::sentinel_t<ForwardRange>,
		hamon::ranges::subrange_kind::unsized
	>;

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		int x[] = {1, 2, 3, 4, 5};
		ForwardRange r{x};
		ForwardSizedSubrange sr(r.begin(), r.end(), 5);
		VERIFY(hamon::ranges::get<0>(sr).m_ptr      == x);
		VERIFY(hamon::ranges::get<1>(sr).m_it.m_ptr == x+5);
		VERIFY(hamon::ranges::get<0>(std::move(sr)).m_ptr      == x);
		VERIFY(hamon::ranges::get<1>(std::move(sr)).m_it.m_ptr == x+5);
		VERIFY(hamon::get<0>(sr).m_ptr      == x);
		VERIFY(hamon::get<1>(sr).m_it.m_ptr == x+5);
		VERIFY(hamon::get<0>(std::move(sr)).m_ptr      == x);
		VERIFY(hamon::get<1>(std::move(sr)).m_it.m_ptr == x+5);

		using Iter = hamon::ranges::iterator_t<ForwardRange>;
		using Sent = hamon::ranges::sentinel_t<ForwardRange>;
		using R = ForwardSizedSubrange;
		static_assert(hamon::is_same<decltype(hamon::get<0>(sr)), Iter>::value, "");
		static_assert(hamon::is_same<decltype(hamon::get<1>(sr)), Sent>::value, "");
		static_assert(hamon::is_same<decltype(hamon::get<0>(static_cast<R&&>(sr))), Iter>::value, "");
		static_assert(hamon::is_same<decltype(hamon::get<1>(static_cast<R&&>(sr))), Sent>::value, "");
		static_assert(hamon::is_same<decltype(hamon::get<0>(static_cast<const R&>(sr))), Iter>::value, "");
		static_assert(hamon::is_same<decltype(hamon::get<1>(static_cast<const R&>(sr))), Sent>::value, "");
		static_assert(hamon::is_same<decltype(hamon::get<0>(static_cast<const R&&>(sr))), Iter>::value, "");
		static_assert(hamon::is_same<decltype(hamon::get<1>(static_cast<const R&&>(sr))), Sent>::value, "");
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	{
		int x[] = {1, 2, 3, 4, 5};
		ForwardRange r{x};
		ForwardUnsizedSubrange sr(r.begin(), r.end());
		VERIFY(hamon::ranges::get<0>(sr).m_ptr      == x);
		VERIFY(hamon::ranges::get<1>(sr).m_it.m_ptr == x+5);
		VERIFY(hamon::ranges::get<0>(std::move(sr)).m_ptr      == x);
		VERIFY(hamon::ranges::get<1>(std::move(sr)).m_it.m_ptr == x+5);
		VERIFY(hamon::get<0>(sr).m_ptr      == x);
		VERIFY(hamon::get<1>(sr).m_it.m_ptr == x+5);
		VERIFY(hamon::get<0>(std::move(sr)).m_ptr      == x);
		VERIFY(hamon::get<1>(std::move(sr)).m_it.m_ptr == x+5);

		using Iter = hamon::ranges::iterator_t<ForwardRange>;
		using Sent = hamon::ranges::sentinel_t<ForwardRange>;
		using R = ForwardUnsizedSubrange;
		static_assert(hamon::is_same<decltype(hamon::get<0>(sr)), Iter>::value, "");
		static_assert(hamon::is_same<decltype(hamon::get<1>(sr)), Sent>::value, "");
		static_assert(hamon::is_same<decltype(hamon::get<0>(static_cast<R&&>(sr))), Iter>::value, "");
		static_assert(hamon::is_same<decltype(hamon::get<1>(static_cast<R&&>(sr))), Sent>::value, "");
		static_assert(hamon::is_same<decltype(hamon::get<0>(static_cast<const R&>(sr))), Iter>::value, "");
		static_assert(hamon::is_same<decltype(hamon::get<1>(static_cast<const R&>(sr))), Sent>::value, "");
		static_assert(hamon::is_same<decltype(hamon::get<0>(static_cast<const R&&>(sr))), Iter>::value, "");
		static_assert(hamon::is_same<decltype(hamon::get<1>(static_cast<const R&&>(sr))), Sent>::value, "");
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	{
		int x[] = {1, 2, 3, 4, 5};
		MoveOnlySubrange sr(x, x+5);
//		VERIFY(hamon::ranges::get<0>(sr).m_ptr == x);
		VERIFY(hamon::ranges::get<1>(sr)       == x+5);
		VERIFY(hamon::ranges::get<0>(std::move(sr)).m_ptr == x);
		VERIFY(hamon::ranges::get<1>(std::move(sr))       == x+5);
	}
	return true;
}

GTEST_TEST(RangesTest, SubrangeGetTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

#undef VERIFY

}	// namespace get_test
}	// namespace subrange_test
}	// namespace hamon_ranges_test
