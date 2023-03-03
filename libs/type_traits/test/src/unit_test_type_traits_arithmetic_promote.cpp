/**
 *	@file	unit_test_type_traits_arithmetic_promote.cpp
 *
 *	@brief	arithmetic_promote のテスト
 */

#include <hamon/type_traits/arithmetic_promote.hpp>
#include <hamon/type_traits/is_same.hpp>

#define HAMON_ARITHMETIC_PROMOTE_TEST(T, ...)	\
	static_assert(hamon::is_same<T, hamon::arithmetic_promote<__VA_ARGS__>::type>::value, "");	\
	static_assert(hamon::is_same<T, hamon::arithmetic_promote_t<__VA_ARGS__>>::value, "")

HAMON_ARITHMETIC_PROMOTE_TEST(float,				float);
HAMON_ARITHMETIC_PROMOTE_TEST(double,				double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,			long double);
HAMON_ARITHMETIC_PROMOTE_TEST(int,					int);
HAMON_ARITHMETIC_PROMOTE_TEST(char,					char);
HAMON_ARITHMETIC_PROMOTE_TEST(short,				short);
HAMON_ARITHMETIC_PROMOTE_TEST(long,					long);
HAMON_ARITHMETIC_PROMOTE_TEST(long long,			long long);
HAMON_ARITHMETIC_PROMOTE_TEST(unsigned int,			unsigned int);
HAMON_ARITHMETIC_PROMOTE_TEST(unsigned char,		unsigned char);
HAMON_ARITHMETIC_PROMOTE_TEST(unsigned short,		unsigned short);
HAMON_ARITHMETIC_PROMOTE_TEST(unsigned long,		unsigned long);
HAMON_ARITHMETIC_PROMOTE_TEST(unsigned long long,	unsigned long long);

HAMON_ARITHMETIC_PROMOTE_TEST(float,		float,			float);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		float,			double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	float,			long double);
HAMON_ARITHMETIC_PROMOTE_TEST(float,		float,			int);
HAMON_ARITHMETIC_PROMOTE_TEST(float,		float,			char);
HAMON_ARITHMETIC_PROMOTE_TEST(float,		float,			unsigned int);
HAMON_ARITHMETIC_PROMOTE_TEST(float,		float,			unsigned char);

HAMON_ARITHMETIC_PROMOTE_TEST(double,		double,			float);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		double,			double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	double,			long double);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		double,			int);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		double,			char);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		double,			unsigned int);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		double,			unsigned char);

HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	float);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	long double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	int);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	char);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	unsigned int);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	unsigned char);

HAMON_ARITHMETIC_PROMOTE_TEST(float,		int,			float);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		int,			double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	int,			long double);
HAMON_ARITHMETIC_PROMOTE_TEST(int,			int,			int);
HAMON_ARITHMETIC_PROMOTE_TEST(int,			int,			char);
HAMON_ARITHMETIC_PROMOTE_TEST(unsigned int,	int,			unsigned int);
HAMON_ARITHMETIC_PROMOTE_TEST(int,			int,			unsigned char);

HAMON_ARITHMETIC_PROMOTE_TEST(float,		char,			float);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		char,			double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	char,			long double);
HAMON_ARITHMETIC_PROMOTE_TEST(int,			char,			int);
HAMON_ARITHMETIC_PROMOTE_TEST(int,			char,			char);
HAMON_ARITHMETIC_PROMOTE_TEST(unsigned int,	char,			unsigned int);
HAMON_ARITHMETIC_PROMOTE_TEST(int,			char,			unsigned char);

HAMON_ARITHMETIC_PROMOTE_TEST(float,		unsigned int,	float);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		unsigned int,	double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	unsigned int,	long double);
HAMON_ARITHMETIC_PROMOTE_TEST(unsigned int, unsigned int,	int);
HAMON_ARITHMETIC_PROMOTE_TEST(unsigned int,	unsigned int,	char);
HAMON_ARITHMETIC_PROMOTE_TEST(unsigned int,	unsigned int,	unsigned int);
HAMON_ARITHMETIC_PROMOTE_TEST(unsigned int,	unsigned int,	unsigned char);

HAMON_ARITHMETIC_PROMOTE_TEST(float,		unsigned char,	float);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		unsigned char,	double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	unsigned char,	long double);
HAMON_ARITHMETIC_PROMOTE_TEST(int,			unsigned char,	int);
HAMON_ARITHMETIC_PROMOTE_TEST(int,			unsigned char,	char);
HAMON_ARITHMETIC_PROMOTE_TEST(unsigned int,	unsigned char,	unsigned int);
HAMON_ARITHMETIC_PROMOTE_TEST(int,			unsigned char,	unsigned char);

HAMON_ARITHMETIC_PROMOTE_TEST(float,		float,			float,			float);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		float,			float,			double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	float,			float,			long double);
HAMON_ARITHMETIC_PROMOTE_TEST(float,		float,			float,			int);
HAMON_ARITHMETIC_PROMOTE_TEST(float,		float,			float,			char);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		float,			double,			float);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		float,			double,			double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	float,			double,			long double);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		float,			double,			int);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		float,			double,			char);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	float,			long double,	float);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	float,			long double,	double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	float,			long double,	long double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	float,			long double,	int);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	float,			long double,	char);
HAMON_ARITHMETIC_PROMOTE_TEST(float,		float,			int,			float);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		float,			int,			double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	float,			int,			long double);
HAMON_ARITHMETIC_PROMOTE_TEST(float,		float,			int,			int);
HAMON_ARITHMETIC_PROMOTE_TEST(float,		float,			int,			char);
HAMON_ARITHMETIC_PROMOTE_TEST(float,		float,			char,			float);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		float,			char,			double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	float,			char,			long double);
HAMON_ARITHMETIC_PROMOTE_TEST(float,		float,			char,			int);
HAMON_ARITHMETIC_PROMOTE_TEST(float,		float,			char,			char);

HAMON_ARITHMETIC_PROMOTE_TEST(double,		double,			float,			float);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		double,			float,			double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	double,			float,			long double);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		double,			float,			int);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		double,			float,			char);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		double,			double,			float);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		double,			double,			double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	double,			double,			long double);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		double,			double,			int);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		double,			double,			char);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	double,			long double,	float);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	double,			long double,	double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	double,			long double,	long double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	double,			long double,	int);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	double,			long double,	char);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		double,			int,			float);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		double,			int,			double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	double,			int,			long double);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		double,			int,			int);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		double,			int,			char);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		double,			char,			float);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		double,			char,			double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	double,			char,			long double);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		double,			char,			int);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		double,			char,			char);

HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	float,			float);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	float,			double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	float,			long double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	float,			int);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	float,			char);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	double,			float);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	double,			double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	double,			long double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	double,			int);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	double,			char);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	long double,	float);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	long double,	double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	long double,	long double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	long double,	int);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	long double,	char);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	int,			float);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	int,			double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	int,			long double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	int,			int);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	int,			char);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	char,			float);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	char,			double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	char,			long double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	char,			int);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	long double,	char,			char);

HAMON_ARITHMETIC_PROMOTE_TEST(float,		int,			float,			float);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		int,			float,			double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	int,			float,			long double);
HAMON_ARITHMETIC_PROMOTE_TEST(float,		int,			float,			int);
HAMON_ARITHMETIC_PROMOTE_TEST(float,		int,			float,			char);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		int,			double,			float);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		int,			double,			double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	int,			double,			long double);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		int,			double,			int);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		int,			double,			char);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	int,			long double,	float);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	int,			long double,	double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	int,			long double,	long double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	int,			long double,	int);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	int,			long double,	char);
HAMON_ARITHMETIC_PROMOTE_TEST(float,		int,			int,			float);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		int,			int,			double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	int,			int,			long double);
HAMON_ARITHMETIC_PROMOTE_TEST(int,			int,			int,			int);
HAMON_ARITHMETIC_PROMOTE_TEST(int,			int,			int,			char);
HAMON_ARITHMETIC_PROMOTE_TEST(float,		int,			char,			float);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		int,			char,			double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	int,			char,			long double);
HAMON_ARITHMETIC_PROMOTE_TEST(int,			int,			char,			int);
HAMON_ARITHMETIC_PROMOTE_TEST(int,			int,			char,			char);

HAMON_ARITHMETIC_PROMOTE_TEST(float,		char,			float,			float);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		char,			float,			double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	char,			float,			long double);
HAMON_ARITHMETIC_PROMOTE_TEST(float,		char,			float,			int);
HAMON_ARITHMETIC_PROMOTE_TEST(float,		char,			float,			char);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		char,			double,			float);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		char,			double,			double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	char,			double,			long double);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		char,			double,			int);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		char,			double,			char);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	char,			long double,	float);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	char,			long double,	double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	char,			long double,	long double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	char,			long double,	int);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	char,			long double,	char);
HAMON_ARITHMETIC_PROMOTE_TEST(float,		char,			int,			float);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		char,			int,			double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	char,			int,			long double);
HAMON_ARITHMETIC_PROMOTE_TEST(int,			char,			int,			int);
HAMON_ARITHMETIC_PROMOTE_TEST(int,			char,			int,			char);
HAMON_ARITHMETIC_PROMOTE_TEST(float,		char,			char,			float);
HAMON_ARITHMETIC_PROMOTE_TEST(double,		char,			char,			double);
HAMON_ARITHMETIC_PROMOTE_TEST(long double,	char,			char,			long double);
HAMON_ARITHMETIC_PROMOTE_TEST(int,			char,			char,			int);
HAMON_ARITHMETIC_PROMOTE_TEST(int,			char,			char,			char);

#undef HAMON_ARITHMETIC_PROMOTE_TEST
