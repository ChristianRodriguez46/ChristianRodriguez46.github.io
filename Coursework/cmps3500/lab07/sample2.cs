/* sample2.cs 
 * demonstrate input, output, random numbers, primitive types, unsafe keyword
 *   
 *  $ mcs /unsafe sample2.cs   <== if you uncomment unsafe code you must do this
 *
 */

using System;

namespace Sample2 {
  class Application {
    static void Main() {

      int i = System.Int32.MaxValue;        // everything is boxed as an Object 

      // a random number generator
      Random random = new Random();
      i = Convert.ToInt32(random.NextDouble()*100);  
      i = i % 5;

      string s = i.ToString();    
     
      Console.WriteLine( "\nint: {0} string: {1}\n", i, s );  


      float val1 = 10.35001f;
      //  i = val1;   C# is strongly typed - no implicit narrowing coercion

      string val2 = "this is a test string";

      byte val3 = 0xff;  //  unsigned 8-bit integers 0 - 255.

      decimal val4 = 34.23m; // 'm' does an implicit cast from float to decimal


      // invalid input will raise an implicit exception on input 
      Console.WriteLine("Enter a number: ");  

      i = Convert.ToInt32(Console.ReadLine());

      Console.WriteLine(
        "5 different datatypes: \n * {0} \n  * {1} \n * {2} \n * {3} \n * {4}",
         val1, val2, val3, val4, i
      );

   /*
    * // use of unsafe means you must compile with /unsafe compiler option
    *     unsafe {
    *      int* iptr;    // C# supports pointers only in unsafe blocks 
    *        iptr = &i; 
    *   }   
    */

     }
   }
}
