#include "widget.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "Game_control.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Gobang_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    Widget w;
    // 设置全局样式表
    QString styleSheet =
        "QMessageBox {"
        "background-color: #B1723C;"  // 背景色
        "color: white;"                // 文本颜色
        "font: bold;"                  // 字体加粗
        "font-family: 宋体;"          // 使用宋体
        "font-size: 12pt;"             // 字体大小
        "}";
    a.setStyleSheet(styleSheet);
    w.show();
    return a.exec();
}
