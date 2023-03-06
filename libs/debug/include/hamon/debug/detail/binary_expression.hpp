/**
 *	@file	binary_expression.hpp
 *
 *	@brief
 */

#ifndef HAMON_DEBUG_DETAIL_BINARY_EXPRESSION_HPP
#define HAMON_DEBUG_DETAIL_BINARY_EXPRESSION_HPP

#include <hamon/debug/detail/binary_expression_fwd.hpp>
#include <hamon/debug/detail/expression_base.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>
#include <ostream>

namespace hamon
{

namespace debug
{

namespace detail
{

template <typename Lhs, typename Rhs, typename OP>
class binary_expression : public expression_base<binary_expression<Lhs, Rhs, OP>, typename OP::result_type>
{
public:
	using result_type = typename OP::result_type;

	HAMON_CONSTEXPR binary_expression(binary_expression const& be)
		: m_lhs(be.m_lhs)
		, m_rhs(be.m_rhs)
	{
	}

	HAMON_CONSTEXPR binary_expression(binary_expression&& be)
		: m_lhs(hamon::forward<Lhs>(be.m_lhs))
		, m_rhs(hamon::forward<Rhs>(be.m_rhs))
	{
	}

	HAMON_CONSTEXPR binary_expression(Lhs&& lhs, Rhs&& rhs)
		: m_lhs(hamon::forward<Lhs>(lhs))
		, m_rhs(hamon::forward<Rhs>(rhs))
	{
	}

	HAMON_CONSTEXPR binary_expression(Lhs const& lhs, Rhs const& rhs)
		: m_lhs(lhs)
		, m_rhs(rhs)
	{
	}

	HAMON_CONSTEXPR char const* label(void) const
	{
		return OP::label();
	}

	HAMON_CONSTEXPR Lhs const& lhs(void) const { return m_lhs; }
	HAMON_CONSTEXPR Rhs const& rhs(void) const { return m_rhs; }

private:
	Lhs		m_lhs;
	Rhs		m_rhs;
};

template <typename CharT, typename Traits, typename Lhs, typename Rhs, typename OP>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, binary_expression<Lhs, Rhs, OP> const& rhs)
{
	return os << "(" << rhs.lhs() << " " << rhs.label() << " " << rhs.rhs() << ")";
}

}	// namespace detail

}	// namespace debug

}	// namespace hamon

#endif // HAMON_DEBUG_DETAIL_BINARY_EXPRESSION_HPP
