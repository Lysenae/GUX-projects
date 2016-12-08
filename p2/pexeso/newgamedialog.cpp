#include "newgamedialog.h"

NewGameDialog::NewGameDialog()
{
    m_main_lt    = new QVBoxLayout();

    m_players_lt = new QHBoxLayout();
    m_theme_lt   = new QHBoxLayout();
    m_size_lt    = new QHBoxLayout();
    m_btns_lt    = new QHBoxLayout();

    m_players_lbl = new QLabel(tr("Players"));
    m_theme_lbl   = new QLabel(tr("Theme"));
    m_size_lbl    = new QLabel(tr("Size"));

    m_players_cb = new QComboBox();
    m_theme_cb   = new QComboBox();
    m_size_cb    = new QComboBox();

    m_create_btn = new QPushButton(tr("Create"));
    m_cancel_btn = new QPushButton(tr("Cancel"));

    m_btns_spacer = new QSpacerItem(10, 10, QSizePolicy::Expanding,
        QSizePolicy::Minimum);

    m_players_lt->addWidget(m_players_lbl);
    m_players_lt->addWidget(m_players_cb);

    m_theme_lt->addWidget(m_theme_lbl);
    m_theme_lt->addWidget(m_theme_cb);

    m_size_lt->addWidget(m_size_lbl);
    m_size_lt->addWidget(m_size_cb);

    m_btns_lt->addSpacerItem(m_btns_spacer);
    m_btns_lt->addWidget(m_create_btn);
    m_btns_lt->addWidget(m_cancel_btn);

    m_main_lt->addLayout(m_players_lt);
    m_main_lt->addLayout(m_size_lt);
    m_main_lt->addLayout(m_theme_lt);
    m_main_lt->addLayout(m_btns_lt);

    setGeometry(0, 0, 250, 165);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setLayout(m_main_lt);

    QObject::connect(m_create_btn, SIGNAL(clicked()), this, SLOT(onCreateClicked()));
    QObject::connect(m_cancel_btn, SIGNAL(clicked()), this, SLOT(reject()));

    populateComboBoxes();
}

void NewGameDialog::populateComboBoxes()
{
    m_players_cb->addItem("1", QVariant(1));
    m_players_cb->addItem("2", QVariant(2));
    m_players_cb->addItem("3", QVariant(3));
    m_players_cb->addItem("4", QVariant(4));
    m_players_cb->setCurrentIndex(0);

    m_theme_cb->addItem("Animals", QVariant(1));
    m_theme_cb->addItem("Nature", QVariant(2));
    m_theme_cb->addItem("Fruit", QVariant(3));
    m_theme_cb->setCurrentIndex(0);

    m_size_cb->addItem("4x4", QVariant(16));
    m_size_cb->addItem("5x4", QVariant(20));
    m_size_cb->addItem("6x4", QVariant(24));
    m_size_cb->addItem("6x6", QVariant(36));
    m_theme_cb->setCurrentIndex(0);
}

void NewGameDialog::onCreateClicked()
{
    int players = m_players_cb->currentData().toInt();
    int theme   = m_theme_cb->currentData().toInt();
    int size    = m_size_cb->currentData().toInt();
    emit passSettings(players, theme, size);
    accept();
}
