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

void acldisplay::on_pathWidget_returnPressed()
{
    path = ui->pathWidget->text();

    QProcess    p;

    command = "getfacl " + path;
    p.start(command);
    p.waitForFinished(10);

    QString     stdOUT = p.readAllStandardOutput();
    QString     stdERR = p.readAllStandardError();

    parseACL(stdOUT);
    qDebug() << temp;
}

void acldisplay::parseACL(QString acl)
{
    result = acl.split("\n");
    for(int i=0; i < result.length(); i++){
        if(i <= 2){
            qDebug() << result[i];
            temp = result[i].split(": ");

            if(i == 0){
                ui->fileNameLabel->setText(temp[1]);
            }else if(i == 1){
                ui->ownerNameLabel->setText(temp[1]);
            }else if(i ==2){
                ui->groupNameLabel->setText(temp[1]);
            }
        }


    }
}

















