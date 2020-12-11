/*****************************************************************************
 *   Copyright (C) 2020 by Bayram KARAHAN                                    *
 *   <bayramk@gmail.com>                                                     *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 3 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .          *
 *****************************************************************************/
#include "qrwidget.h"
#include <QPainter>
#include <QDebug>
#include <qrencode.h>

QRWidget::QRWidget(QWidget *parent) :
    QWidget(parent),
    data("Hello QR")//Note: The encoding fails with empty string so I just default to something else. Use the setQRData() call to change this.
{
}

void QRWidget::setQRData(QString data){
    this->data=data;
    update();
}

void QRWidget::paintEvent(QPaintEvent *pe){
    QPainter painter(this);
    //NOTE: I have hardcoded some parameters here that would make more sense as variables.
    QRcode *qr = QRcode_encodeString(data.toStdString().c_str(), 1, QR_ECLEVEL_L, QR_MODE_8, 0);
    if(0!=qr){
        QColor fg("black");
        QColor bg("white");
        painter.setBrush(bg);
        painter.setPen(Qt::NoPen);
        painter.drawRect(0,0,width(),height());
        painter.setBrush(fg);
        const int s=qr->width>0?qr->width:1;
        const double w=width();
        const double h=height();
        const double aspect=w/h;
        const double scale=((aspect>1.0)?h:w)/s;
        for(int y=0;y<s;y++){
            const int yy=y*s;
            for(int x=0;x<s;x++){
                const int xx=yy+x;
                const unsigned char b=qr->data[xx];
                if(b &0x01){
                    const double rx1=x*scale, ry1=y*scale;
                    QRectF r(rx1, ry1, scale, scale);
                    painter.drawRects(&r,1);
                }
            }
        }
        QRcode_free(qr);
    }
    else{
        QColor error("red");
        painter.setBrush(error);
        painter.drawRect(0,0,width(),height());
        qDebug()<<"QR FAIL: "<< strerror(errno);
    }
    qr=0;
}
