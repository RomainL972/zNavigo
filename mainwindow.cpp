#include "mainwindow.h"

MainWindow::MainWindow() : QMainWindow()
{
    onglets = new QTabWidget();
    setCentralWidget(onglets);

    QAction *ajouterOnglet = new QAction(tr("Ajouter un onglet"));
    QAction *supprimerOnglet = new QAction(tr("Supprimer un onglet"));
    QAction *quitter = new QAction(tr("Quitter"));

    QAction *pageSuivante = new QAction(QIcon("icones/suiv.png"), tr("Page suivante"));
    QAction *pagePrecedante = new QAction(QIcon("icones/prec.png"), tr("Page précédante"));
    QAction *actualiser = new QAction(QIcon("icones/actu.png"), tr("Actualiser"));
    QAction *pageAccueil = new QAction(QIcon("icones/home.png"), tr("Page d'accueil"));
    url = new QLineEdit();
    QAction *chargerUrl = new QAction(QIcon("icones/go.png"), tr("Charger la page"));

    QMenu *menuFichier = menuBar()->addMenu(tr("&Fichier"));
    menuFichier->addAction(ajouterOnglet);
    menuFichier->addAction(supprimerOnglet);
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
    toolBarNavigation->addAction(actualiser);
    toolBarNavigation->addAction(pageAccueil);
    toolBarNavigation->addWidget(url);
    toolBarNavigation->addAction(chargerUrl);

    progression = new QProgressBar();
    statusBar()->addWidget(progression, 1);

    addTab();

    connect(chargerUrl, SIGNAL(triggered()), this, SLOT(setUrl()));
    connect(actualiser, SIGNAL(triggered()), this, SLOT(setUrl()));
}

void MainWindow::addTab()
{
    QWebEngineView *page = new QWebEngineView();
    onglets->addTab(page, "Onglet");
    connect(page, SIGNAL(loadProgress(int)), progression, SLOT(setValue(int)));
    connect(page, SIGNAL(titleChanged(QString)), this, SLOT(changerTitre(QString)));
    connect(page, SIGNAL(urlChanged(QUrl)), this, SLOT(changeUrl(QUrl)));

    page->load(QUrl("https://www.google.com.au"));
}

void MainWindow::changerTitre(QString titre)
{
    onglets->setTabText(onglets->currentIndex(), titre);
}

void MainWindow::changeUrl(QUrl newUrl)
{
    url->setText(newUrl.toString());
}

void MainWindow::setUrl()
{
    QWidget *currentWidget = onglets->currentWidget();
    QWebEngineView *page = currentWidget->findChild<QWebEngineView *>();
    page->load(QUrl(url->text()));
}
