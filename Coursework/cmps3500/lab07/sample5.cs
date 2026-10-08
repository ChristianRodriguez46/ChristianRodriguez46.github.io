/* sample5.cs
 * demonstrate interfaces 
 *
 * An interface is a special type of class that has nothing but implicit virtual
 * functions. No member variables or implementation allowed. An interface is 
 * analogous to an abstract class in C++ with all virtual methods. In C++ an
 * abstract class is used as a base class only and contains at least one pure 
 * virtual function; e.g.
 *     class AB {
 *     public:
 *         virtual void f() = 0;
 *     };
*/

using System;

namespace Sample5 {

  interface IShape {
     void DisplayArea();
  }

  // A simple implementation of a shape 'interface'  
  class Rectangle : IShape {
     public Rectangle(int inWidth, int inHeight) {
       m_Width = inWidth;
       m_Height = inHeight;
     }

     // implementation of IShape method
     public void DisplayArea() {
       Console.WriteLine("The area is: {0}", m_Width * m_Height);
     }

     // private member variables
     private int m_Width = 0;
     private int m_Height = 0;
  }

  // driver class
  class Application {
     static void Main() {
       IShape shape = new Rectangle(10, 10);
       shape.DisplayArea();
     }
  }
}
