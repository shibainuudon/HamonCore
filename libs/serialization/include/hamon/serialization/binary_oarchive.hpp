/**
 *	@file	binary_oarchive.hpp
 *
 *	@brief	binary_oarchiveの定義
 */

#ifndef HAMON_SERIALIZATION_BINARY_OARCHIVE_HPP
#define HAMON_SERIALIZATION_BINARY_OARCHIVE_HPP

#include <hamon/serialization/detail/save_value.hpp>
#include <ostream>
#include <cstddef>
#include <vector>
#include <memory>
#include <cstring>	// memcpy

namespace hamon
{

namespace serialization
{

template <typename CharT, typename Traits>
void save_binary(std::basic_ostream<CharT, Traits>& os, void const* p, std::size_t size)
{
	auto pbuf = os.rdbuf();
	auto const count = (size + (sizeof(CharT) - 1)) / sizeof(CharT);
	if (size % sizeof(CharT) == 0)
	{
		// size が sizeof(CharT) の倍数のときはそのまま書き込めば良い
		pbuf->sputn(static_cast<CharT const*>(p), count);
	}
	else
	{
		// そうでないときは、一時バッファにコピーしてから書き込む
		std::vector<CharT> buf(count);	// TODO basic_stringを使ったほうが、countが小さい場合に高速かもしれない
		std::memcpy(buf.data(), p, size);
		pbuf->sputn(buf.data(), count);
	}
}

class binary_oarchive_impl_base
{
public:
	virtual ~binary_oarchive_impl_base()
	{}

	virtual void save(void const* src, std::size_t size) = 0;
};

template <typename OStream>
class binary_oarchive_impl
	: public binary_oarchive_impl_base
{
public:
	explicit binary_oarchive_impl(OStream& os)
		: m_os(os)
	{}

	void save(void const* src, std::size_t size) override
	{
		save_binary(m_os, src, size);
	}

private:
	binary_oarchive_impl& operator=(binary_oarchive_impl const&) = delete;

	OStream&	m_os;
};

class binary_oarchive
{
public:
	template <typename OStream>
	explicit binary_oarchive(OStream& os)
		: m_impl(new binary_oarchive_impl<OStream>(os))
	{
	}

	template <typename T>
	binary_oarchive& operator<<(T const& t)
	{
		hamon::serialization::save_value(*this, t);
		return *this;
	}

	template <typename T>
	binary_oarchive& operator&(T const& t)
	{
		return *this << t;
	}

private:
	template <typename T>
	friend void save_arithmetic(binary_oarchive& oa, T const& t)
	{
		oa.m_impl->save(&t, sizeof(T));
	}

	std::unique_ptr<binary_oarchive_impl_base>	m_impl;
};

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_BINARY_OARCHIVE_HPP
