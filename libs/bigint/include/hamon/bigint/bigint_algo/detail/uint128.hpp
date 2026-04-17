/**
 *	@file	uint128.hpp
 *
 *	@brief	uint128 の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_DETAIL_UINT128_HPP
#define HAMON_BIGINT_BIGINT_ALGO_DETAIL_UINT128_HPP

#include <hamon/bit/countl_zero.hpp>
#include <hamon/bit/shl.hpp>
#include <hamon/bit/shr.hpp>
#include <hamon/cstddef.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace bigint_algo
{
namespace detail
{

struct uint128
{
private:
	hamon::uint64_t m_word[2];

public:
	HAMON_CXX11_CONSTEXPR
	uint128() HAMON_NOEXCEPT
		: m_word{}
	{}

	HAMON_CXX11_CONSTEXPR
	uint128(hamon::uint64_t v) HAMON_NOEXCEPT
		: m_word{v}
	{}

	HAMON_CXX11_CONSTEXPR
	uint128(hamon::uint64_t low, hamon::uint64_t high) HAMON_NOEXCEPT
		: m_word{low, high}
	{}

	HAMON_CXX11_CONSTEXPR
	uint128(int v) HAMON_NOEXCEPT
		: m_word{static_cast<hamon::uint64_t>(v), (v < 0 ? ~0ULL : 0ULL)}
	{}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	explicit operator hamon::uint64_t() const HAMON_NOEXCEPT
	{
        return m_word[0];
    }

private:
	static HAMON_CXX14_CONSTEXPR void
	knuth_4_3_1_d(
		hamon::uint32_t* u, hamon::size_t u_size,
		hamon::uint32_t const* v, hamon::size_t v_size,
		hamon::uint32_t* q) HAMON_NOEXCEPT
	{
		// Pre: u + [0, u_size), v + [0, v_size), and q + [0, u_size - v_size) are all valid ranges
		// constexpr auto int_max = static_cast<hamon::size_t>(INT_MAX);
		// HAMON_ASSERT(v_size <= int_max);
		// HAMON_ASSERT(u_size <= int_max);
		// HAMON_ASSERT(u_size > v_size);
		const int n = static_cast<int>(v_size);
		const int m = static_cast<int>(u_size - v_size - 1);
		// HAMON_ASSERT(v[n - 1] >> 31 != 0); // Arguments are already normalized

		for (int j = m; j >= 0; --j)
		{
			const auto two_digits = (static_cast<hamon::uint64_t>(u[j + n]) << 32) | u[j + n - 1];
			auto qhat = two_digits / v[n - 1];
			auto rhat = two_digits % v[n - 1];

			while ((qhat >> 32) != 0 ||
				static_cast<hamon::uint32_t>(qhat) * static_cast<hamon::uint64_t>(v[n - 2]) > ((rhat << 32) | u[j + n - 2]))
			{
				--qhat;
				rhat += v[n - 1];
				if ((rhat >> 32) != 0)
				{
					break;
				}
			}

			hamon::int64_t k = 0;
			hamon::int64_t t = 0;
			for (int i = 0; i < n; ++i)
			{
				const auto prod = static_cast<hamon::uint32_t>(qhat) * static_cast<hamon::uint64_t>(v[i]);
				t = u[i + j] - k - static_cast<hamon::uint32_t>(prod);
				u[i + j] = static_cast<hamon::uint32_t>(t);
				k = static_cast<hamon::int64_t>(prod >> 32) - (t >> 32);
			}
			t = u[j + n] - k;
			u[j + n] = static_cast<hamon::uint32_t>(t);

			q[j] = static_cast<hamon::uint32_t>(qhat);
			if (t < 0)
			{
				--q[j];
				k = 0;
				for (int i = 0; i < n; ++i)
				{
					t = u[i + j] + k + v[i];
					u[i + j] = static_cast<hamon::uint32_t>(t);
					k = t >> 32;
				}
				u[j + n] += static_cast<hamon::uint32_t>(k);
			}
		}

		// quotient is in q, normalized remainder is in u
	}

	static HAMON_CXX14_CONSTEXPR hamon::uint64_t
	udiv128(hamon::uint64_t high, hamon::uint64_t low, hamon::uint64_t divisor, hamon::uint64_t& remainder)
	{
		// HAMON_ASSERT(high < divisor);

#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED) && defined(HAS_128_DIV_INTRINSICS)
		if (!hamon::is_constant_evaluated())
		{
			return _udiv128(high, low, divisor, &remainder);
		}
#endif

		const auto d = hamon::countl_zero(static_cast<hamon::uint32_t>(divisor >> 32));
		if (d >= 32)
		{
			// divisor < 2^32
			auto rem = (high << 32) | (low >> 32);
			auto const div = static_cast<hamon::uint32_t>(divisor);
			auto result = rem / div;
			rem = ((rem % div) << 32) | static_cast<hamon::uint32_t>(low);
			result = (result << 32) | (rem / div);
			remainder = rem % div;
			return result;
		}

		hamon::uint32_t u[5] =
		{
			static_cast<hamon::uint32_t>(low << d),
			static_cast<hamon::uint32_t>(low >> (32 - d)),
			static_cast<hamon::uint32_t>(high << d),
			static_cast<hamon::uint32_t>(high >> (32 - d)),
			0,
		};
		if (d != 0)
		{
			u[2] |= static_cast<hamon::uint32_t>(low >> (64 - d));
			u[4] |= static_cast<hamon::uint32_t>(high >> (64 - d));
		}

		hamon::uint32_t v[2] =
		{
			static_cast<hamon::uint32_t>(divisor << d),
			static_cast<hamon::uint32_t>(divisor >> (32 - d)),
		};
		hamon::uint32_t q[3] = {};

		knuth_4_3_1_d(u, 5, v, 2, q);
		// HAMON_ASSERT(u[4] == 0);
		// HAMON_ASSERT(u[3] == 0);
		// HAMON_ASSERT(u[2] == 0);
		remainder = (static_cast<hamon::uint64_t>(u[1]) << (32 - d)) | (u[0] >> d);

		// HAMON_ASSERT(q[2] == 0);
		return (static_cast<hamon::uint64_t>(q[1]) << 32) | q[0];
	}

public:
	HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR uint128
	operator/(uint128 const& lhs, hamon::uint64_t rhs) HAMON_NOEXCEPT
	{
		hamon::uint64_t rem{};
		return
		{
			udiv128(lhs.m_word[1] % rhs, lhs.m_word[0], rhs, rem),
			lhs.m_word[1] / rhs
		};
	}

	HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR uint128
	operator<<(uint128 const& lhs, unsigned int rhs) HAMON_NOEXCEPT
	{
		auto const s = static_cast<int>(rhs);
		return
		{
			hamon::shl(lhs.m_word[0], s),
			hamon::shl(lhs.m_word[1], s) | hamon::shr(lhs.m_word[0], 64 - s)
		};
	}

	HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR uint128
	operator>>(uint128 const& lhs, unsigned int rhs) HAMON_NOEXCEPT
	{
		auto const s = static_cast<int>(rhs);
		return
		{
			hamon::shr(lhs.m_word[0], s) | hamon::shl(lhs.m_word[1], 64 - s),
			hamon::shr(lhs.m_word[1], s)
		};
	}

	HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR uint128
	operator|(uint128 const& lhs, uint128 const& rhs) HAMON_NOEXCEPT
	{
		return
		{
			lhs.m_word[0] | rhs.m_word[0],
			lhs.m_word[1] | rhs.m_word[1]
		};
	}

	HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR bool
	operator<(uint128 const& lhs, uint128 const& rhs) HAMON_NOEXCEPT
	{
		if (lhs.m_word[1] < rhs.m_word[1])
		{
			return true;
		}

		if (lhs.m_word[1] > rhs.m_word[1])
		{
			return false;
		}

		return lhs.m_word[0] < rhs.m_word[0];
	}
};

}	// namespace detail
}	// namespace bigint_algo

// is_integralの特殊化
template <> struct is_integral<bigint_algo::detail::uint128> : public hamon::true_type{};
template <> struct is_integral<bigint_algo::detail::uint128 const> : public hamon::true_type{};
template <> struct is_integral<bigint_algo::detail::uint128 volatile> : public hamon::true_type{};
template <> struct is_integral<bigint_algo::detail::uint128 const volatile> : public hamon::true_type{};

}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_DETAIL_UINT128_HPP
