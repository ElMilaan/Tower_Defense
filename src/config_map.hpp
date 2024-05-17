#include <iostream>
#include <fstream>
#include <string>

int main () {
std::ifstream myfile; myfile.open("config_map.itd");
std::string mystring;
if ( myfile.is_open() ) {
char mychar;
while ( myfile ) {
mychar = myfile.get();
std::cout << mychar;
}
}
}