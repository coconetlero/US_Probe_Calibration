/********************************************************************************
** Form generated from reading UI file 'ProbeCalibrationWidget.ui'
**
** Created: Mon Jan 9 14:50:04 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROBECALIBRATIONWIDGET_H
#define UI_PROBECALIBRATIONWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProbeCalibrationWidget
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_6;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_8;
    QPushButton *cropButton;
    QPushButton *rotationsButton;
    QLabel *rotationsLabel;
    QPushButton *translationsButton;
    QLabel *translationsLabel;
    QPushButton *calibrateButton;
    QPushButton *cancelButton;

    void setupUi(QWidget *ProbeCalibrationWidget)
    {
        if (ProbeCalibrationWidget->objectName().isEmpty())
            ProbeCalibrationWidget->setObjectName(QString::fromUtf8("ProbeCalibrationWidget"));
        ProbeCalibrationWidget->resize(427, 309);
        gridLayout = new QGridLayout(ProbeCalibrationWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableWidget = new QTableWidget(ProbeCalibrationWidget);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        QFont font;
        font.setPointSize(12);
        tableWidget->setFont(font);
        tableWidget->setColumnCount(3);
        tableWidget->horizontalHeader()->setVisible(true);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(55);
        tableWidget->horizontalHeader()->setMinimumSectionSize(10);
        tableWidget->verticalHeader()->setDefaultSectionSize(20);

        gridLayout->addWidget(tableWidget, 0, 0, 7, 1);

        verticalLayout = new QVBoxLayout();
#ifndef Q_OS_MAC
        verticalLayout->setSpacing(-1);
#endif
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 2);
        label = new QLabel(ProbeCalibrationWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        radioButton_4 = new QRadioButton(ProbeCalibrationWidget);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));
        QFont font1;
        font1.setPointSize(13);
        radioButton_4->setFont(font1);
        radioButton_4->setChecked(true);

        horizontalLayout->addWidget(radioButton_4);

        radioButton_6 = new QRadioButton(ProbeCalibrationWidget);
        radioButton_6->setObjectName(QString::fromUtf8("radioButton_6"));

        horizontalLayout->addWidget(radioButton_6);

        radioButton_5 = new QRadioButton(ProbeCalibrationWidget);
        radioButton_5->setObjectName(QString::fromUtf8("radioButton_5"));
        radioButton_5->setContextMenuPolicy(Qt::NoContextMenu);

        horizontalLayout->addWidget(radioButton_5);

        radioButton_8 = new QRadioButton(ProbeCalibrationWidget);
        radioButton_8->setObjectName(QString::fromUtf8("radioButton_8"));

        horizontalLayout->addWidget(radioButton_8);


        verticalLayout->addLayout(horizontalLayout);

        cropButton = new QPushButton(ProbeCalibrationWidget);
        cropButton->setObjectName(QString::fromUtf8("cropButton"));
        cropButton->setFlat(false);

        verticalLayout->addWidget(cropButton);


        gridLayout->addLayout(verticalLayout, 0, 2, 1, 1);

        rotationsButton = new QPushButton(ProbeCalibrationWidget);
        rotationsButton->setObjectName(QString::fromUtf8("rotationsButton"));

        gridLayout->addWidget(rotationsButton, 1, 2, 1, 1);

        rotationsLabel = new QLabel(ProbeCalibrationWidget);
        rotationsLabel->setObjectName(QString::fromUtf8("rotationsLabel"));
        rotationsLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(rotationsLabel, 2, 2, 1, 1);

        translationsButton = new QPushButton(ProbeCalibrationWidget);
        translationsButton->setObjectName(QString::fromUtf8("translationsButton"));

        gridLayout->addWidget(translationsButton, 3, 2, 1, 1);

        translationsLabel = new QLabel(ProbeCalibrationWidget);
        translationsLabel->setObjectName(QString::fromUtf8("translationsLabel"));
        translationsLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(translationsLabel, 4, 2, 1, 1);

        calibrateButton = new QPushButton(ProbeCalibrationWidget);
        calibrateButton->setObjectName(QString::fromUtf8("calibrateButton"));

        gridLayout->addWidget(calibrateButton, 5, 2, 1, 1);

        cancelButton = new QPushButton(ProbeCalibrationWidget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        gridLayout->addWidget(cancelButton, 6, 2, 1, 1);


        retranslateUi(ProbeCalibrationWidget);
        QObject::connect(cropButton, SIGNAL(clicked()), ProbeCalibrationWidget, SLOT(crop()));
        QObject::connect(calibrateButton, SIGNAL(clicked()), ProbeCalibrationWidget, SLOT(calibrate()));
        QObject::connect(rotationsButton, SIGNAL(clicked()), ProbeCalibrationWidget, SLOT(loadRotationsFile()));
        QObject::connect(translationsButton, SIGNAL(clicked()), ProbeCalibrationWidget, SLOT(loadTranslationsFile()));
        QObject::connect(cancelButton, SIGNAL(clicked()), ProbeCalibrationWidget, SLOT(close()));

        QMetaObject::connectSlotsByName(ProbeCalibrationWidget);
    } // setupUi

    void retranslateUi(QWidget *ProbeCalibrationWidget)
    {
        ProbeCalibrationWidget->setWindowTitle(QApplication::translate("ProbeCalibrationWidget", "Probe Calibration Setup", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ProbeCalibrationWidget", "Type of Depth of US:", 0, QApplication::UnicodeUTF8));
        radioButton_4->setText(QApplication::translate("ProbeCalibrationWidget", "4", 0, QApplication::UnicodeUTF8));
        radioButton_6->setText(QApplication::translate("ProbeCalibrationWidget", "6", 0, QApplication::UnicodeUTF8));
        radioButton_5->setText(QApplication::translate("ProbeCalibrationWidget", "5", 0, QApplication::UnicodeUTF8));
        radioButton_8->setText(QApplication::translate("ProbeCalibrationWidget", "8", 0, QApplication::UnicodeUTF8));
        cropButton->setText(QApplication::translate("ProbeCalibrationWidget", "Crop Images", 0, QApplication::UnicodeUTF8));
        rotationsButton->setText(QApplication::translate("ProbeCalibrationWidget", "Load Rotations File", 0, QApplication::UnicodeUTF8));
        rotationsLabel->setText(QApplication::translate("ProbeCalibrationWidget", "No rotations file loaded", 0, QApplication::UnicodeUTF8));
        translationsButton->setText(QApplication::translate("ProbeCalibrationWidget", "Load Translations File", 0, QApplication::UnicodeUTF8));
        translationsLabel->setText(QApplication::translate("ProbeCalibrationWidget", "No translations file loaded", 0, QApplication::UnicodeUTF8));
        calibrateButton->setText(QApplication::translate("ProbeCalibrationWidget", "Calibrate Probe", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("ProbeCalibrationWidget", "Cancel ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ProbeCalibrationWidget: public Ui_ProbeCalibrationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROBECALIBRATIONWIDGET_H
