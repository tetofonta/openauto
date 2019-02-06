/*
*  This file is part of openauto project.
*  Copyright (C) 2018 f1x.studio (Michal Szwaj)
*
*  openauto is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 3 of the License, or
*  (at your option) any later version.

*  openauto is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with openauto. If not, see <http://www.gnu.org/licenses/>.
*/

#include <QApplication>
#include <QPushButton>
#include <f1x/openauto/autoapp/UI/MainWindow.hpp>
#include <QtWidgets/QListWidget>
#include <alsa_manager.h>
#include <volume_control.h>
#include <welcome_page.h>
#include "ui_mainwindow.h"

namespace f1x {
    namespace openauto {
        namespace autoapp {
            namespace ui {

                QPushButton *addButton(QListWidget *list, Ui::MainWindow *ui, char *icon) {
                    QListWidgetItem *item = new QListWidgetItem(list);
                    QPushButton *button = new QPushButton();
                    button->setIcon(QIcon(icon));
                    button->setFlat(true);
                    item->setSizeHint(button->minimumSizeHint());
                    ui->listWidget->setItemWidget(item, button);
                    return button;
                }

                void MainWindow::onVolume() {
                    if (this->isMuted) {
                        this->volume->setIcon(QIcon(":/ico_volume"));
                        long v = this->vol;
                        alsaVolume(AUDIO_VOLUME_SET, &v);
                    } else {
                        this->volume->setIcon(QIcon(":/ico_volume_mute"));
                        long v = 0;
                        alsaVolume(AUDIO_VOLUME_SET, &v);
                    }
                    this->isMuted = !this->isMuted;
                }

                void MainWindow::showPage(QWidget *w) {
                    w->show();
                    w->setGeometry(QRect(QPoint(10, 70), QSize(920, 510)));
                }

                void MainWindow::onVolume_btn() {
                    showPage(volume_pg);
                }

                MainWindow::MainWindow(QWidget *parent)
                        : QMainWindow(parent), ui(new Ui::MainWindow) {
                    ui->setupUi(this);

                    /*loading pages*/
                    ui->setupUi(this);
                    welcome_pg = new welcome_page(this);
                    welcome_pg->hide();
                    volume_pg = new volume_control(this, &(this->isMuted), &(this->vol));
                    volume_pg->hide();
                    connect(volume_pg, SIGNAL (volumeMuted()),this, SLOT (onVolume()));
                    /**/

                    /*setting up current volume value*/
                    alsaVolume(AUDIO_VOLUME_GET, &(this->vol));
                    /**/

                    /*first page*/
                    showPage(welcome_pg);

                    /*adding defaults status buttons TODO*/
                    addButton(ui->listWidget, ui, ":/ico_setting");
                    addButton(ui->listWidget, ui, ":/ico_bt_on");
                    this->volume = addButton(ui->listWidget, ui, ":/ico_volume");
                    addButton(ui->listWidget, ui, ":/ico_wifi_connected");
                    addButton(ui->listWidget, ui, ":/ico_usb");


                    /*connecting callbacks*/
                    connect(volume, SIGNAL(released()), this, SLOT(onVolume()));


                    connect(ui->volume_v, SIGNAL(released()), this, SLOT(onVolume_btn()));
                }

                MainWindow::~MainWindow() {
                    delete ui;
                }

            }
        }
    }
}
