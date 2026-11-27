/**
 *	@file	basic_ostringstream.hpp
 *
 *	@brief	basic_ostringstream の定義
 */

#ifndef HAMON_SSTREAM_BASIC_OSTRINGSTREAM_HPP
#define HAMON_SSTREAM_BASIC_OSTRINGSTREAM_HPP

#include <hamon/sstream/basic_ostringstream_fwd.hpp>
#include <hamon/sstream/basic_stringbuf.hpp>
#include <hamon/ios/ios_base.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/ostream/basic_ostream.hpp>
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

// 31.8.4 Class template basic_ostringstream[ostringstream]

template <typename charT, typename traits/* = char_traits<charT>*/, typename Allocator/* = allocator<charT>*/>
class basic_ostringstream : public hamon::basic_ostream<charT, traits>
{
private:
	using base_type = hamon::basic_ostream<charT, traits>;

public:
	using char_type = charT;
	using int_type = typename traits::int_type;
	using pos_type = typename traits::pos_type;
	using off_type = typename traits::off_type;
	using traits_type = traits;
	using allocator_type = Allocator;

	// [ostringstream.cons], constructors
	basic_ostringstream()
		: basic_ostringstream(ios_base::out)
	{}

	explicit
	basic_ostringstream(ios_base::openmode which)
		// [ostringstream.cons]/1
		: base_type(hamon::addressof(sb))
		, sb(which | ios_base::out)
	{}

	explicit
	basic_ostringstream(
		hamon::basic_string<charT, traits, Allocator> const& s,
		ios_base::openmode which = ios_base::out)
		// [ostringstream.cons]/2
		: base_type(hamon::addressof(sb))
		, sb(s, which | ios_base::out)
	{}

	basic_ostringstream(ios_base::openmode which, Allocator const& a)
		// [ostringstream.cons]/3
		: base_type(hamon::addressof(sb))
		, sb(which | ios_base::out, a)
	{}

	explicit
	basic_ostringstream(
		hamon::basic_string<charT, traits, Allocator>&& s,
		ios_base::openmode which = ios_base::out)
		// [ostringstream.cons]/4
		: base_type(hamon::addressof(sb))
		, sb(hamon::move(s), which | ios_base::out)
	{}

	template <typename SAlloc>
	basic_ostringstream(
		hamon::basic_string<charT, traits, SAlloc> const& s,
		Allocator const& a)
		: basic_ostringstream(s, ios_base::out, a)
	{}

	template <typename SAlloc>
	basic_ostringstream(
		hamon::basic_string<charT, traits, SAlloc> const& s,
		ios_base::openmode which,
		Allocator const& a)
		// [ostringstream.cons]/5
		: base_type(hamon::addressof(sb))
		, sb(s, which | ios_base::out, a)
	{}

	template <typename SAlloc,
		// [ostringstream.cons]/6
		typename = hamon::enable_if_t<
			!hamon::is_same_v<SAlloc, Allocator>>>
	explicit
	basic_ostringstream(
		hamon::basic_string<charT, traits, SAlloc> const& s,
		ios_base::openmode which = ios_base::out)
		// [ostringstream.cons]/7
		: base_type(hamon::addressof(sb))
		, sb(s, which | ios_base::out)
	{}

#if 0	// TODO
	template <typename T,
		// [ostringstream.cons]/9
		typename = hamon::enable_if_t<
			hamon::is_convertible_v<T const&, hamon::basic_string_view<charT, traits>>>>
	explicit
	basic_ostringstream(T const& t, ios_base::openmode which = ios_base::out)
		// [ostringstream.cons]/10
		: base_type(hamon::addressof(sb))
		, sb(t, which | ios_base::out, Allocator())	// [ostringstream.cons]/8
	{}

	template <typename T,
		// [ostringstream.cons]/9
		typename = hamon::enable_if_t<
			hamon::is_convertible_v<T const&, hamon::basic_string_view<charT, traits>>>>
	basic_ostringstream(T const& t, Allocator const& a)
		// [ostringstream.cons]/10
		: base_type(hamon::addressof(sb))
		, sb(t, ios_base::out, a)	// [ostringstream.cons]/8
	{}

	template <typename T,
		// [ostringstream.cons]/9
		typename = hamon::enable_if_t<
			hamon::is_convertible_v<T const&, hamon::basic_string_view<charT, traits>>>>
	basic_ostringstream(T const& t, ios_base::openmode which, Allocator const& a)
		// [ostringstream.cons]/10
		: base_type(hamon::addressof(sb))
		, sb(t, which | ios_base::out, a)
	{}
#endif

	basic_ostringstream(basic_ostringstream const&) = delete;

	basic_ostringstream(basic_ostringstream&& rhs)
		// [ostringstream.cons]/11
		: base_type(hamon::move(rhs))
		, sb(hamon::move(rhs.sb))
	{
		// [ostringstream.cons]/11
		base_type::set_rdbuf(hamon::addressof(sb));
	}

	basic_ostringstream& operator=(basic_ostringstream const&) = delete;

	basic_ostringstream& operator=(basic_ostringstream&& rhs)
	{
		base_type::operator=(hamon::move(rhs));
		sb = hamon::move(rhs.sb);
		return *this;
	}

	// [ostringstream.swap], swap
	void swap(basic_ostringstream& rhs)
	{
		// [ostringstream.swap]/1
		base_type::swap(rhs);
		sb.swap(rhs.sb);
	}

	// [ostringstream.members], members
	hamon::basic_stringbuf<charT, traits, Allocator>* rdbuf() const
	{
		// [ostringstream.members]/1
		return const_cast<hamon::basic_stringbuf<charT, traits, Allocator>*>(hamon::addressof(sb));
	}

	hamon::basic_string<charT, traits, Allocator> str() const&
	{
		// [ostringstream.members]/2
		return rdbuf()->str();
	}

	template <typename SAlloc>
	hamon::basic_string<charT, traits, SAlloc> str(SAlloc const& sa) const
	{
		// [ostringstream.members]/3
		return rdbuf()->str(sa);
	}

	hamon::basic_string<charT, traits, Allocator> str() &&
	{
		// [ostringstream.members]/4
		return hamon::move(*rdbuf()).str();
	}

	hamon::basic_string_view<charT, traits> view() const noexcept
	{
		// [ostringstream.members]/5
		return rdbuf()->view();
	}

	void str(hamon::basic_string<charT, traits, Allocator> const& s)
	{
		// [ostringstream.members]/6
		rdbuf()->str(s);
	}

	template <typename SAlloc>
	void str(hamon::basic_string<charT, traits, SAlloc> const& s)
	{
		// [ostringstream.members]/7
		rdbuf()->str(s);
	}

	void str(hamon::basic_string<charT, traits, Allocator>&& s)
	{
		// [ostringstream.members]/8
		rdbuf()->str(hamon::move(s));
	}

	template <typename T,
		// [ostringstream.members]/9
		typename = hamon::enable_if_t<
			hamon::is_convertible_v<T const&, hamon::basic_string_view<charT, traits>>>>
	void str(T const& t)
	{
		// [ostringstream.members]/10
		rdbuf()->str(t);
	}

private:
	hamon::basic_stringbuf<charT, traits, Allocator> sb;   // exposition only
};

template <typename charT, typename traits, typename Allocator>
void swap(
	basic_ostringstream<charT, traits, Allocator>& x,
	basic_ostringstream<charT, traits, Allocator>& y)
{
	// [ostringstream.swap]/2
	x.swap(y);
}

}	// namespace hamon
#endif

#endif // HAMON_SSTREAM_BASIC_OSTRINGSTREAM_HPP
