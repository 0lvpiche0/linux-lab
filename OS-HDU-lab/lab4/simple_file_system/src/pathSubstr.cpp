#include <queue>
#include <array>
#include <string>
using namespace std;

array<string, 2> pathSubstr_2(const string &path) {
    auto it = path.end() - 1;
    array<string, 2> arr;
    for (; it!= path.begin() && *it != '/'; --it) ;
    if (it == path.begin() && *it == '/') {
        arr[0] = "/";
    } else {
        arr[0] = string{path.begin(), it};
        arr[1] = string{it + 1, path.end()};
    }
    return arr;
}

queue<string> pathSubstr(const string &path) {
    queue<string> q;
    int pos = 0, prev = 0;
    if (path[0] == '/') {
        q.push("/");
        prev = pos = 1;
    }
    while ((pos = path.find('/', pos)) != string::npos) {
        q.push(path.substr(prev, pos - prev));
        pos++;
        prev = pos;
    }
    q.push(path.substr(prev, path.length() - prev));
    return q;
}