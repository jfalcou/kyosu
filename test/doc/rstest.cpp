#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <boost/math/tools/fraction.hpp>

int main()
{
  std::cout.precision(16);
  using w_t = eve::wide<double, eve::fixed<2>>;
//  auto z = kyosu::complex(1.0, 3.5);
  auto z = kyosu::complex(w_t(20.0, 1.0), w_t(0.0, 5.0));
//  auto z = kyosu::complex(1.0, 3.5);
  auto rs = kyosu::_::Rs(10, z);
  for(int n=1; n < 10; ++n)
  {
    auto rn = kyosu::_::R(n, z);
    std::cout << "n " << n << " R(n, z) " << rn << " == " << rs[n-1] << std::endl;
  }

  return 0;
}
