//Christian Rodriguez
#include <iostream>

using namespace std;

class Control
{
    protected:
        string text;
    public:
        Control(string t)
        {
            text = t;
        }
};

class Checkbox : public Control
{
    private: 
        bool checked;
    public:
        Checkbox(string t, bool c)
            : Control(t)
        {
            checked = c;
        }
        string display()
        {
            if (checked == true)
                return "[x] " + text;
            else
                return "[ ] " + text;
            
        }

};

class Textbox : public Control
{
    private: 
        string caption;
    public:
        Textbox (string c, string t)
            : Control(t)
        {
            caption = c;
        }

        string display()
        {
            if (text == "")
                return caption + ": " + "N/A";
            else
                return caption + ": " + text; 
        }
};


int main(){

    Textbox t1("First Name", "Marco");
    Textbox t2("Middle Name", "");
    Textbox t3("Last Name", "Polo");

    Checkbox c1("Employed", true);
    Checkbox c2("Student", false);

    cout << t1.display() << endl;
    cout << t2.display() << endl;
    cout << t3.display() << endl;
    cout << endl; 
    cout << c1.display() << endl;
    cout << c2.display() << endl;

    return 0;
}
