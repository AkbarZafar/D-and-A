#include <iostream>


int main(){
  std::string cmdline;
  std::getline(std::cin, cmdline);
  while (!std::cin.eof()){
    if(cmdline == "exit") return 0;
    
    getline(std::cin, cmdline);
  }
  
}