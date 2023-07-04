/**
 *	@file	serialize_test.hpp
 *
 *	@brief	
 */

#ifndef UNIT_TEST_COMMON_SERIALIZE_TEST_HPP
#define UNIT_TEST_COMMON_SERIALIZE_TEST_HPP

#include <hamon/serialization/nvp.hpp>
#include <hamon/serialization/archives/binary_iarchive.hpp>
#include <hamon/serialization/archives/binary_oarchive.hpp>
#include <hamon/serialization/archives/json_iarchive.hpp>
#include <hamon/serialization/archives/json_oarchive.hpp>
#include <hamon/serialization/archives/text_iarchive.hpp>
#include <hamon/serialization/archives/text_oarchive.hpp>
#include <hamon/serialization/archives/xml_iarchive.hpp>
#include <hamon/serialization/archives/xml_oarchive.hpp>

namespace
{

template <typename OArchive, typename IArchive, typename Stream, typename T>
void SerializeTest(T const& value)
{
	Stream s;
	{
		OArchive oa(s);
		oa << HAMON_SERIALIZATION_NVP(value);
	}
	{
		T tmp;
		IArchive ia(s);
		ia >> HAMON_SERIALIZATION_NVP(tmp);

		EXPECT_EQ(value, tmp);
	}
}

}	// namespace

#endif // UNIT_TEST_COMMON_SERIALIZE_TEST_HPP
