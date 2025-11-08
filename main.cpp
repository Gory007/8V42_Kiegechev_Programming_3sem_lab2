#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <algorithm>
#include <cstdio>

using IP = std::tuple<int, int, int, int>;

std::string to_string(const IP& ip) {
    return std::to_string(std::get<0>(ip)) + "." +
           std::to_string(std::get<1>(ip)) + "." +
           std::to_string(std::get<2>(ip)) + "." +
           std::to_string(std::get<3>(ip));
}

IP parse_ip(const std::string& s) {
    int a, b, c, d;
    std::sscanf(s.c_str(), "%d.%d.%d.%d", &a, &b, &c, &d);
    return {a, b, c, d};
}

int main() {
    //std::ios::sync_with_stdio(false);
    //std::cin.tie(nullptr);

    std::ifstream file("ip_filter.tsv");
    std::vector<IP> ips;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        if (!line.empty() && line.back() == '\r') line.pop_back();

        ips.push_back(parse_ip(line.substr(0, line.find('\t'))));
    }


    std::sort(ips.rbegin(), ips.rend());

    std::for_each(ips.begin(), ips.end(), [](const IP& ip){
        std::cout << to_string(ip) << '\n';
    });

    std::for_each(ips.begin(), ips.end(), [](const IP& ip){
        if (std::get<0>(ip) == 1)
            std::cout << to_string(ip) << '\n';
    });

    std::for_each(ips.begin(), ips.end(), [](const IP& ip){
        if (std::get<0>(ip) == 46 && std::get<1>(ip) == 70)
            std::cout << to_string(ip) << '\n';
    });

    std::for_each(ips.begin(), ips.end(), [](const IP& ip){
        if (std::get<0>(ip) == 46 || std::get<1>(ip) == 46 ||
            std::get<2>(ip) == 46 || std::get<3>(ip) == 46)
            std::cout << to_string(ip) << '\n';
    });

    return 0;
}
