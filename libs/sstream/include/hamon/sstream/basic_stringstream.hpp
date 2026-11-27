/**
 *	@file	basic_stringstream.hpp
 *
 *	@brief	basic_stringstream の定義
 */

#ifndef HAMON_SSTREAM_BASIC_STRINGSTREAM_HPP
#define HAMON_SSTREAM_BASIC_STRINGSTREAM_HPP

#include <hamon/sstream/basic_stringstream_fwd.hpp>
#include <hamon/sstream/basic_stringbuf.hpp>
#include <hamon/ios/ios_base.hpp>
#include <hamon/istream/basic_iostream.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/string/char_traits.hpp>
#include <hamon/string/basic_string.hpp>
#include <hamon/string_view/basic_string_view.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/move.hpp>

#if 1
namespace hamon
{

// 31.8.5 Class template basic_stringstream[stringstream]

template <typename charT, typename traits/* = char_traits<charT>*/, typename Allocator/* = allocator<charT>*/>
class basic_stringstream : public hamon::basic_iostream<charT, traits>
{
private:
	using base_type = hamon::basic_iostream<charT, traits>;

public:
	using char_type = charT;
	using int_type = typename traits::int_type;
	using pos_type = typename traits::pos_type;
	using off_type = typename traits::off_type;
	using traits_type = traits;
	using allocator_type = Allocator;

	// [stringstream.cons], constructors
	basic_stringstream()
		: basic_stringstream(ios_base::out | ios_base::in)
	{}

	explicit
	basic_stringstream(ios_base::openmode which)
		// [stringstream.cons]/1
		: base_type(hamon::addressof(sb))
		, sb(which)
	{}

	explicit
	basic_stringstream(
		hamon::basic_string<charT, traits, Allocator> const& s,
		ios_base::openmode which = ios_base::out | ios_base::in)
		// [stringstream.cons]/2
		: base_type(hamon::addressof(sb))
		, sb(s, which)
	{}

	basic_stringstream(ios_base::openmode which, Allocator const& a)
		// [stringstream.cons]/3
		: base_type(hamon::addressof(sb))
		, sb(which, a)
	{}

	explicit
	basic_stringstream(
		hamon::basic_string<charT, traits, Allocator>&& s,
		ios_base::openmode which = ios_base::out | ios_base::in)
		// [stringstream.cons]/4
		: base_type(hamon::addressof(sb))
#if 0	// TODO
		, sb(hamon::move(s), which)
#else
		, sb(std::basic_string<charT, traits, Allocator>(s.c_str()), which)
#endif
	{}

	template <typename SAlloc>
	basic_stringstream(
		hamon::basic_string<charT, traits, SAlloc> const& s,
		Allocator const& a)
		: basic_stringstream(s, ios_base::out | ios_base::in, a)
	{}

	template <typename SAlloc>
	basic_stringstream(
		hamon::basic_string<charT, traits, SAlloc> const& s,
		ios_base::openmode which,
		Allocator const& a)
		// [stringstream.cons]/5
		: base_type(hamon::addressof(sb))
		, sb(s, which, a)
	{}

	template <typename SAlloc,
		// [stringstream.cons]/6
		typename = hamon::enable_if_t<
			!hamon::is_same_v<SAlloc, Allocator>>>
	explicit
	basic_stringstream(
		hamon::basic_string<charT, traits, SAlloc> const& s,
		ios_base::openmode which = ios_base::out | ios_base::in)
		// [stringstream.cons]/7
		: base_type(hamon::addressof(sb))
		, sb(s, which)
	{}

#if 0	// TODO
	template <typename T,
		// [stringstream.cons]/9
		typename = hamon::enable_if_t<
			hamon::is_convertible_v<T const&, hamon::basic_string_view<charT, traits>>>>
	explicit
	basic_stringstream(T const& t,
		ios_base::openmode which = ios_base::out | ios_base::in)
		// [stringstream.cons]/10
		: base_type(hamon::addressof(sb))
		, sb(t, which, Allocator())	// [stringstream.cons]/8
	{}

	template <typename T,
		// [stringstream.cons]/9
		typename = hamon::enable_if_t<
			hamon::is_convertible_v<T const&, hamon::basic_string_view<charT, traits>>>>
	basic_stringstream(T const& t, Allocator const& a)
		// [stringstream.cons]/10
		: base_type(hamon::addressof(sb))
		, sb(t, ios_base::out | ios_base::in, a)	// [stringstream.cons]/8
	{}

	template <typename T,
		// [stringstream.cons]/9
		typename = hamon::enable_if_t<
			hamon::is_convertible_v<T const&, hamon::basic_string_view<charT, traits>>>>
	basic_stringstream(T const& t, ios_base::openmode which, Allocator const& a)
		// [stringstream.cons]/10
		: base_type(hamon::addressof(sb))
		, sb(t, which, a)
	{}
#endif

	basic_stringstream(basic_stringstream const&) = delete;

	basic_stringstream(basic_stringstream&& rhs)
		// [stringstream.cons]/11
		: base_type(hamon::move(rhs))
		, sb(hamon::move(rhs.sb))
	{
		// [stringstream.cons]/11
		hamon::basic_istream<charT, traits>::set_rdbuf(hamon::addressof(sb));
	}

	basic_stringstream& operator=(basic_stringstream const&) = delete;

	basic_stringstream& operator=(basic_stringstream&& rhs)
	{
		base_type::operator=(hamon::move(rhs));
		sb = hamon::move(rhs.sb);
		return *this;
	}

	// [stringstream.swap], swap
	void swap(basic_stringstream& rhs)
	{
		// [stringstream.swap]/1
		base_type::swap(rhs);
		sb.swap(rhs.sb);
	}

	// [stringstream.members], members
	hamon::basic_stringbuf<charT, traits, Allocator>* rdbuf() const
	{
		// [stringstream.members]/1
		return const_cast<hamon::basic_stringbuf<charT, traits, Allocator>*>(hamon::addressof(sb));
	}

	hamon::basic_string<charT, traits, Allocator> str() const&
	{
		// [stringstream.members]/2
		return rdbuf()->str();
	}

	template <typename SAlloc>
	hamon::basic_string<charT, traits, SAlloc> str(SAlloc const& sa) const
	{
		// [stringstream.members]/3
		return rdbuf()->str(sa);
	}

	hamon::basic_string<charT, traits, Allocator> str() &&
	{
		// [stringstream.members]/4
		return hamon::move(*rdbuf()).str();
	}

	hamon::basic_string_view<charT, traits> view() const noexcept
	{
		// [stringstream.members]/5
		return rdbuf()->view();
	}

	void str(hamon::basic_string<charT, traits, Allocator> const& s)
	{
		// [stringstream.members]/6
		rdbuf()->str(s);
	}

	template <typename SAlloc>
	void str(hamon::basic_string<charT, traits, SAlloc> const& s)
	{
		// [stringstream.members]/7
		rdbuf()->str(s);
	}

	void str(hamon::basic_string<charT, traits, Allocator>&& s)
	{
		// [stringstream.members]/8
		rdbuf()->str(hamon::move(s));
	}

	template <typename T,
		// [stringstream.members]/9
		typename = hamon::enable_if_t<
			hamon::is_convertible_v<T const&, hamon::basic_string_view<charT, traits>>>>
	void str(T const& t)
	{
		// [stringstream.members]/10
		rdbuf()->str(t);
	}

private:
	hamon::basic_stringbuf<charT, traits, Allocator> sb;   // exposition only
};

template <typename charT, typename traits, typename Allocator>
void swap(
	basic_stringstream<charT, traits, Allocator>& x,
	basic_stringstream<charT, traits, Allocator>& y)
{
	// [stringstream.swap]/2
	x.swap(y);
}

}	// namespace hamon
#endif

#endif // HAMON_SSTREAM_BASIC_STRINGSTREAM_HPP
