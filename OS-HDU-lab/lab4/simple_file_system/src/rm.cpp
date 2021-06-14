#include "statement.h"
#include <iostream>

void my_rm() {
    std::string str;
    std::cin>>str;
    switch (_my_rm(str)) {
    case NOTFOUND:
        printf("can`t find this file\n");
        break;
    case OK: 
        printf("rm success\n");
        break;
    default:
        printf("8 ke neng\n");
        break;
    }
}
int _my_rm(const std::string &filename) {
    FCB *fcb = findDirFile(filename, true);
    if (fcb == NULL) return NOTFOUND;
    freeFile(fcb);
    return OK;    
}