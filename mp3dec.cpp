#include "mp3IncludeHeader.h"

Mp3Dec::Mp3Dec()
{

}

MP3INFO Mp3Dec::getMp3Info(const wchar_t *url, int songNumber)
{
    mp3Path = QString::fromWCharArray(url);                     //提取MP3文件详细地址
    fp = _wfopen(url, L"rb");                                   //地址可能有过长字符，采取宽字节读取函数打开,读写方式为只读二进制
    if (fp == NULL)                                             //对文件不存在的调试信息
    {
        qDebug() << "文件不存在";
    }
    fseek(fp, 0, SEEK_SET);
    fread(&ID3Header, 1, 3, fp);                                //读入ID3Header
    unsigned int i = 10;                                        //从第十一个字节读入数据（前10个为标签头）
    MP3INFO mp3Save;                                            //实例化一个结构体接收MP3文件信息
    mp3Save.mp3Url = mp3Path;
    mp3Save.number = songNumber;
    fseek(fp, 6, SEEK_SET);
    fread(&Header_size, 1, 4, fp);                              //读取标签大小
    //计算标签大小
    mp3_TagSize = ((Header_size[0] & 0xff) << 21) | ((Header_size[1] & 0xff) << 14) | ((Header_size[2] & 0xff) << 7) | (Header_size[3] & 0xff);
    while (i < (mp3_TagSize - 10))
    {
        frameIDS fID;                                           //声明标签帧结构体
        fseek(fp, i, SEEK_SET);
        fread(&FrameId, 1, 4, fp);                              //读取标签帧
        fseek(fp, 4+i, SEEK_SET);
        fread(&frameSize, 1, 4, fp);                            //读取帧内容的大小
        framecount = frameSize[0] * 0x1000000 + frameSize[1] * 0x10000 + frameSize[2] * 0x100 + frameSize[3];     //计算帧内容的大小
        QString frame;
        frame = FrameId[0];
        for (int j = 1; j < 4; j++)
        {
            frame += FrameId[j];
        }                                                        //文件读取帧标识存入FrameId，转为QString存入frame
        fID.beginNum = i + 10;                                   //帧数据起始位置
        fID.FrameId = frame;                                     //帧内容大小存入framesize
        i = 10 + i + framecount;                                 //下一个标签帧起始位置
        fID.endNum = i;                                          //得到标签帧结束位置
        m_IDmap.insert(frame, fID);                              //使用容器赋值
        int lenth = fID.endNum - fID.beginNum;                   //得到数据长度
        if (fID.FrameId == "TIT2")                               //标题
        {
            QFile file(mp3Path);                                 //使用QFile操作文件
            if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
            {
                 qDebug() << "打开文件错误";
            }
            QTextStream QTstream(&file);                                 //使用QTextStream操作文件
            QTstream.seek(fID.beginNum + 1);                             //定位到标签帧开头
            QString all = QTstream.readLine(lenth - 1);                   //读取标签帧到all中
            QTextCodec *code = QTextCodec::codecForName("GBK");
            QString ua = code -> toUnicode(all.toLocal8Bit().data());    //使用GBK字符集支持中文
            QString GBKc = ua.mid(0, (int)(lenth / 2 - 1));              //出现多余数据，取前面部分
            mp3Save.mp3Name = GBKc;                                      //得到歌名
            file.close();
         }
        else if (fID.FrameId == "TPE1" )                                 //歌手
        {
            QFile file(mp3Path);
            if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
            {
                 qDebug() << "打开文件错误";
            }
            QTextStream stream(&file);
            stream.seek(fID.beginNum + 1);
            QString all = stream.readLine(lenth - 1);
            QTextCodec *codec = QTextCodec::codecForName("GBK");
            QString ua = codec -> toUnicode(all.toLocal8Bit().data());
            QString GBKc = ua.mid(0, (int)(lenth / 2 - 1));
            mp3Save.mp3Singer = GBKc;
            file.close();
        }
        else if (fID.FrameId == "TALB" )                                 //专辑
        {
            QFile file(mp3Path);
            if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
            {
                 qDebug() << "打开文件错误";
            }
            QTextStream stream(&file);
            stream.seek(fID.beginNum + 1);
            QString all= stream.readLine(lenth - 1);
            QTextCodec *codec = QTextCodec::codecForName("GBK");
            QString ua = codec -> toUnicode(all.toLocal8Bit().data());
            QString GBKc = ua.mid(0, (int)(lenth / 2 - 1));
            mp3Save.mp3Album = GBKc;
            file.close();
        }
        else if (fID.FrameId == "TRCK" )                                 //音轨
        {
            QFile file(mp3Path);
            if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
            {
                 qDebug() << "打开文件错误";
            }
            QTextStream stream(&file);
            stream.seek(fID.beginNum + 1);
            QString all = stream.readLine(lenth - 1);
            QTextCodec *codec = QTextCodec::codecForName("GBK");
            QString ua = codec -> toUnicode(all.toLocal8Bit().data());
            QString GBKc = ua.mid(0, (int)(lenth / 2 - 1));
            mp3Save.mp3Trck = GBKc;
            file.close();
                 if(frame == "APIC")                                     //遇到备注即跳出循环
                 {
                     break;
                 }
        }
    }
    return mp3Save;
}
