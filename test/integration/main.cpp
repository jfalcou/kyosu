#include <kyosu/kyosu.hpp>
#include <iostream;>

int main()
{
  std::cout << kyosu::complex<float>{3.4f,6.7f} << "\n";
  std::cout << kyosu::quaternion<float>{2,5,8,0.1} << "\n";
  std::cout << kyosu::octonion<float>{8,7,6,5,4,3,2,1} << "\n";
}
