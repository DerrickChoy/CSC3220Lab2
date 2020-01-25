#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

const int KING_ATRIUM = 350;
const int KING_STANDARD = 290;
const int QUEEN_ATRIUM = 325;
const int QUEEN_STANDARD= 284;
const double PARKING = 12.75;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void calculate();

    void nextBtn();

    void on_queenBtn_clicked();

    void on_kingBtn_clicked();

    void on_atriumBtn_clicked();

    void on_standardBtn_clicked();

    void on_parkingBtn_clicked();

    void on_numDays_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
