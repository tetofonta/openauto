#ifndef VOLUME_CONTROL_H
#define VOLUME_CONTROL_H

#include <QWidget>
#include "alsa_manager.h"

namespace Ui {
class volume_control;
}

class volume_control : public QWidget
{
    Q_OBJECT

public:
    explicit volume_control(QWidget *parent, bool * isMuted, long * vol);
    ~volume_control();

public slots:
    void onVolChange(int);

signals:
    void volumeMuted();

private:
    Ui::volume_control *ui;

    bool * isMuted;
    long * vol;
};

#endif // VOLUME_CONTROL_H
