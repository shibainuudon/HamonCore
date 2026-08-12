/**
 *	@file	unit_test_type_traits_is_member_object_pointer.cpp
 *
 *	@brief	is_member_object_pointer のテスト
 */

#include <hamon/type_traits/is_member_object_pointer.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_MEMBER_OBJECT_POINTER_TEST(b, T)	\
	static_assert(hamon::is_member_object_pointer_v<T>      == b, #T);	\
	static_assert(hamon::is_member_object_pointer<T>::value == b, #T);	\
	static_assert(hamon::is_member_object_pointer<T>{}()    == b, #T);	\
	static_assert(hamon::is_member_object_pointer<T>{}      == b, #T)

#else

#define HAMON_IS_MEMBER_OBJECT_POINTER_TEST(b, T)	\
	static_assert(hamon::is_member_object_pointer<T>::value == b, #T);	\
	static_assert(hamon::is_member_object_pointer<T>{}()    == b, #T);	\
	static_assert(hamon::is_member_object_pointer<T>{}      == b, #T)

#endif

HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false,                int);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, const          int);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false,       volatile int);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, const volatile int);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false,                int*);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, const          int*);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false,       volatile int*);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, const volatile int*);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int**);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int&&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int[2]);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int[]);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int(*)[2]);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int(*)[]);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int(&)[2]);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int(&)[]);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int(&&)[2]);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int(&&)[]);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(true,  int  (UDT::*               ));
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(true,  float(UDT::* const         ));
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(true,  char (UDT::*       volatile));
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(true,  void*(UDT::* const volatile));
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::*               )(             )               );
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, char   (UDT::*               )(int          ) const         );
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, short  (UDT::*               )(float        )       volatile);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, long   (UDT::*               )(double       ) const volatile);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, float  (UDT::* const         )(int, int     )               );
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, double (UDT::* const         )(int, int, int) const         );
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, void   (UDT::* const         )(char         )       volatile);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int*   (UDT::* const         )(char*        ) const volatile);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, char*  (UDT::*       volatile)(int&         )               );
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, short* (UDT::*       volatile)(int*         ) const         );
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, long*  (UDT::*       volatile)(long         )       volatile);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, float* (UDT::*       volatile)(short        ) const volatile);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, double*(UDT::* const volatile)(const long&  )               );
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, void*  (UDT::* const volatile)(const int&   ) const         );
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::* const volatile)(char const*  )       volatile);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::* const volatile)(char, char   ) const volatile);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::*               )(...)                              );
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, char   (UDT::*               )(int          , ...) const         );
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, short  (UDT::*               )(float        , ...)       volatile);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, long   (UDT::*               )(double       , ...) const volatile);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, float  (UDT::* const         )(int, int     , ...)               );
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, double (UDT::* const         )(int, int, int, ...) const         );
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, void   (UDT::* const         )(char         , ...)       volatile);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int*   (UDT::* const         )(char*        , ...) const volatile);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, char*  (UDT::*       volatile)(int&         , ...)               );
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, short* (UDT::*       volatile)(int*         , ...) const         );
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, long*  (UDT::*       volatile)(long         , ...)       volatile);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, float* (UDT::*       volatile)(short        , ...) const volatile);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, double*(UDT::* const volatile)(const long&  , ...)               );
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, void*  (UDT::* const volatile)(const int&   , ...) const         );
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::* const volatile)(char const*  , ...)       volatile);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::* const volatile)(char, char   , ...) const volatile);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::*               )(             )               &);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, char   (UDT::*               )(int          ) const         &);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, short  (UDT::*               )(float        )       volatile&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, long   (UDT::*               )(double       ) const volatile&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, float  (UDT::* const         )(int, int     )               &);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, double (UDT::* const         )(int, int, int) const         &);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, void   (UDT::* const         )(char         )       volatile&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int*   (UDT::* const         )(char*        ) const volatile&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, char*  (UDT::*       volatile)(int&         )               &);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, short* (UDT::*       volatile)(int*         ) const         &);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, long*  (UDT::*       volatile)(long         )       volatile&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, float* (UDT::*       volatile)(short        ) const volatile&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, double*(UDT::* const volatile)(const long&  )               &);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, void*  (UDT::* const volatile)(const int&   ) const         &);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::* const volatile)(char const*  )       volatile&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::* const volatile)(char, char   ) const volatile&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::*               )(...)                              &);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, char   (UDT::*               )(int          , ...) const         &);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, short  (UDT::*               )(float        , ...)       volatile&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, long   (UDT::*               )(double       , ...) const volatile&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, float  (UDT::* const         )(int, int     , ...)               &);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, double (UDT::* const         )(int, int, int, ...) const         &);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, void   (UDT::* const         )(char         , ...)       volatile&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int*   (UDT::* const         )(char*        , ...) const volatile&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, char*  (UDT::*       volatile)(int&         , ...)               &);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, short* (UDT::*       volatile)(int*         , ...) const         &);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, long*  (UDT::*       volatile)(long         , ...)       volatile&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, float* (UDT::*       volatile)(short        , ...) const volatile&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, double*(UDT::* const volatile)(const long&  , ...)               &);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, void*  (UDT::* const volatile)(const int&   , ...) const         &);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::* const volatile)(char const*  , ...)       volatile&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::* const volatile)(char, char   , ...) const volatile&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::*               )(             )               &&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, char   (UDT::*               )(int          ) const         &&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, short  (UDT::*               )(float        )       volatile&&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, long   (UDT::*               )(double       ) const volatile&&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, float  (UDT::* const         )(int, int     )               &&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, double (UDT::* const         )(int, int, int) const         &&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, void   (UDT::* const         )(char         )       volatile&&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int*   (UDT::* const         )(char*        ) const volatile&&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, char*  (UDT::*       volatile)(int&         )               &&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, short* (UDT::*       volatile)(int*         ) const         &&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, long*  (UDT::*       volatile)(long         )       volatile&&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, float* (UDT::*       volatile)(short        ) const volatile&&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, double*(UDT::* const volatile)(const long&  )               &&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, void*  (UDT::* const volatile)(const int&   ) const         &&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::* const volatile)(char const*  )       volatile&&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::* const volatile)(char, char   ) const volatile&&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::*               )(...)                              &&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, char   (UDT::*               )(int          , ...) const         &&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, short  (UDT::*               )(float        , ...)       volatile&&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, long   (UDT::*               )(double       , ...) const volatile&&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, float  (UDT::* const         )(int, int     , ...)               &&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, double (UDT::* const         )(int, int, int, ...) const         &&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, void   (UDT::* const         )(char         , ...)       volatile&&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int*   (UDT::* const         )(char*        , ...) const volatile&&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, char*  (UDT::*       volatile)(int&         , ...)               &&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, short* (UDT::*       volatile)(int*         , ...) const         &&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, long*  (UDT::*       volatile)(long         , ...)       volatile&&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, float* (UDT::*       volatile)(short        , ...) const volatile&&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, double*(UDT::* const volatile)(const long&  , ...)               &&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, void*  (UDT::* const volatile)(const int&   , ...) const         &&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::* const volatile)(char const*  , ...)       volatile&&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::* const volatile)(char, char   , ...) const volatile&&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::*               )(             )                noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, char   (UDT::*               )(int          ) const          noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, short  (UDT::*               )(float        )       volatile noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, long   (UDT::*               )(double       ) const volatile noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, float  (UDT::* const         )(int, int     )                noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, double (UDT::* const         )(int, int, int) const          noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, void   (UDT::* const         )(char         )       volatile noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int*   (UDT::* const         )(char*        ) const volatile noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, char*  (UDT::*       volatile)(int&         )                noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, short* (UDT::*       volatile)(int*         ) const          noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, long*  (UDT::*       volatile)(long         )       volatile noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, float* (UDT::*       volatile)(short        ) const volatile noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, double*(UDT::* const volatile)(const long&  )                noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, void*  (UDT::* const volatile)(const int&   ) const          noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::* const volatile)(char const*  )       volatile noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::* const volatile)(char, char   ) const volatile noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::*               )(...)                               noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, char   (UDT::*               )(int          , ...) const          noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, short  (UDT::*               )(float        , ...)       volatile noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, long   (UDT::*               )(double       , ...) const volatile noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, float  (UDT::* const         )(int, int     , ...)                noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, double (UDT::* const         )(int, int, int, ...) const          noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, void   (UDT::* const         )(char         , ...)       volatile noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int*   (UDT::* const         )(char*        , ...) const volatile noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, char*  (UDT::*       volatile)(int&         , ...)                noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, short* (UDT::*       volatile)(int*         , ...) const          noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, long*  (UDT::*       volatile)(long         , ...)       volatile noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, float* (UDT::*       volatile)(short        , ...) const volatile noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, double*(UDT::* const volatile)(const long&  , ...)                noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, void*  (UDT::* const volatile)(const int&   , ...) const          noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::* const volatile)(char const*  , ...)       volatile noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::* const volatile)(char, char   , ...) const volatile noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::*               )(             )               & noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, char   (UDT::*               )(int          ) const         & noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, short  (UDT::*               )(float        )       volatile& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, long   (UDT::*               )(double       ) const volatile& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, float  (UDT::* const         )(int, int     )               & noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, double (UDT::* const         )(int, int, int) const         & noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, void   (UDT::* const         )(char         )       volatile& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int*   (UDT::* const         )(char*        ) const volatile& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, char*  (UDT::*       volatile)(int&         )               & noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, short* (UDT::*       volatile)(int*         ) const         & noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, long*  (UDT::*       volatile)(long         )       volatile& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, float* (UDT::*       volatile)(short        ) const volatile& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, double*(UDT::* const volatile)(const long&  )               & noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, void*  (UDT::* const volatile)(const int&   ) const         & noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::* const volatile)(char const*  )       volatile& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::* const volatile)(char, char   ) const volatile& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::*               )(...)                              & noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, char   (UDT::*               )(int          , ...) const         & noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, short  (UDT::*               )(float        , ...)       volatile& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, long   (UDT::*               )(double       , ...) const volatile& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, float  (UDT::* const         )(int, int     , ...)               & noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, double (UDT::* const         )(int, int, int, ...) const         & noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, void   (UDT::* const         )(char         , ...)       volatile& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int*   (UDT::* const         )(char*        , ...) const volatile& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, char*  (UDT::*       volatile)(int&         , ...)               & noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, short* (UDT::*       volatile)(int*         , ...) const         & noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, long*  (UDT::*       volatile)(long         , ...)       volatile& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, float* (UDT::*       volatile)(short        , ...) const volatile& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, double*(UDT::* const volatile)(const long&  , ...)               & noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, void*  (UDT::* const volatile)(const int&   , ...) const         & noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::* const volatile)(char const*  , ...)       volatile& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::* const volatile)(char, char   , ...) const volatile& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::*               )(             )               && noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, char   (UDT::*               )(int          ) const         && noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, short  (UDT::*               )(float        )       volatile&& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, long   (UDT::*               )(double       ) const volatile&& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, float  (UDT::* const         )(int, int     )               && noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, double (UDT::* const         )(int, int, int) const         && noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, void   (UDT::* const         )(char         )       volatile&& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int*   (UDT::* const         )(char*        ) const volatile&& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, char*  (UDT::*       volatile)(int&         )               && noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, short* (UDT::*       volatile)(int*         ) const         && noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, long*  (UDT::*       volatile)(long         )       volatile&& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, float* (UDT::*       volatile)(short        ) const volatile&& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, double*(UDT::* const volatile)(const long&  )               && noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, void*  (UDT::* const volatile)(const int&   ) const         && noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::* const volatile)(char const*  )       volatile&& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::* const volatile)(char, char   ) const volatile&& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::*               )(...)                              && noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, char   (UDT::*               )(int          , ...) const         && noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, short  (UDT::*               )(float        , ...)       volatile&& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, long   (UDT::*               )(double       , ...) const volatile&& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, float  (UDT::* const         )(int, int     , ...)               && noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, double (UDT::* const         )(int, int, int, ...) const         && noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, void   (UDT::* const         )(char         , ...)       volatile&& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int*   (UDT::* const         )(char*        , ...) const volatile&& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, char*  (UDT::*       volatile)(int&         , ...)               && noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, short* (UDT::*       volatile)(int*         , ...) const         && noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, long*  (UDT::*       volatile)(long         , ...)       volatile&& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, float* (UDT::*       volatile)(short        , ...) const volatile&& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, double*(UDT::* const volatile)(const long&  , ...)               && noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, void*  (UDT::* const volatile)(const int&   , ...) const         && noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::* const volatile)(char const*  , ...)       volatile&& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, int    (UDT::* const volatile)(char, char   , ...) const volatile&& noexcept);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, f1);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, f2);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, f3);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, mf1);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, mf2);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, mf3);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, mf4);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(true,  mp);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, mp&);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, cmf);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, foo0_t);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, foo1_t);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, foo2_t);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, foo3_t);
HAMON_IS_MEMBER_OBJECT_POINTER_TEST(false, foo4_t);

#undef HAMON_IS_MEMBER_OBJECT_POINTER_TEST
