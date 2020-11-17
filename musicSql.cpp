#include "mp3IncludeHeader.h"

void createMp3Db(QStringList path, int size, mp3LinkList mp3List)
{
    mp3InfoNode  mp3DbInfoNode;
    Mp3Dec       mp3DbDec;
    MP3INFO      mp3DbInfo;
    QSqlDatabase TUSTMusic = QSqlDatabase::addDatabase("QMYSQL");
    TUSTMusic.setHostName("localhost");         //主机名
    TUSTMusic.setPort(3306);                    //端口
    TUSTMusic.setDatabaseName("tumusic");       //数据库名
    TUSTMusic.setUserName("root");              //用户名
    TUSTMusic.setPassword("sonodaumi3");        //密码
    if(!TUSTMusic.open("root","sonodaumi3"))
    {
        qDebug() << "error!";
    }
    QSqlQuery dbQuery(TUSTMusic);
    QString dbStr = "CREATE TABLE inform(musicid int , fn VARCHAR(100),album VARCHAR(100), title VARCHAR(100), track VARCHAR(100), oth VARCHAR(100), pathmu VARCHAR(100))";
    dbQuery.exec(dbStr);
    TUSTMusic.transaction();
    for(int i = 0; i < size; i++)
    {
        QFileInfo QFI(path[i]);
        QString mp3FileName = QFI.fileName();
        const wchar_t * url = reinterpret_cast<const wchar_t *>(path[i].utf16());                  //转换路径为宽字节作为getMp3Info函数参数
        mp3DbInfo = mp3DbDec.getMp3Info(url, i + 1);                                               //通过getMp3Info函数读取mp3文件信息返回给结构体
        dbQuery.prepare("insert into inform(musicID, fn ,album, title, track, oth, pathmu) values(?,?,?,?,?,?,?)");
        dbQuery.addBindValue(i+1);
        dbQuery.addBindValue(mp3FileName);
        dbQuery.addBindValue(mp3DbInfo.mp3Album);
        dbQuery.addBindValue(mp3DbInfo.mp3Name);
        dbQuery.addBindValue(mp3DbInfo.mp3Trck);
        dbQuery.addBindValue(mp3DbInfo.mp3Name);
        dbQuery.addBindValue(path[i]);
        dbQuery.exec();
    }
    TUSTMusic.commit();
    dbQuery.exec("select * from inform");
    while(dbQuery.next())
    {
        int i = 1;
        mp3DbInfoNode.tmp_Num      = dbQuery.value("musicid").toString();
        mp3DbInfoNode.tmp_FileName = dbQuery.value("fn").toString();
        mp3DbInfoNode.tmp_Album    = dbQuery.value("album").toString();
        mp3DbInfoNode.tmp_Name     = dbQuery.value("title").toString();
        mp3DbInfoNode.tmp_Trck     = dbQuery.value("track").toString();
        mp3DbInfoNode.tmp_OTHER    = dbQuery.value("oth").toString();
        mp3DbInfoNode.tmp_path     = dbQuery.value("pathmu").toString();
        mp3List.TailInsertLinkList(mp3DbInfoNode, i++);
    }
}




