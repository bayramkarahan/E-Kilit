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
#include "keyboard.h"
#include <QDebug>
#include<QPushButton>
#include<QVBoxLayout>


Keyboard::Keyboard(QWidget *parent) :
    QWidget(parent),
    data("Hello QR")//Note: The encoding fails with empty string so I just default to something else. Use the setQRData() call to change this.
{
    QPushButton *loginButton= new QPushButton(this);
    loginButton->setFixedSize(80, 30);
    loginButton->setIconSize(QSize(60,30));
    loginButton->setText("Kilit Aç");
    loginButton->setStyleSheet("Text-align:left");
    loginButton->setFlat(true);
   // loginButton->move(screenSize.width()/2-40,screenSize.height()/2-30);
    // loginButton->setIcon(QIcon(":icons/saveprofile.png"));
    //connect(passwd, SIGNAL(returnPressed()),loginButton,SIGNAL(clicked()));

    connect(loginButton, &QPushButton::clicked, [=]() {

});


    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(loginButton);
    //layout->addWidget(textEdit);
    //layout->addWidget(closeButton);
     //layout->addWidget(qe1);
    setLayout(layout);


}

/*void Keyboard::setQRData(QString data){
    this->data=data;
    update();
}

*/
