/**
 *	@file	basic_streambuf.hpp
 *
 *	@brief	basic_streambuf の定義
 */

#ifndef HAMON_STREAMBUF_BASIC_STREAMBUF_HPP
#define HAMON_STREAMBUF_BASIC_STREAMBUF_HPP

#include <streambuf>

namespace hamon
{

using std::basic_streambuf;

#if 0	// TODO

// 31.6.3 Class template basic_streambuf[streambuf]

// 31.6.3.1 General[streambuf.general]

template <typename charT, typename traits = char_traits<charT>>
class basic_streambuf
{
public:
	using char_type = charT;
	using int_type = traits::int_type;
	using pos_type = traits::pos_type;
	using off_type = traits::off_type;
	using traits_type = traits;

	virtual ~basic_streambuf();

	// [streambuf.locales], locales
	locale   pubimbue(const locale& loc);
	locale   getloc() const;

	// [streambuf.buffer], buffer and positioning
	basic_streambuf* pubsetbuf(char_type* s, streamsize n);
	pos_type pubseekoff(off_type off, ios_base::seekdir way,
		ios_base::openmode which = ios_base::in | ios_base::out);
	pos_type pubseekpos(pos_type sp,
		ios_base::openmode which = ios_base::in | ios_base::out);
	int pubsync();

	// get and put areas
	// [streambuf.pub.get], get area
	streamsize in_avail();
	int_type snextc();
	int_type sbumpc();
	int_type sgetc();
	streamsize sgetn(char_type* s, streamsize n);

	// [streambuf.pub.pback], putback
	int_type sputbackc(char_type c);
	int_type sungetc();

	// [streambuf.pub.put], put area
	int_type   sputc(char_type c);
	streamsize sputn(const char_type* s, streamsize n);

protected:
	basic_streambuf();
	basic_streambuf(const basic_streambuf& rhs);
	basic_streambuf& operator=(const basic_streambuf& rhs);

	void swap(basic_streambuf& rhs);

	// [streambuf.get.area], get area access
	char_type* eback() const;
	char_type* gptr()  const;
	char_type* egptr() const;
	void       gbump(int n);
	void       setg(char_type* gbeg, char_type* gnext, char_type* gend);

	// [streambuf.put.area], put area access
	char_type* pbase() const;
	char_type* pptr() const;
	char_type* epptr() const;
	void       pbump(int n);
	void       setp(char_type* pbeg, char_type* pend);

	// [streambuf.virtuals], virtual functions
	// [streambuf.virt.locales], locales
	virtual void imbue(const locale& loc);

	// [streambuf.virt.buffer], buffer management and positioning
	virtual basic_streambuf* setbuf(char_type* s, streamsize n);
	virtual pos_type seekoff(off_type off, ios_base::seekdir way,
		ios_base::openmode which = ios_base::in | ios_base::out);
	virtual pos_type seekpos(pos_type sp,
		ios_base::openmode which = ios_base::in | ios_base::out);
	virtual int sync();

	// [streambuf.virt.get], get area
	virtual streamsize showmanyc();
	virtual streamsize xsgetn(char_type* s, streamsize n);
	virtual int_type   underflow();
	virtual int_type   uflow();

	// [streambuf.virt.pback], putback
	virtual int_type   pbackfail(int_type c = traits::eof());

	// [streambuf.virt.put], put area
	virtual streamsize xsputn(const char_type* s, streamsize n);
	virtual int_type   overflow(int_type c = traits::eof());
};

#endif

}	// namespace hamon

#endif // HAMON_STREAMBUF_BASIC_STREAMBUF_HPP
