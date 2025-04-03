/**
 *	@file	unordered_multiset_test_helper.hpp
 *
 *	@brief
 */

#ifndef HAMON_UNORDERED_MULTISET_TEST_HELPER_HPP
#define HAMON_UNORDERED_MULTISET_TEST_HELPER_HPP

#include <hamon/functional.hpp>

namespace hamon_unordered_multiset_test
{

struct TransparentKey
{
	int value;

	explicit constexpr TransparentKey(int v) : value(v) {}

	friend constexpr bool operator==(TransparentKey const& lhs, TransparentKey const& rhs)
	{
		return lhs.value == rhs.value;
	}

	friend constexpr bool operator==(TransparentKey const& lhs, int rhs)
	{
		return lhs.value == rhs;
	}

	friend constexpr bool operator==(int lhs, TransparentKey const& rhs)
	{
		return lhs == rhs.value;
	}

	constexpr hamon::size_t hash() const { return hamon::hash<int>{}(value); }
};

}	// namespace hamon_unordered_multiset_test

#endif // HAMON_UNORDERED_MULTISET_TEST_HELPER_HPP
