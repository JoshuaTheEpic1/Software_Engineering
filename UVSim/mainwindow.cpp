#include <iostream>
#include <stdexcept>
#include <sstream>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QRegularExpression>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "operations.h"
#include <QClipboard>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->memoryTable->setRowCount(this->mainMemory.getMemoryList().size());
    ui->memoryTable->setColumnCount(1);
    ui->instructionTable->setRowCount(this->mainMemory.getMemoryList().size());
    ui->instructionTable->setColumnCount(1);
    ui->redPrimary->setValidator( new QIntValidator(0, 100, this));
    ui->bluePrimary->setValidator( new QIntValidator(0, 100, this));
    ui->greenPrimary->setValidator( new QIntValidator(0, 100, this));
    ui->greenSecondary->setValidator( new QIntValidator(0, 100, this));
    ui->blueSecondary->setValidator( new QIntValidator(0, 100, this));
    ui->redSecondary->setValidator( new QIntValidator(0, 100, this));
    ui->file1Button->setEnabled(false);
    ui->file2ButtonBorder->hide();
    ui->file3ButtonBorder->hide();
    ui->haltedText->hide();
    ui->defaultColors->hide();
    toggleColor();

}
void MainWindow::createLists(){
    std::ostringstream temp;

    ui->memoryTable->setHorizontalHeaderItem(0, new QTableWidgetItem("memory"));
    ui->instructionTable->setHorizontalHeaderItem(0,  new QTableWidgetItem("Instructions"));
    this->instructions.resize(this->mainMemory.getMemoryList().size());
    this->instructMemoryLocations.resize(this->mainMemory.getMemoryList().size());
    for(int i=0; i < this->mainMemory.getMemoryList().size(); i++){

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
            if(this->fourDigitInput == false && this->sixDigitInput == false){
                if(temp->text().length() == 5){
                    this->fourDigitInput = true;
                }else if(temp->text().length() == 7){
                    this->sixDigitInput = true;
                }
            }
            if(temp->text().length() == 5 && fourDigitInput == true){
                for(int j = 0; j < 3; j++){
                    QString qTemp = temp->text().at(j);
                    instructionText << qTemp.toStdString();
                    if(j<2){
                        QString qTemp = temp->text().at(j+3);
                        memoryLocationText << qTemp.toStdString();
                    }
                }
            }else if(temp->text().length() == 7 && sixDigitInput == true){
                for(int j = 0; j < 4; j++){
                    QString qTemp = temp->text().at(j);
                    instructionText << qTemp.toStdString();
                    if(j<=2){
                        QString qTemp = temp->text().at(j+4);
                        memoryLocationText << qTemp.toStdString();
                    }
                }
            }
            else{
            this->mainMemory.setMemoryLocation(this->mainMemory.getMemoryLocation()+1);
            }
            try{
                int instructionInt = std::stoi(instructionText.str());
                int memoryLocationInt = std::stoi(memoryLocationText.str());
                if(memoryLocationInt > 249){
                    throw std::out_of_range("Main memory is too large");
                }
                if(instructionInt == 10 || instructionInt == -10){
                    ui->textInput->setPlaceholderText("Please type a number");
                    this->instructionMemoryLocation = memoryLocationInt;
                    disableFileButtons();
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
                this->mainMemory.setMemoryLocation(this->mainMemory.getMemoryLocation() + 1);

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
        enableFileButtons();
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

    for(int i = this->mainMemory.getMemoryLocation(); i < this->mainMemory.getMemoryList().size() && this->mainMemory.getMemoryLocation() < this->mainMemory.getMemoryList().size(); i++){
        std::ostringstream memoryLocationText;
        std::ostringstream instructionText;
        QTableWidgetItem *temp = ui->instructionTable->item(i,0);

        if(temp->text().length() >= 5 && (temp->text().at(0) == QString::fromStdString("+") || temp->text().at(0) == QString::fromStdString("-"))){
            if(this->fourDigitInput == false && this->sixDigitInput == false){
                if(temp->text().length() == 5){
                    this->fourDigitInput = true;
                }else if(temp->text().length() == 7){
                    this->sixDigitInput = true;
                }
            }
            if(temp->text().length() == 5 && fourDigitInput == true){
                for(int j = 0; j < 3; j++){
                    QString qTemp = temp->text().at(j);
                    instructionText << qTemp.toStdString();
                     if(j<2){
                        QString qTemp = temp->text().at(j+3);
                        memoryLocationText << qTemp.toStdString();
                    }
                }
            }else if(temp->text().length() == 7 && sixDigitInput == true){
                for(int j = 0; j < 4; j++){
                    QString qTemp = temp->text().at(j);
                    instructionText << qTemp.toStdString();
                    if(j<=2){
                        QString qTemp = temp->text().at(j+4);
                        memoryLocationText << qTemp.toStdString();
                    }
                }
            }
            else{
                this->mainMemory.setMemoryLocation(this->mainMemory.getMemoryLocation()+1);
            }
            try{
                int instructionInt = std::stoi(instructionText.str());
                int memoryLocationInt = std::stoi(memoryLocationText.str());
                if(memoryLocationInt > 249){
                    throw std::out_of_range("Main memory is too large");
                }
                if(instructionInt == 43 || instructionInt == -43){
                    this->mainMemory.setMemoryLocation(this->mainMemory.getMemoryLocation() + 1);
                    ui->instructionTable->selectRow(i);
                    temp->setBackground(QColor::fromRgb(3,223,252));
                    pause();
                    break;
                }
                else if(instructionInt == 10 || instructionInt == -10){
                    ui->textInput->setPlaceholderText("Please type a number");
                    this->waitingForInputFromAll = true;
                    this->instructionMemoryLocation = memoryLocationInt;
                    this->enableInput();
                    disableFileButtons();
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
    ui->haltedText->show();
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
    ui->haltedText->hide();
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
    // Open file dialog to select a text file
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Instruction File"), "", tr("Text Files (*.txt)"));
    
    // Check if a file was selected
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot open file: ") + file.errorString());
        return;
    }

    QTextStream in(&file);
    QString line;
    int row = 0;

    // Read the file line by line
    while (!in.atEnd() && row < this->mainMemory.getMemoryList().size()) {
        line = in.readLine();
        
        // Validate the instruction format, automatically skipping invalidly formatted instructions
        QRegularExpression regex("^[+-]\\d{4}$");
        QRegularExpressionMatch match = regex.match(line);
        if (match.hasMatch()) {
            ui->instructionTable->setItem(row, 0, new QTableWidgetItem(line));
            row++;
        }
    }

    file.close();
}

void MainWindow::on_saveButton_clicked()
{
    // Open file dialog to select a location to save the text file
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Instruction File"), "", tr("Text Files (*.txt)"));
    
    // Check if a file name was provided
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot open file: ") + file.errorString());
        return;
    }

    QTextStream out(&file);

    // Iterate through the instructionTable and write each instruction to the file
    for (int row = 0; row < this->mainMemory.getMemoryList().size(); ++row) {
        QTableWidgetItem *item = ui->instructionTable->item(row, 0);
        if (item) {
            QString instruction = item->text();
            if (!instruction.isEmpty()) {
                out << instruction << "\n";
            }
        }
    }

    file.close();
    QMessageBox::information(this, tr("Success"), tr("Instructions saved successfully."));
}



void MainWindow::on_customizeColor_clicked()
{
    ui->customizeColor->hide();
    toggleColor();

}
void MainWindow::toggleColor(){
    ui->colorErrorText->hide();
    if(ui->redPrimary->isHidden()){
        ui->redPrimary->show();
        ui->redSecondary->show();
        ui->greenPrimary->show();
        ui->greenSecondary->show();
        ui->blueSecondary->show();
        ui->bluePrimary->show();
        ui->primaryText->show();
        ui->secondaryText->show();
        ui->confirmColor->show();
        ui->defaultColors->show();
    }
    else{
        ui->redPrimary->hide();
        ui->redSecondary->hide();
        ui->greenPrimary->hide();
        ui->greenSecondary->hide();
        ui->blueSecondary->hide();
        ui->bluePrimary->hide();
        ui->primaryText->hide();
        ui->secondaryText->hide();
        ui->confirmColor->hide();
        ui->defaultColors->hide();
    }

}

void MainWindow::on_confirmColor_clicked()
{
    int red;
    int green;
    int blue;
    std::stringstream s;
    ui->customizeColor->show();
    toggleColor();
    if(ui->redPrimary->text() != "" && ui->bluePrimary->text() != "" && ui->greenPrimary->text() != ""){
        red = ui->redPrimary->text().toInt();
        green = ui->greenPrimary->text().toInt();
        blue = ui->bluePrimary->text().toInt();

        if(red > 255 || red < 0 || blue > 255 || blue < 0 || green > 255 || green < 0){
            ui->colorErrorText->show();

        }
        else{
        s << "background-color: rgb(" << red << ","<< green << "," << blue << ");";
        ui->centralwidget->setStyleSheet(QString::fromStdString(s.str()));
        }
    }
    if(ui->redSecondary->text() != "" && ui->blueSecondary->text() != "" && ui->greenSecondary->text() != ""){
        red = ui->redSecondary->text().toInt();
        green = ui->greenSecondary->text().toInt();
        blue = ui->blueSecondary->text().toInt();
        if(red > 255 || red < 0 || blue > 255 || blue < 0 || green > 255 || green < 0){
            ui->colorErrorText->show();
        }
        else{
            s.str("");
            s << "background-color: rgb(" << red << ","<< green << "," << blue << ");" << "\n color: rgb(0,0,0);";
            ui->confirmColor->setStyleSheet(QString::fromStdString(s.str()));
            ui->customizeColor->setStyleSheet(QString::fromStdString(s.str()));
            ui->inputButton->setStyleSheet(QString::fromStdString(s.str()));
            ui->loadButton->setStyleSheet(QString::fromStdString(s.str()));
            ui->saveButton->setStyleSheet(QString::fromStdString(s.str()));
            ui->resetButton->setStyleSheet(QString::fromStdString(s.str()));
            ui->unPauseButton->setStyleSheet(QString::fromStdString(s.str()));
            ui->runAllInstructionButtons->setStyleSheet(QString::fromStdString(s.str()));
            ui->runInstructionButton->setStyleSheet(QString::fromStdString(s.str()));
            ui->file1Button->setStyleSheet(QString::fromStdString(s.str()));
            ui->file2Button->setStyleSheet(QString::fromStdString(s.str()));
            ui->file3Button->setStyleSheet(QString::fromStdString(s.str()));
            ui->defaultColors->setStyleSheet(QString::fromStdString(s.str()));
        }
    }

}

void MainWindow::paste(){
    //clip board copy/paste testing to help josh
    QString temp = QApplication::clipboard()->text(); // grabs the text from the clipboard (what ever is copied on your computer)
    QStringList lines = temp.split("\n", Qt::SkipEmptyParts); // creates a list from the clipboard each list element is what was seperated by a new line
    stringstream temp2; // a string you can put the lines into for testing
    for(int i = 0; i < lines.size(); i++){   // a for loop that goes through each element in the list
        temp2 << lines[i].toStdString() << "\n"; // puts the element into the test string above and adds a new line after converting it to standard string
        std::cout << lines[i].toStdString() << endl; // outputs the element [i] to the clipboard as a standard string instead of QString
    }
    temp2 << "hello hello" << endl; // added to test setting to clip board
    QApplication::clipboard()->setText(QString::fromStdString(temp2.str())); // this will set the clipboard with the text you want to have copied in this case original + hello hello

    std::cout << "paste pressed" << std::endl;

}

void MainWindow::copy(){
    std::cout << "copied pressed" << std::endl;
}



void MainWindow::on_file1Button_clicked()
{
    ui->file1Button->setEnabled(false);
    ui->file1ButtonBorder->setHidden(false);
    if(ui->file2Button->isEnabled() == false){    // if button two isn't enabled it enables it
        ui->file2Button->setEnabled(true);
        ui->file2ButtonBorder->setHidden(true);
        saveToClass(&this->instructionsFile2, &this->mainMemoryFile2);

    }
    if(ui->file3Button->isEnabled() == false){
        ui->file3Button->setEnabled(true);
        ui->file3ButtonBorder->setHidden(true);
        saveToClass(&this->instructionsFile3,&this->mainMemoryFile3);
    }
    setMemoryAndInstructions(&instructionsFile1,&mainMemoryFile1);
}


void MainWindow::on_file2Button_clicked()
{
    ui->file2Button->setEnabled(false);
    ui->file2ButtonBorder->setHidden(false);
    if(ui->file1Button->isEnabled() == false){    // if button two isn't enabled it enables it
        ui->file1Button->setEnabled(true);
        ui->file1ButtonBorder->setHidden(true);
        saveToClass(&this->instructionsFile1, &this->mainMemoryFile1);

    }
    if(ui->file3Button->isEnabled() == false){
        ui->file3Button->setEnabled(true);
        ui->file3ButtonBorder->setHidden(true);
        saveToClass(&this->instructionsFile3,&this->mainMemoryFile3);
    }
    setMemoryAndInstructions(&instructionsFile2,&mainMemoryFile2);
}


void MainWindow::on_file3Button_clicked()
{
    ui->file3Button->setEnabled(false);
    ui->file3ButtonBorder->setHidden(false);
    if(ui->file2Button->isEnabled() == false){    // if button two isn't enabled it enables it
        ui->file2Button->setEnabled(true);
        ui->file2ButtonBorder->setHidden(true);
        saveToClass(&this->instructionsFile2, &this->mainMemoryFile2);

    }
    if(ui->file1Button->isEnabled() == false){
        ui->file1Button->setEnabled(true);
        ui->file1ButtonBorder->setHidden(true);
        saveToClass(&this->instructionsFile1, &this->mainMemoryFile1);
    }
    setMemoryAndInstructions(&instructionsFile3,&mainMemoryFile3);
}

void MainWindow::setMemoryAndInstructions(Instructions* instruct,MainMemory* memory){
    if(instruct->fourDigitInput == true){
        this->fourDigitInput = true;
    }
    if(instruct->sixDigitInput == true){
        this->sixDigitInput = true;
    }
    if(ui->unPauseButton->isEnabled()){
        ui->haltedText->hide();
        ui->unPauseButton->setEnabled(false);
        ui->runAllInstructionButtons->setEnabled(true);
        ui->runInstructionButton->setEnabled(true);
    }
    this->mainMemory.setAll(memory->getMemoryList(),memory->getMemoryLocation(),memory->getAccumulator());
    ui->accumulatorInt->setText(QString::number(this->mainMemory.getAccumulator()));
    for(int i = 0; i < instruct->getFullInstructionTable().size(); i++){
        QTableWidgetItem *temp = ui->instructionTable->item(i,0);
        QTableWidgetItem *temp2 = ui->memoryTable->item(i,0);
        temp->setText(instruct->getFullInstructionTable().at(i));
        temp2->setText(QString::number(memory->getValueAt(i)));
        if(i > this->mainMemory.getMemoryLocation()){
            temp->setBackground(QColorConstants::White);
        }else if(i < this->mainMemory.getMemoryLocation()){
            if(temp->text().length() == 5 && this->sixDigitInput == true){
                temp->setBackground(QColor::fromRgb(3,223,252));
            }
            else if(temp->text().length() == 7 && this->sixDigitInput == true){
                temp->setBackground(QColor::fromRgb(3,223,252));
            }
            else{
                temp->setBackground(QColor::fromRgb(154, 154, 154));
            }
        }


    }
    if(this->mainMemory.getMemoryLocation() > 0){
        this->ui->instructionTable->selectRow(this->mainMemory.getMemoryLocation()-1);
    }else{
        this->ui->instructionTable->selectRow(this->mainMemory.getMemoryLocation());
    }


}
void MainWindow::saveToClass(Instructions *instruct,MainMemory *memory){
    if(this->fourDigitInput == true){
        instruct->fourDigitInput = true;
    }
    if(this->sixDigitInput == true){
        instruct->sixDigitInput = true;
    }
    memory->setAll(this->mainMemory.getMemoryList(),this->mainMemory.getMemoryLocation(),this->mainMemory.getAccumulator());
    for(int i = 0; i < instruct->getFullInstructionTable().size(); i++){
        QTableWidgetItem *temp = ui->instructionTable->item(i,0);
        instruct->setInstruction(i,temp->text());
    }

}
void MainWindow::disableFileButtons(){
    if(ui->file1ButtonBorder->isHidden()){
            ui->file1Button->setEnabled(false);
    }
    if(ui->file2ButtonBorder->isHidden()){
            ui->file2Button->setEnabled(false);

    }
    if(ui->file3ButtonBorder->isHidden()){
            ui->file3Button->setEnabled(false);
    }
}

void MainWindow::enableFileButtons(){
    if(ui->file1ButtonBorder->isHidden()){
            ui->file1Button->setEnabled(true);
    }
    if(ui->file2ButtonBorder->isHidden()){
            ui->file2Button->setEnabled(true);
    }
    if(ui->file3ButtonBorder->isHidden()){
            ui->file3Button->setEnabled(true);
    }
}

void MainWindow::on_defaultColors_clicked()
{

    ui->centralwidget->setStyleSheet("background-color: rgb(76, 114, 29);");
    ui->confirmColor->setStyleSheet("background-color: rgb(255,255,255);\n color: rgb(0, 0, 0);");
    ui->customizeColor->setStyleSheet("background-color: rgb(255,255,255);\n color: rgb(0, 0, 0)/;");
    ui->inputButton->setStyleSheet("background-color: rgb(255,255,255);\n color: rgb(0, 0, 0)/;");
    ui->loadButton->setStyleSheet("background-color: rgb(255,255,255);\n color: rgb(0, 0, 0)/;");
    ui->saveButton->setStyleSheet("background-color: rgb(255,255,255);\n color: rgb(0, 0, 0)/;");
    ui->resetButton->setStyleSheet("background-color: rgb(255,255,255);\n color: rgb(0, 0, 0)/;");
    ui->unPauseButton->setStyleSheet("background-color: rgb(255,255,255);\n color: rgb(0, 0, 0)/;");
    ui->runAllInstructionButtons->setStyleSheet("background-color: rgb(255,255,255);\n color: rgb(0, 0, 0)/;");
    ui->runInstructionButton->setStyleSheet("background-color: rgb(255,255,255);\n color: rgb(0, 0, 0)/;");
    ui->file1Button->setStyleSheet("background-color: rgb(255,255,255);\n color: rgb(0, 0, 0)/;");
    ui->file2Button->setStyleSheet("background-color: rgb(255,255,255);\n color: rgb(0, 0, 0)/;");
    ui->file3Button->setStyleSheet("background-color: rgb(255,255,255);\n color: rgb(0, 0, 0)/;");
    ui->defaultColors->setStyleSheet("background-color: rgb(255,255,255);\n color: rgb(0, 0, 0)/;");
    toggleColor();



}

