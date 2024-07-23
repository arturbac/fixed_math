#include <fixedmath/fixed_math.hpp>
// #include <fixedmath/unittests/compile_time_unit_tests.h>
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <string_view>
using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::milliseconds;
using std::chrono::steady_clock;
using std::cout;
using std::endl;

using std::string_view;
namespace fixedmath::inline v2
  {
// using std::asin;
// using std::atan;

// using std::tan;
// using std::sin;
using limits_ = std::numeric_limits<fixedmath::fixed_t>;

struct tuple_type
  {
  fixed_t fx;
  float f;
  double d;
  };

constexpr auto perf(steady_clock::time_point start, steady_clock::time_point end)
  {
  return duration_cast<milliseconds>(end - start).count();
  }

template<typename test_type, typename test_function>
auto test(std::vector<test_type> data_fx, test_function fnobj)
  {
  size_t test_size{data_fx.size()};
  std::vector<test_type> out_data_fx;
  out_data_fx.resize(test_size);
  auto start = steady_clock::now();
  std::transform(data_fx.begin(), data_fx.end(), out_data_fx.begin(), fnobj);
  auto end = steady_clock::now();
  return perf(start, end);
  }

template<typename test_function>
struct test_executor
  {
  int64_t operator()(string_view info)
    {
    std::random_device rd;   // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd());  // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 256);
    size_t test_size{10000000};

    std::vector<fixed_t> data_fx;
    std::vector<float> data_f;
    std::vector<double> data_d;
    data_fx.reserve(test_size);
    data_f.reserve(test_size);
    data_d.reserve(test_size);

    for(size_t n = 0; n < test_size; ++n)
      {
      int value{distrib(gen)};
      data_fx.emplace_back(phi / 4 * value / 256);
      data_f.emplace_back(static_cast<float>(phi / 4 * value / 256));
      data_d.emplace_back(static_cast<double>(phi / 4 * value / 256));
      }

    auto float_perf{test(data_f, test_function{})};
    auto double_perf{test(data_d, test_function{})};
    auto fix_perf{test(data_fx, test_function{})};

    int64_t noop{static_cast<int64_t>(std::accumulate(data_fx.begin(), data_fx.end(), fixed_t{}))};
    noop += static_cast<int64_t>(std::accumulate(data_f.begin(), data_f.end(), float{}));
    noop += static_cast<int64_t>(std::accumulate(data_d.begin(), data_d.end(), double{}));

    cout << info << " fixed:" << fix_perf << "ms float:" << float_perf << " ms double:" << double_perf << " ms ";
    return noop;
    }
  };

struct sin_test
  {
  template<typename value_type>
  auto operator()(value_type const & tp)
    {
    return sin(tp);
    }
  };

struct asin_test
  {
  template<typename value_type>
  auto operator()(value_type const & tp)
    {
    return asin(tp);
    }
  };

struct tan_test
  {
  template<typename value_type>
  auto operator()(value_type const & tp)
    {
    return tan(tp);
    }
  };

struct atan_test
  {
  template<typename value_type>
  auto operator()(value_type const & tp)
    {
    return atan(tp);
    }
  };

struct sqrt_test
  {
  template<typename value_type>
  auto operator()(value_type const & tp)
    {
    return sqrt(tp);
    }
  };

struct arith_test
  {
  template<typename value_type>
  auto operator()(value_type const & tp)
    {
    return (1 + tp * tp) / (1 - tp);
    }
  };

struct add_test
  {
  template<typename value_type>
  auto operator()(value_type const & tp)
    {
    return tp + tp;
    }
  };

struct mul_test
  {
  template<typename value_type>
  auto operator()(value_type const & tp)
    {
    return tp * tp;
    }
  };

struct div_test
  {
  template<typename value_type>
  auto operator()(value_type const & tp)
    {
    return tp / tp;
    }
  };
  }  // namespace fixedmath

int main(int argc, char ** argv)
  {
  cout << fixedmath::test_executor<fixedmath::sin_test>{}("sin") << endl;
  cout << fixedmath::test_executor<fixedmath::asin_test>{}("asin") << endl;
  cout << fixedmath::test_executor<fixedmath::tan_test>{}("tan") << endl;
  cout << fixedmath::test_executor<fixedmath::atan_test>{}("atan") << endl;
  cout << fixedmath::test_executor<fixedmath::sqrt_test>{}("sqrt") << endl;
  cout << fixedmath::test_executor<fixedmath::arith_test>{}("arith_test") << endl;
  cout << fixedmath::test_executor<fixedmath::add_test>{}("add") << endl;
  cout << fixedmath::test_executor<fixedmath::mul_test>{}("mul") << endl;
  cout << fixedmath::test_executor<fixedmath::div_test>{}("div") << endl;
  return EXIT_SUCCESS;
  }

