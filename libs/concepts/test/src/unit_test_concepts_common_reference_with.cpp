/**
 *	@file	unit_test_concepts_common_reference_with.cpp
 *
 *	@brief	common_reference_with のテスト
 */

#include <hamon/concepts/common_reference_with.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_COMMON_REFERENCE_WITH_TEST(B, T1, T2)	\
	static_assert(B == hamon::common_reference_with<T1, T2>, "");	\
	static_assert(B == hamon::common_reference_with_t<T1, T2>::value, "")
#else
#  define HAMON_COMMON_REFERENCE_WITH_TEST(B, T1, T2)	\
	static_assert(B == hamon::common_reference_with<T1, T2>::value, "");	\
	static_assert(B == hamon::common_reference_with_t<T1, T2>::value, "")
#endif

namespace hamon_concepts_test
{

namespace common_reference_with_test
{

HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               , int               );
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               , int const         );
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               , int       volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               , int const volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         , int               );
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         , int const         );
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         , int       volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         , int const volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile, int               );
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile, int const         );
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile, int       volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile, int const volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile, int               );
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile, int const         );
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile, int       volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile, int const volatile);

HAMON_COMMON_REFERENCE_WITH_TEST(false, int               , int               *);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int               , int const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int               , int       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int               , int const volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const         , int               *);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const         , int const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const         , int       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const         , int const volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int       volatile, int               *);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int       volatile, int const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int       volatile, int       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int       volatile, int const volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const volatile, int               *);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const volatile, int const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const volatile, int       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const volatile, int const volatile*);

HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               , int               &);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               , int const         &);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               , int       volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               , int const volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         , int               &);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         , int const         &);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         , int       volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         , int const volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile, int               &);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile, int const         &);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile, int       volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile, int const volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile, int               &);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile, int const         &);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile, int       volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile, int const volatile&);

HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               , int               &&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               , int const         &&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               , int       volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               , int const volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         , int               &&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         , int const         &&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         , int       volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         , int const volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile, int               &&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile, int const         &&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile, int       volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile, int const volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile, int               &&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile, int const         &&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile, int       volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile, int const volatile&&);

HAMON_COMMON_REFERENCE_WITH_TEST(false, int               *, int               );
HAMON_COMMON_REFERENCE_WITH_TEST(false, int               *, int const         );
HAMON_COMMON_REFERENCE_WITH_TEST(false, int               *, int       volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int               *, int const volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const         *, int               );
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const         *, int const         );
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const         *, int       volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const         *, int const volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int       volatile*, int               );
HAMON_COMMON_REFERENCE_WITH_TEST(false, int       volatile*, int const         );
HAMON_COMMON_REFERENCE_WITH_TEST(false, int       volatile*, int       volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int       volatile*, int const volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const volatile*, int               );
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const volatile*, int const         );
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const volatile*, int       volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const volatile*, int const volatile);

HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               *, int               *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               *, int const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               *, int       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               *, int const volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         *, int               *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         *, int const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         *, int       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         *, int const volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile*, int               *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile*, int const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile*, int       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile*, int const volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile*, int               *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile*, int const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile*, int       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile*, int const volatile*);

HAMON_COMMON_REFERENCE_WITH_TEST(false, int               *, int               &);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int               *, int const         &);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int               *, int       volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int               *, int const volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const         *, int               &);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const         *, int const         &);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const         *, int       volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const         *, int const volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int       volatile*, int               &);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int       volatile*, int const         &);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int       volatile*, int       volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int       volatile*, int const volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const volatile*, int               &);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const volatile*, int const         &);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const volatile*, int       volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const volatile*, int const volatile&);

HAMON_COMMON_REFERENCE_WITH_TEST(false, int               *, int               &&);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int               *, int const         &&);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int               *, int       volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int               *, int const volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const         *, int               &&);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const         *, int const         &&);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const         *, int       volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const         *, int const volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int       volatile*, int               &&);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int       volatile*, int const         &&);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int       volatile*, int       volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int       volatile*, int const volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const volatile*, int               &&);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const volatile*, int const         &&);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const volatile*, int       volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const volatile*, int const volatile&&);

HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               &, int               );
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               &, int const         );
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               &, int       volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               &, int const volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         &, int               );
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         &, int const         );
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         &, int       volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         &, int const volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&, int               );
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&, int const         );
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&, int       volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&, int const volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&, int               );
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&, int const         );
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&, int       volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&, int const volatile);

HAMON_COMMON_REFERENCE_WITH_TEST(false, int               &, int               *);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int               &, int const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int               &, int       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int               &, int const volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const         &, int               *);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const         &, int const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const         &, int       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const         &, int const volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int       volatile&, int               *);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int       volatile&, int const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int       volatile&, int       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int       volatile&, int const volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const volatile&, int               *);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const volatile&, int const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const volatile&, int       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const volatile&, int const volatile*);

HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               &, int               &);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               &, int const         &);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               &, int       volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               &, int const volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         &, int               &);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         &, int const         &);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         &, int       volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         &, int const volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&, int               &);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&, int const         &);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&, int       volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&, int const volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&, int               &);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&, int const         &);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&, int       volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&, int const volatile&);

HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               &, int               &&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               &, int const         &&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               &, int       volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               &, int const volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         &, int               &&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         &, int const         &&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         &, int       volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         &, int const volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&, int               &&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&, int const         &&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&, int       volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&, int const volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&, int               &&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&, int const         &&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&, int       volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&, int const volatile&&);

HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               &&, int               );
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               &&, int const         );
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               &&, int       volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               &&, int const volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         &&, int               );
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         &&, int const         );
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         &&, int       volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         &&, int const volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&&, int               );
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&&, int const         );
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&&, int       volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&&, int const volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&&, int               );
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&&, int const         );
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&&, int       volatile);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&&, int const volatile);

HAMON_COMMON_REFERENCE_WITH_TEST(false, int               &&, int               *);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int               &&, int const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int               &&, int       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int               &&, int const volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const         &&, int               *);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const         &&, int const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const         &&, int       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const         &&, int const volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int       volatile&&, int               *);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int       volatile&&, int const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int       volatile&&, int       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int       volatile&&, int const volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const volatile&&, int               *);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const volatile&&, int const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const volatile&&, int       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int const volatile&&, int const volatile*);

HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               &&, int               &);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               &&, int const         &);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               &&, int       volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               &&, int const volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         &&, int               &);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         &&, int const         &);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         &&, int       volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         &&, int const volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&&, int               &);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&&, int const         &);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&&, int       volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&&, int const volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&&, int               &);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&&, int const         &);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&&, int       volatile&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&&, int const volatile&);

HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               &&, int               &&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               &&, int const         &&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               &&, int       volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               &&, int const volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         &&, int               &&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         &&, int const         &&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         &&, int       volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         &&, int const volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&&, int               &&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&&, int const         &&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&&, int       volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile&&, int const volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&&, int               &&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&&, int const         &&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&&, int       volatile&&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile&&, int const volatile&&);

HAMON_COMMON_REFERENCE_WITH_TEST(false, int, void);
HAMON_COMMON_REFERENCE_WITH_TEST(false, int, int());

HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               *, void               *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               *, void const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               *, void       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int               *, void const volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         *, void               *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         *, void const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         *, void       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const         *, void const volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile*, void               *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile*, void const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile*, void       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int       volatile*, void const volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile*, void               *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile*, void const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile*, void       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const volatile*, void const volatile*);

HAMON_COMMON_REFERENCE_WITH_TEST(true,  void               *, int               *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void               *, int const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void               *, int       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void               *, int const volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void const         *, int               *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void const         *, int const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void const         *, int       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void const         *, int const volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void       volatile*, int               *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void       volatile*, int const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void       volatile*, int       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void       volatile*, int const volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void const volatile*, int               *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void const volatile*, int const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void const volatile*, int       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void const volatile*, int const volatile*);


HAMON_COMMON_REFERENCE_WITH_TEST(true,  void               *, void               *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void               *, void const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void               *, void       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void               *, void const volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void const         *, void               *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void const         *, void const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void const         *, void       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void const         *, void const volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void       volatile*, void               *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void       volatile*, void const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void       volatile*, void       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void       volatile*, void const volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void const volatile*, void               *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void const volatile*, void const         *);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void const volatile*, void       volatile*);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  void const volatile*, void const volatile*);

HAMON_COMMON_REFERENCE_WITH_TEST(true,  int      *&, void      *&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int      *&, void const*&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const*&, void      *&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  int const*&, void const*&);

struct A { A(int) { } };
HAMON_COMMON_REFERENCE_WITH_TEST(true,  A, int);

struct B { };
HAMON_COMMON_REFERENCE_WITH_TEST(false, A, B);

struct C { C(A&) { } };
HAMON_COMMON_REFERENCE_WITH_TEST(true,  A&, C);
#if !defined(_MSC_VER)
HAMON_COMMON_REFERENCE_WITH_TEST(true,  A&, C&&);		// TODO
#endif
HAMON_COMMON_REFERENCE_WITH_TEST(true,  A&, const C&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  A&, C&);
HAMON_COMMON_REFERENCE_WITH_TEST(false, const A&, C);
HAMON_COMMON_REFERENCE_WITH_TEST(false, const A&, const C&);

struct D;
struct E { E(D&) { } };
struct D { D(E&) { } };
HAMON_COMMON_REFERENCE_WITH_TEST(false, D&, E&); // ambiguous conversion

struct F;
struct G { G(const F&) { } };
struct F { F(const G&) { } };

}	// namespace common_reference_with_test

}	// namespace hamon_concepts_test

namespace HAMON_BASIC_COMMON_REFERENCE_NAMESPACE
{

template <template <typename> class Qual1, template <typename> class Qual2>
struct basic_common_reference<
	hamon_concepts_test::common_reference_with_test::F,
	hamon_concepts_test::common_reference_with_test::G,
	Qual1, Qual2>
{
	using type = Qual1<Qual2<hamon_concepts_test::common_reference_with_test::F>>;
};

template <template <typename> class Qual1, template <typename> class Qual2>
struct basic_common_reference<
	hamon_concepts_test::common_reference_with_test::G,
	hamon_concepts_test::common_reference_with_test::F,
	Qual1, Qual2>
{
	using type = Qual1<Qual2<hamon_concepts_test::common_reference_with_test::F>>;
};

}	// namespace HAMON_BASIC_COMMON_REFERENCE_NAMESPACE

namespace hamon_concepts_test
{

namespace common_reference_with_test
{

HAMON_COMMON_REFERENCE_WITH_TEST(false, F&, G&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  F, G);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  F, const G);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  const F, const G);

struct Base { };
struct Derived : Base { };
HAMON_COMMON_REFERENCE_WITH_TEST(true,  Derived&, Base&);
HAMON_COMMON_REFERENCE_WITH_TEST(true,  Derived*, Base*);

}	// namespace common_reference_with_test

}	// namespace hamon_concepts_test

#undef HAMON_COMMON_REFERENCE_WITH_TEST
