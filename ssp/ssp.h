#ifndef SSP_H
#define SSP_H

#include "mapinfo.h"
#include "dialog.h"

#include <QWidget>
#include <QLabel>

namespace Ui {
class ssp;
}

class ssp : public QWidget
{
    Q_OBJECT

public:
    explicit ssp(QWidget *parent = 0);
    ~ssp();
    MapInfo map;
    QLabel *myLabel = new QLabel(this);
    vector<QLabel*> V;
    bool paintPause = true;
    void initMap();
    void deleteV();

private slots:
    void on_pushButtonNew_clicked();
    void on_pushButtonOld_clicked();

    void on_pushButtonCalculate_clicked();

    void receiveData(QString data);


private:
    Ui::ssp *ui;
    void paintEvent(QPaintEvent *event);
    Dialog *dialog;
};

#endif // SSP_H
