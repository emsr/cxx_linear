/*
/home/ed/bin/bin/g++ -std=c++17 -o test_lerp test_lerp.cpp
*/

#include <limits>
#include <type_traits>

#include "lerp.h"

#include <iostream>

template<typename Real>
  bool
  test_ends()
  {
    const auto a = Real{-3};
    const auto b = Real{+5};
    const auto t = Real{3} / Real{4};
    auto ca = std::lerp(a, b, Real{0});
    std::cout << "ca = " << ca << '\n';
    std::cout << std::boolalpha << "ca == a: " << (ca == a) << '\n';
    auto cb = std::lerp(a, b, Real{1});
    std::cout << "cb = " << cb << '\n';
    std::cout << std::boolalpha << "cb == b: " << (cb == b) << '\n';
    return ca == a && cb == b;
  }

template<typename Real>
  bool
  test_huge()
  {
    const auto a = -std::numeric_limits<Real>::max();
    const auto b = +std::numeric_limits<Real>::max();
    const auto t = Real{3} / Real{4};
    auto c = std::lerp(a, b, t);
    std::cout << "c = " << c << '\n';
    std::cout << std::boolalpha << "c == b/2: " << (c == b / Real{2}) << '\n';
    return c == b / Real{2};
  }

template<typename Real>
  bool
  test_inf()
  {
    const auto a = Real{5};
    const auto b = a;
    const auto t = std::numeric_limits<Real>::infinity();
    auto c = std::lerp(a, b, t);
    std::cout << "c = " << c << '\n';
    std::cout << std::boolalpha << "c == a: " << (c == a) << '\n';
    return c == a;
  }

int
main()
{
  bool ok = true;

  ok = ok && test_ends<float>();
  ok = ok && test_ends<double>();
  ok = ok && test_ends<long double>();

  ok = ok && test_huge<float>();
  ok = ok && test_huge<double>();
  ok = ok && test_huge<long double>();

  ok = ok && test_inf<float>();
  ok = ok && test_inf<double>();
  ok = ok && test_inf<long double>();

  return ok;
}
