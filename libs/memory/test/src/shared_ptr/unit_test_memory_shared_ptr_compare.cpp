/**
 *	@file	unit_test_memory_shared_ptr_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<class T, class U>
 *	bool operator==(const shared_ptr<T>& a, const shared_ptr<U>& b) noexcept;
 *	template<class T, class U>
 *	strong_ordering operator<=>(const shared_ptr<T>& a, const shared_ptr<U>& b) noexcept;
 *
 *	template<class T>
 *	bool operator==(const shared_ptr<T>& x, nullptr_t) noexcept;
 *	template<class T>
 *	strong_ordering operator<=>(const shared_ptr<T>& x, nullptr_t) noexcept;
 */

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/compare.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace shared_ptr_test
{

namespace compare_test
{

struct D
{
	template <typename T>
	HAMON_CXX14_CONSTEXPR void operator()(T*) const {}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test1()
{
	hamon::shared_ptr<int> sp1(new int{42});
	hamon::shared_ptr<int> sp2(new int{42});
	hamon::shared_ptr<int> sp3(sp1);
	hamon::shared_ptr<int> sp4;

	VERIFY( (sp1 == sp1));
	VERIFY(!(sp1 == sp2));
	VERIFY( (sp1 == sp3));
	VERIFY(!(sp1 == sp4));

	VERIFY(!(sp1 != sp1));
	VERIFY( (sp1 != sp2));
	VERIFY(!(sp1 != sp3));
	VERIFY( (sp1 != sp4));

	VERIFY(!(sp1 == nullptr));
	VERIFY(!(sp2 == nullptr));
	VERIFY(!(sp3 == nullptr));
	VERIFY( (sp4 == nullptr));

	VERIFY( (sp1 != nullptr));
	VERIFY( (sp2 != nullptr));
	VERIFY( (sp3 != nullptr));
	VERIFY(!(sp4 != nullptr));

	VERIFY(!(nullptr == sp1));
	VERIFY(!(nullptr == sp2));
	VERIFY(!(nullptr == sp3));
	VERIFY( (nullptr == sp4));

	VERIFY( (nullptr != sp1));
	VERIFY( (nullptr != sp2));
	VERIFY( (nullptr != sp3));
	VERIFY(!(nullptr != sp4));

	return true;
}

HAMON_CXX20_CONSTEXPR
bool test2()
{
	int a[3]{};
	hamon::shared_ptr<int> sp1(&a[0], D{});
	hamon::shared_ptr<int> sp2(&a[1], D{});
	hamon::shared_ptr<int> sp3(&a[1], D{});
	hamon::shared_ptr<int> sp4(&a[2], D{});
	hamon::shared_ptr<int> sp5;

	static_assert(noexcept(sp1 == sp2), "");
	static_assert(noexcept(sp1 != sp2), "");
	static_assert(noexcept(sp1 <  sp2), "");
	static_assert(noexcept(sp1 >  sp2), "");
	static_assert(noexcept(sp1 <= sp2), "");
	static_assert(noexcept(sp1 >= sp2), "");

	VERIFY(!(sp2 == sp1));
	VERIFY( (sp2 == sp2));
	VERIFY( (sp2 == sp3));
	VERIFY(!(sp2 == sp4));
	VERIFY(!(sp2 == sp5));

	VERIFY( (sp2 != sp1));
	VERIFY(!(sp2 != sp2));
	VERIFY(!(sp2 != sp3));
	VERIFY( (sp2 != sp4));
	VERIFY( (sp2 != sp5));

	VERIFY(!(sp2 < sp1));
	VERIFY(!(sp2 < sp2));
	VERIFY(!(sp2 < sp3));
	VERIFY( (sp2 < sp4));
	VERIFY(!(sp2 < sp5));

	VERIFY( (sp2 > sp1));
	VERIFY(!(sp2 > sp2));
	VERIFY(!(sp2 > sp3));
	VERIFY(!(sp2 > sp4));
	VERIFY( (sp2 > sp5));

	VERIFY(!(sp2 <= sp1));
	VERIFY( (sp2 <= sp2));
	VERIFY( (sp2 <= sp3));
	VERIFY( (sp2 <= sp4));
	VERIFY(!(sp2 <= sp5));

	VERIFY( (sp2 >= sp1));
	VERIFY( (sp2 >= sp2));
	VERIFY( (sp2 >= sp3));
	VERIFY(!(sp2 >= sp4));
	VERIFY( (sp2 >= sp5));

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(noexcept(sp1 <=> sp2), "");
	VERIFY(hamon::is_gt(sp2 <=> sp1));
	VERIFY(hamon::is_eq(sp2 <=> sp2));
	VERIFY(hamon::is_eq(sp2 <=> sp3));
	VERIFY(hamon::is_lt(sp2 <=> sp4));
#endif

	static_assert(noexcept(sp1 == nullptr), "");
	static_assert(noexcept(sp1 != nullptr), "");
	static_assert(noexcept(sp1 <  nullptr), "");
	static_assert(noexcept(sp1 >  nullptr), "");
	static_assert(noexcept(sp1 <= nullptr), "");
	static_assert(noexcept(sp1 >= nullptr), "");

	static_assert(noexcept(nullptr == sp1), "");
	static_assert(noexcept(nullptr != sp1), "");
	static_assert(noexcept(nullptr <  sp1), "");
	static_assert(noexcept(nullptr >  sp1), "");
	static_assert(noexcept(nullptr <= sp1), "");
	static_assert(noexcept(nullptr >= sp1), "");

	VERIFY(!(sp1 == nullptr));
	VERIFY( (sp1 != nullptr));
	VERIFY(!(sp1 <  nullptr));
	VERIFY( (sp1 >  nullptr));
	VERIFY(!(sp1 <= nullptr));
	VERIFY( (sp1 >= nullptr));

	VERIFY( (sp5 == nullptr));
	VERIFY(!(sp5 != nullptr));
	VERIFY(!(sp5 <  nullptr));
	VERIFY(!(sp5 >  nullptr));
	VERIFY( (sp5 <= nullptr));
	VERIFY( (sp5 >= nullptr));

	VERIFY(!(nullptr == sp1));
	VERIFY( (nullptr != sp1));
	VERIFY( (nullptr <  sp1));
	VERIFY(!(nullptr >  sp1));
	VERIFY( (nullptr <= sp1));
	VERIFY(!(nullptr >= sp1));

	VERIFY( (nullptr == sp5));
	VERIFY(!(nullptr != sp5));
	VERIFY(!(nullptr <  sp5));
	VERIFY(!(nullptr >  sp5));
	VERIFY( (nullptr <= sp5));
	VERIFY( (nullptr >= sp5));

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(noexcept(sp1 <=> nullptr), "");
	static_assert(noexcept(nullptr <=> sp1), "");
	VERIFY(hamon::is_gt(sp1 <=> nullptr));
	VERIFY(hamon::is_eq(sp5 <=> nullptr));
	VERIFY(hamon::is_lt(nullptr <=> sp1));
	VERIFY(hamon::is_eq(nullptr <=> sp5));
#endif

	return true;
}

#undef VERIFY

#if defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC) && \
	!(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 130000))
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#else
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#endif

GTEST_TEST(SharedPtrTest, CompareTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test1());
	// ポインタの大小比較はconstexprにできない
	EXPECT_TRUE(test2());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace compare_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
