#ifndef MIDPOINT_H
#define MIDPOINT_H 1

#include <cmath>

namespace std
{

  template<typename _Int>
    constexpr std::enable_if_t<std::is_integral_v<_Int>
			   && !std::is_same_v<_Int, bool>, _Int>
    midpoint(_Int __a, _Int __b) noexcept
    {
      using _UInt = std::make_unsigned_t<_Int>;
      return _Int(_UInt(__a) + (_UInt(__b) - _UInt(__a)) / 2);
    }

  // What about infinity?
  template<typename _Float>
    constexpr std::enable_if_t<std::is_floating_point_v<_Float>, _Float>
    midpoint(_Float __a, _Float __b) noexcept
    {
      if (std::isnan(__a) || std::isnan(__b))
	return std::numeric_limits<_Float>::quiet_NaN();
      else
	return std::isnormal(__a) && std::isnormal(__b)
		? __a / 2 + __b / 2
		: (__a + __b) / 2;
    }

  template<typename _Tp>
    _Tp*
    midpoint(_Tp* __a, _Tp* __b)
    { return static_cast<_Tp*>(std::midpoint(intptr_t(__a), intptr_t(__b))); }

} // namespace std

#endif // MIDPOINT_H
