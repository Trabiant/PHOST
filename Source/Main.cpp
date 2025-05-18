#include "SlidingIndicatorWidget.h"
#include "Window.h"
#include <QFile>
#include <spdlog/spdlog.h>
#include <QApplication>
#include <QApplication>
#include <QStyleFactory>
#include <QFontDatabase>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    // Назначение шрифта по умолчанию
    int id = QFontDatabase::addApplicationFont(":/Inter.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont defaultFont(family);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QStringList styles = QStyleFactory::keys();
    for (const QString &s : styles)
        qDebug() << s;
    Window w;
    w.show();
    return a.exec();
}
