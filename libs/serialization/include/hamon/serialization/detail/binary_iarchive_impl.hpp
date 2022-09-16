/**
 *	@file	binary_iarchive_impl.hpp
 *
 *	@brief	binary_iarchive_implの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_BINARY_IARCHIVE_IMPL_HPP
#define HAMON_SERIALIZATION_DETAIL_BINARY_IARCHIVE_IMPL_HPP

#include <istream>	// basic_istream
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
void load_binary(std::basic_istream<CharT, Traits>& is, void* p, std::size_t size)
{
	auto pbuf = is.rdbuf();

	auto const count = (size + (sizeof(CharT) - 1)) / sizeof(CharT);
	if (size % sizeof(CharT) == 0)
	{
		// size が sizeof(CharT) の倍数のときはそのまま読み込めば良い
		pbuf->sgetn(static_cast<CharT*>(p), count);
	}
	else
	{
		// そうでないときは、一時バッファに読み込んでからコピーする
		std::vector<CharT> buf(count);	// TODO basic_stringを使ったほうが、countが小さい場合に高速かもしれない
		pbuf->sgetn(buf.data(), count);
		std::memcpy(p, buf.data(), size);
	}

	// データにEOF(-1)が含まれていた場合にeofビットが立って、
	// それ以降の読み込みが行われなくなってしまう
	pbuf->pubseekoff(0, std::ios::cur, std::ios::in);	// eofビットを下ろす
}

class binary_iarchive_impl_base
{
public:
	virtual ~binary_iarchive_impl_base()
	{
	}

	virtual void load(void* dst, std::size_t size) = 0;
};

template <typename IStream>
class binary_iarchive_impl
	: public binary_iarchive_impl_base
{
public:
	explicit binary_iarchive_impl(IStream& is)
		: m_is(is)
	{}

	void load(void* dst, std::size_t size) override
	{
		load_binary(m_is, dst, size);
	}

private:
	binary_iarchive_impl& operator=(binary_iarchive_impl const&) = delete;

	IStream&	m_is;
};

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_BINARY_IARCHIVE_IMPL_HPP
