#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class CreditCard
{
    protected:
        string number;
        string type;
        int expmo, expyear;
        
        bool check_luhn()
        {
            int nDigits = number.length();

            int nSum = 0, isSecond = false;
           for (int i = nDigits - 1; i >= 0; i --)
           {
                int d = number[i] - '0';

                if (isSecond == true)
                    d = d*2;

                //add two digits to handle
                //cases that make two digits after
                //doubling
                nSum += d / 10;
                nSum += d % 10;

                isSecond = !isSecond;
           }

          return (nSum % 10 == 0); 

            // EXTRA CREDIT
            // Google/Lookup how the LUHN algorithm works
            // and implement here using number property

        }

    public:
        CreditCard(string num, int exm, int exy)
        {
            number = num;
            expmo = exm;
            expyear = exy;
        }

        virtual bool validate(int curmo, int cury, string code) = 0;
};

class Visa : public CreditCard
{
    public:
        Visa(string num, int m, int y) : CreditCard(num, m, y)
    {
        type = "Visa";
    }

        bool validate(int cm, int cy, string code)
        {
            int stored = expyear * 100 + expmo;     // 202211
            int curr = cy * 100 + cm;               // 202202

            return (curr <= stored) && number.length() == 16 && code.length() == 3 && number[0] == '4' && check_luhn();
        }    
};

class Amex : public CreditCard
{
    public:
        Amex(string num, int m, int y) : CreditCard(num, m, y)
    {
        type = "AMEX";
    }

        bool validate(int cm, int cy, string code)
        {
            int stored = expyear * 100 + expmo;     // 202211
            int curr = cy * 100 + cm;               // 202202

            return (curr <= stored) && number.length() == 15 && code.length() == 4 && number[0] == '3' && check_luhn();
        }    
};

class Mastercard : public CreditCard
{
    public:
        Mastercard(string num, int m, int y) : CreditCard(num, m, y)
    {
        type = "MC";
    }

        bool validate(int cm, int cy, string code)
        {
            int stored = expyear * 100 + expmo;     // 202211
            int curr = cy * 100 + cm;               // 202202

            return (curr <= stored) && number.length() == 16 && code.length() == 3 && number[0] == '5' && check_luhn();
        }    
};

/*
 * Validation rules
 * ----------------
 *  AMEX => 15 chars long, starts with a '3', code = length 4
 *  MC   => 16 chars long, starts with a '5', code = length 3
 *
 * */

// Factory function to return child objects of CreditCard
CreditCard * create()
{
    string ccno;
    int ccmo, ccyr;

    cout << "Enter credit card number: ";
    cin >> ccno;

    cout << "Enter card exp month and year ";
    cin >> ccmo >> ccyr;

    if (ccno[0] == '4')
    {
        return new Visa(ccno, ccmo, ccyr);
    }
    else if (ccno[0] == '3')    // Amex
    {
        // Comment out return statement above
        // Uncomment next line
        return new Amex(ccno, ccmo, ccyr);
    }
    else if (ccno[0] == '5')    // Mastercard
    {
        // Comment out return statement above
        // Uncomment next line
        return new Mastercard(ccno, ccmo, ccyr);
    }
    else
        return NULL;
}

int main()
{   
    int valmo = 2, valyear = 2024;  // this represents the current month and year
    string valcode;

    CreditCard * cc = create();

    if (cc != NULL)
    {
        cout << "Enter validation code: ";
        cin >> valcode;

        // Polymorphic call to validate function
        // The correct validate function is called regardless of 
        // which child CreditCard object has been created
        if (cc->validate(valmo, valyear, valcode))
        {
            cout << "Approved" << endl;
        }
        else
        {
            cout << "Declined" << endl;
        }
    }
    else
        cout << "Invalid credit card" << endl;

    delete cc;

    return 0;
}

