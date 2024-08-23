/**
 *	@file	unit_test_memory_shared_ptr_owner_hash.cpp
 *
 *	@brief	owner_hash のテスト
 *
 *	size_t owner_hash() const noexcept;
 */

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace shared_ptr_test
{

namespace owner_hash_test
{

struct X
{
	int i;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::shared_ptr<X> sp1(new X{3});
		hamon::shared_ptr<X> sp2(sp1);
		hamon::shared_ptr<X> sp3;
		hamon::shared_ptr<X> sp4(new X{3});
		hamon::shared_ptr<int> sp5(sp1, &(sp1->i));
		hamon::shared_ptr<int> sp6(sp1, nullptr);
		hamon::shared_ptr<int> sp7(sp4, &(sp1->i));
		hamon::shared_ptr<int> sp8;

		static_assert(noexcept(sp1.owner_hash()), "");
		static_assert(hamon::is_same<decltype(sp1.owner_hash()), hamon::size_t>::value, "");

		VERIFY( (sp1.owner_hash() == sp1.owner_hash()));
		VERIFY( (sp1.owner_hash() == sp2.owner_hash()));
		VERIFY(!(sp1.owner_hash() == sp3.owner_hash()));
		VERIFY(!(sp1.owner_hash() == sp4.owner_hash()));
		VERIFY( (sp1.owner_hash() == sp5.owner_hash()));
		VERIFY( (sp1.owner_hash() == sp6.owner_hash()));
		VERIFY(!(sp1.owner_hash() == sp7.owner_hash()));
		VERIFY(!(sp1.owner_hash() == sp8.owner_hash()));

		VERIFY(!(sp3.owner_hash() == sp1.owner_hash()));
		VERIFY(!(sp3.owner_hash() == sp2.owner_hash()));
		VERIFY( (sp3.owner_hash() == sp3.owner_hash()));
		VERIFY(!(sp3.owner_hash() == sp4.owner_hash()));
		VERIFY(!(sp3.owner_hash() == sp5.owner_hash()));
		VERIFY(!(sp3.owner_hash() == sp6.owner_hash()));
		VERIFY(!(sp3.owner_hash() == sp7.owner_hash()));
		VERIFY( (sp3.owner_hash() == sp8.owner_hash()));

		VERIFY(!(sp4.owner_hash() == sp1.owner_hash()));
		VERIFY(!(sp4.owner_hash() == sp2.owner_hash()));
		VERIFY(!(sp4.owner_hash() == sp3.owner_hash()));
		VERIFY( (sp4.owner_hash() == sp4.owner_hash()));
		VERIFY(!(sp4.owner_hash() == sp5.owner_hash()));
		VERIFY(!(sp4.owner_hash() == sp6.owner_hash()));
		VERIFY( (sp4.owner_hash() == sp7.owner_hash()));
		VERIFY(!(sp4.owner_hash() == sp8.owner_hash()));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(SharedPtrTest, OwnerHashTest)
{
	// std::hash が constexpr に対応していない TODO
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test());
}

}	// namespace owner_hash_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
