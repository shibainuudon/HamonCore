/**
 *	@file	binary_oarchive_impl.hpp
 *
 *	@brief	binary_oarchive_implの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_BINARY_OARCHIVE_IMPL_HPP
#define HAMON_SERIALIZATION_DETAIL_BINARY_OARCHIVE_IMPL_HPP

#include <ostream>	// basic_ostream
#include <cstddef>
#include <vector>
#include <cstring>	// memcpy

namespace hamon
{

namespace serialization
{

namespace detail
{

template <typename CharT, typename Traits>
void save_binary(std::basic_ostream<CharT, Traits>& os, void const* p, std::size_t size)
{
	auto pbuf = os.rdbuf();
	auto const count = (size + (sizeof(CharT) - 1)) / sizeof(CharT);
	if (size % sizeof(CharT) == 0)
	{
		// size が sizeof(CharT) の倍数のときはそのまま書き込めば良い
		pbuf->sputn(static_cast<CharT const*>(p), static_cast<std::streamsize>(count));
	}
	else
	{
		// そうでないときは、一時バッファにコピーしてから書き込む
		std::vector<CharT> buf(count);	// TODO basic_stringを使ったほうが、countが小さい場合に高速かもしれない
		std::memcpy(buf.data(), p, size);
		pbuf->sputn(buf.data(), static_cast<std::streamsize>(count));
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

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_BINARY_OARCHIVE_IMPL_HPP
