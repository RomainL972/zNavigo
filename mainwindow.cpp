#include "mainwindow.h"

MainWindow::MainWindow() : QMainWindow()
{
    setWindowTitle("zNavigo");
    setWindowIcon(QIcon(":/icones/web.png"));
    tabs = new QTabWidget();
    setCentralWidget(tabs);

    addTabAction = new QAction(tr("Add a tab"));
    deleteTabAction = new QAction(tr("Delete a tab"));
    quitAction = new QAction(tr("Quit"));
    nextPageAction = new QAction(QIcon(":/icones/suiv.png"), tr("Next Page"));
    previousPageAction = new QAction(QIcon(":/icones/prec.png"), tr("Previous Page"));
    reloadAction = new QAction(QIcon(":/icones/actu.png"), tr("Reload"));
    homePageAction = new QAction(QIcon(":/icones/home.png"), tr("Home Page"));
    urlLineEdit = new QLineEdit(HOME_URL);
    loadUrlAction = new QAction(QIcon(":/icones/go.png"), tr("Load the page"));
    aboutQtAction = new QAction(tr("About Qt"));
    aboutZNavigoAction = new QAction(tr("About zNavigo"));

    deleteTabAction->setEnabled(false);
    previousPageAction->setEnabled(false);
    nextPageAction->setEnabled(false);

    addTabAction->setShortcut(QKeySequence(tr("Ctrl+T", "Shortcut for add tab")));
    deleteTabAction->setShortcut(QKeySequence(tr("Ctrl+W", "Shortcut for delete tab")));
    quitAction->setShortcut(QKeySequence(tr("Ctrl+Q", "Shortcut for quit")));
    reloadAction->setShortcut(QKeySequence(tr("Ctrl+R", "Shortcut for reload")));

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(addTabAction);
    fileMenu->addAction(deleteTabAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);

    navigateMenu = menuBar()->addMenu(tr("&Navigate"));
    navigateMenu->addAction(nextPageAction);
    navigateMenu->addAction(previousPageAction);
    navigateMenu->addAction(reloadAction);
    navigateMenu->addAction(homePageAction);

    historyMenu = menuBar()->addMenu(tr("&History"));

    languageMenu = menuBar()->addMenu(tr("&Language"));

    englishAction = new LanguageAction("English", "en");
    connect(englishAction, SIGNAL(changeLocale(QString)), this, SLOT(changeTranslation(QString)));
    frenchAction = new LanguageAction("Français", "fr");
    connect(frenchAction, SIGNAL(changeLocale(QString)), this, SLOT(changeTranslation(QString)));
    languageMenu->addAction(englishAction);
    languageMenu->addAction(frenchAction);

    aboutMenu = menuBar()->addMenu(tr("About"));
    aboutMenu->addAction(aboutQtAction);
    aboutMenu->addAction(aboutZNavigoAction);

    navigateToolBar = addToolBar(tr("Navigate"));
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
    WebPage *page = new WebPage();
    tabs->addTab(page, tr("Tab"));
    tabs->setCurrentIndex(tabs->currentIndex()+1);
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
    QMessageBox::information(this, tr("About zNavigo"), tr("zNavigo is my own web browser, I originally create it for an exercice on <a href='https://openclassrooms.com'>openclassrooms.com</a>"));
}

void MainWindow::updateUrl(int newIndex)
{
    updateHistory();
    changeUrl(getPage()->url());
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
    return (QWebEngineView*)tabs->currentWidget();
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

void MainWindow::changeTranslation(QString newLocale)
{
    emit applyTranslation(newLocale);
}
