#pragma once

#include <span>
#include <numeric>
#include <stdexcept>
#include <utility>
#include <cassert>
#include <source_location>
#include <iostream>
#include <concepts>

#include <boost_ut.h>

namespace metatests
  {
using boost::ut::reflection::source_location;

struct test_result
  {
  enum struct value_type : uint8_t
    {
    succeed,
    failed
    };
  using enum value_type;
  value_type value_{};

  explicit constexpr operator bool() const noexcept { return value_ == succeed; }

  constexpr test_result() noexcept = default;

  explicit constexpr test_result(bool value) noexcept : value_{value ? succeed : failed} {}

  explicit constexpr test_result(value_type value) noexcept : value_{value} {}

  constexpr test_result & operator|=(test_result rh) noexcept
    {
    value_ = value_ == failed || rh.value_ == failed ? failed : succeed;
    return *this;
    }

  constexpr test_result operator|(test_result rh) noexcept
    {
    return test_result{value_ == failed || rh.value_ == failed ? failed : succeed};
    }
  };

template<typename T, typename... U>
concept is_any_of = (std::same_as<T, U> || ...);

template<typename test_result_type>
concept compatibile_test_result = is_any_of<test_result_type, bool, test_result>;

template<compatibile_test_result test_result_type>
constexpr auto
  expect(test_result_type expression, source_location const location = source_location::current()) -> test_result
  {
  if(std::is_constant_evaluated())
    {
    if(!expression)
      throw;
    return test_result{expression};
    }
  else
    {
    boost::ut::expect(static_cast<bool>(expression), location);
    return test_result{expression};
    }
  }

template<typename T, std::equality_comparable_with<T> U>
constexpr auto
  expect_eq(T const & left, U const & right, source_location const location = source_location::current()) -> test_result
  {
  if(std::is_constant_evaluated())
    {
    if(left != right)
      throw;
    return test_result{left == right};
    }
  else
    {
    boost::ut::expect(boost::ut::eq(left, right), location);
    return test_result{left == right};
    }
  }

template<typename T, std::equality_comparable_with<T> U>
constexpr auto expect_neq(T const & left, U const & right, source_location const location = source_location::current())
  -> test_result
  {
  if(std::is_constant_evaluated())
    {
    if(left == right)
      throw;
    return test_result{left != right};
    }
  else
    {
    boost::ut::expect(boost::ut::neq(left, right), location);
    return test_result{left != right};
    }
  }

template<typename T, std::equality_comparable_with<T> U>
constexpr auto
  expect_gt(T const & left, U const & right, source_location const location = source_location::current()) -> test_result
  {
  if(std::is_constant_evaluated())
    {
    if(left <= right)
      throw;
    return test_result{left > right};
    }
  else
    {
    boost::ut::expect(boost::ut::gt(left, right), location);
    return test_result{left > right};
    }
  }

template<typename T, std::equality_comparable_with<T> U>
constexpr auto
  expect_lt(T const & left, U const & right, source_location const location = source_location::current()) -> test_result
  {
  if(std::is_constant_evaluated())
    {
    if(left >= right)
      throw;
    return test_result{left < right};
    }
  else
    {
    boost::ut::expect(boost::ut::lt(left, right), location);
    return test_result{left < right};
    }
  }
template<typename T, typename U, typename X>
  requires requires(T const & t, U const & u, X const & x) {
    { t - u } -> std::three_way_comparable_with<X>;
  }
constexpr auto expect_approx(
  T const & left, U const & right, X const & approx, source_location const location = source_location::current()
) -> test_result
  {
  if(std::is_constant_evaluated())
    {
    using sub_res_type = decltype(left - right);
    sub_res_type diff{left - right};
    if(diff < sub_res_type(0))
      diff = -diff;
    if(diff >= approx)
      throw;
    return test_result{diff < approx};
    }
  else
    {
    boost::ut::expect(boost::ut::approx(left, right, approx), location);
    return test_result{boost::ut::approx(left, right, approx)};
    }
  }

template<typename except, typename test_type>
test_result require_throw(test_type const & test) noexcept
  {
  try
    {
    test();
    }
  catch(except const &)
    {
    return test_result{};
    }
  catch(...)
    {
    return test_result{false};
    }
  return test_result{false};
  }

template<typename test_type>
test_result require_throw(test_type const & test) noexcept
  {
  try
    {
    test();
    }
  catch(...)
    {
    return test_result{};
    }
  return test_result{false};
  }

template<typename unit_test>
[[maybe_unused]]
constexpr test_result
  run_runtime_test(unit_test const & test, source_location const location = source_location::current())
  {
  return expect(test(), location);
  }

template<typename unit_test>
[[maybe_unused]]
consteval test_result
  run_consteval_test(unit_test const & test, source_location const location = source_location::current())
  {
  return expect(test(), location);
  }

namespace detail
  {
  template<typename T, typename... Args>
  struct infer_type
    {
    using type = T;
    using next_elem = infer_type<Args...>;
    };

  template<typename T>
  struct infer_type<T>
    {
    using type = T;
    using next_elem = void;
    };
  }  // namespace detail

template<typename... Args>
struct type_list
  {
  using type_iterator = detail::infer_type<Args...>;
  };

namespace detail
  {
  template<typename templ_list>
  struct test_invoke
    {
    template<typename unit_test>
    constexpr static test_result constexpr_run(unit_test const & test)
      {
      return test_invoke<typename templ_list::type_iterator>::do_run(test);
      }

    template<typename unit_test>
    consteval static test_result consteval_run(unit_test const & test)
      {
      return test_invoke<typename templ_list::type_iterator>::do_run(test);
      }

    template<typename unit_test>
    constexpr static test_result do_run(unit_test const & test)
      {
      using test_type = typename templ_list::type;
      using next_test = typename templ_list::next_elem;
      using ptr_type = test_type const *;
      test_result res = test(ptr_type{});
      if constexpr(!std::is_same_v<void, next_test>)
        res |= test_invoke<next_test>::do_run(test);
      return res;
      }
    };

  }  // namespace detail

template<typename templ_list, typename unit_test>
[[maybe_unused]]
constexpr test_result
  run_runtime_test(unit_test const & test, source_location const location = source_location::current())
  {
  return expect(detail::test_invoke<templ_list>::constexpr_run(test), location);
  }

template<typename templ_list, typename unit_test>
[[maybe_unused]]
consteval test_result
  run_consteval_test(unit_test const & test, source_location const location = source_location::current())
  {
#ifndef DISABLE_CONSTEVAL_TESTING
  // same gcc can fail building consteval complicated code, ex on ubuntu it reports nonsense while on gentoo there is no
  // problem at all
  return expect(detail::test_invoke<templ_list>::consteval_run(test), location);
#else
  return test_result{};
#endif
  }

consteval test_result test()
  {
  using traits_test_list = metatests::type_list<uint16_t, int32_t, int64_t, double>;
  int counter{};
  auto test_fn = [&counter]<typename value_type>(value_type const *) -> test_result
  {
    counter++;
    return test_result{};
  };

  auto res = run_runtime_test<traits_test_list>(test_fn);
  return res | test_result{counter == 4};
  }

static_assert(test());

namespace detail
  {
  template<typename templ_list, typename templ_list2>
  struct test_invoke_dual
    {
    template<typename unit_test>
    constexpr static test_result constexpr_run(unit_test const & test)
      {
      return test_invoke_dual<typename templ_list::type_iterator, typename templ_list2::type_iterator>::do_run(test);
      }

    template<typename unit_test>
    consteval static test_result consteval_run(unit_test const & test)
      {
      return test_invoke_dual<typename templ_list::type_iterator, typename templ_list2::type_iterator>::do_run(test);
      }

    template<typename unit_test>
    constexpr static test_result do_run(unit_test const & test)
      {
      using test_type = typename templ_list::type;
      using next_test = typename templ_list::next_elem;

      test_result res = do_run_sec<test_type>(test);
      if constexpr(!std::is_same_v<void, next_test>)
        res |= test_invoke_dual<next_test, templ_list2>::do_run(test);
      return res;
      }

    template<typename test_type1, typename unit_test>
    constexpr static test_result do_run_sec(unit_test const & test)
      {
      using test_type2 = typename templ_list2::type;
      using next_test = typename templ_list2::next_elem;

      using ptr_type1 = test_type1 const *;
      using ptr_type2 = test_type2 const *;
      test_result res = test(ptr_type1{}, ptr_type2{});
      if constexpr(!std::is_same_v<void, next_test>)
        res |= test_invoke_dual<templ_list, next_test>::template do_run_sec<test_type1>(test);
      return res;
      }
    };
  }  // namespace detail

template<typename templ_list, typename templ_list2, typename unit_test>
[[maybe_unused]]
constexpr test_result
  run_constexpr_test_dual(unit_test const & test, source_location const location = source_location::current())
  {
  return expect(detail::test_invoke_dual<templ_list, templ_list2>::constexpr_run(test), location);
  }

template<typename templ_list, typename templ_list2, typename unit_test>
[[maybe_unused]]
consteval test_result
  run_consteval_test_dual(unit_test const & test, source_location const location = source_location::current())
  {
  return expect(detail::test_invoke_dual<templ_list, templ_list2>::consteval_run(test), location);
  }

consteval test_result test_dual()
  {
  using traits_test_list = metatests::type_list<uint16_t, int32_t, int64_t, double>;
  using traits_test_list2 = metatests::type_list<uint16_t, uint32_t, uint64_t>;
  int counter{};
  auto test_fn
    = [&counter]<typename value_type, typename value_type2>(value_type const *, value_type2 const *) -> test_result
  {
    counter++;
    return test_result{};
  };

  auto res = run_constexpr_test_dual<traits_test_list, traits_test_list2>(test_fn);
  return res | test_result{counter == 12};
  }

static_assert(test_dual());
  }  // namespace metatests

void dump(auto const & result)
  {
  for(auto el: result)
    std::cout << el << ",";
  std::cout << std::endl;
  }

struct non_trivial
  {
  int value_;

  constexpr non_trivial() noexcept : value_{0x1fff'ffff} {}

  constexpr non_trivial(int value) noexcept : value_{value} {}

  constexpr non_trivial(non_trivial && r) noexcept : value_{std::exchange(r.value_, 0x1fff'ffff)} {}

  constexpr non_trivial(non_trivial const & r) noexcept : value_{r.value_} {}

  constexpr non_trivial & operator=(non_trivial && r) noexcept
    {
    value_ = std::exchange(r.value_, 0x1fff'ffff);
    return *this;
    }

  constexpr non_trivial & operator=(non_trivial const & r) noexcept
    {
    value_ = r.value_;
    return *this;
    }

  constexpr non_trivial & operator++() noexcept
    {
    ++value_;
    return *this;
    }

  constexpr ~non_trivial() {}

  constexpr bool operator==(non_trivial const & r) const noexcept = default;

  constexpr bool operator==(int r) const noexcept { return value_ == r; }

  void swap(non_trivial & r) noexcept { std::swap(value_, r.value_); }
  };

inline std::ostream & operator<<(std::ostream & stream, non_trivial const & v)
  {
  stream << v.value_;
  return stream;
  }

struct non_trivial_ptr
  {
  int * value_;

  constexpr non_trivial_ptr() noexcept : value_{} {}

  constexpr non_trivial_ptr(int value) noexcept : value_{new int{value}} {}

  constexpr non_trivial_ptr(non_trivial_ptr && r) noexcept : value_{std::exchange(r.value_, nullptr)} {}

  constexpr non_trivial_ptr(non_trivial_ptr const & r) noexcept : value_{}
    {
    if(r.value_ != nullptr)
      value_ = new int(*r.value_);
    }

  constexpr non_trivial_ptr & operator=(non_trivial_ptr && r) noexcept
    {
    if(value_ != nullptr)
      delete value_;

    value_ = std::exchange(r.value_, nullptr);
    return *this;
    }

  constexpr non_trivial_ptr & operator=(non_trivial_ptr const & r) noexcept
    {
    if(value_ != nullptr)
      {
      delete value_;
      value_ = nullptr;
      }
    if(r.value_ != nullptr)
      value_ = new int(*r.value_);
    return *this;
    }

  constexpr non_trivial_ptr & operator++() noexcept
    {
    assert(value_ != nullptr);
    ++*value_;
    return *this;
    }

  constexpr ~non_trivial_ptr()
    {
    if(value_ != nullptr)
      delete value_;
    }

  constexpr bool operator==(non_trivial_ptr const & r) const noexcept
    {
    if(value_ != nullptr && r.value_ != nullptr)
      return *value_ == *r.value_;

    return value_ == nullptr && r.value_ == nullptr;
    }

  constexpr bool operator==(int r) const noexcept
    {
    if(value_ != nullptr)
      return *value_ == r;
    return false;
    }

  constexpr int value() const noexcept { return *value_; }

  constexpr void swap(non_trivial_ptr & r) noexcept { std::swap(value_, r.value_); }
  };

struct non_trivial_ptr_except
  {
  non_trivial_ptr obj;
  constexpr non_trivial_ptr_except() noexcept(false) = default;

  constexpr non_trivial_ptr_except(int value) noexcept(false) : obj{value} {}

  constexpr non_trivial_ptr_except(non_trivial_ptr_except && r) noexcept(false) = default;
  constexpr non_trivial_ptr_except(non_trivial_ptr_except const & r) noexcept(false) = default;
  constexpr non_trivial_ptr_except & operator=(non_trivial_ptr_except && r) noexcept(false) = default;
  constexpr non_trivial_ptr_except & operator=(non_trivial_ptr_except const & r) noexcept(false) = default;
  constexpr ~non_trivial_ptr_except() = default;

  constexpr non_trivial_ptr_except & operator++() noexcept
    {
    ++obj;
    return *this;
    }

  constexpr bool operator==(non_trivial_ptr_except const &) const noexcept = default;

  constexpr int value() const noexcept(false) { return obj.value(); }

  constexpr void swap(non_trivial_ptr_except & r) { std::swap(obj, r.obj); }
  };

struct non_trivial_ptr_except_copy
  {
  non_trivial_ptr obj;
  constexpr non_trivial_ptr_except_copy() noexcept(false) = default;

  constexpr non_trivial_ptr_except_copy(int value) noexcept(false) : obj{value} {}

  constexpr non_trivial_ptr_except_copy(non_trivial_ptr_except_copy const & r) noexcept(false) = default;
  constexpr non_trivial_ptr_except_copy & operator=(non_trivial_ptr_except_copy const & r) noexcept(false) = default;
  constexpr ~non_trivial_ptr_except_copy() = default;

  constexpr non_trivial_ptr_except_copy & operator++() noexcept
    {
    ++obj;
    return *this;
    }

  constexpr bool operator==(non_trivial_ptr_except_copy const &) const noexcept = default;
  };

// for testing strong exception guarantee
template<typename Super, int throw_at_value>
struct non_trivial_throwing_tmpl : public Super
  {
  using super_type = Super;
  constexpr non_trivial_throwing_tmpl() noexcept(std::is_nothrow_default_constructible_v<super_type>) = default;

  constexpr non_trivial_throwing_tmpl(int value) noexcept(std::is_nothrow_constructible_v<super_type, int>) :
      super_type{value}
    {
    }

  constexpr non_trivial_throwing_tmpl(non_trivial_throwing_tmpl const & r) : super_type{r}
    {
    if constexpr(not noexcept(super_type{r}))
      if(operator==(throw_at_value))
        throw std::runtime_error{""};
    }

  constexpr non_trivial_throwing_tmpl(non_trivial_throwing_tmpl && r) noexcept(noexcept(super_type{std::move(r)})) :
      super_type{std::move(r)}
    {
    if constexpr(not noexcept(super_type{std::move(r)}))
      if(operator==(throw_at_value))
        throw std::runtime_error{""};
    }

  using super_type::operator==;
  using super_type::operator++;

  void set_value(int value) { super_type::operator=(value); }

  constexpr non_trivial_throwing_tmpl & operator=(non_trivial_throwing_tmpl const & r)
    {
    super_type::operator=(r);
    if constexpr(not noexcept(super_type::operator=(r)))
      if(operator==(throw_at_value))
        throw std::runtime_error{""};
    return *this;
    }

  constexpr non_trivial_throwing_tmpl & operator=(non_trivial_throwing_tmpl && r
  ) noexcept(noexcept(super_type::operator=(std::move(r))))
    {
    super_type::operator=(r);
    if constexpr(not noexcept(super_type::operator=(std::move(r))))
      if(operator==(throw_at_value))
        throw std::runtime_error{""};
    return *this;
    }

  constexpr ~non_trivial_throwing_tmpl() = default;
  };

template<int throw_at_value>
using non_trivial_throwing = non_trivial_throwing_tmpl<non_trivial_ptr_except, throw_at_value>;

template<int throw_at_value>
using non_trivial_throwing_copy = non_trivial_throwing_tmpl<non_trivial_ptr_except_copy, throw_at_value>;

std::ostream & operator<<(std::ostream & stream, non_trivial_ptr const & v);
std::ostream & operator<<(std::ostream & stream, non_trivial_ptr_except const & v);
std::ostream & operator<<(std::ostream & stream, non_trivial_ptr_except_copy const & v);
