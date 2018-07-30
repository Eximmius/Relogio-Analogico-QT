#include <QApplication>
#include <QPushButton>
#include <QLayout>
#include <QtWidgets>

#include "analogclock.h"

QPushButton *adiantar_min, *atrasar_min;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    AnalogClock clock;
    //Cria e ajusta botões para adiantar e atrasar relógio
    adiantar_min = new QPushButton ("Adiantar");
    adiantar_min->setAutoRepeatInterval(20);        //signal é repetido se mantém pressionado a cada 20ms
    adiantar_min->setAutoRepeatDelay(1000);         //repetição começa após 1s
    adiantar_min->setAutoRepeat(true);
    adiantar_min->setStyleSheet("background-color: rgb(153,102,255);");

    atrasar_min = new QPushButton ("Atrasar");
    atrasar_min->setAutoRepeatInterval(20);
    atrasar_min->setAutoRepeatDelay(1000);
    atrasar_min->setAutoRepeat(true);
    atrasar_min->setStyleSheet("background-color: rgb(153,102,255);");

    QObject::connect(adiantar_min,SIGNAL(clicked()), &clock, SLOT(ajustar()));  //Conecta Signal ao Slot
    QObject::connect(atrasar_min,SIGNAL(clicked()), &clock, SLOT(ajustar()));

    //Layout Horizontal para adicionar os botões
    QHBoxLayout *hLay = new QHBoxLayout;
    hLay->addStretch();
    hLay->addWidget(adiantar_min);
    hLay->addWidget(atrasar_min);
    hLay->addStretch();

    //Layout Vertical para Adicionar Layout Horizontal e Relógio
    QVBoxLayout *vLay = new QVBoxLayout;
    vLay->addWidget(&clock);
    vLay->addLayout(hLay);

    //Cria e Ajusta Janela Principal
    QWidget *mainWindow = new QWidget;
    mainWindow->setStyleSheet("background-color: rgb(0,0,0);");
    mainWindow->setLayout(vLay);
    mainWindow->resize(500,500);
    mainWindow->setWindowTitle("Relógio");
    mainWindow->show();

    return app.exec();
}
