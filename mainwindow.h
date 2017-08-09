#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define HOME_URL "http://www.lebbadi.fr"

#include <QtWidgets>
#include <QtWebEngineWidgets>
#include "historyitem.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    QWebEngineView* getPage();
    void updateHistory();

public slots:
    void addTab();
    void deleteTab();
    void previousPage();
    void nextPage();
    void reload();
    void goHome();
    void load(QString url="");
    void load(QUrl url);
    void about();
    void updateUrl(int newIndex);
    void changeTitle(QString title);
    void changeUrl(QUrl newUrl);
    void changeIcon(QIcon newIcon);

private:
    QList<QWebEngineView *> *pages;
    QTabWidget *tabs;
    QAction *addTabAction;
    QAction *deleteTabAction;
    QAction *quitAction;
    QAction *nextPageAction;
    QAction *previousPageAction;
    QAction *reloadAction;
    QAction *homePageAction;
    QLineEdit *urlLineEdit;
    QAction *loadUrlAction;
    QAction *aboutQtAction;
    QAction *aboutZNavigoAction;
    QMenu *fileMenu;
    QMenu *navigateMenu;
    QMenu *historyMenu;
    QMenu *aboutMenu;
    QToolBar *navigateToolBar;
    QProgressBar *progress;

};

#endif // MAINWINDOW_H
