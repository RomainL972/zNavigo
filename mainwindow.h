#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QWebEngineView>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

signals:

public slots:
    void addTab();
    void changerTitre(QString titre);
    void changeUrl(QUrl newUrl);
    void setUrl();

private:
    QTabWidget *onglets;
    QProgressBar *progression;
    QLineEdit *url;
};

#endif // MAINWINDOW_H
