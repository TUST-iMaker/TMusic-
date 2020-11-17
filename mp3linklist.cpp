#include "mp3IncludeHeader.h"

mp3LinkList::mp3LinkList()
{
    head =  new LNode;
    head -> next =nullptr;
}

//头插法创建链表
void mp3LinkList::TailInsertLinkList(mp3InfoNode tmp_Info, int posiLinkList)
{
    LNode * mp3LNodeInfo;
    int searchPosi = 0;
    mp3LNodeInfo = head;
    while(mp3LNodeInfo != nullptr && searchPosi < posiLinkList - 1)
    {
        mp3LNodeInfo = mp3LNodeInfo -> next;
        searchPosi++;
    }
    LNode * tmpFileInfo = new LNode;
    (tmpFileInfo -> tmp_Info).tmp_Num        = tmp_Info.tmp_Num;
    (tmpFileInfo -> tmp_Info).tmp_FileName   = tmp_Info.tmp_FileName;
    (tmpFileInfo -> tmp_Info).tmp_Album      = tmp_Info.tmp_Album;
    (tmpFileInfo -> tmp_Info).tmp_Name       = tmp_Info.tmp_Name;
    (tmpFileInfo -> tmp_Info).tmp_Trck       = tmp_Info.tmp_Trck;
    (tmpFileInfo -> tmp_Info).tmp_OTHER      = tmp_Info.tmp_OTHER;
    (tmpFileInfo -> tmp_Info).tmp_path       = tmp_Info.tmp_path;
    tmpFileInfo  -> next                     = mp3LNodeInfo -> next;
    mp3LNodeInfo -> next                     = tmpFileInfo;
}

mp3InfoNode mp3LinkList::printMp3Info(int SQLVar)
{
    LNode * mp3PrintLNodeInfo;
    mp3InfoNode printNode;
    int printSearchPos = 0;
    mp3PrintLNodeInfo = head;
    while(mp3PrintLNodeInfo != nullptr && printSearchPos < SQLVar)
    {
        mp3PrintLNodeInfo = mp3PrintLNodeInfo -> next;
        printSearchPos++;
    }
    if(mp3PrintLNodeInfo == nullptr)
    {
        mp3InfoNode error;
        error.tmp_Num = -1;
        return error;
    }
    printNode.tmp_Num         = (mp3PrintLNodeInfo -> tmp_Info).tmp_Num;
    printNode.tmp_FileName    = (mp3PrintLNodeInfo -> tmp_Info).tmp_FileName;
    printNode.tmp_Album       = (mp3PrintLNodeInfo -> tmp_Info).tmp_Album;
    printNode.tmp_Name        = (mp3PrintLNodeInfo -> tmp_Info).tmp_Name;
    printNode.tmp_Trck        = (mp3PrintLNodeInfo -> tmp_Info).tmp_Trck;
    printNode.tmp_OTHER       = (mp3PrintLNodeInfo -> tmp_Info).tmp_OTHER;
    printNode.tmp_path        = (mp3PrintLNodeInfo -> tmp_Info).tmp_path;
    mp3PrintLNodeInfo -> next = mp3PrintLNodeInfo  -> next;
    return printNode;
}

mp3LinkList::~mp3LinkList(){

}

