#include <fixedmath/fixed_math.hpp>
#include <fixedmath/unittests/compile_time_unit_tests.h>
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <string_view>

using fixedmath::fixed_t;
using fixedmath::make_fixed;
using std::cout;
using std::endl;
using std::chrono::duration_cast;
using std::chrono::steady_clock;
using std::chrono::microseconds;
using std::chrono::milliseconds;
using fixedmath::sin;
using std::sin;
using fixedmath::asin;
using std::asin;
using fixedmath::tan;
using std::tan;
using fixedmath::atan;
using std::atan;
using std::string_view;
using fixedmath::phi;

using limits__ = std::numeric_limits<fixedmath::fixed_t>;

struct tuple_type 
  {
  fixed_t fx; float f; double d;
  };
  
constexpr auto perf( steady_clock::time_point start, steady_clock::time_point end ) { return duration_cast<milliseconds>(end - start).count(); }

template<typename test_type, typename test_function>
auto test( std::vector<test_type> data_fx, test_function fnobj )
  {
  size_t test_size { data_fx.size() };
  std::vector<test_type> out_data_fx;
  out_data_fx.resize( test_size );
  auto start = steady_clock::now();
  std::transform( data_fx.begin(), data_fx.end(), out_data_fx.begin(), fnobj );
  auto end = steady_clock::now();
  return perf(start,end);
  }

template<typename test_function>
struct test_executor
  {
  void operator()( string_view info )
    {
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 256);
    size_t test_size { 10000000 };

    std::vector<fixed_t> data_fx; std::vector<float> data_f; std::vector<double> data_d;
    data_fx.reserve( test_size );data_f.reserve( test_size );data_d.reserve( test_size );

    for(size_t n=0; n<test_size; ++n)
      {
      int value {  distrib(gen) };
      data_fx.emplace_back( phi/4*value/256 );
      data_f.emplace_back( static_cast<float>(phi/4*value/256) );
      data_d.emplace_back( static_cast<double>(phi/4*value/256) );
      }


    auto float_perf { test(data_f, test_function{} ) };
    auto double_perf { test(data_d, test_function{} ) };
    auto fix_perf { test(data_fx, test_function{} ) };

    cout << info << " fixed:"<< fix_perf << "ms float:" << float_perf << " ms double:" << double_perf << " ms"<< endl;

    }
  };
  
struct sin_test{
  template<typename value_type>
  auto operator()(value_type const & tp){ return sin(tp); } 
};
struct asin_test{
  template<typename value_type>
  auto operator()(value_type const & tp){ return asin(tp); } 
};
struct tan_test{
  template<typename value_type>
  auto operator()(value_type const & tp){ return tan(tp); } 
};
struct atan_test{
  template<typename value_type>
  auto operator()(value_type const & tp){ return atan(tp); } 
};
int main(int argc, char **argv) 
{
test_executor<sin_test>{}("sin");
test_executor<asin_test>{}("asin");
test_executor<tan_test>{}("tan");
test_executor<atan_test>{}("atan");
return EXIT_SUCCESS;
}

