/**
 *	@file	unit_test_string_cons.cpp
 *
 *	@brief	コンストラクタのテスト
 *
 *	constexpr basic_string() noexcept(noexcept(Allocator())) : basic_string(Allocator()) { }
 *	constexpr explicit basic_string(const Allocator& a) noexcept;
 *	constexpr basic_string(const basic_string& str);
 *	constexpr basic_string(basic_string&& str) noexcept;
 *	constexpr basic_string(const basic_string& str, size_type pos, const Allocator& a = Allocator());
 *	constexpr basic_string(const basic_string& str, size_type pos, size_type n, const Allocator& a = Allocator());
 *	constexpr basic_string(basic_string&& str, size_type pos, const Allocator& a = Allocator());
 *	constexpr basic_string(basic_string&& str, size_type pos, size_type n, const Allocator& a = Allocator());
 *	template<class T>
 *	constexpr basic_string(const T& t, size_type pos, size_type n, const Allocator& a = Allocator());
 *	template<class T>
 *	constexpr explicit basic_string(const T& t, const Allocator& a = Allocator());
 *	constexpr basic_string(const charT* s, size_type n, const Allocator& a = Allocator());
 *	constexpr basic_string(const charT* s, const Allocator& a = Allocator());
 *	basic_string(nullptr_t) = delete;
 *	constexpr basic_string(size_type n, charT c, const Allocator& a = Allocator());
 *	template<class InputIterator>
 *	constexpr basic_string(InputIterator begin, InputIterator end, const Allocator& a = Allocator());
 *	template<container-compatible-range<charT> R>
 *	constexpr basic_string(from_range_t, R&& rg, const Allocator& a = Allocator());
 *	constexpr basic_string(initializer_list<charT>, const Allocator& = Allocator());
 *	constexpr basic_string(const basic_string&, const Allocator&);
 *	constexpr basic_string(basic_string&&, const Allocator&);
 */

#include <hamon/string/basic_string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <initializer_list>
#include "constexpr_test.hpp"
#include "string_test_helper.hpp"

HAMON_WARNING_PUSH()
#if defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION >= 120000)
HAMON_WARNING_DISABLE_GCC("-Wstringop-overread")
#endif

namespace hamon_test
{
namespace string_test
{
namespace cons_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
ConsTest()
{
	using string = hamon::basic_string<CharT>;
	using Allocator = typename string::allocator_type;
	using SizeType = typename string::size_type;
	using Helper = StringTestHelper<CharT>;
	
	// constexpr basic_string() noexcept(noexcept(Allocator()))
	static_assert( hamon::is_default_constructible           <string>::value, "is_default_constructible");
	static_assert( hamon::is_nothrow_default_constructible   <string>::value, "is_nothrow_default_constructible");
	static_assert( hamon::is_implicitly_default_constructible<string>::value, "is_implicitly_default_constructible");
	static_assert(!hamon::is_trivially_default_constructible <string>::value, "is_trivially_default_constructible");
	{
		string const s;
		VERIFY(s.size() == 0);
	}

	// constexpr explicit basic_string(const Allocator& a) noexcept;
	static_assert( hamon::is_constructible           <string, const Allocator&>::value, "is_constructible");
	static_assert( hamon::is_nothrow_constructible   <string, const Allocator&>::value, "is_nothrow_constructible");
	static_assert(!hamon::is_implicitly_constructible<string, const Allocator&>::value, "is_implicitly_constructible");
	static_assert(!hamon::is_trivially_constructible <string, const Allocator&>::value, "is_trivially_constructible");
	{
		Allocator const alloc{};
		string const s(alloc);
		VERIFY(s.size() == 0);
	}

	// constexpr basic_string(const basic_string& str);
	static_assert( hamon::is_copy_constructible           <string>::value, "is_copy_constructible");
	static_assert(!hamon::is_nothrow_copy_constructible   <string>::value, "is_nothrow_copy_constructible");
	static_assert( hamon::is_implicitly_copy_constructible<string>::value, "is_implicitly_copy_constructible");
	static_assert(!hamon::is_trivially_copy_constructible <string>::value, "is_trivially_copy_constructible");
	{
		string const s1;
		string const s2{s1};
		VERIFY(s2.size() == 0);
	}
	{
		string const s1{Helper::abcde()};
		string const s2{s1};
		VERIFY(s2.size() == 5);
		VERIFY(s2[0] == Helper::abcde()[0]);
		VERIFY(s2[1] == Helper::abcde()[1]);
		VERIFY(s2[2] == Helper::abcde()[2]);
		VERIFY(s2[3] == Helper::abcde()[3]);
		VERIFY(s2[4] == Helper::abcde()[4]);
	}

	// constexpr basic_string(basic_string&& str) noexcept;
	static_assert( hamon::is_move_constructible           <string>::value, "is_move_constructible");
	static_assert( hamon::is_nothrow_move_constructible   <string>::value, "is_nothrow_move_constructible");
	static_assert( hamon::is_implicitly_move_constructible<string>::value, "is_implicitly_move_constructible");
	static_assert(!hamon::is_trivially_move_constructible <string>::value, "is_trivially_move_constructible");
	{
		string s1;
		string s2{hamon::move(s1)};
		VERIFY(s2.size() == 0);
	}
	{
		string s1{Helper::abcde()};
		string s2{hamon::move(s1)};
		VERIFY(s2.size() == 5);
		VERIFY(s2[0] == Helper::abcde()[0]);
		VERIFY(s2[1] == Helper::abcde()[1]);
		VERIFY(s2[2] == Helper::abcde()[2]);
		VERIFY(s2[3] == Helper::abcde()[3]);
		VERIFY(s2[4] == Helper::abcde()[4]);
	}

	// constexpr basic_string(const basic_string& str, size_type pos, const Allocator& a = Allocator());
	static_assert( hamon::is_constructible           <string, const string&, SizeType>::value, "is_constructible");
	static_assert(!hamon::is_nothrow_constructible   <string, const string&, SizeType>::value, "is_nothrow_constructible");
	static_assert( hamon::is_implicitly_constructible<string, const string&, SizeType>::value, "is_implicitly_constructible");
	static_assert(!hamon::is_trivially_constructible <string, const string&, SizeType>::value, "is_trivially_constructible");
	static_assert( hamon::is_constructible           <string, const string&, SizeType, const Allocator&>::value, "is_constructible");
	static_assert(!hamon::is_nothrow_constructible   <string, const string&, SizeType, const Allocator&>::value, "is_nothrow_constructible");
	static_assert( hamon::is_implicitly_constructible<string, const string&, SizeType, const Allocator&>::value, "is_implicitly_constructible");
	static_assert(!hamon::is_trivially_constructible <string, const string&, SizeType, const Allocator&>::value, "is_trivially_constructible");
	{
		string const s1{Helper::abcde()};
		string const s2{s1, 1};
		VERIFY(s2.size() == 4);
		VERIFY(s2[0] == Helper::abcde()[1]);
		VERIFY(s2[1] == Helper::abcde()[2]);
		VERIFY(s2[2] == Helper::abcde()[3]);
		VERIFY(s2[3] == Helper::abcde()[4]);
	}
	{
		Allocator const alloc{};
		string const s1{Helper::abcde()};
		string const s2{s1, 2, alloc};
		VERIFY(s2.size() == 3);
		VERIFY(s2[0] == Helper::abcde()[2]);
		VERIFY(s2[1] == Helper::abcde()[3]);
		VERIFY(s2[2] == Helper::abcde()[4]);
	}

	// constexpr basic_string(const basic_string& str, size_type pos, size_type n, const Allocator& a = Allocator());
	static_assert( hamon::is_constructible           <string, const string&, SizeType, SizeType>::value, "is_constructible");
	static_assert(!hamon::is_nothrow_constructible   <string, const string&, SizeType, SizeType>::value, "is_nothrow_constructible");
	static_assert( hamon::is_implicitly_constructible<string, const string&, SizeType, SizeType>::value, "is_implicitly_constructible");
	static_assert(!hamon::is_trivially_constructible <string, const string&, SizeType, SizeType>::value, "is_trivially_constructible");
	static_assert( hamon::is_constructible           <string, const string&, SizeType, SizeType, const Allocator&>::value, "is_constructible");
	static_assert(!hamon::is_nothrow_constructible   <string, const string&, SizeType, SizeType, const Allocator&>::value, "is_nothrow_constructible");
	static_assert( hamon::is_implicitly_constructible<string, const string&, SizeType, SizeType, const Allocator&>::value, "is_implicitly_constructible");
	static_assert(!hamon::is_trivially_constructible <string, const string&, SizeType, SizeType, const Allocator&>::value, "is_trivially_constructible");
	{
		string const s1{Helper::abcde()};
		string const s2{s1, 1, 3};
		VERIFY(s2.size() == 3);
		VERIFY(s2[0] == Helper::abcde()[1]);
		VERIFY(s2[1] == Helper::abcde()[2]);
		VERIFY(s2[2] == Helper::abcde()[3]);
	}
	{
		Allocator const alloc{};
		string const s1{Helper::abcde()};
		string const s2{s1, 2, 2, alloc};
		VERIFY(s2.size() == 2);
		VERIFY(s2[0] == Helper::abcde()[2]);
		VERIFY(s2[1] == Helper::abcde()[3]);
	}

	// constexpr basic_string(basic_string&& str, size_type pos, const Allocator& a = Allocator());
	static_assert( hamon::is_constructible           <string, string&&, SizeType>::value, "is_constructible");
	static_assert(!hamon::is_nothrow_constructible   <string, string&&, SizeType>::value, "is_nothrow_constructible");
	static_assert( hamon::is_implicitly_constructible<string, string&&, SizeType>::value, "is_implicitly_constructible");
	static_assert(!hamon::is_trivially_constructible <string, string&&, SizeType>::value, "is_trivially_constructible");
	static_assert( hamon::is_constructible           <string, string&&, SizeType, const Allocator&>::value, "is_constructible");
	static_assert(!hamon::is_nothrow_constructible   <string, string&&, SizeType, const Allocator&>::value, "is_nothrow_constructible");
	static_assert( hamon::is_implicitly_constructible<string, string&&, SizeType, const Allocator&>::value, "is_implicitly_constructible");
	static_assert(!hamon::is_trivially_constructible <string, string&&, SizeType, const Allocator&>::value, "is_trivially_constructible");
	{
		string s1{Helper::abcde()};
		string const s2{hamon::move(s1), 1};
		VERIFY(s2.size() == 4);
		VERIFY(s2[0] == Helper::abcde()[1]);
		VERIFY(s2[1] == Helper::abcde()[2]);
		VERIFY(s2[2] == Helper::abcde()[3]);
		VERIFY(s2[3] == Helper::abcde()[4]);
	}
	{
		Allocator const alloc{};
		string s1{Helper::abcde()};
		string const s2{hamon::move(s1), 2, alloc};
		VERIFY(s2.size() == 3);
		VERIFY(s2[0] == Helper::abcde()[2]);
		VERIFY(s2[1] == Helper::abcde()[3]);
		VERIFY(s2[2] == Helper::abcde()[4]);
	}

	// constexpr basic_string(basic_string&& str, size_type pos, size_type n, const Allocator& a = Allocator());
	static_assert( hamon::is_constructible           <string, string&&, SizeType, SizeType>::value, "is_constructible");
	static_assert(!hamon::is_nothrow_constructible   <string, string&&, SizeType, SizeType>::value, "is_nothrow_constructible");
	static_assert( hamon::is_implicitly_constructible<string, string&&, SizeType, SizeType>::value, "is_implicitly_constructible");
	static_assert(!hamon::is_trivially_constructible <string, string&&, SizeType, SizeType>::value, "is_trivially_constructible");
	static_assert( hamon::is_constructible           <string, string&&, SizeType, SizeType, const Allocator&>::value, "is_constructible");
	static_assert(!hamon::is_nothrow_constructible   <string, string&&, SizeType, SizeType, const Allocator&>::value, "is_nothrow_constructible");
	static_assert( hamon::is_implicitly_constructible<string, string&&, SizeType, SizeType, const Allocator&>::value, "is_implicitly_constructible");
	static_assert(!hamon::is_trivially_constructible <string, string&&, SizeType, SizeType, const Allocator&>::value, "is_trivially_constructible");
	{
		string s1{Helper::abcde()};
		string const s2{hamon::move(s1), 1, 3};
		VERIFY(s2.size() == 3);
		VERIFY(s2[0] == Helper::abcde()[1]);
		VERIFY(s2[1] == Helper::abcde()[2]);
		VERIFY(s2[2] == Helper::abcde()[3]);
	}
	{
		Allocator const alloc{};
		string s1{Helper::abcde()};
		string const s2{hamon::move(s1), 2, 2, alloc};
		VERIFY(s2.size() == 2);
		VERIFY(s2[0] == Helper::abcde()[2]);
		VERIFY(s2[1] == Helper::abcde()[3]);
	}

#if HAMON_CXX_STANDARD >= 17	// TODO
	using string_view = std::basic_string_view<CharT>;

	// template<class T>
	// constexpr basic_string(const T& t, size_type pos, size_type n, const Allocator& a = Allocator());
	static_assert( hamon::is_constructible           <string, const string_view&, SizeType, SizeType>::value, "is_constructible");
	static_assert(!hamon::is_nothrow_constructible   <string, const string_view&, SizeType, SizeType>::value, "is_nothrow_constructible");
	static_assert( hamon::is_implicitly_constructible<string, const string_view&, SizeType, SizeType>::value, "is_implicitly_constructible");
	static_assert(!hamon::is_trivially_constructible <string, const string_view&, SizeType, SizeType>::value, "is_trivially_constructible");
	static_assert( hamon::is_constructible           <string, const string_view&, SizeType, SizeType, const Allocator&>::value, "is_constructible");
	static_assert(!hamon::is_nothrow_constructible   <string, const string_view&, SizeType, SizeType, const Allocator&>::value, "is_nothrow_constructible");
	static_assert( hamon::is_implicitly_constructible<string, const string_view&, SizeType, SizeType, const Allocator&>::value, "is_implicitly_constructible");
	static_assert(!hamon::is_trivially_constructible <string, const string_view&, SizeType, SizeType, const Allocator&>::value, "is_trivially_constructible");
	{
		string_view const s1{Helper::abcde()};
		string const s2{s1, 1, 3};
		VERIFY(s2.size() == 3);
		VERIFY(s2[0] == Helper::abcde()[1]);
		VERIFY(s2[1] == Helper::abcde()[2]);
		VERIFY(s2[2] == Helper::abcde()[3]);
	}
	{
		Allocator const alloc{};
		string_view const s1{Helper::abcde()};
		string const s2{s1, 2, 2, alloc};
		VERIFY(s2.size() == 2);
		VERIFY(s2[0] == Helper::abcde()[2]);
		VERIFY(s2[1] == Helper::abcde()[3]);
	}

	// template<class T>
	// constexpr explicit basic_string(const T& t, const Allocator& a = Allocator());
	static_assert( hamon::is_constructible           <string, const string_view&>::value, "is_constructible");
	static_assert(!hamon::is_nothrow_constructible   <string, const string_view&>::value, "is_nothrow_constructible");
	static_assert(!hamon::is_implicitly_constructible<string, const string_view&>::value, "is_implicitly_constructible");
	static_assert(!hamon::is_trivially_constructible <string, const string_view&>::value, "is_trivially_constructible");
	static_assert( hamon::is_constructible           <string, const string_view&, const Allocator&>::value, "is_constructible");
	static_assert(!hamon::is_nothrow_constructible   <string, const string_view&, const Allocator&>::value, "is_nothrow_constructible");
	static_assert(!hamon::is_implicitly_constructible<string, const string_view&, const Allocator&>::value, "is_implicitly_constructible");
	static_assert(!hamon::is_trivially_constructible <string, const string_view&, const Allocator&>::value, "is_trivially_constructible");
	{
		string_view const s1{Helper::abcde()};
		string const s2{s1};
		VERIFY(s2.size() == 5);
		VERIFY(s2[0] == Helper::abcde()[0]);
		VERIFY(s2[1] == Helper::abcde()[1]);
		VERIFY(s2[2] == Helper::abcde()[2]);
		VERIFY(s2[3] == Helper::abcde()[3]);
		VERIFY(s2[4] == Helper::abcde()[4]);
	}
	{
		Allocator const alloc{};
		string_view const s1{Helper::abcde()};
		string const s2{s1, alloc};
		VERIFY(s2.size() == 5);
		VERIFY(s2[0] == Helper::abcde()[0]);
		VERIFY(s2[1] == Helper::abcde()[1]);
		VERIFY(s2[2] == Helper::abcde()[2]);
		VERIFY(s2[3] == Helper::abcde()[3]);
		VERIFY(s2[4] == Helper::abcde()[4]);
	}
#endif

	// constexpr basic_string(const charT* s, size_type n, const Allocator& a = Allocator());
	static_assert( hamon::is_constructible           <string, const CharT*, SizeType>::value, "is_constructible");
	static_assert(!hamon::is_nothrow_constructible   <string, const CharT*, SizeType>::value, "is_nothrow_constructible");
	static_assert( hamon::is_implicitly_constructible<string, const CharT*, SizeType>::value, "is_implicitly_constructible");
	static_assert(!hamon::is_trivially_constructible <string, const CharT*, SizeType>::value, "is_trivially_constructible");
	static_assert( hamon::is_constructible           <string, const CharT*, SizeType, const Allocator&>::value, "is_constructible");
	static_assert(!hamon::is_nothrow_constructible   <string, const CharT*, SizeType, const Allocator&>::value, "is_nothrow_constructible");
	static_assert( hamon::is_implicitly_constructible<string, const CharT*, SizeType, const Allocator&>::value, "is_implicitly_constructible");
	static_assert(!hamon::is_trivially_constructible <string, const CharT*, SizeType, const Allocator&>::value, "is_trivially_constructible");
	{
		string const s{Helper::abcde(), 5};
		VERIFY(s.size() == 5);
		VERIFY(s[0] == Helper::abcde()[0]);
		VERIFY(s[1] == Helper::abcde()[1]);
		VERIFY(s[2] == Helper::abcde()[2]);
		VERIFY(s[3] == Helper::abcde()[3]);
		VERIFY(s[4] == Helper::abcde()[4]);
	}
	{
		Allocator const alloc{};
		string const s{Helper::abcde(), 4, alloc};
		VERIFY(s.size() == 4);
		VERIFY(s[0] == Helper::abcde()[0]);
		VERIFY(s[1] == Helper::abcde()[1]);
		VERIFY(s[2] == Helper::abcde()[2]);
		VERIFY(s[3] == Helper::abcde()[3]);
	}

	// constexpr basic_string(const charT* s, const Allocator& a = Allocator());
	static_assert( hamon::is_constructible           <string, const CharT*>::value, "is_constructible");
	static_assert(!hamon::is_nothrow_constructible   <string, const CharT*>::value, "is_nothrow_constructible");
	static_assert( hamon::is_implicitly_constructible<string, const CharT*>::value, "is_implicitly_constructible");
	static_assert(!hamon::is_trivially_constructible <string, const CharT*>::value, "is_trivially_constructible");
	static_assert( hamon::is_constructible           <string, const CharT*, const Allocator&>::value, "is_constructible");
	static_assert(!hamon::is_nothrow_constructible   <string, const CharT*, const Allocator&>::value, "is_nothrow_constructible");
	static_assert( hamon::is_implicitly_constructible<string, const CharT*, const Allocator&>::value, "is_implicitly_constructible");
	static_assert(!hamon::is_trivially_constructible <string, const CharT*, const Allocator&>::value, "is_trivially_constructible");
	{
		string const s{Helper::abcde()};
		VERIFY(s.size() == 5);
		VERIFY(s[0] == Helper::abcde()[0]);
		VERIFY(s[1] == Helper::abcde()[1]);
		VERIFY(s[2] == Helper::abcde()[2]);
		VERIFY(s[3] == Helper::abcde()[3]);
		VERIFY(s[4] == Helper::abcde()[4]);
	}
	{
		Allocator const alloc{};
		string const s{Helper::bcde(), alloc};
		VERIFY(s.size() == 4);
		VERIFY(s[0] == Helper::bcde()[0]);
		VERIFY(s[1] == Helper::bcde()[1]);
		VERIFY(s[2] == Helper::bcde()[2]);
		VERIFY(s[3] == Helper::bcde()[3]);
	}

	// basic_string(nullptr_t) = delete;
	// TODO C++23
//	static_assert(!hamon::is_constructible<string, std::nullptr_t>::value, "");

	// constexpr basic_string(size_type n, charT c, const Allocator& a = Allocator());
	static_assert( hamon::is_constructible           <string, SizeType, CharT>::value, "is_constructible");
	static_assert(!hamon::is_nothrow_constructible   <string, SizeType, CharT>::value, "is_nothrow_constructible");
//	static_assert( hamon::is_implicitly_constructible<string, SizeType, CharT>::value, "is_implicitly_constructible");
	static_assert(!hamon::is_trivially_constructible <string, SizeType, CharT>::value, "is_trivially_constructible");
	static_assert( hamon::is_constructible           <string, SizeType, CharT, const Allocator&>::value, "is_constructible");
	static_assert(!hamon::is_nothrow_constructible   <string, SizeType, CharT, const Allocator&>::value, "is_nothrow_constructible");
	static_assert( hamon::is_implicitly_constructible<string, SizeType, CharT, const Allocator&>::value, "is_implicitly_constructible");
	static_assert(!hamon::is_trivially_constructible <string, SizeType, CharT, const Allocator&>::value, "is_trivially_constructible");
	{
		// string{size_type, charT} だとinitializer_listのほうにマッチしてしまうので、
		// string(size_type, charT) にしなければいけない
		string const s(4, Helper::abcde()[1]);
		VERIFY(s.size() == 4);
		VERIFY(s[0] == Helper::abcde()[1]);
		VERIFY(s[1] == Helper::abcde()[1]);
		VERIFY(s[2] == Helper::abcde()[1]);
		VERIFY(s[3] == Helper::abcde()[1]);
	}
	{
		Allocator const alloc{};
		string const s{3, Helper::abcde()[2], alloc};
		VERIFY(s.size() == 3);
		VERIFY(s[0] == Helper::abcde()[2]);
		VERIFY(s[1] == Helper::abcde()[2]);
		VERIFY(s[2] == Helper::abcde()[2]);
	}

	// template<class InputIterator>
	// constexpr basic_string(InputIterator begin, InputIterator end, const Allocator& a = Allocator());
	static_assert( hamon::is_constructible           <string, const CharT*, const CharT*>::value, "is_constructible");
	static_assert(!hamon::is_nothrow_constructible   <string, const CharT*, const CharT*>::value, "is_nothrow_constructible");
	static_assert( hamon::is_implicitly_constructible<string, const CharT*, const CharT*>::value, "is_implicitly_constructible");
	static_assert(!hamon::is_trivially_constructible <string, const CharT*, const CharT*>::value, "is_trivially_constructible");
	static_assert( hamon::is_constructible           <string, const CharT*, const CharT*, const Allocator&>::value, "is_constructible");
	static_assert(!hamon::is_nothrow_constructible   <string, const CharT*, const CharT*, const Allocator&>::value, "is_nothrow_constructible");
	static_assert( hamon::is_implicitly_constructible<string, const CharT*, const CharT*, const Allocator&>::value, "is_implicitly_constructible");
	static_assert(!hamon::is_trivially_constructible <string, const CharT*, const CharT*, const Allocator&>::value, "is_trivially_constructible");
	{
		string const s(Helper::abcde(), Helper::abcde() + 5);
		VERIFY(s.size() == 5);
		VERIFY(s[0] == Helper::abcde()[0]);
		VERIFY(s[1] == Helper::abcde()[1]);
		VERIFY(s[2] == Helper::abcde()[2]);
		VERIFY(s[3] == Helper::abcde()[3]);
		VERIFY(s[4] == Helper::abcde()[4]);
	}
	{
		Allocator const alloc{};
		string const s(Helper::abcde() + 1, Helper::abcde() + 4, alloc);
		VERIFY(s.size() == 3);
		VERIFY(s[0] == Helper::abcde()[1]);
		VERIFY(s[1] == Helper::abcde()[2]);
		VERIFY(s[2] == Helper::abcde()[3]);
	}

	// template<container-compatible-range<charT> R>
	// constexpr basic_string(from_range_t, R&& rg, const Allocator& a = Allocator());
	{
		// TODO
	}

	// constexpr basic_string(initializer_list<charT>, const Allocator& = Allocator());
	static_assert( hamon::is_constructible           <string, std::initializer_list<CharT>>::value, "is_constructible");
	static_assert(!hamon::is_nothrow_constructible   <string, std::initializer_list<CharT>>::value, "is_nothrow_constructible");
	static_assert( hamon::is_implicitly_constructible<string, std::initializer_list<CharT>>::value, "is_implicitly_constructible");
	static_assert(!hamon::is_trivially_constructible <string, std::initializer_list<CharT>>::value, "is_trivially_constructible");
	static_assert( hamon::is_constructible           <string, std::initializer_list<CharT>, const Allocator&>::value, "is_constructible");
	static_assert(!hamon::is_nothrow_constructible   <string, std::initializer_list<CharT>, const Allocator&>::value, "is_nothrow_constructible");
	static_assert( hamon::is_implicitly_constructible<string, std::initializer_list<CharT>, const Allocator&>::value, "is_implicitly_constructible");
	static_assert(!hamon::is_trivially_constructible <string, std::initializer_list<CharT>, const Allocator&>::value, "is_trivially_constructible");
	{
		string const s =
		{
			Helper::abcde()[3],
			Helper::abcde()[0],
			Helper::abcde()[2],
			Helper::abcde()[1],
		};
		VERIFY(s.size() == 4);
		VERIFY(s[0] == Helper::abcde()[3]);
		VERIFY(s[1] == Helper::abcde()[0]);
		VERIFY(s[2] == Helper::abcde()[2]);
		VERIFY(s[3] == Helper::abcde()[1]);
	}
	{
		Allocator const alloc{};
		string const s (
			{
				Helper::abcde()[3],
				Helper::abcde()[4],
				Helper::abcde()[0],
			},
			alloc);
		VERIFY(s.size() == 3);
		VERIFY(s[0] == Helper::abcde()[3]);
		VERIFY(s[1] == Helper::abcde()[4]);
		VERIFY(s[2] == Helper::abcde()[0]);
	}

	// constexpr basic_string(const basic_string&, const Allocator&);
	static_assert( hamon::is_constructible           <string, const string&, const Allocator&>::value, "is_constructible");
	static_assert(!hamon::is_nothrow_constructible   <string, const string&, const Allocator&>::value, "is_nothrow_constructible");
	static_assert( hamon::is_implicitly_constructible<string, const string&, const Allocator&>::value, "is_implicitly_constructible");
	static_assert(!hamon::is_trivially_constructible <string, const string&, const Allocator&>::value, "is_trivially_constructible");
	{
		Allocator const alloc{};
		string const s1;
		string const s2{s1, alloc};
		VERIFY(s2.size() == 0);
	}
	{
		Allocator const alloc{};
		string const s1{Helper::abcde()};
		string const s2{s1, alloc};
		VERIFY(s2.size() == 5);
		VERIFY(s2[0] == Helper::abcde()[0]);
		VERIFY(s2[1] == Helper::abcde()[1]);
		VERIFY(s2[2] == Helper::abcde()[2]);
		VERIFY(s2[3] == Helper::abcde()[3]);
		VERIFY(s2[4] == Helper::abcde()[4]);
	}

	// constexpr basic_string(basic_string&&, const Allocator&);
	static_assert( hamon::is_constructible           <string, string&&, const Allocator&>::value, "is_constructible");
//	static_assert(!hamon::is_nothrow_constructible   <string, string&&, const Allocator&>::value, "is_nothrow_constructible");
	static_assert( hamon::is_implicitly_constructible<string, string&&, const Allocator&>::value, "is_implicitly_constructible");
	static_assert(!hamon::is_trivially_constructible <string, string&&, const Allocator&>::value, "is_trivially_constructible");
	{
		Allocator const alloc{};
		string s1;
		string s2{hamon::move(s1), alloc};
		VERIFY(s2.size() == 0);
	}
	{
		Allocator const alloc{};
		string s1{Helper::abcde()};
		string s2{hamon::move(s1), alloc};
		VERIFY(s2.size() == 5);
		VERIFY(s2[0] == Helper::abcde()[0]);
		VERIFY(s2[1] == Helper::abcde()[1]);
		VERIFY(s2[2] == Helper::abcde()[2]);
		VERIFY(s2[3] == Helper::abcde()[3]);
		VERIFY(s2[4] == Helper::abcde()[4]);
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, ConsTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(ConsTest<TypeParam>());
}

}	// namespace cons_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
