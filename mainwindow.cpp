#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    nextBtn();
    calculate();
    cardInput();
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

void MainWindow::cardInput(){
    if(ui->americanExpressRadioButton->isChecked())
        ui->creditCardLineEdit->setInputMask("3999-999999-99999:0");
    else if(ui->visaRadioButton->isChecked())
        ui->creditCardLineEdit->setInputMask("4999-9999-9999-9999;0");
    else if(ui->masterCardRadioButton->isChecked())
        ui->creditCardLineEdit->setInputMask("5999-9999-9999-9999;0");
    else if(ui->discoverRadioButton->isChecked())
        ui->creditCardLineEdit->setInputMask("6999-9999-9999-9999;0");
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
    ui->numNightsLbl->setText("Number of Nights: " + QString::number(arg1));
    calculate();
}

void MainWindow::on_visaRadioButton_clicked()
{
    cardInput();
}

void MainWindow::on_masterCardRadioButton_clicked()
{
    cardInput();
}

void MainWindow::on_discoverRadioButton_clicked()
{
    cardInput();
}

void MainWindow::on_americanExpressRadioButton_clicked()
{
    cardInput();
}

void MainWindow::on_numAdultsBox_valueChanged(int arg1){
    ui->numAdultsLbl_2->setText("Number of Adults: " + QString::number(arg1));
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
    ui->firstDayLbl->setText("First Day: " + ui->dateInput->text());
    if(ui->parkingBtn->isChecked()){
        ui->ParkingLbl->setText("Parking: YES");
    }else{
        ui->ParkingLbl->setText("Parking: NO");
    }
}

void MainWindow::on_exitButton_clicked(){
    QApplication::quit();
}

void MainWindow::on_nameTxt_textChanged(){
    QString name = ui->nameTxt->toPlainText();
    ui->thankYouLbl->setText("Thank you " + name + " for purchasing from KEVININC!");
}
