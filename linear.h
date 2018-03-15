#ifndef LINEAR_H
#define LINEAR_H 1

namespace std
{

  template<typename _Int>
    _Int
    midpoint(_Int __a, _Int __b)
    {
      using _UInt = std::make_unsigned_t<_Int>;
      return _Int(_UInt(__a) + (_UInt(__b) - _UInt(__a)) / 2);
    }

  template<typename _Tp>
    _Tp*
    midpoint(_Tp* __a, _Tp* __b)
    { return static_cast<_Tp*>(midpoint(intptr_t(__a), intptr_t(__b))); }

// What about infinity?
  template<typename _Float>
    Float
    midpoint(_Float __a, _Float __b)
    {
      if (std::isnan(__a) || std::isnan(__b))
	return std::numeric_limits<_Float>::quiet_NaN();
      else
	return std::isnormal(__a) && std::isnormal(__b)
		? __a / 2 + __b / 2
		: (__a + __b) / 2;
    }

}

#endif // LINEAR_H
