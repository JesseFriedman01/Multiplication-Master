#include "subform.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SubForm subform;

    //subform.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    subform.setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    subform.show();

    return a.exec();
}
