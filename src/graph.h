#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>

extern "C" {
#include "s21_bank_calc.h"
#include "s21_smart_calc.h"
}

namespace Ui {
class Graph;
}

class Graph : public QDialog {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();

 private:
  Ui::Graph *ui;

 public slots:
  void draw_Graph(QString, double, double, double, double);
};

#endif  // GRAPH_H
