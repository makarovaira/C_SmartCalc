#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:

 private:
  Ui::MainWindow *ui;
  Graph *grWindow;

 private slots:
  void print_x();
  void group_signals();
  void digits_numbers();
  void arithmetic_op();
  void additional_op();
  void delete_all();
  void delete_symbol();
  void braces();
  void dot();
  void unary_pm();
  void print_ans();
  void delete_zero();
  void on_pushButton_calc_clicked();
  void on_pushButton_depositCalc_clicked();

  void on_pushButton_graph_clicked();

  void on_pushButton_xValue_clicked();

 signals:
  void drawGraph(QString, double, double, double, double);
};
#endif  // MAINWINDOW_H
