#include <welcome_page.h>
#include "ui_welcome_page.h"

welcome_page::welcome_page(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::welcome_page)
{
    ui->setupUi(this);
}

welcome_page::~welcome_page()
{
    delete ui;
}
