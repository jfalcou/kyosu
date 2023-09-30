#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  using kyosu::convert;
  using kyosu::complex_t;
  using kyosu::quaternion_t;

  double f =  72.987654321;
  std::cout << "Real to complex of floats:      ";
  std::cout << std::setprecision(10) << f << " -> " << convert(f, eve::as<complex_t<float>>()) << "\n";
  std::cout << "Real to quaternion of double:   " ;
  std::cout << f << " -> " << convert(f, eve::as<quaternion_t<double>>()) << "\n";

  std::cout << "Complex to quaternion ofdouble: ";
  auto c = kyosu::complex(3.5f,-2.9f);
  std::cout << c << " -> " << convert(c, eve::as<quaternion_t<double>>()) << "\n";

  return 0;
}
