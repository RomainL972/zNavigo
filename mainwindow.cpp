#include "mainwindow.h"

MainWindow::MainWindow() : QMainWindow()
{
    setWindowTitle("zNavigo");
    setWindowIcon(QIcon(qApp->applicationDirPath() + "/icones/web.png"));
    pages = new QList<QWebEngineView *>();
    tabs = new QTabWidget();
    setCentralWidget(tabs);

    addTabAction = new QAction(tr("Ajouter un onglet"));
    deleteTabAction = new QAction(tr("Supprimer un onglet"));
    quitAction = new QAction(tr("Quitter"));
    nextPageAction = new QAction(QIcon(qApp->applicationDirPath() + "/icones/suiv.png"), tr("Page suivante"));
    previousPageAction = new QAction(QIcon(qApp->applicationDirPath() + "/icones/prec.png"), tr("Page précédante"));
    reloadAction = new QAction(QIcon(qApp->applicationDirPath() + "/icones/actu.png"), tr("Actualiser"));
    homePageAction = new QAction(QIcon(qApp->applicationDirPath() + "/icones/home.png"), tr("Page d'accueil"));
    urlLineEdit = new QLineEdit(HOME_URL);
    loadUrlAction = new QAction(QIcon(qApp->applicationDirPath() + "/icones/go.png"), tr("Charger la page"));
    aboutQtAction = new QAction(tr("A propos de Qt"));
    aboutZNavigoAction = new QAction(tr("A propos de zNavigo"));

    deleteTabAction->setEnabled(false);
    previousPageAction->setEnabled(false);
    nextPageAction->setEnabled(false);

    addTabAction->setShortcut(QKeySequence(tr("Ctrl+T")));
    deleteTabAction->setShortcut(QKeySequence(tr("Ctrl+W")));
    quitAction->setShortcut(QKeySequence(tr("Ctrl+Q")));
    reloadAction->setShortcut(QKeySequence(tr("Ctrl+R")));

    fileMenu = menuBar()->addMenu(tr("&Fichier"));
    fileMenu->addAction(addTabAction);
    fileMenu->addAction(deleteTabAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);

    navigateMenu = menuBar()->addMenu(tr("&Navigation"));
    navigateMenu->addAction(nextPageAction);
    navigateMenu->addAction(previousPageAction);
    navigateMenu->addAction(reloadAction);
    navigateMenu->addAction(homePageAction);

    historyMenu = menuBar()->addMenu(tr("&Historique"));

    aboutMenu = menuBar()->addMenu(tr("&A propos"));
    aboutMenu->addAction(aboutQtAction);
    aboutMenu->addAction(aboutZNavigoAction);

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
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(aboutZNavigoAction, SIGNAL(triggered()), this, SLOT(about()));
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
}

void MainWindow::nextPage()
{
    if(!(getPage()->history()->canGoForward()))
        return;
    getPage()->history()->forward();
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
    if(!(QRegularExpression("^(http(s)?:\\/\\/.)?(www\\.)?[-a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*)$").match(url.toString()).hasMatch()))
        url = QUrl("https://www.google.com/search?q=" + url.toString());
    else if(QRegularExpression("^(www\\.)?[-a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*)$").match(url.toString()).hasMatch())
        url = QUrl("http://" + url.toString());
    getPage()->load(url);
}

void MainWindow::about()
{
    QMessageBox::information(this, tr("A propos de zNavigo"), tr("zNavigo est un navigateur web que j'ai cree en tant que TP pour <a href='https://openclassrooms.com'>openclassrooms.com</a>"));
}

void MainWindow::updateUrl(int newIndex)
{
    if(pages[0].count()-1 >= newIndex) {
        updateHistory();
        changeUrl(getPage()->url());
    }
}

void MainWindow::changeTitle(QString title)
{
    updateHistory();
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

void MainWindow::changeIcon(QIcon newIcon)
{
    tabs->setTabIcon(tabs->currentIndex(), newIcon);
}

QWebEngineView* MainWindow::getPage()
{
    return pages[0][tabs->currentIndex()];
}

void MainWindow::updateHistory()
{
    historyMenu->clear();
    QList<QWebEngineHistoryItem> items = getPage()->history()->items();
    for(int i = 0; i < items.size(); i++) {
        HistoryItem *menu = new HistoryItem(items[i].title(), items[i].url());
        historyMenu->addMenu(menu);
        connect(menu, SIGNAL(urlClicked(QString)), this, SLOT(load(QString)));
    }
}
