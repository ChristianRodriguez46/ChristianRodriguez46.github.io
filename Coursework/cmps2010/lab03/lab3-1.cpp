#include <iostream>
#include <cstdlib>
using namespace std;

int main(){
  unsigned int seed = time(0);
  srand(seed);

  const int MIN_VALUE = -10;
  const int MAX_VALUE = 10;
  
  int userInput;

  int num = (rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE;

  cout << "WELCOME TO THE GUESSING GAME!" << endl << endl << endl; 


  if(num > 0){
      cout << "The number is positive" << endl;
  }else{ 
      cout << "The number is negative" << endl;
  }


  if(num %2 == 0){
      cout << "The number is even" << endl;
  }else{ 
      cout << "The number is odd" << endl;
  }


  if(num >= -4 && num <= 4){
      cout << "The number is between -4 and 4 (inclusive)" << endl;
  }else{
      cout << "The number is less than -4 or greater than 4" << endl;
  }
  
  cout <<  "" << endl << endl;

  
  cout << "GUESS THE NUMBER!: "; cin >> userInput;

  
  cout << endl << endl;
  
  
  if(userInput == num){ cout << "Wow you actually got it (ノಠ益ಠ)ノ彡┻━┻" << endl;
  }else{
      cout << "YOUR WRONG ᕦ(ò_óˇ)ᕤ" << endl;
  } 
 
  char ans; 

  cout << "want another hint?(y/n)";
  
  cin >> ans;

  cout << "" << endl << endl;


  if(ans == 'n'){ 
      cout << "honorable but you still lost" << endl;
  }else{ 
      cout << "YOU LOSE " << endl;
  }
      
  cout << "" << endl;
  cout << "The number was " << num << "." << endl;
  
  return 0;
}
