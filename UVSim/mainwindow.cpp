#include <iostream>
#include <sstream>
#include <QMessageBox>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "operations.h"

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
void MainWindow::createLists(){
    std::ostringstream temp;
    ui->memoryTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Memory"));
    ui->instructionTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Instructions"));
    this->instructions.resize(100);
    this->instructMemoryLocations.resize(100);
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
        ui->memoryTable->setItem(i,0,new QTableWidgetItem("0"));
        ui->instructionTable->setItem(i,0,new QTableWidgetItem(""));
    }
    ui->memoryTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_runInstructionButton_clicked()
{
    this->waitingForInputFromAll = false;

    if(this->mainMemory.getMemoryLocation() < this->mainMemory.getMemoryList().size()){
        std::ostringstream memoryLocationText;
        std::ostringstream instructionText;
        QTableWidgetItem *temp = ui->instructionTable->item(this->mainMemory.getMemoryLocation(),0);
        if(temp->text().length() >= 5 && (temp->text().at(0) == QString::fromStdString("+") || temp->text().at(0) == QString::fromStdString("-"))){
            for(int j = 0; j < 3; j++){
                QString qTemp = temp->text().at(j);
                instructionText << qTemp.toStdString();
                if(j<2){
                    QString qTemp = temp->text().at(j+3);
                    memoryLocationText << qTemp.toStdString();
                }
            }
            std::cout << instructionText.str() << std::endl;
            std::cout << memoryLocationText.str() << std::endl;
            try{
                int instructionInt = std::stoi(instructionText.str());
                int memoryLocationInt = std::stoi(memoryLocationText.str());
                if(instructionInt == 10 || instructionInt == -10){
                    ui->textInput->setPlaceholderText("Please type a number");
                    this->instructionMemoryLocation = memoryLocationInt;
                    this->enableInput();
                    this->mainMemory.setMemoryLocation(this->mainMemory.getMemoryLocation() + 1);
                }
                else if(instructionInt == 11 || instructionInt == -11){
                    //Gives pop up instead of using write function so it displays on GUI
                    QString writeMsg = QString("The value in memory location %1 is %2").arg(QString::number(memoryLocationInt)).arg(QString::number(this->mainMemory.getValueAt(memoryLocationInt)));
                    QMessageBox::about(this, "Write Command", writeMsg);
                    this->mainMemory.setMemoryLocation(this->mainMemory.getMemoryLocation() + 1);
                }
                else{
                    doInstruction(instructionInt,memoryLocationInt,&this->mainMemory);

                }
                temp->setBackground(QColor::fromRgb(3,223,252));
                if(instructionInt == 21 || instructionInt == -21){
                    ui->memoryTable->setItem(memoryLocationInt,0,new QTableWidgetItem(QString::number(mainMemory.getAccumulator())));
                }
            }
            catch(...){
                temp->setBackground(QColor::fromRgb(255,0,0));

            }
        }
        else{
            temp->setBackground(QColor::fromRgb(255,0,0));
            this->mainMemory.setMemoryLocation(this->mainMemory.getMemoryLocation() + 1);

        }
        std::cout << mainMemory.getMemoryLocation() << std::endl;
        ui->instructionTable->selectRow(this->mainMemory.getMemoryLocation()-1);
        ui->accumulatorInt->setText(QString::fromStdString(std::to_string(this->mainMemory.getAccumulator())));

    }

}


void MainWindow::on_inputButton_clicked()
{
    try{
        QString tempStr = ui->textInput->toPlainText();
        int temp = std::stoi(ui->textInput->toPlainText().toStdString());
        READ(this->instructionMemoryLocation,&this->mainMemory,temp);
        ui->memoryTable->setItem(instructionMemoryLocation,0,new QTableWidgetItem(tempStr)); //Makes value visible within the memory table
        ui->textInput->setEnabled(false);
        ui->textInput->setPlaceholderText(""); //Clears message/clarifies as inactive
        ui->textInput->clear();
        ui->inputButton->setEnabled(false);
        ui->runAllInstructionButtons->setEnabled(true);
        ui->runInstructionButton->setEnabled(true);
        if(this->waitingForInputFromAll == true){
            on_runAllInstructionButtons_clicked();
        }

    }
    catch(...){
        ui->textInput->setPlaceholderText("ERROR: Please type a number");

    }

}


void MainWindow::on_runAllInstructionButtons_clicked()
{
    this->waitingForInputFromAll = false;
    for(int i = this->mainMemory.getMemoryLocation(); i < this->mainMemory.getMemoryList().size() && this->mainMemory.getMemoryLocation() <100; i++){
        std::ostringstream memoryLocationText;
        std::ostringstream instructionText;
        QTableWidgetItem *temp = ui->instructionTable->item(i,0);
        if(temp->text().length() >= 5 && (temp->text().at(0) == QString::fromStdString("+") || temp->text().at(0) == QString::fromStdString("-"))){
            for(int j = 0; j < 3; j++){
                QString qTemp = temp->text().at(j);
                instructionText << qTemp.toStdString();
                if(j<2){
                    QString qTemp = temp->text().at(j+3);
                    memoryLocationText << qTemp.toStdString();
                }
            }
            try{
                int instructionInt = std::stoi(instructionText.str());
                int memoryLocationInt = std::stoi(memoryLocationText.str());
                if(instructionInt == 43 || instructionInt == -43){
                    this->mainMemory.setMemoryLocation(this->mainMemory.getMemoryLocation() + 1);
                    ui->instructionTable->selectRow(i);
                    pause();
                    break;
                }
                else if(instructionInt == 10 || instructionInt == -10){
                    ui->textInput->setPlaceholderText("Please type a number");
                    this->waitingForInputFromAll = true;
                    this->instructionMemoryLocation = memoryLocationInt;
                    this->enableInput();
                    this->mainMemory.setMemoryLocation(this->mainMemory.getMemoryLocation() + 1);
                    temp->setBackground(QColor::fromRgb(3,223,252));
                    ui->instructionTable->selectRow(i);
                    break;
                }
                doInstruction(instructionInt,memoryLocationInt,&this->mainMemory);
                if(instructionInt == 21 || instructionInt == -21){
                    ui->memoryTable->setItem(memoryLocationInt,0,new QTableWidgetItem(QString::number(mainMemory.getAccumulator())));
                }
            }
            catch(...){
                temp->setBackground(QColor::fromRgb(255,0,0));

            }
            std::cout << instructionText.str() << std::endl;
            std::cout << memoryLocationText.str() << std::endl;
            temp->setBackground(QColor::fromRgb(3,223,252));
        }
        else{
            temp->setBackground(QColor::fromRgb(255,0,0));
            this->mainMemory.setMemoryLocation(this->mainMemory.getMemoryLocation() + 1);

        }
        ui->instructionTable->selectRow(i);
        ui->accumulatorInt->setText(QString::fromStdString(std::to_string(this->mainMemory.getAccumulator())));

    }

}

void MainWindow::pause(){
    ui->runAllInstructionButtons->setEnabled(false);
    ui->runInstructionButton->setEnabled(false);
    ui->unPauseButton->setEnabled(true);

}
void MainWindow::enableInput(){
    ui->runAllInstructionButtons->setEnabled(false);
    ui->runInstructionButton->setEnabled(false);
    ui->textInput->setEnabled(true);
    ui->inputButton->setEnabled(true);
}



void MainWindow::on_unPauseButton_clicked()
{

    ui->unPauseButton->setEnabled(false);
    on_runAllInstructionButtons_clicked();
}






void MainWindow::on_resetButton_clicked()
{
    std::cout << "resetting" << std::endl;
    for(int i = 0; i < mainMemory.getMemoryList().size(); i++){
        mainMemory.setValueAt(0,i);
    }
    mainMemory.setMemoryLocation(0);
    mainMemory.setAccumulator(0);
    ui->accumulatorInt->setText("0"); //Displays accumulator as 0 on reset
    createLists();
}

void MainWindow::on_loadButton_clicked()
{

}

void MainWindow::on_saveButton_clicked()
{

}


