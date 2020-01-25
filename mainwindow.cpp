#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    if(!ui->kingBtn->isChecked() && !ui->queenBtn->isChecked()){
        goNext = false;
    }else if(!ui->atriumBtn->isChecked() && !ui->standardBtn->isChecked()){
        goNext = false;
    }else if(!ui->parkingBtn->isChecked()){
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
