/**
 *	@file	unit_test_concepts_cpp17_function_object.cpp
 *
 *	@brief	cpp17_function_object のテスト
 */

#include <hamon/concepts/detail/cpp17_function_object.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_CPP17_FUNCTION_OBJECT_TEST(B, ...)	\
	static_assert(B == hamon::detail::cpp17_function_object<__VA_ARGS__>, "");	\
	static_assert(B == hamon::detail::cpp17_function_object_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_CPP17_FUNCTION_OBJECT_TEST(B, ...)	\
	static_assert(B == hamon::detail::cpp17_function_object<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::detail::cpp17_function_object_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_concepts_test
{

namespace cpp17_function_object_test
{

HAMON_CPP17_FUNCTION_OBJECT_TEST(false, void);
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, int);
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, int*);
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, int&);
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, int&&);
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, int[]);
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, int(*)[]);
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, int(&)[]);
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, int(&&)[]);
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, int[2]);
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, int(*)[2]);
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, int(&)[2]);
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, int(&&)[2]);
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, int());
HAMON_CPP17_FUNCTION_OBJECT_TEST(true,  int(*)());
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, int(&)());
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, int(*)(int));
HAMON_CPP17_FUNCTION_OBJECT_TEST(true,  int(*)(int), int);

enum E { };
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, E);
enum class CE { };
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, CE);
struct A { };
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, A);
union B { };
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, B);

struct F1
{
	void operator()();
};
HAMON_CPP17_FUNCTION_OBJECT_TEST(true,  F1);
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, F1, int);
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, F1, int, float);

struct F2
{
	bool operator()(int) const;
};
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, F2);
HAMON_CPP17_FUNCTION_OBJECT_TEST(true,  F2, int);
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, F2, int, float);

struct F3
{
	bool operator()() const;
	void operator()(int, float);
};
HAMON_CPP17_FUNCTION_OBJECT_TEST(true,  F3);
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, F3, int);
HAMON_CPP17_FUNCTION_OBJECT_TEST(true,  F3, int, float);

struct F4
{
	void operator()(int) = delete;
	void operator()(int) const;
};
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, F4, int);
HAMON_CPP17_FUNCTION_OBJECT_TEST(true,  F4 const, int);

struct F5
{
	void operator()(int&) = delete;
	void operator()(int&&);
	void operator()(int const&);
	void operator()(int const&&) = delete;
};
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, F5, int&);
HAMON_CPP17_FUNCTION_OBJECT_TEST(true,  F5, int&&);
HAMON_CPP17_FUNCTION_OBJECT_TEST(true,  F5, int const&);
HAMON_CPP17_FUNCTION_OBJECT_TEST(false, F5, int const&&);

}	// namespace cpp17_function_object_test

}	// namespace hamon_concepts_test

#undef HAMON_CPP17_FUNCTION_OBJECT_TEST
