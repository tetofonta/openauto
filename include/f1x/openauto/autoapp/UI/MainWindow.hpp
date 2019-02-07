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

#pragma once

#include <memory>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>

namespace Ui
{
class MainWindow;
}

namespace f1x
{
namespace openauto
{
namespace autoapp
{
namespace ui
{

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

signals:
    void exit();
    void openSettings();
    void toggleCursor();
    void openConnectDialog();

private slots:
    void onVolume();
    void onVolume_btn();
    void onMedia_btn();
private:
    void showPage(QWidget * w);

    Ui::MainWindow *ui;

    QPushButton * bt;
    QPushButton * volume;
    QPushButton * wireless;

    bool isMuted = false;

    long vol = 50;

    QWidget * media_player_pg;
    QWidget * volume_pg;
    QWidget * welcome_pg;

    QWidget * current = nullptr;
};

}
}
}
}
