#include <welcome_page.h>
#include "ui_welcome_page.h"

Welcome_page::Welcome_page(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Welcome_page)
{
    ui->setupUi(this);
}

Welcome_page::~Welcome_page()
{
    delete ui;
}
