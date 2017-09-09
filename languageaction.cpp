#include "languageaction.h"

LanguageAction::LanguageAction(QString locale, QString code) : QAction(locale), codeLocale(code)
{
    connect(this, SIGNAL(triggered()), this, SLOT(actionClicked()));
}

void LanguageAction::actionClicked()
{
    emit changeLocale(codeLocale);
}
