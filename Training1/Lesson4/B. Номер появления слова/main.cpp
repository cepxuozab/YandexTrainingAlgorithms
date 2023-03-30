#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

auto main()->int
{
    std::unordered_map<std::string,int> frequencies;
    for(std::string str; std::cin>>str;){
        frequencies[str]++;
        std::cout<<frequencies.at(str) - 1<<' ';
    }
    return 0;    
}