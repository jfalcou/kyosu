#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include </home/jt/falcoudev/kyosu/kyosu/include/kyosu/types/impl/detail/bessel_jyr01.hpp>

auto f = [](auto n, auto z){
  using kyosu::cyl_bessel_jnu;
  using kyosu::cyl_bessel_ynu;
  std::cout.precision(4);
  std::cout << std::scientific << std::endl;
  std::cout << "n " << n << " z " << z  << "\n";
  std::cout.precision(16);
  std::cout << std::scientific << std::endl;
  auto [jv0, yv0, jv1, yv1] = kyosu::_::cb_jyr01(n, z);
  std::cout << "jv0 " << jv0 << "\n";
  std::cout << "jv1 " << jv1 << "\n";
  std::cout << "yv0 " << yv0 << "\n";
  std::cout << "yv1 " << yv1 << "\n";
  std::cout << std::endl;
};

int main()
{
//   double n = 0.2;
//   auto z = kyosu::complex(1.0e-110, 1.0e-110);
//   f(n, z);
  {
    double n = 0.2;
    auto z = kyosu::complex(2.0, 3.0);
    f(n, z);
  }
//   n = 0.2;
//   z = kyosu::complex(-2.0, 3.0);
//   f(n, z);
//   n = 0.2;
//   z = kyosu::complex(20.0, 3.0);
//   f(n, z);
//   n = 0.2;
//   z = kyosu::complex(-20.0, 3.0);
//   f(n, z);
//   using w_t = eve::wide<double, eve::fixed<4>>;
//   auto wz = kyosu::complex(w_t(2.0, -2.0, 20.0, -20.0), w_t(3.0));
//   f(n, wz);

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
