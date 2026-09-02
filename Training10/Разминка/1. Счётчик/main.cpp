#include <iostream>

int main() 
{
	int mod, a, b;
	std::cin>>mod>>a>>b;
	std::cout<<(b - a + mod) % mod;

	return 0;
}
