#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    nextBtn();
    calculate();
    cardInput();
    loadImage();
}

void MainWindow::calculate(){
    nextBtn();
    double cost = 0;
    if(ui->kingBtn->isChecked() && ui->atriumBtn->isChecked()){
        cost += KING_ATRIUM;
        ui->roomCostLabel->setText("Room Cost: $" + QString::number(KING_ATRIUM * ui->numDays->value(),'f',2));
        ui->roomTypeLbl->setText("Room Type: King Atrium");
    }else if(ui->queenBtn->isChecked() && ui->atriumBtn->isChecked()){
        cost += QUEEN_ATRIUM;
        ui->roomCostLabel->setText("Room Cost: $" + QString::number(QUEEN_ATRIUM * ui->numDays->value(),'f',2));
        ui->roomTypeLbl->setText("Room Type: Queen Atrium");
    }else if(ui->kingBtn->isChecked() && ui->standardBtn->isChecked()){
        cost += KING_STANDARD;
        ui->roomCostLabel->setText("Room Cost: $" + QString::number(KING_STANDARD * ui->numDays->value(),'f',2));
        ui->roomTypeLbl->setText("Room Type: King Standard");
    }else if(ui->queenBtn->isChecked() && ui->standardBtn->isChecked()){
        cost += QUEEN_STANDARD;
        ui->roomCostLabel->setText("Room Cost: $" + QString::number(QUEEN_STANDARD * ui->numDays->value(),'f',2));
        ui->roomTypeLbl->setText("Room Type: Queen Standard");
    }
    if(ui->parkingBtn->isChecked()){
        cost += PARKING;
        ui->parkingCostLabel->setText("Parking Cost: $" + QString::number(PARKING*ui->numDays->value(),'f',2));
    }
    //Second page
    cost *= ui->numDays->value();
    ui->costLbl->setText("Price: $" + QString::number(cost,'f',2));
    ui->taxCostLabel->setText("Tax Cost: $" + QString::number(cost*.15,'f',2));
    ui->totalCostLabel->setText("Total Cost: $"+ QString::number(cost*1.15,'f',2));
    ui->resortFeeCostLabel->setText("Resort Fee Cost: $" +QString::number(RESORT_FEE*ui->numDays->value(),'f',2));
    //Third page
    ui->amountDueLbl->setText("Amount due: $" + QString::number(cost*1.15,'f',2));
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
        ui->creditCardLineEdit->setInputMask("3999-999999-99999;0");
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
    QString queenFilename = ":/images/queen.jpeg";
    if(queenImg.load(queenFilename)){
        queenImg = queenImg.scaled(ui->imgLbl->size(), Qt::KeepAspectRatioByExpanding);
    }
    ui->imgLbl->setPixmap(queenImg);
    calculate();
}

void MainWindow::on_kingBtn_clicked(){
    QString kingFilename = ":/images/king.jpeg";
    if(kingImg.load(kingFilename)){
        kingImg = kingImg.scaled(ui->imgLbl->size(), Qt::KeepAspectRatioByExpanding);
    }
    ui->imgLbl->setPixmap(kingImg);
    calculate();
}

void MainWindow::on_atriumBtn_clicked(){
    QString atriumFilename = ":/images/atrium.jpg";
    if(atriumImg.load(atriumFilename)){
        atriumImg = atriumImg.scaled(ui->imgLbl->size(), Qt::KeepAspectRatioByExpanding);
    }
    ui->imgLbl->setPixmap(atriumImg);
    calculate();
}

void MainWindow::on_standardBtn_clicked(){
    QString standardFilename = ":/images/standard.jpg";
    if(standardImg.load(standardFilename)){
        standardImg = standardImg.scaled(ui->imgLbl->size(), Qt::KeepAspectRatioByExpanding);
    }
    ui->imgLbl->setPixmap(standardImg);
    calculate();
}

void MainWindow::on_parkingBtn_clicked(){
    calculate();
}

void MainWindow::on_numDays_valueChanged(int arg1){
    ui->numNightsLbl->setText("Number of Nights: " + QString::number(arg1));
    calculate();
}

void MainWindow::on_visaRadioButton_clicked(){
    cardInput();
}

void MainWindow::on_masterCardRadioButton_clicked(){
    cardInput();
}

void MainWindow::on_discoverRadioButton_clicked(){
    cardInput();
}

void MainWindow::on_americanExpressRadioButton_clicked(){
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
    if(ui->kingBtn->isChecked()){
        max = 3;

    }
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
    ui->thankYouLbl->setText("Thank you " + name + " for \npurchasing from the Lemachoy bois!");
}

void MainWindow::on_backButton_clicked(){
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_payButton_clicked(){
    QMessageBox payMessage;
    QString payText = "Your transaction has been finalized!";
    payMessage.setText(payText);
    payMessage.exec();
    ui->stackedWidget->setCurrentIndex(2);
    //Credit card info to next page
    QString cardDigits = ui->creditCardLineEdit->text();
    QStringRef subString(&cardDigits,cardDigits.size()-4,4);
    ui->creditInfoLbl->setText("Credit Card Ending in: " + subString);
}


void MainWindow::loadImage(){
    QString queenFilename = ":/images/queen.jpeg";
    if(queenImg.load(queenFilename)){
        queenImg = queenImg.scaled(ui->imgLbl->size(), Qt::KeepAspectRatioByExpanding);
    }
    ui->imgLbl->setPixmap(queenImg);
}
