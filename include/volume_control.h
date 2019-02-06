#ifndef VOLUME_CONTROL_H
#define VOLUME_CONTROL_H

#pragma once

#include <memory>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
namespace Ui {
class volume_control;
}
namespace f1x
{
namespace openauto
{
namespace autoapp
{
namespace ui
{
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
}}}}
#endif // VOLUME_CONTROL_H
