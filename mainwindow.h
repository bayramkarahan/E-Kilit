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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMenu>
#include<QLineEdit>
#include<QLabel>
#include<QPushButton>

#include<QWebEngineView>
#include<QTimer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void updateQrCode( QString text );
int getRand(int min, int max);
void zamanlama();
void klavyeButtonClick();
QStringList listRemove(QStringList list,QString data);
QStringList fileToList(QString filename);
void listToFile(QStringList list, QString filename);
QString listGetLine(QStringList list,QString data);

void onLoadFinished();
void qrkodPngSlot();

private:
    //Ui::MainWindow *ui;
QLineEdit *passwd;
QLabel *sifre;
QLabel *loginCountLabel;
QMenu *kilitMenu();
QMenu *ayarMenu();
int qrnumber;
QPushButton *enterButton;
QString localDir;


QWebEngineView *we;
QTimer *qrkodpngtimer;
};

#endif // MAINWINDOW_H
