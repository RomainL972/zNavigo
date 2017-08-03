#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define HOME_URL "http://www.lebbadi.fr"

#include <QtWidgets>
#include <QWebEngineView>
#include <QWebEngineHistory>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    QWebEngineView* getPage();

public slots:
    void addTab();
    void deleteTab();
    void previousPage();
    void nextPage();
    void reload();
    void goHome();
    void load(QString url="");
    void load(QUrl url);
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
    QMenu *fileBar;
    QMenu *navigateMenu;
    QToolBar *navigateToolBar;
    QProgressBar *progress;

};

#endif // MAINWINDOW_H
