/**
  * @file mainwindow.cpp
  * @brief Define all the functions of the MainWindow class
  * @author Romain Lebbadi-Breteau
  * @version 1.0
  * @date 02/08/2017
  */
#include "mainwindow.h"
/**
  @def HOME_URL
  @brief contains the default home url
  */
#define HOME_URL "http://www.lebbadi.fr"

MainWindow::MainWindow() : QMainWindow()
{
    pages = new QList<QWebEngineView *>();
    onglets = new QTabWidget();
    setCentralWidget(onglets);

    QAction *ajouterOnglet = new QAction(tr("Ajouter un onglet"));
    supprimerOnglet = new QAction(tr("Supprimer un onglet"));
    QAction *quitter = new QAction(tr("Quitter"));

    pageSuivante = new QAction(QIcon("icones/suiv.png"), tr("Page suivante"));
    pagePrecedante = new QAction(QIcon("icones/prec.png"), tr("Page précédante"));
    QAction *actualiser = new QAction(QIcon("icones/actu.png"), tr("Actualiser"));
    QAction *pageAccueil = new QAction(QIcon("icones/home.png"), tr("Page d'accueil"));
    url = new QLineEdit(HOME_URL);
    QAction *chargerUrl = new QAction(QIcon("icones/go.png"), tr("Charger la page"));

    QMenu *menuFichier = menuBar()->addMenu(tr("&Fichier"));
    menuFichier->addAction(ajouterOnglet);
    menuFichier->addAction(supprimerOnglet);
    supprimerOnglet->setEnabled(false);
    menuFichier->addSeparator();
    menuFichier->addAction(quitter);

    QMenu *menuNavigation = menuBar()->addMenu(tr("&Navigation"));
    menuNavigation->addAction(pagePrecedante);
    menuNavigation->addAction(pageSuivante);
    menuNavigation->addAction(actualiser);
    menuNavigation->addAction(pageAccueil);

    QToolBar *toolBarNavigation = addToolBar(tr("Navigation"));
    toolBarNavigation->addAction(pagePrecedante);
    toolBarNavigation->addAction(pageSuivante);
    pagePrecedante->setEnabled(false);
    pageSuivante->setEnabled(false);
    toolBarNavigation->addAction(actualiser);
    toolBarNavigation->addAction(pageAccueil);
    toolBarNavigation->addWidget(url);
    toolBarNavigation->addAction(chargerUrl);

    progression = new QProgressBar();
    statusBar()->addWidget(progression, 1);

    addTab();

    connect(chargerUrl, SIGNAL(triggered()), this, SLOT(setUrl()));
    connect(actualiser, SIGNAL(triggered()), this, SLOT(actualiser()));
    connect(ajouterOnglet, SIGNAL(triggered()), this, SLOT(addTab()));
    connect(onglets, SIGNAL(currentChanged(int)), this, SLOT(updateUrl(int)));
    connect(pageAccueil, SIGNAL(triggered()), this, SLOT(goHome()));
    connect(quitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(pagePrecedante, SIGNAL(triggered(bool)), this, SLOT(pageBefore()));
    connect(pageSuivante, SIGNAL(triggered(bool)), this, SLOT(pageAfter()));
    connect(supprimerOnglet, SIGNAL(triggered()), this, SLOT(deleteTab()));
    connect(url, SIGNAL(returnPressed()), this, SLOT(setUrl()));
}

void MainWindow::addTab()
{
    QWebEngineView *page = new QWebEngineView();
    onglets->addTab(page, tr("Onglet"));
    onglets->setCurrentIndex(onglets->currentIndex()+1);
    pages->insert(onglets->currentIndex(), page);
    url->setText(HOME_URL);
    connect(page, SIGNAL(loadProgress(int)), progression, SLOT(setValue(int)));
    connect(page, SIGNAL(titleChanged(QString)), this, SLOT(changerTitre(QString)));
    connect(page, SIGNAL(urlChanged(QUrl)), this, SLOT(changeUrl(QUrl)));

    setUrl();
    if(onglets->count() >= 2)
        supprimerOnglet->setEnabled(true);
}

void MainWindow::changerTitre(QString titre)
{
    onglets->setTabText(onglets->currentIndex(), titre);
}

void MainWindow::changeUrl(QUrl newUrl)
{
    QWebEngineView *page = pages[0][onglets->currentIndex()];
    if(page->history()->canGoBack())
        pagePrecedante->setEnabled(true);
    if(page->history()->canGoForward())
        pageSuivante->setEnabled(true);
    url->setText(newUrl.toString());
}

void MainWindow::setUrl()
{
    QWebEngineView *page;
    int currentIndex = onglets->currentIndex();
    page = pages[0][currentIndex];
    page->load(QUrl(url->text()));
}

void MainWindow::updateUrl(int newIndex)
{
    if(pages[0].count()-1 >= newIndex) {
        QWebEngineView *page;
        page = pages[0][newIndex];
        url->setText(page->url().toString());
    }
}

void MainWindow::goHome()
{
    url->setText(HOME_URL);
    setUrl();
}

void MainWindow::pageBefore()
{
    QWebEngineView *page = pages[0][onglets->currentIndex()];
    if(!(page->history()->canGoBack()))
        return;
    page->history()->back();
    pageSuivante->setEnabled(true);
    if(!(page->history()->canGoBack()))
        pagePrecedante->setEnabled(false);
}

void MainWindow::pageAfter()
{
    QWebEngineView *page = pages[0][onglets->currentIndex()];
    if(!(page->history()->canGoForward()))
        return;
    page->history()->forward();
    pagePrecedante->setEnabled(true);
    if(!(page->history()->canGoForward()))
        pageSuivante->setEnabled(false);
}

void MainWindow::deleteTab()
{
    pages->removeAt(onglets->currentIndex());
    onglets->removeTab(onglets->currentIndex());
    if(onglets->count() <= 1)
        supprimerOnglet->setEnabled(false);
}

void MainWindow::actualiser()
{
    url->setText(pages[0][onglets->currentIndex()]->url().toString());
    setUrl();
}
