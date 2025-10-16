#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>

using IP = std::array<int, 4>;

// Преобразование IP в строку
std::string to_string(const IP& ip) {
    return std::to_string(ip[0]) + '.' + std::to_string(ip[1]) + '.' +
           std::to_string(ip[2]) + '.' + std::to_string(ip[3]);
}

// Парсинг "a.b.c.d" в массив чисел
IP parse_ip(const std::string& str) {
    IP ip{};
    std::stringstream ss(str);
    std::string part;
    for (int i = 0; i < 4; ++i) {
        std::getline(ss, part, '.');
        ip[i] = std::stoi(part);
    }
    return ip;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const std::string filename = "ip_filter.tsv";
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << '\n';
        return 1;
    }

    std::vector<IP> ips;
    std::string line;

    // читаем из файла все строки
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::string ip_str = line.substr(0, line.find('\t'));
        try {
            ips.push_back(parse_ip(ip_str));
        } catch (...) {
            // пропускаем некорректные строки
        }
    }

    // сортировка в обратном порядке
    std::sort(ips.begin(), ips.end(), [](const IP& a, const IP& b) {
        return a > b; // std::array поддерживает лексикографическое сравнение
    });

    // вывод всех IP
    for (const auto& ip : ips)
        std::cout << to_string(ip) << '\n';

    // 1) первый байт == 1
    for (const auto& ip : ips)
        if (ip[0] == 1)
            std::cout << to_string(ip) << '\n';

    // 2) первый == 46, второй == 70
    for (const auto& ip : ips)
        if (ip[0] == 46 && ip[1] == 70)
            std::cout << to_string(ip) << '\n';

    // 3) хотя бы один байт == 46
    for (const auto& ip : ips)
        if (std::any_of(ip.begin(), ip.end(), [](int v){ return v == 46; }))
            std::cout << to_string(ip) << '\n';

    return 0;
}
