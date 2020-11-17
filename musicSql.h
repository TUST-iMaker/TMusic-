#ifndef MUSICSQL_H
#define MUSICSQL_H

#include "mp3IncludeHeader.h"

//创建mp3数据库，以MySQL进行
void createMp3Db(QStringList path, int size, mp3LinkList mp3List);

#endif // MUSICSQL_H
