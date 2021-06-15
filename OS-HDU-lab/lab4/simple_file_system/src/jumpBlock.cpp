#include "statement.h"
extern DISK *disk;




unsigned short jumpBlock(unsigned short BlockNum, int n) {
    for (unsigned short i = 0; disk->busy[BlockNum] != BlockNum && i < n; i++) {
        BlockNum = disk->busy[BlockNum];
    }
    return BlockNum;
}
