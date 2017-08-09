#include "historyitem.h"

HistoryItem::HistoryItem(QString title, QUrl url)
{
    if(title.isEmpty())
        title = url.toString();
    m_title = title;
    m_url = url.toString();
    setTitle(m_title);
    m_action = addAction(m_url);
    connect(m_action, SIGNAL(triggered(bool)), this, SLOT(sendUrlClicked()));
}

void HistoryItem::sendUrlClicked()
{
    emit urlClicked(m_url);
}
