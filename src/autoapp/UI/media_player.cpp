#include <media_player.h>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <dirent.h>
#include <functional>
#include "ui_media_player.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <zconf.h>

void media_player::onPlay_pause(){
    if(this->isPlaying){
        local.pause();
        ui->control->setIcon(QIcon(":/ico_play"));
        this->isPlaying = false;
        return;
    }
    local.play();
    ui->control->setIcon(QIcon(":/ico_pause"));
    this->isPlaying = true;
    return;
}
void media_player::onBack(){
    local.back();
}
void media_player::onFw() {
    local.next();
}

void media_player::onSrc(){
    ui->sources->show();
}

void media_player::onOrder(){
    if(this->isRandom){
        ui->repeat->setIcon(QIcon(":/ico_repeat"));
        this->isRandom = false;
    }else {
        ui->repeat->setIcon(QIcon(":/ico_random"));
        this->isRandom = true;
    }
    local.build_playlist(true, (char *) current_source.c_str(), isRandom);
}

void media_player::chsrc(std::string folder){
    local.stop();
    usleep(1000);
    local.pause();
    local.build_playlist(true, (char *) folder.c_str(), isRandom);
    this->current_source = folder;
    std::cout << folder << std::endl;
}

QPushButton *addSource(QListWidget *list, char *icon, char * text) {
    QListWidgetItem *item = new QListWidgetItem(list);
    QPushButton *button = new QPushButton();
    button->setIcon(QIcon(icon));
    button->setText(text);
    button->setFlat(true);
//    item->setSizeHint(button->minimumSizeHint());
    list->setItemWidget(item, button);
    return button;
}

void media_player::scanLocalSources(std::string path, int rec, QListWidget * list) {
    if(rec == 0) return;

    if (auto dir = opendir(path.c_str())) {
        while (auto f = readdir(dir)) {
            if (!f->d_name || f->d_name[0] == '.') continue;
            if (f->d_type == DT_DIR){
                connect(addSource(list, ":/ico_usb.png", f->d_name), &QPushButton::released, this, std::bind(this->chsrc, path + f->d_name + "/"));
            }
        }
        closedir(dir);
    }
}


media_player::media_player(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::media_player)
{
    ui->setupUi(this);

    local=source_diskmedia(ui->title, ui->author, ui->album, ui->horizontalSlider);

    scanLocalSources("/media/pi/", 100, ui->sources);


    local.init();
    local.build_playlist(true, (char *) current_source.c_str(), isRandom);

    connect(ui->control, SIGNAL(released()), this, SLOT(onPlay_pause()));
    connect(ui->back, SIGNAL(released()), this, SLOT(onBack()));
    connect(ui->forward, SIGNAL(released()), this, SLOT(onFw()));
    connect(ui->repeat, SIGNAL(released()), this, SLOT(onOrder()));
    connect(ui->source, SIGNAL(released()), this, SLOT(onSrc()));
}

media_player::~media_player()
{
    delete ui;
}
