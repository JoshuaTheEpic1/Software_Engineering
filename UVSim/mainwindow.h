#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <vector>
#include "mainMemory.h"
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
    void enableButton();
    MainMemory mainMemory;


private slots:
    void on_runInstructionButton_clicked();

    void on_inputButton_clicked(bool checked);

    void on_inputButton_clicked();

    void on_runAllInstructionButtons_clicked();

    void on_pushButton_clicked();

    void on_unPauseButton_clicked();

    void on_resetButton_clicked();

private:
    Ui::MainWindow *ui;
    int memoryLocation = 0;
    std::vector<std::string> instructions;
    std::vector<int> instructMemoryLocations;
    int instructionMemoryLocation = 0;
    bool waitingForInputFromAll = false;
};
#endif // MAINWINDOW_H
