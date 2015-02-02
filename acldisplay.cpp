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
    // Execute this when the user presses enter in the line edit widget
    path = ui->pathWidget->text();

    QProcess    p;
    // launch a process to get ACL info from specified location
    command = "getfacl " + path;
    p.start(command);
    p.waitForFinished(10);

    QString     stdOUT = p.readAllStandardOutput();
    QString     stdERR = p.readAllStandardError();

    parseACL(stdOUT);
}

void acldisplay::parseACL(QString acl)
{
    // split the ACL by \n so that we can treat each line as a separate entity
    result = acl.split("\n");
    ui->tableWidget->setRowCount(0);

    for(int i = 0; i < result.length() - 2; i++){
        if(i <= 2){
            qDebug() << result[i];
            temp = result[i].split(": ");

            // set values for the three fixed text fields, we do this by splitting on ": "
            // because we do not care about the first part of the field (as it never changes)
            if(i == 0){
                ui->fileNameLabel->setText(temp[1]);
            }else if(i == 1){
                ui->ownerNameLabel->setText(temp[1]);
            }else if(i ==2){
                ui->groupNameLabel->setText(temp[1]);
            }

        }else{
            // all these entities are ACL attributes that the user should be able to change
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setCheckState(Qt::Checked);

            tableItems.insert(i, item);
            permissions[i] = result[i].split(":");
        }
    }

    qDebug() << tableItems.keys();
    ui->tableWidget->setRowCount(1);

    qDebug() << result.length() << result;
    for(int i = 3; i < result.length() - 2; i++){
        QTableWidgetItem *item2 = new QTableWidgetItem();
        item2 = tableItems.value(i);
        ui->tableWidget->setItem(i - 3, 0, item2);
        qDebug() << i << " , " << i - 3;
        ui->tableWidget->insertRow(1);
    }

    qDebug() << ui->tableWidget->rowCount();
}

















