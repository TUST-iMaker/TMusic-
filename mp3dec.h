//对mp3文件进行分析，以结构体返回mp3歌手，标题等信息

#ifndef MP3DEC_H
#define MP3DEC_H

#include "mp3IncludeHeader.h"

class Mp3Dec;                   //Mp3解码类

//存放标签帧帧头结构体
typedef struct
{
    int beginNum;
    int endNum;
    QString FrameId;
} frameIDS;

//存放MP3文件的详细信息
typedef struct
{
    QString mp3Url;             //存放这首歌的详细路径
    QString mp3Name;            //歌名  TIT2
    QString mp3Album;           //专辑  TALB
    QString mp3Singer;          //歌手  TPE1
    QString mp3Trck;            //歌曲图片存放路径
    QString mp3Apic;            //歌曲备注
    int     number;             //歌曲编号
} MP3INFO;

class Mp3Dec
{
public:
    Mp3Dec();  
    FILE          *fp;
    QString       mp3Path;           //存放mp3文件路径
    unsigned char ID3Header[3];      //存放标签头ID3
    unsigned char Header_size[4];    //存放标签大小
    unsigned char FrameId[4];        //存放帧标识
    unsigned int  mp3_TagSize;       //标签帧大小
    unsigned char frameSize[4];      //存放该帧内容的大小 
    unsigned int  framecount;        //计算出帧内容的大小
    MP3INFO getMp3Info(const wchar_t *url, int songNumber); //获取mp3音乐文件信息
    QMap<QString, frameIDS> m_IDmap; //遍历mp3文件
    ~Mp3Dec(){}
};

#endif // MP3DEC_H
