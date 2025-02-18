#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
 auto I = kyosu::complex(0.0, 1.0);
  std::cout << "tricomi(2.0, 1, 1.5)         "<< kyosu::tricomi(2.0, 1, 1.5)        << std::endl;
  std::cout << "tricomi(2.0, 1, I)           "<< kyosu::tricomi(2.0, 1, I)          << std::endl;
  return 0;
}
