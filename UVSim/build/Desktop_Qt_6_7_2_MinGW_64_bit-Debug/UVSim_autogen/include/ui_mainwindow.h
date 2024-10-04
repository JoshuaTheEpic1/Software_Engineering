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
    QLabel *label_3;
    QLabel *accumulator;
    QLabel *accumulatorInt;
    QPushButton *runAllInstructionButtons;
    QTableWidget *memoryTable;
    QTableWidget *instructionTable;
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
        inputButton->setGeometry(QRect(410, 260, 83, 29));
        textInput = new QTextEdit(centralwidget);
        textInput->setObjectName("textInput");
        textInput->setEnabled(false);
        textInput->setGeometry(QRect(400, 220, 104, 31));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textInput->sizePolicy().hasHeightForWidth());
        textInput->setSizePolicy(sizePolicy);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(400, 190, 63, 20));
        accumulator = new QLabel(centralwidget);
        accumulator->setObjectName("accumulator");
        accumulator->setGeometry(QRect(540, 80, 71, 16));
        accumulatorInt = new QLabel(centralwidget);
        accumulatorInt->setObjectName("accumulatorInt");
        accumulatorInt->setGeometry(QRect(610, 80, 49, 16));
        runAllInstructionButtons = new QPushButton(centralwidget);
        runAllInstructionButtons->setObjectName("runAllInstructionButtons");
        runAllInstructionButtons->setGeometry(QRect(370, 100, 141, 41));
        memoryTable = new QTableWidget(centralwidget);
        memoryTable->setObjectName("memoryTable");
        memoryTable->setGeometry(QRect(10, 10, 151, 501));
        instructionTable = new QTableWidget(centralwidget);
        instructionTable->setObjectName("instructionTable");
        instructionTable->setGeometry(QRect(170, 10, 151, 501));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        runInstructionButton->setText(QCoreApplication::translate("MainWindow", "Execute Next  Instruction", nullptr));
        inputButton->setText(QCoreApplication::translate("MainWindow", "Enter", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Input", nullptr));
        accumulator->setText(QCoreApplication::translate("MainWindow", "Accumlator:", nullptr));
        accumulatorInt->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        runAllInstructionButtons->setText(QCoreApplication::translate("MainWindow", "Execute All Instructions", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H