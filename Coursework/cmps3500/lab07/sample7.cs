/* sample7.cs
 *  demonstrate event handling in C#
 *  $ mcs sample7.cs
 *  $ mono sample7.exe                      
 */

using System;

namespace Sample6 {
  public class Application {
    static void Main() {
      ClassA classA = new ClassA();
      classA.ValueChanged += 
        new ClassA.ValueChangedHandler(Application.OnValueChanged);

      classA.Value = 100;   
    }
   
    // this is the event handler 
    private static void OnValueChanged(int oldValue, int newValue)
    {
      Console.WriteLine( 
        "From OnValueChanged event handler: old value: {0}, new value: {1}",
        oldValue, newValue
      );
    }
  }

  public class ClassA
  {
    // a delegate is similar to a function pointer in C/C++
    public delegate void ValueChangedHandler(int oldValue, int newValue);

    //  specify the delegate to be called when ValueChanged event occurs
    public event ValueChangedHandler ValueChanged;

    public ClassA()
    {
      m_Value = 0;
    }

    // Value is a property
    public int Value
    {
      get
      {
        return m_Value;
      }
      set
      {
        int oldValue = m_Value;
        m_Value = value;
        this.OnValueChanged(oldValue, m_Value);
      }
    }

    // private methods
    private void OnValueChanged(int oldValue, int newValue)
    {
      if (this.ValueChanged != null)
      {
        this.ValueChanged(oldValue, newValue);
      }
    }
    
    // private members
    int m_Value;
  }
}
