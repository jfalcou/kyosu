#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::rot_axis;
  using kyosu::complex_t;
  using kyosu::quaternion_t;

  std::cout << "Real:        ";
  auto v = rot_axis(kyosu::complex_t<float>(3.5f,-2.9f));
  std::cout << 72.9f << " -> (" << v[0] << ", " << v[1] << ",  " << v[2] << ")\n";

  std::cout << "Complex:     ";
  auto vc = rot_axis(kyosu::complex_t<float>(3.5f,-2.9f));
  std::cout << kyosu::complex_t<float>(3.5f,-2.9f) << " -> (" << vc[0] << ", " << vc[1] << ",  " << vc[2] << ")\n";

  std::cout << "Quaternion:  ";
  auto vq = rot_axis(kyosu::quaternion_t<double>(1.,2.,3.,4.));
  std::cout << kyosu::quaternion_t<double>(1.,2.,3.,4.) << " -> " << vq[0] << ", " << vq[1] << ",  " << vq[2] << ")\n";

  return 0;
}
