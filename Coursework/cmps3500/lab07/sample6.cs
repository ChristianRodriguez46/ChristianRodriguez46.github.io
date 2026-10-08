/* sample6.cs 
 * demonstrate parameter passing in C# 
 *     $ mcs [filename.cs]            // will produce intermediate code
 *     $ mono [filename.exe]          // will execute intermediate code 
 */

using System;

namespace Functions {
  class Application {

    // demonstrate pass-by-result "out mode" and "in mode" parameter passing
    // pass by value 'in mode' is the default 
    // Foo (out 5, xin) is a compilation error - 5 is not a modifiable L-value
    // Foo (out xout, xin) would be a compilation error if xin has no value
    static void Foo (out int x, int y)  {
       Console.WriteLine ("In function foo...");   

       // int a = x;  # compilation error if you read xout b/f assigning it
       x = 10;  // assignment must occur for method to complete normally
       Console.WriteLine ("set out parameter x to 10: {0}",x);   

       y = x; // can read x now - changing y doesn't modify y in caller
       Console.WriteLine ("set in parameter y to 10: {0}", y);   
       Console.WriteLine ("Leaving function foo...\n");   
    }

    // demonstrate pass-by-reference "inout mode" parameter passing
    static void Foo2 (ref int xref)
    {     xref = 999;  }   // changes argument in caller

    static void Main()    {
      int xout, xin, xref;   
      xin = 5;
      Foo (out xout, xin);    
      Console.WriteLine ("out parameter xout is 10: {0} \n", xout);  
      Console.WriteLine ("in parameter xin is still 5: {0} \n", xin);  
  
      xref = 5; 
      Foo2 (ref xref);
      Console.WriteLine ("ref parameter xref is now 999: {0} \n", xref);   

    } // end Main 

 } // end Application 

} // end Namespace
