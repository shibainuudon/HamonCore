/**
 *	@file	unit_test_qvm_vector_any.cpp
 *
 *	@brief	anyのテスト
 */

#include <hamon/qvm/vector.hpp>
#include "constexpr_test.hpp"
#include "vector_test.hpp"
#include <type_traits>

namespace hamon_qvm_test
{

namespace vector_test
{

TYPED_TEST(VectorTest, AnyTest)
{
	using vector2b = hamon::qvm::vector<bool, 2>;
	using vector3b = hamon::qvm::vector<bool, 3>;
	using vector4b = hamon::qvm::vector<bool, 4>;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  hamon::qvm::any(vector2b(true,  true)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  hamon::qvm::any(vector2b(false, true)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  hamon::qvm::any(vector2b(true,  false)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::qvm::any(vector2b(false, false)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  hamon::qvm::any(vector3b(true,  true,  true)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  hamon::qvm::any(vector3b(false, true,  true)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  hamon::qvm::any(vector3b(true,  false, true)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  hamon::qvm::any(vector3b(true,  true,  false)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::qvm::any(vector3b(false, false, false)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  hamon::qvm::any(vector4b(true,  true,  true,  true)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  hamon::qvm::any(vector4b(false, true,  true,  true)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  hamon::qvm::any(vector4b(true,  false, true,  true)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  hamon::qvm::any(vector4b(true,  true,  false, true)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  hamon::qvm::any(vector4b(true,  true,  true,  false)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::qvm::any(vector4b(false, false, false, false)));
}

}	// namespace vector_test

}	// namespace hamon_qvm_test
