#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    nextBtn();
    calculate();
}

void MainWindow::calculate(){
    nextBtn();
    double cost = 0;
    if(ui->kingBtn->isChecked() && ui->atriumBtn->isChecked()){
        cost += KING_ATRIUM;
    }else if(ui->queenBtn->isChecked() && ui->atriumBtn->isChecked()){
        cost += QUEEN_ATRIUM;
    }else if(ui->kingBtn->isChecked() && ui->standardBtn->isChecked()){
        cost += KING_STANDARD;
    }else if(ui->queenBtn->isChecked() && ui->standardBtn->isChecked()){
        cost += QUEEN_STANDARD;
    }
    if(ui->parkingBtn->isChecked()){
        cost += 12.75;
    }
    cost *= ui->numDays->value();
    ui->costLbl->setText("Price: " + QString::number(cost));
}

void MainWindow::nextBtn(){
    bool goNext = true;
    if((!ui->kingBtn->isChecked() && !ui->queenBtn->isChecked()) || (!ui->atriumBtn->isChecked() && !ui->standardBtn->isChecked())){
        goNext = false;
    }else if(ui->numAdultsBox->value() == 0){
        goNext = false;
    }
    ui->nextBtn->setDisabled(!goNext);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_queenBtn_clicked(){
    calculate();
}

void MainWindow::on_kingBtn_clicked(){
    calculate();
}

void MainWindow::on_atriumBtn_clicked(){
    calculate();
}

void MainWindow::on_standardBtn_clicked(){
    calculate();
}

void MainWindow::on_parkingBtn_clicked(){
    calculate();
}

void MainWindow::on_numDays_valueChanged(int arg1){
    calculate();
}

void MainWindow::on_numAdultsBox_valueChanged(int arg1){
    calculate();
}

void MainWindow::on_nextBtn_clicked(){
    bool goNext = true;
    if((!ui->kingBtn->isChecked() && !ui->queenBtn->isChecked()) || (!ui->atriumBtn->isChecked() && !ui->standardBtn->isChecked())){
        goNext = false;
    }else if(ui->numAdultsBox->value() == 0){
        goNext = false;
    }
    int max = 4;
    if(ui->kingBtn->isChecked()) max = 3;
    int numPeople = ui->numChildBox->value() + ui->numAdultsBox->value();
    if(numPeople > max){
        QMessageBox errorMsg;
        QString msg = "You have too many people (max is " +  QString::number(max) + ").";
        errorMsg.setText(msg);
        errorMsg.exec();
    }else if(goNext){
        ui->stackedWidget->setCurrentIndex(1);
    }
}
