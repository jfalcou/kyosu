#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  auto z = kyosu::complex(eve::wide<double>(1.0, 0.0));
  auto m = eve::wide<double>(1.0);
  auto diff = kyosu::is_not_equal(z, m);
  std::cout << "z " << z << std::endl;
  std::cout << "m " << m << std::endl;
  std::cout << diff << std::endl;
  return 0;
}
