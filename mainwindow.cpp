/**
  * @file mainwindow.cpp
  * @brief Define all the functions of the MainWindow class
  * @author Romain Lebbadi-Breteau
  * @version 1.1
  * @date 02/08/2017
  */
#include "mainwindow.h"

MainWindow::MainWindow() : QMainWindow()
{
    pages = new QList<QWebEngineView *>();
    tabs = new QTabWidget();
    setCentralWidget(tabs);

    addTabAction = new QAction(tr("Ajouter un onglet"));
    deleteTabAction = new QAction(tr("Supprimer un onglet"));
    quitAction = new QAction(tr("Quitter"));
    nextPageAction = new QAction(QIcon("icones/suiv.png"), tr("Page suivante"));
    previousPageAction = new QAction(QIcon("icones/prec.png"), tr("Page précédante"));
    reloadAction = new QAction(QIcon("icones/actu.png"), tr("Actualiser"));
    homePageAction = new QAction(QIcon("icones/home.png"), tr("Page d'accueil"));
    urlLineEdit = new QLineEdit(HOME_URL);
    loadUrlAction = new QAction(QIcon("icones/go.png"), tr("Charger la page"));

    deleteTabAction->setEnabled(false);
    previousPageAction->setEnabled(false);
    nextPageAction->setEnabled(false);

    fileBar = menuBar()->addMenu(tr("&Fichier"));
    fileBar->addAction(addTabAction);
    fileBar->addAction(deleteTabAction);
    fileBar->addSeparator();
    fileBar->addAction(quitAction);

    navigateMenu = menuBar()->addMenu(tr("&Navigation"));
    navigateMenu->addAction(nextPageAction);
    navigateMenu->addAction(previousPageAction);
    navigateMenu->addAction(reloadAction);
    navigateMenu->addAction(homePageAction);

    navigateToolBar = addToolBar(tr("Navigation"));
    navigateToolBar->addAction(previousPageAction);
    navigateToolBar->addAction(nextPageAction);
    navigateToolBar->addAction(reloadAction);
    navigateToolBar->addAction(homePageAction);
    navigateToolBar->addWidget(urlLineEdit);
    navigateToolBar->addAction(loadUrlAction);

    progress = new QProgressBar();
    statusBar()->addWidget(progress, 1);

    addTab();

    connect(addTabAction, SIGNAL(triggered()), this, SLOT(addTab()));
    connect(deleteTabAction, SIGNAL(triggered()), this, SLOT(deleteTab()));
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(previousPageAction, SIGNAL(triggered(bool)), this, SLOT(previousPage()));
    connect(nextPageAction, SIGNAL(triggered(bool)), this, SLOT(nextPage()));
    connect(reloadAction, SIGNAL(triggered()), this, SLOT(reload()));
    connect(homePageAction, SIGNAL(triggered()), this, SLOT(goHome()));
    connect(loadUrlAction, SIGNAL(triggered()), this, SLOT(load()));
    connect(urlLineEdit, SIGNAL(returnPressed()), this, SLOT(load()));
    connect(tabs, SIGNAL(currentChanged(int)), this, SLOT(updateUrl(int)));
}

void MainWindow::addTab()
{
    QWebEngineView *page = new QWebEngineView();
    tabs->addTab(page, tr("Onglet"));
    tabs->setCurrentIndex(tabs->currentIndex()+1);
    pages->insert(tabs->currentIndex(), page);
    connect(page, SIGNAL(loadProgress(int)), progress, SLOT(setValue(int)));
    connect(page, SIGNAL(titleChanged(QString)), this, SLOT(changeTitle(QString)));
    connect(page, SIGNAL(urlChanged(QUrl)), this, SLOT(changeUrl(QUrl)));
    connect(page, SIGNAL(iconChanged(QIcon)), this, SLOT(changeIcon(QIcon)));

    goHome();
    if(tabs->count() >= 2)
        deleteTabAction->setEnabled(true);
}

void MainWindow::deleteTab()
{
    if(tabs->count() == 1)
        return;
    pages->removeOne(getPage());
    tabs->removeTab(tabs->currentIndex());
    if(tabs->count() == 1)
        deleteTabAction->setEnabled(false);
}

void MainWindow::previousPage()
{
    if(!(getPage()->history()->canGoBack()))
        return;
    getPage()->history()->back();
    nextPageAction->setEnabled(true);
    if(!(getPage()->history()->canGoBack()))
        previousPageAction->setEnabled(false);
}

void MainWindow::nextPage()
{
    if(!(getPage()->history()->canGoForward()))
        return;
    getPage()->history()->forward();
    previousPageAction->setEnabled(true);
    if(!(getPage()->history()->canGoForward()))
        nextPageAction->setEnabled(false);
}

void MainWindow::reload()
{
    load(getPage()->url());
}

void MainWindow::goHome()
{
    load(HOME_URL);
}

void MainWindow::load(QString url)
{
    if(url == "")
        url = urlLineEdit->text();
    load(QUrl(url));
}

void MainWindow::load(QUrl url)
{
    getPage()->load(url);
}

void MainWindow::updateUrl(int newIndex)
{
    if(pages[0].count()-1 >= newIndex) {
        changeUrl(getPage()->url());
    }
}

void MainWindow::changeTitle(QString title)
{
    tabs->setTabText(tabs->currentIndex(), title);
}

void MainWindow::changeUrl(QUrl newUrl)
{
    if(getPage()->history()->canGoBack())
        previousPageAction->setEnabled(true);
    else
        previousPageAction->setEnabled(false);
    if(getPage()->history()->canGoForward())
        nextPageAction->setEnabled(true);
    else
        nextPageAction->setEnabled(false);
    urlLineEdit->setText(newUrl.toString());
}

QWebEngineView* MainWindow::getPage()
{
    return pages[0][tabs->currentIndex()];
}

void MainWindow::changeIcon(QIcon newIcon)
{
    tabs->setTabIcon(tabs->currentIndex(), newIcon);
}
