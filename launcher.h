#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QObject>
#include <QApplication>
#include <QTranslator>
#include <QString>
#include "mainwindow.h"

class Launcher : public QObject
{
    Q_OBJECT
public:
    Launcher(int argc, char *argv[]);
    void translate(QString locale);

signals:

public slots:
    void reloadMainWindow(QString newLocale);

private:
    MainWindow *window;
};

#endif // LAUNCHER_H
