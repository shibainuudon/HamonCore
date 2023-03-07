/**
 *	@file	unit_test_qvm_matrix_serialize.cpp
 *
 *	@brief	シリアライズのテスト
 */

#include <hamon/qvm/matrix.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <gtest/gtest.h>
#include "serialize_test.hpp"
#include "matrix_test.hpp"

namespace hamon_qvm_test
{

namespace matrix_test
{

using MatrixSerializeTestTypes = ::testing::Types<
	int
	, float
	, double
#if !defined(__EMSCRIPTEN__)
	, long double
#endif
>;

template <typename T>
class MatrixSerializeTest : public ::testing::Test {};

TYPED_TEST_SUITE(MatrixSerializeTest, MatrixSerializeTestTypes);

template <typename T, hamon::size_t N, hamon::size_t M>
void MatrixSerializeTestSub()
{
	using namespace hamon::serialization;
	using matrix_type = hamon::qvm::matrix<T, N, M>;

	matrix_type const v = make_random_matrix<T, N, M>();

	SerializeTest<json_oarchive,   json_iarchive,   std::stringstream>(v);
	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(HAMON_NO_STD_WSTREAMBUF)
	SerializeTest<json_oarchive,   json_iarchive,   std::wstringstream>(v);
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

TYPED_TEST(MatrixSerializeTest, SerializeTest)
{
	using T = TypeParam;
	MatrixSerializeTestSub<T, 1, 1>();
	MatrixSerializeTestSub<T, 1, 2>();
	MatrixSerializeTestSub<T, 1, 3>();
	MatrixSerializeTestSub<T, 1, 4>();
	MatrixSerializeTestSub<T, 2, 1>();
	MatrixSerializeTestSub<T, 2, 2>();
	MatrixSerializeTestSub<T, 2, 3>();
	MatrixSerializeTestSub<T, 2, 4>();
	MatrixSerializeTestSub<T, 3, 1>();
	MatrixSerializeTestSub<T, 3, 2>();
	MatrixSerializeTestSub<T, 3, 3>();
	MatrixSerializeTestSub<T, 3, 4>();
	MatrixSerializeTestSub<T, 4, 1>();
	MatrixSerializeTestSub<T, 4, 2>();
	MatrixSerializeTestSub<T, 4, 3>();
	MatrixSerializeTestSub<T, 4, 4>();
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
