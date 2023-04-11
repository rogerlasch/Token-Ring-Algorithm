

#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H

inline void f_log(const std::string &str)
{
    static std::ofstream ofn("output.txt");
    ofn << str << std::endl;
    std::cout << str << std::endl;
}
#define _FLOG(str, ...) f_log(std::vformat(str, std::make_format_args(__VA_ARGS__)))

template <class T>
inline T getValueFromInput(const std::string &msg)
{
    T val;
    _FLOG("{}", msg);
    std::cin >> val;
    return val;
}
#endif
