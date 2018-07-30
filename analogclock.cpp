/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>

#include "analogclock.h"

AnalogClock::AnalogClock(QWidget *parent, int ajuste_min, int ajuste_hor)
    : QWidget(parent), m_ajuste_min(ajuste_min),m_ajuste_hor(ajuste_hor)
{
    //Cria Timer para dar Update (PaintEvent)
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);
    setWindowTitle(tr("Relógio"));
}

void AnalogClock::paintEvent(QPaintEvent *)
{
    //Pontos Poligono Hora e Minuto
    static const QPoint hourHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -40)
    };
    static const QPoint minuteHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -70)
    };

    //Cores dos ponteiros
    QColor hourColor(127, 0, 127);
    QColor minuteColor(0, 127, 127, 191);
    QColor secondColor(255, 255, 255);

    //Obtém hora atual
    QTime time = QTime::currentTime();

    //Ajuste Widget Relógio
    int side = qMin(width(), height());
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);

    //Desenha Ponteiro e Riscos da Hora
    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);

    painter.save();         //salva Painter na Stack
    painter.rotate(30.0 * ((time.hour()+m_ajuste_hor + (time.minute()+m_ajuste_min/4.0) / 60.0)));   //rotaciona a hora
    painter.drawConvexPolygon(hourHand, 3); //desenha ponteiro hora
    painter.restore();      //restora Painter

    painter.setPen(hourColor);

    for (int i = 0; i < 12; ++i) {
        painter.drawLine(88, 0, 96, 0); //desenha 'risquinhos' hora
        painter.rotate(30.0);
    }
    //Desenha números das horas relógio
    painter.save();
    painter.drawText(-85,4,"9");
    painter.drawText(78,4,"3");
    painter.drawText(-3,83,"6");
    painter.drawText(-7,-75,"12");
    painter.restore();

    //Desenha Ponteiro Minutos
    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);

    painter.save();
    painter.rotate(6.0 * (time.minute()+m_ajuste_min/4.0 + time.second() / 60.0));
    painter.drawConvexPolygon(minuteHand, 3);
    painter.restore();

    painter.setPen(minuteColor);

    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter.drawLine(92, 0, 96, 0);     //Risquinhos minutos
        painter.rotate(6.0);
    }

    painter.setPen(Qt::NoPen);
    painter.setPen(secondColor);

    painter.save();
    painter.rotate((time.second()+30.0)*6.0);
    painter.drawLine(0,85,0,0);             //ponteiro segundos
    painter.restore();
}

void AnalogClock::ajustar(){
    //Verifica qual Botão foi Clicado
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    QString ajuste = clickedButton->text();

    if (ajuste == "Adiantar"){
        m_ajuste_min++;
        if (m_ajuste_min>=(60*4)){
            m_ajuste_min=0;
            m_ajuste_hor++;
        }
    } else if (ajuste == "Atrasar"){
        m_ajuste_min--;
        if (m_ajuste_min<=(-60*4)){
            m_ajuste_min=0;
            m_ajuste_hor--;
        }
    }
}
