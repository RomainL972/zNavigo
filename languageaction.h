#ifndef LANGUAGEACTION_H
#define LANGUAGEACTION_H

#include <QtWidgets>

class LanguageAction : public QAction
{
    Q_OBJECT
public:
    LanguageAction(QString locale, QString code);
private slots:
    void actionClicked();
signals:
    void changeLocale(QString locale);
private:
    QString codeLocale;
};

#endif // LANGUAGEACTION_H
