#include "acldisplay.h"
#include "ui_acldisplay.h"

acldisplay::acldisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::acldisplay)
{
    ui->setupUi(this);
}

acldisplay::~acldisplay()
{
    delete ui;
}
