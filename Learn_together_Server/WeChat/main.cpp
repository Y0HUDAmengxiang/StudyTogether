#include "ckernel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
    QApplication a(argc, argv);
    //WeChatDialog w;
    //w.show();
    Ckernel::GetInstance();

    return a.exec();
}
