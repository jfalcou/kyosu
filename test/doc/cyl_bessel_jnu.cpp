#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::cyl_bessel_jnu;
  std::cout.precision(16);
  std::cout << std::scientific << std::endl;
  double_t n = 0.2;
  auto z = kyosu::complex(1.0e-110, 1.0e-110);
  std::cout << "n " << n << " z " << z  << " -> " << cyl_bessel_jnu(n, z)<< "\n";
  n = 1.2;
  std::cout << "n " << n << " z " << z  << " -> " << cyl_bessel_jnu(n, z)<< "\n";
  n = 2.2;
  std::cout << "n " << n << " z " << z  << " -> " << cyl_bessel_jnu(n, z)<< "\n";
  z = kyosu::complex(15.0, 1.0);
  n = 1.2;
  std::cout << "n " << n << " z " << z  << " -> " << cyl_bessel_jnu(n, z)<< "\n";
  n = 0.2;
  std::cout << "n " << n << " z " << z  << " -> " << cyl_bessel_jnu(n, z)<< "\n";
  n = 2.2;
  std::cout << "n " << n << " z " << z  << " -> " << cyl_bessel_jnu(n, z)<< "\n";
  n = 3.2;
  std::cout << "n " << n << " z " << z  << " -> " << cyl_bessel_jnu(n, z)<< "\n";
  n = 30.2;
  std::cout << "n " << n << " z " << z  << " -> " << cyl_bessel_jnu(n, z)<< "\n";

  return 0;
}
