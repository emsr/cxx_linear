/*
/home/ed/bin/bin/g++ -std=c++20 -o test_midpoint_new test_midpoint_new.cpp
LD_LIBRARY_PATH=/home/ed/bin/lib64 ./test_midpoint_new
*/

#include <cmath>
#include <numeric>
#include <iostream>
#include <limits>
#include <cstdint>
#include <type_traits>

/// @see https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p0811r3.html

namespace phlegm
{

  /**
   * Computing the (integer) midpoint of two integer values via
   *  (a+b)/2
   * can cause overflow for signed or unsigned integers as well
   * as for floating-point values.
   */
  template<typename Int>
    constexpr std::enable_if_t<std::is_integral_v<Int>
			   && !std::is_same_v<Int, bool>, Int>
    midpoint(Int a, Int b) noexcept
    {
      using UInt = std::make_unsigned_t<Int>;
      return a > b
		? a - Int(UInt(a) - UInt(b) / 2)
		: a + Int(UInt(b) - UInt(a) / 2);
    }

  /**
   * Computing the (integer) midpoint of two float values via
   *  (a+b)/2
   * can cause overflow.
   * The choice
   *   a + (b - a)/2
   * is not correctly rounded (by rounding in the subtraction and the addition).
   * A third choice
   *   a/2 + b/2
   * prevents overflow but is not correctly rounded for subnormal inputs
   * (due to rounding each separately).
   *
   * What about infinity?
   */
  template<typename Float>
    constexpr std::enable_if_t<std::is_floating_point_v<Float>, Float>
    midpoint(Float a, Float b) noexcept
    {
      constexpr auto max = std::numeric_limits<Float>::max() / 2;
      if (std::isnan(a) || std::isnan(b))
	return std::numeric_limits<Float>::quiet_NaN();
      else if (std::abs(a) < max && std::abs(b) < max)
        return (a + b) / 2;
      else
	return a / 2 + b / 2;
    }

 /**
  * Midpoint between two pointers.
  *
  * As with integers, when the midpoint lies between two pointer values
  * the one closer to a is chosen; for the usual case of a<b,
  * this is compatible with the usual half-open ranges by selecting
  * a when [a,b) is [a,a+1).
  */
  template<typename Tp>
    constexpr std::enable_if_t<std::is_object_v<Tp>, Tp*>
    midpoint(Tp* a, Tp* b)
    {
      return a + (b - a) / 2;
    }

} // namespace phlegm

int
main()
{
  auto d = std::numeric_limits<double>::max_digits10;
  std::cout.precision(d);
  const double K = 4.4501477170144023e-308;
  double X[] = {
      K, phlegm::midpoint(K, K)
  };
  bool nK = std::isnormal(K);
  bool mK = std::isnormal(phlegm::midpoint(K, K));
  std::cout << ' ' << X[0] << ' ' << X[1] << '\n';
  auto pK = phlegm::midpoint(K, K);
  auto dnorm = std::numeric_limits<double>::denorm_min();
  std::cout << ' ' << dnorm << '\n';
  auto deps = std::numeric_limits<double>::epsilon();
  std::cout << ' ' << deps << '\n';
  auto diff = X[0] - X[1];
  std::cout << ' ' << diff << '\n';
  auto min = std::numeric_limits<double>::min();
  std::cout << ' ' << min << '\n';
  std::cout << ' ' << min/2 << '\n';
}

/*
phlegm::midpoint<double> (a=4.4501477170144023e-308, b=4.4501477170144023e-308) at test_midpoint.cpp:35
35	      if (std::isnan(a) || std::isnan(b))
(gdb) n
38		return std::isnormal(a) && std::isnormal(b)
(gdb) 
39			? a / 2 + b / 2
(gdb) 
38		return std::isnormal(a) && std::isnormal(b)
(gdb) p std::isnormal(a)
$1 = true
(gdb) p std::isnormal(b)
$2 = true
(gdb) p a / 2
$3 = 2.2250738585072014e-308
(gdb) p b / 2
$4 = 2.2250738585072014e-308
(gdb) p a / 2 + b / 2
$5 = 4.4501477170144028e-308
(gdb) p (a+b)/2
$6 = 4.4501477170144023e-308
(gdb) p a
$7 = 4.4501477170144023e-308
(gdb) 

(gdb) p pK
$8 = 4.4501477170144028e-308

(gdb) p K/2+K/2
$13 = 4.4501477170144028e-308
(gdb) p (K+K)/2
$14 = 4.4501477170144023e-308
*/
