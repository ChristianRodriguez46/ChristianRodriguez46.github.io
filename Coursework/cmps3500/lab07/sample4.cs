/* sample4.cs
 * demonstrate C# constructors, destructors, and properties 
 * Unlike C++, public and private can preface individual class members
 */

using System;

namespace Sample4 {
  class Rectangle {

    public Rectangle () {}             // constructors can be public or private

    public Rectangle( int w, int h) {  // can overload constructor like C++
      Width = w;                       // Width is a property - see def below
      m_Height = h; 
    }

    // Width property definition -- a property is unlike anything in C++
    public int Width  {
      get  {              // get is an implicit method inside Width property
        return m_Width;   // returns the value of private member m_Width 
      }
      set {               // sets the value, outputs it to the console
        m_Width = value;  // value is an implicit argument to set 
      }
    }

    public int Height {    // no set means Height property is read-only
      get {
        return m_Height;
      }
    }

    // C# has implicit garbage collection but you can still implement a C++ 
    // style destructor for various cleanup activities

    ~Rectangle() {
       // cleanup statements 
    }

    private int m_Width = 0;
    private int m_Height = 10;
  }

  class Application {
    static void Main() {
      Rectangle myRectangle = new Rectangle();
      myRectangle.Width = 100;   // implicitly calls Rectangle.Width.Set{100}
      int height = myRectangle.Height; //implicitly calls Rectangle.Height.Get{}

      Console.WriteLine("Rectangle's height: {0}", height);

      Console.WriteLine(
         "Area of the Rectangle: {0}",
         myRectangle.Width * myRectangle.Height
      );
    }
  }
}
