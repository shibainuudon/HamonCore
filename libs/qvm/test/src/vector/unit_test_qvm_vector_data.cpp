/**
 *	@file	unit_test_qvm_vector_data.cpp
 *
 *	@brief	dataのテスト
 */

#include <hamon/qvm/vector.hpp>
#include "constexpr_test.hpp"
#include "vector_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace vector_test
{

template <typename T, std::size_t N>
void DataTest()
{
	using vector = hamon::qvm::vector<T, N>;

	{
		vector const v;
		auto p = v.data();
		EXPECT_TRUE(p != nullptr);
		EXPECT_TRUE(p == &v[0]);
		static_assert(std::is_same<decltype(p), T const*>::value, "");
	}
	{
		vector v;
		auto p = v.data();
		EXPECT_TRUE(p != nullptr);
		EXPECT_TRUE(p == &v[0]);
		static_assert(std::is_same<decltype(p), T*>::value, "");
	}
}

TYPED_TEST(VectorTest, DataTest)
{
	using T = TypeParam;
	DataTest<T, 2>();
	DataTest<T, 3>();
	DataTest<T, 4>();
}

}	// namespace vector_test

}	// namespace hamon_qvm_test
