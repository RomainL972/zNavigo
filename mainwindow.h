/**
  * @file mainwindow.h
  * @brief Contain the MainWindow class
  * @author Romain Lebbadi-Breteau
  * @version 1.0
  * @date 02/08/2017
  *
  * This file contains the main window (MainWindow)
  *
  */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QWebEngineView>
#include <QWebEngineHistory>

/**
 * @brief The MainWindow class
 *
 * This window is open while the programm is running and inherit QMainWindow.
 * It contains the differents tabs, the tool bars File and Navigation and a status bar with a QProgressBar in it
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * @brief MainWindow is the constructor
     *
     * The constructor will build the tool bars, the statusbar and initialize the first tab
     *
     */
    MainWindow();

signals:

public slots:
    /**
     * @brief addTab create a new tab
     *
     * This slot is called at the beginning of the programm and when the user click on "add a tab"
     *
     */
    void addTab();
    /**
     * @brief changerTitre change the tab title
     * @param titre is the new title
     *
     * This slot is called each time the web page title change
     *
     */
    void changerTitre(QString titre);
    /**
     * @brief changeUrl change the url written
     * @param newUrl is the new url
     *
     * This slot is called when the web page url change
     *
     */
    void changeUrl(QUrl newUrl);
    /**
     * @brief setUrl load an url
     *
     * This slot is called when the user want to load a new url
     *
     */
    void setUrl();
    /**
     * @brief updateUrl change the url written
     * @param newIndex is the new tab index
     *
     * This slot is caled when the user change tab to write the current url in the url QLineEdit
     *
     */
    void updateUrl(int newIndex);
    /**
     * @brief goHome call setUrl() with HOME_URL as new url
     */
    void goHome();
    /**
     * @brief pageAfter load the next page in history if possible
     */
    void pageAfter();
    /**
     * @brief pageBefore load the previous page in history if possible
     */
    void pageBefore();
    /**
     * @brief deleteTab delete the current tab
     */
    void deleteTab();
    /**
     * @brief actualiser reload the current page by using setUrl()
     */
    void actualiser();

private:
    /**
     * @brief onglets contains the tabs
     */
    QTabWidget *onglets;
    /**
     * @brief progression show the page load progression
     */
    QProgressBar *progression;
    /**
     * @brief url is the QLineEdit with the url
     */
    QLineEdit *url;
    /**
     * @brief pages contains the different web pages opens
     */
    QList<QWebEngineView *> *pages;
    /**
     * @brief pagePrecedante is the button to load the previous url
     */
    QAction *pagePrecedante;
    /**
     * @brief pageSuivante is the button to load the next url
     */
    QAction *pageSuivante;
    /**
     * @brief supprimerOnglet is the button to delete a tab
     */
    QAction *supprimerOnglet;
};

#endif // MAINWINDOW_H
