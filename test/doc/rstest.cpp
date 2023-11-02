#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>
//#include <boost/math/tools/fraction.hpp>

int main()
{
  std::cout.precision(16);
  size_t n = 10;
  auto z = kyosu::complex(1.0, 2.0);
  using c_t =  decltype(z);
  auto rs = kyosu::_::Rs(n, z);
  std::vector < c_t> rrs(n);
  for(size_t i=0; i < n; ++i)
  {
    rrs[i] = kyosu::_::R(i+1, z);
    std::cout << "rs    " << rs[i] << std::endl;
    std::cout << "rrs   " << rrs[i] << std::endl;
    std::cout << "j/jm1 " << kyosu::cyl_bessel_jn(i, z)/kyosu::cyl_bessel_jn(i+1, z)<< std::endl;
  }
  auto js = kyosu::_::Js(n, z);
  for(size_t i=1; i < n; ++i)
  {
    std::cout << i << " -> js      " << js[i] << std::endl;
    std::cout << i << " -> jn      " << kyosu::cyl_bessel_jn(i, z) << std::endl;
  }
//   std::vector<c_t > js(n+1);
//   for(size_t i=0; i < n+1; ++i)
//   {
//     js[i] = kyosu::cyl_bessel_jn(i, z);
//   }
//   for(size_t i=1; i < n; ++i)
//   {
//     std::cout << i << " -> rs      " << rs[i] << std::endl;
//    std::cout << i << " -> jsp1/rs " << js[i]/rs[i-1] << std::endl;
//     std::cout << i << " -> js      " << js[i]/js[i-1] << std::endl;
//   }

  return 0;
}
