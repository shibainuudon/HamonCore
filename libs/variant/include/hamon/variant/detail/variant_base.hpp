/**
 *	@file	variant_base.hpp
 *
 *	@brief	variant_base の定義
 */

#ifndef HAMON_VARIANT_DETAIL_VARIANT_BASE_HPP
#define HAMON_VARIANT_DETAIL_VARIANT_BASE_HPP

#include <hamon/variant/detail/variadic_union.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint/int8_t.hpp>
#include <hamon/cstdint/int16_t.hpp>
#include <hamon/cstdint/int32_t.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/in_place_index_t.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace variant_detail
{

struct access;

template <typename... Types>
struct variant_base
{
private:
#if 0
	using index_type = hamon::size_t;
#else
	using index_type =
		hamon::conditional_t<(sizeof...(Types) < (hamon::size_t)hamon::numeric_limits<hamon::int8_t>::max()),  hamon::int8_t,
		hamon::conditional_t<(sizeof...(Types) < (hamon::size_t)hamon::numeric_limits<hamon::int16_t>::max()), hamon::int16_t,
		hamon::conditional_t<(sizeof...(Types) < (hamon::size_t)hamon::numeric_limits<hamon::int32_t>::max()), hamon::int32_t,
		hamon::size_t>>>;
#endif

	static const index_type s_invalid_index = static_cast<index_type>(-1);

public:
	HAMON_CXX11_CONSTEXPR
	variant_base()
		: m_union()
		, m_index(s_invalid_index)
	{}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。
	template <hamon::size_t I, typename... Args>
	HAMON_CXX11_CONSTEXPR explicit
	variant_base(hamon::in_place_index_t<I> tag, Args&&... args)
		: m_union(tag, hamon::forward<Args>(args)...)
		, m_index(I)
	{}
HAMON_WARNING_POP()

	HAMON_CXX11_CONSTEXPR hamon::size_t
	index() const HAMON_NOEXCEPT
	{
		return static_cast<hamon::size_t>(m_index);
	}

	HAMON_CXX14_CONSTEXPR void
	index(hamon::size_t i) HAMON_NOEXCEPT
	{
		m_index = static_cast<index_type>(i);
	}

	HAMON_CXX11_CONSTEXPR bool
	valueless_by_exception() const HAMON_NOEXCEPT
	{
		return m_index == s_invalid_index;
	}

	HAMON_CXX14_CONSTEXPR void
	set_valueless() HAMON_NOEXCEPT
	{
		m_index = s_invalid_index;
	}

#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	constexpr void begin_lifetime()
	{
		m_union.begin_lifetime();
	}
#endif

private:
	variadic_union<Types...> m_union;
	index_type               m_index;

	friend struct access;
};

}	// namespace variant_detail

}	// namespace hamon

#endif // HAMON_VARIANT_DETAIL_VARIANT_BASE_HPP
