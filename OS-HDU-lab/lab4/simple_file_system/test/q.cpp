#include <queue>
#include <string>
#include <iostream>
#include <ctime>
#include <cstring>
using namespace std;

queue<string> PathSub(const string &path) {
    queue<string> q;
    int pos = 0, prev = 0;
    if (path[0] == '/') {
        q.push("home");
        pos = 1;
    }
    while ((pos = path.find('/', pos)) != string::npos) {
        q.push(path.substr(prev, pos));
        prev = pos;
    }
    return q;
}

#define FILENAME_LEN 12
struct FCB {
    char filename[FILENAME_LEN]; // 文件名
    // char exname[EXNAME_LEN]; // 文件扩展名
    bool attribute; // false表示目录，true表示数据文件
    time_t _time; //创建日期
    unsigned short first; //起始盘号
    unsigned int length; //长度
    bool in_use; // 是否为空
    void init(const char *str, unsigned int _first, bool _attribute) {
        // strncpy(filename, str, FILENAME_LEN);
        _time = time(NULL);
        first = _first;
        length = 0;
        attribute = _attribute;
        in_use = true;
    }
};

int main() {
    // auto q = PathSub("/123/456/789");
    // while (!q.empty()) {
    //     cout << q.front()<<endl;
    //     q.pop();
    // }
    // printf("%d", sizeof(FCB));
    queue<int> q1;
    queue<int> q2;
    clock_t startTime;
	clock_t endTime;
    startTime = clock();
    for (int i = 0; i < 100000000; i++) q1.push(i);
    endTime = clock();
	cout << "："  << double(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    startTime = clock();
    for (int i = 0; i < 100000000; i++) q2.emplace(i);
	endTime = clock();
	cout << "："  << double(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}