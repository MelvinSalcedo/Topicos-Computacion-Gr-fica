/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSlider *horizontalSlider;
    QLabel *Histograma;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *OpenImage;
    QPushButton *Save;
    QSlider *Contraste;
    QLabel *label_6;
    QSlider *Divicion;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *Equalisacion;
    QPushButton *Gamma;
    QPushButton *Griss;
    QLabel *label_3;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(749, 469);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(390, 100, 351, 321));
        label->setAutoFillBackground(true);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(180, 40, 211, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(220, 40, 171, 21));
        horizontalSlider->setMinimum(0);
        horizontalSlider->setMaximum(100);
        horizontalSlider->setOrientation(Qt::Horizontal);
        Histograma = new QLabel(centralWidget);
        Histograma->setObjectName(QStringLiteral("Histograma"));
        Histograma->setGeometry(QRect(10, 100, 351, 321));
        Histograma->setAutoFillBackground(true);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 70, 81, 20));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(400, 70, 81, 20));
        OpenImage = new QPushButton(centralWidget);
        OpenImage->setObjectName(QStringLiteral("OpenImage"));
        OpenImage->setGeometry(QRect(0, 0, 80, 28));
        Save = new QPushButton(centralWidget);
        Save->setObjectName(QStringLiteral("Save"));
        Save->setGeometry(QRect(0, 30, 81, 28));
        Contraste = new QSlider(centralWidget);
        Contraste->setObjectName(QStringLiteral("Contraste"));
        Contraste->setGeometry(QRect(498, 34, 161, 16));
        Contraste->setMinimum(1);
        Contraste->setMaximum(50);
        Contraste->setSingleStep(1);
        Contraste->setPageStep(10);
        Contraste->setOrientation(Qt::Horizontal);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(420, 50, 69, 20));
        Divicion = new QSlider(centralWidget);
        Divicion->setObjectName(QStringLiteral("Divicion"));
        Divicion->setGeometry(QRect(496, 52, 161, 16));
        Divicion->setMinimum(1);
        Divicion->setMaximum(50);
        Divicion->setSingleStep(1);
        Divicion->setPageStep(10);
        Divicion->setOrientation(Qt::Horizontal);
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(180, 0, 352, 30));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        Equalisacion = new QPushButton(widget);
        Equalisacion->setObjectName(QStringLiteral("Equalisacion"));

        horizontalLayout_2->addWidget(Equalisacion);

        Gamma = new QPushButton(widget);
        Gamma->setObjectName(QStringLiteral("Gamma"));

        horizontalLayout_2->addWidget(Gamma);

        Griss = new QPushButton(widget);
        Griss->setObjectName(QStringLiteral("Griss"));

        horizontalLayout_2->addWidget(Griss);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(422, 32, 69, 20));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "Brillo", 0));
        Histograma->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "Histograma", 0));
        label_5->setText(QApplication::translate("MainWindow", "Imagen", 0));
        OpenImage->setText(QApplication::translate("MainWindow", "Open", 0));
        Save->setText(QApplication::translate("MainWindow", "save", 0));
        label_6->setText(QApplication::translate("MainWindow", "divicion", 0));
        Equalisacion->setText(QApplication::translate("MainWindow", "ecualizador", 0));
        Gamma->setText(QApplication::translate("MainWindow", "Gamma", 0));
        Griss->setText(QApplication::translate("MainWindow", "Gris", 0));
        label_3->setText(QApplication::translate("MainWindow", "Producto", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
