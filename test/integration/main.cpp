#include <kyosu/kyosu.hpp>
#include <iostream>

int main()
{
  std::cout << kyosu::complex(3.4f,6.7f) << "\n";
  std::cout << kyosu::quaternion(float>{2,5,8,0.1) << "\n";
}
