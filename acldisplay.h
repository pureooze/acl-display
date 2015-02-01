#ifndef ACLDISPLAY_H
#define ACLDISPLAY_H

#include <QMainWindow>

namespace Ui {
class acldisplay;
}

class acldisplay : public QMainWindow
{
    Q_OBJECT

public:
    explicit acldisplay(QWidget *parent = 0);
    ~acldisplay();

private:
    Ui::acldisplay *ui;
};

#endif // ACLDISPLAY_H
