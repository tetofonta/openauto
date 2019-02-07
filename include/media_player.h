#ifndef MEDIA_PLAYER_H
#define MEDIA_PLAYER_H

#include <QWidget>
#include "source_diskmedia.h"

namespace Ui {
    class media_player;
}

class media_player : public QWidget
{
Q_OBJECT

public:
    explicit media_player(QWidget *parent = 0);
    ~media_player();

private slots:
    void onPlay_pause();
    void onBack();
    void onFw();
    void onOrder();
    void titles(char*,char*,char*);

private:
    Ui::media_player *ui;
    bool isPlaying = false;
    bool isRandom = false;

    std::string current_source = "/media/pi";

    source_diskmedia local = source_diskmedia();
};

#endif // MEDIA_PLAYER_H
