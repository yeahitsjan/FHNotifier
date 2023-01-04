#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QFontDatabase>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    // add icon font
    QFontDatabase::addApplicationFont(":/MaterialIconsOutlined-Regular.otf");

    QString _stylesheet;
    QFile _styleFile(":/style.qss");
    if (_styleFile.open(QIODevice::ReadOnly)) {
        QTextStream rd(&_styleFile);
        _stylesheet = rd.readAll();
        _styleFile.close();
    }
    app.setStyleSheet(_stylesheet);

    MainWindow win;
    win.show();
    return app.exec();
}
