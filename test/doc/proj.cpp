#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::proj;
  using kyosu::complex;
  using kyosu::quaternion;
  auto inf = eve::inf(eve::as<float>());

  std::cout << "Real:        \n";
  std::cout << "    " <<  72.9f << " -> " << proj(72.9f) << "\n";
  std::cout << "    " <<  inf   << " -> " << proj(inf) << "\n";
  std::cout << "    " <<  -inf  << " -> " << proj(-inf) << "\n";

  std::cout << "Complex:     \n";
  std::cout << "    " << complex<float>(3.5f,-2.9f) << " -> " << proj(complex<float>(3.5f,-2.9f)) << "\n";
  std::cout << "    " <<  complex<float>(3.5f,inf)   << " -> " << proj(complex<float>(3.5f,inf)) << "\n";
  std::cout << "    " <<  complex<float>(3.5f,-inf) << " -> " << proj(complex<float>(3.5f,-inf)) << "\n";
  std::cout << "    " <<  complex<float>(inf,-2.9f) << " ->  " << proj(complex<float>(inf,-2.9f)) << "\n";
  std::cout << "    " <<  complex<float>(inf, 2.9f) << " ->  " << proj(complex<float>(inf,2.9f)) << "\n";

  std::cout << "Quaternion:  \n";
  std::cout << "    " <<  quaternion<double>(1.f,2.f,3.f,4.f) << " -> " << proj(quaternion<double>(1.f,2.f,3.f,4.f)) << "\n";
  std::cout << "    " <<  quaternion<double>(-1.f,inf,3.f,-4.f) << " -> " << proj(quaternion<double>(-1.f,inf,3.f,-4.f)) << "\n";

  using T =  eve::wide < float, eve::fixed < 2 > >;
  using c_t = kyosu::as_quaternion_t<T>;
  auto g = c_t(32, 44, 55, 34);
  std::cout << g << std::endl;
  return 0;
}
