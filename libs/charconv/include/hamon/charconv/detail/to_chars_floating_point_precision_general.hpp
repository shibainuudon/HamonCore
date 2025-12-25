/**
 *	@file	to_chars_floating_point_precision_general.hpp
 *
 *	@brief	to_chars_floating_point_precision_general の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_TO_CHARS_FLOATING_POINT_PRECISION_GENERAL_HPP
#define HAMON_CHARCONV_DETAIL_TO_CHARS_FLOATING_POINT_PRECISION_GENERAL_HPP

#include <hamon/charconv/to_chars_result.hpp>
#include <hamon/charconv/detail/ryu/d2fixed.hpp>
#include <hamon/algorithm/find.hpp>
#include <hamon/algorithm/find_if.hpp>
#include <hamon/algorithm/lower_bound.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/cstring/memcpy.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/ieee754/binary.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/assert.hpp>

namespace hamon
{

namespace detail
{

template <typename Floating>
struct general_precision_tables;

template <>
struct general_precision_tables<float>
{
	static constexpr int max_special_P() { return 7; }

	static uint32_t const* special_X_table()
	{
		static const uint32_t table[63] = { 0x38C73ABCu, 0x3A79096Bu, 0x3C1BA5E3u, 0x3DC28F5Cu, 0x3F733333u,
		0x4117FFFFu, 0x38D0AAA7u, 0x3A826AA8u, 0x3C230553u, 0x3DCBC6A7u, 0x3F7EB851u, 0x411F3333u, 0x42C6FFFFu,
		0x38D19C3Fu, 0x3A8301A7u, 0x3C23C211u, 0x3DCCB295u, 0x3F7FDF3Bu, 0x411FEB85u, 0x42C7E666u, 0x4479DFFFu,
		0x38D1B468u, 0x3A8310C1u, 0x3C23D4F1u, 0x3DCCCA2Du, 0x3F7FFCB9u, 0x411FFDF3u, 0x42C7FD70u, 0x4479FCCCu,
		0x461C3DFFu, 0x38D1B6D2u, 0x3A831243u, 0x3C23D6D4u, 0x3DCCCC89u, 0x3F7FFFACu, 0x411FFFCBu, 0x42C7FFBEu,
		0x4479FFAEu, 0x461C3FCCu, 0x47C34FBFu, 0x38D1B710u, 0x3A83126Au, 0x3C23D704u, 0x3DCCCCC6u, 0x3F7FFFF7u,
		0x411FFFFAu, 0x42C7FFF9u, 0x4479FFF7u, 0x461C3FFAu, 0x47C34FF9u, 0x497423F7u, 0x38D1B716u, 0x3A83126Eu,
		0x3C23D709u, 0x3DCCCCCCu, 0x3F7FFFFFu, 0x411FFFFFu, 0x42C7FFFFu, 0x4479FFFFu, 0x461C3FFFu, 0x47C34FFFu,
		0x497423FFu, 0x4B18967Fu };
		return table;
	}

	static constexpr int max_P() { return 39; }

	static uint32_t const* ordinary_X_table()
	{
		static const uint32_t table[44] = { 0x38D1B717u, 0x3A83126Eu, 0x3C23D70Au, 0x3DCCCCCCu, 0x3F7FFFFFu,
		0x411FFFFFu, 0x42C7FFFFu, 0x4479FFFFu, 0x461C3FFFu, 0x47C34FFFu, 0x497423FFu, 0x4B18967Fu, 0x4CBEBC1Fu,
		0x4E6E6B27u, 0x501502F8u, 0x51BA43B7u, 0x5368D4A5u, 0x551184E7u, 0x56B5E620u, 0x58635FA9u, 0x5A0E1BC9u,
		0x5BB1A2BCu, 0x5D5E0B6Bu, 0x5F0AC723u, 0x60AD78EBu, 0x6258D726u, 0x64078678u, 0x65A96816u, 0x6753C21Bu,
		0x69045951u, 0x6AA56FA5u, 0x6C4ECB8Fu, 0x6E013F39u, 0x6FA18F07u, 0x7149F2C9u, 0x72FC6F7Cu, 0x749DC5ADu,
		0x76453719u, 0x77F684DFu, 0x799A130Bu, 0x7B4097CEu, 0x7CF0BDC2u, 0x7E967699u, 0x7F7FFFFFu };
		return table;
	}
};

template <>
struct general_precision_tables<double>
{
	static constexpr int max_special_P() { return 15; }

	static uint64_t const* special_X_table()
	{
		static const uint64_t table[195] = { 0x3F18E757928E0C9Du, 0x3F4F212D77318FC5u, 0x3F8374BC6A7EF9DBu,
		0x3FB851EB851EB851u, 0x3FEE666666666666u, 0x4022FFFFFFFFFFFFu, 0x3F1A1554FBDAD751u, 0x3F504D551D68C692u,
		0x3F8460AA64C2F837u, 0x3FB978D4FDF3B645u, 0x3FEFD70A3D70A3D7u, 0x4023E66666666666u, 0x4058DFFFFFFFFFFFu,
		0x3F1A3387ECC8EB96u, 0x3F506034F3FD933Eu, 0x3F84784230FCF80Du, 0x3FB99652BD3C3611u, 0x3FEFFBE76C8B4395u,
		0x4023FD70A3D70A3Du, 0x4058FCCCCCCCCCCCu, 0x408F3BFFFFFFFFFFu, 0x3F1A368D04E0BA6Au, 0x3F506218230C7482u,
		0x3F847A9E2BCF91A3u, 0x3FB99945B6C3760Bu, 0x3FEFFF972474538Eu, 0x4023FFBE76C8B439u, 0x4058FFAE147AE147u,
		0x408F3F9999999999u, 0x40C387BFFFFFFFFFu, 0x3F1A36DA54164F19u, 0x3F506248748DF16Fu, 0x3F847ADA91B16DCBu,
		0x3FB99991361DC93Eu, 0x3FEFFFF583A53B8Eu, 0x4023FFF972474538u, 0x4058FFF7CED91687u, 0x408F3FF5C28F5C28u,
		0x40C387F999999999u, 0x40F869F7FFFFFFFFu, 0x3F1A36E20F35445Du, 0x3F50624D49814ABAu, 0x3F847AE09BE19D69u,
		0x3FB99998C2DA04C3u, 0x3FEFFFFEF39085F4u, 0x4023FFFF583A53B8u, 0x4058FFFF2E48E8A7u, 0x408F3FFEF9DB22D0u,
		0x40C387FF5C28F5C2u, 0x40F869FF33333333u, 0x412E847EFFFFFFFFu, 0x3F1A36E2D51EC34Bu, 0x3F50624DC5333A0Eu,
		0x3F847AE136800892u, 0x3FB9999984200AB7u, 0x3FEFFFFFE5280D65u, 0x4023FFFFEF39085Fu, 0x4058FFFFEB074A77u,
		0x408F3FFFE5C91D14u, 0x40C387FFEF9DB22Du, 0x40F869FFEB851EB8u, 0x412E847FE6666666u, 0x416312CFEFFFFFFFu,
		0x3F1A36E2E8E94FFCu, 0x3F50624DD191D1FDu, 0x3F847AE145F6467Du, 0x3FB999999773D81Cu, 0x3FEFFFFFFD50CE23u,
		0x4023FFFFFE5280D6u, 0x4058FFFFFDE7210Bu, 0x408F3FFFFD60E94Eu, 0x40C387FFFE5C91D1u, 0x40F869FFFDF3B645u,
		0x412E847FFD70A3D7u, 0x416312CFFE666666u, 0x4197D783FDFFFFFFu, 0x3F1A36E2EAE3F7A7u, 0x3F50624DD2CE7AC8u,
		0x3F847AE14782197Bu, 0x3FB9999999629FD9u, 0x3FEFFFFFFFBB47D0u, 0x4023FFFFFFD50CE2u, 0x4058FFFFFFCA501Au,
		0x408F3FFFFFBCE421u, 0x40C387FFFFD60E94u, 0x40F869FFFFCB923Au, 0x412E847FFFBE76C8u, 0x416312CFFFD70A3Du,
		0x4197D783FFCCCCCCu, 0x41CDCD64FFBFFFFFu, 0x3F1A36E2EB16A205u, 0x3F50624DD2EE2543u, 0x3F847AE147A9AE94u,
		0x3FB9999999941A39u, 0x3FEFFFFFFFF920C8u, 0x4023FFFFFFFBB47Du, 0x4058FFFFFFFAA19Cu, 0x408F3FFFFFF94A03u,
		0x40C387FFFFFBCE42u, 0x40F869FFFFFAC1D2u, 0x412E847FFFF97247u, 0x416312CFFFFBE76Cu, 0x4197D783FFFAE147u,
		0x41CDCD64FFF99999u, 0x4202A05F1FFBFFFFu, 0x3F1A36E2EB1BB30Fu, 0x3F50624DD2F14FE9u, 0x3F847AE147ADA3E3u,
		0x3FB9999999990CDCu, 0x3FEFFFFFFFFF5014u, 0x4023FFFFFFFF920Cu, 0x4058FFFFFFFF768Fu, 0x408F3FFFFFFF5433u,
		0x40C387FFFFFF94A0u, 0x40F869FFFFFF79C8u, 0x412E847FFFFF583Au, 0x416312CFFFFF9724u, 0x4197D783FFFF7CEDu,
		0x41CDCD64FFFF5C28u, 0x4202A05F1FFF9999u, 0x42374876E7FF7FFFu, 0x3F1A36E2EB1C34C3u, 0x3F50624DD2F1A0FAu,
		0x3F847AE147AE0938u, 0x3FB9999999998B86u, 0x3FEFFFFFFFFFEE68u, 0x4023FFFFFFFFF501u, 0x4058FFFFFFFFF241u,
		0x408F3FFFFFFFEED1u, 0x40C387FFFFFFF543u, 0x40F869FFFFFFF294u, 0x412E847FFFFFEF39u, 0x416312CFFFFFF583u,
		0x4197D783FFFFF2E4u, 0x41CDCD64FFFFEF9Du, 0x4202A05F1FFFF5C2u, 0x42374876E7FFF333u, 0x426D1A94A1FFEFFFu,
		0x3F1A36E2EB1C41BBu, 0x3F50624DD2F1A915u, 0x3F847AE147AE135Au, 0x3FB9999999999831u, 0x3FEFFFFFFFFFFE3Du,
		0x4023FFFFFFFFFEE6u, 0x4058FFFFFFFFFEA0u, 0x408F3FFFFFFFFE48u, 0x40C387FFFFFFFEEDu, 0x40F869FFFFFFFEA8u,
		0x412E847FFFFFFE52u, 0x416312CFFFFFFEF3u, 0x4197D783FFFFFEB0u, 0x41CDCD64FFFFFE5Cu, 0x4202A05F1FFFFEF9u,
		0x42374876E7FFFEB8u, 0x426D1A94A1FFFE66u, 0x42A2309CE53FFEFFu, 0x3F1A36E2EB1C4307u, 0x3F50624DD2F1A9E4u,
		0x3F847AE147AE145Eu, 0x3FB9999999999975u, 0x3FEFFFFFFFFFFFD2u, 0x4023FFFFFFFFFFE3u, 0x4058FFFFFFFFFFDCu,
		0x408F3FFFFFFFFFD4u, 0x40C387FFFFFFFFE4u, 0x40F869FFFFFFFFDDu, 0x412E847FFFFFFFD5u, 0x416312CFFFFFFFE5u,
		0x4197D783FFFFFFDEu, 0x41CDCD64FFFFFFD6u, 0x4202A05F1FFFFFE5u, 0x42374876E7FFFFDFu, 0x426D1A94A1FFFFD7u,
		0x42A2309CE53FFFE6u, 0x42D6BCC41E8FFFDFu, 0x3F1A36E2EB1C4328u, 0x3F50624DD2F1A9F9u, 0x3F847AE147AE1477u,
		0x3FB9999999999995u, 0x3FEFFFFFFFFFFFFBu, 0x4023FFFFFFFFFFFDu, 0x4058FFFFFFFFFFFCu, 0x408F3FFFFFFFFFFBu,
		0x40C387FFFFFFFFFDu, 0x40F869FFFFFFFFFCu, 0x412E847FFFFFFFFBu, 0x416312CFFFFFFFFDu, 0x4197D783FFFFFFFCu,
		0x41CDCD64FFFFFFFBu, 0x4202A05F1FFFFFFDu, 0x42374876E7FFFFFCu, 0x426D1A94A1FFFFFBu, 0x42A2309CE53FFFFDu,
		0x42D6BCC41E8FFFFCu, 0x430C6BF52633FFFBu };
		return table;
	}

	static constexpr int max_P() { return 309; }

	static uint64_t const* ordinary_X_table()
	{
		static const uint64_t table[314] = { 0x3F1A36E2EB1C432Cu, 0x3F50624DD2F1A9FBu, 0x3F847AE147AE147Au,
		0x3FB9999999999999u, 0x3FEFFFFFFFFFFFFFu, 0x4023FFFFFFFFFFFFu, 0x4058FFFFFFFFFFFFu, 0x408F3FFFFFFFFFFFu,
		0x40C387FFFFFFFFFFu, 0x40F869FFFFFFFFFFu, 0x412E847FFFFFFFFFu, 0x416312CFFFFFFFFFu, 0x4197D783FFFFFFFFu,
		0x41CDCD64FFFFFFFFu, 0x4202A05F1FFFFFFFu, 0x42374876E7FFFFFFu, 0x426D1A94A1FFFFFFu, 0x42A2309CE53FFFFFu,
		0x42D6BCC41E8FFFFFu, 0x430C6BF52633FFFFu, 0x4341C37937E07FFFu, 0x4376345785D89FFFu, 0x43ABC16D674EC7FFu,
		0x43E158E460913CFFu, 0x4415AF1D78B58C3Fu, 0x444B1AE4D6E2EF4Fu, 0x4480F0CF064DD591u, 0x44B52D02C7E14AF6u,
		0x44EA784379D99DB4u, 0x45208B2A2C280290u, 0x4554ADF4B7320334u, 0x4589D971E4FE8401u, 0x45C027E72F1F1281u,
		0x45F431E0FAE6D721u, 0x46293E5939A08CE9u, 0x465F8DEF8808B024u, 0x4693B8B5B5056E16u, 0x46C8A6E32246C99Cu,
		0x46FED09BEAD87C03u, 0x4733426172C74D82u, 0x476812F9CF7920E2u, 0x479E17B84357691Bu, 0x47D2CED32A16A1B1u,
		0x48078287F49C4A1Du, 0x483D6329F1C35CA4u, 0x48725DFA371A19E6u, 0x48A6F578C4E0A060u, 0x48DCB2D6F618C878u,
		0x4911EFC659CF7D4Bu, 0x49466BB7F0435C9Eu, 0x497C06A5EC5433C6u, 0x49B18427B3B4A05Bu, 0x49E5E531A0A1C872u,
		0x4A1B5E7E08CA3A8Fu, 0x4A511B0EC57E6499u, 0x4A8561D276DDFDC0u, 0x4ABABA4714957D30u, 0x4AF0B46C6CDD6E3Eu,
		0x4B24E1878814C9CDu, 0x4B5A19E96A19FC40u, 0x4B905031E2503DA8u, 0x4BC4643E5AE44D12u, 0x4BF97D4DF19D6057u,
		0x4C2FDCA16E04B86Du, 0x4C63E9E4E4C2F344u, 0x4C98E45E1DF3B015u, 0x4CCF1D75A5709C1Au, 0x4D03726987666190u,
		0x4D384F03E93FF9F4u, 0x4D6E62C4E38FF872u, 0x4DA2FDBB0E39FB47u, 0x4DD7BD29D1C87A19u, 0x4E0DAC74463A989Fu,
		0x4E428BC8ABE49F63u, 0x4E772EBAD6DDC73Cu, 0x4EACFA698C95390Bu, 0x4EE21C81F7DD43A7u, 0x4F16A3A275D49491u,
		0x4F4C4C8B1349B9B5u, 0x4F81AFD6EC0E1411u, 0x4FB61BCCA7119915u, 0x4FEBA2BFD0D5FF5Bu, 0x502145B7E285BF98u,
		0x50559725DB272F7Fu, 0x508AFCEF51F0FB5Eu, 0x50C0DE1593369D1Bu, 0x50F5159AF8044462u, 0x512A5B01B605557Au,
		0x516078E111C3556Cu, 0x5194971956342AC7u, 0x51C9BCDFABC13579u, 0x5200160BCB58C16Cu, 0x52341B8EBE2EF1C7u,
		0x526922726DBAAE39u, 0x529F6B0F092959C7u, 0x52D3A2E965B9D81Cu, 0x53088BA3BF284E23u, 0x533EAE8CAEF261ACu,
		0x53732D17ED577D0Bu, 0x53A7F85DE8AD5C4Eu, 0x53DDF67562D8B362u, 0x5412BA095DC7701Du, 0x5447688BB5394C25u,
		0x547D42AEA2879F2Eu, 0x54B249AD2594C37Cu, 0x54E6DC186EF9F45Cu, 0x551C931E8AB87173u, 0x5551DBF316B346E7u,
		0x558652EFDC6018A1u, 0x55BBE7ABD3781ECAu, 0x55F170CB642B133Eu, 0x5625CCFE3D35D80Eu, 0x565B403DCC834E11u,
		0x569108269FD210CBu, 0x56C54A3047C694FDu, 0x56FA9CBC59B83A3Du, 0x5730A1F5B8132466u, 0x5764CA732617ED7Fu,
		0x5799FD0FEF9DE8DFu, 0x57D03E29F5C2B18Bu, 0x58044DB473335DEEu, 0x583961219000356Au, 0x586FB969F40042C5u,
		0x58A3D3E2388029BBu, 0x58D8C8DAC6A0342Au, 0x590EFB1178484134u, 0x59435CEAEB2D28C0u, 0x59783425A5F872F1u,
		0x59AE412F0F768FADu, 0x59E2E8BD69AA19CCu, 0x5A17A2ECC414A03Fu, 0x5A4D8BA7F519C84Fu, 0x5A827748F9301D31u,
		0x5AB7151B377C247Eu, 0x5AECDA62055B2D9Du, 0x5B22087D4358FC82u, 0x5B568A9C942F3BA3u, 0x5B8C2D43B93B0A8Bu,
		0x5BC19C4A53C4E697u, 0x5BF6035CE8B6203Du, 0x5C2B843422E3A84Cu, 0x5C6132A095CE492Fu, 0x5C957F48BB41DB7Bu,
		0x5CCADF1AEA12525Au, 0x5D00CB70D24B7378u, 0x5D34FE4D06DE5056u, 0x5D6A3DE04895E46Cu, 0x5DA066AC2D5DAEC3u,
		0x5DD4805738B51A74u, 0x5E09A06D06E26112u, 0x5E400444244D7CABu, 0x5E7405552D60DBD6u, 0x5EA906AA78B912CBu,
		0x5EDF485516E7577Eu, 0x5F138D352E5096AFu, 0x5F48708279E4BC5Au, 0x5F7E8CA3185DEB71u, 0x5FB317E5EF3AB327u,
		0x5FE7DDDF6B095FF0u, 0x601DD55745CBB7ECu, 0x6052A5568B9F52F4u, 0x60874EAC2E8727B1u, 0x60BD22573A28F19Du,
		0x60F2357684599702u, 0x6126C2D4256FFCC2u, 0x615C73892ECBFBF3u, 0x6191C835BD3F7D78u, 0x61C63A432C8F5CD6u,
		0x61FBC8D3F7B3340Bu, 0x62315D847AD00087u, 0x6265B4E5998400A9u, 0x629B221EFFE500D3u, 0x62D0F5535FEF2084u,
		0x630532A837EAE8A5u, 0x633A7F5245E5A2CEu, 0x63708F936BAF85C1u, 0x63A4B378469B6731u, 0x63D9E056584240FDu,
		0x64102C35F729689Eu, 0x6444374374F3C2C6u, 0x647945145230B377u, 0x64AF965966BCE055u, 0x64E3BDF7E0360C35u,
		0x6518AD75D8438F43u, 0x654ED8D34E547313u, 0x6583478410F4C7ECu, 0x65B819651531F9E7u, 0x65EE1FBE5A7E7861u,
		0x6622D3D6F88F0B3Cu, 0x665788CCB6B2CE0Cu, 0x668D6AFFE45F818Fu, 0x66C262DFEEBBB0F9u, 0x66F6FB97EA6A9D37u,
		0x672CBA7DE5054485u, 0x6761F48EAF234AD3u, 0x679671B25AEC1D88u, 0x67CC0E1EF1A724EAu, 0x680188D357087712u,
		0x6835EB082CCA94D7u, 0x686B65CA37FD3A0Du, 0x68A11F9E62FE4448u, 0x68D56785FBBDD55Au, 0x690AC1677AAD4AB0u,
		0x6940B8E0ACAC4EAEu, 0x6974E718D7D7625Au, 0x69AA20DF0DCD3AF0u, 0x69E0548B68A044D6u, 0x6A1469AE42C8560Cu,
		0x6A498419D37A6B8Fu, 0x6A7FE52048590672u, 0x6AB3EF342D37A407u, 0x6AE8EB0138858D09u, 0x6B1F25C186A6F04Cu,
		0x6B537798F428562Fu, 0x6B88557F31326BBBu, 0x6BBE6ADEFD7F06AAu, 0x6BF302CB5E6F642Au, 0x6C27C37E360B3D35u,
		0x6C5DB45DC38E0C82u, 0x6C9290BA9A38C7D1u, 0x6CC734E940C6F9C5u, 0x6CFD022390F8B837u, 0x6D3221563A9B7322u,
		0x6D66A9ABC9424FEBu, 0x6D9C5416BB92E3E6u, 0x6DD1B48E353BCE6Fu, 0x6E0621B1C28AC20Bu, 0x6E3BAA1E332D728Eu,
		0x6E714A52DFFC6799u, 0x6EA59CE797FB817Fu, 0x6EDB04217DFA61DFu, 0x6F10E294EEBC7D2Bu, 0x6F451B3A2A6B9C76u,
		0x6F7A6208B5068394u, 0x6FB07D457124123Cu, 0x6FE49C96CD6D16CBu, 0x7019C3BC80C85C7Eu, 0x70501A55D07D39CFu,
		0x708420EB449C8842u, 0x70B9292615C3AA53u, 0x70EF736F9B3494E8u, 0x7123A825C100DD11u, 0x7158922F31411455u,
		0x718EB6BAFD91596Bu, 0x71C33234DE7AD7E2u, 0x71F7FEC216198DDBu, 0x722DFE729B9FF152u, 0x7262BF07A143F6D3u,
		0x72976EC98994F488u, 0x72CD4A7BEBFA31AAu, 0x73024E8D737C5F0Au, 0x7336E230D05B76CDu, 0x736C9ABD04725480u,
		0x73A1E0B622C774D0u, 0x73D658E3AB795204u, 0x740BEF1C9657A685u, 0x74417571DDF6C813u, 0x7475D2CE55747A18u,
		0x74AB4781EAD1989Eu, 0x74E10CB132C2FF63u, 0x75154FDD7F73BF3Bu, 0x754AA3D4DF50AF0Au, 0x7580A6650B926D66u,
		0x75B4CFFE4E7708C0u, 0x75EA03FDE214CAF0u, 0x7620427EAD4CFED6u, 0x7654531E58A03E8Bu, 0x768967E5EEC84E2Eu,
		0x76BFC1DF6A7A61BAu, 0x76F3D92BA28C7D14u, 0x7728CF768B2F9C59u, 0x775F03542DFB8370u, 0x779362149CBD3226u,
		0x77C83A99C3EC7EAFu, 0x77FE494034E79E5Bu, 0x7832EDC82110C2F9u, 0x7867A93A2954F3B7u, 0x789D9388B3AA30A5u,
		0x78D27C35704A5E67u, 0x79071B42CC5CF601u, 0x793CE2137F743381u, 0x79720D4C2FA8A030u, 0x79A6909F3B92C83Du,
		0x79DC34C70A777A4Cu, 0x7A11A0FC668AAC6Fu, 0x7A46093B802D578Bu, 0x7A7B8B8A6038AD6Eu, 0x7AB137367C236C65u,
		0x7AE585041B2C477Eu, 0x7B1AE64521F7595Eu, 0x7B50CFEB353A97DAu, 0x7B8503E602893DD1u, 0x7BBA44DF832B8D45u,
		0x7BF06B0BB1FB384Bu, 0x7C2485CE9E7A065Eu, 0x7C59A742461887F6u, 0x7C9008896BCF54F9u, 0x7CC40AABC6C32A38u,
		0x7CF90D56B873F4C6u, 0x7D2F50AC6690F1F8u, 0x7D63926BC01A973Bu, 0x7D987706B0213D09u, 0x7DCE94C85C298C4Cu,
		0x7E031CFD3999F7AFu, 0x7E37E43C8800759Bu, 0x7E6DDD4BAA009302u, 0x7EA2AA4F4A405BE1u, 0x7ED754E31CD072D9u,
		0x7F0D2A1BE4048F90u, 0x7F423A516E82D9BAu, 0x7F76C8E5CA239028u, 0x7FAC7B1F3CAC7433u, 0x7FE1CCF385EBC89Fu,
		0x7FEFFFFFFFFFFFFFu };
		return table;
	}
};

template <typename Floating>
inline hamon::to_chars_result
to_chars_floating_point_precision_general(char* first, char* last, Floating value, int precision) noexcept
{
	using Binary = hamon::ieee754::binary<Floating>;
	Binary const bits(value);

	// 負の値、ゼロ、NaN、Infinityはこの関数より前で処理されていなければならない
	HAMON_ASSERT(bits.sign() == 0u);
	HAMON_ASSERT(!bits.is_zero());
	HAMON_ASSERT(bits.is_finite());

	using uint_type = typename Binary::uint_type;
	const auto uint_value = bits.uint();

	// C11 7.21.6.1 "The fprintf function"/5:
	// "A negative precision argument is taken as if the precision were omitted."
	// /8: "g,G [...] Let P equal the precision if nonzero, 6 if the precision is omitted,
	// or 1 if the precision is zero."

	// Performance note: It's possible to rewrite this for branchless codegen,
	// but profiling will be necessary to determine whether that's faster.
	if (precision < 0)
	{
		precision = 6;
	}
	else if (precision == 0)
	{
		precision = 1;
	}
	else if (precision < 1000000)
	{
		// precision is ok.
	}
	else
	{
		// Avoid integer overflow.
		// Due to general notation's zero-trimming behavior, we can simply clamp precision.
		// This is further clamped below.
		precision = 1000000;
	}

	// precision is now the Standard's P.

	// /8: "Then, if a conversion with style E would have an exponent of X:
	// - if P > X >= -4, the conversion is with style f (or F) and precision P - (X + 1).
	// - otherwise, the conversion is with style e (or E) and precision P - 1."

	// /8: "Finally, [...] any trailing zeros are removed from the fractional portion of the result
	// and the decimal-point character is removed if there is no fractional portion remaining."

	using Tables = general_precision_tables<Floating>;

	const uint_type* table_begin;
	const uint_type* table_end;

	if (precision <= Tables::max_special_P())
	{
		table_begin = Tables::special_X_table() + (precision - 1) * (precision + 10) / 2;
		table_end = table_begin + precision + 5;
	}
	else
	{
		table_begin = Tables::ordinary_X_table();
		table_end = table_begin + hamon::min(precision, Tables::max_P()) + 5;
	}

	// Profiling indicates that linear search is faster than binary search for small tables.
	// Performance note: lambda captures may have a small performance cost.
	const uint_type* const table_lower_bound = [=] {
		//if constexpr (!hamon::is_same<Floating, float>::value)
		{
			// threshold determined via profiling
			if (precision > 155)
			{
				return hamon::lower_bound(table_begin, table_end, uint_value, hamon::less<uint_type>{});
			}
		}

		return hamon::find_if(table_begin, table_end, [=](const uint_type elem) { return uint_value <= elem; });
	}();

	const hamon::ptrdiff_t table_index = table_lower_bound - table_begin;
	const int scientific_exponent_X = static_cast<int>(table_index - 5);
	const bool use_fixed_notation = precision > scientific_exponent_X && scientific_exponent_X >= -4;

	// Performance note: it might (or might not) be faster to modify Ryu Printf to perform zero-trimming.
	// Such modifications would involve a fairly complicated state machine (notably, both '0' and '9' digits would
	// need to be buffered, due to rounding), and that would have performance costs due to increased branching.
	// Here, we're using a simpler approach: writing into a local buffer, manually zero-trimming, and then copying into
	// the output range. The necessary buffer size is reasonably small, the zero-trimming logic is simple and fast,
	// and the final copying is also fast.

	constexpr int max_output_length =
		hamon::is_same<Floating, float>::value ? 117 : 773; // cases: 0x1.fffffep-126f and 0x1.fffffffffffffp-1022
	constexpr int max_fixed_precision =
		hamon::is_same<Floating, float>::value ? 37 : 66; // cases: 0x1.fffffep-14f and 0x1.fffffffffffffp-14
	constexpr int max_scientific_precision =
		hamon::is_same<Floating, float>::value ? 111 : 766; // cases: 0x1.fffffep-126f and 0x1.fffffffffffffp-1022

	// Note that max_output_length is determined by scientific notation and is more than enough for fixed notation.
	// 0x1.fffffep+127f is 39 digits, plus 1 for '.', plus max_fixed_precision for '0' digits, equals 77.
	// 0x1.fffffffffffffp+1023 is 309 digits, plus 1 for '.', plus max_fixed_precision for '0' digits, equals 376.

	char buffer[max_output_length];
	const char* const significand_first = buffer; // e.g. "1.234"
	const char* significand_last = nullptr;
	const char* exponent_first = nullptr; // e.g. "e-05"
	const char* exponent_last = nullptr;
	int effective_precision; // number of digits printed after the decimal point, before trimming

	// Write into the local buffer.
	// Clamping effective_precision allows buffer to be as small as possible, and increases efficiency.
	if (use_fixed_notation)
	{
		effective_precision = hamon::min(precision - (scientific_exponent_X + 1), max_fixed_precision);
		const hamon::to_chars_result buf_result =
			ryu::d2fixed_buffered_n(buffer, hamon::end(buffer), value, (uint32_t)effective_precision);
		HAMON_ASSERT(buf_result.ec == hamon::errc{});
		significand_last = buf_result.ptr;
	}
	else
	{
		effective_precision = hamon::min(precision - 1, max_scientific_precision);
		const hamon::to_chars_result buf_result =
			ryu::d2exp_buffered_n(buffer, hamon::end(buffer), value, (uint32_t)effective_precision);
		HAMON_ASSERT(buf_result.ec == hamon::errc{});
		significand_last = hamon::find(buffer, buf_result.ptr, 'e');
		exponent_first = significand_last;
		exponent_last = buf_result.ptr;
	}

	// If we printed a decimal point followed by digits, perform zero-trimming.
	if (effective_precision > 0)
	{
		while (significand_last[-1] == '0')
		{ // will stop at '.' or a nonzero digit
			--significand_last;
		}

		if (significand_last[-1] == '.')
		{
			--significand_last;
		}
	}

	// Copy the significand to the output range.
	const hamon::ptrdiff_t significand_distance = significand_last - significand_first;
	if (last - first < significand_distance)
	{
		return { last, hamon::errc::value_too_large };
	}
	hamon::memcpy(first, significand_first, static_cast<hamon::size_t>(significand_distance));
	first += significand_distance;

	// Copy the exponent to the output range.
	if (!use_fixed_notation)
	{
		const hamon::ptrdiff_t _Exponent_distance = exponent_last - exponent_first;
		if (last - first < _Exponent_distance)
		{
			return { last, hamon::errc::value_too_large };
		}
		hamon::memcpy(first, exponent_first, static_cast<hamon::size_t>(_Exponent_distance));
		first += _Exponent_distance;
	}

	return { first, hamon::errc{} };
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_TO_CHARS_FLOATING_POINT_PRECISION_GENERAL_HPP
