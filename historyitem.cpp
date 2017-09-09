#include "historyitem.h"

HistoryItem::HistoryItem(QString title, QUrl url) : QMenu(title)
{
    if(title.isEmpty())
        setTitle(url.toString());
    m_action = addAction(url.toString());
    QFont font;
    font.setUnderline(true);
    m_action->setFont(font);

    connect(m_action, SIGNAL(triggered(bool)), this, SLOT(sendUrlClicked()));
}

void HistoryItem::sendUrlClicked()
{
    emit urlClicked(m_action->text());
}
