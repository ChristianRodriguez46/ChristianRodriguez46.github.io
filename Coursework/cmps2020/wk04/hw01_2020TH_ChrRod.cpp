#include <iostream>
#include <fstream>
#include <iomanip> //included libray for set precision

using namespace std;

// sample file-write code. Adapt as necessary for your assignment

void save(string filename)
{
    ofstream fout;
    fout.open(filename);
    if (fout.is_open())
    {
        fout << "Line 1 saved to file" << endl;
        fout << "Line 2 saved to file" << endl;
        fout.close();
    }
}
struct CountyInfo
{
        string name;
        double infections;
};

class CoronaData 
{
    protected: 
        CountyInfo data[5];
    public: 
        CoronaData()
        {
            // hard-coded data. Could load from any source.
            data[0].name = "Los Angeles";
            data[0].infections = 255000;
            data[1].name = "Riverside";
            data[1].infections = 55766;
            data[2].name = "Orange";
            data[2].infections = 52166;
            data[3].name = "San Bernardino";
            data[3].infections = 50709;
            data[4].name = "San Diego";
            data[4].infections = 42950;
        }

        virtual void save_to_file(string filename)= 0;
};

class CoronaDataJson : public CoronaData
{
    void save_to_file(string filename)
    {
        ofstream file;
        file.open(filename);
        if (file.is_open())
        { 
            {
                file << "{\n \"data\" : [\n";

                for (int i = 0; i < 5; i++)
                {
                    file << "   {\"name\" : \"" << fixed << setprecision(4) << data[i].name << "\", \"infections\" : \"" << data[i].infections << "\" }";
                    if (i < 4) {file << ",";}
                    file << endl;
                }

                file << "  ] \n}\n";
                file.close();
            }
        }else
        {
            //throw an error if I can't open file
            cout << "There was an error opening file for writing!\n";
        }
    }
};

class CoronaDataCsv : public CoronaData
{
    void save_to_file(string filename)
    {
        ofstream file;
        file.open(filename);
        if (file.is_open())
        { 
            {
                file << "County, Infections\n";

                for (int i = 0; i < 5; i++)     //loop through data
                {
                    file << '\"' << data[i].name<< "\", " << fixed << setprecision(4) << data[i].infections << endl;
                }
                file.close();
            }
        }else
        {
            cout << "There was an error opening file for writing!\n";
        }
    }
};


void save(CoronaData *cd, string filename)
{
    cd->save_to_file(filename);
    cout << "File is ready." << endl;
}

int main()
{
    CoronaData * cd;
    char input;      //make sure the input is a letter

    // code to prompt the user for format type

    cout << "Choose output format (j = JSON, c = CSV): ";
    cin >> input;
    cout << endl;

    // User chose JSON format
    if (input == 'j')
    {
        cd = new CoronaDataJson;
        save(cd, "corona.json");
    }
    // do something similar for CSV format

    //User chose CSV format
    else if (input == 'c')
    {
        cd = new CoronaDataCsv;
        save(cd, "corona.csv");
    }
    else{
        cout << "Invalid choice!\n";
    }
    // don't forget pointer cleanup
    delete cd;

    return 0;
}
