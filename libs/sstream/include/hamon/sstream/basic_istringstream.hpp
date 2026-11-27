/**
 *	@file	basic_istringstream.hpp
 *
 *	@brief	basic_istringstream の定義
 */

#ifndef HAMON_SSTREAM_BASIC_ISTRINGSTREAM_HPP
#define HAMON_SSTREAM_BASIC_ISTRINGSTREAM_HPP

#include <hamon/sstream/basic_ostringstream_fwd.hpp>
#include <hamon/sstream/basic_stringbuf.hpp>
#include <hamon/ios/ios_base.hpp>
#include <hamon/istream/basic_istream.hpp>
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

// 31.8.3 Class template basic_istringstream[istringstream]

template <typename charT, typename traits/* = char_traits<charT>*/, typename Allocator/* = allocator<charT>*/>
class basic_istringstream : public hamon::basic_istream<charT, traits>
{
private:
	using base_type = hamon::basic_istream<charT, traits>;

public:
	using char_type = charT;
	using int_type = typename traits::int_type;
	using pos_type = typename traits::pos_type;
	using off_type = typename traits::off_type;
	using traits_type = traits;
	using allocator_type = Allocator;

	// [istringstream.cons], constructors
	basic_istringstream()
		: basic_istringstream(ios_base::in)
	{}

	explicit
	basic_istringstream(ios_base::openmode which)
		// [istringstream.cons]/1
		: base_type(hamon::addressof(sb))
		, sb(which | ios_base::in)
	{}

	explicit
	basic_istringstream(
		hamon::basic_string<charT, traits, Allocator> const& s,
		ios_base::openmode which = ios_base::in)
		// [istringstream.cons]/2
		: base_type(hamon::addressof(sb))
		, sb(s, which | ios_base::in)
	{}

	basic_istringstream(ios_base::openmode which, Allocator const& a)
		// [istringstream.cons]/3
		: base_type(hamon::addressof(sb))
		, sb(which | ios_base::in, a)
	{}

	explicit
	basic_istringstream(
		hamon::basic_string<charT, traits, Allocator>&& s,
		ios_base::openmode which = ios_base::in)
		// [istringstream.cons]/4
		: base_type(hamon::addressof(sb))
#if 0	// TODO
		, sb(hamon::move(s), which | ios_base::in)
#else
		, sb(std::basic_string<charT, traits, Allocator>(s.c_str()), which | ios_base::in)
#endif
	{}

	template <typename SAlloc>
	basic_istringstream(
		hamon::basic_string<charT, traits, SAlloc> const& s,
		Allocator const& a)
		: basic_istringstream(s, ios_base::in, a)
	{}

	template <typename SAlloc>
	basic_istringstream(
		hamon::basic_string<charT, traits, SAlloc> const& s,
		ios_base::openmode which,
		Allocator const& a)
		// [istringstream.cons]/5
		: base_type(hamon::addressof(sb))
		, sb(s, which | ios_base::in, a)
	{}

	template <typename SAlloc,
		// [istringstream.cons]/6
		typename = hamon::enable_if_t<
			!hamon::is_same_v<SAlloc, Allocator>>>
	explicit
	basic_istringstream(
		hamon::basic_string<charT, traits, SAlloc> const& s,
		ios_base::openmode which = ios_base::in)
		// [istringstream.cons]/7
		: base_type(hamon::addressof(sb))
		, sb(s, which | ios_base::in)
	{}

#if 0	// TODO
	template <typename T,
		// [istringstream.cons]/9
		typename = hamon::enable_if_t<
			hamon::is_convertible_v<T const&, hamon::basic_string_view<charT, traits>>>>
	explicit
	basic_istringstream(T const& t, ios_base::openmode which = ios_base::in)
		// [istringstream.cons]/10
		: base_type(hamon::addressof(sb))
		, sb(t, which | ios_base::in, Allocator())	// [istringstream.cons]/8
	{}

	template <typename T,
		// [istringstream.cons]/9
		typename = hamon::enable_if_t<
			hamon::is_convertible_v<T const&, hamon::basic_string_view<charT, traits>>>>
	basic_istringstream(T const& t, Allocator const& a)
		// [istringstream.cons]/10
		: base_type(hamon::addressof(sb))
		, sb(t, ios_base::in, a)	// [istringstream.cons]/8
	{}

	template <typename T,
		// [istringstream.cons]/9
		typename = hamon::enable_if_t<
			hamon::is_convertible_v<T const&, hamon::basic_string_view<charT, traits>>>>
	basic_istringstream(T const& t, ios_base::openmode which, Allocator const& a)
		// [istringstream.cons]/10
		: base_type(hamon::addressof(sb))
		, sb(t, which | ios_base::in, a)
	{}
#endif

	basic_istringstream(basic_istringstream const&) = delete;

	basic_istringstream(basic_istringstream&& rhs)
		// [istringstream.cons]/11
		: base_type(hamon::move(rhs))
		, sb(hamon::move(rhs.sb))
	{
		// [istringstream.cons]/11
		base_type::set_rdbuf(hamon::addressof(sb));
	}

	basic_istringstream& operator=(basic_istringstream const&) = delete;

	basic_istringstream& operator=(basic_istringstream&& rhs)
	{
		base_type::operator=(hamon::move(rhs));
		sb = hamon::move(rhs.sb);
		return *this;
	}

	// [istringstream.swap], swap
	void swap(basic_istringstream& rhs)
	{
		// [istringstream.swap]/1
		base_type::swap(rhs);
		sb.swap(rhs.sb);
	}

	// [istringstream.members], members
	hamon::basic_stringbuf<charT, traits, Allocator>* rdbuf() const
	{
		// [istringstream.members]/1
		return const_cast<hamon::basic_stringbuf<charT, traits, Allocator>*>(hamon::addressof(sb));
	}

	hamon::basic_string<charT, traits, Allocator> str() const&
	{
		// [istringstream.members]/2
		return rdbuf()->str();
	}

	template <typename SAlloc>
	hamon::basic_string<charT, traits, SAlloc> str(SAlloc const& sa) const
	{
		// [istringstream.members]/3
		return rdbuf()->str(sa);
	}

	hamon::basic_string<charT, traits, Allocator> str() &&
	{
		// [istringstream.members]/4
		return hamon::move(*rdbuf()).str();
	}

	hamon::basic_string_view<charT, traits> view() const noexcept
	{
		// [istringstream.members]/5
		return rdbuf()->view();
	}

	void str(hamon::basic_string<charT, traits, Allocator> const& s)
	{
		// [istringstream.members]/6
		rdbuf()->str(s);
	}

	template <typename SAlloc>
	void str(hamon::basic_string<charT, traits, SAlloc> const& s)
	{
		// [istringstream.members]/7
		rdbuf()->str(s);
	}

	void str(hamon::basic_string<charT, traits, Allocator>&& s)
	{
		// [istringstream.members]/8
		rdbuf()->str(hamon::move(s));
	}

	template <typename T,
		// [ostringstream.members]/9
		typename = hamon::enable_if_t<
			hamon::is_convertible_v<T const&, hamon::basic_string_view<charT, traits>>>>
	void str(T const& t)
	{
		// [istringstream.members]/10
		rdbuf()->str(t);
	}

private:
	hamon::basic_stringbuf<charT, traits, Allocator> sb;   // exposition only
};

template <typename charT, typename traits, typename Allocator>
void swap(
	basic_istringstream<charT, traits, Allocator>& x,
	basic_istringstream<charT, traits, Allocator>& y)
{
	// [istringstream.swap]/2
	x.swap(y);
}

}	// namespace hamon
#endif

#endif // HAMON_SSTREAM_BASIC_ISTRINGSTREAM_HPP
