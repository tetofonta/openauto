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

void media_player::titles(char * title, char * artist, char * album){
    char buffer[100];
    sprintf(buffer, "<html><head/><body><p><span style=\" font-size:28pt; font-weight:600;\">%s</span></p></body></html>", title);
    ui->title->setText(buffer);
    sprintf(buffer, "<html><head/><body><p><span style=\" font-size:18pt; \">%s</span></p></body></html>", artist);
    ui->author->setText(buffer);
    sprintf(buffer, "<html><head/><body><p><span style=\" font-size:26pt; font-weight:600;\">%s</span></p></body></html>", album);
    ui->album->setText(buffer);
}

media_player::media_player(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::media_player)
{
    ui->setupUi(this);

    local.init();
    local.build_playlist(true, (char *) current_source.c_str(), isRandom);

    connect(local, SIGNAL(new_song_started(char *, char *, char *)), this, SLOT(titles(char*,char*,char*)));

    connect(ui->control, SIGNAL(release()), this, SLOT(onPlay_pause()));
    connect(ui->back, SIGNAL(release()), this, SLOT(onBack()));
    connect(ui->forward, SIGNAL(release()), this, SLOT(onFw()));
    connect(ui->repeat, SIGNAL(released()), this, SLOT(onOrder()));
}

media_player::~media_player()
{
    delete ui;
}
