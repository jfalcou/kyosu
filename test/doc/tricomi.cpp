#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  auto I = kyosu::complex(0.0, 1.0);
  std::cout << "tricomi(2.0, 1, 1.5)         " << kyosu::tricomi(2.0, 1, 1.5) << std::endl;
  std::cout << "tricomi(2.0, 1, I)           " << kyosu::tricomi(2.0, 1, I) << std::endl;
  std::cout << "tricomi( 1.72725307941437, 0.0, 0.0)  " << kyosu::tricomi(1.72725307941437, 0.0, 0.0) << std::endl;
  std::cout << "tricomi( 1.72725307941437, 1.0, 1.0)  " << kyosu::tricomi(1.72725307941437, 1.0, 1.0) << std::endl;
  std::cout << "tricomi( 1.72725307941437, 2.0, 2.0)  " << kyosu::tricomi(1.72725307941437, 2.0, 2.0) << std::endl;
  std::cout << "tricomi( 1.72725307941437, 3.0, 3.0)  " << kyosu::tricomi(1.72725307941437, 3.0, 3.0) << std::endl;
  std::cout << "tricomi( 1.72725307941437+I, 0.0, 0.0)  " << kyosu::tricomi(1.72725307941437 + I, 0.0, 0.0)
            << std::endl;
  std::cout << "tricomi( 1.72725307941437+I, 1.0, 1.0)  " << kyosu::tricomi(1.72725307941437 + I, 1.0, 1.0)
            << std::endl;
  std::cout << "tricomi( 1.72725307941437+I, 2.0, 2.0)  " << kyosu::tricomi(1.72725307941437 + I, 2.0, 2.0)
            << std::endl;
  std::cout << "tricomi( 1.72725307941437+I, 3.0, 3.0)  " << kyosu::tricomi(1.72725307941437 + I, 3.0, 3.0)
            << std::endl;
  return 0;
}
