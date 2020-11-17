#include "mp3IncludeHeader.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //声明一个启动画面对象，设置图像并显示
    QSplashScreen * TUSTSplash = new QSplashScreen;
    TUSTSplash -> setPixmap(QPixmap(":/ico/icon/QTCOVER.jpg"));
    TUSTSplash -> show();
    MainWindow w;
    w.setStyleSheet("background-color:#F8F8FF");
    w.show();
    QThread::msleep(2000);
    TUSTSplash -> finish(&w);
    delete TUSTSplash;
    return a.exec();
}
