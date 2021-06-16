#include "statement.h"
#include <iostream>

extern USEROPEN openfilelist[MAXOPENFILE];
extern DISK *disk;
extern std::queue<unsigned short> free_q;

void my_write() {
    // printf("it is write\n");
    std::string filename;
    std::cin>>filename;
    int fd = NOTFOUND;
    FCB *fcb = findDirFile(filename, true);
    if (fcb == NULL) {
        printf("can`t find this file\n");
        return ;
    }
    for (unsigned short i = 0; i < MAXOPENFILE; i++) {
        if (openfilelist[i].fcb == fcb) {
            fd = i;
            break;
        }
    }
    switch (fd) {
    case NOTFOUND:
        printf("openlist can`t find this file\n");
        break;
    default:
        break;
    }
    _my_write(fd);
}

void _my_write(const unsigned short fd) {;
    if (fd > MAXOPENFILE) return ;
    FCB *fcb = openfilelist[fd].fcb;
    if (!fcb->attribute) return ;
    char c;
    again:
    printf("Truncated write(t) Overlay write(o) Add write(a)\n");
    std::cin>>c;
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
    getchar();
    std::getline(std::cin, w_str);
    while (std::getline(std::cin, line)) {
        w_str += '\n' + line;
    }
    // while (std::cin>>line) {
    //     w_str += '\n' + line;
    // }
    // std::cout<<w_str<<std::endl;
    // getchar();
    printf("written %u\n", _do_write(fd, w_str, c));
}


unsigned short _do_write(const unsigned short fd, const std::string &text, const char wstyle) {
    // printf("go to _do_write\n");
    // getchar();
    if (fd > MAXOPENFILE) return 0;
    FCB *fcb = openfilelist[fd].fcb;
    unsigned short len = text.size();
    // std::cout<<"len :"<<len<<std::endl;
    // if (text.length() > sizeof(disk)) len = sizeof(disk);
    unsigned short BlockNum = 0;
    unsigned short m = 0;
    unsigned short temp;
    openfilelist[fd].fcbstate = true;
    switch (wstyle) {
        case 't': 
            freeFile(fcb);
            if (free_q.empty()) return 0;
            temp = free_q.front();
            free_q.pop();
            disk->busy[temp] = temp;
            fcb->first = temp;
            fcb->length = 0;
            BlockNum = temp;
            fcb->in_use = true;
            break;
        case 'o':
            BlockNum = jumpBlock(fcb->first, openfilelist[fd].count / BLOCKSIZE);
            temp = disk->busy[BlockNum];
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
    // printf("switch\n");
    // getchar();
    unsigned short it = 0;
    if (m > 0) {
        strncpy(diskToChar(BlockNum),text.substr(it, m).c_str(), m);
        it = m;
    }
    bool flag = false;
    while (len - it >= BLOCKSIZE) {
        flag = true;
        if (free_q.empty()) {
            fcb->length += it;
            openfilelist[fd].count += it;
            return it;
        }
        temp = free_q.front();
        free_q.pop();
        disk->busy[BlockNum] = temp;
        BlockNum = temp;
        disk->busy[BlockNum] = BlockNum;
        strncpy(diskToChar(BlockNum),text.substr(it, BLOCKSIZE).c_str(), m);
        fcb->length += BLOCKSIZE;
        it += BLOCKSIZE;
    }
    // std::cout<<it<<std::endl;
    // printf("while\n");
    // getchar();
    if (len - it > 0) {
        if (flag) {
            if (free_q.empty()) {
                fcb->length += it;
                openfilelist[fd].count += it;
                return it;
            }
            temp = free_q.front();
            free_q.pop();
            disk->busy[BlockNum] = temp;
            BlockNum = temp;            
            disk->busy[BlockNum] = BlockNum;
        }
        // std::cout<<"write"<<text.substr(it, len - it).c_str()<<std::endl;
        // std::cout<<"it "<<it<<" len: "<<len<<std::endl;
        strncpy(diskToChar(BlockNum),text.substr(it, len - it).c_str(), len - it);
        fcb->length += len - it;
        it += len - it;
    }
    // printf("if\n");
    // getchar();
    return it;
}

