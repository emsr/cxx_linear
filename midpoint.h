#ifndef MIDPOINT_H
#define MIDPOINT_H 1

namespace std
{

  template<typename _Float>
    linear(_Float __a, _Float __b, _Float __t)
    {
      if (std::isnan(__a) || std::isnan(__b) || std::isnan(__t))
	return std::numeric_limits<_Float>::quiet_NaN();
      else if (__a * __b <= 0)
	return __t * __b + (1 - __t) * __a;
      else if (__t == 1)
	return __b;
      else
	{
	  const auto __x = __a + __t * (__b - __a);
	  return __t > 1 == __b > __a
		 ? std::max(__b, __x)
		 : std::min(__b,__x);
	}
    }

}

#endif // MIDPOINT_H
