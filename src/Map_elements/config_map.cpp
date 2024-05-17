#include <iostream>
#include <fstream>
#include <string>
#include "config_map.hpp"

void config_map (){
std::ifstream myfile;
myfile.open("shopping_list.txt");
std::string myline;
if ( myfile.is_open() ) {
while ( myfile ) { // equivalent to myfile.good()
std::getline (myfile, myline);
std::cout << myline << '\n';

}
}
else {
std::cout << "Couldn't open file\n";
}
}