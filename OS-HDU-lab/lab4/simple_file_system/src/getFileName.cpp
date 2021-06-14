#include "statement.h"
#include<array>

// 这是之前写的，思考之后发现没必要使用文件扩展名，但可能以后要用到就留着了
std::array<std::string, 2> getFileName(const std::string &filename) {
    std::array<std::string, 2> arr;
    auto it = filename.end();
    for (; it != filename.begin(); --it) if (*it == '.') break;
    if (it == filename.begin()) {
        if (*it == '.') {
            arr[0] = "";
            arr[1] = std::string{it + 1 , filename.end()};
        } else {
            arr[0] = filename;
            arr[1] = "";
        }
    } else {
        arr[0] = std::string{filename.begin(), it};
        arr[1] = std::string{it + 1, filename.end()};
    }
    return arr;
}