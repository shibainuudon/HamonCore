/**
 *	@file	unit_test_qvm_quaternion_serialize.cpp
 *
 *	@brief	シリアライズのテスト
 */

#include <hamon/qvm/quaternion.hpp>
#include <gtest/gtest.h>
#include "serialize_test.hpp"
#include "quaternion_test.hpp"

namespace hamon_qvm_test
{

namespace quaternion_test
{

using QuaternionSerializeTestTypes = ::testing::Types<
	int
	, float
	, double
#if !defined(__EMSCRIPTEN__)
	, long double
#endif
>;

template <typename T>
class QuaternionSerializeTest : public ::testing::Test {};

TYPED_TEST_SUITE(QuaternionSerializeTest, QuaternionSerializeTestTypes);

TYPED_TEST(QuaternionSerializeTest, SerializeTest)
{
	using namespace hamon::serialization;
	using T = TypeParam;
	using quaternion = hamon::qvm::quaternion<T>;

	quaternion const q = make_random_quaternion<T>();

	SerializeTest<json_oarchive,   json_iarchive,   std::stringstream>(q);
	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(q);
	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(q);
	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(q);

#if !defined(HAMON_NO_STD_WSTREAMBUF)
	SerializeTest<json_oarchive,   json_iarchive,   std::wstringstream>(q);
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(q);
	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(q);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(q);
#endif
}

}	// namespace quaternion_test

}	// namespace hamon_qvm_test
