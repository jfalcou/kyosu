#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  eve::wide re = {2.0, -4.0, -10.0, 0.0};
  eve::wide im = {0.0, -1.0, 0.0, 5.0};
  auto c =  kyosu::complex(re, im);
  auto belongs =  [](auto v) {return kyosu::abs(v) > 8.0 || v == 2.0; };

  std::cout << " <- c                              = " << c << '\n';
  std::cout << " -> chi(c, belongs)                = " << kyosu::chi(c, belongs) << '\n';
  std::cout << " -> chi[real(c) > -2](c, belongs)  = " << kyosu::chi[kyosu::real(c) > -2](c, belongs) << '\n';
}
