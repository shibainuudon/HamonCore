/**
 *	@file	base64_impl.hpp
 *
 *	@brief	base64_impl の定義
 */

#ifndef HAMON_BASE64_DETAIL_BASE64_IMPL_HPP
#define HAMON_BASE64_DETAIL_BASE64_IMPL_HPP

#include <cstddef>
#include <cstdint>
#include <string>
#include <array>

namespace hamon
{

namespace detail
{

template <typename Derived>
struct base64_impl
{
private:
	static std::array<int, 0x80> init_char_to_index_table()
	{
		auto const char_table = Derived::get_char_table();

		std::array<int, 0x80> tbl;
		tbl.fill(-1);
		for (int i = 0; i < 64; ++i)
		{
			tbl[char_table[i]] = i;
		}
		return tbl;
	}

	static std::array<int, 0x80> get_char_to_index_table()
	{
		static const std::array<int, 0x80> s_table = init_char_to_index_table();
		return s_table;
	}

	template <typename CharT>
	static int char_to_index(CharT c)
	{
		return get_char_to_index_table()[static_cast<std::size_t>(c)];
	}

public:
	// 1.元データを6ビットずつに分割する。（6ビットに満たない分は後ろに0を追加して6ビットにする）
	// 2.各6ビットの値を変換表を使って4文字ずつ変換する。
	// 3.4文字に足りない分は = 記号を後ろに追加する。
	template <typename Dst>
	static Dst encode(void const* ptr, std::size_t bytes)
	{
		auto const char_table = Derived::get_char_table();
		auto const padding    = Derived::get_padding();

		Dst result;

		auto first = static_cast<std::uint8_t const*>(ptr);
		auto last = first + bytes;
		while (first != last)
		{
			std::uint8_t arr3[3] {};
			int i = 0;
			while (i < 3 && first != last)
			{
				arr3[i++] = *first++;
			}

			std::uint8_t const arr4[4]
			{
				static_cast<std::uint8_t>( (arr3[0] & 0xfc) >> 2),
				static_cast<std::uint8_t>(((arr3[0] & 0x03) << 4) + ((arr3[1] & 0xf0) >> 4)),
				static_cast<std::uint8_t>(((arr3[1] & 0x0f) << 2) + ((arr3[2] & 0xc0) >> 6)),
				static_cast<std::uint8_t>(  arr3[2] & 0x3f),
			};

			for (int j = 0; j < 4; ++j)
			{
				if (j < (i + 1))
				{
					result += char_table[arr4[j]];
				}
				else if (padding != 0)
				{
					result += padding;
				}
			}
		}

		return result;
	}

	template <typename Dst, typename Iterator>
	static Dst decode(Iterator first, Iterator last)
	{
		auto const padding = Derived::get_padding();

		std::string buf;

		while (first != last)
		{
			std::uint8_t arr4[4] {};
			int i = 0;
			while (i < 4)
			{
				if (first == last)
				{
					break;
				}

				auto const c = *first;
				auto const index = char_to_index(c);
				if (c == padding || index == -1)
				{
					first = last;
					break;
				}
				arr4[i++] = static_cast<std::uint8_t>(index);
				++first;
			}

			std::uint8_t const arr3[3]
			{
				static_cast<std::uint8_t>(( arr4[0]        << 2) + ((arr4[1] & 0x30) >> 4)),
				static_cast<std::uint8_t>(((arr4[1] & 0xf) << 4) + ((arr4[2] & 0x3c) >> 2)),
				static_cast<std::uint8_t>(((arr4[2] & 0x3) << 6) +   arr4[3]),
			};

			for (int j = 0; j < (i - 1); ++j)
			{
				buf += arr3[j];
			}
		}

		using const_pointer = typename Dst::const_pointer;
		return {
			reinterpret_cast<const_pointer>(buf.data()),
			reinterpret_cast<const_pointer>(buf.data() + buf.size())
		};
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_BASE64_DETAIL_BASE64_IMPL_HPP
