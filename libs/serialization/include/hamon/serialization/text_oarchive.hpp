/**
 *	@file	text_oarchive.hpp
 *
 *	@brief	text_oarchiveの定義
 */

#ifndef HAMON_SERIALIZATION_TEXT_OARCHIVE_HPP
#define HAMON_SERIALIZATION_TEXT_OARCHIVE_HPP

#include <hamon/serialization/detail/save_value.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <cstdint>
#include <type_traits>
#include <memory>
#include <limits>
#include <array>
#include <iomanip>

#if HAMON_HAS_INCLUDE(<charconv>) && (HAMON_CXX_STANDARD >= 17)
#include <charconv>
#endif

namespace hamon
{

namespace serialization
{

class text_oarchive_impl_base
{
public:
	virtual ~text_oarchive_impl_base()
	{}

	virtual void save(std::intmax_t) = 0;
	virtual void save(std::uintmax_t) = 0;
	virtual void save(float) = 0;
	virtual void save(double) = 0;
	virtual void save(long double) = 0;
};

template <typename OStream>
class text_oarchive_impl
	: public text_oarchive_impl_base
{
public:
	explicit text_oarchive_impl(OStream& os)
		: m_os(os)
	{}

	void save(std::intmax_t t) override
	{
		m_os << t << " ";
	}

	void save(std::uintmax_t t) override
	{
		m_os << t << " ";
	}
	
	void save(float t) override
	{
		save_float_impl(t);
	}

	void save(double t) override
	{
		save_float_impl(t);
	}

	void save(long double t) override
	{
		save_float_impl(t);
	}

private:
	template <typename T>
	void save_float_impl(T t)
	{
#if defined(__cpp_lib_to_chars) && (__cpp_lib_to_chars >= 201611L)
		auto constexpr digits =
			4 +	// sign, decimal point, "e+" or "e-"
			std::numeric_limits<T>::max_digits10 +
			3;	// log10(max_exponent10)
		std::array<char, digits + 1> buf{};
		auto result = std::to_chars(buf.data(), buf.data() + buf.size(), t);
		m_os << buf.data() << " ";
		(void)result;
#else
		auto const flags = m_os.flags();
		m_os << std::setprecision(std::numeric_limits<T>::max_digits10) << std::scientific << t << " ";
		m_os.flags(flags);
#endif
	}

private:
	text_oarchive_impl& operator=(text_oarchive_impl const&) = delete;

	OStream&	m_os;
};

class text_oarchive
{
public:
	template <typename OStream>
	explicit text_oarchive(OStream& os)
		: m_impl(new text_oarchive_impl<OStream>(os))
	{
	}

	template <typename T>
	text_oarchive& operator<<(T const& t)
	{
		hamon::serialization::save_value(*this, t);
		return *this;
	}

	template <typename T>
	text_oarchive& operator&(T const& t)
	{
		return *this << t;
	}

private:
	template <typename T, typename = hamon::enable_if_t<std::is_floating_point<T>::value>>
	void save_arithmetic_impl(T const& t, hamon::detail::overload_priority<2>)
	{
		m_impl->save(t);
	}
	template <typename T, typename = hamon::enable_if_t<std::is_unsigned<T>::value>>
	void save_arithmetic_impl(T const& t, hamon::detail::overload_priority<1>)
	{
		m_impl->save(static_cast<std::uintmax_t>(t));
	}
	template <typename T, typename = hamon::enable_if_t<std::is_signed<T>::value>>
	void save_arithmetic_impl(T const& t, hamon::detail::overload_priority<0>)
	{
		m_impl->save(static_cast<std::intmax_t>(t));
	}

	template <typename T>
	friend void save_arithmetic(text_oarchive& oa, T const& t)
	{
		oa.save_arithmetic_impl(t, hamon::detail::overload_priority<2>{});
	}

	std::unique_ptr<text_oarchive_impl_base>	m_impl;
};

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_TEXT_OARCHIVE_HPP
