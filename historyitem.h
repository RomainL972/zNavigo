#ifndef HISTORYITEM_H
#define HISTORYITEM_H

#include <QtWidgets>

class HistoryItem : public QMenu
{
    Q_OBJECT
public:
    HistoryItem(QString title, QUrl url);

signals:
    void urlClicked(QString url);

private slots:
    void sendUrlClicked();

private:
    QAction *m_action;
};

#endif // HISTORYITEM_H
