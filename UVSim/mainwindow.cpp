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



// Constructor for MainWindow class
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) // Initialize the base class QMainWindow
    , ui(new Ui::MainWindow) // Create a new UI instance
{

    ui->setupUi(this); // Set up the UI components
    ui->memoryTable->setRowCount(this->mainMemory.getMemoryList().size());// Set row count based on memory size
    ui->memoryTable->setColumnCount(1); // Set column count for memory table
    ui->instructionTable->setRowCount(this->mainMemory.getMemoryList().size()); // Set row count for instruction table
    ui->instructionTable->setColumnCount(1); // Set column count for instruction table

    // Set validators for RGB input fields to allow only numbers between 0 and 100
    ui->redPrimary->setValidator( new QIntValidator(0, 100, this)); 
    ui->bluePrimary->setValidator( new QIntValidator(0, 100, this));
    ui->greenPrimary->setValidator( new QIntValidator(0, 100, this));
    ui->greenSecondary->setValidator( new QIntValidator(0, 100, this));
    ui->blueSecondary->setValidator( new QIntValidator(0, 100, this));
    ui->redSecondary->setValidator( new QIntValidator(0, 100, this));

    // Disable certain buttons and hide UI elements initially
    ui->file1Button->setEnabled(false);
    ui->file2ButtonBorder->hide();
    ui->file3ButtonBorder->hide();
    ui->haltedText->hide();
    ui->defaultColors->hide();
    
    toggleColor(); // Call function to set initial colors

}

// Function to create and initialize lists in the memory and instruction tables
void MainWindow::createLists(){
    std::ostringstream temp; // Temporary string stream for formatting

    // Set horizontal headers for the memory and instruction tables
    ui->memoryTable->setHorizontalHeaderItem(0, new QTableWidgetItem("memory"));
    ui->instructionTable->setHorizontalHeaderItem(0,  new QTableWidgetItem("Instructions"));

    // Resize instruction lists based on memory size
    this->instructions.resize(this->mainMemory.getMemoryList().size());
    this->instructMemoryLocations.resize(this->mainMemory.getMemoryList().size());

    // Loop through memory list to populate table headers and initial values
    for(int i=0; i < this->mainMemory.getMemoryList().size(); i++){
        temp.str(""); // Clear the string stream
        if(i < 10){
            temp << "00" << i; // Format single-digit indices with leading zeros
        }
        else if(i < 100){
            temp << "0" << i; // Format double-digit indices with leading zero
        }
        else {
            temp << i; // Format triple-digit indices
        }

        ui->memoryTable->setVerticalHeaderItem(i, new QTableWidgetItem(QString::fromStdString(temp.str()))); // Set vertical header item
        ui->memoryTable->setItem(i,0,new QTableWidgetItem("0")); // Initialize memory table with zeros
        ui->instructionTable->setItem(i,0,new QTableWidgetItem("")); // Initialize instruction table with empty strings

    }
    ui->memoryTable->setEditTriggers(QAbstractItemView::NoEditTriggers); // Disable editing in memory table
}

// Destructor for MainWindow class
MainWindow::~MainWindow()
{
    delete ui; // Clean up UI resources
}

// Slot function for handling run instruction button click
void MainWindow::on_runInstructionButton_clicked() {
    this->waitingForInputFromAll = false; // Reset input waiting flag

    // Check if the current memory location is valid
    if(this->mainMemory.getMemoryLocation() < this->mainMemory.getMemoryList().size()){
        std::ostringstream memoryLocationText; // Stream for memory location text
        std::ostringstream instructionText; // Stream for instruction text
        QTableWidgetItem *temp = ui->instructionTable->item(this->mainMemory.getMemoryLocation(),0); // Get current instruction item

        // Validate instruction format
        if((temp->text().length() == 5 || temp->text().length() == 7) && (temp->text().at(0) == QString::fromStdString("+") || temp->text().at(0) == QString::fromStdString("-"))){
            // Check for four or six digit input
            if(this->fourDigitInput == false && this->sixDigitInput == false){
                if(temp->text().length() == 5){
                    this->fourDigitInput = true; // Set flag for four-digit input
                }else if(temp->text().length() == 7){
                    this->sixDigitInput = true; // Set flag for six-digit input
                }
            }

            // Process four-digit input
            if(temp->text().length() == 5 && fourDigitInput == true){
                for(int j = 0; j < 3; j++){
                    QString qTemp = temp->text().at(j);
                    instructionText << qTemp.toStdString(); // Build instruction text
                    if(j<2){
                        QString qTemp = temp->text().at(j+3);
                        memoryLocationText << qTemp.toStdString(); // Build memory location text
                    }
                }
            // Process six-digit input
            } else if(temp->text().length() == 7 && sixDigitInput == true){
                for(int j = 0; j < 4; j++){
                    QString qTemp = temp->text().at(j);
                    instructionText << qTemp.toStdString(); // Build instruction text
                    if(j<=2){
                        QString qTemp = temp->text().at(j+4);
                        memoryLocationText << qTemp.toStdString(); // Build memory location text
                    }
                }
            }
            
            try{
                // Convert instruction and memory location text to integers
                int instructionInt = std::stoi(instructionText.str());
                int memoryLocationInt = std::stoi(memoryLocationText.str());
                if(memoryLocationInt > this->mainMemory.getMemoryList().size()){
                    throw std::out_of_range("Main memory is too large"); // Check for out-of-range memory access
                }

                // Handle specific instructions
                if(instructionInt == 10 || instructionInt == -10){
                    ui->textInput->setPlaceholderText("Please type a number"); // Prompt for input
                    this->instructionMemoryLocation = memoryLocationInt; // Set instruction memory location
                    disableFileButtons(); // Disable file buttons
                    this->enableInput(); // Enable input
                    this->mainMemory.setMemoryLocation(this->mainMemory.getMemoryLocation() + 1); // Move to next memory location
                }
                else if(instructionInt == 11 || instructionInt == -11){
                   // Display value in memory location via pop-up
                    QString writeMsg = QString("The value in memory location %1 is %2").arg(QString::number(memoryLocationInt)).arg(QString::number(this->mainMemory.getValueAt(memoryLocationInt)));
                    QMessageBox::about(this, "Write Command", writeMsg); // Show message box
                    this->mainMemory.setMemoryLocation(this->mainMemory.getMemoryLocation() + 1); // Move to next memory location
                }
                else{
                    doInstruction(instructionInt,memoryLocationInt,&this->mainMemory); // Execute the instruction
                }
                
                // Highlight the executed instruction
                temp->setBackground(QColor::fromRgb(3,223,252));
                if(instructionInt == 21 || instructionInt == -21){
                    ui->memoryTable->setItem(memoryLocationInt,0,new QTableWidgetItem(QString::number(mainMemory.getAccumulator())));
                }
            }
            catch(...){
                temp->setBackground(QColor::fromRgb(255,0,0)); // Highlight error in red
                this->mainMemory.setMemoryLocation(this->mainMemory.getMemoryLocation() + 1); // Move to next memory location

            }
        }
        else{
            temp->setBackground(QColor::fromRgb(255,0,0)); // Highlight error in red
            this->mainMemory.setMemoryLocation(this->mainMemory.getMemoryLocation() + 1); // Move to next memory location

        }
        std::cout << mainMemory.getMemoryLocation() << std::endl; // Output current memory location to console
        ui->instructionTable->selectRow(this->mainMemory.getMemoryLocation()-1); // Select the current instruction row
        ui->accumulatorInt->setText(QString::fromStdString(std::to_string(this->mainMemory.getAccumulator()))); // Update accumulator display

    }

}

// Slot function for handling input button click
void MainWindow::on_inputButton_clicked()
{
    try{
        enableFileButtons();// Enable file-related buttons
        QString tempStr = ui->textInput->toPlainText(); // Get text input from the UI
        int temp = std::stoi(ui->textInput->toPlainText().toStdString()); // Convert input text to integer
        READ(this->instructionMemoryLocation,&this->mainMemory,temp); // Read value into main memory
        
        // Update memory table to display the input value
        ui->memoryTable->setItem(instructionMemoryLocation,0,new QTableWidgetItem(tempStr)); //Makes value visible within the memory table
        ui->textInput->setEnabled(false); // Disable text input field
        ui->textInput->setPlaceholderText(""); // Clear placeholder text
        ui->textInput->clear(); // Clear the input field
        ui->inputButton->setEnabled(false); // Disable input button
        ui->runAllInstructionButtons->setEnabled(true); // Enable run all instructions button
        ui->runInstructionButton->setEnabled(true); // Enable run instruction button

        // If waiting for input from all, trigger the run all instructions function
        if(this->waitingForInputFromAll == true){
            on_runAllInstructionButtons_clicked();
        }

    }
    catch(...){
        // Handle any exceptions by prompting the user to enter a valid number
        ui->textInput->setPlaceholderText("ERROR: Please type a number");

    }

}

// Slot function for handling the run all instruction button click
void MainWindow::on_runAllInstructionButtons_clicked()
{
    this->waitingForInputFromAll = false; // Reset waiting flag

    // Loop through memory locations starting from the current memory location
    for(int i = this->mainMemory.getMemoryLocation(); i < this->mainMemory.getMemoryList().size() && this->mainMemory.getMemoryLocation() < this->mainMemory.getMemoryList().size(); i++){
        std::ostringstream memoryLocationText; // Stream for memory location text
        std::ostringstream instructionText; // Stream for instruction text
        QTableWidgetItem *temp = ui->instructionTable->item(i,0); // Get current instruction item

        // Stop execution if the instruction cell is empty
        if(temp->text().isEmpty()){
            ui->runAllInstructionButtons->setEnabled(true);
            ui->runInstructionButton->setEnabled(true);

            break;
        }

        // Validate instruction format
        if((temp->text().length() == 5 || temp->text().length() == 7) && (temp->text().at(0) == QString::fromStdString("+") || temp->text().at(0) == QString::fromStdString("-"))){ // very simple validation.
            // Check for four or six digit input
            if(this->fourDigitInput == false && this->sixDigitInput == false){
                if(temp->text().length() == 5){
                    this->fourDigitInput = true; // Set flag for four-digit input
                }else if(temp->text().length() == 7){
                    this->sixDigitInput = true; // Set flag for six-digit input
                }
            }

            // Process four-digit input
            if(temp->text().length() == 5 && fourDigitInput == true){
                for(int j = 0; j < 3; j++){
                    QString qTemp = temp->text().at(j);
                    instructionText << qTemp.toStdString(); // Build instruction text
                     if(j<2){
                        QString qTemp = temp->text().at(j+3);
                        memoryLocationText << qTemp.toStdString(); // Build memory location text
                    }
                }

            // Process six-digit input
            }else if(temp->text().length() == 7 && sixDigitInput == true){
                for(int j = 0; j < 4; j++){
                    QString qTemp = temp->text().at(j);
                    instructionText << qTemp.toStdString(); // Build instruction text
                    if(j<=2){
                        QString qTemp = temp->text().at(j+4);
                        memoryLocationText << qTemp.toStdString(); // Build memory location text
                    }
                }
            }
            try{
                // Convert instruction and memory location text to integers
                int instructionInt = std::stoi(instructionText.str()); 
                int memoryLocationInt = std::stoi(memoryLocationText.str());
                if(memoryLocationInt >= this->mainMemory.getMemoryList().size()){
                    throw std::out_of_range("Main memory is too large"); // Check for out-of-range memory access
                }

                // Handle specific instructions
                if(instructionInt == 43 || instructionInt == -43){
                    this->mainMemory.setMemoryLocation(this->mainMemory.getMemoryLocation() + 1); // Move to next memory location
                    ui->instructionTable->selectRow(i); // Select current instruction row
                    temp->setBackground(QColor::fromRgb(3,223,252)); // Highlight executed instruction
                    pause(); // Pause execution
                    break;
                }
                else if(instructionInt == 10 || instructionInt == -10){
                    ui->textInput->setPlaceholderText("Please type a number"); // Prompt for input
                    this->waitingForInputFromAll = true; // Set waiting flag
                    this->instructionMemoryLocation = memoryLocationInt; // Set instruction memory location
                    this->enableInput(); // Enable input
                    disableFileButtons(); // Disable file buttons
                    this->mainMemory.setMemoryLocation(this->mainMemory.getMemoryLocation() + 1); // Move to next memory location
                    temp->setBackground(QColor::fromRgb(3,223,252)); // Highlight executed instruction
                    ui->instructionTable->selectRow(i); // Select current instruction row
                    break;
                }
                // Execute the instruction
                doInstruction(instructionInt,memoryLocationInt,&this->mainMemory);
                if(instructionInt == 21 || instructionInt == -21){
                    // Update memory table with accumulator value
                    ui->memoryTable->setItem(memoryLocationInt,0,new QTableWidgetItem(QString::number(mainMemory.getAccumulator())));
                }
            } catch(...) {
                temp->setBackground(QColor::fromRgb(255,0,0)); // Highlight error in red

            }
            // Output instruction and memory location to console for debugging
            std::cout << instructionText.str() << std::endl;
            std::cout << memoryLocationText.str() << std::endl;
            temp->setBackground(QColor::fromRgb(3,223,252)); // Highlight executed instruction
        } else {
            
            temp->setBackground(QColor::fromRgb(255,0,0)); // Highlight error in red
            this->mainMemory.setMemoryLocation(this->mainMemory.getMemoryLocation() + 1); // Move to next memory location

        }
        
        // Update UI with current accumulator value
        ui->instructionTable->selectRow(i); // Select current instruction row
        ui->accumulatorInt->setText(QString::fromStdString(std::to_string(this->mainMemory.getAccumulator()))); // Update accumulator display
    }

}

// Function to pause execution and update UI
void MainWindow::pause(){
    ui->haltedText->show(); // Show halted message
    ui->runAllInstructionButtons->setEnabled(false); // Disable run all instructions button
    ui->runInstructionButton->setEnabled(false); // Disable run instruction button
    ui->unPauseButton->setEnabled(true); // Enable unpause button


}

// Function to enable input fields and buttons
void MainWindow::enableInput(){
    ui->runAllInstructionButtons->setEnabled(false); // Disable run all instructions button
    ui->runInstructionButton->setEnabled(false); // Disable run instruction button
    ui->textInput->setEnabled(true); // Enable text input field
    ui->inputButton->setEnabled(true); // Enable input button
    ui->textInput->setFocus(); // Set focus to text input field
}


// Slot function for handling unpause button click
void MainWindow::on_unPauseButton_clicked()
{
    ui->haltedText->hide(); // Hide halted message
    ui->unPauseButton->setEnabled(false); // Disable unpause button
    on_runAllInstructionButtons_clicked(); // Trigger run all instructions

}

// Slot function for handling the reset button click
void MainWindow::on_resetButton_clicked() {
    std::cout << "resetting" << std::endl; // Log reset action to console

    // Reset all memory values to 0
    for (int i = 0; i < mainMemory.getMemoryList().size(); i++) {
        mainMemory.setValueAt(0, i); // Set each memory location to 0
    }

    // Reset memory location and accumulator
    mainMemory.setMemoryLocation(0); // Reset memory location to the start
    mainMemory.setAccumulator(0); // Reset accumulator to 0
    ui->accumulatorInt->setText("0"); // Display accumulator as 0 on reset

    // Ensure all memory values are set to 0 again (redundant)
    for (int i = 0; i < mainMemory.getMemoryList().size(); i++) {
        mainMemory.setValueAt(i, 0); // Set each memory location to 0
    }

    createLists(); // Recreate the lists in the UI
}

// Slot function for handling the load button click
void MainWindow::on_loadButton_clicked() {
    // Open file dialog to select a text file
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Instruction File"), "", tr("Text Files (*.txt)"));

    // Check if a file was selected
    if (fileName.isEmpty()) {
        return; // Exit if no file was selected
    }

    QFile file(fileName); // Create a QFile object for the selected file
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Show warning if the file cannot be opened
        QMessageBox::warning(this, tr("Error"), tr("Cannot open file: ") + file.errorString());
        return;
    }

    QTextStream in(&file); // Create a text stream for reading the file
    QString line; // Variable to hold each line read from the file
    int row = 0; // Row index for the instruction table

    // Read the file line by line
    while (!in.atEnd() && row < this->mainMemory.getMemoryList().size()) {
        line = in.readLine(); // Read a line from the file

        // Validate the instruction format for both 4-digit and 6-digit numbers
        QRegularExpression regex("^[+-]\\d{4,6}$");
        QRegularExpressionMatch match = regex.match(line);
        if (match.hasMatch()) {
            // Convert 4-digit words to 6-digit format
            if (line.length() == 5) {
                // Extract the sign and the number
                QString sign = line.left(1);
                QString number = line.mid(1);

                // Create the new 6-digit format
                line = sign + "0" + number.left(2) + "0" + number.mid(2); // e.g., +1010 -> +010010, -2999 -> -029099
            }
            ui->instructionTable->setItem(row, 0, new QTableWidgetItem(line)); // Set the instruction in the table
            row++; // Move to the next row
        }
    }

    file.close(); // Close the file after reading
}

// Slot function for handling the save button click
void MainWindow::on_saveButton_clicked() {
    // Open file dialog to select a location to save the text file
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Instruction File"), "", tr("Text Files (*.txt)"));

    // Check if a file name was provided
    if (fileName.isEmpty()) {
        return; // Exit if no file name was provided
    }

    QFile file(fileName); // Create a QFile object for the selected file
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Show warning if the file cannot be opened
        QMessageBox::warning(this, tr("Error"), tr("Cannot open file: ") + file.errorString());
        return;
    }

    QTextStream out(&file); // Create a text stream for writing to the file

    // Iterate through the instructionTable and write each instruction to the file
    for (int row = 0; row < this->mainMemory.getMemoryList().size(); ++row) {
        QTableWidgetItem *item = ui->instructionTable->item(row, 0); // Get the instruction item
        if (item) {
            QString instruction = item->text(); // Get the instruction text
            if (!instruction.isEmpty()) {
                out << instruction << "\n"; // Write instruction to the file
            }
        }
    }

    file.close(); // Close the file after writing
    QMessageBox::information(this, tr("Success"), tr("Instructions saved successfully.")); // Show success message
}

// Slot function for handling the customize color button click
void MainWindow::on_customizeColor_clicked() {
    ui->customizeColor->hide(); // Hide the customize color button
    toggleColor(); // Toggle the visibility of color customization options
}

// Function to toggle color customization visibility
void MainWindow::toggleColor() {
    ui->colorErrorText->hide(); // Hide any error messages related to color

    // Show or hide color input fields based on their current visibility
    if (ui->redPrimary->isHidden()) {
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
    } else {
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

// Slot function for handling the confirm color button click
void MainWindow::on_confirmColor_clicked() {
    int red; // Variable for red color value
    int green; // Variable for green color value
    int blue; // Variable for blue color value
    std::stringstream s; // String stream for building style strings

    ui->customizeColor->show(); // Show the customize color button
    toggleColor(); // Toggle the visibility of color customization options

    // Check if primary color inputs are valid
    if (ui->redPrimary->text() != "" && ui->bluePrimary->text() != "" && ui->greenPrimary->text() != "") {
        red = ui->redPrimary->text().toInt(); // Convert red input to integer
        green = ui->greenPrimary->text().toInt(); // Convert green input to integer
        blue = ui->bluePrimary->text().toInt(); // Convert blue input to integer

        // Validate color values
        if (red > 255 || red < 0 || blue > 255 || blue < 0 || green > 255 || green < 0) {
            ui->colorErrorText->show(); // Show error if color values are out of range
        } else {
            // Set the background color based on RGB values
            s << "background-color: rgb(" << red << "," << green << "," << blue << ");";
            ui->centralwidget->setStyleSheet(QString::fromStdString(s.str())); // Apply the style to the central widget
        }
    }

    // Check if secondary color inputs are valid
    if (ui->redSecondary->text() != "" && ui->blueSecondary->text() != "" && ui->greenSecondary->text() != "") {
        red = ui->redSecondary->text().toInt(); // Convert secondary red input to integer
        green = ui->greenSecondary->text().toInt(); // Convert secondary green input to integer
        blue = ui->blueSecondary->text().toInt(); // Convert secondary blue input to integer

        // Validate secondary color values
        if (red > 255 || red < 0 || blue > 255 || blue < 0 || green > 255 || green < 0) {
            ui->colorErrorText->show(); // Show error if secondary color values are out of range
        } else {
            s.str(""); // Clear the string stream
            // Set the background color and text color for buttons
            s << "background-color: rgb(" << red << "," << green << "," << blue << ");" << "\n color: rgb(0,0,0);";
            ui->confirmColor->setStyleSheet(QString::fromStdString(s.str())); // Apply style to confirm button
            ui->customizeColor->setStyleSheet(QString::fromStdString(s.str())); // Apply style to customize button
            ui->inputButton->setStyleSheet(QString::fromStdString(s.str())); // Apply style to input button
            ui->loadButton->setStyleSheet(QString::fromStdString(s.str())); // Apply style to load button
            ui->saveButton->setStyleSheet(QString::fromStdString(s.str())); // Apply style to save button
            ui->resetButton->setStyleSheet(QString::fromStdString(s.str())); // Apply style to reset button
            ui->unPauseButton->setStyleSheet(QString::fromStdString(s.str())); // Apply style to unpause
            ui->runAllInstructionButtons->setStyleSheet(QString::fromStdString(s.str())); // Style for run all instructions button
            ui->runInstructionButton->setStyleSheet(QString::fromStdString(s.str())); // Style for run instruction button
            ui->file1Button->setStyleSheet(QString::fromStdString(s.str())); // Style for file 1 button
            ui->file2Button->setStyleSheet(QString::fromStdString(s.str())); // Style for file 2 button
            ui->file3Button->setStyleSheet(QString::fromStdString(s.str())); // Style for file 3 button
            ui->defaultColors->setStyleSheet(QString::fromStdString(s.str())); // Style for default colors button
        }
    }
}

// Function to handle pasting text from the clipboard into the instruction table
void MainWindow::paste() {
    // Grab the text from the clipboard
    QString temp = QApplication::clipboard()->text(); // Get the clipboard text
    QStringList lines = temp.split("\n", Qt::SkipEmptyParts); // Split the text into lines

    int rowNumber = 0; // Initialize row number for pasting
    auto rowList = ui->instructionTable->selectionModel()->selectedRows(); // Get selected rows in the instruction table
    if (rowList.count() > 0) {
        rowNumber = rowList.constFirst().row(); // Get the first selected row number
    }

    // Paste each line into the instruction table starting from the selected row
    for (int i = 0; i < lines.size(); i++) {
        ui->instructionTable->setItem(i, rowNumber, new QTableWidgetItem(lines[i])); // Set the item in the table
    }
}

// Function to handle copying selected instructions to the clipboard
void MainWindow::copy() {
    std::stringstream text; // String stream to hold copied text
    for (int i = 0; i < this->mainMemory.getMemoryList().size(); i++) {
        QTableWidgetItem *temp = ui->instructionTable->item(i, 0); // Get the instruction item
        if (temp->isSelected()) { // Check if the item is selected
            text << temp->text().toStdString() << std::endl; // Append the text to the stream
        }
    }
    QApplication::clipboard()->setText(QString::fromStdString(text.str())); // Set the clipboard text
}

// Slot function for handling file 1 button click
void MainWindow::on_file1Button_clicked() {
    ui->file1Button->setEnabled(false); // Disable file 1 button
    ui->file1ButtonBorder->setHidden(false); // Show border for file 1 button

    // If file 2 button is disabled, enable it and save its state
    if (ui->file2Button->isEnabled() == false) {
        ui->file2Button->setEnabled(true); // Enable file 2 button
        ui->file2ButtonBorder->setHidden(true); // Hide border for file 2 button
        saveToClass(&this->instructionsFile2, &this->mainMemoryFile2); // Save file 2 data
    }

    // If file 3 button is disabled, enable it and save its state
    if (ui->file3Button->isEnabled() == false) {
        ui->file3Button->setEnabled(true); // Enable file 3 button
        ui->file3ButtonBorder->setHidden(true); // Hide border for file 3 button
        saveToClass(&this->instructionsFile3, &this->mainMemoryFile3); // Save file 3 data
    }

    setMemoryAndInstructions(&instructionsFile1, &mainMemoryFile1); // Load file 1 data into the GUI table
}

// Slot function for handling file 2 button click
void MainWindow::on_file2Button_clicked() {
    ui->file2Button->setEnabled(false); // Disable file 2 button
    ui->file2ButtonBorder->setHidden(false); // Show border for file 2 button

    // If file 1 button is disabled, enable it and save its state
    if (ui->file1Button->isEnabled() == false) {
        ui->file1Button->setEnabled(true); // Enable file 1 button
        ui->file1ButtonBorder->setHidden(true); // Hide border for file 1 button
        saveToClass(&this->instructionsFile1, &this->mainMemoryFile1); // Save file 1 data
    }

    // If file 3 button is disabled, enable it and save its state
    if (ui->file3Button->isEnabled() == false) {
        ui->file3Button->setEnabled(true); // Enable file 3 button
        ui->file3ButtonBorder->setHidden(true); // Hide border for file 3 button
        saveToClass(&this->instructionsFile3, &this->mainMemoryFile3); // Save file 3 data
    }

    setMemoryAndInstructions(&instructionsFile2, &mainMemoryFile2); // Load file 2 data into the GUI table
}

// Slot function for handling file 3 button click
void MainWindow::on_file3Button_clicked() {
    ui->file3Button->setEnabled(false); // Disable file 3 button
    ui->file3ButtonBorder->setHidden(false); // Show border for file 3 button

    // If file 2 button is disabled, enable it and save its state
    if (ui->file2Button->isEnabled() == false) {
        ui->file2Button->setEnabled(true); // Enable file 2 button
        ui->file2ButtonBorder->setHidden(true); // Hide border for file 2 button
        saveToClass(&this->instructionsFile2, &this->mainMemoryFile2); // Save file 2 data
    }

    // If file 1 button is disabled, enable it and save its state
    if (ui->file1Button->isEnabled() == false) {
        ui->file1Button->setEnabled(true); // Enable file 1 button
        ui->file1ButtonBorder->setHidden(true); // Hide border for file 1 button
        saveToClass(&this->instructionsFile1, &this->mainMemoryFile1); // Save file 1 data
    }

    setMemoryAndInstructions(&instructionsFile3, &mainMemoryFile3); // Load file 3 data into the GUI table
}

// Function to copy the provided memory and instructions class to the GUI classes
void MainWindow::setMemoryAndInstructions(Instructions* instruct, MainMemory* memory) {
    // Set input flags based on the provided instruction object
    if (instruct->fourDigitInput == true) {
        this->fourDigitInput = true; // Set four-digit input flag
    }
    if (instruct->sixDigitInput == true) {
        this->sixDigitInput = true; // Set six-digit input flag
    }

    // If the program is paused, unpause it
    if (ui->unPauseButton->isEnabled()) {
        ui->haltedText->hide(); // Hide halted message
        ui->unPauseButton->setEnabled(false); // Disable unpause button
        ui->runAllInstructionButtons->setEnabled(true); // Enable run all instructions button
        ui->runInstructionButton->setEnabled(true); // Enable run instruction button
    }

    // Update main memory with the provided memory data
    this->mainMemory.setAll(memory->getMemoryList(), memory->getMemoryLocation(), memory->getAccumulator());
    ui->accumulatorInt->setText(QString::number(this->mainMemory.getAccumulator())); // Display the accumulator value

    // Populate the instruction and memory tables with data
    for (int i = 0; i < instruct->getFullInstructionTable().size(); i++) {
        QTableWidgetItem *temp = ui->instructionTable->item(i, 0); // Get instruction item
        QTableWidgetItem *temp2 = ui->memoryTable->item(i, 0); // Get memory item
        temp->setText(instruct->getFullInstructionTable().at(i)); // Set instruction text
        temp2->setText(QString::number(memory->getValueAt(i))); // Set memory value

        // Reset colors based on the current memory location
        if (i >= this->mainMemory.getMemoryLocation()) {
            temp->setBackground(QColorConstants::White); // Reset background to white for future instructions
        } else if (i < this->mainMemory.getMemoryLocation()) {
            // Set background color based on input type and validity
            if (temp->text().length() == 5 && this->fourDigitInput == true) {
                temp->setBackground(QColor::fromRgb(3, 223, 252)); // Highlight valid four-digit input
            } else if (temp->text().length() == 7 && this->sixDigitInput == true) {
                temp->setBackground(QColor::fromRgb(3, 223, 252)); // Highlight valid six-digit input
            } else if (temp->text().length() == 0) {
                temp->setBackground(QColor::fromRgb(255, 0, 0)); // Highlight empty input in red
            } else {
                temp->setBackground(QColor::fromRgb(255, 0, 0)); // Highlight invalid input in red
            }
        }


    }

    // selects the last row ran.
    if (this->mainMemory.getMemoryLocation() == 0) {
        this->ui->instructionTable->selectRow(this->mainMemory.getMemoryLocation());
    }else{
        this->ui->instructionTable->selectRow(this->mainMemory.getMemoryLocation()-1);
    }
}

// Function to copy the current GUI classes to the provided instruction and memory files
void MainWindow::saveToClass(Instructions *instruct, MainMemory *memory) {
    // Set input flags based on the current state
    if (this->fourDigitInput == true) {
        instruct->fourDigitInput = true; // Set four-digit input flag
    }
    if (this->sixDigitInput == true) {
        instruct->sixDigitInput = true; // Set six-digit input flag
    }

    // Update the memory object with current GUI memory data
    memory->setAll(this->mainMemory.getMemoryList(), this->mainMemory.getMemoryLocation(), this->mainMemory.getAccumulator());

    // Copy instructions from the GUI to the instruction object
    for (int i = 0; i < instruct->getFullInstructionTable().size(); i++) {
        QTableWidgetItem *temp = ui->instructionTable->item(i, 0); // Get instruction item
        instruct->setInstruction(i, temp->text()); // Set instruction text
    }
}

// Function to disable all file buttons
void MainWindow::disableFileButtons() {
    // Disable file 1 button if its border is hidden
    if (ui->file1ButtonBorder->isHidden()) {
        ui->file1Button->setEnabled(false);
    }
    // Disable file 2 button if its border is hidden
    if (ui->file2ButtonBorder->isHidden()) {
        ui->file2Button->setEnabled(false);
    }
    // Disable file 3 button if its border is hidden
    if (ui->file3ButtonBorder->isHidden()) {
        ui->file3Button->setEnabled(false);
    }
}

// Function to enable all file buttons except the currently selected one
void MainWindow::enableFileButtons() {
    // Enable file 1 button if its border is hidden
    if (ui->file1ButtonBorder->isHidden()) {
        ui->file1Button->setEnabled(true);
    }
    // Enable file 2 button if its border is hidden
    if (ui->file2ButtonBorder->isHidden()) {
        ui->file2Button->setEnabled(true);
    }
    // Enable file 3 button if its border is hidden
    if (ui->file3ButtonBorder->isHidden()) {
        ui->file3Button->setEnabled(true);
    }
}

// Slot function for handling the default colors button click
void MainWindow::on_defaultColors_clicked() {
    // Reset styles to default colors
    ui->centralwidget->setStyleSheet("background-color: rgb(76, 114, 29);");
    ui->confirmColor->setStyleSheet("background-color: rgb(255,255,255);\n color: rgb(0, 0, 0);");
    ui->customizeColor->setStyleSheet("background-color: rgb(255,255,255);\n color: rgb(0, 0, 0);");
    ui->inputButton->setStyleSheet("background-color: rgb(255,255,255);\n color: rgb(0, 0, 0);");
    ui->loadButton->setStyleSheet("background-color: rgb(255,255,255);\n color: rgb(0, 0, 0);");
    ui->saveButton->setStyleSheet("background-color: rgb(255,255,255);\n color: rgb(0, 0, 0);");
    ui->resetButton->setStyleSheet("background-color: rgb(255,255,255);\n color: rgb(0, 0, 0);");
    ui->unPauseButton->setStyleSheet("background-color: rgb(255,255,255);\n color: rgb(0, 0, 0);");
    ui->runAllInstructionButtons->setStyleSheet("background-color: rgb(255,255,255);\n color: rgb(0, 0, 0);");
    ui->runInstructionButton->setStyleSheet("background-color: rgb(255,255,255);\n color: rgb(0, 0, 0);");
    ui->file1Button->setStyleSheet("background-color: rgb(255,255,255);\n color: rgb(0, 0, 0);");
    ui->file2Button->setStyleSheet("background-color: rgb(255,255,255);\n color: rgb(0, 0, 0);");
    ui->file3Button->setStyleSheet("background-color: rgb(255,255,255);\n color: rgb(0, 0, 0);");
    ui->defaultColors->setStyleSheet("background-color: rgb(255,255,255);\n color: rgb(0, 0, 0);");
    ui->redPrimary->setText("76");
    ui->redSecondary->setText("255");
    ui->greenPrimary->setText("114");
    ui->greenSecondary->setText("255");
    ui->bluePrimary->setText("29");
    ui->blueSecondary->setText("255");
    
    toggleColor(); // Toggle color customization visibility
    ui->customizeColor->show(); // Show the customize color button
}
