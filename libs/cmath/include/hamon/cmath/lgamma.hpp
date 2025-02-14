/**
 *	@file	lgamma.hpp
 *
 *	@brief	lgamma 関数の定義
 */

#ifndef HAMON_CMATH_LGAMMA_HPP
#define HAMON_CMATH_LGAMMA_HPP

#include <hamon/cmath/fabs.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/is_integer.hpp>
#include <hamon/cmath/log.hpp>
#include <hamon/cmath/sin.hpp>
#include <hamon/cmath/trunc.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/numbers/pi.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CXX11_CONSTEXPR float
lgamma_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_lgammaf(x);
}

inline HAMON_CXX11_CONSTEXPR double
lgamma_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_lgamma(x);
}

inline HAMON_CXX11_CONSTEXPR long double
lgamma_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_lgammal(x);
}

#else

template<typename T>
HAMON_CXX11_CONSTEXPR T
lgamma_unchecked_ct_3(T x, T y)
{
	return x < 0 ?
		hamon::log(hamon::numbers::pi_fn<T>() / hamon::fabs(x * hamon::sin(x * hamon::numbers::pi_fn<T>()))) - y :
		y;
}

template<typename T>
HAMON_CXX11_CONSTEXPR T
lgamma_unchecked_ct_2_d_1(T x, T w, T v, T t)
{
	return lgamma_unchecked_ct_3(x, static_cast<T>(
		(((((-0.00163312359200500807  * t + 8.3644533703385956e-4)  * t +
			 -5.9518947575728181e-4)  * t + 7.9365057505415415e-4)  * t +
			 -0.00277777777735463043) * t + 0.08333333333333309869) * v +
			  0.91893853320467274178 +
		((w - T(0.5)) * hamon::log(w) - w)));
}

template<typename T>
HAMON_CXX11_CONSTEXPR T
lgamma_unchecked_ct_2_d(T x, T w, T v)
{
	return lgamma_unchecked_ct_2_d_1(x, w, v, v * v);
}

template<typename T>
HAMON_CXX11_CONSTEXPR T
lgamma_unchecked_ct_2_c_1(T x, T t, int k)
{
	return lgamma_unchecked_ct_3(x, static_cast<T>(
		k == 0 ? (((((((((((
			1.16333640008e-8       * t + -8.33156123568e-8)      * t +
			3.832869977018e-7)     * t + -1.5814047847688e-6)    * t +
			6.50106723241e-6)      * t + -2.74514060128677e-5)   * t +
			1.209015360925566e-4)  * t + -5.666333178228163e-4)  * t +
			0.0029294103665559733) * t + -0.0180340086069185819) * t +
			0.1651788780501166204) * t +  1.1031566406452431944) * t +
			1.2009736023470742248 :
		k == 1 ? (((((((((((
			1.3842760642e-9        * t + -6.9417501176e-9)       * t +
			3.42976459827e-8)      * t + -1.785317236779e-7)     * t +
			9.525947257118e-7)     * t + -5.2483007560905e-6)    * t +
			3.02364659535708e-5)   * t + -1.858396115473822e-4)  * t +
			0.0012634378559425382) * t + -0.0102594702201954322) * t +
			0.1243625515195050218) * t +  1.3888709263595291174) * t +
			2.4537365708424422209 :
		k == 2 ? (((((((((((
			1.298977078e-10        * t + -8.02957489e-10)        * t +
			4.945484615e-9)        * t + -3.17563534834e-8)      * t +
			2.092136698089e-7)     * t + -1.4252023958462e-6)    * t +
			1.01652510114008e-5)   * t + -7.74550502862323e-5)   * t +
			6.537746948291078e-4)  * t + -0.006601491253552183)  * t +
			0.0996711934948138193) * t +  1.6110931485817511402) * t +
			3.9578139676187162939 :
		k == 3 ? (((((((((((
			1.83995642e-11         * t + -1.353537034e-10)       * t +
			9.984676809e-10)       * t + -7.6346363974e-9)       * t +
			5.99311464148e-8)      * t + -4.868554120177e-7)     * t +
			4.1441957716669e-6)    * t + -3.77160856623282e-5)   * t +
			3.805693126824884e-4)  * t + -0.0045979851178130194) * t +
			0.0831422678749791178) * t +  1.7929113303999329439) * t +
			5.6625620598571415285 :
		(((((((((((
			3.4858778e-12          * t + -2.97587783e-11)        * t +
			2.557677575e-10)       * t + -2.2705728282e-9)       * t +
			2.0702499245e-8)       * t + -1.954426390917e-7)     * t +
			1.9343161886722e-6)    * t + -2.0479024910257e-5)    * t +
			2.405181940241215e-4)  * t + -0.0033842087561074799) * t +
			0.0713079483483518997) * t +  1.9467574842460867884) * t +
			7.5343642367587329552));
}

template<typename T>
HAMON_CXX11_CONSTEXPR T
lgamma_unchecked_ct_2_c(T x, T w, int k)
{
	return lgamma_unchecked_ct_2_c_1(x, w - (static_cast<T>(k) + T(3.5)), k);
}

template<typename T>
HAMON_CXX11_CONSTEXPR T
lgamma_unchecked_ct_2_b_2(T x, T t, int k)
{
	return lgamma_unchecked_ct_3(x, static_cast<T>(
		k == 0 ? ((((((((((((
			-4.587497028e-11         * t +  1.902363396e-10)        * t +
			 8.6377323367e-10)       * t +  1.15513678861e-8)       * t +
			-2.556403058605e-8)      * t + -1.5236723372486e-7)     * t +
			-3.1680510638574e-6)     * t +  1.22903704923381e-6)    * t +
			 2.334372474572637e-5)   * t +  0.00111544038088797696) * t +
			 0.00344717051723468982) * t +  0.03198287045148788384) * t +
			-0.32705333652955399526) * t +  0.40120442440953927615 :
		k == 1 ? ((((((((((((
			-5.184290387e-11         * t + -8.3355121068e-10)       * t +
			-2.56167239813e-9)       * t +  1.455875381397e-8)      * t +
			 1.3512178394703e-7)     * t +  2.9898826810905e-7)     * t +
			-3.58107254612779e-6)    * t + -2.445260816156224e-5)   * t +
			-4.417127762011821e-5)   * t +  0.00112859455189416567) * t +
			 0.00804694454346728197) * t +  0.04919775747126691372) * t +
			-0.24818372840948854178) * t +  0.11071780856646862561 :
		k == 2 ? ((((((((((((
			 3.0279161576e-10        * t +  1.60742167357e-9)       * t +
			-4.05596009522e-9)       * t + -5.089259920266e-8)      * t +
			-2.029496209743e-8)      * t +  1.35130272477793e-6)    * t +
			 3.91430041115376e-6)    * t + -2.871505678061895e-5)   * t +
			-2.3052137536922035e-4)  * t +  4.5534656385400747e-4)  * t +
			 0.01153444585593040046) * t +  0.07924014651650476036) * t +
			-0.12152192626936502982) * t + -0.07916438300260539592 :
		k == 3 ? ((((((((((((
			-5.091914958e-10         * t + -1.15274986907e-9)       * t +
			 1.237873512188e-8)      * t +  2.937383549209e-8)      * t +
			-3.0621450667958e-7)     * t + -7.7409414949954e-7)     * t +
			 8.16753874325579e-6)    * t +  2.412433382517375e-5)   * t +
			-2.60612176060637e-4)    * t + -9.1000087658659231e-4)  * t +
			 0.01068093850598380797) * t +  0.11395654404408482305) * t +
			 0.07209569059984075595) * t + -0.10971041451764266684 :
		k == 4 ? ((((((((((((
			 4.0119897187e-10        * t + -1.3224526679e-10)       * t +
			-1.002723190355e-8)      * t +  2.569249716518e-8)      * t +
			 2.0336011868466e-7)     * t + -1.1809768272606e-6)     * t +
			-3.00660303810663e-6)    * t +  4.402212897757763e-5)   * t +
			-1.462405876235375e-5)   * t + -0.0016487379559600128)  * t +
			 0.00513927520866443706) * t +  0.13843580753590579416) * t +
			 0.32730190978254056722) * t +  0.08588339725978624973 :
		k == 5 ? ((((((((((((
			-1.5413428348e-10        * t +  6.4905779353e-10)       * t +
			 1.60702811151e-9)       * t + -2.655645793815e-8)      * t +
			 7.619544277956e-8)      * t +  4.7604380765353e-7)     * t +
			-4.90748870866195e-6)    * t +  8.21513040821212e-6)    * t +
			 1.4804944070262948e-4)  * t + -0.00122152255762163238) * t +
			-8.7425289205498532e-4)  * t +  0.1443870369965796831)  * t +
			 0.61315889733595543766) * t +  0.55513708159976477557 :
		((((((((((((
			 1.049740243e-11         * t + -2.5832017855e-10)       * t +
			 1.39591845075e-9)       * t + -2.1177278325e-10)       * t +
			-5.082950464905e-8)      * t +  3.7801785193343e-7)     * t +
			-7.3982266659145e-7)     * t + -1.088918441519888e-5)   * t +
			 1.2491810452478905e-4)  * t + -4.9171790705139895e-4)  * t +
			-0.0042570708944826646)  * t +  0.13595080378472757216) * t +
			 0.89518356003149514744) * t +  1.31073912535196238583));
}

template<typename T>
HAMON_CXX11_CONSTEXPR T
lgamma_unchecked_ct_2_b_1(T x, T t, int k)
{
	return lgamma_unchecked_ct_2_b_2(x, t - (static_cast<T>(k) - T(3.5)), k);
}

template<typename T>
HAMON_CXX11_CONSTEXPR T
lgamma_unchecked_ct_2_b(T x, T t)
{
	return lgamma_unchecked_ct_2_b_1(x, t, static_cast<int>(hamon::trunc(t)) + 4);
}

template<typename T>
HAMON_CXX11_CONSTEXPR T
lgamma_unchecked_ct_2_a(T x, T w, int k)
{
	return lgamma_unchecked_ct_3(x, -hamon::log(static_cast<T>(
		k == 0 ? ((((((((((
			 9.967270908702825e-5    * w + -1.9831672170162227e-4)  * w +
			-0.00117085315349625822) * w +  0.00722012810948319552) * w +
			-0.0096221300936780297)  * w + -0.04219772092994235254) * w +
			 0.16653861065243609743) * w + -0.04200263501129018037) * w +
			-0.65587807152061930091) * w +  0.57721566490153514421) * w +
			 0.99999999999999999764) * w :
		((((((((((
			 4.67209725901142e-5     * w + -6.812300803992063e-5)   * w +
			-0.00132531159076610073) * w +  0.0073352117810720277)  * w +
			-0.00968095666383935949) * w + -0.0421764281187354028)  * w +
			 0.16653313644244428256) * w + -0.04200165481709274859) * w +
			-0.65587818792782740945) * w +  0.57721567315209190522) * w +
			 0.99999999973565236061) * w)));
}

template<typename T>
HAMON_CXX11_CONSTEXPR T
lgamma_unchecked_ct_1(T x, T w)
{
	return
		w < T(0.5) ? lgamma_unchecked_ct_2_a(x, w, w < T(0.25) ? 0 : 1) :
		w < T(3.5) ? lgamma_unchecked_ct_2_b(x, w - T(4.5) / (w + T(0.5))) :
		w < T(8.0) ? lgamma_unchecked_ct_2_c(x, w, static_cast<int>(hamon::trunc(w)) - 3) :
		             lgamma_unchecked_ct_2_d(x, w, T(1) / w);
}

template<typename T>
HAMON_CXX11_CONSTEXPR T
lgamma_unchecked_ct(T x)
{
	return lgamma_unchecked_ct_1(x, x < 0 ? -x : x);
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
lgamma_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
	{
		return std::lgamma(x);
	}
#endif
	return lgamma_unchecked_ct(x);
}

#endif

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
lgamma_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		x == 1 ||
		x == 2 ?
			FloatType(0) :
		hamon::iszero(x) ||
		hamon::isinf(x)  ||
		(x < 0 && hamon::is_integer(x)) ?
			hamon::numeric_limits<FloatType>::infinity() :
		lgamma_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	ガンマ関数の絶対値の自然対数 (loge) を計算します．
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x
 *
 *	@return	x のガンマ関数の絶対値の自然対数を返します。
 *
 *	x が 1       の場合、+0  を返す。
 *	x が 2       の場合、+0  を返す。
 *	x が ±0      の場合、+∞ を返す。
 *	x が 負の整数 の場合、+∞ を返す。
 *	x が ±∞      の場合、+∞ を返す。
 *	x が NaN     の場合、NaN を返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
lgamma(FloatType arg) HAMON_NOEXCEPT
{
	return detail::lgamma_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
lgamma(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::lgamma_impl(static_cast<double>(arg));
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
lgammaf(float arg) HAMON_NOEXCEPT
{
	return detail::lgamma_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
lgammal(long double arg) HAMON_NOEXCEPT
{
	return detail::lgamma_impl(arg);
}

}	// namespace hamon

#endif // HAMON_CMATH_LGAMMA_HPP
