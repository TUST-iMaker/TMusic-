#include "mp3IncludeHeader.h"

Mp3Dec      mp3DecInfo;                                  //mp3解码类分析文件
MP3INFO     mp3Info;                                     //mp3结构体存储文件信息
int         mp3Num = 0;                                  //存储mp3文件序号
int         rowadd = 0, rowminus    = 0, rowout = -1;    //rowadd为下一曲操作变量 rowminus为上一曲操作变量 rowout为全局行数选中记录变量，默认为-1
int         column = 0, infoListVar = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui -> setupUi(this);
    //建立一个状态栏
    QStatusBar * downStBar = statusBar();
    //隐藏标题栏
    setWindowFlags (Qt::CustomizeWindowHint);
    //显示状态栏
    setStatusBar(downStBar);
    //设置状态栏颜色
    downStBar -> setStyleSheet("background-color:#FFFFFF");
    //声明msg字符串作为帮助窗口说明文字，并添加超链接
    QString aboutMsg = "科大音乐 v1.0 by KA <br> My Github: <a href=\"https://github.com/KazaraYouhei\">  KazaraYouhei </a></p><br> My website: <a href=\"http://ypwblog.online\"> ypwblog";
    //建立一个音频播放对象
    QMediaPlayer * TustMusicPlayer = new QMediaPlayer;
    //设置播放列表标题字符串
    QStringList listTableTitle = { " " , "文件名" , "专辑" , "标题" , "音轨" , "其他信息" , "路径"};

    //设置tableWidget列数与头标题
    ui -> tableWidget -> setColumnCount(7);
    ui -> tableWidget -> setHorizontalHeaderLabels(listTableTitle);
    //设置初始行数，等待添加行
    ui -> tableWidget -> setRowCount(0);
    ui -> tableWidget -> horizontalHeader() -> setStretchLastSection(true);
    ui -> tableWidget -> setFocusPolicy(Qt::NoFocus);
    //设置选中行数为蓝色
    ui -> tableWidget -> setStyleSheet("QTableWidget::item:selected { background-color: #C0C0C0 }");
    //选中首行时,不选中表头
    ui -> tableWidget -> horizontalHeader() -> setHighlightSections(false);
    //设置选择行为，以行为单位,并选择单行
    ui -> tableWidget -> setSelectionBehavior(QAbstractItemView::SelectRows);
    ui -> tableWidget -> setSelectionMode(QAbstractItemView::SingleSelection);
    //禁止用户编辑窗格
    ui -> tableWidget -> setEditTriggers(QAbstractItemView::NoEditTriggers);;
    ui -> tableWidget -> setFrameShape(QFrame::NoFrame);
    ui -> tableWidget -> setShowGrid(false);
    //设置tableWidget字体和隔行变色
    ui -> tableWidget -> setFont(QFont("Helvetica"));
    ui -> tableWidget -> setAlternatingRowColors(true);
    ui -> tableWidget -> setPalette(QPalette("#C0C0C0"));
    ui -> tableWidget -> horizontalHeader() -> setStyleSheet("QHeaderView::section{background:#F8F8FF;}");
    //设置tableWidget流畅滚动
    ui -> tableWidget -> setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    //设置searTableWidget列数和头标题
    ui -> searTableWidget -> setColumnCount(7);
    ui -> searTableWidget -> setHorizontalHeaderLabels(listTableTitle);
    //设置选中行数为蓝色
    ui -> searTableWidget -> setStyleSheet("QTableWidget::item:selected { background-color: #C0C0C0 }");
    //选中首行时,不选中表头
    ui -> searTableWidget -> horizontalHeader() -> setHighlightSections(false);
    //设置选择行为，以行为单位并选择单行
    ui -> searTableWidget -> setSelectionBehavior(QAbstractItemView::SelectRows);
    ui -> searTableWidget -> setSelectionMode(QAbstractItemView::SingleSelection);
    //设置初始行数，等待添加行
    ui -> searTableWidget -> setRowCount(0);
    ui -> searTableWidget -> horizontalHeader() -> setStretchLastSection(true);
    ui -> searTableWidget -> setFocusPolicy(Qt::NoFocus);
    //设置searTableWidget字体和隔行变色
    ui -> searTableWidget -> setFont(QFont("Helvetica"));
    ui -> searTableWidget -> setAlternatingRowColors(true);
    ui -> searTableWidget -> setPalette(QPalette("#C0C0C0"));
    ui -> searTableWidget -> horizontalHeader() -> setStyleSheet("QHeaderView::section{background:#F8F8FF;}");
    //设置searTableWidget流畅滚动
    ui -> searTableWidget -> setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    //禁止用户编辑窗格
    ui -> searTableWidget -> setEditTriggers(QAbstractItemView::NoEditTriggers);;
    ui -> searTableWidget -> setFrameShape(QFrame::NoFrame);
    ui -> searTableWidget -> setShowGrid(false);
    //隐藏列表序号
    QHeaderView * mp3SearHeader = ui ->  searTableWidget -> verticalHeader();
    mp3SearHeader -> setHidden(true);

    ui -> downWidget         -> setStyleSheet("background-color:#F5F5F5");
    ui->  lineEdit           -> setPlaceholderText("搜索本地音乐");
    ui -> lineEdit           -> setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px");
    ui -> leftWidget         -> setStyleSheet("background-color:#F5F5F5");
    ui -> titleWidget        -> setStyleSheet("background-color:#F4A460");
    ui -> quitBtn            -> setIcon(QIcon(":/ico/icon/quiticon.png"));
    ui -> quitBtn            -> setIconSize(QSize(60, 60));
    ui -> settingBtn         -> setIcon(QIcon(":/ico/icon/set.png"));
    ui -> settingBtn         -> setIconSize(QSize(45, 45));
    ui -> mainLocalTabWidget -> tabBar() -> hide();
    ui -> mainLocalTabWidget -> setCurrentIndex(0);
    ui -> setWidget          -> setStyleSheet("background-color:#FFFFFF");
    ui -> voiceBtn           -> setIcon(QIcon(":/ico/icon/Voice.png"));
    ui -> voiceBtn           -> setIconSize(QSize(45, 45));
    ui -> voiceSlider        -> setMinimum(0);
    ui -> voiceSlider        -> setMaximum(100);
    ui -> voiceSlider        -> setValue(25);
    ui -> playBtn            -> setIcon(QIcon(":/ico/icon/play.png"));
    ui -> playBtn            -> setIconSize(QSize(70, 70));
    ui -> pauseBtn           -> setIcon(QIcon(":/ico/icon/pause.png"));
    ui -> pauseBtn           -> setIconSize(QSize(70, 70));
    ui -> pauseBtn           -> lower();
    ui -> downBtn            -> setIcon(QIcon(":/ico/icon/down.png"));
    ui -> downBtn            -> setIconSize(QSize(40, 40));
    ui -> upBtn              -> setIcon(QIcon(":/ico/icon/up.png"));
    ui -> upBtn              -> setIconSize(QSize(40, 40));
    ui -> titleLabel         -> setStyleSheet("color:white;");
    ui -> searBtn            -> setIcon(QIcon(":/ico/icon/sea.jpg"));
    ui -> searBtn            -> setIconSize(QSize(20, 20));
    ui -> tabWidgetmusic     -> tabBar() -> hide();
    ui -> tabWidgetmusic     -> setCurrentIndex(0);
    ui -> defaultBtn         -> setIcon(QIcon(":/ico/icon/default.png"));
    ui -> defaultBtn         -> setIconSize(QSize(60, 60));
    ui -> tabWidgetmain      -> tabBar() -> hide();
    ui -> tabWidgetmain      -> setCurrentIndex(0);
    ui -> canBtn             -> setIcon(QIcon(":/ico/icon/quiticon.png"));
    ui -> canBtn             -> setIconSize(QSize(20, 20));
    ui -> helpTabWidget      -> tabBar() -> hide();
    ui -> helpTabWidget      -> setDocumentMode(true);
    ui -> mainLocalTabWidget -> setDocumentMode(true);
    ui -> tabWidgetmusic     -> setDocumentMode(true);
    ui -> tabWidgetmain      -> setDocumentMode(true);
    ui -> tableWidget        -> setColumnWidth(0, 10);

    connect(ui -> webBtn, &QPushButton::clicked, [=](){
        QString webSite = "https://me.csdn.net/qq_16211817?ops_request_misc=%7B%22request%5Fid%22%3A%22160439395119724835823979%22%2C%22scm%22%3A%2220140713.130064515..%22%7D&request_id=160439395119724835823979&biz_id=206&utm_medium=distribute.pc_search_result.none-task-user-null-1-88774999.nonecase&utm_term=kazarayouhei";
        QDesktopServices::openUrl(QUrl(webSite));
    });

    connect(ui -> helpBtn, &QPushButton::clicked, [=](){
        QProcess * myHelpProcess = new QProcess;
        QStringList manuals("D:/code/Music/docs/intro.txt");
        myHelpProcess -> start("notepad.exe", manuals);
    });

    connect(ui -> canBtn, &QPushButton::clicked, [=](){
        ui -> tabWidgetmusic -> setCurrentIndex(0);
        ui -> lineEdit       -> setText("");
    });

//    点击左下角专辑封面会切换到详细页面
//    connect(ui -> defaultPushButton, &QPushButton::clicked, [=](){
//        ui -> defaultPushButton -> lower();
//        ui -> tabWidgetmain     -> setCurrentIndex(1);
//    });

    connect(ui -> searBtn, &QPushButton::clicked, [=](){
        int rowC   = ui -> tableWidget     -> rowCount();
        int serRow = ui -> searTableWidget -> rowCount();
        QString inputRes = ui -> lineEdit -> text();
        QString itemText;
        for (int i = serRow - 1; i >= 0; i--)
        {
            ui -> searTableWidget -> removeRow(--serRow);
        }
        if (rowC != 0)
        {
            for (int i = 0; i < rowC; i++)
            {
                for (int j = 1; j < 4; j++)
                {
                    itemText = ui -> tableWidget -> item(i, j) -> text();
                    if (!inputRes.isEmpty())
                    {
                        bool mate = itemText.contains(inputRes, Qt::CaseInsensitive);
                        if (mate)
                        {
                            int RowCount   = ui -> searTableWidget -> rowCount();
                            ui -> searTableWidget -> insertRow(RowCount);
                            int rowSearRes = ui -> searTableWidget -> rowCount();
                            for (int js = 0; js < 6; js++)
                            {
                                ui -> searTableWidget -> setItem(rowSearRes - 1, js, new QTableWidgetItem(ui -> tableWidget -> item(i, js) -> text()));
                                if(js == 0 || js == 4)
                                {
                                    ui -> searTableWidget -> item(rowSearRes - 1, js) -> setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                                }
                            }
                            break;
                        }
                    }
                }
            }
            if (ui -> searTableWidget -> rowCount() == 0)
            {
                ui -> tabWidgetmusic -> setCurrentIndex(2);
                QString noResText = QString("未找到' %1 ',建议更改关键词再次查找").arg(inputRes);
                ui -> noRes -> setText(noResText);
            }
            else
            {
                ui -> tabWidgetmusic -> setCurrentIndex(1);
            }
            //固定表格长宽
            ui -> searTableWidget -> horizontalHeader() -> setSectionResizeMode(QHeaderView::ResizeToContents);
            ui -> searTableWidget -> verticalHeader()   -> setSectionResizeMode(QHeaderView::Fixed);
            ui -> searTableWidget -> horizontalHeader() -> setMinimumSectionSize(100);
        }
        else
        {
            ui -> tabWidgetmusic -> setCurrentIndex(2);
            QString noResText = QString("未找到' %1 ',建议更改关键词再次查找").arg(inputRes);
            ui -> noRes -> setText(noResText);
        }
    });

    connect(ui -> aboutBtn, &QPushButton::clicked, ui -> actionabout, [=](){
        QMessageBox::about(this, "科大音乐 v1.0", aboutMsg);
    });

    connect(ui -> settingBtn, &QPushButton::clicked, [=](){
        ui -> mainLocalTabWidget -> setCurrentIndex(1);
    });

    connect(ui -> quitBtn, &QPushButton::clicked, [=](){
        this -> close();
    });

    connect(ui -> localBtn, &QPushButton::clicked, [=](){
        ui -> mainLocalTabWidget -> setCurrentIndex(0);
        ui -> tabWidgetmusic     -> setCurrentIndex(0);
    });

    //调节音量滑条
    connect(ui -> voiceSlider, &QSlider::valueChanged, [=]()mutable
    {
        TustMusicPlayer -> setVolume(ui -> voiceSlider -> value());
    });

    //设置按下打开文件动作
    connect(ui -> fileBtn, &QPushButton::clicked, [=]()mutable
    {
        int rowCount = ui -> tableWidget -> rowCount();
        QString choosePath = QFileDialog::getOpenFileName(this, "选择音乐", "C:\\", "*.mp3");              //读取歌曲路径
        int save = 0;
        for (int i = 0; i < rowCount; i++)
        {
            QString pathText = ui -> tableWidget -> item(i, 6) -> text();
            if(pathText == choosePath)
            {
                save++;
            }
            else
            {

            }
        }
        if (save == 0)
        {
            if (choosePath != nullptr)                                                                        //若用户选中了歌曲，就读取歌曲
            {
                QHeaderView   * mp3Header     = ui -> tableWidget -> verticalHeader();
                mp3Header -> setHidden(true);
                QFileInfo       mp3fileInfo(choosePath);
                QString         mp3FileName = mp3fileInfo.fileName();                                         //读取文件名并返回
                const wchar_t * mp3Url      = reinterpret_cast<const wchar_t *>(choosePath.utf16());          //转换路径为宽字节作为getMp3Info函数参数
                mp3Info                     = mp3DecInfo.getMp3Info(mp3Url, mp3Num + 1);                      //通过getMp3Info函数读取mp3文件信息返回
                TustMusicPlayer -> setMedia(QUrl::fromLocalFile(choosePath));                                 //获取路径
                QString     mp3Num_Str = QString::number(rowCount + 1);                                       //转换序号为QString类型
                QStringList mp3FileInfoList;
                //将选中的mp3文件信息读入列表
                mp3FileInfoList << mp3Num_Str << mp3FileName << mp3Info.mp3Album << mp3Info.mp3Name << mp3Info.mp3Trck << mp3Info.mp3Name;
                //固定表格长宽
                ui -> tableWidget -> horizontalHeader() -> setSectionResizeMode(QHeaderView::Stretch);
                ui -> tableWidget -> verticalHeader()   -> setSectionResizeMode(QHeaderView::Stretch);
                //动态添加行
                int monofileRowCount = ui -> tableWidget -> rowCount();
                ui -> tableWidget -> insertRow(monofileRowCount);
                //将列表信息填入表格
                for (; column < 6; column++)
                {
                    ui -> tableWidget -> setItem(rowCount, column, new QTableWidgetItem(mp3FileInfoList[infoListVar++]));
                    if(column == 0 || column == 4)
                    {
                        ui -> tableWidget -> item(rowCount, column) -> setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    }
                }
                ui -> tableWidget -> setItem(rowCount, column, new QTableWidgetItem(choosePath));
                //固定表格长宽
                ui -> tableWidget -> horizontalHeader() -> setSectionResizeMode(QHeaderView::ResizeToContents);
                ui -> tableWidget -> verticalHeader()   -> setSectionResizeMode(QHeaderView::Fixed);
                ui -> tableWidget -> horizontalHeader() -> setMinimumSectionSize(100);
                //重置循环变量
                column = 0, infoListVar = 0;
                //更改状态栏信息提示成功
                downStBar -> showMessage(tr("导入歌曲成功!"));
            }
            else                                                                                             //若用户为选中歌曲，不做操作
            {

            }
        }
    });

    //从指定路径数据库导入全部歌曲
    connect(ui -> secBtn, &QPushButton::clicked, [=]()mutable
    {
        int rowCount = ui -> tableWidget -> rowCount();
        mp3LinkList   mp3FileLinkList;                                                                     //声明存放mp3信息链表
        //对行设置操作
        QHeaderView * mp3Header   = ui ->  tableWidget -> verticalHeader();
        QString       SQLFileName = QFileDialog::getExistingDirectory(this, tr("选择文件夹"), "C:/");       //选择文件夹
        mp3Header -> setHidden(true);                                                                      //隐藏行号
        if(SQLFileName != nullptr)
        {
            QDir        mp3FileDir(SQLFileName);                                                           //设置文件过滤器
            //从文件过滤器扫描指定文件
            QStringList mp3MameFilters;
            mp3MameFilters << "*.mp3";
            //mp3Files负责记录文件名称，filesname负责记录文件路径，以循环字符串形式连接
            QStringList mp3Files        = mp3FileDir.entryList(mp3MameFilters, QDir::Files|QDir::Readable, QDir::Name);
            QStringList mp3FilesName    = mp3FileDir.entryList(mp3MameFilters, QDir::Files|QDir::Readable, QDir::Name);
            int mp3Size = mp3Files.size();
            for (int mp3FilePath = 0; mp3FilePath < mp3Size; mp3FilePath++)
            {
                mp3FilesName[mp3FilePath] = SQLFileName + "/" + mp3Files[mp3FilePath];
            }
            QStringList mp3LoopFiles;
            for(int i = 0; i < rowCount; i++)
            {
                QString pathText = ui -> tableWidget -> item(i, 6) -> text();
                for(int j = 0; j < mp3Size; j++)
                {
                    if(pathText == mp3FilesName[j])
                    {

                    }
                    else
                    {
                        mp3LoopFiles << mp3FilesName[j];
                    }
                }
            }
            qDebug() << mp3LoopFiles;
            //创建mp3文件链表
            createMp3Db(mp3LoopFiles, mp3LoopFiles.size(), mp3FileLinkList);
            //固定表格长宽
            ui -> tableWidget -> horizontalHeader() -> setSectionResizeMode(QHeaderView::Stretch);
            ui -> tableWidget -> verticalHeader()   -> setSectionResizeMode(QHeaderView::Stretch);
            //添加行
            ui -> tableWidget -> setRowCount(rowCount + mp3Files.size());
            //声明mp3SizeLoop变量,作为行号变量
            int mp3SizeLoop = mp3Size - 1;
            //循环负责写入数据
            for (int SQLoop = 0; SQLoop < mp3Size; SQLoop++)
            {
                int SQLResLoop = 0;
                mp3InfoNode mp3FileInfoNode = mp3FileLinkList.printMp3Info(SQLoop + 1);
                QStringList resInfoList;
                QString     mp3Num_Str = QString::number(rowCount + mp3FileInfoNode.tmp_Num.toInt());
                resInfoList << mp3Num_Str << mp3FileInfoNode.tmp_FileName << mp3FileInfoNode.tmp_Album << mp3FileInfoNode.tmp_Name << mp3FileInfoNode.tmp_Trck << mp3FileInfoNode.tmp_OTHER << mp3FileInfoNode.tmp_path;
                if(mp3FileInfoNode.tmp_Num != -1)
                {
                    int SQLRow = 0;
                    for (; SQLRow < 7; SQLRow++)
                    {
                        ui -> tableWidget -> setItem(mp3Num_Str.toInt() - 1, SQLRow, new QTableWidgetItem(resInfoList[SQLResLoop++]));
                    }
                    SQLResLoop = 0, SQLRow = 0;
                }
                else
                {
                    break;
                }
                mp3SizeLoop--;
            }
            //固定表格长宽
            ui        -> tableWidget -> horizontalHeader() -> setSectionResizeMode(QHeaderView::ResizeToContents);
            ui        -> tableWidget -> horizontalHeader() -> setMinimumSectionSize(100);
            downStBar -> showMessage(tr("导入播放列表成功!"));
            mp3LoopFiles.clear();
        }
        else
        {

        }
    });

    bool sortTableUpOrDown = true;
    connect(ui -> tableWidget -> horizontalHeader(), &QHeaderView::sectionClicked, [&](int column){
        if(sortTableUpOrDown)
        {
            ui-> tableWidget -> sortItems(column, Qt::AscendingOrder);
            sortTableUpOrDown = false;
        }
        else
        {
            ui-> tableWidget -> sortItems(column, Qt::DescendingOrder);
            sortTableUpOrDown = true;
        }
    });

    bool sortSearUpOrDown = true;
    connect(ui -> searTableWidget -> horizontalHeader(), &QHeaderView::sectionClicked, [&](int column){
        if(sortSearUpOrDown)
        {
            ui-> searTableWidget -> sortItems(column, Qt::AscendingOrder);
            sortSearUpOrDown = false;
        }
        else
        {
            ui-> searTableWidget -> sortItems(column, Qt::DescendingOrder);
            sortSearUpOrDown = true;
        }
    });

    //双击歌曲播放
    connect(ui -> tableWidget, &QTableWidget::cellDoubleClicked, [=](int doubleRow)
    {
        QTableWidgetItem * doubleItem = new QTableWidgetItem;
        doubleItem       = ui-> tableWidget -> item(doubleRow, 6);
        QString PlayPath = doubleItem -> text();                    //转换歌曲路径
        TustMusicPlayer -> setMedia(QUrl::fromLocalFile(PlayPath));
        TustMusicPlayer -> setVolume(100);                          //设置声音和播放路径
        TustMusicPlayer -> play();                                  //播放歌曲
        downStBar       -> showMessage(tr("歌曲正在播放"));           //更新状态栏
        rowminus = doubleRow;                           //返回歌曲行信息供上一曲下一曲菜单使用
        rowadd   = doubleRow;
        rowout   = doubleRow;
        ui -> pauseBtn -> raise();
        ui -> defaultBtn -> setIcon(QIcon(":/ico/icon/music.jpg"));
        ui -> defaultBtn -> setIconSize(QSize(65, 65));
    });

    //播放歌曲操作
    connect(ui -> playBtn , &QPushButton::clicked, [=]()mutable
    {
        QTableWidgetItem * playItem = new QTableWidgetItem;
        if (rowout != -1)                                        //如果行数被初始化过（不为-1）进行操作
        {
            playItem = ui -> tableWidget -> item(rowout, 6);
            QString playPath = playItem -> text();
            TustMusicPlayer -> setMedia(QUrl::fromLocalFile(playPath));
            TustMusicPlayer -> setVolume(100);
            TustMusicPlayer -> play();
            downStBar       -> showMessage(tr("歌曲正在播放"));
            ui -> pauseBtn -> raise();
        }
        else
        {
            if ((ui -> tableWidget -> rowCount()) != 0)          //如果行数没被初始化过，即未双选过歌曲并且列表有歌曲，默认播放第一首歌曲
            {
                playItem = ui -> tableWidget -> item(0, 6);
                QString playPath = playItem -> text();
                TustMusicPlayer -> setMedia(QUrl::fromLocalFile(playPath));
                TustMusicPlayer -> setVolume(100);
                TustMusicPlayer -> play();
                downStBar       -> showMessage(tr("歌曲正在播放"));
                ui -> pauseBtn -> raise();
            }
            else                                                 //如果列表没有歌曲，那么该操作无效
            {

            }
        }
    });

    //暂停播放歌曲操作
    connect(ui -> pauseBtn, &QPushButton::clicked,[=]()
    {
        TustMusicPlayer -> pause();
        downStBar       -> showMessage(tr("暂停播放"));
        ui -> playBtn -> raise();
    });

    //上一曲操作
    connect(ui -> upBtn, &QPushButton::clicked, [=]()mutable
    {
        if ((ui -> tableWidget -> rowCount()) != 0)
        {
            QTableWidgetItem * upItem = new QTableWidgetItem;
            if (rowminus > 0)                                             //列表不是第一首歌曲执行以下操作
            {
                upItem = ui -> tableWidget -> item(--rowminus, 6);         //播放上一曲
            }
            else                                                          //列表是第一首歌曲播放最后一首歌曲
            {
                upItem   =  ui -> tableWidget -> item((ui -> tableWidget -> rowCount()) - 1, 6);
                rowminus = (ui -> tableWidget -> rowCount()) - 1;          //重置变量
            }
            QString upPlayPath = upItem -> text();
            TustMusicPlayer      -> setMedia(QUrl::fromLocalFile(upPlayPath));
            TustMusicPlayer      -> setVolume(100);
            TustMusicPlayer      -> play();
            ui -> playBtn -> raise();
            downStBar            -> showMessage(tr("歌曲正在播放"));
            ui -> pauseBtn -> raise();
        }
        else
        {

        }
    });

    //下一曲操作
    connect(ui -> downBtn, &QPushButton::clicked,[=]()mutable
    {
        if ((ui -> tableWidget -> rowCount()) != 0)
        {
            QTableWidgetItem * downItem = new QTableWidgetItem;
            if (rowadd < (ui -> tableWidget -> rowCount()) - 1)
            {
                downItem = ui -> tableWidget -> item(++rowadd, 6);
            }
            else
            {
                downItem = ui -> tableWidget -> item(0, 6);
                rowadd = 0;
            }
            QString downPlayPath = downItem -> text();
            TustMusicPlayer -> setMedia(QUrl::fromLocalFile(downPlayPath));
            TustMusicPlayer -> setVolume(100);
            TustMusicPlayer -> play();
            ui -> pauseBtn -> raise();
            downStBar -> showMessage(tr("歌曲正在播放"));
        }
        else
        {

        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
