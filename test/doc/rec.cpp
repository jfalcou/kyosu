#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>
#include <complex>

int main()
{
  using kyosu::complex_t;
  using kyosu::quaternion_t;
  using kyosu::rec;

  std::cout << "Real:        ";
  std::cout << 72.9f << " -> " << rec(72.9f) << "\n";

  std::cout << "Complex:     ";
  std::cout << kyosu::complex_t<float>(3.5f, -2.9f) << " -> " << rec(kyosu::complex_t<float>(3.5f, -2.9f)) << "\n";

  std::cout << "Quaternion:  ";
  std::cout << kyosu::quaternion_t<double>(1., 2., 3., 4.) << " -> " << rec(kyosu::quaternion_t<double>(1., 2., 3., 4.))
            << "\n";

  std::cout << "SIMD:        ";
  using wc_t = eve::wide<kyosu::complex_t<double>, eve::fixed<2>>;
  std::cout << wc_t(kyosu::complex_t<double>(1.3, -3.7)) << " -> " << rec(wc_t(kyosu::complex_t<double>(1.3, -3.7)))
            << "\n";


  std::cout << "kyosu::complex(3.0, 0.0)        "<< kyosu::complex(3.0, 0.0) << "\n";
  std::cout << "rec(kyosu::complex(3.0, 0.0))   "<<rec(kyosu::complex(3.0, 0.0)) << "\n";
  std::cout << "rec(kyosu::complex(-3.0, 0.0))  "<< rec(kyosu::complex(-3.0, 0.0)) << "\n";
  std::cout << "rec[kyosu::pedantic](kyosu::complex(3.0, 0.0))   "<<rec(kyosu::complex[kyosu::pedantic](3.0, 0.0)) << "\n";
  std::cout << "rec[kyosu::pedantic](kyosu::complex(-3.0, 0.0))  "<< rec(kyosu::complex[kyosu::pedantic](-3.0, 0.0)) << "\n";

  std::cout << "kyosu::complex(3.0, -0.0)       "<< kyosu::complex(3.0, -0.0) << "\n";
  std::cout << "rec(kyosu::complex(3.0, -0.0))  "<<rec(kyosu::complex(3.0, -0.0)) << "\n";
  std::cout << "rec(kyosu::complex(-3.0, -0.0)) "<< rec(kyosu::complex(-3.0, -0.0)) << "\n";
  std::cout << "rec[kyosu::pedantic](kyosu::complex(3.0, -0.0))  "<<rec(kyosu::complex(3.0, -0.0)) << "\n";
  std::cout << "rec[kyosu::pedantic](kyosu::complex(-3.0, -0.0)) "<< rec(kyosu::complex(-3.0, -0.0)) << "\n";


  std::cout << "1.0/(std::complex<double>(3.0, 0.0))     "     << 1.0/(std::complex<double>(3.0, 0.0))     << "\n";
  std::cout << "1.0/(std::complex<double>(-3.0, 0.0))    "    << 1.0/(std::complex<double>(-3.0, 0.0))    << "\n"<< "\n";;

  std::cout << "1.0/(std::complex<double>(0.0, 0.0))     "     << 1.0/(std::complex<double>(0.0, 0.0))     << "\n";
  std::cout << "1.0/(std::complex<double>(-0.0, 0.0))    "    << 1.0/(std::complex<double>(-0.0, 0.0))    << "\n";
  std::cout << "1.0/(std::complex<double>(0.0, -0.0))    "    << 1.0/(std::complex<double>(0.0, -0.0))    << "\n";
  std::cout << "1.0/(std::complex<double>(-0.0, 0.0))    "    << 1.0/(std::complex<double>(-0.0, 0.0))    << "\n";

  std::cout << "rec(kyosu::complex_t<double>(0.0, 0.0))  "  << rec(kyosu::complex_t<double>(0.0, 0.0))  << "\n";
  std::cout << "rec(kyosu::complex_t<double>(-0.0, 0.0)) " << rec(kyosu::complex_t<double>(-0.0, 0.0)) << "\n";
  std::cout << "rec(kyosu::complex_t<double>(0.0, -0.0)) " << rec(kyosu::complex_t<double>(0.0, -0.0)) << "\n";
  std::cout << "rec(kyosu::complex_t<double>(-0.0, 0.0)) " << rec(kyosu::complex_t<double>(-0.0, 0.0)) << "\n";
  return 0;
}
