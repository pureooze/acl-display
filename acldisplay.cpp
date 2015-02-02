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
}

void acldisplay::parseACL(QString acl)
{
    result = acl.split("\n");
    ui->tableWidget->setRowCount(0);

    for(int i=0; i < result.length() - 2; i++){

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
        }else{
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setCheckState(Qt::Checked);

            tableItems.insert(i, item);
            permissions[i] = result[i].split(":");
        }
    }
    qDebug() << tableItems.keys();
    QTableWidgetItem *item2 = new QTableWidgetItem();
    item2 = tableItems.value(4);
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setItem(1,0,item2);
    //ui->tableWidget->insertRow(1);
    qDebug() << ui->tableWidget->rowCount();
}

















