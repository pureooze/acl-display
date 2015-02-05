#ifndef ACLDISPLAY_H
#define ACLDISPLAY_H

#include <QMainWindow>
#include <QProcess>
#include <QDebug>
#include <QHash>
#include <QMap>
#include <QTableWidgetItem>

namespace Ui {
class acldisplay;
}

class acldisplay : public QMainWindow
{
    Q_OBJECT

public:
    explicit acldisplay(QWidget *parent = 0);
    ~acldisplay();

private slots:
    void on_pathWidget_returnPressed();

private:
    Ui::acldisplay *ui;

    void parseACL(QString);
    void checkPermission(QTableWidgetItem* , QString);

    QString path;
    QString command;

    QStringList result;
    QStringList temp;
    QStringList symPermission;

    QHash<int, QStringList>                         permissions;
    QMap<int, QTableWidgetItem *>                   checkBoxes;
    QMap<int, QMap<int, QTableWidgetItem *> *>      tableItems;
};

#endif // ACLDISPLAY_H
