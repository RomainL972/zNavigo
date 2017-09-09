#include "launcher.h"

Launcher::Launcher(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setOrganizationName("Lebbadi Corporation");
    app.setOrganizationDomain("lebbadi.fr");
    app.setApplicationName("zNavigo");
    app.setApplicationVersion("1.3");

    QSettings settings;

    QString locale = QLocale::system().name().section('_', 0, 0);

    locale = settings.value("locale/preferred", locale).toString();
    translate(locale);

    window = new MainWindow;
    window->show();

    connect(window, SIGNAL(applyTranslation(QString)), this, SLOT(reloadMainWindow(QString)));

    app.exec();
}

void Launcher::reloadMainWindow(QString newLocale)
{
    translate(newLocale);

    int answer = QMessageBox::warning(window, tr("Restart needed"), tr("We need to restart this window to apply the translation, do you want to restart now?"), QMessageBox::Yes | QMessageBox::No);

    switch (answer) {
    case QMessageBox::Yes:
        window->deleteLater();
        window = new MainWindow;
        window->show();
        connect(window, SIGNAL(applyTranslation(QString)), this, SLOT(reloadMainWindow(QString)));
        break;
    case QMessageBox::No:
        QMessageBox::information(window, tr("Restart Later"), tr("You can restart later to apply the translation"));
        break;
    }
}

void Launcher::translate(QString locale)
{
    QSettings settings;
    settings.setValue("locale/preferred", locale);

    QTranslator translator;

    if(translator.load("znavigo_"+locale, ":/translations/")) {
        qApp->installTranslator(&translator);
        qDebug("Translation installed");
    }
    else
        qWarning("Can't load zNavigo translation");

//    QString path = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
//    if(translator.load("qt_fr.qm", QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
//        qApp->installTranslator(&translator);
//    else
//        qWarning("Can't load qt translation");

}
