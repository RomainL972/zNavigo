#ifndef ONGLET_H
#define ONGLET_H

#include <QWidget>
#include <QProgressBar>
#include <QWebEngineView>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>

class Onglet : public QWidget
{
    Q_OBJECT
public:
    Onglet();

public slots:
    void chargerPage();

private:
    QProgressBar *m_progressionChargement;
    QLineEdit *m_barreUrl;
    QWebEngineView *m_page;
    QPushButton *m_chargerPage;
};

#endif // ONGLET_H
