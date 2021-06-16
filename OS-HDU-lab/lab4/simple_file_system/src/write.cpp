#include "statement.h"
#include <iostream>

extern USEROPEN openfilelist[MAXOPENFILE];
extern DISK *disk;
extern std::queue<unsigned short> free_q;

void my_write() {
    std::string filename;
    std::cin>>filename;
    int fd = _my_open(filename);
    switch (_my_open(filename)) {
    case NOTFOUND:
        printf("invalid filename\n");
        break;
    case NO_FREE_OPEN:
        printf("Open file full\n");
    default:
        break;
    }
    _my_write(fd);
}

void _my_write(int fd) {
    FCB *fcb = openfilelist[fd].fcb;
    char c;
    again:
    printf("Truncated write(t) Overlay write(o) Add write(a)\n");
    scanf("%c", &c);
    switch (c) {
        case 't':
        case 'o':
        case 'a': break;
        case 'n': return;
        default:
            printf("pleas input t/o/a, or input n to give up\n");
            goto again;
    }
    std::string w_str;
    std::string line;
    std::getline(std::cin, w_str);
    while (std::getline(std::cin, line)) {
        w_str += '/' + line;
    }
    printf("written %u\n", _do_write(fd, w_str, c));
}


unsigned short _do_write(const int fd, const std::string &text, const char wstyle) {
    FCB *fcb = openfilelist[fd].fcb;
    unsigned short len = text.length();
    if (text.length() > sizeof(disk)) len = sizeof(disk);
    unsigned short BlockNum = 0;
    unsigned short m = 0;
    switch (wstyle) {
        case 't': 
            freeFile(fcb);
            if (free_q.empty()) return 0;
            unsigned short temp = free_q.front();
            free_q.pop();
            disk->busy[temp] = temp;
            fcb->first = temp;
            fcb->length = 0;
            BlockNum = temp;
            fcb->in_use = true;
            break;
        case 'o':
            BlockNum = jumpBlock(fcb->first, openfilelist[fd].count / BLOCKSIZE);
            unsigned short temp = disk->busy[BlockNum];
            while (disk->busy[temp] != temp) {
                unsigned short temp2 = disk->busy[temp];
                freeBlock(temp);
                temp = temp2;
            }
            freeBlock(temp);
            fcb->length = openfilelist[fd].count;
            disk->busy[BlockNum] = BlockNum;
            m = openfilelist[fd].count % BLOCKSIZE; 
            break;
        case 'a': 
            BlockNum = jumpBlock(fcb->first, fcb->length / BLOCKSIZE);
            m = fcb->length % BLOCKSIZE; 
            break;
        default:
            return 0;
    }
    unsigned short it = 0;
    if (m > 0) {
        strncpy(diskToChar(BlockNum),text.substr(it, m).c_str(), m);
        it = m;
    }
    while (len - it >= BLOCKSIZE) {
        if (free_q.empty()) {
            fcb->length += it;
            openfilelist[fd].count += it;
            return it;
        }
        unsigned short temp = free_q.front();
        free_q.pop();
        disk->busy[BlockNum] = temp;
        BlockNum = temp;
        disk->busy[BlockNum] = BlockNum;
        strncpy(diskToChar(BlockNum),text.substr(it, BLOCKSIZE).c_str(), m);
        fcb->length += BLOCKSIZE;
        it += BLOCKSIZE;
    }
    if (len - it > 0) {
        if (free_q.empty()) {
            fcb->length += it;
            openfilelist[fd].count += it;
            return it;
        }
        unsigned short temp = free_q.front();
        free_q.pop();
        disk->busy[BlockNum] = temp;
        BlockNum = temp;
        disk->busy[BlockNum] = BlockNum;
        strncpy(diskToChar(BlockNum),text.substr(it, len - it).c_str(), m);
        fcb->length += len - it;
        it += len - it;
    }
    return it;
}

