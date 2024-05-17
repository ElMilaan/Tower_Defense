#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "config_map.hpp"
#include <vector>

void config_map (){
std::ifstream myfile;
std::string map_location;
std::vector <int> path_color;
std::vector <int> in_color;
std::vector <int> out_color;

myfile.open("shopping_list.txt");
std::string myline;
if ( myfile.is_open() ) {
while ( myfile ) { 
std::getline (myfile, myline);
std::cout << myline << '\n';
std::stringstream line_stream;
line_stream << myline;
if (myline.starts_with("#"))
{
    
}
if (myline.starts_with(""))
{
    
}
if (myline.starts_with("map"))
{
    
}
if (myline.starts_with("path"))
{
    
}
if (myline.starts_with("in"))
{
    
}
if (myline.starts_with("out"))
{
    
}
if (myline.starts_with("graph"))
{
    
}
if (myline.starts_with("node"))
{
    
}
}
}
else {
std::cout << "Couldn't open file\n";
}
}