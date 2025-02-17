﻿/**
 *	@file	double_factorial.hpp
 *
 *	@brief	double_factorial 関数の定義
 */

#ifndef HAMON_CMATH_DOUBLE_FACTORIAL_HPP
#define HAMON_CMATH_DOUBLE_FACTORIAL_HPP

#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/cstddef.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <bool Unsigned, hamon::size_t N>
struct max_double_factorial_t;

template <> struct max_double_factorial_t<false, 1> { static const unsigned int value = 7; };
template <> struct max_double_factorial_t<true,  1> { static const unsigned int value = 7; };
template <> struct max_double_factorial_t<false, 2> { static const unsigned int value = 11; };
template <> struct max_double_factorial_t<true,  2> { static const unsigned int value = 12; };
template <> struct max_double_factorial_t<false, 4> { static const unsigned int value = 19; };
template <> struct max_double_factorial_t<true,  4> { static const unsigned int value = 20; };
template <> struct max_double_factorial_t<false, 8> { static const unsigned int value = 33; };
template <> struct max_double_factorial_t<true,  8> { static const unsigned int value = 33; };

template <typename T>
HAMON_CXX11_CONSTEXPR unsigned int max_double_factorial() HAMON_NOEXCEPT
{
	return max_double_factorial_t<hamon::is_unsigned<T>::value, sizeof(T)>::value;
}

template <>
inline HAMON_CXX11_CONSTEXPR unsigned int max_double_factorial<float>() HAMON_NOEXCEPT
{
	return 56;
}
template <>
inline HAMON_CXX11_CONSTEXPR unsigned int max_double_factorial<double>() HAMON_NOEXCEPT
{
	return 300;
}
template <>
inline HAMON_CXX11_CONSTEXPR unsigned int max_double_factorial<long double>() HAMON_NOEXCEPT
{
	return 300;
}

static HAMON_CXX11_CONSTEXPR hamon::uintmax_t s_double_factorial_tbl_int[] =
{
	1,					 //  0!!
	1,					 //  1!!
	2,					 //  2!!
	3,					 //  3!!
	8,					 //  4!!
	15,					 //  5!!
	48,					 //  6!!
	105,				 //  7!!
	384,				 //  8!!
	945,				 //  9!!
	3840,				 // 10!!
	10395,				 // 11!!
	46080,				 // 12!!
	135135,				 // 13!!
	645120,				 // 14!!
	2027025,			 // 15!!
	10321920,			 // 16!!
	34459425,			 // 17!!
	185794560,			 // 18!!
	654729075,			 // 19!!
	3715891200,			 // 20!!
	13749310575,		 // 21!!
	81749606400,		 // 22!!
	316234143225,		 // 23!!
	1961990553600,		 // 24!!
	7905853580625,		 // 25!!
	51011754393600,		 // 26!!
	213458046676875,	 // 27!!
	1428329123020800,	 // 28!!
	6190283353629375,	 // 29!!
	42849873690624000,	 // 30!!
	191898783962510625,	 // 31!!
	1371195958099968000, // 32!!
	6332659870762850625, // 33!!
};

template <HAMON_CONSTRAINED_PARAM(hamon::integral, T)>
HAMON_CXX11_CONSTEXPR T
unchecked_double_factorial_impl(unsigned int n, hamon::detail::overload_priority<2>) HAMON_NOEXCEPT
{
	return static_cast<T>(s_double_factorial_tbl_int[n]);
}

static HAMON_CXX11_CONSTEXPR long double s_double_factorial_tbl_flt[] =
{
	1.0,                          //  0!!
	1.0,                          //  1!!
	2.0,                          //  2!!
	3.0,                          //  3!!
	8.0,                          //  4!!
	15.0,                         //  5!!
	48.0,                         //  6!!
	105.0,                        //  7!!
	384.0,                        //  8!!
	945.0,                        //  9!!
	3840.0,                       // 10!!
	10395.0,                      // 11!!
	46080.0,                      // 12!!
	135135.0,                     // 13!!
	645120.0,                     // 14!!
	2027025.0,                    // 15!!
	10321920.0,                   // 16!!
	34459425.0,                   // 17!!
	185794560.0,                  // 18!!
	654729075.0,                  // 19!!
	3715891200.0,                 // 20!!
	13749310575.0,                // 21!!
	81749606400.0,                // 22!!
	316234143225.0,               // 23!!
	1961990553600.0,              // 24!!
	7905853580625.0,              // 25!!
	51011754393600.0,             // 26!!
	213458046676875.0,            // 27!!
	1428329123020800.0,           // 28!!
	6190283353629375.0,           // 29!!
	42849873690624000.0,          // 30!!
	191898783962510625.0,         // 31!!
	1371195958099968000.0,        // 32!!
	6332659870762850625.0,        // 33!!
	46620662575398912000.0,       // 34!!
	221643095476699771875.0,      // 35!!
	1678343852714360832000.0,     // 36!!
	8200794532637891559375.0,     // 37!!
	6.3777066403145711616E+22,    // 38!!
	3.198309867728777708156E+23,  // 39!!
	2.55108265612582846464E+24,   // 40!!
	1.311307045768798860344E+25,  // 41!!
	1.071454715572847955149E+26,  // 42!!
	5.63862029680583509948E+26,   // 43!!
	4.714400748520531002655E+27,  // 44!!
	2.537379133562625794766E+28,  // 45!!
	2.168624344319444261221E+29,  // 46!!
	1.19256819277443412354E+30,   // 47!!
	1.040939685273333245386E+31,  // 48!!
	5.843584144594727205346E+31,  // 49!!
	5.204698426366666226931E+32,  // 50!!
	2.980227913743310874726E+33,  // 51!!
	2.706443181710666438004E+34,  // 52!!
	1.579520794283954763605E+35,  // 53!!
	1.461479318123759876522E+36,  // 54!!
	8.687364368561751199827E+36,  // 55!!
	8.184284181493055308524E+37,  // 56!!
	4.951797690080198183901E+38,  // 57!!
	4.746884825265972078944E+39,  // 58!!
	2.921560637147316928502E+40,  // 59!!
	2.848130895159583247366E+41,  // 60!!
	1.782151988659863326386E+42,  // 61!!
	1.765841154998941613367E+43,  // 62!!
	1.122755752855713895623E+44,  // 63!!
	1.130138339199322632555E+45,  // 64!!
	7.297912393562140321551E+45,  // 65!!
	7.458913038715529374863E+46,  // 66!!
	4.889601303686634015439E+47,  // 67!!
	5.072060866326559974907E+48,  // 68!!
	3.373824899543777470653E+49,  // 69!!
	3.550442606428591982435E+50,  // 70!!
	2.395415678676082004164E+51,  // 71!!
	2.556318676628586227353E+52,  // 72!!
	1.74865344543353986304E+53,   // 73!!
	1.891675820705153808241E+54,  // 74!!
	1.31149008407515489728E+55,   // 75!!
	1.437673623735916894263E+56,  // 76!!
	1.009847364737869270905E+57,  // 77!!
	1.121385426514015177525E+58,  // 78!!
	7.977794181429167240152E+58,  // 79!!
	8.971083412112121420203E+59,  // 80!!
	6.462013286957625464523E+60,  // 81!!
	7.356288397931939564567E+61,  // 82!!
	5.363471028174829135554E+62,  // 83!!
	6.179282254262829234236E+63,  // 84!!
	4.558950373948604765221E+64,  // 85!!
	5.314182738666033141443E+65,  // 86!!
	3.966286825335286145742E+66,  // 87!!
	4.67648081002610916447E+67,   // 88!!
	3.529995274548404669711E+68,  // 89!!
	4.208832729023498248023E+69,  // 90!!
	3.212295699839048249437E+70,  // 91!!
	3.872126110701618388181E+71,  // 92!!
	2.987435000850314871976E+72,  // 93!!
	3.63979854405952128489E+73,   // 94!!
	2.838063250807799128377E+74,  // 95!!
	3.494206602297140433495E+75,  // 96!!
	2.752921353283565154526E+76,  // 97!!
	3.424322470251197624825E+77,  // 98!!
	2.725392139750729502981E+78,  // 99!!
	3.424322470251197624825E+79,  //100!!
	2.752646061148236798011E+80,  //101!!
	3.492808919656221577321E+81,  //102!!
	2.835225442982683901951E+82,  //103!!
	3.632521276442470440414E+83,  //104!!
	2.976986715131818097048E+84,  //105!!
	3.850472553029018666839E+85,  //106!!
	3.185375785191045363842E+86,  //107!!
	4.158510357271340160186E+87,  //108!!
	3.472059605858239446588E+88,  //109!!
	4.574361392998474176205E+89,  //110!!
	3.853986162502645785712E+90,  //111!!
	5.123284760158291077349E+91,  //112!!
	4.355004363627989737855E+92,  //113!!
	5.840544626580451828178E+93,  //114!!
	5.008255018172188198533E+94,  //115!!
	6.775031766833324120686E+95,  //116!!
	5.859658371261460192284E+96,  //117!!
	7.99453748486332246241E+97,   //118!!
	6.972993461801137628817E+98,  //119!!
	9.593444981835986954892E+99,  //120!!
	8.437322088779376530869E+100, //121!!
	1.170400287783990408497E+102, //122!!
	1.037790616919863313297E+103, //123!!
	1.451296356852148106536E+104, //124!!
	1.297238271149829141621E+105, //125!!
	1.828633409633706614235E+106, //126!!
	1.647492604360283009859E+107, //127!!
	2.340650764331144466221E+108, //128!!
	2.125265459624765082718E+109, //129!!
	3.042845993630487806088E+110, //130!!
	2.78409775210844225836E+111,  //131!!
	4.016556711592243904036E+112, //132!!
	3.702850010304228203619E+113, //133!!
	5.382185993533606831408E+114, //134!!
	4.998847513910708074886E+115, //135!!
	7.319772951205705290715E+116, //136!!
	6.848421094057670062594E+117, //137!!
	1.010128667266387330119E+119, //138!!
	9.519305320740161387006E+119, //139!!
	1.414180134172942262166E+121, //140!!
	1.342222050224362755568E+122, //141!!
	2.008135790525578012276E+123, //142!!
	1.919377531820838740462E+124, //143!!
	2.891715538356832337677E+125, //144!!
	2.78309742114021617367E+126,  //145!!
	4.221904686000975213009E+127, //146!!
	4.091153209076117775295E+128, //147!!
	6.248418935281443315253E+129, //148!!
	6.095818281523415485189E+130, //149!!
	9.37262840292216497288E+131,  //150!!
	9.204685605100357382636E+132, //151!!
	1.424639517244169075878E+134, //152!!
	1.408316897580354679543E+135, //153!!
	2.193944856556020376852E+136, //154!!
	2.182891191249549753292E+137, //155!!
	3.422553976227391787889E+138, //156!!
	3.427139170261793112668E+139, //157!!
	5.407635282439279024864E+140, //158!!
	5.449151280716251049143E+141, //159!!
	8.652216451902846439782E+142, //160!!
	8.77313356195316418912E+143,  //161!!
	1.401659065208261123245E+145, //162!!
	1.430020770598365762827E+146, //163!!
	2.298720866941548242121E+147, //164!!
	2.359534271487303508664E+148, //165!!
	3.815876639122970081922E+149, //166!!
	3.940422233383796859469E+150, //167!!
	6.410672753726589737628E+151, //168!!
	6.659313574418616692502E+152, //169!!
	1.089814368133520255397E+154, //170!!
	1.138742621225583454418E+155, //171!!
	1.874480713189654839283E+156, //172!!
	1.970024734720259376143E+157, //173!!
	3.261596440949999420352E+158, //174!!
	3.44754328576045390825E+159,  //175!!
	5.740409736071998979819E+160, //176!!
	6.102151615796003417602E+161, //177!!
	1.021792933020815818408E+163, //178!!
	1.092285139227484611751E+164, //179!!
	1.839227279437468473134E+165, //180!!
	1.977036102001747147269E+166, //181!!
	3.347393648576192621104E+167, //182!!
	3.617976066663197279502E+168, //183!!
	6.159204313380194422831E+169, //184!!
	6.693255723326914967079E+170, //185!!
	1.145612002288716162647E+172, //186!!
	1.251638820262133098844E+173, //187!!
	2.153750564302786385775E+174, //188!!
	2.365597370295431556815E+175, //189!!
	4.092126072175294132973E+176, //190!!
	4.518290977264274273516E+177, //191!!
	7.856882058576564735309E+178, //192!!
	8.720301586120049347886E+179, //193!!
	1.52423511936385355865E+181,  //194!!
	1.700458809293409622838E+182, //195!!
	2.987500833953152974954E+183, //196!!
	3.349903854308016956991E+184, //197!!
	5.915251651227242890409E+185, //198!!
	6.666308670072953744411E+186, //199!!
	1.183050330245448578082E+188, //200!!
	1.339928042684663702627E+189, //201!!
	2.389761667095806127725E+190, //202!!
	2.720053926649867316332E+191, //203!!
	4.875113800875444500559E+192, //204!!
	5.576110549632227998481E+193, //205!!
	1.004273442980341567115E+195, //206!!
	1.154254883773871195686E+196, //207!!
	2.0888887613991104596E+197,   //208!!
	2.412392707087390798983E+198, //209!!
	4.386666398938131965159E+199, //210!!
	5.090148611954394585854E+200, //211!!
	9.299732765748839766137E+201, //212!!
	1.084201654346286046787E+203, //213!!
	1.990142811870251709953E+204, //214!!
	2.331033556844515000592E+205, //215!!
	4.298708473639743693499E+206, //216!!
	5.058342818352597551284E+207, //217!!
	9.371184472534641251829E+208, //218!!
	1.107777077219218863731E+210, //219!!
	2.061660583957621075402E+211, //220!!
	2.448187340654473688846E+212, //221!!
	4.576886496385918787393E+213, //222!!
	5.459457769659476326126E+214, //223!!
	1.025222575190445808376E+216, //224!!
	1.228377998173382173378E+217, //225!!
	2.31700301993040752693E+218,  //226!!
	2.788418055853577533569E+219, //227!!
	5.2827668854413291614E+220,   //228!!
	6.385477347904692551873E+221, //229!!
	1.215036383651505707122E+223, //230!!
	1.475045267365983979483E+224, //231!!
	2.818884410071493240523E+225, //232!!
	3.436855472962742672195E+226, //233!!
	6.596189519567294182824E+227, //234!!
	8.076610361462445279658E+228, //235!!
	1.556700726617881427147E+230, //236!!
	1.914156655666599531279E+231, //237!!
	3.704947729350557796609E+232, //238!!
	4.574834407043172879756E+233, //239!!
	8.891874550441338711861E+234, //240!!
	1.102535092097404664021E+236, //241!!
	2.15183364120680396827E+237,  //242!!
	2.679160273796693333572E+238, //243!!
	5.250474084544601682579E+239, //244!!
	6.563942670801898667251E+240, //245!!
	1.291616624797972013915E+242, //246!!
	1.621293839688068970811E+243, //247!!
	3.203209229498970594508E+244, //248!!
	4.037021660823291737319E+245, //249!!
	8.00802307374742648627E+246,  //250!!
	1.013292436866646226067E+248, //251!!
	2.01802181458435147454E+249,  //252!!
	2.56362986527261495195E+250,  //253!!
	5.125775409044252745332E+251, //254!!
	6.537256156445168127472E+252, //255!!
	1.312198504715328702805E+254, //256!!
	1.68007483220640820876E+255,  //257!!
	3.385472142165548053237E+256, //258!!
	4.351393815414597260689E+257, //259!!
	8.802227569630424938416E+258, //260!!
	1.13571378582320988504E+260,  //261!!
	2.306183623243171333865E+261, //262!!
	2.986927256715041997655E+262, //263!!
	6.088324765361972321403E+263, //264!!
	7.915357230294861293786E+264, //265!!
	1.619494387586284637493E+266, //266!!
	2.113400380488727965441E+267, //267!!
	4.340244958731242828482E+268, //268!!
	5.685047023514678227036E+269, //269!!
	1.17186613885743556369E+271,  //270!!
	1.540647743372477799527E+272, //271!!
	3.187475897692224733237E+273, //272!!
	4.205968339406864392708E+274, //273!!
	8.73368395967669576907E+275,  //274!!
	1.156641293336887707995E+277, //275!!
	2.410496772870768032263E+278, //276!!
	3.203896382543178951145E+279, //277!!
	6.701181028580735129692E+280, //278!!
	8.938870907295469273695E+281, //279!!
	1.876330688002605836314E+283, //280!!
	2.511822724950026865908E+284, //281!!
	5.291252540167348458405E+285, //282!!
	7.10845831160857603052E+286,  //283!!
	1.502715721407526962187E+288, //284!!
	2.025910618808444168698E+289, //285!!
	4.297766963225527111855E+290, //286!!
	5.814363475980234764164E+291, //287!!
	1.237756885408951808214E+293, //288!!
	1.680351044558287846843E+294, //289!!
	3.589494967685960243821E+295, //290!!
	4.889821539664617634314E+296, //291!!
	1.048132530564300391196E+298, //292!!
	1.432717711121732966854E+299, //293!!
	3.081509639859043150116E+300, //294!!
	4.22651724780911225222E+301,  //295!!
	9.121268533982767724342E+302, //296!!
	1.255275622599306338909E+304, //297!!
	2.718138023126864781854E+305, //298!!
	3.753274111571925953339E+306, //299!!
	8.154414069380594345562E+307, //300!!
};

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
HAMON_CXX11_CONSTEXPR T
unchecked_double_factorial_impl(unsigned int n, hamon::detail::overload_priority<1>) HAMON_NOEXCEPT
{
	return static_cast<T>(s_double_factorial_tbl_flt[n]);
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
unchecked_double_factorial(unsigned int n) HAMON_NOEXCEPT
{
	return unchecked_double_factorial_impl<T>(n, hamon::detail::overload_priority<2>{});
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
double_factorial_impl(unsigned int n) HAMON_NOEXCEPT
{
	return
		n > max_double_factorial<T>() ?
			hamon::numeric_limits<T>::infinity() :
		unchecked_double_factorial<T>(n);
}

}	// namespace detail

/**
 *	@brief	二重階乗を計算する
 *
 *	二重階乗 n!! は、与えられた自然数 n に対し、
 *	1 から n まで n と同じ偶奇性を持つものだけを全て掛けた積を言う。
 *	n = 0 のときは 1 と定義する。
 *
 *	結果の値がオーバーフローする場合、戻り値の型が
 *	・浮動小数点数型なら inf
 *	・整数型なら 0
 *	を返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR Arithmetic
double_factorial(unsigned int n) HAMON_NOEXCEPT
{
	return detail::double_factorial_impl<Arithmetic>(n);
}

}	// namespace hamon

#endif // HAMON_CMATH_DOUBLE_FACTORIAL_HPP
