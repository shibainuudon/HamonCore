/**
 *	@file	unit_test_qvm_vector_serialize.cpp
 *
 *	@brief	シリアライズのテスト
 */

#include <hamon/qvm/vector.hpp>
#include <gtest/gtest.h>
#include "serialize_test.hpp"
#include "vector_test.hpp"

namespace hamon_qvm_test
{

namespace vector_test
{

template <typename T, std::size_t N>
void VectorSerializeTest()
{
	using namespace hamon::serialization;
	using vector_type = hamon::qvm::vector<T, N>;

	vector_type const v = make_random_vector<T, N>();

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

TYPED_TEST(VectorTest, SerializeTest)
{
	using T = TypeParam;
	VectorSerializeTest<T, 0>();
	VectorSerializeTest<T, 1>();
	VectorSerializeTest<T, 2>();
	VectorSerializeTest<T, 3>();
	VectorSerializeTest<T, 4>();
}

}	// namespace vector_test

}	// namespace hamon_qvm_test
