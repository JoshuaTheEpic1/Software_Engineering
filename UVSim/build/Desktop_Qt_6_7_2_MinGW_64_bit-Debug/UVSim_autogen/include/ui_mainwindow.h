/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *runInstructionButton;
    QPushButton *inputButton;
    QTextEdit *textInput;
    QLabel *accumulator;
    QLabel *accumulatorInt;
    QPushButton *runAllInstructionButtons;
    QTableWidget *memoryTable;
    QTableWidget *instructionTable;
    QPushButton *unPauseButton;
    QPushButton *resetButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        runInstructionButton = new QPushButton(centralwidget);
        runInstructionButton->setObjectName("runInstructionButton");
        runInstructionButton->setGeometry(QRect(370, 60, 141, 41));
        inputButton = new QPushButton(centralwidget);
        inputButton->setObjectName("inputButton");
        inputButton->setEnabled(false);
        inputButton->setGeometry(QRect(370, 260, 83, 29));
        textInput = new QTextEdit(centralwidget);
        textInput->setObjectName("textInput");
        textInput->setEnabled(false);
        textInput->setGeometry(QRect(370, 230, 181, 31));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textInput->sizePolicy().hasHeightForWidth());
        textInput->setSizePolicy(sizePolicy);
        accumulator = new QLabel(centralwidget);
        accumulator->setObjectName("accumulator");
        accumulator->setGeometry(QRect(530, 60, 71, 16));
        accumulatorInt = new QLabel(centralwidget);
        accumulatorInt->setObjectName("accumulatorInt");
        accumulatorInt->setGeometry(QRect(600, 60, 49, 16));
        runAllInstructionButtons = new QPushButton(centralwidget);
        runAllInstructionButtons->setObjectName("runAllInstructionButtons");
        runAllInstructionButtons->setGeometry(QRect(370, 100, 141, 41));
        memoryTable = new QTableWidget(centralwidget);
        memoryTable->setObjectName("memoryTable");
        memoryTable->setGeometry(QRect(10, 10, 151, 501));
        instructionTable = new QTableWidget(centralwidget);
        instructionTable->setObjectName("instructionTable");
        instructionTable->setGeometry(QRect(170, 10, 151, 501));
        unPauseButton = new QPushButton(centralwidget);
        unPauseButton->setObjectName("unPauseButton");
        unPauseButton->setEnabled(false);
        unPauseButton->setGeometry(QRect(370, 140, 80, 24));
        resetButton = new QPushButton(centralwidget);
        resetButton->setObjectName("resetButton");
        resetButton->setGeometry(QRect(120, 510, 80, 24));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "UVSim", nullptr));
        runInstructionButton->setText(QCoreApplication::translate("MainWindow", "Execute Next Instruction", nullptr));
        inputButton->setText(QCoreApplication::translate("MainWindow", "Enter", nullptr));
        accumulator->setText(QCoreApplication::translate("MainWindow", "Accumlator:", nullptr));
        accumulatorInt->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        runAllInstructionButtons->setText(QCoreApplication::translate("MainWindow", "Execute All Instructions", nullptr));
        unPauseButton->setText(QCoreApplication::translate("MainWindow", "Unpause", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "Reset All", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
