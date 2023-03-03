/**
 *	@file	bitflags.hpp
 *
 *	@brief	bitflags クラステンプレートの定義
 */

#ifndef HAMON_BITFLAGS_BITFLAGS_HPP
#define HAMON_BITFLAGS_BITFLAGS_HPP

#include <hamon/type_traits/make_uint_least_n.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_enum.hpp>
#include <hamon/bit/popcount.hpp>
#include <hamon/config.hpp>
#include <string>
#include <cstdint>
#include <cstddef>
#include <ostream>
#include <cstdlib>		// std::abort
#include <stdexcept>	// std::out_of_range

namespace hamon
{

/**
 *	@brief	enumと組み合わせて安全なビットフラグを実現するクラステンプレート.
 *
 *	@tparam		E		enum型
 *	@tparam		N		ビット数
 *	@tparam		Dense	密かどうか
 * 
 *	密かどうかとは：
 *	　下位Nビットの全てのビットがそれぞれ立つ可能性があるとき、密であるとする。
 * 
 *	密である場合のみ、以下の関数が定義される：
 *	* all(void)
 *	* operator<<, operator<<=
 *	* operator>>, operator>>=
 *	* operator~
 *	* set(void)
 *	* flip(void)
 *
 *	@code
 *	enum Enum1
 *	{
 *		kOption1_1,
 *		kOption1_2
 *	};
 *
 *	enum Enum2
 *	{
 *		kOption2_1,
 *		kOption2_2
 *	};
 *	@endcode
 *
 *	が定義されている場合、
 *	bitflags<Enum1> x;
 *	bitflags<Enum2> y;
 *	のように使うことができる
 *
 *	・bitflags<Enum1> は Enum1の列挙子のビットしか立つことがない
 *	　(この場合は下位2ビットしか絶対に変化しない)
 *
 *	・bitflags<Enum1> と bitflags<Enum2>は違う型として区別される(型安全)
 */
template <typename E, std::size_t N = 32, bool Dense = false>
class bitflags
{
private:
	static_assert(hamon::is_enum<E>::value, "");

	using value_type = hamon::make_uint_least_n_t<N>;
	using size_type = std::size_t;

public:
	/**
	 *	@brief	デフォルトコンストラクタ
	 *
	 *	全てのビットが下りた状態に初期化されます
	 */
	HAMON_CONSTEXPR
	bitflags(void) HAMON_NOEXCEPT
		: m_value()
	{}

	/**
	 *	@brief	enum からのコンストラクタ
	 *
	 *	@param	pos
	 * 
	 *	@exception	pos >= size() の場合、out_of_range例外を送出する。
	 *
	 *	pos番目のビットだけが立った状態に初期化されます
	 */
	explicit HAMON_CONSTEXPR
	bitflags(E pos)
		: m_value(make_value(pos))
	{}

private:
	/**
	 *	@brief	value_type からのコンストラクタ
	 *
	 *	@param	value
	 *
	 *	value を直接設定。外部から呼び出せないようにprivate指定。
	 */
	explicit HAMON_CONSTEXPR
	bitflags(value_type value) HAMON_NOEXCEPT
		: m_value(value)
	{}

public:
	/**
	 *	@brief	ビットが立っているかどうか取得
	 *
	 *	@param	pos
	 *
	 *	@return	pos番目のビットが立っていたらtrue
	 * 
	 *	@exception	pos >= size() の場合、out_of_range例外を送出する。
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR bool
	test(E pos) const
	{
		return (m_value & make_value(pos)) != 0;
	}

	/**
	 *	@brief	全てのビットが1になっているかを取得
	 *
	 *	@return	全てのビットが1になっていればtrue
	 * 
	 *	@note	この関数はDenseがtrueのときのみオーバーロード候補となる
	 */
	template <bool B = Dense, typename = hamon::enable_if_t<B>>
	HAMON_NODISCARD HAMON_CONSTEXPR bool
	all() const HAMON_NOEXCEPT
	{
		return count() == size();
	}

	/**
	 *	@brief	ビットが1つでも立っているかどうか取得
	 *
	 *	@return	1つでもビットが立っていたらtrue
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR bool
	any() const HAMON_NOEXCEPT
	{
		return m_value != 0;
	}

	/**
	 *	@brief	ビットが全て下りているかどうか取得
	 *
	 *	@return	ビットが全て下りていたらtrue
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR bool
	none() const HAMON_NOEXCEPT
	{
		return m_value == 0;
	}

	/**
	 *	@brief	1になっているビットの数を取得する
	 *
	 *	@return	1になっているビットの数
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	count() const HAMON_NOEXCEPT
	{
		return static_cast<size_type>(hamon::popcount(m_value));
	}

	/**
	 *	@brief	ビット数を取得する
	 *
	 *	@return	テンプレートパラメータ N
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR size_type
	size() const HAMON_NOEXCEPT
	{
		return N;
	}

	/**
	 *	@brief	operator&
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR bitflags
	operator&(bitflags const& rhs) const HAMON_NOEXCEPT
	{
		return bitflags(m_value & rhs.m_value);
	}

	/**
	 *	@brief	operator|
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR bitflags
	operator|(bitflags const& rhs) const HAMON_NOEXCEPT
	{
		return bitflags(m_value | rhs.m_value);
	}

	/**
	 *	@brief	operator^
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR bitflags
	operator^(bitflags const& rhs) const HAMON_NOEXCEPT
	{
		return bitflags(m_value ^ rhs.m_value);
	}

	/**
	 *	@brief	operator&=
	 */
	HAMON_CXX14_CONSTEXPR bitflags&
	operator&=(bitflags const& rhs) HAMON_NOEXCEPT
	{
		return *this = (*this & rhs);
	}

	/**
	 *	@brief	operator|=
	 */
	HAMON_CXX14_CONSTEXPR bitflags&
	operator|=(bitflags const& rhs) HAMON_NOEXCEPT
	{
		return *this = (*this | rhs);
	}

	/**
	 *	@brief	operator^=
	 */
	HAMON_CXX14_CONSTEXPR bitflags&
	operator^=(bitflags const& rhs) HAMON_NOEXCEPT
	{
		return *this = (*this ^ rhs);
	}
	
	/**
	 *	@brief	ビットを左シフトさせる
	 *
	 *	@note	この関数はDenseがtrueのときのみオーバーロード候補となる
	 */
	template <bool B = Dense, typename = hamon::enable_if_t<B>>
	HAMON_NODISCARD HAMON_CONSTEXPR bitflags
	operator<<(size_type pos) const HAMON_NOEXCEPT
	{
		return bitflags(static_cast<value_type>((m_value << pos) & get_mask_bit()));
	}

	/**
	 *	@brief	ビットを右シフトさせる
	 *
	 *	@note	この関数はDenseがtrueのときのみオーバーロード候補となる
	 */
	template <bool B = Dense, typename = hamon::enable_if_t<B>>
	HAMON_NODISCARD HAMON_CONSTEXPR bitflags
	operator>>(size_type pos) const HAMON_NOEXCEPT
	{
		return bitflags(static_cast<value_type>(m_value >> pos));
	}

	/**
	 *	@brief	ビットを左シフトさせる
	 *
	 *	@param	pos
	 *
	 *	@return	自身への参照
	 *
	 *	@note	この関数はDenseがtrueのときのみオーバーロード候補となる
	 */
	template <bool B = Dense, typename = hamon::enable_if_t<B>>
	HAMON_CXX14_CONSTEXPR bitflags&
	operator<<=(size_type pos) HAMON_NOEXCEPT
	{
		return *this = (*this << pos);
	}

	/**
	 *	@brief	ビットを右シフトさせる
	 *
	 *	@param	pos
	 *
	 *	@return	自身への参照
	 * 
	 *	@note	この関数はDenseがtrueのときのみオーバーロード候補となる
	 */
	template <bool B = Dense, typename = hamon::enable_if_t<B>>
	HAMON_CXX14_CONSTEXPR bitflags&
	operator>>=(size_type pos) HAMON_NOEXCEPT
	{
		return *this = (*this >> pos);
	}

	/**
	 *	@brief	ビットを反転させる
	 * 
	 *	@note	この関数はDenseがtrueのときのみオーバーロード候補となる
	 */
	template <bool B = Dense, typename = hamon::enable_if_t<B>>
	HAMON_NODISCARD HAMON_CONSTEXPR bitflags
	operator~() const HAMON_NOEXCEPT
	{
		return bitflags(static_cast<value_type>(~m_value & get_mask_bit()));
	}

	/**
	 *	@brief	pos番目のビットを1にする
	 *
	 *	@param	pos
	 *
	 *	@return	自身への参照
	 * 
	 *	@exception	pos >= size() の場合、out_of_range例外を送出する。
	 */
	HAMON_CXX14_CONSTEXPR bitflags&
	set(E pos)
	{
		return *this |= bitflags(pos);
	}

	/**
	 *	@brief	全ビットを1にする
	 *
	 *	@return	自身への参照
	 * 
	 *	@note	この関数はDenseがtrueのときのみオーバーロード候補となる
	 */
	template <bool B = Dense, typename = hamon::enable_if_t<B>>
	HAMON_CXX14_CONSTEXPR bitflags&
	set() HAMON_NOEXCEPT
	{
		m_value = get_mask_bit();
		return *this;
	}

	/**
	 *	@brief	pos番目のビットを0にする
	 *
	 *	@param	pos
	 *
	 *	@return	自身への参照
	 * 
	 *	@exception	pos >= size() の場合、out_of_range例外を送出する。
	 */
	HAMON_CXX14_CONSTEXPR bitflags&
	reset(E pos)
	{
		m_value = static_cast<value_type>(m_value & ~make_value(pos));
		return *this;
	}

	/**
	 *	@brief	全ビットを0にする
	 *
	 *	@return	自身への参照
	 */
	HAMON_CXX14_CONSTEXPR bitflags&
	reset() HAMON_NOEXCEPT
	{
		m_value = 0;
		return *this;
	}

	/**
	 *	@brief	pos番目のビットを反転する
	 *
	 *	@param	pos
	 *
	 *	@return	自身への参照
	 * 
	 *	@exception	pos >= size() の場合、out_of_range例外を送出する。
	 */
	HAMON_CXX14_CONSTEXPR bitflags&
	flip(E pos)
	{
		return *this ^= bitflags(pos);
	}

	/**
	 *	@brief	全ビットを反転する
	 *
	 *	@return	自身への参照
	 * 
	 *	@note	この関数はDenseがtrueのときのみオーバーロード候補となる
	 */
	template <bool B = Dense, typename = hamon::enable_if_t<B>>
	HAMON_CXX14_CONSTEXPR bitflags&
	flip() HAMON_NOEXCEPT
	{
		m_value = static_cast<value_type>(m_value ^ get_mask_bit());
		return *this;
	}

	/**
	 *	@brief	unsigned long 型に変換
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR unsigned long
	to_ulong() const HAMON_NOEXCEPT
	{
		return static_cast<unsigned long>(m_value);
	}

	/**
	 *	@brief	unsigned long long 型に変換
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR unsigned long long
	to_ullong() const HAMON_NOEXCEPT
	{
		return static_cast<unsigned long long>(m_value);
	}

	/**
	 *	@brief	string 型に変換
	 */
	template <
		typename CharT = char,
		typename Traits = std::char_traits<CharT>,
		typename Allocator = std::allocator<CharT>
	>
	HAMON_NODISCARD /*HAMON_CONSTEXPR*/
	std::basic_string<CharT, Traits, Allocator>
    to_string(CharT zero = CharT('0'), CharT one = CharT('1')) const
	{
		std::basic_string<CharT, Traits, Allocator> result;
		auto value = m_value;
		auto const mask = static_cast<value_type>(1) << (N - 1);
		for (std::size_t i = 0; i < N; ++i)
		{
			if (value & mask)
			{
				result.append(1, one);
			}
			else
			{
				result.append(1, zero);
			}
			value = static_cast<value_type>(value << 1);
		}
		return result;
	}

	/**
	 *	@brief	boolへの変換オペレータ
	 *
	 *	@return	1つでもビットが立っていたらtrue
	 *
	 *	@code
	 *	if ((f & Bitflags::Value1).any()) { ... }
	 *	@endcode
	 *
	 *	ではなく、
	 *
	 *	@code
	 *	if (f & Bitflags::Value1) { ... }
	 *	@endcode
	 *
	 *	と書けるようにする。
	 */
	HAMON_NODISCARD explicit HAMON_CONSTEXPR
	operator bool() const HAMON_NOEXCEPT
	{
		return any();
	}

	/**
	 *	@brief	operator==
	 *
	 *	@return	右辺と左辺のビットが等しければtrue
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR bool
	operator==(bitflags const& rhs) const HAMON_NOEXCEPT
	{
		return m_value == rhs.m_value;
	}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	/**
	 *	@brief	operator!=
	 *
	 *	@return	右辺と左辺のビットが等しくなければtrue
	 */
	HAMON_NODISCARD HAMON_CONSTEXPR bool
	operator!=(bitflags const& rhs) const HAMON_NOEXCEPT
	{
		return !(*this == rhs);
	}
#endif

private:
	HAMON_NODISCARD static HAMON_CONSTEXPR value_type
	make_value(E pos)
	{
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_GCC("-Wconversion")
		return static_cast<size_type>(pos) < N ?
			static_cast<value_type>(static_cast<value_type>(1) << (static_cast<size_type>(pos))) :
			(throw_out_of_range(), static_cast<value_type>(0));
HAMON_WARNING_POP()
	}

	HAMON_NODISCARD static HAMON_CONSTEXPR value_type
	get_mask_bit() HAMON_NOEXCEPT
	{
		return (value_type(1) << N) - 1;
	}

	HAMON_NORETURN static void
	throw_out_of_range()
	{
#if !defined(HAMON_NO_EXCEPTIONS)
		throw std::out_of_range("bitflags");
#else
		std::abort();
#endif
	}

private:
	value_type	m_value;
};

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits, typename E, std::size_t N, bool Dense>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, bitflags<E, N, Dense> const& rhs)
{
	return os << rhs.template to_string<CharT, Traits>();
}

}	// namespace hamon

#endif // HAMON_BITFLAGS_BITFLAGS_HPP
