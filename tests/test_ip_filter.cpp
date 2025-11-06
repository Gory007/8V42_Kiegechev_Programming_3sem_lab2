#include <gtest/gtest.h>
#include <vector>
#include <array>
#include <algorithm>

using IP = std::array<int,4>;

void sort_ips(std::vector<IP>& ips) {
    std::sort(ips.begin(), ips.end(), [](const IP& a, const IP& b) {
        return a > b;
    });
}

TEST(IPFilterTest, SortDescending) {
    std::vector<IP> ips = {
        {1, 2, 3, 4},
        {46, 70, 1, 1},
        {255, 255, 255, 255},
        {46, 70, 0, 1}
    };
    sort_ips(ips);
    EXPECT_EQ(ips.front(), (IP{255,255,255,255}));
    EXPECT_EQ(ips.back(), (IP{1,2,3,4}));
}

TEST(IPFilterTest, FilterFirstByte) {
    std::vector<IP> ips = {
        {1, 1, 1, 1},
        {2, 2, 2, 2},
        {1, 9, 9, 9}
    };
    std::vector<IP> result;
    std::copy_if(ips.begin(), ips.end(), std::back_inserter(result),
                 [](const IP& ip){ return ip[0] == 1; });
    EXPECT_EQ(result.size(), 2);
}

TEST(IPFilterTest, FilterFirstSecondByte) {
    std::vector<IP> ips = {
        {46, 70, 1, 1},
        {46, 69, 1, 1},
        {1, 70, 46, 70}
    };
    std::vector<IP> result;
    std::copy_if(ips.begin(), ips.end(), std::back_inserter(result),
                 [](const IP& ip){ return ip[0] == 46 && ip[1] == 70; });
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], (IP{46,70,1,1}));
}

TEST(IPFilterTest, FilterAnyByte46) {
    std::vector<IP> ips = {
        {1, 46, 3, 4},
        {46, 0, 0, 0},
        {0, 0, 0, 0}
    };
    std::vector<IP> result;
    std::copy_if(ips.begin(), ips.end(), std::back_inserter(result),
                 [](const IP& ip){
                     return std::any_of(ip.begin(), ip.end(),
                                        [](int v){ return v == 46; });
                 });
    EXPECT_EQ(result.size(), 2);
}
