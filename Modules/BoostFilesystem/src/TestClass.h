#pragma once
#ifndef _TestClass_h_
#define _TestClass_h_


// deal with EXPORT...

class TestClass {

protected:
  // Private constructor to avoid wrapping
  TestClass() {}
  ~TestClass() {}
  
private:
  TestClass(const TestClass&);  // Not implemented.
  void operator=(const TestClass&);  // Not implemented.

public:

  /**
   * @brief Suma de 2 imagenes punto a punto.
   *
   * @param i1 primera imagen
   * @param i2 segunda imagen
   * @return resultado
   **/
  static int Sum(int i1, int i2);
  
  
};


#endif 
//  _TestClass_h_
