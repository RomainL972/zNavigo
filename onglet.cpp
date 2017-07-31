#include "onglet.h"

Onglet::Onglet() : QWidget()
{
    m_progressionChargement = new QProgressBar();
    m_progressionChargement->setValue(0);
    m_barreUrl = new QLineEdit();
    m_page = new QWebEngineView();
    m_page->show();
    m_chargerPage = new QPushButton(tr("Charger"));

    QGridLayout *layoutHaut = new QGridLayout();
    layoutHaut->addWidget(new QLabel(tr("Progression :")), 0, 0);
    layoutHaut->addWidget(m_progressionChargement, 0, 1);
    layoutHaut->addWidget(new QLabel(tr("URL :")), 1, 0);
    layoutHaut->addWidget(m_barreUrl, 1, 1);
    layoutHaut->addWidget(m_chargerPage, 1, 2);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(layoutHaut);
    layout->addWidget(m_page);

    this->setLayout(layout);

    connect(m_chargerPage, SIGNAL(clicked()), this, SLOT(chargerPage()));
    connect(m_page, SIGNAL(loadProgress(int)), m_progressionChargement, SLOT(setValue(int)));
}

void Onglet::chargerPage()
{
    m_page->load(m_barreUrl->text());
}
