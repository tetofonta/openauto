#include <volume_control.h>
#include "ui_volume_control.h"
#include <alsa_manager.h>
#include <cstdio>

namespace f1x {
    namespace openauto {
        namespace autoapp {
            namespace ui {
void volume_control::onVolChange(int val){
    if((!val && !*(this->isMuted)) || (val && *(this->isMuted))){
        emit volumeMuted();
    }

    long v = val;
    *(this->vol) = val;
    char buffer [170];
    sprintf(buffer, "<html><head/><body><p><span style=\" font-size:72pt; font-weight:600;\">%d%%</span></p></body></html>", val);
    ui->volume_v->setText(buffer);

    alsaVolume(AUDIO_VOLUME_SET, &v);
}

volume_control::volume_control(QWidget *parent, bool * isMuted, long * vol) :
    QWidget(parent),
    ui(new Ui::volume_control)
{
    this->isMuted = isMuted;
    this->vol = vol;
    ui->setupUi(this);

    ui->dial->setValue(*vol);
    connect(ui->dial, SIGNAL(valueChanged(int)), this, SLOT(onVolChange(int)));
}

volume_control::~volume_control()
{
    delete ui;
}
}}}}
