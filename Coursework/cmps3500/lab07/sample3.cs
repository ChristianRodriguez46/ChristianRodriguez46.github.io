/* sample3.cs
 * demonstrate arrays in C# 
 */

using System;

namespace Sample3 {
  class Application {
    static void Main() {
      // all arrays are heap dynamic objects from System.Array class 
      int[] intArray = new int[32];    

      // you can omit new if you initialize array when you declare it
      int[] numbers = {1, 2, 3, 4, 5};      // implicit heap dynamic
      numbers[0] = 0;   

      // Length is a property of System.Array 
      for (int i = 0; i < intArray.Length; i++) {
        intArray[i] = i;
      }

      // print the array back to screen using C# foreach loop
      Console.Write("intArray contents: ");
      foreach (int i in intArray) {
        Console.Write("{0} ", i);
      }
      Console.Write("\n");
    }
  }
}
