/**
 *	@file	value_expression.hpp
 *
 *	@brief
 */

#ifndef HAMON_DEBUG_DETAIL_VALUE_EXPRESSION_HPP
#define HAMON_DEBUG_DETAIL_VALUE_EXPRESSION_HPP

#include <hamon/debug/detail/value_expression_fwd.hpp>
#include <hamon/debug/detail/expression_base.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <ostream>
#include <cstddef>
#include <utility>

namespace hamon
{

namespace debug
{

namespace detail
{

template <typename T>
class value_expression : public expression_base<value_expression<T>, hamon::remove_reference_t<T>>
{
public:
	HAMON_CONSTEXPR value_expression(value_expression&& ve)
		: m_value(std::forward<T>(ve.m_value))
	{
	}

	HAMON_CONSTEXPR value_expression(value_expression const& ve)
		: m_value(ve.m_value)
	{
	}

	explicit HAMON_CONSTEXPR value_expression(T&& val)
		: m_value(std::forward<T>(val))
	{
	}

	value_expression& operator=(value_expression const&) = delete;

	HAMON_CONSTEXPR T const& value(void) const { return m_value; }

private:
	T		m_value;
};

template <typename Stream, typename Expr, typename = void>
struct stream_outputtable_impl
	: public hamon::false_type {};

template <typename Stream, typename Expr>
struct stream_outputtable_impl<Stream, Expr, hamon::void_t<decltype(std::declval<Stream&>() << std::declval<Expr const&>().value())>>
	: public hamon::true_type {};

template <typename CharT, typename Traits, typename T>
using stream_outputtable =
	typename stream_outputtable_impl<std::basic_ostream<CharT, Traits>, value_expression<T>>::type;

template <typename CharT, typename Traits, typename T, typename = hamon::enable_if_t<stream_outputtable<CharT, Traits, T>::value>>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, value_expression<T> const& rhs)
{
	return os << rhs.value();
}

template <typename CharT, typename Traits, typename T, hamon::enable_if_t<!stream_outputtable<CharT, Traits, T>::value>* = nullptr>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, value_expression<T> const& /*rhs*/)
{
	return os;// << rhs.value();
}

template <typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, value_expression<std::nullptr_t> const& /*rhs*/)
{
	return os << "nullptr";
}

}	// namespace detail

}	// namespace debug

}	// namespace hamon

#endif // HAMON_DEBUG_DETAIL_VALUE_EXPRESSION_HPP
