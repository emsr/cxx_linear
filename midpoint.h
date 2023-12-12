#ifndef MIDPOINT_H
#define MIDPOINT_H 1

#include <cmath>
#include <cstdint>

namespace std
{

  /**
   * Computing the (integer) midpoint of two integer values via
   *  (a+b)/2
   * can cause overflow for signed or unsigned integers as well
   * as for floating-point values.
   */
  template<typename _Int>
    constexpr std::enable_if_t<std::is_integral_v<_Int>
			   && !std::is_same_v<_Int, bool>, _Int>
    midpoint(_Int __a, _Int __b) noexcept
    {
      using _UInt = std::make_unsigned_t<_Int>;
      return __a > __b
		? __a - _Int(_UInt(__a) - _UInt(__b) / 2)
		: __a + _Int(_UInt(__b) - _UInt(__a) / 2);
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
  template<typename _Float>
    constexpr std::enable_if_t<std::is_floating_point_v<_Float>, _Float>
    midpoint(_Float __a, _Float __b) noexcept
    {
      constexpr auto __max = std::numeric_limits<_Float>::max() / 2;
      if (std::isnan(__a) || std::isnan(__b))
	return std::numeric_limits<_Float>::quiet_NaN();
      else if (std::abs(__a) < __max && std::abs(__b) < __max)
        return (__a + __b) / 2;
      else
	return __a / 2 + __b / 2;
    }

 /**
  * Midpoint between two pointers.
  *
  * As with integers, when the midpoint lies between two pointer values
  * the one closer to a is chosen; for the usual case of a<b,
  * this is compatible with the usual half-open ranges by selecting
  * a when [a,b) is [a,a+1).
  */
  template<typename _Tp>
    _Tp*
    midpoint(_Tp* __a, _Tp* __b)
    {
      return __a + (__b - __a) / 2;
    }

} // namespace std

#endif // MIDPOINT_H
