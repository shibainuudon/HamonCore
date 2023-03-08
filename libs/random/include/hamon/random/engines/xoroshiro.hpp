/**
 *	@file	xoroshiro.hpp
 *
 *	@brief	xoroshiro の定義
 */

#ifndef HAMON_RANDOM_ENGINES_XOROSHIRO_HPP
#define HAMON_RANDOM_ENGINES_XOROSHIRO_HPP

#include <hamon/random/engines/detail/xorshift_base.hpp>
#include <hamon/bit/rotl.hpp>
#include <hamon/cstdint/uint32_t.hpp>
#include <hamon/cstdint/uint64_t.hpp>

namespace hamon
{

/**
 *	@brief	xoroshiro128** (XOR/rotate/shift/rotate)
 */
class xoroshiro128starstar : public xorshift_base<hamon::uint64_t, 2, xoroshiro128starstar>
{
	using base_type = xorshift_base<hamon::uint64_t, 2, xoroshiro128starstar>;
public:
	// 継承コンストラクタ
	using base_type::base_type;

	result_type operator()()
	{
		result_type const A = 24;
		result_type const B = 16;
		result_type const C = 37;
		result_type const S = 5;
		result_type const R = 7;
		result_type const T = 9;

		auto const s0 = m_state[0];
		auto       s1 = m_state[1];
		auto const result = hamon::rotl(s0 * S, R) * T;
		s1 ^= s0;
		m_state[0] = hamon::rotl(s0, A) ^ s1 ^ (s1 << B);
		m_state[1] = hamon::rotl(s1, C);
		return result;
	}
};

/**
 *	@brief	xoroshiro128*
 */
class xoroshiro128star : public xorshift_base<hamon::uint64_t, 2, xoroshiro128star>
{
	using base_type = xorshift_base<hamon::uint64_t, 2, xoroshiro128star>;
public:
	// 継承コンストラクタ
	using base_type::base_type;

	result_type operator()()
	{
		result_type const A = 24;
		result_type const B = 16;
		result_type const C = 37;
		result_type const S = 0x9e3779b97f4a7c13;

		auto const s0 = m_state[0];
		auto       s1 = m_state[1];
		auto const result = s0 * S;
		s1 ^= s0;
		m_state[0] = hamon::rotl(s0, A) ^ s1 ^ (s1 << B);
		m_state[1] = hamon::rotl(s1, C);
		return result;
	}
};

/**
 *	@brief	xoroshiro128+
 */
class xoroshiro128plus : public xorshift_base<hamon::uint64_t, 2, xoroshiro128plus>
{
	using base_type = xorshift_base<hamon::uint64_t, 2, xoroshiro128plus>;
public:
	// 継承コンストラクタ
	using base_type::base_type;

	result_type operator()()
	{
		result_type const A = 24;
		result_type const B = 16;
		result_type const C = 37;

		auto const s0 = m_state[0];
		auto       s1 = m_state[1];
		auto const result = s0 + s1;
		s1 ^= s0;
		m_state[0] = hamon::rotl(s0, A) ^ s1 ^ (s1 << B);
		m_state[1] = hamon::rotl(s1, C);
		return result;
	}
};

/**
 *	@brief	xoroshiro64**
 */
class xoroshiro64starstar : public xorshift_base<hamon::uint32_t, 2, xoroshiro64starstar>
{
	using base_type = xorshift_base<hamon::uint32_t, 2, xoroshiro64starstar>;
public:
	// 継承コンストラクタ
	using base_type::base_type;

	result_type operator()()
	{
		result_type const A = 26;
		result_type const B =  9;
		result_type const C = 13;
		result_type const S = 0x9E3779BB;
		result_type const R = 5;
		result_type const T = 5;

		auto const s0 = m_state[0];
		auto       s1 = m_state[1];
		auto const result = hamon::rotl(s0 * S, R) * T;
		s1 ^= s0;
		m_state[0] = hamon::rotl(s0, A) ^ s1 ^ (s1 << B);
		m_state[1] = hamon::rotl(s1, C);
		return result;
	}
};

/**
 *	@brief	xoroshiro64*
 */
class xoroshiro64star : public xorshift_base<hamon::uint32_t, 2, xoroshiro64star>
{
	using base_type = xorshift_base<hamon::uint32_t, 2, xoroshiro64star>;
public:
	// 継承コンストラクタ
	using base_type::base_type;

	result_type operator()()
	{
		result_type const A = 26;
		result_type const B =  9;
		result_type const C = 13;
		result_type const S = 0x9E3779BB;

		auto const s0 = m_state[0];
		auto       s1 = m_state[1];
		auto const result = s0 * S;
		s1 ^= s0;
		m_state[0] = hamon::rotl(s0, A) ^ s1 ^ (s1 << B);
		m_state[1] = hamon::rotl(s1, C);
		return result;
	}
};

/**
 *	@brief	xoroshiro1024+
 */
class xoroshiro1024plus : public xorshift_base<hamon::uint64_t, 16, xoroshiro1024plus>
{
	using base_type = xorshift_base<hamon::uint64_t, 16, xoroshiro1024plus>;
public:
	// 継承コンストラクタ
	using base_type::base_type;

	result_type operator()()
	{
		result_type const A = 25;
		result_type const B = 27;
		result_type const C = 36;

		auto const p = ((m_p + 1) & 15);
		auto const q = m_p;
		auto const s0 = m_state[p];
		auto       s1 = m_state[q];
		auto const result = s0 + s1;
		s1 ^= s0;
		m_state[q] = hamon::rotl(s0, A) ^ s1 ^ (s1 << B);
		m_state[p] = hamon::rotl(s1, C);
		m_p = p;
		return result;
	}

private:
	int		m_p = 0;
};

/**
 *	@brief	xoroshiro1024*
 */
class xoroshiro1024star : public xorshift_base<hamon::uint64_t, 16, xoroshiro1024star>
{
	using base_type = xorshift_base<hamon::uint64_t, 16, xoroshiro1024star>;
public:
	// 継承コンストラクタ
	using base_type::base_type;

	result_type operator()()
	{
		result_type const A = 25;
		result_type const B = 27;
		result_type const C = 36;
		result_type const S = 0x9e3779b97f4a7c13;

		auto const p = ((m_p + 1) & 15);
		auto const q = m_p;
		auto const s0 = m_state[p];
		auto       s1 = m_state[q];
		auto const result = s0 * S;
		s1 ^= s0;
		m_state[q] = hamon::rotl(s0, A) ^ s1 ^ (s1 << B);
		m_state[p] = hamon::rotl(s1, C);
		m_p = p;
		return result;
	}

private:
	int		m_p = 0;
};

/**
 *	@brief	xoroshiro1024**
 */
class xoroshiro1024starstar : public xorshift_base<hamon::uint64_t, 16, xoroshiro1024starstar>
{
	using base_type = xorshift_base<hamon::uint64_t, 16, xoroshiro1024starstar>;
public:
	// 継承コンストラクタ
	using base_type::base_type;

	result_type operator()()
	{
		result_type const A = 25;
		result_type const B = 27;
		result_type const C = 36;
		result_type const S = 5;
		result_type const R = 7;
		result_type const T = 9;

		auto const p = ((m_p + 1) & 15);
		auto const q = m_p;
		auto const s0 = m_state[p];
		auto       s1 = m_state[q];
		auto const result = hamon::rotl(s0 * S, R) * T;
		s1 ^= s0;
		m_state[q] = hamon::rotl(s0, A) ^ s1 ^ (s1 << B);
		m_state[p] = hamon::rotl(s1, C);
		m_p = p;
		return result;
	}

private:
	int		m_p = 0;
};

}	// namespace hamon

#endif // HAMON_RANDOM_ENGINES_XOROSHIRO_HPP
