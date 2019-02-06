#ifndef WELCOME_PAGE_H
#define WELCOME_PAGE_H

#include <QWidget>

namespace Ui {
    class welcome_page;
}

class welcome_page : public QWidget
{
Q_OBJECT

public:
    explicit welcome_page(QWidget *parent = 0);
    ~welcome_page();

private:
    Ui::welcome_page *ui;
};

#endif // WELCOME_PAGE_H
