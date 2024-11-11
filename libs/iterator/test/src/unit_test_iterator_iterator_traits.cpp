/**
 *	@file	unit_test_iterator_iterator_traits.cpp
 *
 *	@brief	iterator_traits のテスト
 */

#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/contiguous_iterator_tag.hpp>
#include <hamon/iterator/output_iterator_tag.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/forward_list.hpp>
#include <hamon/list.hpp>
#include <hamon/map.hpp>
#include <hamon/string.hpp>
#include <hamon/vector.hpp>
#include <utility>	// pair
#include <iterator>

namespace hamon_iterator_test
{

namespace iterator_traits_test
{

template <typename, typename = hamon::void_t<>>
struct has_iterator_concept
	: public hamon::false_type {};
 
template <typename T>
struct has_iterator_concept<T, hamon::void_t<typename T::iterator_concept>>
	: public hamon::true_type {};

template <typename, typename = hamon::void_t<>>
struct has_iterator_category
	: public hamon::false_type {};
 
template <typename T>
struct has_iterator_category<T, hamon::void_t<typename T::iterator_category>>
	: public hamon::true_type {};

template <typename, typename = hamon::void_t<>>
struct has_value_type
	: public hamon::false_type {};
 
template <typename T>
struct has_value_type<T, hamon::void_t<typename T::value_type>>
	: public hamon::true_type {};

template <typename, typename = hamon::void_t<>>
struct has_difference_type
	: public hamon::false_type {};
 
template <typename T>
struct has_difference_type<T, hamon::void_t<typename T::difference_type>>
	: public hamon::true_type {};

template <typename, typename = hamon::void_t<>>
struct has_pointer
	: public hamon::false_type {};
 
template <typename T>
struct has_pointer<T, hamon::void_t<typename T::pointer>>
	: public hamon::true_type {};

template <typename, typename = hamon::void_t<>>
struct has_reference
	: public hamon::false_type {};
 
template <typename T>
struct has_reference<T, hamon::void_t<typename T::reference>>
	: public hamon::true_type {};

// T* の特殊化
static_assert( has_iterator_concept<hamon::iterator_traits<int*>>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<int               *>::iterator_concept,  hamon::contiguous_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<int               *>::iterator_category, hamon::random_access_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<int               *>::value_type,        int>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<int               *>::difference_type,   hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<int               *>::pointer,           int*>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<int               *>::reference,         int&>::value, "");

static_assert( has_iterator_concept<hamon::iterator_traits<int const*>>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<int const         *>::iterator_concept,  hamon::contiguous_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<int const         *>::iterator_category, hamon::random_access_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<int const         *>::value_type,        int>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<int const         *>::difference_type,   hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<int const         *>::pointer,           int const*>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<int const         *>::reference,         int const&>::value, "");

static_assert( has_iterator_concept<hamon::iterator_traits<int volatile*>>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<int       volatile*>::iterator_concept,  hamon::contiguous_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<int       volatile*>::iterator_category, hamon::random_access_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<int       volatile*>::value_type,        int>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<int       volatile*>::difference_type,   hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<int       volatile*>::pointer,           int volatile*>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<int       volatile*>::reference,         int volatile&>::value, "");

static_assert( has_iterator_concept<hamon::iterator_traits<int const volatile*>>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<int const volatile*>::iterator_concept,  hamon::contiguous_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<int const volatile*>::iterator_category, hamon::random_access_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<int const volatile*>::value_type,        int>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<int const volatile*>::difference_type,   hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<int const volatile*>::pointer,           int const volatile*>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<int const volatile*>::reference,         int const volatile&>::value, "");

// T* だけど is_object_v<T> を満たさない場合
static_assert(!has_iterator_concept <hamon::iterator_traits<void*>>::value, "");
static_assert(!has_iterator_category<hamon::iterator_traits<void*>>::value, "");
static_assert(!has_value_type       <hamon::iterator_traits<void*>>::value, "");
static_assert(!has_difference_type  <hamon::iterator_traits<void*>>::value, "");
static_assert(!has_pointer          <hamon::iterator_traits<void*>>::value, "");
static_assert(!has_reference        <hamon::iterator_traits<void*>>::value, "");

using it1 = hamon::vector<float>::iterator;
//static_assert(!has_iterator_concept<hamon::iterator_traits<it1>>::value, "");	// vector::iteratorがただのポインタの場合はtrueになる
//static_assert(hamon::is_same<hamon::iterator_traits<it1>::iterator_concept,  hamon::contiguous_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it1>::iterator_category, hamon::random_access_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it1>::value_type,        float>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it1>::difference_type,   hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it1>::pointer,           float*>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it1>::reference,         float&>::value, "");

using it2 = hamon::vector<float>::const_iterator;
//static_assert(!has_iterator_concept<hamon::iterator_traits<it2>>::value, "");	// vector::const_iteratorがただのポインタの場合はtrueになる
//static_assert(hamon::is_same<hamon::iterator_traits<it2>::iterator_concept,  hamon::contiguous_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it2>::iterator_category, hamon::random_access_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it2>::value_type,        float>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it2>::difference_type,   hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it2>::pointer,           float const*>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it2>::reference,         float const&>::value, "");

using it3 = hamon::string::iterator;
//static_assert(!has_iterator_concept<hamon::iterator_traits<it3>>::value, "");	// string::iteratorがただのポインタの場合はtrueになる
//static_assert(hamon::is_same<hamon::iterator_traits<it3>::iterator_concept,  hamon::contiguous_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it3>::iterator_category, hamon::random_access_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it3>::value_type,        char>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it3>::difference_type,   hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it3>::pointer,           char*>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it3>::reference,         char&>::value, "");

using it4 = hamon::list<int>::iterator;
static_assert(!has_iterator_concept<hamon::iterator_traits<it4>>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it4>::iterator_category, hamon::bidirectional_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it4>::value_type,        int>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it4>::difference_type,   hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it4>::pointer,           int*>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it4>::reference,         int&>::value, "");

using it5 = hamon::forward_list<int>::iterator;
static_assert(!has_iterator_concept<hamon::iterator_traits<it5>>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it5>::iterator_category, hamon::forward_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it5>::value_type,        int>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it5>::difference_type,   hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it5>::pointer,           int*>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it5>::reference,         int&>::value, "");

using it6 = std::reverse_iterator<int*>;
static_assert(!has_iterator_concept<hamon::iterator_traits<it6>>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it6>::iterator_category, hamon::random_access_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it6>::value_type,        int>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it6>::difference_type,   hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it6>::pointer,           int*>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it6>::reference,         int&>::value, "");

using it7 = hamon::map<int, float>::iterator;
static_assert(!has_iterator_concept<hamon::iterator_traits<it7>>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it7>::iterator_category, hamon::bidirectional_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it7>::difference_type,   hamon::ptrdiff_t>::value, "");
#if !defined(HAMON_USE_STD_MAP)
static_assert(hamon::is_same<hamon::iterator_traits<it7>::value_type,        hamon::pair<int const, float>>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it7>::pointer,           hamon::pair<int const, float>*>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<it7>::reference,         hamon::pair<int const, float>&>::value, "");
#endif

// [iterator.traits]/3.1

struct MyIterator1
{
	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = char const;
	using difference_type   = short;
	using pointer           = int const;
	using reference         = long;
};

static_assert(!has_iterator_concept<hamon::iterator_traits<MyIterator1>>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator1>::iterator_category, hamon::forward_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator1>::value_type,        char const>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator1>::difference_type,   short>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator1>::pointer,           int const>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator1>::reference,         long>::value, "");

struct MyIterator2
{
	using iterator_category = hamon::bidirectional_iterator_tag;
	using value_type        = float;
	using difference_type   = double const;
	using reference         = long double const&;
};

static_assert(!has_iterator_concept<hamon::iterator_traits<MyIterator2>>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator2>::iterator_category, hamon::bidirectional_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator2>::value_type,        float>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator2>::difference_type,   double const>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator2>::pointer,           void>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator2>::reference,         long double const&>::value, "");

// [iterator.traits]/3.2

struct MyIterator3
{
	using value_type        = int const;
	using difference_type   = long const;

	int& operator*() const;
	MyIterator3& operator++();
	MyIterator3  operator++(int);
	bool operator==(MyIterator3 const&) const;
	bool operator!=(MyIterator3 const&) const;
};

static_assert(!has_iterator_concept<hamon::iterator_traits<MyIterator3>>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator3>::iterator_category, hamon::forward_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator3>::value_type,        int>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator3>::difference_type,   long const>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator3>::pointer,           void>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator3>::reference,         int&>::value, "");

struct MyIterator4
{
	using value_type        = float const;
	using difference_type   = int const;
	using pointer           = short const;
	using reference         = char const;

	float& operator*() const;
	MyIterator4& operator++();
	MyIterator4  operator++(int);
	MyIterator4& operator--();
	MyIterator4  operator--(int);
	bool operator==(MyIterator4 const&) const;
	bool operator!=(MyIterator4 const&) const;
};

static_assert(!has_iterator_concept<hamon::iterator_traits<MyIterator4>>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator4>::iterator_category, hamon::bidirectional_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator4>::value_type,        float>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator4>::difference_type,   int const>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator4>::pointer,           short const>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator4>::reference,         char const>::value, "");

struct MyIterator5
{
	using value_type        = int const;
	using difference_type   = long const;

	int operator*() const;
	int* operator->() const;
	MyIterator5& operator++();
	MyIterator5  operator++(int);
	bool operator==(MyIterator5 const&) const;
	bool operator!=(MyIterator5 const&) const;
};

static_assert(!has_iterator_concept<hamon::iterator_traits<MyIterator5>>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator5>::iterator_category, hamon::input_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator5>::value_type,        int>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator5>::difference_type,   long const>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator5>::pointer,           int*>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator5>::reference,         int>::value, "");

struct MyIterator6
{
	using value_type        = int const;

	value_type& operator*() const;
	value_type* operator->() const;
	MyIterator6& operator++();
	MyIterator6  operator++(int);
	MyIterator6& operator--();
	MyIterator6  operator--(int);
	MyIterator6& operator+=(hamon::ptrdiff_t);
	MyIterator6& operator-=(hamon::ptrdiff_t);
	MyIterator6 operator+(hamon::ptrdiff_t) const;
	MyIterator6 operator-(hamon::ptrdiff_t) const;
	hamon::ptrdiff_t operator-(MyIterator6 const&) const;
	friend MyIterator6 operator+(hamon::ptrdiff_t, MyIterator6 const&);
	value_type& operator[](hamon::ptrdiff_t);
	bool operator==(MyIterator6 const&) const;
	bool operator!=(MyIterator6 const&) const;
	bool operator< (MyIterator6 const&) const;
	bool operator> (MyIterator6 const&) const;
	bool operator<=(MyIterator6 const&) const;
	bool operator>=(MyIterator6 const&) const;
};

static_assert(!has_iterator_concept<hamon::iterator_traits<MyIterator6>>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator6>::iterator_category, hamon::random_access_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator6>::value_type,        int>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator6>::difference_type,   hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator6>::pointer,           int const*>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator6>::reference,         int const&>::value, "");

struct MyIterator7
{
	using iterator_category = hamon::random_access_iterator_tag;
	using value_type        = float const;
	using difference_type   = long const;

	int& operator*() const;
	MyIterator7& operator++();
	MyIterator7  operator++(int);
	bool operator==(MyIterator7 const&) const;
	bool operator!=(MyIterator7 const&) const;
};

static_assert(!has_iterator_concept<hamon::iterator_traits<MyIterator7>>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator7>::iterator_category, hamon::random_access_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator7>::value_type,        float>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator7>::difference_type,   long const>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator7>::pointer,           void>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator7>::reference,         int&>::value, "");

// [iterator.traits]/3.3

struct MyIterator8
{
	using value_type        = int;
	using difference_type   = long const;

	int& operator*() const;
	MyIterator8& operator++();
	MyIterator8  operator++(int);
};

static_assert(!has_iterator_concept<hamon::iterator_traits<MyIterator8>>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator8>::iterator_category, hamon::output_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator8>::value_type,        void>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator8>::difference_type,   long const>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator8>::pointer,           void>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator8>::reference,         void>::value, "");

struct MyIterator9
{
	using value_type        = int;

	int& operator*() const;
	MyIterator9& operator++();
	MyIterator9  operator++(int);
};

static_assert(!has_iterator_concept<hamon::iterator_traits<MyIterator9>>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator9>::iterator_category, hamon::output_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator9>::value_type,        void>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator9>::difference_type,   void>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator9>::pointer,           void>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<MyIterator9>::reference,         void>::value, "");

// [iterator.traits]/3.4

static_assert(!has_iterator_concept <hamon::iterator_traits<int>>::value, "");
static_assert(!has_iterator_category<hamon::iterator_traits<int>>::value, "");
static_assert(!has_value_type       <hamon::iterator_traits<int>>::value, "");
static_assert(!has_difference_type  <hamon::iterator_traits<int>>::value, "");
static_assert(!has_pointer          <hamon::iterator_traits<int>>::value, "");
static_assert(!has_reference        <hamon::iterator_traits<int>>::value, "");

struct S{};

static_assert(!has_iterator_concept <hamon::iterator_traits<S>>::value, "");
static_assert(!has_iterator_category<hamon::iterator_traits<S>>::value, "");
static_assert(!has_value_type       <hamon::iterator_traits<S>>::value, "");
static_assert(!has_difference_type  <hamon::iterator_traits<S>>::value, "");
static_assert(!has_pointer          <hamon::iterator_traits<S>>::value, "");
static_assert(!has_reference        <hamon::iterator_traits<S>>::value, "");

static_assert( has_iterator_concept <hamon::iterator_traits<S*>>::value, "");
static_assert( has_iterator_category<hamon::iterator_traits<S*>>::value, "");
static_assert( has_value_type       <hamon::iterator_traits<S*>>::value, "");
static_assert( has_difference_type  <hamon::iterator_traits<S*>>::value, "");
static_assert( has_pointer          <hamon::iterator_traits<S*>>::value, "");
static_assert( has_reference        <hamon::iterator_traits<S*>>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<S*>::iterator_concept,  hamon::contiguous_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<S*>::iterator_category, hamon::random_access_iterator_tag>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<S*>::value_type,        S>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<S*>::difference_type,   hamon::ptrdiff_t>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<S*>::pointer,           S*>::value, "");
static_assert(hamon::is_same<hamon::iterator_traits<S*>::reference,         S&>::value, "");

}	// namespace iterator_traits_test

}	// namespace hamon_iterator_test
