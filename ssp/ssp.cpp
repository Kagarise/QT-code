#include "ssp.h"
#include "ui_ssp.h"
#include "floyd.h"
#include "dijkstra.h"

#include <QFile>
#include <QPoint>
#include <QLabel>
#include <QString>
#include <QPainter>
#include <QFileDialog>
#include <QTextStream>

#include <cmath>

QString dialogData;

ssp::ssp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ssp)
{
    ui->setupUi(this);

    // widget style
    QString widgetQSS = "QWidget{border: 2px solid #CCC; border-radius: 5px;}";

    ui->widgetLeft->setStyleSheet(widgetQSS);
    ui->widgetRight->setStyleSheet(widgetQSS);

    // Load new style
    //    QString bQSS = "QPushButton{border: 2px solid #0FF; border-radius: 5px;}";
    //    QPushButton *bLoad = ui->pushButtonOld;
    //    bLoad->setStyleSheet(bQSS);

    // Set radioButton default value
    ui->radioButtonFloyd->setChecked(true);
    ui->radioButtonDistance->setChecked(true);
}

ssp::~ssp()
{
    delete ui;
}

void ssp::on_pushButtonNew_clicked()
{
    dialog = new Dialog(this);
    dialog->setModal(true);
    connect(dialog, SIGNAL(sendData(QString)), this, SLOT(receiveData(QString)));
    dialog->show();
}

void ssp::on_pushButtonOld_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Load Map", "../", "TXT(*.txt)");
    if(!filePath.isEmpty()){
        QFile file(filePath);
        if(file.open(QIODevice::ReadOnly)){
            // Read Start
            QTextStream ss(&file);
            initMap();
            ss >> map.vexnum >> map.arcnum;
            for(int i = 0; i < map.arcnum; i++){
                int u, v;
                double dis, speed;
                ss >> u >> v >> dis >> speed;
                map.side_info_vec.push_back(SideInfo(u, v, dis, speed));
            }
            // Read End
            deleteV();
            update();
        }
        file.close();
    }
}

void ssp::on_pushButtonCalculate_clicked()
{
    bool algo = ui->radioButtonFloyd->isChecked();
    bool meth = ui->radioButtonDistance->isChecked();
    map.st = ui->lineEditStart->text().toInt();
    map.en = ui->lineEditEnd->text().toInt();
    if(algo){ // Solve By Floyd
        Floyd floyd;
        floyd.init(map);
        if(meth) floyd.solveByDistance();
        else floyd.solveByTime();
        map.side_set = floyd.findWay();
    }
    else{ // Solve By Dijkstra
        Dijkstra dijkstra;
        dijkstra.init(map);
        if(meth) dijkstra.solveByDistance();
        else dijkstra.solveByTime();
        map.side_set = dijkstra.findWay();
    }
    deleteV();
    update();
}

void ssp::paintEvent(QPaintEvent *event){
//    if(paintPause)
//        return;
//    paintPause = true;
    // makesure Paint Area
    int width = this->width();
    int height = this->height();
    int cX = width - width * 0.3;
    int cY = height / 2 * 1.05;
    int cR = cY * 0.7;
    int labelSize = 18;
    int len = V.size();
    QPoint QP[map.vexnum+10];
    double pi = acos(-1.0);
    // Find Point
    for(int i = 1; i <= map.vexnum; i++){
        QP[i].setX(cX + cR * cos(2 * pi * i / map.vexnum)), QP[i].setY(cY + cR * sin(2 * pi * i / map.vexnum));
        if(i > len){
            QLabel *label = new QLabel(this);
            label->setText(QString("%1").arg(i));
            label->setGeometry(rect().x() + QP[i].x(), rect().y() + QP[i].y(), labelSize, labelSize);
            label->show();
            len++;
            V.push_back(label);
        }
        else{
            myLabel = V[i-1];
            myLabel->setText(QString("%1").arg(i));
            myLabel->setGeometry(rect().x() + QP[i].x(), rect().y() + QP[i].y(), labelSize, labelSize);
            myLabel->show();
            V[i-1] = myLabel;
        }
    }
    // Draw Line
    QPainter p;
    p.begin(this);
    for(int i = 0; i < map.arcnum; i++){
        int u = map.side_info_vec[i].u, v = map.side_info_vec[i].v;
        // Result way
        if(map.side_set.count(make_pair(u,v)) || map.side_set.count(make_pair(v,u)))
            p.setPen(QPen(QColor(0,255,255), 3));
        else
            p.setPen(QPen(QColor(192,192,192), 3));
        p.drawLine(QP[u], QP[v]);
    }
    p.end();
}

void ssp::receiveData(QString data){
    QTextStream ss(&data);
    initMap();
    ss >> map.vexnum >> map.arcnum;
    for(int i = 0; i < map.arcnum; i++){
        int u, v;
        double dis, speed;
        ss >> u >> v >> dis >> speed;
        map.side_info_vec.push_back(SideInfo(u, v, dis, speed));
    }
    deleteV();
    update();
}

void ssp::initMap(){
    map.vexnum = map.arcnum = 0;
    map.st = map.en = 0;
    map.side_info_vec.clear();
    map.side_set.clear();
    paintPause = false;
}

void ssp::deleteV(){
    int len = V.size();
    for(int i = 0; i < len; i++){
        delete(V[i]);
    }
    V.clear();
}
