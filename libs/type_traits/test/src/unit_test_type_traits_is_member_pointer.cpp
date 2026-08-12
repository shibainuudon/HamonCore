/**
 *	@file	unit_test_type_traits_is_member_pointer.cpp
 *
 *	@brief	is_member_pointer のテスト
 */

#include <hamon/type_traits/is_member_pointer.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_MEMBER_POINTER_TEST_IMPL(b, T)	\
	static_assert(hamon::is_member_pointer_v<T>      == b, #T);	\
	static_assert(hamon::is_member_pointer<T>::value == b, #T);	\
	static_assert(hamon::is_member_pointer<T>{}()    == b, #T);	\
	static_assert(hamon::is_member_pointer<T>{}      == b, #T)

#else

#define HAMON_IS_MEMBER_POINTER_TEST_IMPL(b, T)	\
	static_assert(hamon::is_member_pointer<T>::value == b, #T);	\
	static_assert(hamon::is_member_pointer<T>{}()    == b, #T);	\
	static_assert(hamon::is_member_pointer<T>{}      == b, #T)

#endif

HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, int);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, int*);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, int**);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, int&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, int&&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, int[2]);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, int[]);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, int(*)[2]);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, int(*)[]);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, int(&)[2]);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, int(&)[]);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, int(&&)[2]);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, int(&&)[]);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true, int(UDT::*));
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true, char(UDT::*));
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true, char(UDT::* const));
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true, char(UDT::* volatile));
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true, char(UDT::* const volatile));
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true, int*(UDT::*));
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true, void*(UDT::*));
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::*               )(             )               );
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  char   (UDT::*               )(int          ) const         );
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  short  (UDT::*               )(float        )       volatile);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  long   (UDT::*               )(double       ) const volatile);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  float  (UDT::* const         )(int, int     )               );
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  double (UDT::* const         )(int, int, int) const         );
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  void   (UDT::* const         )(char         )       volatile);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int*   (UDT::* const         )(char*        ) const volatile);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  char*  (UDT::*       volatile)(int&         )               );
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  short* (UDT::*       volatile)(int*         ) const         );
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  long*  (UDT::*       volatile)(long         )       volatile);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  float* (UDT::*       volatile)(short        ) const volatile);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  double*(UDT::* const volatile)(const long&  )               );
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  void*  (UDT::* const volatile)(const int&   ) const         );
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::* const volatile)(char const*  )       volatile);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::* const volatile)(char, char   ) const volatile);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::*               )(...)                              );
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  char   (UDT::*               )(int          , ...) const         );
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  short  (UDT::*               )(float        , ...)       volatile);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  long   (UDT::*               )(double       , ...) const volatile);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  float  (UDT::* const         )(int, int     , ...)               );
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  double (UDT::* const         )(int, int, int, ...) const         );
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  void   (UDT::* const         )(char         , ...)       volatile);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int*   (UDT::* const         )(char*        , ...) const volatile);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  char*  (UDT::*       volatile)(int&         , ...)               );
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  short* (UDT::*       volatile)(int*         , ...) const         );
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  long*  (UDT::*       volatile)(long         , ...)       volatile);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  float* (UDT::*       volatile)(short        , ...) const volatile);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  double*(UDT::* const volatile)(const long&  , ...)               );
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  void*  (UDT::* const volatile)(const int&   , ...) const         );
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::* const volatile)(char const*  , ...)       volatile);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::* const volatile)(char, char   , ...) const volatile);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::*               )(             )               &);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  char   (UDT::*               )(int          ) const         &);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  short  (UDT::*               )(float        )       volatile&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  long   (UDT::*               )(double       ) const volatile&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  float  (UDT::* const         )(int, int     )               &);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  double (UDT::* const         )(int, int, int) const         &);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  void   (UDT::* const         )(char         )       volatile&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int*   (UDT::* const         )(char*        ) const volatile&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  char*  (UDT::*       volatile)(int&         )               &);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  short* (UDT::*       volatile)(int*         ) const         &);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  long*  (UDT::*       volatile)(long         )       volatile&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  float* (UDT::*       volatile)(short        ) const volatile&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  double*(UDT::* const volatile)(const long&  )               &);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  void*  (UDT::* const volatile)(const int&   ) const         &);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::* const volatile)(char const*  )       volatile&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::* const volatile)(char, char   ) const volatile&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::*               )(...)                              &);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  char   (UDT::*               )(int          , ...) const         &);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  short  (UDT::*               )(float        , ...)       volatile&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  long   (UDT::*               )(double       , ...) const volatile&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  float  (UDT::* const         )(int, int     , ...)               &);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  double (UDT::* const         )(int, int, int, ...) const         &);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  void   (UDT::* const         )(char         , ...)       volatile&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int*   (UDT::* const         )(char*        , ...) const volatile&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  char*  (UDT::*       volatile)(int&         , ...)               &);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  short* (UDT::*       volatile)(int*         , ...) const         &);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  long*  (UDT::*       volatile)(long         , ...)       volatile&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  float* (UDT::*       volatile)(short        , ...) const volatile&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  double*(UDT::* const volatile)(const long&  , ...)               &);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  void*  (UDT::* const volatile)(const int&   , ...) const         &);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::* const volatile)(char const*  , ...)       volatile&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::* const volatile)(char, char   , ...) const volatile&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::*               )(             )               &&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  char   (UDT::*               )(int          ) const         &&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  short  (UDT::*               )(float        )       volatile&&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  long   (UDT::*               )(double       ) const volatile&&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  float  (UDT::* const         )(int, int     )               &&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  double (UDT::* const         )(int, int, int) const         &&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  void   (UDT::* const         )(char         )       volatile&&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int*   (UDT::* const         )(char*        ) const volatile&&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  char*  (UDT::*       volatile)(int&         )               &&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  short* (UDT::*       volatile)(int*         ) const         &&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  long*  (UDT::*       volatile)(long         )       volatile&&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  float* (UDT::*       volatile)(short        ) const volatile&&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  double*(UDT::* const volatile)(const long&  )               &&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  void*  (UDT::* const volatile)(const int&   ) const         &&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::* const volatile)(char const*  )       volatile&&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::* const volatile)(char, char   ) const volatile&&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::*               )(...)                              &&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  char   (UDT::*               )(int          , ...) const         &&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  short  (UDT::*               )(float        , ...)       volatile&&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  long   (UDT::*               )(double       , ...) const volatile&&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  float  (UDT::* const         )(int, int     , ...)               &&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  double (UDT::* const         )(int, int, int, ...) const         &&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  void   (UDT::* const         )(char         , ...)       volatile&&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int*   (UDT::* const         )(char*        , ...) const volatile&&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  char*  (UDT::*       volatile)(int&         , ...)               &&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  short* (UDT::*       volatile)(int*         , ...) const         &&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  long*  (UDT::*       volatile)(long         , ...)       volatile&&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  float* (UDT::*       volatile)(short        , ...) const volatile&&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  double*(UDT::* const volatile)(const long&  , ...)               &&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  void*  (UDT::* const volatile)(const int&   , ...) const         &&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::* const volatile)(char const*  , ...)       volatile&&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::* const volatile)(char, char   , ...) const volatile&&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::*               )(             )                noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  char   (UDT::*               )(int          ) const          noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  short  (UDT::*               )(float        )       volatile noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  long   (UDT::*               )(double       ) const volatile noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  float  (UDT::* const         )(int, int     )                noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  double (UDT::* const         )(int, int, int) const          noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  void   (UDT::* const         )(char         )       volatile noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int*   (UDT::* const         )(char*        ) const volatile noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  char*  (UDT::*       volatile)(int&         )                noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  short* (UDT::*       volatile)(int*         ) const          noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  long*  (UDT::*       volatile)(long         )       volatile noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  float* (UDT::*       volatile)(short        ) const volatile noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  double*(UDT::* const volatile)(const long&  )                noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  void*  (UDT::* const volatile)(const int&   ) const          noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::* const volatile)(char const*  )       volatile noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::* const volatile)(char, char   ) const volatile noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::*               )(...)                               noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  char   (UDT::*               )(int          , ...) const          noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  short  (UDT::*               )(float        , ...)       volatile noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  long   (UDT::*               )(double       , ...) const volatile noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  float  (UDT::* const         )(int, int     , ...)                noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  double (UDT::* const         )(int, int, int, ...) const          noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  void   (UDT::* const         )(char         , ...)       volatile noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int*   (UDT::* const         )(char*        , ...) const volatile noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  char*  (UDT::*       volatile)(int&         , ...)                noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  short* (UDT::*       volatile)(int*         , ...) const          noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  long*  (UDT::*       volatile)(long         , ...)       volatile noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  float* (UDT::*       volatile)(short        , ...) const volatile noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  double*(UDT::* const volatile)(const long&  , ...)                noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  void*  (UDT::* const volatile)(const int&   , ...) const          noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::* const volatile)(char const*  , ...)       volatile noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::* const volatile)(char, char   , ...) const volatile noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::*               )(             )               & noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  char   (UDT::*               )(int          ) const         & noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  short  (UDT::*               )(float        )       volatile& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  long   (UDT::*               )(double       ) const volatile& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  float  (UDT::* const         )(int, int     )               & noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  double (UDT::* const         )(int, int, int) const         & noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  void   (UDT::* const         )(char         )       volatile& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int*   (UDT::* const         )(char*        ) const volatile& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  char*  (UDT::*       volatile)(int&         )               & noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  short* (UDT::*       volatile)(int*         ) const         & noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  long*  (UDT::*       volatile)(long         )       volatile& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  float* (UDT::*       volatile)(short        ) const volatile& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  double*(UDT::* const volatile)(const long&  )               & noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  void*  (UDT::* const volatile)(const int&   ) const         & noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::* const volatile)(char const*  )       volatile& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::* const volatile)(char, char   ) const volatile& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::*               )(...)                              & noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  char   (UDT::*               )(int          , ...) const         & noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  short  (UDT::*               )(float        , ...)       volatile& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  long   (UDT::*               )(double       , ...) const volatile& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  float  (UDT::* const         )(int, int     , ...)               & noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  double (UDT::* const         )(int, int, int, ...) const         & noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  void   (UDT::* const         )(char         , ...)       volatile& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int*   (UDT::* const         )(char*        , ...) const volatile& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  char*  (UDT::*       volatile)(int&         , ...)               & noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  short* (UDT::*       volatile)(int*         , ...) const         & noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  long*  (UDT::*       volatile)(long         , ...)       volatile& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  float* (UDT::*       volatile)(short        , ...) const volatile& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  double*(UDT::* const volatile)(const long&  , ...)               & noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  void*  (UDT::* const volatile)(const int&   , ...) const         & noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::* const volatile)(char const*  , ...)       volatile& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::* const volatile)(char, char   , ...) const volatile& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::*               )(             )               && noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  char   (UDT::*               )(int          ) const         && noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  short  (UDT::*               )(float        )       volatile&& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  long   (UDT::*               )(double       ) const volatile&& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  float  (UDT::* const         )(int, int     )               && noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  double (UDT::* const         )(int, int, int) const         && noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  void   (UDT::* const         )(char         )       volatile&& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int*   (UDT::* const         )(char*        ) const volatile&& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  char*  (UDT::*       volatile)(int&         )               && noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  short* (UDT::*       volatile)(int*         ) const         && noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  long*  (UDT::*       volatile)(long         )       volatile&& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  float* (UDT::*       volatile)(short        ) const volatile&& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  double*(UDT::* const volatile)(const long&  )               && noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  void*  (UDT::* const volatile)(const int&   ) const         && noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::* const volatile)(char const*  )       volatile&& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::* const volatile)(char, char   ) const volatile&& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::*               )(...)                              && noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  char   (UDT::*               )(int          , ...) const         && noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  short  (UDT::*               )(float        , ...)       volatile&& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  long   (UDT::*               )(double       , ...) const volatile&& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  float  (UDT::* const         )(int, int     , ...)               && noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  double (UDT::* const         )(int, int, int, ...) const         && noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  void   (UDT::* const         )(char         , ...)       volatile&& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int*   (UDT::* const         )(char*        , ...) const volatile&& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  char*  (UDT::*       volatile)(int&         , ...)               && noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  short* (UDT::*       volatile)(int*         , ...) const         && noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  long*  (UDT::*       volatile)(long         , ...)       volatile&& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  float* (UDT::*       volatile)(short        , ...) const volatile&& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  double*(UDT::* const volatile)(const long&  , ...)               && noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  void*  (UDT::* const volatile)(const int&   , ...) const         && noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::* const volatile)(char const*  , ...)       volatile&& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  int    (UDT::* const volatile)(char, char   , ...) const volatile&& noexcept);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, f1);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, f2);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, f3);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  mf1);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  mf2);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  mf3);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  mf4);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  mp);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(true,  cmf);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, mf1&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, mf2&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, mf3&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, mf4&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, mp&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, cmf&);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, foo0_t);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, foo1_t);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, foo2_t);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, foo3_t);
HAMON_IS_MEMBER_POINTER_TEST_IMPL(false, foo4_t);

#undef HAMON_IS_MEMBER_POINTER_TEST_IMPL
