#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::as_complex_t;
  using kyosu::as_quaternion_t;


  auto c = kyosu::as_complex_t<float>(3.5f,-2.9f);
  auto q =  kyosu::as_quaternion_t<float>(1.f,2.f,3.f,4.f);
  auto t = 1.0f;
  auto r = kyosu::if_else(t > 2.0f, q, c);
  std::cout << r << std::endl;

  return 0;
}
