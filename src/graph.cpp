#include "graph.h"
#include "ui_graph.h"

Graph::Graph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graph)
{
    ui->setupUi(this);
}

Graph::~Graph()
{
    delete ui;
}

#include <QDebug>

void Graph::draw_Graph(QString str, double xmin, double xmax, double ymin, double ymax)
{
    qDebug() << xmin << xmax << ymin << ymax;
    ui->widget->addGraph();
     ui->widget->xAxis->setRange(xmin, xmax);
     for (int i = 0; i < ui->widget->graphCount(); i++) {
       ui->widget->graph(i)->data()->clear();
     }
     QString tmp = str;
     QVector<double> x, y;
     double res, step = (xmax - xmin) / 1000., min_y = 100000., max_y = -100000.;
     int graph_i = 0;
     double i = xmin;
     while (i <= xmax) {
       tmp.replace("x", QString::number(i));
       QByteArray arr_byte = tmp.toLocal8Bit().data();
       char *ptr_ex = arr_byte.data();
       res = toPostfix(ptr_ex);
       if (!error) {
         min_y = (res < min_y) ? res : min_y;
         max_y = (res > max_y) ? res : max_y;
         x.append(i);
         y.append(res);
       } else {
         ui->widget->graph(graph_i++)->setData(x, y);
         ui->widget->addGraph();
         x.clear();
         y.clear();
       }
       tmp = str;
       i = (round(i * 1000.) / 1000.) + step;
     }
     //if (autoscale) {
     //  ui->widget->yAxis->setRange(min_y, max_y);
     //} else {
       ui->widget->yAxis->setRange(ymin, ymax);
     //}
     ui->widget->graph(graph_i)->setData(x, y);
     ui->widget->replot();
     x.clear();
     y.clear();
     ui->widget->setInteraction(QCP::iRangeZoom, true);
     ui->widget->setInteraction(QCP::iRangeDrag, true);
     ui->widget->setVisible(true);
}

