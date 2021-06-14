// #include "statement.h"

// extern USEROPEN ptrcuridr; 
// extern USEROPEN openfilelist[MAXOPENFILE];
// extern DISK *disk;;
// extern std::string currentdir;

// // 未完成
// int open_dir(const std::string &dirname) {
//     if (dirname == "home") return 0;
//     int BlockDirNum = ptrcuridr.fcb.first;
//     // USEROPEN *temp = ptrcuridr;

//     int dirAddr = -1;
    
//     DirFile *dir = (DirFile *) disk->data[BlockDirNum - OFFSET];
//     for (unsigned short i = 0; i < FCBCOUNT; i++) {
//         if (!dir->fcb[i].attribute && dir->fcb[i].filename == dirname) {
//             dirAddr = i;
//             break;
//         }
//     }
//     if (dirAddr == -1) return -1;

//     int OpenFileAddr = -1;
//     for (unsigned short i = 0; i < MAXOPENFILE; i++) {
//         if (!openfilelist[i].topenfile) {
//             OpenFileAddr = i;
//             break;
//         }
//     }
//     if (OpenFileAddr == -1) return -2;

//     openfilelist[OpenFileAddr].fcb = dir->fcb[dirAddr];
//     openfilelist[OpenFileAddr].dir = currentdir;
    
// }

