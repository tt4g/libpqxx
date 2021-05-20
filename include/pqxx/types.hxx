/* Basic type aliases and forward declarations.
 *
 * Copyright (c) 2000-2021, Jeroen T. Vermeulen
 *
 * See COPYING for copyright license.  If you did not receive a file called
 * COPYING with this source code, please notify the distributor of this
 * mistake, or contact the author.
 */
#ifndef PQXX_H_TYPES
#define PQXX_H_TYPES

#include <cstddef>
#include <cstdint>
#include <iterator>

#if defined(PQXX_HAVE_CONCEPTS) && __has_include(<ranges>)
#  include <ranges>
#endif


namespace pqxx
{
/// Number of rows in a result set.
using result_size_type = int;

/// Difference between result sizes.
using result_difference_type = int;

/// Number of fields in a row of database data.
using row_size_type = int;

/// Difference between row sizes.
using row_difference_type = int;

/// Number of bytes in a field of database data.
using field_size_type = std::size_t;

/// Number of bytes in a large object.
using large_object_size_type = int64_t;


// Forward declarations, to help break compilation dependencies.
// These won't necessarily include all classes in libpqxx.
class binarystring;
class connection;
class const_result_iterator;
class const_reverse_result_iterator;
class const_reverse_row_iterator;
class const_row_iterator;
class dbtransaction;
class field;
class largeobjectaccess;
class notification_receiver;
struct range_error;
class result;
class row;
class stream_from;
class transaction_base;

/// Marker for @c stream_from constructors: "stream from table."
/** @deprecated Use stream_from::table() instead.
 */
struct from_table_t
{};

/// Marker for @c stream_from constructors: "stream from query."
/** @deprecated Use stream_from::query() instead.
 */
struct from_query_t
{};


/// Format code: is data text or binary?
/** Binary-compatible with libpq's format codes.
 */
enum class format : int
{
  text = 0,
  binary = 1,
};


/// Remove any constness, volatile, and reference-ness from a type.
/** @deprecated In C++20 we'll replace this with std::remove_cvref.
 */
template<typename TYPE>
using strip_t = std::remove_cv_t<std::remove_reference_t<TYPE>>;


#if defined(PQXX_HAVE_CONCEPTS)
/// The type of a container's elements.
/** At the time of writing there's a similar thing in @c std::experimental,
 * which we may or may not end up using for this.
 */
template<std::ranges::range CONTAINER>
using value_type = decltype(*std::begin(std::declval<CONTAINER>()));
#else  // PQXX_HAVE_CONCEPTS
/// The type of a container's elements.
/** At the time of writing there's a similar thing in @c std::experimental,
 * which we may or may not end up using for this.
 */
template<typename CONTAINER>
using value_type = decltype(*std::begin(std::declval<CONTAINER>()));
#endif // PQXX_HAVE_CONCEPTS


#if defined(PQXX_HAVE_CONCEPTS)
/// Concept: Any type that we can read as a string of @c char.
template<typename STRING>
concept char_string =
  std::ranges::contiguous_range<STRING> and
  std::same_as<strip_t<value_type<STRING>>, char>;

/// Concept: Anything we can iterate to get things we can read as strings.
template<typename RANGE>
concept char_strings =
  std::ranges::range<RANGE> and char_string<strip_t<value_type<RANGE>>>;
#endif // PQXX_HAVE_CONCEPTS


// TODO: Retire these compatibility definitions once we're on C++20.
#if defined(PQXX_HAVE_CONCEPTS)

/// Template argument type for @c char_string.
/** This is a concept, so only available in C++20 or better.  In pre-C++20
 * environments it's just an alias for @c typename.
 */
#define PQXX_CHAR_STRING_ARG pqxx::char_string

/// Template argument type for @c char_strings
/** This is a concept, so only available in C++20 or better.  In pre-C++20
 * environments it's just an alias for @c typename.
 */
#define PQXX_CHAR_STRINGS_ARG pqxx::char_strings

#else // PQXX_HAVE_CONCEPTS
/// Template argument type for @c char_string.
/** This is a concept, so only available in C++20 or better.  In pre-C++20
 * environments it's just an alias for @c typename.
 */
#define PQXX_CHAR_STRING_ARG typename

/// Template argument type for @c char_strings
/** This is a concept, so only available in C++20 or better.  In pre-C++20
 * environments it's just an alias for @c typename.
 */
#define PQXX_CHAR_STRINGS_ARG typename

#endif // PQXX_HAVE_CONCEPTS


} // namespace pqxx
#endif
