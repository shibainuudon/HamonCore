/**
 *	@file	unit_test_type_traits_common_reference.cpp
 *
 *	@brief	common_reference のテスト
 */

#include <hamon/type_traits/common_reference.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <type_traits>

namespace hamon_type_traits_test
{

namespace common_reference_test
{

template <typename T, typename = void>
struct has_type : std::false_type { };

template <typename T>
struct has_type<T, hamon::void_t<typename T::type>>: std::true_type { };

template <typename... T>
constexpr bool
has_common_ref()
{
	return has_type<hamon::common_reference<T...>>::value;
}

struct A { };
struct B { };
struct C { };

struct D { };
struct E { };
struct F { };

}	// namespace common_reference_test

}	// namespace hamon_type_traits_test

namespace HAMON_BASIC_COMMON_REFERENCE_NAMESPACE
{

template <template <typename> class AQual, template <typename> class BQual>
struct basic_common_reference<
	hamon_type_traits_test::common_reference_test::A,
	hamon_type_traits_test::common_reference_test::B,
	AQual, BQual>
{
	using type = BQual<AQual<hamon_type_traits_test::common_reference_test::C>>;
};

}	// namespace HAMON_BASIC_COMMON_REFERENCE_NAMESPACE

namespace HAMON_COMMON_TYPE_NAMESPACE
{

template <>
struct common_type<
	hamon_type_traits_test::common_reference_test::D,
	hamon_type_traits_test::common_reference_test::E>
{
	using type = hamon_type_traits_test::common_reference_test::F;
};

}	// namespace hamon

namespace hamon_type_traits_test
{

namespace common_reference_test
{

static_assert(!has_common_ref<>(), "");
static_assert(!has_common_ref<char(*)(), int(*)()>(), "");
static_assert(!has_common_ref<void*, int>(), "");
static_assert( has_common_ref<int, int, int>(), "");
static_assert(!has_common_ref<void*, int, int>(), "");
static_assert(!has_common_ref<int, int, void*>(), "");

#define HAMON_COMMON_REFERENCE_TEST(T, ...)	\
	static_assert(std::is_same<T, hamon::common_reference_t<__VA_ARGS__>>::value, "")

HAMON_COMMON_REFERENCE_TEST(int               , int               );
HAMON_COMMON_REFERENCE_TEST(int const         , int const         );
HAMON_COMMON_REFERENCE_TEST(int       volatile, int       volatile);
HAMON_COMMON_REFERENCE_TEST(int const volatile, int const volatile);
HAMON_COMMON_REFERENCE_TEST(int               *, int               *);
HAMON_COMMON_REFERENCE_TEST(int const         *, int const         *);
HAMON_COMMON_REFERENCE_TEST(int       volatile*, int       volatile*);
HAMON_COMMON_REFERENCE_TEST(int const volatile*, int const volatile*);
HAMON_COMMON_REFERENCE_TEST(int               &, int               &);
HAMON_COMMON_REFERENCE_TEST(int const         &, int const         &);
HAMON_COMMON_REFERENCE_TEST(int       volatile&, int       volatile&);
HAMON_COMMON_REFERENCE_TEST(int const volatile&, int const volatile&);
HAMON_COMMON_REFERENCE_TEST(int               &&, int               &&);
HAMON_COMMON_REFERENCE_TEST(int const         &&, int const         &&);
HAMON_COMMON_REFERENCE_TEST(int       volatile&&, int       volatile&&);
HAMON_COMMON_REFERENCE_TEST(int const volatile&&, int const volatile&&);
HAMON_COMMON_REFERENCE_TEST(int               **, int               **);
HAMON_COMMON_REFERENCE_TEST(int const         **, int const         **);
HAMON_COMMON_REFERENCE_TEST(int       volatile**, int       volatile**);
HAMON_COMMON_REFERENCE_TEST(int const volatile**, int const volatile**);
HAMON_COMMON_REFERENCE_TEST(void               , void               );
HAMON_COMMON_REFERENCE_TEST(void const         , void const         );
HAMON_COMMON_REFERENCE_TEST(void       volatile, void       volatile);
HAMON_COMMON_REFERENCE_TEST(void const volatile, void const volatile);
HAMON_COMMON_REFERENCE_TEST(void               *, void               *);
HAMON_COMMON_REFERENCE_TEST(void const         *, void const         *);
HAMON_COMMON_REFERENCE_TEST(void       volatile*, void       volatile*);
HAMON_COMMON_REFERENCE_TEST(void const volatile*, void const volatile*);

HAMON_COMMON_REFERENCE_TEST(int, int               , int               );
HAMON_COMMON_REFERENCE_TEST(int, int               , int const         );
HAMON_COMMON_REFERENCE_TEST(int, int               , int       volatile);
HAMON_COMMON_REFERENCE_TEST(int, int               , int const volatile);
HAMON_COMMON_REFERENCE_TEST(int, int const         , int               );
HAMON_COMMON_REFERENCE_TEST(int, int const         , int const         );
HAMON_COMMON_REFERENCE_TEST(int, int const         , int       volatile);
HAMON_COMMON_REFERENCE_TEST(int, int const         , int const volatile);
HAMON_COMMON_REFERENCE_TEST(int, int       volatile, int               );
HAMON_COMMON_REFERENCE_TEST(int, int       volatile, int const         );
HAMON_COMMON_REFERENCE_TEST(int, int       volatile, int       volatile);
HAMON_COMMON_REFERENCE_TEST(int, int       volatile, int const volatile);
HAMON_COMMON_REFERENCE_TEST(int, int const volatile, int               );
HAMON_COMMON_REFERENCE_TEST(int, int const volatile, int const         );
HAMON_COMMON_REFERENCE_TEST(int, int const volatile, int       volatile);
HAMON_COMMON_REFERENCE_TEST(int, int const volatile, int const volatile);
HAMON_COMMON_REFERENCE_TEST(int, int               , int               &);
HAMON_COMMON_REFERENCE_TEST(int, int               , int const         &);
HAMON_COMMON_REFERENCE_TEST(int, int               , int       volatile&);
HAMON_COMMON_REFERENCE_TEST(int, int               , int const volatile&);
HAMON_COMMON_REFERENCE_TEST(int, int const         , int               &);
HAMON_COMMON_REFERENCE_TEST(int, int const         , int const         &);
HAMON_COMMON_REFERENCE_TEST(int, int const         , int       volatile&);
HAMON_COMMON_REFERENCE_TEST(int, int const         , int const volatile&);
HAMON_COMMON_REFERENCE_TEST(int, int       volatile, int               &);
HAMON_COMMON_REFERENCE_TEST(int, int       volatile, int const         &);
HAMON_COMMON_REFERENCE_TEST(int, int       volatile, int       volatile&);
HAMON_COMMON_REFERENCE_TEST(int, int       volatile, int const volatile&);
HAMON_COMMON_REFERENCE_TEST(int, int const volatile, int               &);
HAMON_COMMON_REFERENCE_TEST(int, int const volatile, int const         &);
HAMON_COMMON_REFERENCE_TEST(int, int const volatile, int       volatile&);
HAMON_COMMON_REFERENCE_TEST(int, int const volatile, int const volatile&);
HAMON_COMMON_REFERENCE_TEST(int, int               , int               &&);
HAMON_COMMON_REFERENCE_TEST(int, int               , int const         &&);
HAMON_COMMON_REFERENCE_TEST(int, int               , int       volatile&&);
HAMON_COMMON_REFERENCE_TEST(int, int               , int const volatile&&);
HAMON_COMMON_REFERENCE_TEST(int, int const         , int               &&);
HAMON_COMMON_REFERENCE_TEST(int, int const         , int const         &&);
HAMON_COMMON_REFERENCE_TEST(int, int const         , int       volatile&&);
HAMON_COMMON_REFERENCE_TEST(int, int const         , int const volatile&&);
HAMON_COMMON_REFERENCE_TEST(int, int       volatile, int               &&);
HAMON_COMMON_REFERENCE_TEST(int, int       volatile, int const         &&);
HAMON_COMMON_REFERENCE_TEST(int, int       volatile, int       volatile&&);
HAMON_COMMON_REFERENCE_TEST(int, int       volatile, int const volatile&&);
HAMON_COMMON_REFERENCE_TEST(int, int const volatile, int               &&);
HAMON_COMMON_REFERENCE_TEST(int, int const volatile, int const         &&);
HAMON_COMMON_REFERENCE_TEST(int, int const volatile, int       volatile&&);
HAMON_COMMON_REFERENCE_TEST(int, int const volatile, int const volatile&&);

HAMON_COMMON_REFERENCE_TEST(int                , int               &, int               );
HAMON_COMMON_REFERENCE_TEST(int                , int               &, int const         );
HAMON_COMMON_REFERENCE_TEST(int                , int               &, int       volatile);
HAMON_COMMON_REFERENCE_TEST(int                , int               &, int const volatile);
HAMON_COMMON_REFERENCE_TEST(int                , int const         &, int               );
HAMON_COMMON_REFERENCE_TEST(int                , int const         &, int const         );
HAMON_COMMON_REFERENCE_TEST(int                , int const         &, int       volatile);
HAMON_COMMON_REFERENCE_TEST(int                , int const         &, int const volatile);
HAMON_COMMON_REFERENCE_TEST(int                , int       volatile&, int               );
HAMON_COMMON_REFERENCE_TEST(int                , int       volatile&, int const         );
HAMON_COMMON_REFERENCE_TEST(int                , int       volatile&, int       volatile);
HAMON_COMMON_REFERENCE_TEST(int                , int       volatile&, int const volatile);
HAMON_COMMON_REFERENCE_TEST(int                , int const volatile&, int               );
HAMON_COMMON_REFERENCE_TEST(int                , int const volatile&, int const         );
HAMON_COMMON_REFERENCE_TEST(int                , int const volatile&, int       volatile);
HAMON_COMMON_REFERENCE_TEST(int                , int const volatile&, int const volatile);
HAMON_COMMON_REFERENCE_TEST(int               &, int               &, int               &);
HAMON_COMMON_REFERENCE_TEST(int const         &, int               &, int const         &);
HAMON_COMMON_REFERENCE_TEST(int       volatile&, int               &, int       volatile&);
HAMON_COMMON_REFERENCE_TEST(int const volatile&, int               &, int const volatile&);
HAMON_COMMON_REFERENCE_TEST(int const         &, int const         &, int               &);
HAMON_COMMON_REFERENCE_TEST(int const         &, int const         &, int const         &);
HAMON_COMMON_REFERENCE_TEST(int const volatile&, int const         &, int       volatile&);
HAMON_COMMON_REFERENCE_TEST(int const volatile&, int const         &, int const volatile&);
HAMON_COMMON_REFERENCE_TEST(int       volatile&, int       volatile&, int               &);
HAMON_COMMON_REFERENCE_TEST(int const volatile&, int       volatile&, int const         &);
HAMON_COMMON_REFERENCE_TEST(int       volatile&, int       volatile&, int       volatile&);
HAMON_COMMON_REFERENCE_TEST(int const volatile&, int       volatile&, int const volatile&);
HAMON_COMMON_REFERENCE_TEST(int const volatile&, int const volatile&, int               &);
HAMON_COMMON_REFERENCE_TEST(int const volatile&, int const volatile&, int const         &);
HAMON_COMMON_REFERENCE_TEST(int const volatile&, int const volatile&, int       volatile&);
HAMON_COMMON_REFERENCE_TEST(int const volatile&, int const volatile&, int const volatile&);
HAMON_COMMON_REFERENCE_TEST(int const         &, int               &, int               &&);
HAMON_COMMON_REFERENCE_TEST(int const         &, int               &, int const         &&);
HAMON_COMMON_REFERENCE_TEST(int                , int               &, int       volatile&&);
HAMON_COMMON_REFERENCE_TEST(int                , int               &, int const volatile&&);
HAMON_COMMON_REFERENCE_TEST(int const         &, int const         &, int               &&);
HAMON_COMMON_REFERENCE_TEST(int const         &, int const         &, int const         &&);
HAMON_COMMON_REFERENCE_TEST(int                , int const         &, int       volatile&&);
HAMON_COMMON_REFERENCE_TEST(int                , int const         &, int const volatile&&);
HAMON_COMMON_REFERENCE_TEST(int                , int       volatile&, int               &&);
HAMON_COMMON_REFERENCE_TEST(int                , int       volatile&, int const         &&);
HAMON_COMMON_REFERENCE_TEST(int                , int       volatile&, int       volatile&&);
HAMON_COMMON_REFERENCE_TEST(int                , int       volatile&, int const volatile&&);
HAMON_COMMON_REFERENCE_TEST(int                , int const volatile&, int               &&);
HAMON_COMMON_REFERENCE_TEST(int                , int const volatile&, int const         &&);
HAMON_COMMON_REFERENCE_TEST(int                , int const volatile&, int       volatile&&);
HAMON_COMMON_REFERENCE_TEST(int                , int const volatile&, int const volatile&&);

HAMON_COMMON_REFERENCE_TEST(int, int               &&, int               );
HAMON_COMMON_REFERENCE_TEST(int, int               &&, int const         );
HAMON_COMMON_REFERENCE_TEST(int, int               &&, int       volatile);
HAMON_COMMON_REFERENCE_TEST(int, int               &&, int const volatile);
HAMON_COMMON_REFERENCE_TEST(int, int const         &&, int               );
HAMON_COMMON_REFERENCE_TEST(int, int const         &&, int const         );
HAMON_COMMON_REFERENCE_TEST(int, int const         &&, int       volatile);
HAMON_COMMON_REFERENCE_TEST(int, int const         &&, int const volatile);
HAMON_COMMON_REFERENCE_TEST(int, int       volatile&&, int               );
HAMON_COMMON_REFERENCE_TEST(int, int       volatile&&, int const         );
HAMON_COMMON_REFERENCE_TEST(int, int       volatile&&, int       volatile);
HAMON_COMMON_REFERENCE_TEST(int, int       volatile&&, int const volatile);
HAMON_COMMON_REFERENCE_TEST(int, int const volatile&&, int               );
HAMON_COMMON_REFERENCE_TEST(int, int const volatile&&, int const         );
HAMON_COMMON_REFERENCE_TEST(int, int const volatile&&, int       volatile);
HAMON_COMMON_REFERENCE_TEST(int, int const volatile&&, int const volatile);
HAMON_COMMON_REFERENCE_TEST(int const&, int               &&, int               &);
HAMON_COMMON_REFERENCE_TEST(int const&, int               &&, int const         &);
HAMON_COMMON_REFERENCE_TEST(int       , int               &&, int       volatile&);
HAMON_COMMON_REFERENCE_TEST(int       , int               &&, int const volatile&);
HAMON_COMMON_REFERENCE_TEST(int const&, int const         &&, int               &);
HAMON_COMMON_REFERENCE_TEST(int const&, int const         &&, int const         &);
HAMON_COMMON_REFERENCE_TEST(int       , int const         &&, int       volatile&);
HAMON_COMMON_REFERENCE_TEST(int       , int const         &&, int const volatile&);
HAMON_COMMON_REFERENCE_TEST(int       , int       volatile&&, int               &);
HAMON_COMMON_REFERENCE_TEST(int       , int       volatile&&, int const         &);
HAMON_COMMON_REFERENCE_TEST(int       , int       volatile&&, int       volatile&);
HAMON_COMMON_REFERENCE_TEST(int       , int       volatile&&, int const volatile&);
HAMON_COMMON_REFERENCE_TEST(int       , int const volatile&&, int               &);
HAMON_COMMON_REFERENCE_TEST(int       , int const volatile&&, int const         &);
HAMON_COMMON_REFERENCE_TEST(int       , int const volatile&&, int       volatile&);
HAMON_COMMON_REFERENCE_TEST(int       , int const volatile&&, int const volatile&);
HAMON_COMMON_REFERENCE_TEST(int               &&, int               &&, int               &&);
HAMON_COMMON_REFERENCE_TEST(int const         &&, int               &&, int const         &&);
HAMON_COMMON_REFERENCE_TEST(int       volatile&&, int               &&, int       volatile&&);
HAMON_COMMON_REFERENCE_TEST(int const volatile&&, int               &&, int const volatile&&);
HAMON_COMMON_REFERENCE_TEST(int const         &&, int const         &&, int               &&);
HAMON_COMMON_REFERENCE_TEST(int const         &&, int const         &&, int const         &&);
HAMON_COMMON_REFERENCE_TEST(int const volatile&&, int const         &&, int       volatile&&);
HAMON_COMMON_REFERENCE_TEST(int const volatile&&, int const         &&, int const volatile&&);
HAMON_COMMON_REFERENCE_TEST(int       volatile&&, int       volatile&&, int               &&);
HAMON_COMMON_REFERENCE_TEST(int const volatile&&, int       volatile&&, int const         &&);
HAMON_COMMON_REFERENCE_TEST(int       volatile&&, int       volatile&&, int       volatile&&);
HAMON_COMMON_REFERENCE_TEST(int const volatile&&, int       volatile&&, int const volatile&&);
HAMON_COMMON_REFERENCE_TEST(int const volatile&&, int const volatile&&, int               &&);
HAMON_COMMON_REFERENCE_TEST(int const volatile&&, int const volatile&&, int const         &&);
HAMON_COMMON_REFERENCE_TEST(int const volatile&&, int const volatile&&, int       volatile&&);
HAMON_COMMON_REFERENCE_TEST(int const volatile&&, int const volatile&&, int const volatile&&);

HAMON_COMMON_REFERENCE_TEST(void, void, const void);
HAMON_COMMON_REFERENCE_TEST(void(*)(), void(*)(), void(* const)());

HAMON_COMMON_REFERENCE_TEST(int, char&, int&);
HAMON_COMMON_REFERENCE_TEST(long, long&, int&);

HAMON_COMMON_REFERENCE_TEST(int*, int*, int*);
HAMON_COMMON_REFERENCE_TEST(void*,       int      *       , void      *       );
HAMON_COMMON_REFERENCE_TEST(void*,       int      *      &, void      *      &);
HAMON_COMMON_REFERENCE_TEST(void const*, int const*      &, void      *      &);
HAMON_COMMON_REFERENCE_TEST(void const*, int      *      &, void const*      &);
HAMON_COMMON_REFERENCE_TEST(void*,       int      * const&, void      *      &);
HAMON_COMMON_REFERENCE_TEST(void*,       int      *      &, void      * const&);
HAMON_COMMON_REFERENCE_TEST(void const*, int const* const&, void      *      &);

HAMON_COMMON_REFERENCE_TEST(C, A, B);
HAMON_COMMON_REFERENCE_TEST(C&, A&, B);
HAMON_COMMON_REFERENCE_TEST(C&, A&, const B);
HAMON_COMMON_REFERENCE_TEST(const C&, const A, B&);
HAMON_COMMON_REFERENCE_TEST(const C&, const A&, B&&);
HAMON_COMMON_REFERENCE_TEST(const C&&, const A, B&&);

HAMON_COMMON_REFERENCE_TEST(F, D, E);
HAMON_COMMON_REFERENCE_TEST(F, D&, E);
HAMON_COMMON_REFERENCE_TEST(F, D&, E&&);

#undef HAMON_COMMON_REFERENCE_TEST

}	// namespace common_reference_test

}	// namespace hamon_type_traits_test
