#ifndef MEDIA_PLAYER_H
#define MEDIA_PLAYER_H

#include <QWidget>

namespace Ui {
    class media_player;
}

class media_player : public QWidget
{
Q_OBJECT

public:
    explicit media_player(QWidget *parent = 0);
    ~media_player();

private:
    Ui::media_player *ui;
};

#endif // MEDIA_PLAYER_H
