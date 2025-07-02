/**
 *	@file	ratio_less.hpp
 *
 *	@brief	ratio_less の定義
 */

#ifndef HAMON_RATIO_RATIO_LESS_HPP
#define HAMON_RATIO_RATIO_LESS_HPP

#include <hamon/ratio/config.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_USE_STD_RATIO)

#include <ratio>

namespace hamon
{

using std::ratio_less;

}	// namespace hamon

#else

#include <hamon/cstdint/intmax_t.hpp>
#include <hamon/cstdint/uintmax_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

// 21.4.5 Comparison of ratios[ratio.comparison]

namespace detail
{

template <hamon::uintmax_t Upper, hamon::uintmax_t Lower>
struct big_uint
{
	static constexpr hamon::uintmax_t upper = Upper;
	static constexpr hamon::uintmax_t lower = Lower;
};

template <typename Lhs, typename Rhs>
struct big_uint_less
{
	static constexpr bool value = (Lhs::upper != Rhs::upper) ?
		(Lhs::upper < Rhs::upper) :
		(Lhs::lower < Rhs::lower);
};

template <hamon::uintmax_t lhs, hamon::uintmax_t rhs>
struct big_mul
{
private:
	static unsigned int const shift = sizeof(hamon::uintmax_t) * 4;	// bitsof(uintmax_t) / 2
	static hamon::uintmax_t const mask = (1ULL << shift) - 1;

	static hamon::uintmax_t const lhs_lo = lhs & mask;
	static hamon::uintmax_t const lhs_hi = lhs >> shift;
	static hamon::uintmax_t const rhs_lo = rhs & mask;
	static hamon::uintmax_t const rhs_hi = rhs >> shift;

	static hamon::uintmax_t const temp1     = lhs_lo * rhs_lo;
	static hamon::uintmax_t const low_lower = temp1 & mask;
	static hamon::uintmax_t const low_upper = temp1 >> shift;

	static hamon::uintmax_t const temp2     = lhs_lo * rhs_hi + low_upper;
	static hamon::uintmax_t const mid_lower = temp2 & mask;
	static hamon::uintmax_t const mid_upper = temp2 >> shift;

	static hamon::uintmax_t const temp3  = lhs_hi * rhs_lo + mid_lower;
	static hamon::uintmax_t const carry = temp3 >> shift;

	static hamon::uintmax_t const upper = lhs_hi * rhs_hi + mid_upper + carry;
	static hamon::uintmax_t const lower = (temp3 << shift) + low_lower;

public:
	using type = big_uint<upper, lower>;
};

template <typename R1, typename R2, bool = (R1::num < 0), bool = (R2::num < 0)>
struct ratio_less_impl
{
	static constexpr bool value = (R1::num < R2::num);
};

// R1::num >= 0 && R2::num >= 0
template <typename R1, typename R2>
struct ratio_less_impl<R1, R2, false, false>
{
private:
	using t1 = typename big_mul<static_cast<hamon::uintmax_t>(R1::num), static_cast<hamon::uintmax_t>(R2::den)>::type;
	using t2 = typename big_mul<static_cast<hamon::uintmax_t>(R2::num), static_cast<hamon::uintmax_t>(R1::den)>::type;
public:
	static constexpr bool value = big_uint_less<t1, t2>::value;
};

// R1::num < 0 && R2::num < 0
template <typename R1, typename R2>
struct ratio_less_impl<R1, R2, true, true>
{
private:
	using t1 = typename big_mul<static_cast<hamon::uintmax_t>(-R2::num), static_cast<hamon::uintmax_t>(R1::den)>::type;
	using t2 = typename big_mul<static_cast<hamon::uintmax_t>(-R1::num), static_cast<hamon::uintmax_t>(R2::den)>::type;
public:
	static constexpr bool value = big_uint_less<t1, t2>::value;
};

}	// namespace detail

template <typename R1, typename R2>
struct ratio_less
	: public hamon::bool_constant<
		hamon::detail::ratio_less_impl<R1, R2>::value>
{};

}	// namespace hamon

#endif

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

namespace hamon
{

template <typename R1, typename R2>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool ratio_less_v = hamon::ratio_less<R1, R2>::value;

}	// namespace hamon

#endif

#endif // HAMON_RATIO_RATIO_LESS_HPP
