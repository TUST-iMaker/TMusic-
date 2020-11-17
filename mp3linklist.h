//mp3链表类，存放mp3文件信息

#ifndef MP3LINKLIST_H
#define MP3LINKLIST_H

#include "mp3IncludeHeader.h"

//临时存储MP3文件信息结构体
typedef struct mp3InfoNode
{
    QString tmp_Num;               //存放序号
    QString tmp_FileName;          //存放文件名
    QString tmp_Album;             //专辑
    QString tmp_Name;              //名称
    QString tmp_Trck;              //音轨
    QString tmp_OTHER;             //其他信息
    QString tmp_path;              //路径
}mp3InfoNode;

//存放节点结构体
typedef struct LNode
{
    mp3InfoNode tmp_Info;             //存放临时信息结构体
    LNode       *next;
}LNode, * LinkList;

//mp3文件链表
class mp3LinkList
{
public:
    mp3LinkList();
    void TailInsertLinkList(mp3InfoNode tmp_Info, int posiLinkList);      //头插法插入链表函数
    mp3InfoNode printMp3Info(int SQLVar);
    ~mp3LinkList();
private:
    LNode *head;
};

#endif // MP3LINKLIST_H
