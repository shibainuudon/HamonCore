/**
 *	@file	unit_test_type_traits_is_implicit_lifetime.cpp
 *
 *	@brief	is_implicit_lifetime のテスト
 */

#include <hamon/type_traits/is_implicit_lifetime.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
#include <hamon/config.hpp>
#include "type_traits_test_utility.hpp"

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4624)	// デストラクターは暗黙的に削除済みとして定義されました

namespace hamon_type_traits_test
{

namespace is_implicit_lifetime_test
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(b, T)	\
	static_assert(hamon::is_implicit_lifetime_v<T>      == b, #T);	\
	static_assert(hamon::is_implicit_lifetime<T>::value == b, #T);	\
	static_assert(hamon::is_implicit_lifetime<T>()      == b, #T)

#else

#define HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(b, T)	\
	static_assert(hamon::is_implicit_lifetime<T>::value == b, #T);	\
	static_assert(hamon::is_implicit_lifetime<T>()      == b, #T)

#endif

#define HAMON_IS_IMPLICIT_LIFETIME_TEST(b, T)	\
	HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(b,                T);	\
	HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(b, const          T);	\
	HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(b,       volatile T);	\
	HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(b, const volatile T);	\
	HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(false, T&);	\
	HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(false, T&&);	\
	HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(true, T*);		\
	HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(true, T[]);	\
	HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(true, T[3])

struct EmptyStruct {};
struct IncompleteStruct;

struct NoEligibleTrivialContructor {
	NoEligibleTrivialContructor() {};
	NoEligibleTrivialContructor(const NoEligibleTrivialContructor&) {}
	NoEligibleTrivialContructor(NoEligibleTrivialContructor&&) {}
};

struct OnlyDefaultConstructorIsTrivial {
	OnlyDefaultConstructorIsTrivial() = default;
	OnlyDefaultConstructorIsTrivial(const OnlyDefaultConstructorIsTrivial&) {}
	OnlyDefaultConstructorIsTrivial(OnlyDefaultConstructorIsTrivial&&) {}
};

struct AllContstructorsAreTrivial {
	AllContstructorsAreTrivial()                                  = default;
	AllContstructorsAreTrivial(const AllContstructorsAreTrivial&) = default;
	AllContstructorsAreTrivial(AllContstructorsAreTrivial&&)      = default;
};

struct InheritedNoEligibleTrivialConstructor : NoEligibleTrivialContructor {
	using NoEligibleTrivialContructor::NoEligibleTrivialContructor;
};

struct InheritedOnlyDefaultConstructorIsTrivial : OnlyDefaultConstructorIsTrivial {
	using OnlyDefaultConstructorIsTrivial::OnlyDefaultConstructorIsTrivial;
};

struct InheritedAllContstructorsAreTrivial : AllContstructorsAreTrivial {
	using AllContstructorsAreTrivial::AllContstructorsAreTrivial;
};

struct UserDeclaredDestructor {
	~UserDeclaredDestructor() = default;
};

struct UserProvidedDestructor {
	~UserProvidedDestructor() {}
};

struct UserDeletedDestructorInAggregate {
	~UserDeletedDestructorInAggregate() = delete;
};

struct UserDeletedDestructorInNonAggregate {
	virtual void NonAggregate();
	~UserDeletedDestructorInNonAggregate() = delete;
};

struct DeletedDestructorViaBaseInAggregate : UserDeletedDestructorInAggregate {};
struct DeletedDestructorViaBaseInNonAggregate : UserDeletedDestructorInNonAggregate {};

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <bool B>
struct ConstrainedUserDeclaredDefaultConstructor {
	ConstrainedUserDeclaredDefaultConstructor()
		requires B
		= default;
	ConstrainedUserDeclaredDefaultConstructor(const ConstrainedUserDeclaredDefaultConstructor&) {}
};

template <bool B>
struct ConstrainedUserProvidedDestructor {
	~ConstrainedUserProvidedDestructor() = default;
	~ConstrainedUserProvidedDestructor()
		requires B
	{}
};
#endif

#if 0
struct StructWithFlexibleArrayMember {
	int arr[];
};

struct StructWithZeroSizedArray {
	int arr[0];
};
#endif

HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  int);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  char);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  short);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  long);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  long long);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  unsigned int);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  unsigned char);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  unsigned short);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  unsigned long);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  unsigned long long);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  bool);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  float);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  double);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  long double);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  void*);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  hamon::nullptr_t);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  enum_UDT);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  enum_uint32_t_UDT);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  enum_uint16_t_UDT);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  enum_uint8_t_UDT);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  enum_int32_t_UDT);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  enum_int16_t_UDT);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  enum_int8_t_UDT);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  enum_class_UDT);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  enum_class_uint32_t_UDT);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  enum_class_uint16_t_UDT);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  enum_class_uint8_t_UDT);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  enum_class_int32_t_UDT);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  enum_class_int16_t_UDT);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  enum_class_int8_t_UDT);

HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(false, void);
HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(false, void const);
HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(false, void volatile);

HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(false, void());
HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(false, void()&);
HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(false, void() const);
HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(false, void (&)());
HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(true,  void (*)());

HAMON_IS_IMPLICIT_LIFETIME_TEST(true, EmptyStruct);
HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(true, int EmptyStruct::*); // Pointer-to-member
HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(true, int (EmptyStruct::*)());
HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(true, int (EmptyStruct::*)() const);
HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(true, int (EmptyStruct::*)()&);
HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(true, int (EmptyStruct::*)()&&);

HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(true, IncompleteStruct[]);
HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(true, IncompleteStruct[82]);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  UserDeclaredDestructor);
HAMON_IS_IMPLICIT_LIFETIME_TEST(false, UserProvidedDestructor);
HAMON_IS_IMPLICIT_LIFETIME_TEST(false, NoEligibleTrivialContructor);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  OnlyDefaultConstructorIsTrivial);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  AllContstructorsAreTrivial);
HAMON_IS_IMPLICIT_LIFETIME_TEST(false, InheritedNoEligibleTrivialConstructor);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  InheritedOnlyDefaultConstructorIsTrivial);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  InheritedAllContstructorsAreTrivial);
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  UserDeletedDestructorInAggregate);
HAMON_IS_IMPLICIT_LIFETIME_TEST(false, UserDeletedDestructorInNonAggregate);
#if HAMON_CXX_STANDARD >= 17
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  DeletedDestructorViaBaseInAggregate);
#endif
HAMON_IS_IMPLICIT_LIFETIME_TEST(false, DeletedDestructorViaBaseInNonAggregate);
#if defined(HAMON_HAS_CXX20_CONCEPTS)
HAMON_IS_IMPLICIT_LIFETIME_TEST(true,  ConstrainedUserDeclaredDefaultConstructor<true>);
HAMON_IS_IMPLICIT_LIFETIME_TEST(false, ConstrainedUserDeclaredDefaultConstructor<false>);
#if defined(HAMON_USE_STD_IS_IMPLICIT_LIFETIME)
HAMON_IS_IMPLICIT_LIFETIME_TEST(false, ConstrainedUserProvidedDestructor<true>);
HAMON_IS_IMPLICIT_LIFETIME_TEST(false, ConstrainedUserProvidedDestructor<false>);
#endif
#endif
#if 0
HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(true, StructWithFlexibleArrayMember);
HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL(true, StructWithZeroSizedArray);
#endif

#undef HAMON_IS_IMPLICIT_LIFETIME_TEST_IMPL
#undef HAMON_IS_IMPLICIT_LIFETIME_TEST

}	// namespace is_implicit_lifetime_test

}	// namespace hamon_type_traits_test

HAMON_WARNING_POP()
