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
#include <hamon/ranges/from_range_t.hpp>
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
inline HAMON_CXX20_CONSTEXPR bool
ConsTest()
{
	using string = hamon::basic_string<CharT>;
	using Allocator = typename string::allocator_type;
	using SizeType = typename string::size_type;
	using Traits = typename string::traits_type;
	using string_view = hamon::basic_string_view<CharT, Traits>;
	using Helper = StringTestHelper<CharT>;
	
	// constexpr basic_string() noexcept(noexcept(Allocator()))
	static_assert( hamon::is_default_constructible           <string>::value, "is_default_constructible");
	static_assert( hamon::is_nothrow_default_constructible   <string>::value, "is_nothrow_default_constructible");
	static_assert( hamon::is_implicitly_default_constructible<string>::value, "is_implicitly_default_constructible");
	static_assert(!hamon::is_trivially_default_constructible <string>::value, "is_trivially_default_constructible");
	{
		string const s;
		VERIFY(GeneralCheck(s));
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
		VERIFY(GeneralCheck(s));
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
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 0);
	}
	{
		auto const p = Helper::abcde();
		string const s1{p};
		string const s2{s1};
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 5);
		VERIFY(s2[0] == p[0]);
		VERIFY(s2[1] == p[1]);
		VERIFY(s2[2] == p[2]);
		VERIFY(s2[3] == p[3]);
		VERIFY(s2[4] == p[4]);
	}
	{
		auto const p = Helper::long_str();
		string const s1{p};
		string const s2{s1};
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 43);
		VERIFY(s2[0] == p[0]);
		VERIFY(s2[1] == p[1]);
		VERIFY(s2[2] == p[2]);
		VERIFY(s2[3] == p[3]);
		VERIFY(s2[41] == p[41]);
		VERIFY(s2[42] == p[42]);
	}

	// constexpr basic_string(basic_string&& str) noexcept;
	static_assert( hamon::is_move_constructible           <string>::value, "is_move_constructible");
	static_assert( hamon::is_nothrow_move_constructible   <string>::value, "is_nothrow_move_constructible");
	static_assert( hamon::is_implicitly_move_constructible<string>::value, "is_implicitly_move_constructible");
	static_assert(!hamon::is_trivially_move_constructible <string>::value, "is_trivially_move_constructible");
	{
		string s1;
		string s2{hamon::move(s1)};
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 0);
	}
	{
		auto const p = Helper::abcde();
		string s1{p};
		string s2{hamon::move(s1)};
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 5);
		VERIFY(s2[0] == p[0]);
		VERIFY(s2[1] == p[1]);
		VERIFY(s2[2] == p[2]);
		VERIFY(s2[3] == p[3]);
		VERIFY(s2[4] == p[4]);
	}
	{
		auto const p = Helper::long_str();
		string s1{p};
		string s2{hamon::move(s1)};
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 43);
		VERIFY(s2[0] == p[0]);
		VERIFY(s2[1] == p[1]);
		VERIFY(s2[2] == p[2]);
		VERIFY(s2[3] == p[3]);
		VERIFY(s2[41] == p[41]);
		VERIFY(s2[42] == p[42]);
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
		auto const p = Helper::abcde();
		string const s1{p};
		string const s2{s1, 1};
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 4);
		VERIFY(s2[0] == p[1]);
		VERIFY(s2[1] == p[2]);
		VERIFY(s2[2] == p[3]);
		VERIFY(s2[3] == p[4]);
	}
	{
		auto const p = Helper::abcde();
		Allocator const alloc{};
		string const s1{p};
		string const s2{s1, 2, alloc};
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 3);
		VERIFY(s2[0] == p[2]);
		VERIFY(s2[1] == p[3]);
		VERIFY(s2[2] == p[4]);
	}
	{
		auto const p = Helper::long_str();
		Allocator const alloc{};
		string const s1{p};
		string const s2{s1, 2, alloc};
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 41);
		VERIFY(s2[0] == p[2]);
		VERIFY(s2[1] == p[3]);
		VERIFY(s2[2] == p[4]);
		VERIFY(s2[39] == p[41]);
		VERIFY(s2[40] == p[42]);
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
		auto const p = Helper::abcde();
		string const s1{p};
		string const s2{s1, 1, 3};
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 3);
		VERIFY(s2[0] == p[1]);
		VERIFY(s2[1] == p[2]);
		VERIFY(s2[2] == p[3]);
	}
	{
		auto const p = Helper::abcde();
		Allocator const alloc{};
		string const s1{p};
		string const s2{s1, 2, 2, alloc};
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 2);
		VERIFY(s2[0] == p[2]);
		VERIFY(s2[1] == p[3]);
	}
	{
		auto const p = Helper::long_str();
		string const s1{p};
		string const s2{s1, 1, 40};
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 40);
		VERIFY(s2[0] == p[1]);
		VERIFY(s2[1] == p[2]);
		VERIFY(s2[2] == p[3]);
		VERIFY(s2[38] == p[39]);
		VERIFY(s2[39] == p[40]);
	}
	{
		auto const p = Helper::long_str();
		Allocator const alloc{};
		string const s1{p};
		string const s2{s1, 1, 40, alloc};
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 40);
		VERIFY(s2[0] == p[1]);
		VERIFY(s2[1] == p[2]);
		VERIFY(s2[2] == p[3]);
		VERIFY(s2[38] == p[39]);
		VERIFY(s2[39] == p[40]);
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
		auto const p = Helper::abcde();
		string s1{p};
		string const s2{hamon::move(s1), 1};
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 4);
		VERIFY(s2[0] == p[1]);
		VERIFY(s2[1] == p[2]);
		VERIFY(s2[2] == p[3]);
		VERIFY(s2[3] == p[4]);
	}
	{
		auto const p = Helper::abcde();
		Allocator const alloc{};
		string s1{p};
		string const s2{hamon::move(s1), 2, alloc};
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 3);
		VERIFY(s2[0] == p[2]);
		VERIFY(s2[1] == p[3]);
		VERIFY(s2[2] == p[4]);
	}
	{
		auto const p = Helper::long_str();
		string s1{p};
		string const s2{hamon::move(s1), 2};
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 41);
		VERIFY(s2[0] == p[2]);
		VERIFY(s2[1] == p[3]);
		VERIFY(s2[2] == p[4]);
		VERIFY(s2[39] == p[41]);
		VERIFY(s2[40] == p[42]);
	}
	{
		auto const p = Helper::long_str();
		Allocator const alloc{};
		string s1{p};
		string const s2{hamon::move(s1), 3, alloc};
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 40);
		VERIFY(s2[0] == p[3]);
		VERIFY(s2[1] == p[4]);
		VERIFY(s2[2] == p[5]);
		VERIFY(s2[38] == p[41]);
		VERIFY(s2[39] == p[42]);
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
		auto const p = Helper::abcde();
		string s1{p};
		string const s2{hamon::move(s1), 1, 3};
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 3);
		VERIFY(s2[0] == p[1]);
		VERIFY(s2[1] == p[2]);
		VERIFY(s2[2] == p[3]);
	}
	{
		auto const p = Helper::abcde();
		Allocator const alloc{};
		string s1{p};
		string const s2{hamon::move(s1), 2, 2, alloc};
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 2);
		VERIFY(s2[0] == p[2]);
		VERIFY(s2[1] == p[3]);
	}

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
		auto const p = Helper::abcde();
		string_view const s1{p};
		string const s2{s1, 1, 3};
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 3);
		VERIFY(s2[0] == p[1]);
		VERIFY(s2[1] == p[2]);
		VERIFY(s2[2] == p[3]);
	}
	{
		auto const p = Helper::abcde();
		Allocator const alloc{};
		string_view const s1{p};
		string const s2{s1, 2, 2, alloc};
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 2);
		VERIFY(s2[0] == p[2]);
		VERIFY(s2[1] == p[3]);
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
		auto const p = Helper::abcde();
		string_view const s1{p};
		string const s2{s1};
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 5);
		VERIFY(s2[0] == p[0]);
		VERIFY(s2[1] == p[1]);
		VERIFY(s2[2] == p[2]);
		VERIFY(s2[3] == p[3]);
		VERIFY(s2[4] == p[4]);
	}
	{
		auto const p = Helper::abcde();
		Allocator const alloc{};
		string_view const s1{p};
		string const s2{s1, alloc};
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 5);
		VERIFY(s2[0] == p[0]);
		VERIFY(s2[1] == p[1]);
		VERIFY(s2[2] == p[2]);
		VERIFY(s2[3] == p[3]);
		VERIFY(s2[4] == p[4]);
	}

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
		auto const p = Helper::abcde();
		string const s{p, 5};
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 5);
		VERIFY(s[0] == p[0]);
		VERIFY(s[1] == p[1]);
		VERIFY(s[2] == p[2]);
		VERIFY(s[3] == p[3]);
		VERIFY(s[4] == p[4]);
	}
	{
		auto const p = Helper::abcde();
		Allocator const alloc{};
		string const s{p, 4, alloc};
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 4);
		VERIFY(s[0] == p[0]);
		VERIFY(s[1] == p[1]);
		VERIFY(s[2] == p[2]);
		VERIFY(s[3] == p[3]);
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
		auto const p = Helper::abcde();
		string const s{p};
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 5);
		VERIFY(s[0] == p[0]);
		VERIFY(s[1] == p[1]);
		VERIFY(s[2] == p[2]);
		VERIFY(s[3] == p[3]);
		VERIFY(s[4] == p[4]);
	}
	{
		auto const p = Helper::bcde();
		Allocator const alloc{};
		string const s{p, alloc};
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 4);
		VERIFY(s[0] == p[0]);
		VERIFY(s[1] == p[1]);
		VERIFY(s[2] == p[2]);
		VERIFY(s[3] == p[3]);
	}

	// basic_string(nullptr_t) = delete;
	static_assert(!hamon::is_constructible<string, std::nullptr_t>::value, "");

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
		auto const c = Helper::abcde()[1];
		string const s(4, c);
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 4);
		VERIFY(s[0] == c);
		VERIFY(s[1] == c);
		VERIFY(s[2] == c);
		VERIFY(s[3] == c);
	}
	{
		auto const c = Helper::abcde()[2];
		Allocator const alloc{};
		string const s{3, c, alloc};
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 3);
		VERIFY(s[0] == c);
		VERIFY(s[1] == c);
		VERIFY(s[2] == c);
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
		auto const p = Helper::abcde();
		string const s(p, p + 5);
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 5);
		VERIFY(s[0] == p[0]);
		VERIFY(s[1] == p[1]);
		VERIFY(s[2] == p[2]);
		VERIFY(s[3] == p[3]);
		VERIFY(s[4] == p[4]);
	}
	{
		auto const p = Helper::abcde();
		Allocator const alloc{};
		string const s(p + 1, p + 4, alloc);
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 3);
		VERIFY(s[0] == p[1]);
		VERIFY(s[1] == p[2]);
		VERIFY(s[2] == p[3]);
	}

	// template<container-compatible-range<charT> R>
	// constexpr basic_string(from_range_t, R&& rg, const Allocator& a = Allocator());
	{
		auto const rng = {0x41, 0x42, 0x43};
		string s(hamon::from_range, rng);
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 3);
		VERIFY(s[0] == 0x41);
		VERIFY(s[1] == 0x42);
		VERIFY(s[2] == 0x43);
	}
	{
		CharT const arr[] = {3, 1, 4, 2};
		Allocator const alloc{};
		string s(hamon::from_range, arr, alloc);
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 4);
		VERIFY(s[0] == 3);
		VERIFY(s[1] == 1);
		VERIFY(s[2] == 4);
		VERIFY(s[3] == 2);
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
		auto const p = Helper::abcde();
		string const s =
		{
			p[3],
			p[0],
			p[2],
			p[1],
		};
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 4);
		VERIFY(s[0] == p[3]);
		VERIFY(s[1] == p[0]);
		VERIFY(s[2] == p[2]);
		VERIFY(s[3] == p[1]);
	}
	{
		auto const p = Helper::abcde();
		Allocator const alloc{};
		string const s (
			{
				p[3],
				p[4],
				p[0],
			},
			alloc);
		VERIFY(GeneralCheck(s));
		VERIFY(s.size() == 3);
		VERIFY(s[0] == p[3]);
		VERIFY(s[1] == p[4]);
		VERIFY(s[2] == p[0]);
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
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 0);
	}
	{
		auto const p = Helper::abcde();
		Allocator const alloc{};
		string const s1{p};
		string const s2{s1, alloc};
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 5);
		VERIFY(s2[0] == p[0]);
		VERIFY(s2[1] == p[1]);
		VERIFY(s2[2] == p[2]);
		VERIFY(s2[3] == p[3]);
		VERIFY(s2[4] == p[4]);
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
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 0);
	}
	{
		auto const p = Helper::abcde();
		Allocator const alloc{};
		string s1{p};
		string s2{hamon::move(s1), alloc};
		VERIFY(GeneralCheck(s2));
		VERIFY(s2.size() == 5);
		VERIFY(s2[0] == p[0]);
		VERIFY(s2[1] == p[1]);
		VERIFY(s2[2] == p[2]);
		VERIFY(s2[3] == p[3]);
		VERIFY(s2[4] == p[4]);
	}

	return true;
}

#undef VERIFY

TYPED_TEST(StringTest, ConsTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(ConsTest<TypeParam>());
	
#if !defined(HAMON_NO_EXCEPTIONS)
	using CharT = TypeParam;
	using string = hamon::basic_string<CharT>;
	using Allocator = typename string::allocator_type;
	using Helper = StringTestHelper<CharT>;

	// [string.cons]/6	Throws: out_of_range if pos > s.size().

	// constexpr basic_string(const basic_string& str, size_type pos, const Allocator& a = Allocator());
	{
		string const s1{Helper::abcde()};
		EXPECT_NO_THROW(string s2(s1, 5); (void)s2;);
		EXPECT_THROW(string s2(s1, 6); (void)s2;, std::out_of_range);
	}
	{
		Allocator const alloc{};
		string const s1{Helper::abcde()};
		EXPECT_NO_THROW(string s2(s1, 5, alloc); (void)s2;);
		EXPECT_THROW(string s2(s1, 6, alloc); (void)s2;, std::out_of_range);
	}
	// constexpr basic_string(const basic_string& str, size_type pos, size_type n, const Allocator& a = Allocator());
	{
		string const s1{Helper::abcde()};
		EXPECT_NO_THROW(string s2(s1, 5, 1); (void)s2;);
		EXPECT_THROW(string s2(s1, 6, 1); (void)s2;, std::out_of_range);
	}
	{
		Allocator const alloc{};
		string const s1{Helper::abcde()};
		EXPECT_NO_THROW(string s2(s1, 5, 1, alloc); (void)s2;);
		EXPECT_THROW(string s2(s1, 6, 1, alloc); (void)s2;, std::out_of_range);
	}
	// constexpr basic_string(basic_string&& str, size_type pos, const Allocator& a = Allocator());
	{
		string s1{Helper::abcde()};
		EXPECT_THROW(string s2(hamon::move(s1), 6); (void)s2;, std::out_of_range);
	}
	{
		Allocator const alloc{};
		string s1{Helper::abcde()};
		EXPECT_THROW(string s2(hamon::move(s1), 6, alloc); (void)s2;, std::out_of_range);
	}
	// constexpr basic_string(basic_string&& str, size_type pos, size_type n, const Allocator& a = Allocator());
	{
		string s1{Helper::abcde()};
		EXPECT_THROW(string s2(hamon::move(s1), 6, 1); (void)s2;, std::out_of_range);
	}
	{
		Allocator const alloc{};
		string s1{Helper::abcde()};
		EXPECT_THROW(string s2(hamon::move(s1), 6, 1, alloc); (void)s2;, std::out_of_range);
	}

	// [string.require]/1
	// If any operation would cause size() to exceed max_size(), that operation throws an exception object of type length_error.

	{
		string const s1;
		auto const c = Helper::abc()[0];	// 'a'
		EXPECT_THROW(string s2(s1.max_size() + 1, c); (void)s2;, std::length_error);
	}
#endif
}

}	// namespace cons_test
}	// namespace string_test
}	// namespace hamon_test

HAMON_WARNING_POP()
