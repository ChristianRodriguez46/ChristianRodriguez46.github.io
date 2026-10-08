/* lab07.cs
 * C# lab07 Modify this code 
 */

using System;

namespace Assignment {
  public class Application  {
    static void Main() {
      double rectWidth = 8.75f, rectHeight = 20.5f;
      IShape shape1 = new Rectangle(rectWidth, rectHeight);
      
      double triBase = 5.5f, triHeight = 12.25f;
      IShape shape2 = new Triangle(triBase, triHeight);

      double cirRadius = 5.5f;
      Circle shape3 = new Circle(cirRadius);
      // test Radius property
      shape3.Radius = 3.5f;
      Console.WriteLine("My Radius is '{0}'\t: ", shape3.Radius);
      
      Console.WriteLine("area of type '{0}'\t: {1}", shape1, shape1.Area);
      Console.WriteLine("area of type '{0}'\t: {1}", shape2, shape2.Area);  
      Console.WriteLine("area of type '{0}'\t: {1}", shape3, shape3.Area);
      shape1.Display();
      shape2.Display();
      shape3.Display();
    }
  }

  public interface IShape {
     void Display ();
      
     double Area {
       get;    // concrete classes must implement IShape.Area.Get()
     }
  }

  ////////////////////////////////////////////////////////////////////////
  public class Rectangle: IShape {
     public Rectangle(double inWidth, double inHeight) {
     }
    
     public double Area {
     }

     public void Display() {
     }

     private double width = 0;
     private double height = 0;
  }
  ////////////////////////////////////////////////////////////////////////
  public class Triangle: IShape {
    public Triangle(double inBase, double inHeight) {
    }

    public double Area {
    }

    public void Display() {
    }

    private double mybase = 0;
    private double myheight = 0;
  }

  ////////////////////////////////////////////////////////////////////////
  public class Circle: IShape {
    public Circle(double inRadius) {
    }

    public double Radius {
    }

    public double Area {
    }

    public void Display() {
    }

    private double radius = 0;
  } 


} // end namespace 
