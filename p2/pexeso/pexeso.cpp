#include "pexeso.h"

Pexeso::Pexeso(QWidget *parent) : QMainWindow(parent)
{
    m_ngd = new NewGameDialog();
    QObject::connect(m_ngd, SIGNAL(passSettings(int,int,int)),
        this, SLOT(getSettings(int,int,int)));
    m_ngd->show();
}

Pexeso::~Pexeso()
{

}

void Pexeso::getSettings(int players, int theme, int size)
{
    qDebug() << "Create: " << players << ", theme: " << theme << " size: " << size;
}
