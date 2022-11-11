/**
 *	@file	unit_test_units_units.cpp
 *
 *	@brief	units のテスト
 */

#include <hamon/units.hpp>
#include <hamon/numbers.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "constexpr_test.hpp"

namespace units_units_test
{

template <typename T>
class UnitsTest : public ::testing::Test {};

using UnitsTestTypes = ::testing::Types<float, double, long double>;

TYPED_TEST_SUITE(UnitsTest, UnitsTestTypes);

TYPED_TEST(UnitsTest, AbsorbedDoseTest)
{
	using joules    = hamon::units::joules<TypeParam>;
	using kilograms = hamon::units::kilograms<TypeParam>;
	using grays     = hamon::units::grays<TypeParam>;
	using metres    = hamon::units::metres<TypeParam>;
	using seconds   = hamon::units::seconds<TypeParam>;

	{
		// J/kg
		HAMON_CONSTEXPR_OR_CONST auto Gy = joules(20) / kilograms(2);
		static_assert(std::is_same<decltype(Gy), const grays>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, Gy.value());
	}
	{
		// m^2・s^-2
		HAMON_CONSTEXPR_OR_CONST auto Gy = (metres(3) * metres(4)) / (seconds(2) * seconds(3));
		static_assert(std::is_same<decltype(Gy), const grays>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, Gy.value());
	}
}

TYPED_TEST(UnitsTest, AccelerationTest)
{
	using metres_per_second_squared = hamon::units::metres_per_second_squared<TypeParam>;
	using metres_per_second         = hamon::units::metres_per_second<TypeParam>;
	using seconds                   = hamon::units::seconds<TypeParam>;
	using metres                    = hamon::units::metres<TypeParam>;

	{
		HAMON_CONSTEXPR_OR_CONST auto x = metres_per_second_squared(10) * seconds(2);
		static_assert(std::is_same<decltype(x), const metres_per_second>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, x.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto x = metres_per_second_squared(10) * seconds(2) * seconds(3);
		static_assert(std::is_same<decltype(x), const metres>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(60, x.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto x = metres_per_second(10) / seconds(2);
		static_assert(std::is_same<decltype(x), const metres_per_second_squared>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, x.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto x = metres(60) / seconds(3) / seconds(2);
		static_assert(std::is_same<decltype(x), const metres_per_second_squared>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, x.value());
	}
}

TYPED_TEST(UnitsTest, ActionTest)
{
	using joule_seconds = hamon::units::joule_seconds<TypeParam>;
	using joules        = hamon::units::joules<TypeParam>;
	using seconds       = hamon::units::seconds<TypeParam>;
	using kilograms     = hamon::units::kilograms<TypeParam>;
	using metres        = hamon::units::metres<TypeParam>;

	{
		// J・s
		HAMON_CONSTEXPR_OR_CONST auto js = joules(4) * seconds(5);
		static_assert(std::is_same<decltype(js), const joule_seconds>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, js.value());
	}
	{
		// kg・m^2・s^-1
		HAMON_CONSTEXPR_OR_CONST auto js = kilograms(2) * metres(3) * metres(4) / seconds(6);
		static_assert(std::is_same<decltype(js), const joule_seconds>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, js.value());
	}
}

TYPED_TEST(UnitsTest, AmountTest)
{
	{
		HAMON_CONSTEXPR hamon::units::moles<TypeParam>      mol(2);

		HAMON_CONSTEXPR hamon::units::kilomoles<TypeParam>  kmol(mol);
		HAMON_CONSTEXPR hamon::units::megamoles<TypeParam>  Mmol(mol);

		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.0 / 1000,        (double)kmol.value(), 0.0000000001);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.0 / 1000 / 1000, (double)Mmol.value(), 0.00000000000001);
	}
	{
		HAMON_CONSTEXPR hamon::units::kilomoles<TypeParam>  kmol(3);

		HAMON_CONSTEXPR hamon::units::moles<TypeParam>      mol(kmol);
		HAMON_CONSTEXPR hamon::units::megamoles<TypeParam>  Mmol(kmol);

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 3.0 * 1000,         mol.value());
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.0 / 1000, (double)Mmol.value(), 0.0000000001);
	}
	{
		HAMON_CONSTEXPR hamon::units::megamoles<TypeParam>  Mmol(4);

		HAMON_CONSTEXPR hamon::units::moles<TypeParam>      mol(Mmol);
		HAMON_CONSTEXPR hamon::units::kilomoles<TypeParam>  kmol(Mmol);

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4.0 * 1000 * 1000, mol.value());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4.0 * 1000,        kmol.value());
	}
}

TYPED_TEST(UnitsTest, AngleTest)
{
	HAMON_CONSTEXPR auto p = hamon::numbers::pi_fn<double>();
	HAMON_CONSTEXPR hamon::units::radians<TypeParam> r(1);
	HAMON_CONSTEXPR hamon::units::degrees<TypeParam> d(2);

	HAMON_CONSTEXPR hamon::units::radians<TypeParam> r_1(r);
	HAMON_CONSTEXPR hamon::units::radians<TypeParam> r_2(d);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 1 * 1.0,             r_1.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2 * p / 180, (double)r_2.value(), 0.000000001);

	HAMON_CONSTEXPR hamon::units::degrees<TypeParam> d_1(r);
	HAMON_CONSTEXPR hamon::units::degrees<TypeParam> d_2(d);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1 * 180 / p, (double)d_1.value(), 0.000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 2 * 1.0,             d_2.value());
}

TYPED_TEST(UnitsTest, AngularAccelerationTest)
{
	using radians_per_second_squared = hamon::units::radians_per_second_squared<TypeParam>;
	using radians = hamon::units::radians<TypeParam>;
	using seconds = hamon::units::seconds<TypeParam>;

	{
		// rad・s^-2
		HAMON_CONSTEXPR_OR_CONST auto a = radians(60) / seconds(3) / seconds(4);
		static_assert(std::is_same<decltype(a), const radians_per_second_squared>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, a.value());
	}
}

TYPED_TEST(UnitsTest, AngularMomentumTest)
{
	using newton_metre_seconds = hamon::units::newton_metre_seconds<TypeParam>;
	using newtons              = hamon::units::newtons<TypeParam>;
	using metres               = hamon::units::metres<TypeParam>;
	using seconds              = hamon::units::seconds<TypeParam>;
	using kilograms            = hamon::units::kilograms<TypeParam>;

	{
		// N・m・s
		HAMON_CONSTEXPR_OR_CONST auto a = newtons(3) * metres(4) * seconds(5);
		static_assert(std::is_same<decltype(a), const newton_metre_seconds>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(60, a.value());
	}
	{
		// m^2・kg・s^-1
		HAMON_CONSTEXPR_OR_CONST auto a = metres(3) * metres(4) * kilograms(5) / seconds(6);
		static_assert(std::is_same<decltype(a), const newton_metre_seconds>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, a.value());
	}
}

TYPED_TEST(UnitsTest, AngularVelocityTest)
{
	using radians_per_second = hamon::units::radians_per_second<TypeParam>;
	using radians = hamon::units::radians<TypeParam>;
	using seconds = hamon::units::seconds<TypeParam>;

	{
		// rad・s^-1
		HAMON_CONSTEXPR_OR_CONST auto a = radians(60) / seconds(3);
		static_assert(std::is_same<decltype(a), const radians_per_second>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, a.value());
	}
}

TYPED_TEST(UnitsTest, AreaTest)
{
	using square_metres = hamon::units::square_metres<TypeParam>;
	using metres        = hamon::units::metres<TypeParam>;
	using kilometres    = hamon::units::kilometres<TypeParam>;

	{
		// m・m
		HAMON_CONSTEXPR_OR_CONST auto a = metres(3) * metres(4);
		static_assert(std::is_same<decltype(a), const square_metres>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, a.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST square_metres a = metres(5) * kilometres(6);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(30000, a.value());
	}
}

TYPED_TEST(UnitsTest, CatalyticActivityTest)
{
	using moles   = hamon::units::moles<TypeParam>;
	using seconds = hamon::units::seconds<TypeParam>;
	using katals  = hamon::units::katals<TypeParam>;

	{
		// mol/s
		HAMON_CONSTEXPR_OR_CONST auto kat = moles(20) / seconds(2);
		static_assert(std::is_same<decltype(kat), const katals>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, kat.value());
	}
}

TYPED_TEST(UnitsTest, CurrentTest)
{
	{
		HAMON_CONSTEXPR hamon::units::amperes<TypeParam>      A(2);

		HAMON_CONSTEXPR hamon::units::kiloamperes<TypeParam>  kA(A);
		HAMON_CONSTEXPR hamon::units::megaamperes<TypeParam>  MA(A);

		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.0 / 1000,        (double)kA.value(), 0.0000000001);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.0 / 1000 / 1000, (double)MA.value(), 0.00000000000001);
	}
	{
		HAMON_CONSTEXPR hamon::units::kiloamperes<TypeParam>  kA(3);

		HAMON_CONSTEXPR hamon::units::amperes<TypeParam>      A(kA);
		HAMON_CONSTEXPR hamon::units::megaamperes<TypeParam>  MA(kA);

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 3.0 * 1000,         A.value());
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.0 / 1000, (double)MA.value(), 0.0000000001);
	}
	{
		HAMON_CONSTEXPR hamon::units::megaamperes<TypeParam>  MA(4);

		HAMON_CONSTEXPR hamon::units::amperes<TypeParam>      A(MA);
		HAMON_CONSTEXPR hamon::units::kiloamperes<TypeParam>  kA(MA);

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4.0 * 1000 * 1000, A.value());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4.0 * 1000,        kA.value());
	}
}

TYPED_TEST(UnitsTest, DynamicViscosityTest)
{
	using pascal_seconds = hamon::units::pascal_seconds<TypeParam>;
	using pascals        = hamon::units::pascals<TypeParam>;
	using seconds        = hamon::units::seconds<TypeParam>;
	using kilograms      = hamon::units::kilograms<TypeParam>;
	using metres         = hamon::units::metres<TypeParam>;

	{
		// Pa・s
		HAMON_CONSTEXPR_OR_CONST auto v = pascals(3) * seconds(4);
		static_assert(std::is_same<decltype(v), const pascal_seconds>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, v.value());
	}
	{
		// m^-1・kg・s^-1
		HAMON_CONSTEXPR_OR_CONST auto v = kilograms(60) / metres(2) / seconds(3);
		static_assert(std::is_same<decltype(v), const pascal_seconds>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, v.value());
	}
}

TYPED_TEST(UnitsTest, ElectricChargeTest)
{
	using amperes     = hamon::units::amperes<TypeParam>;
	using kiloamperes = hamon::units::kiloamperes<TypeParam>;
	using seconds     = hamon::units::seconds<TypeParam>;
	using coulomb     = hamon::units::coulomb<TypeParam>;
	using kilocoulomb = hamon::units::kilocoulomb<TypeParam>;

	{
		HAMON_CONSTEXPR_OR_CONST auto v = amperes(3) * seconds(4);
		static_assert(std::is_same<decltype(v), const coulomb>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, v.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto v = kiloamperes(4) * seconds(5);
		static_assert(std::is_same<decltype(v), const kilocoulomb>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, v.value());
	}
}

TYPED_TEST(UnitsTest, ElectricPotentialTest)
{
	using watts        = hamon::units::watts<TypeParam>;
	using kilowatts    = hamon::units::kilowatts<TypeParam>;
	using amperes      = hamon::units::amperes<TypeParam>;
	using milliamperes = hamon::units::milliamperes<TypeParam>;
	using volts        = hamon::units::volts<TypeParam>;
	using kilovolts    = hamon::units::kilovolts<TypeParam>;
	using joules       = hamon::units::joules<TypeParam>;
	using coulombs     = hamon::units::coulombs<TypeParam>;
	using metres       = hamon::units::metres<TypeParam>;
	using kilograms    = hamon::units::kilograms<TypeParam>;
	using seconds      = hamon::units::seconds<TypeParam>;

	{
		HAMON_CONSTEXPR_OR_CONST auto v = watts(20) / amperes(4);
		static_assert(std::is_same<decltype(v), const volts>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, v.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto v = kilowatts(30) / amperes(2);
		static_assert(std::is_same<decltype(v), const kilovolts>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, v.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto v = watts(40) / milliamperes(5);
		static_assert(std::is_same<decltype(v), const kilovolts>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8, v.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto v = joules(60) / coulombs(5);
		static_assert(std::is_same<decltype(v), const volts>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, v.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto v = metres(4) * metres(5) * kilograms(6) / seconds(1) / seconds(2) / seconds(3) / amperes(4);
		static_assert(std::is_same<decltype(v), const volts>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, v.value());
	}
}

TYPED_TEST(UnitsTest, ElectricalCapacitanceTest)
{
	using coulombs  = hamon::units::coulombs<TypeParam>;
	using volts     = hamon::units::volts<TypeParam>;
	using farads    = hamon::units::farads<TypeParam>;
	using joules    = hamon::units::joules<TypeParam>;
	using seconds   = hamon::units::seconds<TypeParam>;
	using amperes   = hamon::units::amperes<TypeParam>;
	using metres    = hamon::units::metres<TypeParam>;
	using kilograms = hamon::units::kilograms<TypeParam>;

	{
		// C/V
		HAMON_CONSTEXPR_OR_CONST auto F = coulombs(20) / volts(4);
		static_assert(std::is_same<decltype(F), const farads>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, F.value());
	}
	{
		// J/V^2
		HAMON_CONSTEXPR_OR_CONST auto F = joules(60) / volts(2) / volts(3);
		static_assert(std::is_same<decltype(F), const farads>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, F.value());
	}
	{
		// C^2/J
		HAMON_CONSTEXPR_OR_CONST auto F = coulombs(20) * coulombs(10) / joules(4);
		static_assert(std::is_same<decltype(F), const farads>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(50, F.value());
	}
	{
		// s^4 A^2 / (m^-2 kg^-1)
		HAMON_CONSTEXPR_OR_CONST auto s  = seconds(2);
		HAMON_CONSTEXPR_OR_CONST auto A  = amperes(3);
		HAMON_CONSTEXPR_OR_CONST auto m  = metres(4);
		HAMON_CONSTEXPR_OR_CONST auto kg = kilograms(3);
		HAMON_CONSTEXPR_OR_CONST auto F  = s * s * s * s * A * A / m / m / kg;
		static_assert(std::is_same<decltype(F), const farads>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, F.value());
	}
}

TYPED_TEST(UnitsTest, ElectricalConductanceTest)
{
	using ohms      = hamon::units::ohms<TypeParam>;
	using siemens   = hamon::units::siemens<TypeParam>;
	using amperes   = hamon::units::amperes<TypeParam>;
	using volts     = hamon::units::volts<TypeParam>;
	using coulombs  = hamon::units::coulombs<TypeParam>;
	using seconds   = hamon::units::seconds<TypeParam>;
	using kilograms = hamon::units::kilograms<TypeParam>;
	using metre     = hamon::units::metre<TypeParam>;

	{
		// Ω^-1
		HAMON_CONSTEXPR_OR_CONST auto S = TypeParam(10) / ohms(2);
		static_assert(std::is_same<decltype(S), const siemens>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, S.value());
	}
	{
		// A V^-1
		HAMON_CONSTEXPR_OR_CONST auto S = amperes(30) / volts(3);
		static_assert(std::is_same<decltype(S), const siemens>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, S.value());
	}
	{
		// C^2 s kg^-1 m^-2
		HAMON_CONSTEXPR_OR_CONST auto C = coulombs(3);
		HAMON_CONSTEXPR_OR_CONST auto s = seconds(6);
		HAMON_CONSTEXPR_OR_CONST auto kg = kilograms(2);
		HAMON_CONSTEXPR_OR_CONST auto m = metre(3);
		HAMON_CONSTEXPR_OR_CONST auto S = C * C * s / (kg * m * m);
		static_assert(std::is_same<decltype(S), const siemens>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, S.value());
	}
}

TYPED_TEST(UnitsTest, ElectricalConductivityTest)
{
	using siemens_per_metre = hamon::units::siemens_per_metre<TypeParam>;
	using siemens           = hamon::units::siemens<TypeParam>;
	using metres            = hamon::units::metres<TypeParam>;
	using kilograms         = hamon::units::kilograms<TypeParam>;
	using seconds           = hamon::units::seconds<TypeParam>;
	using amperes           = hamon::units::amperes<TypeParam>;
	using volts             = hamon::units::volts<TypeParam>;

	{
		// S/m
		HAMON_CONSTEXPR_OR_CONST auto a = siemens(60) / metres(3);
		static_assert(std::is_same<decltype(a), const siemens_per_metre>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, a.value());
	}
	{
		// A・V^-1・m^-1
		HAMON_CONSTEXPR_OR_CONST auto a = amperes(60) / volts(4) / metres(5);
		static_assert(std::is_same<decltype(a), const siemens_per_metre>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, a.value());
	}
	{
		// m^-3・kg^-1・s^3・A^2
		HAMON_CONSTEXPR_OR_CONST auto m = metres(2);
		HAMON_CONSTEXPR_OR_CONST auto kg = kilograms(3);
		HAMON_CONSTEXPR_OR_CONST auto s = seconds(4);
		HAMON_CONSTEXPR_OR_CONST auto A = amperes(6);
		HAMON_CONSTEXPR_OR_CONST auto a = s * s * s * A * A / (m * m * m * kg);
		static_assert(std::is_same<decltype(a), const siemens_per_metre>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(96, a.value());
	}
}

TYPED_TEST(UnitsTest, ElectricalResistanceTest)
{
	using volts     = hamon::units::volts<TypeParam>;
	using ampere    = hamon::units::ampere<TypeParam>;
	using ohms      = hamon::units::ohms<TypeParam>;
	using watts     = hamon::units::watts<TypeParam>;
	using seconds   = hamon::units::seconds<TypeParam>;
	using farads    = hamon::units::farads<TypeParam>;
	using kilograms = hamon::units::kilograms<TypeParam>;
	using metre     = hamon::units::metre<TypeParam>;
	using coulombs  = hamon::units::coulombs<TypeParam>;

	{
		// V/A
		HAMON_CONSTEXPR_OR_CONST auto O = volts(10) / ampere(2);
		static_assert(std::is_same<decltype(O), const ohms>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, O.value());
	}
	{
		// W/A^2
		HAMON_CONSTEXPR_OR_CONST auto O = watts(60) / ampere(2) / ampere(3);
		static_assert(std::is_same<decltype(O), const ohms>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, O.value());
	}
	{
		// V^2/W
		HAMON_CONSTEXPR_OR_CONST auto O = volts(4) * volts(5) / watts(10);
		static_assert(std::is_same<decltype(O), const ohms>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, O.value());
	}
	{
		// s/F
		HAMON_CONSTEXPR_OR_CONST auto O = seconds(30) / farads(5);
		static_assert(std::is_same<decltype(O), const ohms>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, O.value());
	}
	{
		// kg m^2 / s C^2
		HAMON_CONSTEXPR_OR_CONST auto kg = kilograms(6);
		HAMON_CONSTEXPR_OR_CONST auto m = metre(4);
		HAMON_CONSTEXPR_OR_CONST auto s = seconds(3);
		HAMON_CONSTEXPR_OR_CONST auto C = coulombs(2);
		HAMON_CONSTEXPR_OR_CONST auto O = (kg * m * m) / (s * C * C);
		static_assert(std::is_same<decltype(O), const ohms>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8, O.value());
	}
}

TYPED_TEST(UnitsTest, ElectricalResistivityTest)
{
	using ohm_metre = hamon::units::ohm_metre<TypeParam>;
	using ohms      = hamon::units::ohms<TypeParam>;
	using metres    = hamon::units::metres<TypeParam>;
	using kilograms = hamon::units::kilograms<TypeParam>;
	using seconds   = hamon::units::seconds<TypeParam>;
	using amperes   = hamon::units::amperes<TypeParam>;

	{
		// Ω・m
		HAMON_CONSTEXPR_OR_CONST auto v = ohms(3) * metres(4);
		static_assert(std::is_same<decltype(v), const ohm_metre>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, v.value());
	}
	{
		// m^3・kg・s^-3・A^-2
		HAMON_CONSTEXPR_OR_CONST auto m = metres(4);
		HAMON_CONSTEXPR_OR_CONST auto kg = kilograms(3);
		HAMON_CONSTEXPR_OR_CONST auto s = seconds(2);
		HAMON_CONSTEXPR_OR_CONST auto A = amperes(1);
		HAMON_CONSTEXPR_OR_CONST auto v = m * m * m * kg / (s * s * s * A * A);
		static_assert(std::is_same<decltype(v), const ohm_metre>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(24, v.value());
	}
}

TYPED_TEST(UnitsTest, EnergyTest)
{
	using kilograms = hamon::units::kilograms<TypeParam>;
	using metres    = hamon::units::metres<TypeParam>;
	using seconds   = hamon::units::seconds<TypeParam>;
	using newtons   = hamon::units::newtons<TypeParam>;
	using watts     = hamon::units::watts<TypeParam>;
	using joule     = hamon::units::joule<TypeParam>;

	{
		HAMON_CONSTEXPR_OR_CONST auto v = kilograms(120) * metres(1) * metres(2) / seconds(3) / seconds(4);
		static_assert(std::is_same<decltype(v), const joule>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, v.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto v = newtons(5) * metres(6);
		static_assert(std::is_same<decltype(v), const joule>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(30, v.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto v = watts(7) * seconds(8);
		static_assert(std::is_same<decltype(v), const joule>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(56, v.value());
	}
}

TYPED_TEST(UnitsTest, EnergyDensityTest)
{
	using joules_per_cubic_metre = hamon::units::joules_per_cubic_metre<TypeParam>;
	using joules                 = hamon::units::joules<TypeParam>;
	using metres                 = hamon::units::metres<TypeParam>;
	using kilograms              = hamon::units::kilograms<TypeParam>;
	using seconds                = hamon::units::seconds<TypeParam>;

	{
		// J/m^3
		HAMON_CONSTEXPR_OR_CONST auto a = joules(60) / metres(1) / metres(2) / metres(3);
		static_assert(std::is_same<decltype(a), const joules_per_cubic_metre>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, a.value());
	}
	{
		// m^-1・kg・s^-2
		HAMON_CONSTEXPR_OR_CONST auto a = kilograms(60) / (metres(2) * seconds(3) * seconds(5));
		static_assert(std::is_same<decltype(a), const joules_per_cubic_metre>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, a.value());
	}
}

TYPED_TEST(UnitsTest, EquivalentDoseTest)
{
	using joules    = hamon::units::joules<TypeParam>;
	using kilograms = hamon::units::kilograms<TypeParam>;
	using sieverts  = hamon::units::sieverts<TypeParam>;
	using metres    = hamon::units::metres<TypeParam>;
	using seconds   = hamon::units::seconds<TypeParam>;

	{
		// J/kg
		HAMON_CONSTEXPR_OR_CONST auto Sv = joules(20) / kilograms(2);
		static_assert(std::is_same<decltype(Sv), const sieverts>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, Sv.value());
	}
	{
		// m^2・s^-2
		HAMON_CONSTEXPR_OR_CONST auto Sv = (metres(3) * metres(4)) / (seconds(2) * seconds(3));
		static_assert(std::is_same<decltype(Sv), const sieverts>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, Sv.value());
	}
}

TYPED_TEST(UnitsTest, ForceTest)
{
	using kilograms   = hamon::units::kilograms<TypeParam>;
	using grams       = hamon::units::grams<TypeParam>;
	using pounds      = hamon::units::pounds<TypeParam>;
	using metres      = hamon::units::metres<TypeParam>;
	using centimetres = hamon::units::centimetres<TypeParam>;
	using feet        = hamon::units::feet<TypeParam>;
	using seconds     = hamon::units::seconds<TypeParam>;
	using newtons     = hamon::units::newtons<TypeParam>;
	using dynes       = hamon::units::dynes<TypeParam>;
	using poundals    = hamon::units::poundals<TypeParam>;

	{
		HAMON_CONSTEXPR_OR_CONST auto v = kilograms(120) * metres(2) / seconds(3) / seconds(4);
		static_assert(std::is_same<decltype(v), const newtons>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, v.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto v = grams(40) * centimetres(3) / seconds(4) / seconds(5);
		static_assert(std::is_same<decltype(v), const dynes>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(6.0, (double)v.value(), 0.000001);
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto v = pounds(60) * feet(4) / seconds(5) / seconds(6);
		static_assert(std::is_same<decltype(v), const poundals>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8, v.value());
	}
}

TYPED_TEST(UnitsTest, FrequencyTest)
{
	using T = TypeParam;
	using hertz   = hamon::units::hertz<T>;
	using seconds = hamon::units::seconds<T>;

	{
		HAMON_CONSTEXPR_OR_CONST auto v = T(120) / seconds(3);
		static_assert(std::is_same<decltype(v), const hertz>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(40, v.value());
	}
	{
		HAMON_CONSTEXPR hamon::units::hertz<TypeParam>      Hz(1);

		HAMON_CONSTEXPR hamon::units::kilohertz<TypeParam>  kHz(Hz);
		HAMON_CONSTEXPR hamon::units::megahertz<TypeParam>  MHz(Hz);
		HAMON_CONSTEXPR hamon::units::gigahertz<TypeParam>	GHz(Hz);
		HAMON_CONSTEXPR hamon::units::terahertz<TypeParam>  THz(Hz);

		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0 / 1000,          (double)kHz.value(), 0.0000000001);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0 / 1000000,       (double)MHz.value(), 0.00000000000001);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0 / 1000000000,    (double)GHz.value(), 0.0000000000000001);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0 / 1000000000000, (double)THz.value(), 0.0000000000000000001);
	}
	{
		HAMON_CONSTEXPR hamon::units::kilohertz<TypeParam>  kHz(2);

		HAMON_CONSTEXPR hamon::units::hertz<TypeParam>      Hz(kHz);
		HAMON_CONSTEXPR hamon::units::megahertz<TypeParam>  MHz(kHz);
		HAMON_CONSTEXPR hamon::units::gigahertz<TypeParam>	GHz(kHz);
		HAMON_CONSTEXPR hamon::units::terahertz<TypeParam>  THz(kHz);

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (2.0 * 1000,               Hz.value());
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.0 / 1000,       (double)MHz.value(), 0.0000000001);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.0 / 1000000,    (double)GHz.value(), 0.0000000000001);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.0 / 1000000000, (double)THz.value(), 0.0000000000000001);
	}
}

TYPED_TEST(UnitsTest, HeatCapacityTest)
{
	using joules_per_kelvin = hamon::units::joules_per_kelvin<TypeParam>;
	using joules            = hamon::units::joules<TypeParam>;
	using kelvins           = hamon::units::kelvins<TypeParam>;
	using metres            = hamon::units::metres<TypeParam>;
	using kilograms         = hamon::units::kilograms<TypeParam>;
	using seconds           = hamon::units::seconds<TypeParam>;

	{
		// J/K
		HAMON_CONSTEXPR_OR_CONST auto a = joules(60) / kelvins(3);
		static_assert(std::is_same<decltype(a), const joules_per_kelvin>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, a.value());
	}
	{
		// m^2・kg・s^-2・K^-1
		HAMON_CONSTEXPR_OR_CONST auto a = metres(3) * metres(4) * kilograms(5) / (seconds(2) * seconds(3) * kelvins(1));
		static_assert(std::is_same<decltype(a), const joules_per_kelvin>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, a.value());
	}
}

TYPED_TEST(UnitsTest, IlluminanceTest)
{
	using lumens = hamon::units::lumens<TypeParam>;
	using metres = hamon::units::metres<TypeParam>;
	using lux    = hamon::units::lux<TypeParam>;

	{
		// lm・m^-2
		HAMON_CONSTEXPR_OR_CONST auto lx = lumens(60) / (metres(4) * metres(5));
		static_assert(std::is_same<decltype(lx), const lux>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, lx.value());
	}
}

TYPED_TEST(UnitsTest, InductanceTest)
{
	using volts     = hamon::units::volts<TypeParam>;
	using amperes   = hamon::units::amperes<TypeParam>;
	using seconds   = hamon::units::seconds<TypeParam>;
	using henries   = hamon::units::henries<TypeParam>;
	using joules    = hamon::units::joules<TypeParam>;
	using kilograms = hamon::units::kilograms<TypeParam>;
	using metres    = hamon::units::metres<TypeParam>;

	{
		// V/(A/s)
		HAMON_CONSTEXPR_OR_CONST auto H = volts(30) / (amperes(4) / seconds(2));
		static_assert(std::is_same<decltype(H), const henries>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, H.value());
	}
	{
		// J・A^-2
		HAMON_CONSTEXPR_OR_CONST auto H = joules(30) / (amperes(2) * amperes(3));
		static_assert(std::is_same<decltype(H), const henries>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, H.value());
	}
	{
		// kg・m^2・s^-2・A^-2
		HAMON_CONSTEXPR_OR_CONST auto H = (kilograms(30) * metres(6) * metres(8)) / (seconds(2) * seconds(3) * amperes(4) * amperes(5));
		static_assert(std::is_same<decltype(H), const henries>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, H.value());
	}
}

TYPED_TEST(UnitsTest, InformationTest)
{
	{
		HAMON_CONSTEXPR hamon::units::bits<TypeParam>		b(1);

		HAMON_CONSTEXPR hamon::units::bytes<TypeParam>		B(b);
		HAMON_CONSTEXPR hamon::units::kilobytes<TypeParam>	kB(b);
		HAMON_CONSTEXPR hamon::units::megabytes<TypeParam>	MB(b);
		HAMON_CONSTEXPR hamon::units::gigabytes<TypeParam>	GB(b);
		HAMON_CONSTEXPR hamon::units::kibibytes<TypeParam>	KiB(b);
		HAMON_CONSTEXPR hamon::units::mebibytes<TypeParam>	MiB(b);
		HAMON_CONSTEXPR hamon::units::gibibytes<TypeParam>	GiB(b);

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (1.0 / 8,                              B.value());
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0 / 8 / 1000,               (double)kB.value(),  0.00000000001);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0 / 8 / 1000 / 1000,        (double)MB.value(),  0.000000000000001);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0 / 8 / 1000 / 1000 / 1000, (double)GB.value(),  0.00000000000000001);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (1.0 / 8 / 1024,                       KiB.value());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (1.0 / 8 / 1024 / 1024,                MiB.value());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (1.0 / 8 / 1024 / 1024 / 1024,         GiB.value());
	}
	{
		HAMON_CONSTEXPR hamon::units::bytes<TypeParam>		B(2);

		HAMON_CONSTEXPR hamon::units::bits<TypeParam>		b(B);
		HAMON_CONSTEXPR hamon::units::kilobytes<TypeParam>	kB(B);
		HAMON_CONSTEXPR hamon::units::megabytes<TypeParam>	MB(B);
		HAMON_CONSTEXPR hamon::units::gigabytes<TypeParam>	GB(B);
		HAMON_CONSTEXPR hamon::units::kibibytes<TypeParam>	KiB(B);
		HAMON_CONSTEXPR hamon::units::mebibytes<TypeParam>	MiB(B);
		HAMON_CONSTEXPR hamon::units::gibibytes<TypeParam>	GiB(B);

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (2.0 * 8,                          b.value());
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.0 / 1000,               (double)kB.value(),  0.0000000001);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.0 / 1000 / 1000,        (double)MB.value(),  0.00000000000001);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.0 / 1000 / 1000 / 1000, (double)GB.value(),  0.0000000000000001);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (2.0 / 1024,                       KiB.value());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (2.0 / 1024 / 1024,                MiB.value());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (2.0 / 1024 / 1024 / 1024,         GiB.value());
	}
	{
		HAMON_CONSTEXPR hamon::units::megabytes<TypeParam>	MB(4);

		HAMON_CONSTEXPR hamon::units::bits<TypeParam>		b(MB);
		HAMON_CONSTEXPR hamon::units::bytes<TypeParam>		B(MB);
		HAMON_CONSTEXPR hamon::units::kilobytes<TypeParam>	kB(MB);
		HAMON_CONSTEXPR hamon::units::gigabytes<TypeParam>	GB(MB);
		HAMON_CONSTEXPR hamon::units::kibibytes<TypeParam>	KiB(MB);
		HAMON_CONSTEXPR hamon::units::mebibytes<TypeParam>	MiB(MB);
		HAMON_CONSTEXPR hamon::units::gibibytes<TypeParam>	GiB(MB);

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (4.0 * 8 * 1000 * 1000,                  b.value());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (4.0 * 1000 * 1000,                      B.value());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (4.0 * 1000,                             kB.value());
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(4.0 / 1000,                     (double)GB.value(), 0.000000001);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (4.0 * 1000 * 1000 / 1024,               KiB.value());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (4.0 * 1000 * 1000 / 1024 / 1024,        MiB.value());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (4.0 * 1000 * 1000 / 1024 / 1024 / 1024, GiB.value());
	}
	{
		HAMON_CONSTEXPR hamon::units::kibibytes<TypeParam>	KiB(6);

		HAMON_CONSTEXPR hamon::units::bits<TypeParam>		b(KiB);
		HAMON_CONSTEXPR hamon::units::bytes<TypeParam>		B(KiB);
		HAMON_CONSTEXPR hamon::units::kilobytes<TypeParam>	kB(KiB);
		HAMON_CONSTEXPR hamon::units::megabytes<TypeParam>	MB(KiB);
		HAMON_CONSTEXPR hamon::units::gigabytes<TypeParam>	GB(KiB);
		HAMON_CONSTEXPR hamon::units::mebibytes<TypeParam>	MiB(KiB);
		HAMON_CONSTEXPR hamon::units::gibibytes<TypeParam>	GiB(KiB);

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (6.0 * 8 * 1024,                          b.value());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (6.0 * 1024,                              B.value());
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(6.0 * 1024 / 1000,               (double)kB.value(), 0.0000001);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(6.0 * 1024 / 1000 / 1000,        (double)MB.value(), 0.000000001);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(6.0 * 1024 / 1000 / 1000 / 1000, (double)GB.value(), 0.0000000000001);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (6.0 / 1024,                              MiB.value());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (6.0 / 1024 / 1024,                       GiB.value());
	}
}

TYPED_TEST(UnitsTest, KinematicViscosityTest)
{
	using square_metres_per_second = hamon::units::square_metres_per_second<TypeParam>;
	using seconds                  = hamon::units::seconds<TypeParam>;
	using metres                   = hamon::units::metres<TypeParam>;

	{
		// m^2/s
		HAMON_CONSTEXPR_OR_CONST auto v = metres(10) * metres(6) / seconds(2);
		static_assert(std::is_same<decltype(v), const square_metres_per_second>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(30, v.value());
	}
}

TYPED_TEST(UnitsTest, LengthTest)
{
	HAMON_CONSTEXPR hamon::units::millimetres<TypeParam> mm(1);
	HAMON_CONSTEXPR hamon::units::centimetres<TypeParam> cm(2);
	HAMON_CONSTEXPR hamon::units::metres<TypeParam>      m (3);
	HAMON_CONSTEXPR hamon::units::kilometres<TypeParam>  km(4);
	HAMON_CONSTEXPR hamon::units::inches<TypeParam>		 in(5);
	HAMON_CONSTEXPR hamon::units::feet<TypeParam>		 ft(6);
	HAMON_CONSTEXPR hamon::units::yards<TypeParam>		 yd(7);
	HAMON_CONSTEXPR hamon::units::miles<TypeParam>		 mi(8);

	HAMON_CONSTEXPR hamon::units::metres<float>          m_1(mm);
	HAMON_CONSTEXPR hamon::units::metres<TypeParam>      m_2(cm);
	HAMON_CONSTEXPR hamon::units::metres<float>          m_3(m);
	HAMON_CONSTEXPR hamon::units::metres<TypeParam>      m_4(km);
	HAMON_CONSTEXPR hamon::units::metres<TypeParam>      m_5(in);
	HAMON_CONSTEXPR hamon::units::metres<TypeParam>      m_6(ft);
	HAMON_CONSTEXPR hamon::units::metres<TypeParam>      m_7(yd);
	HAMON_CONSTEXPR hamon::units::metres<TypeParam>      m_8(mi);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1LL *    0.001,  (double)m_1.value(), 0.0000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2LL *    0.01,   (double)m_2.value(), 0.000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 3LL *    1,              m_3.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 4LL * 1000,              m_4.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 5LL *    0.0254, (double)m_5.value(), 0.00000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 6LL *    0.3048, (double)m_6.value(), 0.0000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 7LL *    0.9144, (double)m_7.value(), 0.000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 8LL * 1609.344,  (double)m_8.value(), 0.0001);

	HAMON_CONSTEXPR hamon::units::kilometres<TypeParam>  km_1(mm);
	HAMON_CONSTEXPR hamon::units::kilometres<float>      km_2(cm);
	HAMON_CONSTEXPR hamon::units::kilometres<TypeParam>  km_3(m);
	HAMON_CONSTEXPR hamon::units::kilometres<float>      km_4(km);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1LL * 0.000001, (double)km_1.value(), 0.00000000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2LL * 0.00001,  (double)km_2.value(), 0.000000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3LL * 0.001,    (double)km_3.value(), 0.0000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 4LL * 1,                km_4.value());

	HAMON_CONSTEXPR hamon::units::inches<TypeParam>	in_1(m);
	HAMON_CONSTEXPR hamon::units::inches<float>		in_2(in);
	HAMON_CONSTEXPR hamon::units::inches<TypeParam>	in_3(ft);
	HAMON_CONSTEXPR hamon::units::inches<float>		in_4(yd);
	HAMON_CONSTEXPR hamon::units::inches<TypeParam>	in_5(mi);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3LL *    39.3700787402, (double)in_1.value(), 0.000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 5LL *     1,                    in_2.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 6LL *    12,                    in_3.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 7LL *    36,                    in_4.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 8LL * 63360,                    in_5.value());

	HAMON_CONSTEXPR hamon::units::feet<float>		ft_1(m);
	HAMON_CONSTEXPR hamon::units::feet<TypeParam>	ft_2(in);
	HAMON_CONSTEXPR hamon::units::feet<float>		ft_3(ft);
	HAMON_CONSTEXPR hamon::units::feet<TypeParam>	ft_4(yd);
	HAMON_CONSTEXPR hamon::units::feet<TypeParam>	ft_5(mi);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3LL *    3.2808398950, (double)ft_1.value(), 0.0000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 5LL *    0.0833333333, (double)ft_2.value(), 0.00000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 6LL *    1,                    ft_3.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 7LL *    3,                    ft_4.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 8LL * 5280,                    ft_5.value());

	HAMON_CONSTEXPR hamon::units::yards<TypeParam>	yd_1(m);
	HAMON_CONSTEXPR hamon::units::yards<TypeParam>	yd_2(in);
	HAMON_CONSTEXPR hamon::units::yards<float>		yd_3(ft);
	HAMON_CONSTEXPR hamon::units::yards<float>		yd_4(yd);
	HAMON_CONSTEXPR hamon::units::yards<float>		yd_5(mi);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3LL *    1.0936132983, (double)yd_1.value(), 0.0000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 5LL *    0.0277777777, (double)yd_2.value(), 0.00000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 6LL *    0.3333333333, (double)yd_3.value(), 0.000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 7LL *    1,                    yd_4.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 8LL * 1760,                    yd_5.value());

	HAMON_CONSTEXPR hamon::units::miles<TypeParam>	mi_1(m);
	HAMON_CONSTEXPR hamon::units::miles<TypeParam>	mi_2(in);
	HAMON_CONSTEXPR hamon::units::miles<float>		mi_3(ft);
	HAMON_CONSTEXPR hamon::units::miles<float>		mi_4(yd);
	HAMON_CONSTEXPR hamon::units::miles<float>		mi_5(mi);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3LL * 0.000621371, (double)mi_1.value(), 0.000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 5LL * 0.000015783, (double)mi_2.value(), 0.000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 6LL * 0.000189394, (double)mi_3.value(), 0.000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 7LL * 0.000568182, (double)mi_4.value(), 0.00000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 8LL * 1,                   mi_5.value());
}

TYPED_TEST(UnitsTest, LuminanceTest)
{
	using candelas_per_square_metre = hamon::units::candelas_per_square_metre<TypeParam>;
	using candelas                  = hamon::units::candelas<TypeParam>;
	using metres                    = hamon::units::metres<TypeParam>;

	{
		// cd/m^2
		HAMON_CONSTEXPR_OR_CONST auto a = candelas(60) / (metres(3) * metres(4));
		static_assert(std::is_same<decltype(a), const candelas_per_square_metre>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, a.value());
	}
}

TYPED_TEST(UnitsTest, LuminousFluxTest)
{
	using candelas   = hamon::units::candelas<TypeParam>;
	using steradians = hamon::units::steradians<TypeParam>;
	using lumens     = hamon::units::lumens<TypeParam>;

	{
		// cd・sr
		HAMON_CONSTEXPR_OR_CONST auto lm = candelas(3) * steradians(4);
		static_assert(std::is_same<decltype(lm), const lumens>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, lm.value());
	}
}

TYPED_TEST(UnitsTest, LuminousIntensityTest)
{
	{
		HAMON_CONSTEXPR hamon::units::candelas<TypeParam>      cd(2);

		HAMON_CONSTEXPR hamon::units::kilocandelas<TypeParam>  kcd(cd);
		HAMON_CONSTEXPR hamon::units::megacandelas<TypeParam>  Mcd(cd);

		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.0 / 1000,        (double)kcd.value(), 0.0000000001);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.0 / 1000 / 1000, (double)Mcd.value(), 0.00000000000001);
	}
	{
		HAMON_CONSTEXPR hamon::units::kilocandelas<TypeParam>  kcd(3);

		HAMON_CONSTEXPR hamon::units::candelas<TypeParam>      cd(kcd);
		HAMON_CONSTEXPR hamon::units::megacandelas<TypeParam>  Mcd(kcd);

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 3.0 * 1000,         cd.value());
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.0 / 1000, (double)Mcd.value(), 0.0000000001);
	}
	{
		HAMON_CONSTEXPR hamon::units::megacandelas<TypeParam>  Mcd(4);

		HAMON_CONSTEXPR hamon::units::candelas<TypeParam>      cd(Mcd);
		HAMON_CONSTEXPR hamon::units::kilocandelas<TypeParam>  kcd(Mcd);

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4.0 * 1000 * 1000, cd.value());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4.0 * 1000,        kcd.value());
	}
}

TYPED_TEST(UnitsTest, MagneticFieldIntensityTest)
{
	using amperes_per_metre = hamon::units::amperes_per_metre<TypeParam>;
	using amperes           = hamon::units::amperes<TypeParam>;
	using metres            = hamon::units::metres<TypeParam>;

	{
		// A/m
		HAMON_CONSTEXPR_OR_CONST auto a = amperes(10) / metres(2);
		static_assert(std::is_same<decltype(a), const amperes_per_metre>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, a.value());
	}
}

TYPED_TEST(UnitsTest, MagneticFluxTest)
{
	using volts     = hamon::units::volts<TypeParam>;
	using seconds   = hamon::units::seconds<TypeParam>;
	using webers    = hamon::units::webers<TypeParam>;
	using joules    = hamon::units::joules<TypeParam>;
	using amperes   = hamon::units::amperes<TypeParam>;
	using kilograms = hamon::units::kilograms<TypeParam>;
	using metres    = hamon::units::metres<TypeParam>;

	{
		// V・s
		HAMON_CONSTEXPR_OR_CONST auto Wb = volts(3) * seconds(4);
		static_assert(std::is_same<decltype(Wb), const webers>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, Wb.value());
	}
	{
		// J/A
		HAMON_CONSTEXPR_OR_CONST auto Wb = joules(60) / amperes(4);
		static_assert(std::is_same<decltype(Wb), const webers>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, Wb.value());
	}
	{
		// kg m^2 s^-2 A^-1
		HAMON_CONSTEXPR_OR_CONST auto kg = kilograms(10);
		HAMON_CONSTEXPR_OR_CONST auto m = metres(12);
		HAMON_CONSTEXPR_OR_CONST auto s = seconds(3);
		HAMON_CONSTEXPR_OR_CONST auto A = amperes(2);
		HAMON_CONSTEXPR_OR_CONST auto Wb = (kg * m * m) / (s * s * A);
		static_assert(std::is_same<decltype(Wb), const webers>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(80, Wb.value());
	}
}

TYPED_TEST(UnitsTest, MagneticFluxDensityTest)
{
	using webers        = hamon::units::webers<TypeParam>;
	using square_metres = hamon::units::square_metres<TypeParam>;
	using teslas        = hamon::units::teslas<TypeParam>;
	using volts         = hamon::units::volts<TypeParam>;
	using seconds       = hamon::units::seconds<TypeParam>;
	using metres        = hamon::units::metres<TypeParam>;
	using newtons       = hamon::units::newtons<TypeParam>;
	using amperes       = hamon::units::amperes<TypeParam>;
	using kilograms     = hamon::units::kilograms<TypeParam>;

	{
		// Wb・m^-2
		HAMON_CONSTEXPR_OR_CONST auto T = webers(30) / square_metres(3);
		static_assert(std::is_same<decltype(T), const teslas>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, T.value());
	}
	{
		// V・s・m^-2
		HAMON_CONSTEXPR_OR_CONST auto T = volts(10) * seconds(3) / (metres(2) * metres(3));
		static_assert(std::is_same<decltype(T), const teslas>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, T.value());
	}
	{
		// N・A^-1・m^-1
		HAMON_CONSTEXPR_OR_CONST auto T = newtons(18) / amperes(3) / metres(2);
		static_assert(std::is_same<decltype(T), const teslas>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, T.value());
	}
	{
		// kg・A^-1・s^-2
		HAMON_CONSTEXPR_OR_CONST auto T = kilograms(120) / amperes(3) / seconds(2) / seconds(5);
		static_assert(std::is_same<decltype(T), const teslas>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, T.value());
	}
}

TYPED_TEST(UnitsTest, MagneticPermeabilityTest)
{
	using henries_per_metre = hamon::units::henries_per_metre<TypeParam>;
	using henries           = hamon::units::henries<TypeParam>;
	using metres            = hamon::units::metres<TypeParam>;
	using kilograms         = hamon::units::kilograms<TypeParam>;
	using seconds           = hamon::units::seconds<TypeParam>;
	using amperes           = hamon::units::amperes<TypeParam>;

	{
		// H/m
		HAMON_CONSTEXPR_OR_CONST auto a = henries(10) / metres(2);
		static_assert(std::is_same<decltype(a), const henries_per_metre>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, a.value());
	}
	{
		// m・kg・s^-2・A^-2
		HAMON_CONSTEXPR_OR_CONST auto a = metres(6) * kilograms(10) / (seconds(1) * seconds(2) * amperes(3) * amperes(5));
		static_assert(std::is_same<decltype(a), const henries_per_metre>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, a.value());
	}
}

TYPED_TEST(UnitsTest, MagneticReluctanceTest)
{
	using amperes_per_weber  = hamon::units::amperes_per_weber<TypeParam>;
	using reciprocal_henries = hamon::units::reciprocal_henries<TypeParam>;
	using amperes            = hamon::units::amperes<TypeParam>;
	using webers             = hamon::units::webers<TypeParam>;
	using henries            = hamon::units::henries<TypeParam>;
	using seconds            = hamon::units::seconds<TypeParam>;
	using metres             = hamon::units::metres<TypeParam>;
	using kilograms          = hamon::units::kilograms<TypeParam>;

	{
		// A/Wb
		HAMON_CONSTEXPR_OR_CONST auto a = amperes(60) / webers(2);
		static_assert(std::is_same<decltype(a), const amperes_per_weber>::value, "");
		static_assert(std::is_same<decltype(a), const reciprocal_henries>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(30, a.value());
	}
	{
		// H^-1
		HAMON_CONSTEXPR_OR_CONST auto a = TypeParam(10) / henries(2);
		static_assert(std::is_same<decltype(a), const amperes_per_weber>::value, "");
		static_assert(std::is_same<decltype(a), const reciprocal_henries>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, a.value());
	}
	{
		// m^-2・kg^-1・s^2・A^2
		HAMON_CONSTEXPR_OR_CONST auto a = seconds(2) * seconds(3) * amperes(4) * amperes(5) / (metres(2) * metres(3) * kilograms(4));
		static_assert(std::is_same<decltype(a), const amperes_per_weber>::value, "");
		static_assert(std::is_same<decltype(a), const reciprocal_henries>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, a.value());
	}
}

TYPED_TEST(UnitsTest, MassTest)
{
	HAMON_CONSTEXPR hamon::units::milligrams<TypeParam> mg(1);
	HAMON_CONSTEXPR hamon::units::grams<TypeParam>      g(2);
	HAMON_CONSTEXPR hamon::units::kilograms<TypeParam>  kg(3);
	HAMON_CONSTEXPR hamon::units::tonnes<TypeParam>	    t(4);
	HAMON_CONSTEXPR hamon::units::grains<TypeParam>	    gr(5);
	HAMON_CONSTEXPR hamon::units::ounces<TypeParam>	    oz(6);
	HAMON_CONSTEXPR hamon::units::pounds<TypeParam>	    lb(7);

	HAMON_CONSTEXPR hamon::units::milligrams<TypeParam> mg_1(mg);
	HAMON_CONSTEXPR hamon::units::milligrams<TypeParam> mg_2(g);
	HAMON_CONSTEXPR hamon::units::milligrams<TypeParam> mg_3(kg);
	HAMON_CONSTEXPR hamon::units::milligrams<TypeParam> mg_4(t);
	HAMON_CONSTEXPR hamon::units::milligrams<TypeParam> mg_5(gr);
	HAMON_CONSTEXPR hamon::units::milligrams<TypeParam> mg_6(oz);
	HAMON_CONSTEXPR hamon::units::milligrams<TypeParam> mg_7(lb);

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 1LL * 1.0            *    1.0,                           mg_1.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 2LL * 1.0            * 1000.0,                           mg_2.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 3LL * 1.0            * 1000.0 * 1000.0,                  mg_3.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 4LL * 1.0            * 1000.0 * 1000.0 * 1000.0,         mg_4.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 5LL * 0.00006479891  * 1000.0 * 1000.0,          (double)mg_5.value(), 0.0001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 6LL * 0.028349523125 * 1000.0 * 1000.0,          (double)mg_6.value(), 0.01);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 7LL * 0.45359237     * 1000.0 * 1000.0,          (double)mg_7.value(), 0.1);

	HAMON_CONSTEXPR hamon::units::grams<TypeParam> g_1(mg);
	HAMON_CONSTEXPR hamon::units::grams<TypeParam> g_2(g);
	HAMON_CONSTEXPR hamon::units::grams<TypeParam> g_3(kg);
	HAMON_CONSTEXPR hamon::units::grams<TypeParam> g_4(t);
	HAMON_CONSTEXPR hamon::units::grams<TypeParam> g_5(gr);
	HAMON_CONSTEXPR hamon::units::grams<TypeParam> g_6(oz);
	HAMON_CONSTEXPR hamon::units::grams<TypeParam> g_7(lb);

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1LL * 1.0            *    0.001,        (double)g_1.value(), 0.0000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 2LL * 1.0            *    1.0,                  g_2.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 3LL * 1.0            * 1000.0,                  g_3.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 4LL * 1.0            * 1000.0 * 1000.0,         g_4.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 5LL * 0.00006479891  * 1000.0,          (double)g_5.value(), 0.00000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 6LL * 0.028349523125 * 1000.0,          (double)g_6.value(), 0.00001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 7LL * 0.45359237     * 1000.0,          (double)g_7.value(), 0.001);

	HAMON_CONSTEXPR hamon::units::kilograms<TypeParam> kg_1(mg);
	HAMON_CONSTEXPR hamon::units::kilograms<TypeParam> kg_2(g);
	HAMON_CONSTEXPR hamon::units::kilograms<TypeParam> kg_3(kg);
	HAMON_CONSTEXPR hamon::units::kilograms<TypeParam> kg_4(t);
	HAMON_CONSTEXPR hamon::units::kilograms<TypeParam> kg_5(gr);
	HAMON_CONSTEXPR hamon::units::kilograms<TypeParam> kg_6(oz);
	HAMON_CONSTEXPR hamon::units::kilograms<TypeParam> kg_7(lb);

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1LL * 1.0            *    0.001 * 0.001, (double)kg_1.value(), 0.0000000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2LL * 1.0            *    0.001,         (double)kg_2.value(), 0.0000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 3LL * 1.0            *    1.0,                   kg_3.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 4LL * 1.0            * 1000.0,                   kg_4.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 5LL * 0.00006479891  *    1.0,           (double)kg_5.value(), 0.0000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 6LL * 0.028349523125 *    1.0,           (double)kg_6.value(), 0.00000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 7LL * 0.45359237     *    1.0,           (double)kg_7.value(), 0.0000001);

	HAMON_CONSTEXPR hamon::units::tonnes<TypeParam> t_1(mg);
	HAMON_CONSTEXPR hamon::units::tonnes<TypeParam> t_2(g);
	HAMON_CONSTEXPR hamon::units::tonnes<TypeParam> t_3(kg);
	HAMON_CONSTEXPR hamon::units::tonnes<TypeParam> t_4(t);
	HAMON_CONSTEXPR hamon::units::tonnes<TypeParam> t_5(gr);
	HAMON_CONSTEXPR hamon::units::tonnes<TypeParam> t_6(oz);
	HAMON_CONSTEXPR hamon::units::tonnes<TypeParam> t_7(lb);

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1LL * 1.0            *    0.001 * 0.001 * 0.001, (double)t_1.value(), 0.0000000000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2LL * 1.0            *    0.001 * 0.001,         (double)t_2.value(), 0.00000000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3LL * 1.0            *    0.001,                 (double)t_3.value(), 0.0000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 4LL * 1.0            *    1.0,                           t_4.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 5LL * 0.00006479891  *    0.001,                 (double)t_5.value(), 0.00000000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 6LL * 0.028349523125 *    0.001,                 (double)t_6.value(), 0.00000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 7LL * 0.45359237     *    0.001,                 (double)t_7.value(), 0.0000000001);

	HAMON_CONSTEXPR hamon::units::grains<TypeParam> gr_1(mg);
	HAMON_CONSTEXPR hamon::units::grains<TypeParam> gr_2(g);
	HAMON_CONSTEXPR hamon::units::grains<TypeParam> gr_3(kg);
	HAMON_CONSTEXPR hamon::units::grains<TypeParam> gr_4(t);
	HAMON_CONSTEXPR hamon::units::grains<TypeParam> gr_5(gr);
	HAMON_CONSTEXPR hamon::units::grains<TypeParam> gr_6(oz);
	HAMON_CONSTEXPR hamon::units::grains<TypeParam> gr_7(lb);

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1LL /    0.00006479891 *    0.001 * 0.001, (double)gr_1.value(),  0.000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2LL /    0.00006479891 *    0.001,         (double)gr_2.value(),  0.000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3LL /    0.00006479891 *    1.0,           (double)gr_3.value(),  0.001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 4LL /    0.00006479891 * 1000.0,           (double)gr_4.value(), 10.0);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 5LL *    1.0           *    1.0,                   gr_5.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 6LL *  437.5           *    1.0,                   gr_6.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 7LL * 7000.0           *    1.0,                   gr_7.value());

	HAMON_CONSTEXPR hamon::units::ounces<TypeParam> oz_1(mg);
	HAMON_CONSTEXPR hamon::units::ounces<TypeParam> oz_2(g);
	HAMON_CONSTEXPR hamon::units::ounces<TypeParam> oz_3(kg);
	HAMON_CONSTEXPR hamon::units::ounces<TypeParam> oz_4(t);
	HAMON_CONSTEXPR hamon::units::ounces<TypeParam> oz_5(gr);
	HAMON_CONSTEXPR hamon::units::ounces<TypeParam> oz_6(oz);
	HAMON_CONSTEXPR hamon::units::ounces<TypeParam> oz_7(lb);

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1LL /   0.028349523125 *    0.001 * 0.001, (double)oz_1.value(),  0.000000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2LL /   0.028349523125 *    0.001,         (double)oz_2.value(),  0.000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3LL /   0.028349523125 *    1.0,           (double)oz_3.value(),  0.00001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 4LL /   0.028349523125 * 1000.0,           (double)oz_4.value(),  0.01);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 5LL / 437.5            *    1.0,           (double)oz_5.value(),  0.000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 6LL *   1.0            *    1.0,                   oz_6.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 7LL *  16.0            *    1.0,                   oz_7.value());

	HAMON_CONSTEXPR hamon::units::pounds<TypeParam> lb_1(mg);
	HAMON_CONSTEXPR hamon::units::pounds<TypeParam> lb_2(g);
	HAMON_CONSTEXPR hamon::units::pounds<TypeParam> lb_3(kg);
	HAMON_CONSTEXPR hamon::units::pounds<TypeParam> lb_4(t);
	HAMON_CONSTEXPR hamon::units::pounds<TypeParam> lb_5(gr);
	HAMON_CONSTEXPR hamon::units::pounds<TypeParam> lb_6(oz);
	HAMON_CONSTEXPR hamon::units::pounds<TypeParam> lb_7(lb);

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1LL /   0.45359237 *    0.001 * 0.001, (double)lb_1.value(),  0.0000000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2LL /   0.45359237 *    0.001,         (double)lb_2.value(),  0.0000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3LL /   0.45359237 *    1.0,           (double)lb_3.value(),  0.000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 4LL /   0.45359237 * 1000.0,           (double)lb_4.value(),  0.001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 5LL / 7000.0       *    1.0,           (double)lb_5.value(),  0.00000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 6LL /   16.0       *    1.0,                   lb_6.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 7LL *    1.0       *    1.0,                   lb_7.value());
}

TYPED_TEST(UnitsTest, MassDensityTest)
{
	using kilograms                  = hamon::units::kilograms<TypeParam>;
	using grams                      = hamon::units::grams<TypeParam>;
	using pounds                     = hamon::units::pounds<TypeParam>;

	using metres                     = hamon::units::metres<TypeParam>;
	using centimetres                = hamon::units::centimetres<TypeParam>;
	using feet                       = hamon::units::feet<TypeParam>;

	using kilograms_per_cubic_metre  = hamon::units::kilograms_per_cubic_metre<TypeParam>;
	using grams_per_cubic_centimetre = hamon::units::grams_per_cubic_centimetre<TypeParam>;
	using pounds_per_cubic_foot      = hamon::units::pounds_per_cubic_foot<TypeParam>;

	{
		HAMON_CONSTEXPR_OR_CONST auto v = kilograms(120) / metres(2) / metres(3) / metres(4);
		static_assert(std::is_same<decltype(v), const kilograms_per_cubic_metre>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, v.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto v = grams(120) / centimetres(1) / centimetres(2) / centimetres(3);
		static_assert(std::is_same<decltype(v), const grams_per_cubic_centimetre>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, v.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto v = pounds(120) / feet(3) / feet(4) / feet(5);
		static_assert(std::is_same<decltype(v), const pounds_per_cubic_foot>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.0, (double)v.value(), 0.000001);
	}
}

TYPED_TEST(UnitsTest, MolarEnergyTest)
{
	using joules_per_mole = hamon::units::joules_per_mole<TypeParam>;
	using joules          = hamon::units::joules<TypeParam>;
	using mole            = hamon::units::mole<TypeParam>;
	using metres          = hamon::units::metres<TypeParam>;
	using kilograms       = hamon::units::kilograms<TypeParam>;
	using seconds         = hamon::units::seconds<TypeParam>;

	{
		// J/mol
		HAMON_CONSTEXPR_OR_CONST auto a = joules(60) / mole(2);
		static_assert(std::is_same<decltype(a), const joules_per_mole>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(30, a.value());
	}
	{
		// m^2・kg・s^-2・mol^-1
		HAMON_CONSTEXPR_OR_CONST auto a = metres(2) * metres(3) * kilograms(4) / (seconds(1) * seconds(2) * mole(3));
		static_assert(std::is_same<decltype(a), const joules_per_mole>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, a.value());
	}
}

TYPED_TEST(UnitsTest, MolarHeatCapacityTest)
{
	using joules_per_kelvin_mole = hamon::units::joules_per_kelvin_mole<TypeParam>;
	using joules                 = hamon::units::joules<TypeParam>;
	using kelvins                = hamon::units::kelvins<TypeParam>;
	using mole                   = hamon::units::mole<TypeParam>;
	using metres                 = hamon::units::metres<TypeParam>;
	using kilograms              = hamon::units::kilograms<TypeParam>;
	using seconds                = hamon::units::seconds<TypeParam>;

	{
		// J/(K・mol)
		HAMON_CONSTEXPR_OR_CONST auto a = joules(60) / (kelvins(3) * mole(2));
		static_assert(std::is_same<decltype(a), const joules_per_kelvin_mole>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, a.value());
	}
	{
		// m^2・kg・s^-2・K^-1・mol^-1
		HAMON_CONSTEXPR_OR_CONST auto a = metres(2) * metres(3) * kilograms(4) / (seconds(1) * seconds(2) * kelvins(2) * mole(3));
		static_assert(std::is_same<decltype(a), const joules_per_kelvin_mole>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, a.value());
	}
}

TYPED_TEST(UnitsTest, MomentOfInertiaTest)
{
	using kilograms_square_metre = hamon::units::kilograms_square_metre<TypeParam>;
	using kilograms              = hamon::units::kilograms<TypeParam>;
	using metres                 = hamon::units::metres<TypeParam>;

	{
		// kg・m^2
		HAMON_CONSTEXPR_OR_CONST auto a = kilograms(2) * metres(3) * metres(4);
		static_assert(std::is_same<decltype(a), const kilograms_square_metre>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(24, a.value());
	}
}

TYPED_TEST(UnitsTest, MomentumTest)
{
	using newton_seconds = hamon::units::newton_seconds<TypeParam>;
	using newtons        = hamon::units::newtons<TypeParam>;
	using seconds        = hamon::units::seconds<TypeParam>;
	using metres         = hamon::units::metres<TypeParam>;
	using kilograms      = hamon::units::kilograms<TypeParam>;

	{
		// N・s
		HAMON_CONSTEXPR_OR_CONST auto a = newtons(4) * seconds(5);
		static_assert(std::is_same<decltype(a), const newton_seconds>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, a.value());
	}
	{
		// m・kg・s^-1
		HAMON_CONSTEXPR_OR_CONST auto a = metres(4) * kilograms(3) / seconds(2);
		static_assert(std::is_same<decltype(a), const newton_seconds>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, a.value());
	}
}

TYPED_TEST(UnitsTest, PermittivityTest)
{
	using farads_per_metre = hamon::units::farads_per_metre<TypeParam>;
	using farads           = hamon::units::farads<TypeParam>;
	using metres           = hamon::units::metres<TypeParam>;
	using kilograms        = hamon::units::kilograms<TypeParam>;
	using seconds          = hamon::units::seconds<TypeParam>;
	using amperes          = hamon::units::amperes<TypeParam>;

	{
		// F/m
		HAMON_CONSTEXPR_OR_CONST auto a = farads(60) / metres(3);
		static_assert(std::is_same<decltype(a), const farads_per_metre>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, a.value());
	}
	{
		// m^-3・kg^-1・s^4・A^2
		HAMON_CONSTEXPR_OR_CONST auto m = metres(2);
		HAMON_CONSTEXPR_OR_CONST auto kg = kilograms(3);
		HAMON_CONSTEXPR_OR_CONST auto s = seconds(2);
		HAMON_CONSTEXPR_OR_CONST auto A = amperes(3);
		HAMON_CONSTEXPR_OR_CONST auto a = s * s * s * s * A * A / (m * m * m * kg);
		static_assert(std::is_same<decltype(a), const farads_per_metre>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, a.value());
	}
}

TYPED_TEST(UnitsTest, PowerTest)
{
	using metres    = hamon::units::metres<TypeParam>;
	using joules    = hamon::units::joules<TypeParam>;
	using seconds   = hamon::units::seconds<TypeParam>;
	using watts     = hamon::units::watts<TypeParam>;
	using newtons   = hamon::units::newtons<TypeParam>;
	using kilograms = hamon::units::kilograms<TypeParam>;

	{
		HAMON_CONSTEXPR_OR_CONST auto v = joules(60) / seconds(4);
		static_assert(std::is_same<decltype(v), const watts>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, v.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto v = newtons(10) * metres(6) / seconds(5);
		static_assert(std::is_same<decltype(v), const watts>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, v.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto v = metres(10) * metres(6) * kilograms(8) / seconds(2) / seconds(3) / seconds(4);
		static_assert(std::is_same<decltype(v), const watts>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, v.value());
	}
}

TYPED_TEST(UnitsTest, PressureTest)
{
	using square_metre = hamon::units::square_metre<TypeParam>;
	using metre        = hamon::units::metre<TypeParam>;
	using newtons      = hamon::units::newtons<TypeParam>;
	using kilograms    = hamon::units::kilograms<TypeParam>;
	using seconds      = hamon::units::seconds<TypeParam>;
	using pascals      = hamon::units::pascals<TypeParam>;

	{
		HAMON_CONSTEXPR_OR_CONST auto v = newtons(10) / square_metre(2);
		static_assert(std::is_same<decltype(v), const pascals>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, v.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto v = newtons(60) / metre(2) / metre(3);
		static_assert(std::is_same<decltype(v), const pascals>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, v.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto v = kilograms(120) / metre(2) / seconds(3) / seconds(4);
		static_assert(std::is_same<decltype(v), const pascals>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, v.value());
	}
}

TYPED_TEST(UnitsTest, RadioactivityTest)
{
	using seconds = hamon::units::seconds<TypeParam>;
	using becquerels = hamon::units::becquerels<TypeParam>;

	{
		// s^-1
		HAMON_CONSTEXPR_OR_CONST auto Bq = TypeParam(10) / seconds(2);
		static_assert(std::is_same<decltype(Bq), const becquerels>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, Bq.value());
	}
}

TYPED_TEST(UnitsTest, SolidAngleTest)
{
	HAMON_CONSTEXPR hamon::units::steradians<TypeParam> s(42);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, s.value());
}

TYPED_TEST(UnitsTest, SpecificEnergyTest)
{
	using joules_per_kilogram = hamon::units::joules_per_kilogram<TypeParam>;
	using joules              = hamon::units::joules<TypeParam>;
	using kilograms           = hamon::units::kilograms<TypeParam>;
	using metres              = hamon::units::metres<TypeParam>;
	using seconds             = hamon::units::seconds<TypeParam>;

	{
		// J/kg
		HAMON_CONSTEXPR_OR_CONST auto a = joules(60) / kilograms(2);
		static_assert(std::is_same<decltype(a), const joules_per_kilogram>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(30, a.value());
	}
	{
		// m^2・s^-2
		HAMON_CONSTEXPR_OR_CONST auto a = metres(6) * metres(50) / (seconds(2) * seconds(3));
		static_assert(std::is_same<decltype(a), const joules_per_kilogram>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(50, a.value());
	}
}

TYPED_TEST(UnitsTest, SpecificHeatCapacityTest)
{
	using joules_per_kilogram_kelvin = hamon::units::joules_per_kilogram_kelvin<TypeParam>;
	using joules                     = hamon::units::joules<TypeParam>;
	using kelvins                    = hamon::units::kelvins<TypeParam>;
	using kilograms                  = hamon::units::kilograms<TypeParam>;
	using metres                     = hamon::units::metres<TypeParam>;
	using seconds                    = hamon::units::seconds<TypeParam>;

	{
		// J/(K・kg)
		HAMON_CONSTEXPR_OR_CONST auto a = joules(60) / (kelvins(3) * kilograms(2));
		static_assert(std::is_same<decltype(a), const joules_per_kilogram_kelvin>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, a.value());
	}
	{
		// m^2・s^-2・K^-1
		HAMON_CONSTEXPR_OR_CONST auto a = metres(6) * metres(50) / (seconds(2) * seconds(3) * kelvins(10));
		static_assert(std::is_same<decltype(a), const joules_per_kilogram_kelvin>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, a.value());
	}
}

TYPED_TEST(UnitsTest, SpecificVolumeTest)
{
	using cubic_metres_per_kilogram = hamon::units::cubic_metres_per_kilogram<TypeParam>;
	using metres                    = hamon::units::metres<TypeParam>;
	using kilograms                 = hamon::units::kilograms<TypeParam>;

	{
		// m^3/kg
		HAMON_CONSTEXPR_OR_CONST auto a = metres(2) * metres(3) * metres(4) / kilograms(2);
		static_assert(std::is_same<decltype(a), const cubic_metres_per_kilogram>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, a.value());
	}
}

TYPED_TEST(UnitsTest, SurfaceDensityTest)
{
	using kilograms                  = hamon::units::kilograms<TypeParam>;
	using grams                      = hamon::units::grams<TypeParam>;
	using pounds                     = hamon::units::pounds<TypeParam>;

	using metres                     = hamon::units::metres<TypeParam>;
	using centimetres                = hamon::units::centimetres<TypeParam>;
	using feet                       = hamon::units::feet<TypeParam>;

	using kilograms_per_square_metre  = hamon::units::kilograms_per_square_metre<TypeParam>;
	using grams_per_square_centimetre = hamon::units::grams_per_square_centimetre<TypeParam>;
	using pounds_per_square_foot      = hamon::units::pounds_per_square_foot<TypeParam>;

	{
		HAMON_CONSTEXPR_OR_CONST auto v = kilograms(120) / metres(2) / metres(3);
		static_assert(std::is_same<decltype(v), const kilograms_per_square_metre>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, v.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto v = grams(120) / centimetres(1) / centimetres(2);
		static_assert(std::is_same<decltype(v), const grams_per_square_centimetre>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(60, v.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto v = pounds(120) / feet(3) / feet(4);
		static_assert(std::is_same<decltype(v), const pounds_per_square_foot>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(10.0, (double)v.value(), 0.000001);
	}
}

TYPED_TEST(UnitsTest, SurfaceTensionTest)
{
	using newtons_per_metre = hamon::units::newtons_per_metre<TypeParam>;
	using newtons           = hamon::units::newtons<TypeParam>;
	using metres            = hamon::units::metres<TypeParam>;
	using joules            = hamon::units::joules<TypeParam>;
	using kilograms         = hamon::units::kilograms<TypeParam>;
	using seconds           = hamon::units::seconds<TypeParam>;

	{
		// N / m
		HAMON_CONSTEXPR_OR_CONST auto a = newtons(60) / metres(2);
		static_assert(std::is_same<decltype(a), const newtons_per_metre>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(30, a.value());
	}
	{
		// J / m^2
		HAMON_CONSTEXPR_OR_CONST auto a = joules(60) / (metres(2) * metres(3));
		static_assert(std::is_same<decltype(a), const newtons_per_metre>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, a.value());
	}
	{
		// kg・s^-2
		HAMON_CONSTEXPR_OR_CONST auto a = kilograms(30) / (seconds(2) * seconds(3));
		static_assert(std::is_same<decltype(a), const newtons_per_metre>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, a.value());
	}
}

TYPED_TEST(UnitsTest, TemperatureTest)
{
	using kelvins            = hamon::units::kelvins<TypeParam>;
	using kilokelvins        = hamon::units::kilokelvins<TypeParam>;
	using megakelvins        = hamon::units::megakelvins<TypeParam>;
	using degrees_celsius    = hamon::units::degrees_celsius<TypeParam>;
	using degrees_fahrenheit = hamon::units::degrees_fahrenheit<TypeParam>;

	{
		HAMON_CONSTEXPR kelvins            k(0);
		HAMON_CONSTEXPR kilokelvins        kk(k);
		HAMON_CONSTEXPR megakelvins        Mk(k);
		HAMON_CONSTEXPR degrees_celsius	   c(k);
		HAMON_CONSTEXPR degrees_fahrenheit f(k);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (   0.0,          kk.value());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (   0.0,          Mk.value());
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-273.15, (double)c.value(),  0.00001);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-459.67, (double)f.value(),  0.0001);
	}
	{
		HAMON_CONSTEXPR kelvins            k(TypeParam(255.3722222222));
		HAMON_CONSTEXPR kilokelvins        kk(k);
		HAMON_CONSTEXPR megakelvins        Mk(k);
		HAMON_CONSTEXPR degrees_celsius	   c(k);
		HAMON_CONSTEXPR degrees_fahrenheit f(k);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(255.3722222222 * 0.001,         (double)kk.value(), 0.00000001);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(255.3722222222 * 0.001 * 0.001, (double)Mk.value(), 0.0000000001);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-17.7777777778,                 (double)c.value(),  0.00001);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.0,                          (double)f.value(),  0.00001);
	}
	{
		HAMON_CONSTEXPR kelvins            k(TypeParam(273.15));
		HAMON_CONSTEXPR kilokelvins        kk(k);
		HAMON_CONSTEXPR megakelvins        Mk(k);
		HAMON_CONSTEXPR degrees_celsius	   c(k);
		HAMON_CONSTEXPR degrees_fahrenheit f(k);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(273.15 * 0.001,         (double)kk.value(), 0.00000001);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(273.15 * 0.001 * 0.001, (double)Mk.value(), 0.0000000001);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.0,                  (double)c.value(),  0.00001);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 32.0,                  (double)f.value(),  0.0001);
	}
	// celsius + celsius -> kelvins
	{
		// ※ 7 ℃ + 5 ℃ = 12 ℃　ではない
		// ケルビンに変換してから計算される
		// 280.15 K + 278.15 K = 558.30 K
		HAMON_CONSTEXPR kelvins k = degrees_celsius(7) + degrees_celsius(5);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(558.30, (double)k.value(), 0.0001);
	}
	// fahrenheit + fahrenheit -> kelvins
	{
		// ※ 7 °F + 5 °F = 12 °F　ではない
		// ケルビンに変換してから計算される
		// 259.2611111 K + 258.15 K = 517.41111 K
		HAMON_CONSTEXPR kelvins k = degrees_fahrenheit(7) + degrees_fahrenheit(5);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(517.41111111111111111111111111111, (double)k.value(), 0.0001);
	}
	// celsius - celsius -> kelvins
	{
		// ※ 7 ℃ - 5 ℃ = 2 ℃　ではない
		// ケルビンに変換してから計算される
		// 280.15 K - 278.15 K = 2.0 K
		HAMON_CONSTEXPR kelvins k = degrees_celsius(7) - degrees_celsius(5);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.0, (double)k.value(), 0.0001);
	}
	// fahrenheit - fahrenheit -> kelvins
	{
		// ※ 7 °F - 5 °F = 2 °F　ではない
		// ケルビンに変換してから計算される
		// 259.2611111 K - 258.15 K = 1.11111 K
		HAMON_CONSTEXPR kelvins k = degrees_fahrenheit(7) - degrees_fahrenheit(5);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.11111111111111111111111111111, (double)k.value(), 0.0001);
	}
}

TYPED_TEST(UnitsTest, ThermalConductivityTest)
{
	using watts_per_metre_kelvin = hamon::units::watts_per_metre_kelvin<TypeParam>;
	using watts                  = hamon::units::watts<TypeParam>;
	using metres                 = hamon::units::metres<TypeParam>;
	using kelvins                = hamon::units::kelvins<TypeParam>;
	using kilograms              = hamon::units::kilograms<TypeParam>;
	using seconds                = hamon::units::seconds<TypeParam>;

	{
		// W/(m・K)
		HAMON_CONSTEXPR_OR_CONST auto a = watts(60) / (metres(2) * kelvins(3));
		static_assert(std::is_same<decltype(a), const watts_per_metre_kelvin>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, a.value());
	}
	{
		// m・kg・s^-3・K^-1
		HAMON_CONSTEXPR_OR_CONST auto a = metres(8) * kilograms(6) / (seconds(1) * seconds(2) * seconds(3) * kelvins(4));
		static_assert(std::is_same<decltype(a), const watts_per_metre_kelvin>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, a.value());
	}
}

TYPED_TEST(UnitsTest, TimeTest)
{
	HAMON_CONSTEXPR hamon::units::milliseconds<TypeParam> ms (1);
	HAMON_CONSTEXPR hamon::units::seconds<TypeParam>      s  (2);
	HAMON_CONSTEXPR hamon::units::minutes<TypeParam>      min(3);
	HAMON_CONSTEXPR hamon::units::hours<TypeParam>		  h  (4);
	HAMON_CONSTEXPR hamon::units::days<TypeParam>		  d  (5);
	HAMON_CONSTEXPR hamon::units::years<TypeParam>		  y  (6);

	HAMON_CONSTEXPR hamon::units::seconds<float>          s_1(ms);
	HAMON_CONSTEXPR hamon::units::seconds<float>          s_2(s);
	HAMON_CONSTEXPR hamon::units::seconds<TypeParam>      s_3(min);
	HAMON_CONSTEXPR hamon::units::seconds<TypeParam>      s_4(h);
	HAMON_CONSTEXPR hamon::units::seconds<TypeParam>      s_5(d);
	HAMON_CONSTEXPR hamon::units::seconds<TypeParam>      s_6(y);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1LL *        0.001, (double)s_1.value(), 0.0000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 2LL *        1,             s_2.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 3LL *       60,             s_3.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 4LL *     3600,             s_4.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 5LL *    86400,             s_5.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 6LL * 31557600,             s_6.value());

	HAMON_CONSTEXPR hamon::units::milliseconds<TypeParam>  ms_1(ms);
	HAMON_CONSTEXPR hamon::units::milliseconds<TypeParam>  ms_2(s);
	HAMON_CONSTEXPR hamon::units::milliseconds<TypeParam>  ms_3(min);
	HAMON_CONSTEXPR hamon::units::milliseconds<TypeParam>  ms_4(h);
	HAMON_CONSTEXPR hamon::units::milliseconds<TypeParam>  ms_5(d);
	HAMON_CONSTEXPR hamon::units::milliseconds<TypeParam>  ms_6(y);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 1LL *               1, ms_1.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 2LL *            1000, ms_2.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 3LL *       60 * 1000, ms_3.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 4LL *     3600 * 1000, ms_4.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 5LL *    86400 * 1000, ms_5.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 6LL * 31557600 * 1000, ms_6.value());

	HAMON_CONSTEXPR hamon::units::minutes<TypeParam>	min_1(ms);
	HAMON_CONSTEXPR hamon::units::minutes<TypeParam>	min_2(s);
	HAMON_CONSTEXPR hamon::units::minutes<float>		min_3(min);
	HAMON_CONSTEXPR hamon::units::minutes<TypeParam>	min_4(h);
	HAMON_CONSTEXPR hamon::units::minutes<float>		min_5(d);
	HAMON_CONSTEXPR hamon::units::minutes<TypeParam>	min_6(y);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1LL *      0.000016666666, (double)min_1.value(), 0.000000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2LL *      0.016666666666, (double)min_2.value(), 0.00000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 3LL *      1,                      min_3.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 4LL *     60,                      min_4.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 5LL *   1440,                      min_5.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 6LL * 525960,                      min_6.value());

	HAMON_CONSTEXPR hamon::units::hours<TypeParam>	h_1(ms);
	HAMON_CONSTEXPR hamon::units::hours<float>		h_2(s);
	HAMON_CONSTEXPR hamon::units::hours<TypeParam>	h_3(min);
	HAMON_CONSTEXPR hamon::units::hours<float>		h_4(h);
	HAMON_CONSTEXPR hamon::units::hours<TypeParam>	h_5(d);
	HAMON_CONSTEXPR hamon::units::hours<TypeParam>	h_6(y);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1LL *    0.0000002777777, (double)h_1.value(), 0.0000000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2LL *    0.0002777777777, (double)h_2.value(), 0.0000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3LL *    0.0166666666666, (double)h_3.value(), 0.000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 4LL *    1,                       h_4.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 5LL *   24,                       h_5.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 6LL * 8766,                       h_6.value());

	HAMON_CONSTEXPR hamon::units::days<TypeParam>	d_1(ms);
	HAMON_CONSTEXPR hamon::units::days<TypeParam>	d_2(s);
	HAMON_CONSTEXPR hamon::units::days<TypeParam>	d_3(min);
	HAMON_CONSTEXPR hamon::units::days<float>		d_4(h);
	HAMON_CONSTEXPR hamon::units::days<float>		d_5(d);
	HAMON_CONSTEXPR hamon::units::days<float>		d_6(y);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1LL *   0.00000001157407, (double)d_1.value(), 0.00000000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2LL *   0.00001157407,    (double)d_2.value(), 0.00000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3LL *   0.00069444444,    (double)d_3.value(), 0.000000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 4LL *   0.04166666666,    (double)d_4.value(), 0.00000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 5LL *   1,                        d_5.value());
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  ( 6LL * 365.25,                     d_6.value());
}

TYPED_TEST(UnitsTest, TorqueTest)
{
	using newton_metres = hamon::units::newton_metres<TypeParam>;
	using newtons       = hamon::units::newtons<TypeParam>;
	using metres        = hamon::units::metres<TypeParam>;
	using kilograms     = hamon::units::kilograms<TypeParam>;
	using seconds       = hamon::units::seconds<TypeParam>;

	{
		// N・m
		HAMON_CONSTEXPR_OR_CONST auto a = newtons(4) * metres(5);
		static_assert(std::is_same<decltype(a), const newton_metres>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, a.value());
	}
	{
		// m^2・kg・s^-2
		HAMON_CONSTEXPR_OR_CONST auto a = metres(2) * metres(3) * kilograms(4) / (seconds(2) * seconds(3));
		static_assert(std::is_same<decltype(a), const newton_metres>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, a.value());
	}
}

TYPED_TEST(UnitsTest, VelocityTest)
{
	using metres                 = hamon::units::metres<TypeParam>;
	using centimetres            = hamon::units::centimetres<TypeParam>;
	using kilometres             = hamon::units::kilometres<TypeParam>;
	using feet                   = hamon::units::feet<TypeParam>;
	using miles                  = hamon::units::miles<TypeParam>;

	using seconds                = hamon::units::seconds<TypeParam>;
	using hours                  = hamon::units::hours<TypeParam>;
	
	using metres_per_second      = hamon::units::metres_per_second<TypeParam>;
	using centimetres_per_second = hamon::units::centimetres_per_second<TypeParam>;
	using kilometres_per_hour    = hamon::units::kilometres_per_hour<TypeParam>;
	using feet_per_second        = hamon::units::feet_per_second<TypeParam>;
	using miles_per_hour         = hamon::units::miles_per_hour<TypeParam>;

	{
		HAMON_CONSTEXPR_OR_CONST auto v = metres(10) / seconds(2);
		static_assert(std::is_same<decltype(v), const metres_per_second>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, v.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto v = centimetres(10) / seconds(5);
		static_assert(std::is_same<decltype(v), const centimetres_per_second>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto v = kilometres(120) / hours(2);
		static_assert(std::is_same<decltype(v), const kilometres_per_hour>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(60, (double)v.value(), 0.00001);
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto v = feet(12) / seconds(4);
		static_assert(std::is_same<decltype(v), const feet_per_second>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto v = miles(60) / hours(3);
		static_assert(std::is_same<decltype(v), const miles_per_hour>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(20, (double)v.value(), 0.00000000000001);
	}
}

TYPED_TEST(UnitsTest, VolumeTest)
{
	using metres       = hamon::units::metres<TypeParam>;
	using inches       = hamon::units::inches<TypeParam>;
	using decimetre    = hamon::units::decimetre<TypeParam>;
	using cubic_metres = hamon::units::cubic_metres<TypeParam>;
	using cubic_inches = hamon::units::cubic_inches<TypeParam>;
	using litres       = hamon::units::litres<TypeParam>;

	{
		HAMON_CONSTEXPR_OR_CONST auto v = metres(2) * metres(3) * metres(4);
		static_assert(std::is_same<decltype(v), const cubic_metres>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(24, v.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto v = inches(3) * inches(4) * inches(5);
		static_assert(std::is_same<decltype(v), const cubic_inches>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(60, (double)v.value(), 0.0001);
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto v = decimetre(7) * decimetre(4) * decimetre(2);
		static_assert(std::is_same<decltype(v), const litres>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(56, (double)v.value(), 0.00000000000001);
	}
}

TYPED_TEST(UnitsTest, WavenumberTest)
{
	using metres                = hamon::units::metres<TypeParam>;
	using kilometres            = hamon::units::kilometres<TypeParam>;
	using centimetres           = hamon::units::centimetres<TypeParam>;

	using reciprocal_metres     = hamon::units::reciprocal_metres<TypeParam>;
	using reciprocal_kilometres = hamon::units::reciprocal_kilometres<TypeParam>;
	using kaysers               = hamon::units::kaysers<TypeParam>;

	{
		HAMON_CONSTEXPR_OR_CONST auto v = TypeParam(50) / metres(10);
		static_assert(std::is_same<decltype(v), const reciprocal_metres>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, v.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto v = 100 / kilometres(2);
		static_assert(std::is_same<decltype(v), const reciprocal_kilometres>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(50, v.value());
	}
	{
		HAMON_CONSTEXPR_OR_CONST auto v = 22.5f / centimetres(5);
		static_assert(std::is_same<decltype(v), const kaysers>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4.5, v.value());
	}
}

}	// namespace units_units_test
