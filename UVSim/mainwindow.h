#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <vector>
#include "mainMemory.h"
#include <QKeyEvent>
#include "instructions.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createLists();
    void pause();
    void enableInput();
    void toggleColor();
    MainMemory mainMemory;
    MainMemory mainMemoryFile1;
    MainMemory mainMemoryFile2;
    MainMemory mainMemoryFile3;
    void paste();
    void copy();
protected:
    void keyPressEvent(QKeyEvent *event) override{
        if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_V){
            paste();
        }
        if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_C){
            copy();
        }
    }
private slots:
    void on_runInstructionButton_clicked();

    //void on_inputButton_clicked(bool checked);

    void on_inputButton_clicked();

    void on_runAllInstructionButtons_clicked();

    //void on_pushButton_clicked();

    void on_unPauseButton_clicked();

    void on_resetButton_clicked();

    void on_loadButton_clicked();

    void on_saveButton_clicked();

    void on_customizeColor_clicked();

    void on_confirmColor_clicked();

    void on_file1Button_clicked();

    void on_file2Button_clicked();

    void on_file3Button_clicked();

    void setMemoryAndInstructions(Instructions* instruct,MainMemory* memory);

    void saveToClass(Instructions *instruct,MainMemory *memory);

    void disableFileButtons();

    void enableFileButtons();
    void on_defaultColors_clicked();

private:
    Ui::MainWindow *ui;
    Instructions instructionsFile1;
    Instructions instructionsFile2;
    Instructions instructionsFile3;
    std::vector<std::string> instructions;
    std::vector<int> instructMemoryLocations;
    int instructionMemoryLocation = 0;
    bool waitingForInputFromAll = false;
    bool fourDigitInput = false;
    bool sixDigitInput = false;
};
#endif // MAINWINDOW_H
