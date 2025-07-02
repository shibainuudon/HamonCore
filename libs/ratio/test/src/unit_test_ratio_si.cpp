/**
 *	@file	unit_test_ratio_si.cpp
 *
 *	@brief	SI typedefs のテスト
 */

#include <hamon/ratio.hpp>
#include <gtest/gtest.h>

GTEST_TEST(RatioTest, SITest)
{
#if defined(HAMON_HAS_RATIO_QUECTO)
	{
		using r = hamon::quecto;
		static_assert(r::num == 1, "");
		static_assert(r::den == 1000000000000000000000000000000, "");
	}
#endif
#if defined(HAMON_HAS_RATIO_RONTO)
	{
		using r = hamon::ronto;
		static_assert(r::num == 1, "");
		static_assert(r::den == 1000000000000000000000000000, "");
	}
#endif
#if defined(HAMON_HAS_RATIO_YOCTO)
	{
		using r = hamon::yocto;
		static_assert(r::num == 1, "");
		static_assert(r::den == 1000000000000000000000000, "");
	}
#endif
#if defined(HAMON_HAS_RATIO_ZEPTO)
	{
		using r = hamon::zepto;
		static_assert(r::num == 1, "");
		static_assert(r::den == 1000000000000000000000, "");
	}
#endif
	{
		using r = hamon::atto;
		static_assert(r::num == 1, "");
		static_assert(r::den == 1000000000000000000, "");
	}
	{
		using r = hamon::femto;
		static_assert(r::num == 1, "");
		static_assert(r::den == 1000000000000000, "");
	}
	{
		using r = hamon::pico;
		static_assert(r::num == 1, "");
		static_assert(r::den == 1000000000000, "");
	}
	{
		using r = hamon::nano;
		static_assert(r::num == 1, "");
		static_assert(r::den == 1000000000, "");
	}
	{
		using r = hamon::micro;
		static_assert(r::num == 1, "");
		static_assert(r::den == 1000000, "");
	}
	{
		using r = hamon::milli;
		static_assert(r::num == 1, "");
		static_assert(r::den == 1000, "");
	}
	{
		using r = hamon::centi;
		static_assert(r::num == 1, "");
		static_assert(r::den == 100, "");
	}
	{
		using r = hamon::deci;
		static_assert(r::num == 1, "");
		static_assert(r::den == 10, "");
	}
	{
		using r = hamon::deca;
		static_assert(r::num == 10, "");
		static_assert(r::den == 1, "");
	}
	{
		using r = hamon::hecto;
		static_assert(r::num == 100, "");
		static_assert(r::den == 1, "");
	}
	{
		using r = hamon::kilo;
		static_assert(r::num == 1000, "");
		static_assert(r::den == 1, "");
	}
	{
		using r = hamon::mega;
		static_assert(r::num == 1000000, "");
		static_assert(r::den == 1, "");
	}
	{
		using r = hamon::giga;
		static_assert(r::num == 1000000000, "");
		static_assert(r::den == 1, "");
	}
	{
		using r = hamon::tera;
		static_assert(r::num == 1000000000000, "");
		static_assert(r::den == 1, "");
	}
	{
		using r = hamon::peta;
		static_assert(r::num == 1000000000000000, "");
		static_assert(r::den == 1, "");
	}
	{
		using r = hamon::exa;
		static_assert(r::num == 1000000000000000000, "");
		static_assert(r::den == 1, "");
	}
#if defined(HAMON_HAS_RATIO_ZETTA)
	{
		using r = hamon::zetta;
		static_assert(r::num == 1000000000000000000000, "");
		static_assert(r::den == 1, "");
	}
#endif
#if defined(HAMON_HAS_RATIO_YOTTA)
	{
		using r = hamon::yotta;
		static_assert(r::num == 1000000000000000000000000, "");
		static_assert(r::den == 1, "");
	}
#endif
#if defined(HAMON_HAS_RATIO_RONNA)
	{
		using r = hamon::ronna;
		static_assert(r::num == 1000000000000000000000000000, "");
		static_assert(r::den == 1, "");
	}
#endif
#if defined(HAMON_HAS_RATIO_QUETTA)
	{
		using r = hamon::quetta;
		static_assert(r::num == 1000000000000000000000000000000, "");
		static_assert(r::den == 1, "");
	}
#endif
}
