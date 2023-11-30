#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <vector>
#include </home/jt/falcoudev/kyosu/kyosu/include/kyosu/types/impl/detail/bessel_jyr01.hpp>

auto f = []<typename Z>(auto n, Z z){
  int np1 = int(n)+1;
  auto nf = eve::frac(n);
  std::vector<Z> cjv(np1), cyv(np1);
  std::cout.precision(4);
  std::cout << std::scientific << std::endl;
  std::cout << "n " << n << " z " << z  << "\n";
  std::cout.precision(16);
  std::cout << std::scientific;
  Z jv, yv;
  kumi::tie(jv, yv) = kyosu::_::cb_jyr(n, z, cjv, cyv);

  for(int i=0; i < np1 ; ++i)
  {
    std::cout << "cjv[" << nf+i << "] = " << cjv[i]  << "\n";
  }
  std::cout << "jvn " << jv  << "\n"<< "\n";

  for(int i=0; i < np1 ; ++i)
  {
    std::cout << "cyv[" << nf+i << "] = " << cyv[i]  << "\n";
  }
  std::cout << "yvn " << yv  << "\n";
  std::cout << std::endl;
};

int main()
{
//   {
//     double n = 0.2;
//     auto z = kyosu::complex(1.0e-110, 1.0e-110);
//     f(n, z);
//     n = 1.2;
//     z = kyosu::complex(1.0e-110, 1.0e-110);
//     f(n, z);
//   }
//   {
//     double n = 0.2;
//     auto z = kyosu::complex(2.0, 3.0);
//     f(n, z);
//     n = 1.2;
//     z = kyosu::complex(2.0, 3.0);
//     f(n, z);
//   }
//   {
//     double n = 0.2;
//     auto z = kyosu::complex(-2.0, 3.0);
//     f(n, z);
//     n = 1.2;
//     z = kyosu::complex(-2.0, 3.0);
//     f(n, z);
//   }
//   {
//     double n = 0.2;
//     auto z = kyosu::complex(-2.0, 3.0);
//     f(n, z);
//     n = 1.2;
//     z = kyosu::complex(-2.0, 3.0);
//     f(n, z);
//   }

  {
    double n = 10.2;
    auto z = kyosu::complex(-0.02, 0.5);
    f(n, z);
  }

//   n = 1.2;
//   std::cout << "n " << n << " z " << z  << " -> " << cyl_bessel_jnu(n, z)<< "\n";
//   n = 2.2;
//   std::cout << "n " << n << " z " << z  << " -> " << cyl_bessel_jnu(n, z)<< "\n";
//   z = kyosu::complex(15.0, 1.0);
//   n = 1.2;
//   std::cout << "n " << n << " z " << z  << " -> " << cyl_bessel_jnu(n, z)<< "\n";
//   n = 0.2;
//   std::cout << "n " << n << " z " << z  << " -> " << cyl_bessel_jnu(n, z)<< "\n";
//   n = 2.2;
//   std::cout << "n " << n << " z " << z  << " -> " << cyl_bessel_jnu(n, z)<< "\n";
//   n = 3.2;
//   std::cout << "n " << n << " z " << z  << " -> " << cyl_bessel_jnu(n, z)<< "\n";
//   n = 30.2;
//   std::cout << "n " << n << " z " << z  << " -> " << cyl_bessel_jnu(n, z)<< "\n";

  return 0;
}
