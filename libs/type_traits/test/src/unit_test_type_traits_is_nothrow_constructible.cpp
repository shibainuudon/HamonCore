/**
 *	@file	unit_test_type_traits_is_nothrow_constructible.cpp
 *
 *	@brief	is_nothrow_constructible のテスト
 */

#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <string>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(b, ...)	\
	static_assert(hamon::is_nothrow_constructible_v<__VA_ARGS__>      == b, "");	\
	static_assert(hamon::is_nothrow_constructible<__VA_ARGS__>::value == b, "");	\
	static_assert(hamon::is_nothrow_constructible<__VA_ARGS__>{}()    == b, "");	\
	static_assert(hamon::is_nothrow_constructible<__VA_ARGS__>{}      == b, "")

#else

#define HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(b, ...)	\
	static_assert(hamon::is_nothrow_constructible<__VA_ARGS__>::value == b, "");	\
	static_assert(hamon::is_nothrow_constructible<__VA_ARGS__>{}()    == b, "");	\
	static_assert(hamon::is_nothrow_constructible<__VA_ARGS__>{}      == b, "")

#endif


namespace hamon_type_traits_test
{

namespace is_nothrow_constructible_test
{

struct S1
{
	S1() HAMON_NOEXCEPT_OR_NOTHROW;
	S1(const S1&);
	S1(S1&&) HAMON_NOEXCEPT_OR_NOTHROW;
	S1(int) HAMON_NOEXCEPT_OR_NOTHROW;
	S1(int, float) HAMON_NOEXCEPT_OR_NOTHROW;
	S1(int, UDT, std::string);
	S1(int, int, int) HAMON_NOEXCEPT_OR_NOTHROW;
};

struct S2
{
	S2(const S2&) HAMON_NOEXCEPT_OR_NOTHROW;
	S2(S2&&);
	~S2() HAMON_NOEXCEPT_OR_NOTHROW;
	S2(UDT);
};

HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int, int);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int, int, int);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int, std::string);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&, int);

HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, trivial_except_construct);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  trivial_except_destroy);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, trivial_except_copy_ctor);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  trivial_except_copy_assign);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, trivial_except_move_ctor);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  trivial_except_move_assign);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  trivial_except_construct,		trivial_except_construct);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  trivial_except_destroy,		trivial_except_destroy);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, trivial_except_copy_ctor,		trivial_except_copy_ctor);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  trivial_except_copy_assign,	trivial_except_copy_assign);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, trivial_except_move_ctor,		trivial_except_move_ctor);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, trivial_except_move_assign,	trivial_except_move_assign);

HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	S1);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	const S1);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	volatile S1);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	const volatile S1);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	S1*);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	S1&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	S1&&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	S1[2]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	S1[]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	S1(&)[2]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	S1(&)[]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	S1(&&)[2]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	S1(&&)[]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	S2);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	S2*);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	S2[2]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	int);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	int*);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	int&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	int&&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	int[2]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	int[]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	int(&)[2]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	int(&)[]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	int(&&)[2]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	int(&&)[]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	POD_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	union_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	POD_union_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	enum_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	enum_class_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	foo0_t);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	foo1_t);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	foo2_t);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	foo3_t);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	foo4_t);

HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  S1, S1);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, const S1);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, volatile S1);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, const volatile S1);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, S1*);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, S1&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  S1, S1&&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, const S1&&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, volatile S1&&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, const volatile S1&&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, S1[2]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  S1, int);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, int*);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  S1, int&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  S1, int&&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, std::string);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  S1, int, float);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, int, UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, UDT, int);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, int, UDT, std::string);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, int, int, std::string);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, UDT, int, std::string);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, int, UDT, std::string, int);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  S1, int, int, int);
	
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S2, S2);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S2, S2*);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  S2, S2&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  S2, const S2&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S2, volatile S2&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S2, const volatile S2&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S2, S2&&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  S2, const S2&&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S2, volatile S2&&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S2, const volatile S2&&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S2, S2[2]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S2, UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S2, int);

HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int,        int);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int,        int*);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int,        int&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int,        int&&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int,        int[2]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int,        int[]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int,        int(&)[2]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int,        int(&)[]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int,        int(&&)[2]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int,        int(&&)[]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int*,       int);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,                 int*,                int*);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const          int*,                int*);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,        volatile int*,                int*);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const volatile int*,                int*);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,                int*, const          int*);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const          int*, const          int*);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,       volatile int*, const          int*);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const volatile int*, const          int*);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,                int*,       volatile int*);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const          int*,       volatile int*);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,        volatile int*,       volatile int*);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const volatile int*,       volatile int*);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,                int*, const volatile int*);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const          int*, const volatile int*);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,       volatile int*, const volatile int*);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const volatile int*, const volatile int*);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int*,       int&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int*,       int&&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int*,       int[2]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int*,       int[]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int*,       int(&)[2]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int*,       int(&)[]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int*,       int(&&)[2]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int*,       int(&&)[]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,                int&,                int);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const          int&,                int);	// const参照だけ特別
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,       volatile int&,                int);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const volatile int&,                int);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,                int&, const          int);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const          int&, const          int);	// const参照だけ特別
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,       volatile int&, const          int);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const volatile int&, const          int);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,                int&,       volatile int);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const          int&,       volatile int);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,       volatile int&,       volatile int);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const volatile int&,       volatile int);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,                int&, const volatile int);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const          int&, const volatile int);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,       volatile int&, const volatile int);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const volatile int&, const volatile int);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&,       int*);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,                 int&,                int&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const          int&,                int&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,        volatile int&,                int&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const volatile int&,                int&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,                int&, const          int&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const          int&, const          int&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,       volatile int&, const          int&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const volatile int&, const          int&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,                int&,       volatile int&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const          int&,       volatile int&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,        volatile int&,       volatile int&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const volatile int&,       volatile int&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,                int&, const volatile int&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const          int&, const volatile int&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,       volatile int&, const volatile int&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const volatile int&, const volatile int&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&,       int&&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&,       int[2]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&,       int[]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&,       int(&)[2]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&,       int(&)[]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&,       int(&&)[2]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&,       int(&&)[]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int&&,      int);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&&,      int*);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&&,      int&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int&&,      int&&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&&,      int[2]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&&,      int[]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&&,      int(&)[2]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&&,      int(&)[]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&&,      int(&&)[2]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&&,      int(&&)[]);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int,        UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int, int, int);

HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,                void);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const          void);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,       volatile void);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const volatile void);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,                void,                void);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const          void, const          void);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,       volatile void,       volatile void);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const volatile void, const volatile void);

HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	UDT,			UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	POD_UDT,		               POD_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	POD_UDT,		const          POD_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	POD_UDT,		      volatile POD_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	POD_UDT,		const volatile POD_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	union_UDT,		union_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	union_UDT,		volatile union_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	POD_union_UDT,	POD_union_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	POD_union_UDT,	const volatile POD_union_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	enum_UDT,		enum_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	enum_UDT,		volatile enum_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	enum_class_UDT,	enum_class_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	enum_class_UDT,	const volatile enum_class_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	enum_UDT,		int);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	enum_class_UDT,	int);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	foo0_t,	foo0_t);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	foo1_t,	foo1_t);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	foo2_t,	foo2_t);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	foo3_t,	foo3_t);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	foo4_t,	foo4_t);

HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	nothrow_default_ctor_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_dtor_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_copy_ctor_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_copy_assign_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_move_ctor_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_move_assign_UDT);

HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_default_ctor_UDT,	nothrow_default_ctor_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_dtor_UDT,			nothrow_dtor_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_copy_ctor_UDT,		nothrow_copy_ctor_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_copy_assign_UDT,	nothrow_copy_assign_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	nothrow_move_ctor_UDT,		nothrow_move_ctor_UDT);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_move_assign_UDT,	nothrow_move_assign_UDT);

HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_default_ctor_UDT,	nothrow_default_ctor_UDT&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_dtor_UDT,			nothrow_dtor_UDT&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	nothrow_copy_ctor_UDT,		nothrow_copy_ctor_UDT&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_copy_assign_UDT,	nothrow_copy_assign_UDT&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_move_ctor_UDT,		nothrow_move_ctor_UDT&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_move_assign_UDT,	nothrow_move_assign_UDT&);

HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_default_ctor_UDT,	nothrow_default_ctor_UDT&&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_dtor_UDT,			nothrow_dtor_UDT&&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_copy_ctor_UDT,		nothrow_copy_ctor_UDT&&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_copy_assign_UDT,	nothrow_copy_assign_UDT&&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	nothrow_move_ctor_UDT,		nothrow_move_ctor_UDT&&);
HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_move_assign_UDT,	nothrow_move_assign_UDT&&);

}	// namespace is_nothrow_constructible_test

}	// namespace hamon_type_traits_test

#undef HAMON_IS_NOTHROW_CONSTRUCTIBLE_TEST
