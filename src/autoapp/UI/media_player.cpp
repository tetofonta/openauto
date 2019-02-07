#include <media_player.h>
#include "ui_media_player.h"

media_player::media_player(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::media_player)
{
    ui->setupUi(this);
}

media_player::~media_player()
{
    delete ui;
}
