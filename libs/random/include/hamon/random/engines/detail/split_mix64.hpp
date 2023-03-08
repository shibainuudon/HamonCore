﻿/**
 *	@file	split_mix64.hpp
 *
 *	@brief	split_mix64 の定義
 */

#ifndef HAMON_RANDOM_ENGINES_DETAIL_SPLIT_MIX64_HPP
#define HAMON_RANDOM_ENGINES_DETAIL_SPLIT_MIX64_HPP

#include <hamon/cstdint/uint64_t.hpp>

namespace hamon
{

class split_mix64
{
public:
	using result_type = hamon::uint64_t;

	explicit split_mix64(result_type sd)
		: m_state(sd)
	{}

	result_type operator()()
	{
		result_type z = (m_state += 0x9e3779b97f4a7c15);
		z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
		z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
		return z ^ (z >> 31);
	}

private:
	result_type m_state;
};

}	// namespace hamon

#endif // HAMON_RANDOM_ENGINES_DETAIL_SPLIT_MIX64_HPP
