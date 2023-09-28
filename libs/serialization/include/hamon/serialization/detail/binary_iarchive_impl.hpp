/**
 *	@file	binary_iarchive_impl.hpp
 *
 *	@brief	binary_iarchive_implの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_BINARY_IARCHIVE_IMPL_HPP
#define HAMON_SERIALIZATION_DETAIL_BINARY_IARCHIVE_IMPL_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstring/memcpy.hpp>
#include <hamon/vector.hpp>
#include <istream>	// basic_istream

namespace hamon
{

namespace serialization
{

namespace detail
{

template <typename CharT, typename Traits>
void load_binary(std::basic_istream<CharT, Traits>& is, void* p, hamon::size_t size)
{
	auto pbuf = is.rdbuf();

	auto const count = (size + (sizeof(CharT) - 1)) / sizeof(CharT);
	if (size % sizeof(CharT) == 0)
	{
		// size が sizeof(CharT) の倍数のときはそのまま読み込めば良い
		pbuf->sgetn(static_cast<CharT*>(p), static_cast<std::streamsize>(count));
	}
	else
	{
		// そうでないときは、一時バッファに読み込んでからコピーする
		hamon::vector<CharT> buf(count);	// TODO basic_stringを使ったほうが、countが小さい場合に高速かもしれない
		pbuf->sgetn(buf.data(), static_cast<std::streamsize>(count));
		hamon::memcpy(p, buf.data(), size);
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

	virtual void load(void* dst, hamon::size_t size) = 0;
};

template <typename IStream>
class binary_iarchive_impl
	: public binary_iarchive_impl_base
{
public:
	explicit binary_iarchive_impl(IStream& is)
		: m_is(is)
	{}

	void load(void* dst, hamon::size_t size) override
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
