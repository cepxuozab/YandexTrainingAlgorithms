#include <iostream>
#include <string>
using namespace std::string_literals;
int main() {
  int troom, tcond;
  std::cin >> troom >> tcond;
  std::string str;
  std::cin >> str;
  int ans = 0;
  if (str == "auto"s) {
    ans = tcond;
  } else if (str == "fan"s) {
    ans = troom;
  } else if (str == "freeze") {
    ans = troom > tcond ? tcond : troom;
  } else if (str == "heat") {
    ans = troom < tcond ? tcond : troom;
  }
  std::cout << ans << std::endl;
}
