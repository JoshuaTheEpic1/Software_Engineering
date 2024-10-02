#include <iostream>
#include <fstream>
#include <sstream>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

int countingTemp = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->memoryTable->setRowCount(100);
    ui->memoryTable->setColumnCount(1);
    ui->instructionTable->setRowCount(100);
    ui->instructionTable->setColumnCount(1);


}
void MainWindow::CreateLists(){
    std::ostringstream temp;
    ui->memoryTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Memory"));
    ui->instructionTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Instructions"));
    for(int i=0; i < 100; i++){
        if(i < 10){

            temp.str("");
            temp << "0" << i;
            ui->memoryTable->setVerticalHeaderItem(i, new QTableWidgetItem(QString::fromStdString(temp.str())));
        }
        else{
            temp.str("");
            temp << i;
            ui->memoryTable->setVerticalHeaderItem(i, new QTableWidgetItem(QString::fromStdString(temp.str())));
        }
        ui->memoryTable->setItem(i,0,new QTableWidgetItem("NULL"));
        ui->instructionTable->setItem(i,0,new QTableWidgetItem(""));
        if(i % 2 == 0){
            QTableWidgetItem *temp = ui->memoryTable->item(i,0);
            temp->setBackground(Qt::blue);

        }
        else{
            QTableWidgetItem *temp = ui->memoryTable->item(i,0);
            temp->setBackground(Qt::green);
        }
    }

}
void MainWindow::test(){

    QString temp = "test";
    std::cout << temp.toStdString() << std::endl;
    std::cout << ui->accumulator->text().toStdString() << std::endl;
    int test = 10;
    temp = QString::fromStdString(std::to_string(test));
    ui->accumulatorInt->setText(temp);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_runInstructionButton_clicked()
{
    for(int i = countingTemp; i <= countingTemp; i++){
        ui->accumulatorInt->setText(QString::fromStdString(std::to_string(i)));
        if(i % 2 == 0){
            QTableWidgetItem *temp = ui->instructionTable->item(i,0);
            temp->setBackground(Qt::blue);

        }
        else{
            QTableWidgetItem *temp = ui->instructionTable->item(i,0);
            temp->setBackground(Qt::green);
        }
    }
    countingTemp++;
}

