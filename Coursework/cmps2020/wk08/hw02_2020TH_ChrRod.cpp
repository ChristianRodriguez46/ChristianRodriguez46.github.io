#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

template <typename T>
struct ValueNode
{
    T val;
    ValueNode * next;
};

template <typename T>
class Stack
{
    private:
        ValueNode <T> * head;

        // Function to create a new ValueNode with a given value
        ValueNode <T> * create(T newval)
        {
            ValueNode <T> * newnode;
            try
            {
                newnode = new ValueNode<T>;
                newnode->val = newval;
            }
            catch (bad_alloc)
            {
                newnode = NULL;
            }
            return newnode;
        }
    public:
        // Default constructor that initializes head to NULL
        Stack () 
        {
            head = NULL;
        }

        // Function to push a new value onto the stack
        void push(T newvalue)
        {
            ValueNode <T> * item = create(newvalue);
            if (head == NULL)
            {
                head = item;
                item->next = NULL;
            }
            else
            {
                ValueNode <T> * temp = head;
                head = item;
                item->next = temp;
            }
        }

        // Function to pop a value from the stack and return it
        bool pop(T & popped)
        {
            ValueNode <T> * temp = head;
            bool success = false;
            if (temp != NULL)
            {
                popped = temp->val;
                head = temp->next;
                delete temp;
                success = true;
            }

            return success;
        }

        // TODO - You will need to create a destructor
        // to make sure you don't get random segfaults

        // Destructor to delete all ValueNodes in the stack
        ~Stack() 
        {
            while(head != NULL)
            {
                ValueNode <T> * temp = head;
                head = head->next;
                delete temp;
            }
        }

        // Friend function to display the values in the stack
        friend void show(Stack &s)
        {
            ValueNode <T> * h = s.head;
            while (h != NULL)
            {
                cout << h->val << " ";
                h = h->next;
            }
            cout << endl;
        }

};

// Function to check if a given token is an operator
bool is_op(char * token)
{
    bool op = false;

    if (strlen(token) == 1)
    {
        // TODO add additional operators into the ops string below
        char ops[] = "+-x/^";
        op = strstr(ops, token) != NULL;
    }

    return op;
}

// Function to calculate the result of an operation on two operands
    template <typename T>
double calc(T operand1, T operand2, char op[])
{
    double result;

    char c = op[0];

    switch (c)
    {
        case '+': result = operand1 + operand2;
                  break;

                  // TODO:
                  // Add the remaining operations
                  // Additionally, we are designing the caret ^ operator
                  // as exponentiation
                  // For example a ^ b => a raised to power b
                  //
                  // NOTE: we'll use the x to represent multiplication
                  // rather than the asterisk * as that causes problems 
                  // when used on the command line
        case '-': result = operand1 - operand2;
                  break;
        case 'x': result = operand1 * operand2;
                  break;
        case '/': result = operand1 / operand2;
                  break;
        case '^': result = pow(operand1, operand2);
                  break;
    }

    return result;
}

// Function to solve a given RPN expression
double solve_rpn(int count, char * tokens[])
{
    double result;
    Stack <double> stack;

    // this sample FOR loop shows how to use
    // - is_op() function
    // - atof() function
    // As an example, this loop currently only pushes the tokens detected as non-operators
    // 
    // YOU WILL HAVE TO MODIFY THE LOOP TO FUNCTION 
    // AS AN RPN TOKEN CALCULATOR

    for (int i = 1; i < count; i++)
    {
        if (!is_op(tokens[i]))
        {
            double number = atof(tokens[i]);        // converts a token into number
            stack.push(number);
        }

        // TODO: implement an RPN calculator
        //       - if a token is a number, push to stack
        //       - if a token is an operator, pop two values from the stack
        //         and apply the operator to it (use the calc() function)
        //       - push the result of the calculation back to the stack
        //
        // this is how to pop from the stack
        // double popped;
        // if (stack.pop(popped))
        // {
        //     cout << popped << endl; // this is just demo, remove it
        // }

        // this is how you might use the calc() function
        // 100 and 200 are sample values that were popped from the stack
        // tokens[i] must represent an operator, not a numeric token
        //double test = calc<double>(100, 200, tokens[i]);     // where tokens[i] is an operator
        else
        {
            double operand1, operand2;
            if (stack.pop(operand1) && stack.pop(operand2))
            {
                double result = calc <double> (operand2, operand1, tokens[i]);
                stack.push(result);
            }
        }
    }

    if (stack.pop(result))
    {
        return result;
    }
    else
    {
        cerr << "Error: invalid RPN expression" << endl;
        return 2;
    }
}

int main(int argc, char *argv[])
{
    // Feel free to add more code to main()

    // Check if the correct number of arguments are provided
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <operand1> <operand2> <operator>" << endl;
        return 1;
    }

    /*
    // Check if an operator is provided in the arguments
    bool is_operator_found = false;
    for (int i = 3; i < argc; i++) {
        if (is_op(argv[i])) {
            is_operator_found = true;
            break;
        }
    }

    if (!is_operator_found) {
        cerr << "Error: No operator provided in the arguments." << endl;
        cerr << "Usage: " << argv[0] << " <operand1> <operand2> <operator>" << endl;
        return 1;
    }
*/
    // Call the solve_rpn function with the provided arguments
    cout << solve_rpn(argc, argv) << endl;

    return 0;
}
