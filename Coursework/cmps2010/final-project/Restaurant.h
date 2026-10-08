#include <string>
//Restraunt Class declaration
class Restaurant{
    private:
        std::string name;
        std::string type;
        std::string style;
        unsigned short numLocations;
        float score;
    public:
        //default constructor
        Restaurant();
        Restaurant(std::string, std::string, std::string, unsigned short, float);
        
        void setName(std::string);
        void setType(std::string);
        void setStyle(std::string);
        void setNumLocations(unsigned short);
        void setScore(float);

        std::string toCSV();


};
