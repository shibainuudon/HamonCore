/**
 *	@file	unit_test_qvm_matrix_serialize.cpp
 *
 *	@brief	シリアライズのテスト
 */

#include <hamon/qvm/matrix.hpp>
#include <gtest/gtest.h>
#include "serialize_test.hpp"
#include "matrix_test.hpp"

namespace hamon_qvm_test
{

namespace matrix_test
{

template <typename T, std::size_t N, std::size_t M>
void MatrixSerializeTest()
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

TYPED_TEST(MatrixTest, SerializeTest)
{
	using T = TypeParam;
	MatrixSerializeTest<T, 1, 1>();
	MatrixSerializeTest<T, 1, 2>();
	MatrixSerializeTest<T, 1, 3>();
	MatrixSerializeTest<T, 1, 4>();
	MatrixSerializeTest<T, 2, 1>();
	MatrixSerializeTest<T, 2, 2>();
	MatrixSerializeTest<T, 2, 3>();
	MatrixSerializeTest<T, 2, 4>();
	MatrixSerializeTest<T, 3, 1>();
	MatrixSerializeTest<T, 3, 2>();
	MatrixSerializeTest<T, 3, 3>();
	MatrixSerializeTest<T, 3, 4>();
	MatrixSerializeTest<T, 4, 1>();
	MatrixSerializeTest<T, 4, 2>();
	MatrixSerializeTest<T, 4, 3>();
	MatrixSerializeTest<T, 4, 4>();
}

}	// namespace matrix_test

}	// namespace hamon_qvm_test
