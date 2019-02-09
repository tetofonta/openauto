#include <media_player.h>
#include "ui_media_player.h"

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
void media_player::onFw(){
    local.next();
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


media_player::media_player(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::media_player)
{
    ui->setupUi(this);

    local=source_diskmedia(ui->title, ui->author, ui->album, ui->horizontalSlider);
    local.init();
    local.build_playlist(true, (char *) current_source.c_str(), isRandom);

    connect(ui->control, SIGNAL(released()), this, SLOT(onPlay_pause()));
    connect(ui->back, SIGNAL(released()), this, SLOT(onBack()));
    connect(ui->forward, SIGNAL(released()), this, SLOT(onFw()));
    connect(ui->repeat, SIGNAL(released()), this, SLOT(onOrder()));
}

media_player::~media_player()
{
    delete ui;
}
