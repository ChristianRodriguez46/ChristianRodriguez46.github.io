#include <string>

//Structure Definitions
class Monster{
    private:
        std::string name;
        std::string type;
        std::string color;
        int eyes;
        int arms;
        int legs;
    public:
        void setName(std::string);
        std::string getName() const;
        
        void setType(std::string);
        std::string getType() const;
        
        void setColor(std::string);
        std::string getColor() const;

        void setEyes(int);
        int getEyes() const;

        void setArms(int);
        int getArms() const;

        void setLegs(int);
        int getLegs() const;
};

