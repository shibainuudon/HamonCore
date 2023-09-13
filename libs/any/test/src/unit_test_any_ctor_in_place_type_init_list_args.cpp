/**
 *	@file	unit_test_any_ctor_in_place_type_init_list_args.cpp
 *
 *	@brief	in_place_type_tとinitializer_listと引数をとるコンストラクタのテスト
 *
 *	template<class T, class U, class... Args>
 *	explicit any(in_place_type_t<T>, initializer_list<U> il, Args&&... args);
 */

#include <hamon/any.hpp>
#include <hamon/utility/in_place_type.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>

GTEST_TEST(AnyTest, CtorInPlaceTypeInitListArgsTest)
{
	{
		std::allocator<int> alloc;
		hamon::any a { hamon::in_place_type_t<hamon::vector<int>>{}, {3, 1, 4}, alloc};
		EXPECT_TRUE(a.has_value());
		auto const& vec = hamon::any_cast<hamon::vector<int> const&>(a);
		EXPECT_EQ(3, vec[0]);
		EXPECT_EQ(1, vec[1]);
		EXPECT_EQ(4, vec[2]);
	}
}
