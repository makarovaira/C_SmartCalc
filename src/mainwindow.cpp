#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <limits>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setAlignment(Qt::AlignRight);
    ui->lineEdit->setText("0");
    grWindow = new Graph(this);
    group_signals();
    ui->doubleSpinBox_xmax->setRange(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    ui->doubleSpinBox_xmin->setRange(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    ui->doubleSpinBox_ymax->setRange(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    ui->doubleSpinBox_ymin->setRange(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    ui->doubleSpinBox_xValue->setRange(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::group_signals()
{
    connect(this, &MainWindow::drawGraph, grWindow, &Graph::draw_Graph);
    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(digits_numbers()));

    connect(ui->pushButton_sum,SIGNAL(clicked()),this,SLOT(arithmetic_op()));
    connect(ui->pushButton_sub,SIGNAL(clicked()),this,SLOT(arithmetic_op()));
    connect(ui->pushButton_mult,SIGNAL(clicked()),this,SLOT(arithmetic_op()));
    connect(ui->pushButton_div,SIGNAL(clicked()),this,SLOT(arithmetic_op()));
    connect(ui->pushButton_mod,SIGNAL(clicked()),this,SLOT(arithmetic_op()));

    connect(ui->pushButton_sin,SIGNAL(clicked()),this,SLOT(additional_op()));
    connect(ui->pushButton_asin,SIGNAL(clicked()),this,SLOT(additional_op()));
    connect(ui->pushButton_cos,SIGNAL(clicked()),this,SLOT(additional_op()));
    connect(ui->pushButton_acos,SIGNAL(clicked()),this,SLOT(additional_op()));
    connect(ui->pushButton_tan,SIGNAL(clicked()),this,SLOT(additional_op()));
    connect(ui->pushButton_atan,SIGNAL(clicked()),this,SLOT(additional_op()));
    connect(ui->pushButton_ln,SIGNAL(clicked()),this,SLOT(additional_op()));
    connect(ui->pushButton_log,SIGNAL(clicked()),this,SLOT(additional_op()));
    connect(ui->pushButton_pow,SIGNAL(clicked()),this,SLOT(additional_op()));
    connect(ui->pushButton_sqrt,SIGNAL(clicked()),this,SLOT(additional_op()));

    connect(ui->pushButtonAC,SIGNAL(clicked()),this,SLOT(delete_all()));

    connect(ui->pushButton_detete,SIGNAL(clicked()),this,SLOT(delete_symbol()));

    connect(ui->pushButton_braceO,SIGNAL(clicked()),this,SLOT(braces()));

    connect(ui->pushButton_braceC,SIGNAL(clicked()),this,SLOT(braces()));

    connect(ui->pushButton_dot,SIGNAL(clicked()),this,SLOT(dot()));

    connect(ui->pushButton_x,SIGNAL(clicked()),this,SLOT(print_x()));

    connect(ui->pushButton_un,SIGNAL(clicked()),this,SLOT(unary_pm()));

    connect(ui->pushButton_eq,SIGNAL(clicked()),this,SLOT(print_ans()));
}

void MainWindow::print_x() {
    delete_zero();
    ui->lineEdit->setText(ui->lineEdit->text() + "x");
}

void MainWindow::digits_numbers() {
    delete_zero();
    QPushButton *button = (QPushButton *)sender();
    ui->lineEdit->setText(ui->lineEdit->text() + button->text());
}

void MainWindow::arithmetic_op() {
    delete_zero();
    QPushButton *button = (QPushButton *)sender();
    if (button->text() == "÷") {
        ui->lineEdit->setText(ui->lineEdit->text() + "/");
    } else {
       ui->lineEdit->setText(ui->lineEdit->text() + button->text());

    }
}

void MainWindow::additional_op() {
    delete_zero();
    QPushButton *button = (QPushButton *)sender();
    if(button->text() != "√"){
        ui->lineEdit->setText(ui->lineEdit->text() + button->text() + "(");
    } else {
        ui->lineEdit->setText(ui->lineEdit->text() + "sqrt(");
    }
}

void MainWindow::delete_all() {
    ui->lineEdit->clear();
    ui->lineEdit->setText("0");
}

void MainWindow::delete_symbol() {
    QString newText = ui->lineEdit->text().left(std::size(ui->lineEdit->text()) - 1);
    ui->lineEdit->setText(newText);
}

void MainWindow::braces() {
    delete_zero();
    QPushButton *button = (QPushButton *)sender();
    if(button->text() == "(") {
        ui->lineEdit->setText(ui->lineEdit->text() + button->text());
    } else if(button->text() == ")"){
        if (ui->lineEdit->text() != "0" && ui->lineEdit->text().back() != '(') {
            ui->lineEdit->setText(ui->lineEdit->text() + button->text());
        }

    }
}

void MainWindow::dot() {
    bool tf = 0;
    QString line = ui->lineEdit->text();
    for (int i = line.length() - 1; i >= 0; i--) {
        if (line[i] == '.') {
            tf = 1;
            break;
        } else if (!line[i].isDigit()) {
            break;
        }
    }
    if (tf == 0 && (!line.isEmpty()) && line.back().isDigit()) {
        ui->lineEdit->setText(ui->lineEdit->text() + ".");
    }
}

void MainWindow::unary_pm() {

}

void MainWindow::print_ans()
{
    QByteArray tmp = ui->lineEdit->text().toLocal8Bit();
    char *ptr = tmp.data();
    double ans = toPostfix(ptr);
    if (error != 0) {
        ui->lineEdit->setText("error");
    } else {
        ui->lineEdit->setText(QString::number(ans));
    }
}

void MainWindow::delete_zero() {
    if (ui->lineEdit->text() == "0") {
        ui->lineEdit->clear();
    }
}

void MainWindow::on_pushButton_calc_clicked() {
    credit_calc credit = {{0}, 0, 0, 0};
    double creditSum = ui->lineEdit_creditSum->text().toDouble();
    int term = ui->lineEdit_term->text().toInt();
    if (ui->comboBox->currentText() == "годы") {
        term *=12;
    }
    if (term <= 60) {
        double interestRate = ui->lineEdit_interestRate->text().toDouble();
        if (ui->radioButton_a->isChecked()) {
            ann_credit(creditSum, interestRate, term, &credit);
            ui->lineEdit_monthlyPayment->setText(QString::number(credit.a));
        } else {
            diff_credit(creditSum, interestRate, term, &credit);
            ui->lineEdit_monthlyPayment->setText(QString::number(credit.mounthly_payment[0]) + "..." + QString::number(credit.mounthly_payment[term - 1]));
        }
        ui->lineEdit_overpayment->setText(QString::number(credit.overpayment_credit));
        ui->lineEdit_totalPayout->setText(QString::number(credit.sum));
    }
}


void MainWindow::on_pushButton_depositCalc_clicked() {
    deposit_calc_i depositInt = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    deposit_calc_o depositOut = {0, 0, 0};
    depositInt.depositSum = ui->lineEdit_depositSum->text().toDouble();
    depositInt.term = ui->lineEdit_term_2->text().toDouble();
    if (ui->comboBox_term->currentText() == "годы") {
        depositInt.term *= 12;
    }
    depositInt.interestRate = ui->lineEdit_interestRate_2->text().toDouble();
    if (ui->comboBox_cap->currentText() == "раз в день") {
        depositInt.freqCap = 0;
    } else if (ui->comboBox_cap->currentText() == "раз в месяц") {
        depositInt.freqCap = 1;
    } else if (ui->comboBox_cap->currentText() == "раз в квартал") {
        depositInt.freqCap = 2;
    }
    if (ui->checkBox_cap->isChecked()) {
        depositInt.typeCap = 1;
    } else {
        depositInt.typeCap = 0;
    }
    deposit(&depositInt, &depositOut);
    ui->lineEdit_accruedInterest->setText(QString::number(depositOut.accruedInterest));
    ui->lineEdit_tax->setText(QString::number(depositOut.tax));
    ui->lineEdit_finalPayout->setText(QString::number(depositOut.finalPayout));
}


void MainWindow::on_pushButton_graph_clicked() {

    double xmin = ui->doubleSpinBox_xmin->value();
    double xmax = ui->doubleSpinBox_xmax->value();
    double ymin = ui->doubleSpinBox_ymin->value();
    double ymax = ui->doubleSpinBox_ymax->value();
    if (xmin >= xmax) {
        xmin = -10;
        xmax = 10;
    }
    if (ymin >= ymax) {
        ymin = -10;
        ymax = 10;
    }
    grWindow->show();
    emit drawGraph(ui->lineEdit->text(), xmin, xmax, ymin, ymax);
}


void MainWindow::on_pushButton_xValue_clicked() {
   QString expr = ui->lineEdit->text();
   expr.replace("x", QString::number(ui->doubleSpinBox_xValue->value()));
   QByteArray byt_arr = expr.toLocal8Bit().data();
   double ans = toPostfix(byt_arr.data());
   if (error != 0) {
       ui->lineEdit->setText("error");
   } else {
       ui->lineEdit->setText(QString::number(ans));
   }
}

