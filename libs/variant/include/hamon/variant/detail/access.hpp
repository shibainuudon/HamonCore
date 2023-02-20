/**
 *	@file	access.hpp
 *
 *	@brief	access の定義
 */

#ifndef HAMON_VARIANT_DETAIL_ACCESS_HPP
#define HAMON_VARIANT_DETAIL_ACCESS_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace variant_detail
{

struct access
{
private:
	template <hamon::size_t N, typename = void>
	struct get_impl
	{
		template <typename Union>
		HAMON_CXX11_CONSTEXPR auto operator()(Union&& u) const HAMON_NOEXCEPT
		->decltype(get_impl<N-1>{}(hamon::forward<Union>(u).m_tail))
		{
			return get_impl<N-1>{}(hamon::forward<Union>(u).m_tail);
		}
	};

	template <typename Dummy>
	struct get_impl<0, Dummy>
	{
		template <typename Union>
		HAMON_CXX11_CONSTEXPR auto operator()(Union&& u) const HAMON_NOEXCEPT
		->decltype((hamon::forward<Union>(u).m_head))
		{
			return hamon::forward<Union>(u).m_head;
		}
	};

public:
	template <hamon::size_t I, typename Variant>
	static HAMON_CXX11_CONSTEXPR auto
	get(Variant&& v) HAMON_NOEXCEPT
	->decltype(get_impl<I>{}(hamon::forward<Variant>(v).m_union))
	{
		return get_impl<I>{}(hamon::forward<Variant>(v).m_union);
	}
};

}	// namespace variant_detail

}	// namespace hamon

#endif // HAMON_VARIANT_DETAIL_ACCESS_HPP
