#ifndef MIDPOINT_H
#define MIDPOINT_H 1

namespace std
{

  template<typename _Float>
    std::enable_if_t<_Float, std::is_floating_point_v<_Float>>
    lerp(_Float __a, _Float __b, _Float __t)
    {
      if (std::isnan(__a) || std::isnan(__b) || std::isnan(__t))
	return std::numeric_limits<_Float>::quiet_NaN();
      else if (__a <= 0 && __b >= 0 || __a >= 0 && __b <= 0)
	// ab <= 0 but product could overflow.
	return __t * __b + (1 - __t) * __a;
      else if (__t == _Float{1})
	return __b;
      else
	{ // monotonic near t == 1.
	  const auto __x = __a + __t * (__b - __a);
	  return __t > _Float{1} == __b > __a
		 ? std::max(__b, __x)
		 : std::min(__b,__x);
	}
    }

}

#endif // MIDPOINT_H
