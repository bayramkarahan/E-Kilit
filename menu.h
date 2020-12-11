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
#ifndef MENU_H
#define MENU_H

#include<QWidgetAction>
#include<QGridLayout>

QMenu *MainWindow::ayarMenu()
{   QMenu *menu = new QMenu(this);
    int e=32;
      int b=30;
QSize screenSize = qApp->screens()[0]->size();
      QPushButton *restartButton= new QPushButton(this);
      restartButton->setFixedSize(e*4, b);
      restartButton->setIconSize(QSize(e*4,b));
      restartButton->setText("Yeniden Başlat");
      restartButton->setStyleSheet("Text-align:left");
      restartButton->setFlat(true);
      // restartButton->move(screenSize.width()/2+40,100-0);
       restartButton->setIcon(QIcon(":icons/redo.png"));
      connect(restartButton, &QPushButton::clicked, [=]() {
           //QMenu *ayarMenus=ayarMenu();
          //kilitMenus->exec(mapToGlobal(ayarButton->pos()-QPoint(-60,30)));
        system("systemctl reboot");

});

      QPushButton *poweroffButton= new QPushButton(this);
      poweroffButton->setFixedSize(e*4, b);
      poweroffButton->setIconSize(QSize(e*4,b));
     poweroffButton->setText("Kapat");
      poweroffButton->setStyleSheet("Text-align:left");
      poweroffButton->setFlat(true);
       //poweroffButton->move(screenSize.width()/2+40,screenSize.height()/2-60);
       poweroffButton->setIcon(QIcon(":icons/close.png"));
      connect(poweroffButton, &QPushButton::clicked, [=]() {
          // QMenu *ayarMenus=ayarMenu();
          //kilitMenus->exec(mapToGlobal(ayarButton->pos()-QPoint(-60,30)));
        system("systemctl poweroff");

});

      QPushButton *infoButton= new QPushButton(this);
      infoButton->setFixedSize(e*4, b);
      infoButton->setIconSize(QSize(e*4,b));
     infoButton->setText("Bilgi");
      infoButton->setStyleSheet("Text-align:left");
      infoButton->setFlat(true);
     //  infoButton->move(screenSize.width()/2+40,screenSize.height()/2-60);
       infoButton->setIcon(QIcon(":icons/about.png"));
      connect(infoButton, &QPushButton::clicked, [=]() {
          /// QMenu *ayarMenus=ayarMenu();
         // kilitMenus->exec(mapToGlobal(ayarButton->pos()-QPoint(-60,30)));
          QMessageBox msgBox;
                         msgBox.setText(
                                   "\n"
                                   "Tahtaların QR Kod ile güvenli bir şekilde kullanmak için yazılmış uygulamadır.."
                                   "\nBu uygulamayı kullanmaktan doğabilecek her türlü hukuki sorumluluğu kullanıcı kabul etmiş sayılır."
                                   "\n"
                                   "\n"
                                   "\n\t         Bayram KARAHAN"
                                   "\n\tBilişim Teknolojileri Öğretmeni");
                    msgBox.setWindowTitle("E-Kilit 1.0");
                    msgBox.setInformativeText("İstek ve önerileriniz için;"
                                              "\nE-Posta: bayramk@gmail.com"
                                              "\nwww.bayramkarahan.blogspot.com"
                                              "\n");

                         msgBox.setStandardButtons(QMessageBox::Ok);
                         Qt::WindowFlags flags = 0;
                         flags |= Qt::Window;
                         flags |= Qt::X11BypassWindowManagerHint;
                         flags |= Qt::CustomizeWindowHint;
                         this->setWindowFlags(flags);

                          flags = 0;
                         flags |= Qt::Window;

                          //  QColorDialog abc;
                         msgBox.setWindowFlags(flags);



                         //msgBox.setDefaultButton(QMessageBox::Save);
                         msgBox.exec();
                      //   kalemEgitim();
                         flags |= Qt::Window;
                         flags |= Qt::X11BypassWindowManagerHint;
                         flags |= Qt::WindowStaysOnTopHint;
                     this->setWindowFlags(flags);
                     show();
});

    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
    layout->setContentsMargins(5, 5, 5,5);
   // layout->setVerticalSpacing(0);
  //  layout->setColumnMinimumWidth(0, 37);

   //  layout->addWidget(kalemKapatButton, 7,1,1,1);
    layout->addWidget(restartButton, 2,1,1,1,Qt::AlignCenter);
    layout->addWidget(poweroffButton, 4, 1,1,1,Qt::AlignCenter);
    layout->addWidget(infoButton, 6, 1,1,1,Qt::AlignCenter);

   // layout->addWidget(new QLabel("<font size=2>Yeniden Başlat</font>"),2,2,1,1,Qt::AlignLeft);
   // layout->addWidget(new QLabel("<font size=2>Kapat</font>"),4,2,1,1,Qt::AlignLeft);
    //layout->addWidget(new QLabel("<font size=2>Bilgi</font>"),6,2,1,1,Qt::AlignLeft);


  //  layout->setColumnStretch(6, 255);

    // add a widget action to the context menu
    auto wa = new QWidgetAction(this);
  //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);

   //  menu->setStyleSheet("QMenu { width: auto; height: auto; }");
   return menu;
}


QMenu *MainWindow::kilitMenu()
{   QMenu *menu = new QMenu(this);
int en=40;
int boy=30;
    QPushButton *birButton= new QPushButton;
    birButton->setFixedSize(en, boy);
    birButton->setIconSize(QSize(en,boy));
    birButton->setText("1");
    birButton->setStyleSheet("Text-align:center");
    //birButton->setFlat(true);
    // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

    connect(birButton, &QPushButton::clicked, [=]() {

    passwd->setText(passwd->text()+"1");

    });

    QPushButton *ikiButton= new QPushButton;
    ikiButton->setFixedSize(en, boy);
    ikiButton->setIconSize(QSize(en,boy));
    ikiButton->setText("2");
    ikiButton->setStyleSheet("Text-align:center");
   // ikiButton->setFlat(true);
    // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

    connect(ikiButton, &QPushButton::clicked, [=]() {
        passwd->setText(passwd->text()+"2");


    });


    QPushButton *ucButton= new QPushButton;
    ucButton->setFixedSize(en, boy);
    ucButton->setIconSize(QSize(en,boy));
    ucButton->setText("3");
    ucButton->setStyleSheet("Text-align:center");
   // ucButton->setFlat(true);
    // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

    connect(ucButton, &QPushButton::clicked, [=]() {
        passwd->setText(passwd->text()+"3");

        // menu->close();

    });
    /***************************4***************/
    QPushButton *dortButton= new QPushButton;
    dortButton->setFixedSize(en, boy);
    dortButton->setIconSize(QSize(en,boy));
    dortButton->setText("4");
    dortButton->setStyleSheet("Text-align:center");
   // dortButton->setFlat(true);
    // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

    connect(dortButton, &QPushButton::clicked, [=]() {
        passwd->setText(passwd->text()+"4");


    });

    /***************************5***************/
    QPushButton *besButton= new QPushButton;
    besButton->setFixedSize(en, boy);
    besButton->setIconSize(QSize(en,boy));
    besButton->setText("5");
    besButton->setStyleSheet("Text-align:center");
    //besButton->setFlat(true);
    // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

    connect(besButton, &QPushButton::clicked, [=]() {
        passwd->setText(passwd->text()+"5");


    });

    /***************************6***************/
    QPushButton *altiButton= new QPushButton;
    altiButton->setFixedSize(en, boy);
    altiButton->setIconSize(QSize(en,boy));
    altiButton->setText("6");
    altiButton->setStyleSheet("Text-align:center");
   // altiButton->setFlat(true);
    // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

    connect(altiButton, &QPushButton::clicked, [=]() {
        passwd->setText(passwd->text()+"6");


    });

    /***************************7***************/
    QPushButton *yediButton= new QPushButton;
    yediButton->setFixedSize(en, boy);
    yediButton->setIconSize(QSize(en,boy));
    yediButton->setText("7");
    yediButton->setStyleSheet("Text-align:center");
    //yediButton->setFlat(true);
    // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

    connect(yediButton, &QPushButton::clicked, [=]() {
        passwd->setText(passwd->text()+"7");


    });

    /***************************8***************/
    QPushButton *sekizButton= new QPushButton;
    sekizButton->setFixedSize(en, boy);
    sekizButton->setIconSize(QSize(en,boy));
    sekizButton->setText("8");
    sekizButton->setStyleSheet("Text-align:center");
    //sekizButton->setFlat(true);
    // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

    connect(sekizButton, &QPushButton::clicked, [=]() {

        passwd->setText(passwd->text()+"8");

    });

    /***************************9***************/
    QPushButton *dokuzButton= new QPushButton;
    dokuzButton->setFixedSize(en, boy);
    dokuzButton->setIconSize(QSize(en,boy));
    dokuzButton->setText("9");
    dokuzButton->setStyleSheet("Text-align:center");
   // dokuzButton->setFlat(true);
    // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

    connect(dokuzButton, &QPushButton::clicked, [=]() {
        passwd->setText(passwd->text()+"9");


    });

    /***************************0***************/
    QPushButton *sifirButton= new QPushButton;
    sifirButton->setFixedSize(en, boy);
    sifirButton->setIconSize(QSize(en,boy));
    sifirButton->setText("0");
    sifirButton->setStyleSheet("Text-align:center");
    //sifirButton->setFlat(true);
    // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

    connect(sifirButton, &QPushButton::clicked, [=]() {

        passwd->setText(passwd->text()+"0");

    });

    /***************************backspace***************/
    QPushButton *geriSilButton= new QPushButton;
    geriSilButton->setFixedSize(en, boy);
    geriSilButton->setIconSize(QSize(en,boy));
    geriSilButton->setText("<-");
    geriSilButton->setStyleSheet("Text-align:center");
    //geriSilButton->setFlat(true);
    // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

    connect(geriSilButton, &QPushButton::clicked, [=]() {
        QString str=passwd->text();
        str.chop(1);

        passwd->setText(str);


    });

    /***************************Enter***************/
    enterButton= new QPushButton;
    enterButton->setFixedSize(en, boy);
    enterButton->setIconSize(QSize(en,boy));
    enterButton->setText("Giriş");
    enterButton->setStyleSheet("Text-align:center");
   // enterButton->setFlat(true);
    // kilitButton->setIcon(QIcon(":icons/saveprofile.png"));

    connect(enterButton, &QPushButton::clicked, [=]() {

        if(passwd->text()==QString::number(qrnumber))
        {
            //QMessageBox::information(this,"E-Ağ 3.0","Şifre Doğru");
        exit(0);
        }else
        {
           // QMessageBox::information(this,"E-Ağ 3.0","Şifre Yanlış");

            sifre->setText("Şifre Yanlış");
        }

    });


    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
    layout->setContentsMargins(5, 5, 5,5);
   // layout->setVerticalSpacing(0);
     // layout->setColumnMinimumWidth(0, 10);
    layout->addWidget(birButton, 1,1,1,1);
    layout->addWidget(ikiButton, 1,2,1,1);
    layout->addWidget(ucButton, 1,3,1,1);
    layout->addWidget(dortButton, 2,1,1,1);
    layout->addWidget(besButton, 2,2,1,1);
    layout->addWidget(altiButton, 2,3,1,1);
    layout->addWidget(yediButton, 3,1,1,1);
    layout->addWidget(sekizButton, 3,2,1,1);
    layout->addWidget(dokuzButton, 3,3,1,1);
    layout->addWidget(sifirButton, 4,1,1,1);
    layout->addWidget(geriSilButton, 4,2,1,1);
    layout->addWidget(enterButton, 4,3,1,1);

    // layout->addWidget(new QLabel("<font size=1>Ayarları Kaydet</font>"),6,1,1,1,Qt::AlignHCenter);
    // layout->setColumnStretch(6, 255);

    // add a widget action to the context menu
    auto wa = new QWidgetAction(this);
    //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);

    menu->setStyleSheet("QMenu { width: 142 px; height: 148 px; }");
    return menu;
}

#endif // MENU_H
