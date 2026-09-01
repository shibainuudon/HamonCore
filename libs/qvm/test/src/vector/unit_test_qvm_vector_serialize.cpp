/**
 *	@file	unit_test_qvm_vector_serialize.cpp
 *
 *	@brief	シリアライズのテスト
 */

#include <hamon/qvm/vector/vector.hpp>
#include <hamon/qvm/vector/operators.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/sstream/stringstream.hpp>
#include <hamon/sstream/wstringstream.hpp>
#include <gtest/gtest.h>
#include "serialize_test.hpp"
#include "vector_test.hpp"

namespace hamon_qvm_test
{

namespace vector_test
{

using VectorSerializeTestTypes = ::testing::Types<
	int
	, float
	, double
#if !defined(__EMSCRIPTEN__)
	, long double
#endif
>;

template <typename T>
class VectorSerializeTest : public ::testing::Test {};

TYPED_TEST_SUITE(VectorSerializeTest, VectorSerializeTestTypes);

template <typename T, hamon::size_t N>
void VectorSerializeTestSub()
{
	using namespace hamon::serialization;
	using vector_type = hamon::qvm::vector<T, N>;

	vector_type const v = make_random_vector<T, N>();

	SerializeTest<json_oarchive,   json_iarchive,   hamon::stringstream>(v);
	SerializeTest<text_oarchive,   text_iarchive,   hamon::stringstream>(v);
	SerializeTest<xml_oarchive,    xml_iarchive,    hamon::stringstream>(v);
	SerializeTest<binary_oarchive, binary_iarchive, hamon::stringstream>(v);

#if !defined(HAMON_NO_STD_WSTREAMBUF)
	SerializeTest<json_oarchive,   json_iarchive,   hamon::wstringstream>(v);
	SerializeTest<text_oarchive,   text_iarchive,   hamon::wstringstream>(v);
	SerializeTest<xml_oarchive,    xml_iarchive,    hamon::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, hamon::wstringstream>(v);
#endif
}

TYPED_TEST(VectorSerializeTest, SerializeTest)
{
	using T = TypeParam;
	VectorSerializeTestSub<T, 0>();
	VectorSerializeTestSub<T, 1>();
	VectorSerializeTestSub<T, 2>();
	VectorSerializeTestSub<T, 3>();
	VectorSerializeTestSub<T, 4>();
}

}	// namespace vector_test

}	// namespace hamon_qvm_test
