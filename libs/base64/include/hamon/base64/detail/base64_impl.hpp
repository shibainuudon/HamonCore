/**
 *	@file	base64_impl.hpp
 *
 *	@brief	base64_impl の定義
 */

#ifndef HAMON_BASE64_DETAIL_BASE64_IMPL_HPP
#define HAMON_BASE64_DETAIL_BASE64_IMPL_HPP

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/distance.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/iterator/concepts/weakly_incrementable.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirectly_writable.hpp>
#include <hamon/memory/to_address.hpp>
#include <hamon/ranges/concepts/contiguous_range.hpp>
#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
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
	template <typename CharT>
	static HAMON_CXX14_CONSTEXPR int char_to_index(CharT c)
	{
		int const s_char_to_index_tbl[256] =
		{
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
			-1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
			15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
			-1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
			41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		};

		return
			c == Derived::get_char_table()[62] ? 62 :
			c == Derived::get_char_table()[63] ? 63 :
			s_char_to_index_tbl[static_cast<std::size_t>(c)];
	}

	template <
		typename T,
		typename OutputIterator,
		typename = hamon::enable_if_t<sizeof(T) == 1>
	>
	static HAMON_CXX14_CONSTEXPR void
	encode_impl(
		T const* first,
		T const* last,
		OutputIterator result,
		hamon::detail::overload_priority<1>)
	{
		static_assert(sizeof(T) == 1, "");
		auto const char_table = Derived::get_char_table();
		auto padding = Derived::get_padding();

		// 1.元データを6ビットずつに分割する。（6ビットに満たない分は後ろに0を追加して6ビットにする）
		// 2.各6ビットの値を変換表を使って4文字ずつ変換する。
		// 3.4文字に足りない分は = 記号を後ろに追加する。
		while (first != last)
		{
			std::uint8_t arr3[3] {};
			int i = 0;
			while (i < 3 && first != last)
			{
				arr3[i++] = static_cast<std::uint8_t>(*first++);
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
					*result = char_table[arr4[j]];
					++result;
				}
				else if (padding != 0)
				{
					*result = padding;
					++result;
				}
			}
		}
	}

	template <typename T, typename OutputIterator>
	static /*HAMON_CXX14_CONSTEXPR*/ void
	encode_impl(
		T const* first,
		T const* last,
		OutputIterator result,
		hamon::detail::overload_priority<0>)
	{
		encode_impl(
			reinterpret_cast<std::uint8_t const*>(first),
			reinterpret_cast<std::uint8_t const*>(last),
			result,
			hamon::detail::overload_priority<1>{});
	}

	template <
		typename InputIterator,
		typename T,
		typename = hamon::enable_if_t<sizeof(T) == 1>
	>
	static HAMON_CXX14_CONSTEXPR std::size_t
	decode_impl(
		InputIterator first,
		InputIterator last,
		T* result,
		hamon::detail::overload_priority<1>)
	{
		static_assert(sizeof(T) == 1, "");

		auto const padding = Derived::get_padding();

		std::size_t count = 0;
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
				result[count] = static_cast<T>(arr3[j]);
				++count;
			}
		}

		return count;
	}

	template <typename InputIterator, typename T>
	static /*HAMON_CXX14_CONSTEXPR*/ std::size_t
	decode_impl(
		InputIterator first,
		InputIterator last,
		T* result,
		hamon::detail::overload_priority<0>)
	{
		return decode_impl(
			first,
			last,
			reinterpret_cast<std::uint8_t*>(result),
			hamon::detail::overload_priority<1>{});
	}

public:
	/**
	 *	@brief	Base64エンコードした結果の文字列の長さを取得する
	 *
	 *	@param	bytes	入力のバイト数
	 *
	 *	戻り値に、NULL終端のぶんは含めません
	 */
	static HAMON_CONSTEXPR std::size_t
	get_encoded_size(std::size_t bytes) HAMON_NOEXCEPT
	{
		return Derived::get_padding() == 0 ?
			((bytes * 4) + 2) / 3 :
			((bytes + 2) / 3) * 4;
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iterator),
		HAMON_CONSTRAINED_PARAM(hamon::sized_sentinel_for, Iterator, Sentinel)
	>
	static HAMON_CONSTEXPR std::size_t
	get_encoded_size(Iterator first, Sentinel last) HAMON_NOEXCEPT
	{
		return get_encoded_size(
			static_cast<std::size_t>(hamon::distance(first, last)) * sizeof(hamon::iter_value_t<Iterator>));
	}

	/**
	 *	@brief	Base64デコードした結果のバイト数(の最大)を取得する
	 *
	 *	@param	bytes	入力の文字数
	 *
	 *	Base64エンコードした結果にパディングが含まれる場合、
	 *	実際のバイト数はこの関数が返す値よりも小さい場合があります。
	 *	実際のバイト数はdecode関数の戻り値で取得できます。
	 */
	static HAMON_CONSTEXPR std::size_t
	get_decoded_size(std::size_t length) HAMON_NOEXCEPT
	{
		return Derived::get_padding() == 0 ?
			((length * 3) / 4) :
			((length * 3) + 3) / 4;
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iterator),
		HAMON_CONSTRAINED_PARAM(hamon::sized_sentinel_for, Iterator, Sentinel)
	>
	static HAMON_CONSTEXPR std::size_t
	get_decoded_size(Iterator first, Sentinel last) HAMON_NOEXCEPT
	{
		return get_decoded_size(static_cast<std::size_t>(hamon::distance(first, last)));
	}

	/**
	 *	@brief	Base64エンコード
	 *
	 *	@param	first
	 *	@param	last
	 *	@param	result
	 */
	template <
#if defined(HAMON_USE_STD_RANGES_ITERATOR)
		HAMON_CONSTRAINED_PARAM(hamon::contiguous_iterator, InputIterator),
#else
		HAMON_CONSTRAINED_PARAM(hamon::random_access_iterator, InputIterator),
#endif
		HAMON_CONSTRAINED_PARAM(hamon::sized_sentinel_for, InputIterator, Sentinel),
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, OutputIterator)
	>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires hamon::indirectly_writable<OutputIterator, std::uint8_t>
#endif
	static HAMON_CXX14_CONSTEXPR void
	encode(InputIterator first, Sentinel last, OutputIterator result)
	{
		if (first == last)
		{
			return;
		}

		encode_impl(
			hamon::to_address(first),
			hamon::to_address(first) + hamon::distance(first, last),	// to_address(last)とすると範囲外の参照でエラーになってしまう(MSVC)
			result,
			hamon::detail::overload_priority<1>{});
	}

	/**
	 *	@brief	Base64エンコード(Range版)
	 *
	 *	@param	rng
	 *	@param	result
	 */
	template <
#if defined(HAMON_USE_STD_RANGES_ITERATOR)
		HAMON_CONSTRAINED_PARAM(hamon::ranges::contiguous_range, Range),
#else
		HAMON_CONSTRAINED_PARAM(hamon::ranges::random_access_range, Range),
#endif
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, OutputIterator)
	>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires hamon::indirectly_writable<OutputIterator, std::uint8_t>
#endif
	static HAMON_CXX14_CONSTEXPR void
	encode(Range&& rng, OutputIterator result)
	{
		encode(hamon::ranges::begin(rng), hamon::ranges::end(rng), hamon::move(result));
	}

	/**
	 *	@brief	Base64デコード
	 *
	 *	@param	first
	 *	@param	last
	 *	@param	result
	 */
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, InputIterator),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, InputIterator, Sentinel),
#if defined(HAMON_USE_STD_RANGES_ITERATOR)
		HAMON_CONSTRAINED_PARAM(hamon::contiguous_iterator, OutputIterator)
#else
		HAMON_CONSTRAINED_PARAM(hamon::random_access_iterator, OutputIterator)
#endif
	>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires hamon::indirectly_writable<OutputIterator, std::uint8_t>
#endif
	static HAMON_CXX14_CONSTEXPR std::size_t
	decode(InputIterator first, Sentinel last, OutputIterator result)
	{
		if (first == last)
		{
			return 0u;
		}

		return decode_impl(
			first,
			last,
			hamon::to_address(result),
			hamon::detail::overload_priority<1>{});
	}

	/**
	 *	@brief	Base64デコード(Range版)
	 *
	 *	@param	rng
	 *	@param	result
	 */
	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, Range),
#if defined(HAMON_USE_STD_RANGES_ITERATOR)
		HAMON_CONSTRAINED_PARAM(hamon::contiguous_iterator, OutputIterator)
#else
		HAMON_CONSTRAINED_PARAM(hamon::random_access_iterator, OutputIterator)
#endif
	>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires hamon::indirectly_writable<OutputIterator, std::uint8_t>
#endif
	static HAMON_CXX14_CONSTEXPR std::size_t
	decode(Range&& rng, OutputIterator result)
	{
		return decode(hamon::ranges::begin(rng), hamon::ranges::end(rng), hamon::move(result));
	}

	/**
	 *	@brief
	 */
	template <
		typename Result,
#if defined(HAMON_USE_STD_RANGES_ITERATOR)
		HAMON_CONSTRAINED_PARAM(hamon::contiguous_iterator, Iterator),
#else
		HAMON_CONSTRAINED_PARAM(hamon::random_access_iterator, Iterator),
#endif
		HAMON_CONSTRAINED_PARAM(hamon::sized_sentinel_for, Iterator, Sentinel)
	>
	static Result encode(Iterator first, Sentinel last)
	{
		auto const size = get_encoded_size(first, last);
		if (size == 0)
		{
			return {};
		}

		Result result;
		result.resize(size);
		encode(first, last, result.begin());
		return result;
	}

	/**
	 *	@brief
	 */
	template <
		typename Result,
		HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, Range)
	>
	static Result encode(Range&& rng)
	{
		return encode<Result>(hamon::ranges::begin(rng), hamon::ranges::end(rng));
	}

	/**
	 *	@brief
	 */
	template <
		typename Result,
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iterator),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iterator, Sentinel)
	>
	static Result decode(Iterator first, Sentinel last)
	{
		auto const size = get_decoded_size(first, last);
		if (size == 0)
		{
			return {};
		}

		using value_type = typename Result::value_type;
		Result result;
		result.resize(size / sizeof(value_type));
		auto const actual_size = decode(first, last, result.begin());
		result.resize(actual_size / sizeof(value_type));
		return result;
	}

	/**
	 *	@brief
	 */
	template <
		typename Result,
		HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, Range)
	>
	static Result decode(Range&& rng)
	{
		return decode<Result>(hamon::ranges::begin(rng), hamon::ranges::end(rng));
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_BASE64_DETAIL_BASE64_IMPL_HPP
