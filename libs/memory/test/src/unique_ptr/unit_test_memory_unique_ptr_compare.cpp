/**
 *	@file	unit_test_memory_unique_ptr_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<class T1, class D1, class T2, class D2>
 *	constexpr bool operator==(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y);
 *	template<class T1, class D1, class T2, class D2>
 *	bool operator<(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y);
 *	template<class T1, class D1, class T2, class D2>
 *	bool operator>(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y);
 *	template<class T1, class D1, class T2, class D2>
 *	bool operator<=(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y);
 *	template<class T1, class D1, class T2, class D2>
 *	bool operator>=(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y);
 *	template<class T1, class D1, class T2, class D2>
 *	requires three_way_comparable_with<typename unique_ptr<T1, D1>::pointer, typename unique_ptr<T2, D2>::pointer>
 *	compare_three_way_result_t<typename unique_ptr<T1, D1>::pointer, typename unique_ptr<T2, D2>::pointer>
 *	operator<=>(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y); 
 *
 *	template<class T, class D>
 *	constexpr bool operator==(const unique_ptr<T, D>& x, nullptr_t) noexcept;
 *	template<class T, class D>
 *	constexpr bool operator<(const unique_ptr<T, D>& x, nullptr_t);          
 *	template<class T, class D>
 *	constexpr bool operator<(nullptr_t, const unique_ptr<T, D>& y);          
 *	template<class T, class D>
 *	constexpr bool operator>(const unique_ptr<T, D>& x, nullptr_t);          
 *	template<class T, class D>
 *	constexpr bool operator>(nullptr_t, const unique_ptr<T, D>& y);          
 *	template<class T, class D>
 *	constexpr bool operator<=(const unique_ptr<T, D>& x, nullptr_t);         
 *	template<class T, class D>
 *	constexpr bool operator<=(nullptr_t, const unique_ptr<T, D>& y);         
 *	template<class T, class D>
 *	constexpr bool operator>=(const unique_ptr<T, D>& x, nullptr_t);         
 *	template<class T, class D>
 *	constexpr bool operator>=(nullptr_t, const unique_ptr<T, D>& y);         
 *	template<class T, class D>
 *	requires three_way_comparable<typename unique_ptr<T, D>::pointer>
 *	constexpr compare_three_way_result_t<typename unique_ptr<T, D>::pointer>
 *	operator<=>(const unique_ptr<T, D>& x, nullptr_t);  
 */

#include <hamon/memory/unique_ptr.hpp>
#include <hamon/compare.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace unique_ptr_test
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
	hamon::unique_ptr<int> up1(new int{42});
	hamon::unique_ptr<int> up2(new int{42});
	hamon::unique_ptr<int> up3;

	VERIFY( (up1 == up1));
	VERIFY(!(up1 == up2));
	VERIFY(!(up1 == up3));

	VERIFY(!(up1 != up1));
	VERIFY( (up1 != up2));
	VERIFY( (up1 != up3));

	VERIFY(!(up1 == nullptr));
	VERIFY(!(up2 == nullptr));
	VERIFY( (up3 == nullptr));

	VERIFY( (up1 != nullptr));
	VERIFY( (up2 != nullptr));
	VERIFY(!(up3 != nullptr));

	VERIFY(!(nullptr == up1));
	VERIFY(!(nullptr == up2));
	VERIFY( (nullptr == up3));

	VERIFY( (nullptr != up1));
	VERIFY( (nullptr != up2));
	VERIFY(!(nullptr != up3));

	return true;
}

HAMON_CXX20_CONSTEXPR
bool test2()
{
	int a[3]{};
	hamon::unique_ptr<int, D> up1(&a[0]);
	hamon::unique_ptr<int, D> up2(&a[1]);
	hamon::unique_ptr<int, D> up3(&a[1]);
	hamon::unique_ptr<int, D> up4(&a[2]);
	hamon::unique_ptr<int, D> up5;

	VERIFY(!(up2 == up1));
	VERIFY( (up2 == up2));
	VERIFY( (up2 == up3));
	VERIFY(!(up2 == up4));
	VERIFY(!(up2 == up5));

	VERIFY( (up2 != up1));
	VERIFY(!(up2 != up2));
	VERIFY(!(up2 != up3));
	VERIFY( (up2 != up4));
	VERIFY( (up2 != up5));

	VERIFY(!(up2 < up1));
	VERIFY(!(up2 < up2));
	VERIFY(!(up2 < up3));
	VERIFY( (up2 < up4));
	VERIFY(!(up2 < up5));

	VERIFY( (up2 > up1));
	VERIFY(!(up2 > up2));
	VERIFY(!(up2 > up3));
	VERIFY(!(up2 > up4));
	VERIFY( (up2 > up5));

	VERIFY(!(up2 <= up1));
	VERIFY( (up2 <= up2));
	VERIFY( (up2 <= up3));
	VERIFY( (up2 <= up4));
	VERIFY(!(up2 <= up5));

	VERIFY( (up2 >= up1));
	VERIFY( (up2 >= up2));
	VERIFY( (up2 >= up3));
	VERIFY(!(up2 >= up4));
	VERIFY( (up2 >= up5));

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY(hamon::is_gt(up2 <=> up1));
	VERIFY(hamon::is_eq(up2 <=> up2));
	VERIFY(hamon::is_eq(up2 <=> up3));
	VERIFY(hamon::is_lt(up2 <=> up4));
#endif

	VERIFY(!(up1 == nullptr));
	VERIFY( (up1 != nullptr));
	VERIFY(!(up1 <  nullptr));
	VERIFY( (up1 >  nullptr));
	VERIFY(!(up1 <= nullptr));
	VERIFY( (up1 >= nullptr));

	VERIFY( (up5 == nullptr));
	VERIFY(!(up5 != nullptr));
	VERIFY(!(up5 <  nullptr));
	VERIFY(!(up5 >  nullptr));
	VERIFY( (up5 <= nullptr));
	VERIFY( (up5 >= nullptr));

	VERIFY(!(nullptr == up1));
	VERIFY( (nullptr != up1));
	VERIFY( (nullptr <  up1));
	VERIFY(!(nullptr >  up1));
	VERIFY( (nullptr <= up1));
	VERIFY(!(nullptr >= up1));

	VERIFY( (nullptr == up5));
	VERIFY(!(nullptr != up5));
	VERIFY(!(nullptr <  up5));
	VERIFY(!(nullptr >  up5));
	VERIFY( (nullptr <= up5));
	VERIFY( (nullptr >= up5));

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY(hamon::is_gt(up1 <=> nullptr));
	VERIFY(hamon::is_eq(up5 <=> nullptr));
	VERIFY(hamon::is_lt(nullptr <=> up1));
	VERIFY(hamon::is_eq(nullptr <=> up5));
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UniquePtrTest, CompareTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1());
#if !defined(HAMON_CLANG_VERSION)
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2());
#else
	// clangだとポインタの大小比較をconstexprにできない
	EXPECT_TRUE(test2());
#endif
}

}	// namespace compare_test

}	// namespace unique_ptr_test

}	// namespace hamon_memory_test
