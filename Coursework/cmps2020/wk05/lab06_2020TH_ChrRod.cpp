//Christian Rodriguez
#include <iostream>
#include <fstream>

using namespace std;

class ConfigFileError : public exception
{
  public:
    const char * what() const throw()
    {
      return "Configuration file is badly formed";
    }
};

class ConfigFileMissingKey : public ConfigFileError
{
    public:
        const char * what() const throw()
        {
            return "Missing key";
        }
};

class ConfigFileBadKey: public ConfigFileError
{
    public:
        const char * what() const throw()
        {
            return "Bad key speciation";
        }
};
class ConfigFileMissingSeparator: public ConfigFileError
{
    public:
        const char * what() const throw()
        {
            return "Missing seperator";
        }
};

class ConfigFile
{
    private: 
        bool contains_separator(string line, char sep= '=')
        {
            for (int i = 0; i < line.length(); i++)
            {
                if (line[i] == sep)
                {return true;}
            }
            return false;
        }
        
        bool is_name_valid(string name)
        {
                return name[0] == '_' || isalpha(name[0]);
        }
        bool is_comment(string line)
        {
            if(line[0] == ';') 
                return true;
            else 
                return false;

        }
        bool is_missing_key(string line)
        {
            if (line[0] == '=')
                return true;
            else
                return false;

        }
    public:
        bool load(string filename)
        {
            string line;     // stores a line of text from the file

            // code to read lines of text from a file
            ifstream fin;    // don't forget to include fstream
            fin.open(filename);
            while (getline(fin, line)) 
            {
                cout << line <<endl;
                // at this point, line contains a line of text from the file

                // remember to check for comments and blank lines -- these 
                // should not trigger exceptions
            if(!is_comment(line) && line != "" ){
                // one exception check
                if (!is_name_valid(line))
                    throw ConfigFileBadKey();

                // throw the other exceptions calling the exceptions defined earlier

                if (!contains_separator(line))
                    throw ConfigFileMissingSeparator();
                
                               
                if (is_missing_key(line))
                    throw ConfigFileMissingKey();
                }

            }
            fin.close();

            return true;
        }

};


int main(){

    ConfigFile config;

    try
    {
        if (config.load("config.ini"))
            cout << "Config file verified" << endl;
    }
    catch (ConfigFileMissingKey & ex)
    {
        cerr << ex.what() << endl;
    }
    catch (ConfigFileMissingSeparator & ex)
    {
        cerr << ex.what() << endl;
    }
    catch (ConfigFileBadKey & ex)
    {
        cerr << ex.what() << endl;
    }
    catch (ConfigFileError & ex)
    {
        cerr << ex.what() << endl;
    }

    catch (...)
    {
        cerr << "Something else happened\n";
    }
    // add more exception handlers for all exceptions 
    // also add a catch-all handler

    return 0;
}
