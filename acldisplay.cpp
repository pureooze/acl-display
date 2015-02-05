#include "acldisplay.h"
#include "ui_acldisplay.h"

acldisplay::acldisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::acldisplay)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
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
            for(int x = 0; x < 3; x++){
                QTableWidgetItem *item = new QTableWidgetItem;
                item->setCheckState(Qt::Checked);
                checkBoxes.insert(i, item);
            }

            permissions[i] = result[i].split(":");
        }
    }

    qDebug() << permissions;
    ui->tableWidget->setRowCount(tableItems.size());

    for(int i = 3; i < result.length() - 2; i++){
        QTableWidgetItem *type = new QTableWidgetItem();
        QTableWidgetItem *entity = new QTableWidgetItem();
        QTableWidgetItem *checkBox = new QTableWidgetItem();
        type->setText(permissions.value(i)[0]);
        entity->setText(permissions.value(i)[1]);
        checkBox = checkBoxes.value(i);
        symPermission = permissions.value(i)[2].split("");

        for(int j = 1; j <= 3; j++){
            checkPermission(checkBox, symPermission[j]);
        }

        ui->tableWidget->setItem(i - 3, 0, type);
        ui->tableWidget->setItem(i - 3, 1, entity);
        ui->tableWidget->setItem(i - 3, 2, checkBox);
    }
}

void acldisplay::checkPermission(QTableWidgetItem* checkBox, QString symPermission)
{
    if(symPermission != "-"){
        checkBox->setCheckState(Qt::Checked);
    }else{
        checkBox->setCheckState(Qt::Unchecked);
    }
}















