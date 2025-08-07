/**
 *	@file	unit_test_format_format_kind.cpp
 *
 *	@brief	format_kind のテスト
 *
 *	template<ranges::input_range R>
 *	requires same_as<R, remove_cvref_t<R>>
 *	constexpr range_format format_kind<R> = see below;
 */

#include <hamon/format/format_kind.hpp>
#include <hamon/format/range_format.hpp>
#include <hamon/array.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/deque.hpp>
#include <hamon/forward_list.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/list.hpp>
#include <hamon/map.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/set.hpp>
#include <hamon/span.hpp>
#include <hamon/unordered_map.hpp>
#include <hamon/unordered_set.hpp>
#include <hamon/valarray.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>

namespace hamon_format_test
{

namespace format_kind_test
{

// [format.range.fmtkind]
// If same_as<remove_cvref_t<ranges::range_reference_t<R>>, R> is true,
// format_kind<R> is range_format::disabled.
// [Note 1: This prevents constraint recursion for ranges whose reference type
// is the same range type. For example, std::filesystem::path is a range of
// std::filesystem::path. - end note]
struct recursive_range
{
	struct iterator
	{
		using iterator_concept = hamon::input_iterator_tag;
		using value_type = recursive_range;
		using difference_type = hamon::ptrdiff_t;
		using reference = recursive_range;

		reference operator*() const;

		iterator& operator++();
		iterator operator++(int);

		friend bool operator==(const iterator&, const iterator&);
	};

	iterator begin();
	iterator end();
};

static_assert(hamon::ranges::input_range<recursive_range>, "format_kind requires an input range");
static_assert(hamon::format_kind<recursive_range> == hamon::range_format::disabled);

// TODO
//static_assert(hamon::format_kind<std::filesystem::path> == hamon::range_format::disabled);

static_assert(hamon::format_kind<hamon::map<int, int>> == hamon::range_format::map);
static_assert(hamon::format_kind<hamon::multimap<int, int>> == hamon::range_format::map);
static_assert(hamon::format_kind<hamon::unordered_map<int, int>> == hamon::range_format::map);
static_assert(hamon::format_kind<hamon::unordered_multimap<int, int>> == hamon::range_format::map);

static_assert(hamon::format_kind<hamon::set<int>> == hamon::range_format::set);
static_assert(hamon::format_kind<hamon::multiset<int>> == hamon::range_format::set);
static_assert(hamon::format_kind<hamon::unordered_set<int>> == hamon::range_format::set);
static_assert(hamon::format_kind<hamon::unordered_multiset<int>> == hamon::range_format::set);

static_assert(hamon::format_kind<hamon::array<int, 1>> == hamon::range_format::sequence);
static_assert(hamon::format_kind<hamon::vector<int>> == hamon::range_format::sequence);
static_assert(hamon::format_kind<hamon::deque<int>> == hamon::range_format::sequence);
static_assert(hamon::format_kind<hamon::forward_list<int>> == hamon::range_format::sequence);
static_assert(hamon::format_kind<hamon::list<int>> == hamon::range_format::sequence);

static_assert(hamon::format_kind<hamon::span<int>> == hamon::range_format::sequence);

static_assert(hamon::format_kind<hamon::valarray<int>> == hamon::range_format::sequence);

// [format.range.fmtkind]/3
//   Remarks: Pursuant to [namespace.std], users may specialize format_kind for
//   cv-unqualified program-defined types that model ranges::input_range. Such
//   specializations shall be usable in constant expressions ([expr.const]) and
//   have type const range_format.
// Note only test the specializing, not all constraints.
struct no_specialization : hamon::ranges::view_base
{
	using key_type = void;
	int* begin() const;
	int* end() const;
};

// The struct's "contents" are the same as no_specialization.
struct specialized : hamon::ranges::view_base
{
	using key_type = void;
	int* begin() const;
	int* end() const;
};

}	// namespace format_kind_test

}	// namespace hamon_format_test

template <>
constexpr hamon::range_format hamon::format_kind<hamon_format_test::format_kind_test::specialized> = hamon::range_format::sequence;

namespace hamon_format_test
{

namespace format_kind_test
{

static_assert(hamon::format_kind<no_specialization> == hamon::range_format::set);
static_assert(hamon::format_kind<specialized> == hamon::range_format::sequence);

}	// namespace format_kind_test

}	// namespace hamon_format_test
