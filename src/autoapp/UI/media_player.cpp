#include <media_player.h>
#include "ui_media_player.h"

void media_player::onPlay_pause(){
    if(this->isPlaying){
        local.pause();
        ui->control->setIcon(QIcon(":/ico_pause"));
        this->isPlaying = false;
        return;
    }
    local.play();
    ui->control->setIcon(QIcon(":/ico_play"));
    this->isPlaying = true;
    return;
}
void media_player::onBack(){
    local.back();
}
void media_player::onFw(){
    local.next();
}
void media_player::onRepeat(){

}

media_player::media_player(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::media_player)
{
    ui->setupUi(this);

    local.init();
    local.build_playlist(true, "/media/", true);

    connect(ui->control, SIGNAL(release()), this, SIGNAL(onPlay_pause()));
    connect(ui->back, SIGNAL(release()), this, SIGNAL(onBack()));
    connect(ui->forward, SIGNAL(release()), this, SIGNAL(onFw()));
}

media_player::~media_player()
{
    delete ui;
}
