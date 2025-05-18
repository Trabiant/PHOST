/********************************************************************************
** Form generated from reading UI file 'ProjectWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTWINDOW_H
#define UI_PROJECTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProjectWindow
{
public:
    QFrame *titleBar;
    QPushButton *Close;
    QLabel *miniProgrammName;
    QFrame *frame;
    QPushButton *Confirm;
    QPushButton *Cancel;
    QLabel *label_3;
    QLabel *label_2;
    QPushButton *folderPicker;
    QLabel *label;
    QLineEdit *Name;
    QLabel *text;

    void setupUi(QWidget *ProjectWindow)
    {
        if (ProjectWindow->objectName().isEmpty())
            ProjectWindow->setObjectName("ProjectWindow");
        ProjectWindow->resize(300, 200);
        ProjectWindow->setStyleSheet(QString::fromUtf8("background-color: #1A1A1A;"));
        titleBar = new QFrame(ProjectWindow);
        titleBar->setObjectName("titleBar");
        titleBar->setGeometry(QRect(0, 0, 300, 16));
        titleBar->setStyleSheet(QString::fromUtf8("background-color: #1E1E1E;\n"
"border: none;\n"
"border-top-left-radius: 7px;\n"
"border-top-right-radius: 7px;"));
        titleBar->setFrameShape(QFrame::Shape::StyledPanel);
        titleBar->setFrameShadow(QFrame::Shadow::Raised);
        Close = new QPushButton(titleBar);
        Close->setObjectName("Close");
        Close->setGeometry(QRect(265, 0, 35, 16));
        Close->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: #a63838;\n"
"	border: none; \n"
"	border-top-left-radius: 0px;\n"
"	border-top-right-radius: 7px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #F64C4C;\n"
"}"));
        miniProgrammName = new QLabel(titleBar);
        miniProgrammName->setObjectName("miniProgrammName");
        miniProgrammName->setGeometry(QRect(6, 0, 31, 16));
        QFont font;
        font.setFamilies({QString::fromUtf8("Inter")});
        font.setPointSize(7);
        font.setWeight(QFont::ExtraBold);
        miniProgrammName->setFont(font);
        miniProgrammName->setStyleSheet(QString::fromUtf8("color: #FFFFFF;\n"
"font-family: \"Inter\";\n"
""));
        frame = new QFrame(ProjectWindow);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 300, 200));
        frame->setStyleSheet(QString::fromUtf8("border-radius: 8px;\n"
"color: #1A1A1A;"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        Confirm = new QPushButton(frame);
        Confirm->setObjectName("Confirm");
        Confirm->setEnabled(true);
        Confirm->setGeometry(QRect(35, 155, 80, 23));
        Confirm->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	color: #FFFFFF;\n"
"	font-family: \"Inter\";\n"
"	font-size: 11 px;\n"
"	font-weight: bold;\n"
"	border-radius: 4px;\n"
"	background-color: #3870A6;\n"
"}\n"
"QPushButton:hover{\n"
"	border: 1px solid #438ac8;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #274e73;\n"
"    color: #c8c8c8;\n"
"	border: 1px solid #274e73;\n"
"}"));
        Cancel = new QPushButton(frame);
        Cancel->setObjectName("Cancel");
        Cancel->setGeometry(QRect(180, 155, 80, 23));
        Cancel->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	color: #FFFFFF;\n"
"	font-family: \"Inter\";\n"
"	font-size: 11 px;\n"
"	font-weight: bold;\n"
"	border-radius: 4px;\n"
"	background-color: #3870A6;\n"
"}\n"
"QPushButton:hover{\n"
"	border: 1px solid #438ac8;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #274e73;\n"
"    color: #c8c8c8;\n"
"	border: 1px solid #274e73;\n"
"}"));
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(131, 20, 40, 40));
        label_3->setMinimumSize(QSize(40, 40));
        label_3->setMaximumSize(QSize(40, 40));
        label_3->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/PHOST_icon.png")));
        label_3->setScaledContents(true);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 112, 116, 16));
        label_2->setStyleSheet(QString::fromUtf8("color: #FFFFFF;\n"
"font-family: \"Inter\";\n"
"font-size: 11 px;\n"
"font-weight: bold;\n"
""));
        folderPicker = new QPushButton(frame);
        folderPicker->setObjectName("folderPicker");
        folderPicker->setGeometry(QRect(160, 110, 105, 21));
        folderPicker->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	color: #FFFFFF;\n"
"	font-family: \"Inter\";\n"
"	font-size: 11 px;\n"
"	font-weight: bold;\n"
"	border-radius: 4px;\n"
"	border: 1px solid #3870A6;\n"
"}\n"
"QPushButton:hover{\n"
"	border: 1px solid #438ac8;\n"
"}\n"
"QPushButton:pressed {\n"
"    color: #c8c8c8;\n"
"	border: 1px solid #274e73;\n"
"}"));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 80, 113, 16));
        label->setStyleSheet(QString::fromUtf8("color: #FFFFFF;\n"
"font-family: \"Inter\";\n"
"font-size: 11 px;\n"
"font-weight: bold;\n"
""));
        Name = new QLineEdit(frame);
        Name->setObjectName("Name");
        Name->setGeometry(QRect(160, 79, 105, 21));
        Name->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	color: #ffffff;\n"
"	font-family: \"Inter\";\n"
"	font-size: 11 px;\n"
"	font-weight: bold;\n"
"	border: 1px solid #3870A6;\n"
"	border-radius: 4px;\n"
"}\n"
"QLineEdit:hover {\n"
"    border: 1px solid #438ac8;\n"
"}\n"
"QLineEdit:focus {\n"
"    border: 2px solid #4693d2;\n"
"}"));
        text = new QLabel(frame);
        text->setObjectName("text");
        text->setGeometry(QRect(112, 56, 81, 20));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Inter")});
        font1.setPointSize(7);
        text->setFont(font1);
        text->setStyleSheet(QString::fromUtf8("color: #ffffff;\n"
"background-color: transparent;"));
        frame->raise();
        titleBar->raise();

        retranslateUi(ProjectWindow);

        QMetaObject::connectSlotsByName(ProjectWindow);
    } // setupUi

    void retranslateUi(QWidget *ProjectWindow)
    {
        ProjectWindow->setWindowTitle(QCoreApplication::translate("ProjectWindow", "PHOST", nullptr));
        Close->setText(QString());
        miniProgrammName->setText(QCoreApplication::translate("ProjectWindow", "Phost", nullptr));
        Confirm->setText(QCoreApplication::translate("ProjectWindow", "Confirm", nullptr));
        Cancel->setText(QCoreApplication::translate("ProjectWindow", "Cancel", nullptr));
        label_3->setText(QString());
        label_2->setText(QCoreApplication::translate("ProjectWindow", "Select dataset path:", nullptr));
        folderPicker->setText(QCoreApplication::translate("ProjectWindow", "Dataset path", nullptr));
        label->setText(QCoreApplication::translate("ProjectWindow", "Enter project name:", nullptr));
        text->setText(QCoreApplication::translate("ProjectWindow", "Phost make reality", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjectWindow: public Ui_ProjectWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTWINDOW_H
