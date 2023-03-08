/**
 *	@file	xml_iarchive.hpp
 *
 *	@brief	xml_iarchiveの定義
 */

#ifndef HAMON_SERIALIZATION_XML_IARCHIVE_HPP
#define HAMON_SERIALIZATION_XML_IARCHIVE_HPP

#include <hamon/serialization/detail/archive_base.hpp>
#include <hamon/serialization/detail/xml_iarchive_impl.hpp>
#include <hamon/serialization/detail/load_value.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint/intmax_t.hpp>
#include <hamon/cstdint/uintmax_t.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_floating_point.hpp>
#include <hamon/type_traits/is_signed.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <memory>
#include <string>

namespace hamon
{

namespace serialization
{

class xml_iarchive : public detail::archive_base
{
public:
	template <typename IStream>
	explicit xml_iarchive(IStream& is)
		: m_impl(new detail::xml_iarchive_impl<IStream>(is))
	{
		read_tag();	// <?xml version=\"1.0\"?>
		read_tag();	// <serialization>
	}

	~xml_iarchive()
	{
		read_tag();	// </serialization>
	}

	template <typename T>
	xml_iarchive& operator>>(nvp<T> const& t)
	{
		read_tag();
		hamon::serialization::detail::load_value(*this, t.value());
		read_tag();
		return *this;
	}

	template <typename T>
	xml_iarchive& operator>>(T& t)
	{
		return *this >> make_nvp("", t);
	}

	template <typename T>
	xml_iarchive& operator&(T& t)
	{
		return *this >> t;
	}

private:
	std::string read_tag(void)
	{
		return m_impl->read_tag();
	}

	template <typename CharT>
	static std::basic_string<CharT> unescape(std::basic_string<CharT> const& str)
	{
		bool escaping = false;
		std::basic_string<CharT> result;
		for (hamon::size_t i = 0; i < str.size(); ++i)
		{
			auto c = str[i];
			if (escaping)
			{
				switch (c)
				{
				case 'q': c = '"'; i+=4; break;
				case 'a':
					if (str[i+1] == 'p')
					{
						c = '\'';
						i+=4;
					}
					else
					{
						c = '&';
						i+=3;
					}
					break;
				case 'l': c = '<'; i+=2; break;
				case 'g': c = '>'; i+=2; break;
				}
				escaping = false;
			}
			else
			{
				if (c == '&')
				{
					escaping = true;
					continue;
				}
			}

			result += c;
		}
		return result;
	}

private:
	template <typename T, typename = hamon::enable_if_t<hamon::is_floating_point<T>::value>>
	void load_arithmetic_impl(T& t, hamon::detail::overload_priority<2>)
	{
		m_impl->load(t);
	}
	template <typename T, typename = hamon::enable_if_t<hamon::is_unsigned<T>::value>>
	void load_arithmetic_impl(T& t, hamon::detail::overload_priority<1>)
	{
		hamon::uintmax_t i;
		m_impl->load(i);
		t = static_cast<T>(i);
	}
	template <typename T, typename = hamon::enable_if_t<hamon::is_signed<T>::value>>
	void load_arithmetic_impl(T& t, hamon::detail::overload_priority<0>)
	{
		hamon::intmax_t i;
		m_impl->load(i);
		t = static_cast<T>(i);
	}

	friend void load_arithmetic(xml_iarchive& ia, bool& t)
	{
		ia.m_impl->load(t);
	}

	template <typename T>
	friend void load_arithmetic(xml_iarchive& ia, T& t)
	{
		ia.load_arithmetic_impl(t, hamon::detail::overload_priority<2>{});
	}

	template <typename T>
	friend void load_string(xml_iarchive& ia, T& t)
	{
		T tmp;
		ia.m_impl->load_string_until(tmp, '<');	// 次のタグ開始まで読む
		ia.m_impl->unget_one_char();			// 1文字戻す
		t = unescape(tmp);
	}

	//template <typename T>
	//friend void load_array(xml_iarchive& ia, T& t)
	//{
	//}

	template <typename T>
	friend void load_vector(xml_iarchive& ia, T& t)
	{
		using element_type = typename T::value_type;

		for (;;)
		{
			auto const pos = ia.m_impl->tellg();
			auto const tag = ia.read_tag();
			if (tag[0] == '<' && tag[1] == '/')
			{
				ia.m_impl->seekg(pos);
				break;
			}

			element_type e;
			hamon::serialization::detail::load_value(ia, e);
			t.push_back(e);

			ia.read_tag();
		}
	}

	//friend void start_load_class(xml_iarchive& ia)
	//{
	//}

	//friend void end_load_class(xml_iarchive& ia)
	//{
	//}

private:
	std::unique_ptr<detail::xml_iarchive_impl_base>	m_impl;
};

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_XML_IARCHIVE_HPP
