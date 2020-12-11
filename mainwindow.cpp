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
#include "mainwindow.h"
#include<qrencode.h>
#include<QColor>
#include<qrwidget.h>
#include <random>
#include "QDateTime"
#include<QDebug>
#include<QLineEdit>
#include<QPushButton>
#include<QLabel>
#include<QMessageBox>
#include<QDesktopWidget>
#include<QRect>
#include<QInputDialog>
#include<QTimer>
#include<QCoreApplication>
#include<QSize>
#include <QApplication>
#include<QScreen>
#include<QPixmap>
#include<QPalette>
#include<QFile>
#include<QDir>
#include<QRegularExpression>
#include<filecrud.h>
#include<menu.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)//    ui(new Ui::MainWindow)
{
     localDir=QDir::homePath()+"/";
     QSize screenSize = qApp->screens()[0]->size();
     QTimer *timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(zamanlama()));
     timer->start(1000);

     int boyut=100;

/*************************************************/
    //this->resize(500,400);
    this->resize(screenSize.width(),screenSize.height());
    this->move(0,0);

   //  setAttribute(Qt::WA_TranslucentBackground, true);

   this->setWindowFlags(Qt::Window|
                        Qt::FramelessWindowHint |
                      Qt::WindowStaysOnTopHint
                        |Qt::X11BypassWindowManagerHint);


/******************qr-code***********************************/
    qrnumber=getRand(100000,999999);
    QRWidget *qw=new QRWidget(this);
    qw->setQRData(QString::number(qrnumber));
    qw->resize(boyut,boyut);
    qw->move(screenSize.width()/2,screenSize.height()-boyut-boyut-10);
   // qDebug()<<qrnumber;
/****************************************************/


    /*************************Login Number count********************************/

    auto appIcon = QIcon(":/icons/lock.ico");
    this->setWindowIcon(appIcon);

    setWindowTitle("E-Kilit 1.0");
    QPixmap bkgnd(":/icons/lock.png");
    bkgnd = bkgnd.scaled(200,200, Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);


    QWidget *qww=new QWidget(this);

    qww->resize(200,200);
    qww->setAutoFillBackground(true);
    //qww->setStyleSheet("{background-image: url(:/icons/lock.png);}");
    qww->setPalette(palette);
    qww->move(screenSize.width()/2-100,50);

    loginCountLabel=new QLabel(this);
    loginCountLabel->resize(200,30);
//    loginCountLabel->move(screenSize.width()/2-80,screenSize.height()-boyut-40);
    loginCountLabel->move(qww->pos()+QPoint(15,115));

    //loginCountLabel->setText("Şifre");
    QFont fn( "Arial", 18, QFont::Bold);
    loginCountLabel->setFont(fn);
    loginCountLabel->setStyleSheet("color: #000000");

    if(QFileInfo::exists(localDir+"/E-Kilit"))
    {
       //qDebug()<<"var";
       QStringList list=fileToList("E-Kilit");
       QString line=listGetLine(list,"lc"); //değiştirilecek satır getiriliyor

       if(line!="") //iplistname dosyasında varsa
       {
           QStringList lst1=line.split("=");

           //qDebug()<<"okunan"<<lst1[1];

           int logincount=lst1[1].toInt()+1;
           //qDebug()<<"currentlogin"<<logincount;

           QString kmt="echo lc="+QString::number(logincount)+">"+QDir::homePath()+"/E-Kilit";
           system(kmt.toStdString().c_str());

           loginCountLabel->setText("Giriş Sayısı: "+QString::number(logincount));

       }
    }
    else
    {
       // qDebug()<<"yok";

        QString kmt="echo lc=1>"+QDir::homePath()+"/E-Kilit";
        system(kmt.toStdString().c_str());
        loginCountLabel->setText("Giriş Sayısı: 1");

    }


    //QStringList list=fileToList("iplistname");
    /*****************************************************/
        sifre=new QLabel(this);
        sifre->resize(100,30);
        sifre->move(screenSize.width()/2-40,screenSize.height()/2-90);
        sifre->setText("Şifre");
        //sifre->setText("Şifre"+QString::number(qrnumber));

       passwd=new QLineEdit(this);
        passwd->setFixedSize(80,30);
        passwd->move(screenSize.width()/2-40,screenSize.height()/2-60);
        passwd->setEchoMode(QLineEdit::Password);
        /********************************************************/
        QPushButton *ayarButton= new QPushButton(this);
        ayarButton->setFixedSize(60, 30);
        ayarButton->setIconSize(QSize(60,30));
       // ayarButton->setText("Yeniden Başlat");
        ayarButton->setStyleSheet("Text-align:left");
        ayarButton->setFlat(true);
         ayarButton->move(screenSize.width()-70,50);
         ayarButton->setIcon(QIcon(":icons/settings.png"));
        connect(ayarButton, &QPushButton::clicked, [=]() {
             QMenu *ayarMenus=ayarMenu();
            ayarMenus->exec(mapToGlobal(ayarButton->pos()-QPoint(30,-30)));


});

/********************************************************/
        QPushButton *keybordButton= new QPushButton(this);
        keybordButton->setFixedSize(60, 30);
        keybordButton->setIconSize(QSize(60,30));
       // keybordButton->setText("Klavye");
        keybordButton->setStyleSheet("Text-align:left");
        keybordButton->setFlat(true);
         keybordButton->move(screenSize.width()/2+40,screenSize.height()/2-60);
         keybordButton->setIcon(QIcon(":icons/klavye.png"));
         QMenu *kilitMenus=kilitMenu();

        connect(keybordButton, &QPushButton::clicked, [=]() {

       /* if(QFileInfo::exists("/usr/bin/eta-keyboard"))
      {
            klavyeButtonClick();
        }
        if(QFileInfo::exists("/usr/bin/eta-show-osk"))
      {
            system("/usr/bin/eta-show-osk");
        }*/

            //timerClickSlot();

       kilitMenus->exec(mapToGlobal(keybordButton->pos()));

       passwd->setFocus();
      //qDebug()<<we->page()->toPlainText();

/*            we->page()->runJavaScript("function myFunction() {"
                                        "var Row = document.getElementById('vc-avatar');var Cells = Row.getElementsByTagName('td');"
                                        "return Cells[0].innerText;} myFunction();",
                                        [] (const QVariant &result) {
                    qDebug()<<result.toString();
             });
             */
        });

           connect(passwd, SIGNAL(returnPressed()),enterButton,SIGNAL(clicked()));

                  /************************Eba QR Kod*******************************/
                   qrkodpngtimer = new QTimer(this);
                   connect(qrkodpngtimer, SIGNAL(timeout()), this, SLOT(qrkodPngSlot()));
               we=new QWebEngineView(this);
               we->page()->load(QUrl("https://giris.eba.gov.tr/EBA_GIRIS/studentQrcode.jsp"));
               we->resize(350,700);

               connect(we, &QWebEngineView::loadFinished, this, &MainWindow::onLoadFinished);

               QObject::connect(we, &QWebEngineView::urlChanged, [=] (const QUrl& url) {
                   qDebug()<<"sayfa değişti"<<url.toString();
               QString nurl="https://ders.eba.gov.tr/ders/proxy/VCollabPlayer";
               QRegularExpression re(nurl);

               if(url.toString().contains(re))
               {
                   qDebug()<<"Eba sayfası açıldı";
                   exit(0);
               }

               });

                   /*****************************************************/
}
void MainWindow::zamanlama()
{

this->activateWindow();
//klavyeButtonClick();

}
int MainWindow::getRand(int min, int max){
    unsigned int ms = static_cast<unsigned>(QDateTime::currentMSecsSinceEpoch());
    std::mt19937 gen(ms);
    std::uniform_int_distribution<> uid(min, max);
    return uid(gen);
}

MainWindow::~MainWindow()
{
  //  delete ui;
}

void MainWindow::qrkodPngSlot()
{
    qDebug()<<"foto-saved";
    /*int left, top, width, height;
        left =100;
        top = 170;
        width = 300;
        height = 300;

        QImage image(height, width, QImage::Format_RGB32);
        QRegion rg(left, top, width, height);
        QPainter painter(&image);
        we->page()->view()->render(&painter, QPoint(), rg);
        painter.end();
        image.save("test.png", "PNG", 80);
        qrkodpngtimer->stop();



       /* QPixmap bkgnd("test.png");
        bkgnd = bkgnd.scaled(200,200, Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);


        QWidget *qww=new QWidget(this);

        qww->resize(200,200);
        qww->setAutoFillBackground(true);
        //qww->setStyleSheet("{background-image: url(:/icons/lock.png);}");
        qww->setPalette(palette);
        qww->move(this->width()-250,50);
        qww->show();
      // we->hide();
      */
}
void MainWindow::onLoadFinished()
{
    qDebug()<<"Durum"<<"yüklendi";
    //system("sleep 2");
   // qrkodpngtimer->start(2000);

}

void MainWindow::klavyeButtonClick(){
    QFile data(QDir::homePath()+"/.config/eta/virtualkeyboard/config.ini");
        data.open(QIODevice::Text | QIODevice::ReadOnly);
        QString dataText = data.readAll();

        QRegularExpression re("AutoShow=true");
        QString replacementText("AutoShow=false");

        dataText.replace(re, replacementText);

        QFile newData(QDir::homePath()+"/.config/eta/virtualkeyboard/config.ini");
        if(newData.open(QFile::WriteOnly | QFile::Truncate)) {
            QTextStream out(&newData);
            out << dataText;
        }
        newData.close();
  /******************************************************/
  // system("qdbus org.eta.virtualkeyboard /VirtualKeyboard org.eta.virtualkeyboard.toggle");
 system("killall eta-keyboard");
  system("sleep 1");
  //system("eta-keyboard show");

// komut.append("sed -i 's/false/true/' ").append(stdout).append("/.config/eta/virtualkeyboard/config.ini");
// qDebug()<<komut;
 // arg << "-c" <<komut;
 //p1.start("/bin/bash",arg);
 //p1.waitForFinished(-1); // will wait forever until finished
  //system("sleep 1");


  system("nohup eta-keyboard show &\n");
  system("sleep 1");
  //p1.execute("eta-keyboard show");
 //
  // system("qdbus org.eta.virtualkeyboard /VirtualKeyboard org.eta.virtualkeyboard.toggleAutoShow");
   //system("qdbus org.eta.virtualkeyboard /VirtualKeyboard org.eta.virtualkeyboard.toggleAutoShow");
  // sleep(5);
  // system("qdbus org.eta.virtualkeyboard /VirtualKeyboard org.eta.virtualkeyboard.showFromBottom");
   //system("qdbus org.eta.virtualkeyboard /VirtualKeyboard org.eta.virtualkeyboard.toggle");
/*****************************************************************************/
  QFile data1(QDir::homePath()+"/.config/eta/virtualkeyboard/config.ini");
      data1.open(QIODevice::Text | QIODevice::ReadOnly);
      QString dataText1 = data1.readAll();

      QRegularExpression re1("AutoShow=false");
      QString replacementText1("AutoShow=true");

      dataText1.replace(re1, replacementText1);

      QFile newData1(QDir::homePath()+"/.config/eta/virtualkeyboard/config.ini");
      if(newData1.open(QFile::WriteOnly | QFile::Truncate)) {
          QTextStream out(&newData1);
          out << dataText1;
      }
      newData1.close();
  /*******************************************************************/


}


void MainWindow::updateQrCode(QString text )
{ //using namespace qrcodegen;
  // Create the QR Code object
 /* QRcode *qqr =QRcode_encodeString("text", 1, QR_ECLEVEL_L, QR_MODE_8,0);
  //qint32 *sz = qqr->getSize();
  QImage im(300,300, QImage::Format_RGB32);
    QRgb black = qRgb(  0,  0,  0);
    QRgb white = qRgb(255,255,255);
  for (int y = 0; y < 300; y++)
    for (int x = 0; x < 300; x++)
     // im.setPixel(x,y,QColor(255,0,0,255));
  //ui->widget->setPixmap( QPixmap::fromImage(im.scaled(256,256,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );
*/
}

QStringList MainWindow::listRemove(QStringList list,QString data)
 {
    // qDebug()<<"deneme-ddd"<<data;
    // QStringList list;
     //  qDebug()<<list;
     //list << "bayram|sun" << "cloud" << "sun|elif" << "firi|rain";
     QRegularExpression re(data);
     for(int i=0;i<list.count();i++)if(list[i].contains(re)) list.removeAt(i);
    // qDebug()<<list;
     return list;
 }
QString MainWindow::listGetLine(QStringList list,QString data)
 {
     //QStringList list;
     //list << "bayram|sun" << "cloud" << "sun|elif" << "firi|rain";
     QRegularExpression re(data);
     for(int i=0;i<list.count();i++) if(list[i].contains(re)) return list[i];
     //qDebug()<<list;
     return "";
 }
QStringList MainWindow::fileToList(QString filename)
 {
    FileCrud *fcc=new FileCrud();
    fcc->dosya=localDir+filename;
    QStringList list;
    for(int i=1;i<=fcc->fileCount();i++)
    {
         QString line=fcc->fileGetLine(i);
         if(line!="")
         {
             line.chop(1);
             QStringList lst=line.split("|");
             QString ln="";
             if(lst.count()>0)ln.append(lst[0]);
             if(lst.count()>1)ln.append("|").append(lst[1]);
             if(lst.count()>2)ln.append("|").append(lst[2]);
             if(lst.count()>3)ln.append("|").append(lst[3]);
             if(lst.count()>4)ln.append("|").append(lst[4]);
             if(lst.count()>5)ln.append("|").append(lst[5]);
             if(lst.count()>6)ln.append("|").append(lst[6]);
             if(lst.count()>7)ln.append("|").append(lst[7]);
             if(lst.count()>8)ln.append("|").append(lst[8]);
             if(lst.count()>9)ln.append("|").append(lst[9]);
             if(lst.count()>10)ln.append("|").append(lst[10]);
             if(lst.count()>11)ln.append("|").append(lst[11]);
             if(lst.count()>12)ln.append("|").append(lst[12]);
             if(lst.count()>13)ln.append("|").append(lst[13]);

             list <<ln;
            // qDebug()<<ln;
             // list <<lst[0]+"|"+lst[1]+"|"+lst[2]+"|"+lst[3]+"|"+lst[4]+"|"+lst[5];

         }
    }
       return list;
 }
void MainWindow::listToFile(QStringList list, QString filename)
 {
    FileCrud *fcc=new FileCrud();
    fcc->dosya=localDir+filename;
    fcc->fileRemove();
    for(int i=0;i<list.count();i++)
    {
         QString line=list[i];
         if(line!="")
         {
             //line.chop(1);
             QStringList lst=line.split("|");
             //qDebug()<<line;
             QString ln="";
             if(lst.count()>0)ln.append(lst[0]);
             if(lst.count()>1)ln.append("|").append(lst[1]);
             if(lst.count()>2)ln.append("|").append(lst[2]);
             if(lst.count()>3)ln.append("|").append(lst[3]);
             if(lst.count()>4)ln.append("|").append(lst[4]);
             if(lst.count()>5)ln.append("|").append(lst[5]);
             if(lst.count()>6)ln.append("|").append(lst[6]);
             if(lst.count()>7)ln.append("|").append(lst[7]);
             if(lst.count()>8)ln.append("|").append(lst[8]);
             if(lst.count()>9)ln.append("|").append(lst[9]);
             if(lst.count()>10)ln.append("|").append(lst[10]);
             if(lst.count()>11)ln.append("|").append(lst[11]);
             if(lst.count()>12)ln.append("|").append(lst[12]);
             if(lst.count()>13)ln.append("|").append(lst[13]);

             //qDebug()<<ln;
             fcc->fileWrite(ln);

         }

    }
 }
