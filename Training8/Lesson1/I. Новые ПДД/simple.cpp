#include <iostream>


auto main()->int{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    long long x,y,f,g;
    std::cin>>x>>y>>f>>g;
    auto horizontal_diff = std::llabs(x - f),vertical_diff=std::llabs(y - g);
    if(horizontal_diff != 0)horizontal_diff--;
    if(vertical_diff != 0)vertical_diff--;
    auto res = 3LL*(horizontal_diff + vertical_diff) + 1;
    if(x==f || y==g)res--;
    std::cout<<res;
}