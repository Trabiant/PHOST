/********************************************************************************
** Form generated from reading UI file 'Window.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Window
{
public:
    QPushButton *creatProject;
    QLabel *programmName;
    QPushButton *Start;
    QPushButton *rcLink;
    QFrame *titleBar;
    QPushButton *Hide;
    QPushButton *Close;
    QLabel *miniProgrammName;
    QPushButton *saveMask;
    QPushButton *drawMask;
    QProgressBar *progressBar;
    QFrame *frameRcStatus;
    QLabel *label_2;
    QPushButton *eight;
    QPushButton *four;
    QPushButton *twelve;
    QPushButton *sixteen;
    QLabel *label_3;
    QPushButton *DirectX;
    QPushButton *OpenGL;
    QFrame *frame;
    QLabel *TopLeft;
    QLabel *icon;
    QPushButton *Workflow;
    QPushButton *Editor;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *mainView;
    QListWidget *thumbList;
    QListWidget *listPackages;
    QWidget *page_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *statusText;
    QSpacerItem *horizontalSpacer;
    QLabel *estimationText;
    QLabel *TopRight;

    void setupUi(QWidget *Window)
    {
        if (Window->objectName().isEmpty())
            Window->setObjectName("Window");
        Window->resize(981, 654);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        QBrush brush1(QColor(26, 26, 26, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        QBrush brush2(QColor(30, 30, 30, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Highlight, brush2);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Highlight, brush2);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Highlight, brush2);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::LinkVisited, brush2);
        Window->setPalette(palette);
        Window->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        Window->setMouseTracking(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/PHOST_icon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        Window->setWindowIcon(icon1);
        Window->setStyleSheet(QString::fromUtf8("QWidget {\n"
"	background-color: #1A1A1A;\n"
"}"));
        creatProject = new QPushButton(Window);
        creatProject->setObjectName("creatProject");
        creatProject->setGeometry(QRect(466, 52, 91, 10));
        QFont font;
        font.setFamilies({QString::fromUtf8("Inter")});
        font.setPointSize(8);
        font.setWeight(QFont::DemiBold);
        creatProject->setFont(font);
        creatProject->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	color: #FFFFFF;\n"
"	font-family: \"Inter\";\n"
"	border: 0 px;\n"
"	background-color: transparent;\n"
"}\n"
"QPushButton:pressed {\n"
"    color: #c8c8c8;\n"
"}"));
        creatProject->setAutoExclusive(false);
        programmName = new QLabel(Window);
        programmName->setObjectName("programmName");
        programmName->setGeometry(QRect(73, 47, 81, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Inter")});
        font1.setPointSize(14);
        font1.setWeight(QFont::DemiBold);
        font1.setStyleStrategy(QFont::PreferDefault);
        programmName->setFont(font1);
        programmName->setStyleSheet(QString::fromUtf8("color: #FFFFFF;\n"
"font-family: \"Inter\";\n"
"background-color: transparent;\n"
""));
        Start = new QPushButton(Window);
        Start->setObjectName("Start");
        Start->setGeometry(QRect(900, 56, 51, 21));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Inter")});
        font2.setPointSize(13);
        font2.setWeight(QFont::DemiBold);
        Start->setFont(font2);
        Start->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	color: #FFFFFF;\n"
"	font-family: \"Inter\";\n"
"	border: 0 px;\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"   color: #5b5b5b;\n"
"}\n"
"QPushButton:pressed {\n"
"    color: #c8c8c8;\n"
"}"));
        rcLink = new QPushButton(Window);
        rcLink->setObjectName("rcLink");
        rcLink->setGeometry(QRect(466, 71, 121, 10));
        rcLink->setFont(font);
        rcLink->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	color: #FFFFFF;\n"
"	font-family: \"Inter\";\n"
"	border: 0 px;\n"
"	background-color: transparent;\n"
"}\n"
"QPushButton:pressed {\n"
"    color: #c8c8c8;\n"
"}"));
        titleBar = new QFrame(Window);
        titleBar->setObjectName("titleBar");
        titleBar->setGeometry(QRect(0, 0, 981, 16));
        titleBar->setStyleSheet(QString::fromUtf8("background-color: #1E1E1E;\n"
"border: none;\n"
"border-top-left-radius: 7px;\n"
"border-top-right-radius: 7px;"));
        titleBar->setFrameShadow(QFrame::Shadow::Raised);
        Hide = new QPushButton(titleBar);
        Hide->setObjectName("Hide");
        Hide->setGeometry(QRect(911, 0, 35, 16));
        Hide->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	border: 0 px;\n"
"	background-color: #333333;\n"
"	border-radius: 10 px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #5b5b5b;\n"
"}"));
        Close = new QPushButton(titleBar);
        Close->setObjectName("Close");
        Close->setGeometry(QRect(946, 0, 35, 16));
        Close->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: #a63838;\n"
"	border: none; \n"
"	border-top-left-radius: 0px;\n"
"	border-top-right-radius: 7px;\n"
"    \n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #F64C4C;\n"
"}"));
        miniProgrammName = new QLabel(titleBar);
        miniProgrammName->setObjectName("miniProgrammName");
        miniProgrammName->setGeometry(QRect(6, 0, 31, 16));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Inter")});
        font3.setPointSize(7);
        font3.setBold(true);
        font3.setKerning(true);
        miniProgrammName->setFont(font3);
        miniProgrammName->setStyleSheet(QString::fromUtf8("color: #FFFFFF;\n"
"font-family: \"Inter\";\n"
""));
        Hide->raise();
        miniProgrammName->raise();
        Close->raise();
        saveMask = new QPushButton(Window);
        saveMask->setObjectName("saveMask");
        saveMask->setGeometry(QRect(884, 613, 80, 24));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Inter")});
        font4.setBold(true);
        saveMask->setFont(font4);
        saveMask->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
"QPushButton:disabled {\n"
"   color: #2d4964;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #274e73;\n"
"    color: #c8c8c8;\n"
"	border: 1px solid #274e73;\n"
"}"));
        drawMask = new QPushButton(Window);
        drawMask->setObjectName("drawMask");
        drawMask->setGeometry(QRect(774, 613, 80, 24));
        drawMask->setFont(font4);
        drawMask->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
"QPushButton:disabled {\n"
"   color: #2d4964;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #274e73;\n"
"    color: #c8c8c8;\n"
"	border: 1px solid #274e73;\n"
"}"));
        progressBar = new QProgressBar(Window);
        progressBar->setObjectName("progressBar");
        progressBar->setEnabled(true);
        progressBar->setGeometry(QRect(11, 630, 443, 7));
        QFont font5;
        font5.setStyleStrategy(QFont::PreferDefault);
        progressBar->setFont(font5);
        progressBar->setStyleSheet(QString::fromUtf8("QProgressBar {\n"
"    border-radius: 1 px;\n"
"    background-color: #8C8C8C;\n"
"}\n"
"QProgressBar::chunk {\n"
"    background-color: #EBEBEB;\n"
"    border-radius: 1 px;\n"
"}\n"
""));
        progressBar->setMinimum(0);
        progressBar->setValue(0);
        progressBar->setTextVisible(false);
        frameRcStatus = new QFrame(Window);
        frameRcStatus->setObjectName("frameRcStatus");
        frameRcStatus->setGeometry(QRect(583, 74, 6, 6));
        frameRcStatus->setMinimumSize(QSize(6, 6));
        frameRcStatus->setMaximumSize(QSize(10, 10));
        frameRcStatus->setStyleSheet(QString::fromUtf8("border: 0px;\n"
"background-color: #F64C4C;\n"
"border-radius: 3px;"));
        frameRcStatus->setFrameShape(QFrame::Shape::NoFrame);
        frameRcStatus->setFrameShadow(QFrame::Shadow::Raised);
        label_2 = new QLabel(Window);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(610, 49, 135, 16));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("color: #FFFFFF;\n"
"font-family: \"Inter\";\n"
"background-color: transparent;\n"
""));
        eight = new QPushButton(Window);
        eight->setObjectName("eight");
        eight->setGeometry(QRect(644, 69, 33, 15));
        QFont font6;
        font6.setFamilies({QString::fromUtf8("Inter")});
        font6.setPointSize(7);
        font6.setBold(false);
        eight->setFont(font6);
        eight->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    padding: 0;\n"
"    margin: 0;\n"
"    font-family: \"Inter\";\n"
"    font-size: 7 px;\n"
"    color: #FFFFFF;\n"
"    background-color: #262626;\n"
"    border: none;\n"
"    text-align: center;       /* \320\240\320\260\320\261\320\276\321\202\320\260\320\265\321\202 \320\267\320\264\320\265\321\201\321\214! */\n"
"    vertical-align: middle;   /* \320\230 \321\215\321\202\320\276 \320\261\321\203\320\264\320\265\321\202 \321\200\320\260\320\261\320\276\321\202\320\260\321\202\321\214 */\n"
"	font-weight: regular;\n"
"	border-radius: 3px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2d2d2d;\n"
"}\n"
"QPushButton:checked {\n"
"    background-color: #3870A6;\n"
"}"));
        eight->setCheckable(true);
        eight->setChecked(true);
        four = new QPushButton(Window);
        four->setObjectName("four");
        four->setGeometry(QRect(611, 69, 33, 15));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(four->sizePolicy().hasHeightForWidth());
        four->setSizePolicy(sizePolicy);
        four->setMinimumSize(QSize(0, 0));
        QFont font7;
        font7.setFamilies({QString::fromUtf8("Inter")});
        font7.setPointSize(7);
        font7.setBold(false);
        font7.setHintingPreference(QFont::PreferDefaultHinting);
        four->setFont(font7);
        four->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        four->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    padding: 0;\n"
"    margin: 0;\n"
"    font-family: \"Inter\";\n"
"    font-size: 7 px;\n"
"    color: #FFFFFF;\n"
"    background-color: #262626;\n"
"    border: none;\n"
"    text-align: center;       /* \320\240\320\260\320\261\320\276\321\202\320\260\320\265\321\202 \320\267\320\264\320\265\321\201\321\214! */\n"
"    vertical-align: middle;   /* \320\230 \321\215\321\202\320\276 \320\261\321\203\320\264\320\265\321\202 \321\200\320\260\320\261\320\276\321\202\320\260\321\202\321\214 */\n"
"	font-weight: regular;\n"
"	border-radius: 3px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2d2d2d;\n"
"}\n"
"\n"
"QPushButton:checked {\n"
"    background-color: #3870A6;\n"
"}\n"
""));
        four->setCheckable(true);
        twelve = new QPushButton(Window);
        twelve->setObjectName("twelve");
        twelve->setGeometry(QRect(677, 69, 33, 15));
        QFont font8;
        font8.setFamilies({QString::fromUtf8("Inter")});
        font8.setPointSize(7);
        twelve->setFont(font8);
        twelve->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    padding: 0;\n"
"    margin: 0;\n"
"    font-family: \"Inter\";\n"
"    font-size: 7 px;\n"
"    color: #FFFFFF;\n"
"    background-color: #262626;\n"
"    border: none;\n"
"    text-align: center;       /* \320\240\320\260\320\261\320\276\321\202\320\260\320\265\321\202 \320\267\320\264\320\265\321\201\321\214! */\n"
"    vertical-align: middle;   /* \320\230 \321\215\321\202\320\276 \320\261\321\203\320\264\320\265\321\202 \321\200\320\260\320\261\320\276\321\202\320\260\321\202\321\214 */\n"
"	font-weight: regular;\n"
"	border-radius: 3px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2d2d2d;\n"
"}\n"
"QPushButton:checked {\n"
"    background-color: #3870A6;\n"
"}\n"
""));
        twelve->setCheckable(true);
        sixteen = new QPushButton(Window);
        sixteen->setObjectName("sixteen");
        sixteen->setGeometry(QRect(710, 69, 33, 15));
        sixteen->setFont(font6);
        sixteen->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    padding: 0;\n"
"    margin: 0;\n"
"    font-family: \"Inter\";\n"
"    font-size: 7 px;\n"
"    color: #FFFFFF;\n"
"    background-color: #262626;\n"
"    border: none;\n"
"    text-align: center;       /* \320\240\320\260\320\261\320\276\321\202\320\260\320\265\321\202 \320\267\320\264\320\265\321\201\321\214! */\n"
"    vertical-align: middle;   /* \320\230 \321\215\321\202\320\276 \320\261\321\203\320\264\320\265\321\202 \321\200\320\260\320\261\320\276\321\202\320\260\321\202\321\214 */\n"
"	font-weight: regular;\n"
"	border-radius: 3px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2d2d2d;\n"
"}\n"
"QPushButton:checked {\n"
"    background-color: #3870A6;\n"
"}\n"
"\n"
""));
        sixteen->setCheckable(true);
        sixteen->setChecked(false);
        label_3 = new QLabel(Window);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(770, 49, 108, 16));
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8("color: #FFFFFF;\n"
"font-family: \"Inter\";\n"
"background-color: transparent;"));
        DirectX = new QPushButton(Window);
        DirectX->setObjectName("DirectX");
        DirectX->setGeometry(QRect(769, 69, 45, 15));
        DirectX->setFont(font8);
        DirectX->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    padding: 0;\n"
"    margin: 0;\n"
"    font-family: \"Inter\";\n"
"    font-size: 7 px;\n"
"    color: #FFFFFF;\n"
"    background-color: #262626;\n"
"    border: none;\n"
"    text-align: center;       /* \320\240\320\260\320\261\320\276\321\202\320\260\320\265\321\202 \320\267\320\264\320\265\321\201\321\214! */\n"
"    vertical-align: middle;   /* \320\230 \321\215\321\202\320\276 \320\261\321\203\320\264\320\265\321\202 \321\200\320\260\320\261\320\276\321\202\320\260\321\202\321\214 */\n"
"	font-weight: regular;\n"
"	border-radius: 3px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2d2d2d;\n"
"}\n"
"\n"
"QPushButton:checked {\n"
"    background-color: #3870A6;\n"
"}\n"
""));
        DirectX->setCheckable(true);
        OpenGL = new QPushButton(Window);
        OpenGL->setObjectName("OpenGL");
        OpenGL->setGeometry(QRect(814, 69, 45, 15));
        OpenGL->setFont(font6);
        OpenGL->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    min-width: 39 px;\n"
"    min-height: 12 px;\n"
"    padding: 0;\n"
"    margin: 0;\n"
"    font-family: \"Inter\";\n"
"    font-size: 7 px;\n"
"    color: #FFFFFF;\n"
"    background-color: #262626;\n"
"    border: none;\n"
"    text-align: center;       /* \320\240\320\260\320\261\320\276\321\202\320\260\320\265\321\202 \320\267\320\264\320\265\321\201\321\214! */\n"
"    vertical-align: middle;   /* \320\230 \321\215\321\202\320\276 \320\261\321\203\320\264\320\265\321\202 \321\200\320\260\320\261\320\276\321\202\320\260\321\202\321\214 */\n"
"	font-weight: regular;\n"
"	border-radius: 3px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2d2d2d;\n"
"}\n"
"\n"
"QPushButton:checked {\n"
"    background-color: #3870A6;\n"
"}\n"
""));
        OpenGL->setCheckable(true);
        OpenGL->setChecked(true);
        frame = new QFrame(Window);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 981, 654));
        frame->setStyleSheet(QString::fromUtf8("border-radius: 8px;\n"
"color: #1A1A1A;"));
        frame->setFrameShape(QFrame::Shape::NoFrame);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        TopLeft = new QLabel(frame);
        TopLeft->setObjectName("TopLeft");
        TopLeft->setGeometry(QRect(14, 34, 451, 66));
        TopLeft->setPixmap(QPixmap(QString::fromUtf8(":/TopLeftEdited.png")));
        TopLeft->setScaledContents(true);
        icon = new QLabel(frame);
        icon->setObjectName("icon");
        icon->setGeometry(QRect(18, 41, 52, 52));
        icon->setMinimumSize(QSize(52, 52));
        icon->setMaximumSize(QSize(52, 52));
        icon->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        icon->setPixmap(QPixmap(QString::fromUtf8(":/PHOST_icon.png")));
        icon->setScaledContents(true);
        Workflow = new QPushButton(frame);
        Workflow->setObjectName("Workflow");
        Workflow->setGeometry(QRect(190, 56, 80, 24));
        QFont font9;
        font9.setFamilies({QString::fromUtf8("Inter")});
        font9.setPointSize(11);
        font9.setBold(true);
        Workflow->setFont(font9);
        Workflow->setStyleSheet(QString::fromUtf8("color: #FFFFFF;\n"
"font-family: \"Inter\";\n"
"border: 0 px;\n"
"background-color: transparent;"));
        Editor = new QPushButton(frame);
        Editor->setObjectName("Editor");
        Editor->setGeometry(QRect(326, 56, 51, 24));
        Editor->setFont(font9);
        Editor->setStyleSheet(QString::fromUtf8("color: #FFFFFF;\n"
"font-family: \"Inter\";\n"
"border: 0 px;\n"
"background-color: transparent;"));
        stackedWidget = new QStackedWidget(frame);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(14, 110, 952, 487));
        stackedWidget->setStyleSheet(QString::fromUtf8("color: transparent;"));
        page = new QWidget();
        page->setObjectName("page");
        mainView = new QLabel(page);
        mainView->setObjectName("mainView");
        mainView->setGeometry(QRect(453, 0, 499, 281));
        mainView->setStyleSheet(QString::fromUtf8("border: 0 px;\n"
"background-color: #161616;"));
        mainView->setScaledContents(false);
        mainView->setAlignment(Qt::AlignmentFlag::AlignCenter);
        thumbList = new QListWidget(page);
        thumbList->setObjectName("thumbList");
        thumbList->setGeometry(QRect(453, 281, 499, 206));
        thumbList->setStyleSheet(QString::fromUtf8("border: 0 px;\n"
"background-color: #161616;"));
        thumbList->setIconSize(QSize(80, 80));
        thumbList->setMovement(QListView::Movement::Static);
        thumbList->setResizeMode(QListView::ResizeMode::Adjust);
        thumbList->setLayoutMode(QListView::LayoutMode::SinglePass);
        thumbList->setGridSize(QSize(103, 53));
        thumbList->setViewMode(QListView::ViewMode::IconMode);
        listPackages = new QListWidget(page);
        listPackages->setObjectName("listPackages");
        listPackages->setGeometry(QRect(0, 0, 451, 487));
        listPackages->setStyleSheet(QString::fromUtf8("border: 0 px;"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);
        layoutWidget = new QWidget(frame);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(15, 602, 371, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        statusText = new QLabel(layoutWidget);
        statusText->setObjectName("statusText");
        QFont font10;
        font10.setFamilies({QString::fromUtf8("Inter")});
        font10.setPointSize(10);
        font10.setBold(true);
        statusText->setFont(font10);
        statusText->setStyleSheet(QString::fromUtf8("color: #FFFFFF;\n"
"font-family: \"Inter\";\n"
""));

        horizontalLayout->addWidget(statusText);

        horizontalSpacer = new QSpacerItem(30, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        estimationText = new QLabel(layoutWidget);
        estimationText->setObjectName("estimationText");
        estimationText->setFont(font10);
        estimationText->setStyleSheet(QString::fromUtf8("color: #FFFFFF;\n"
"font-family: \"Inter\";"));

        horizontalLayout->addWidget(estimationText);

        TopRight = new QLabel(Window);
        TopRight->setObjectName("TopRight");
        TopRight->setGeometry(QRect(467, 34, 499, 66));
        TopRight->setPixmap(QPixmap(QString::fromUtf8(":/TopRightEdited.png")));
        TopRight->setScaledContents(true);
        frame->raise();
        saveMask->raise();
        drawMask->raise();
        titleBar->raise();
        progressBar->raise();
        programmName->raise();
        TopRight->raise();
        DirectX->raise();
        four->raise();
        OpenGL->raise();
        label_3->raise();
        label_2->raise();
        creatProject->raise();
        eight->raise();
        Start->raise();
        rcLink->raise();
        sixteen->raise();
        twelve->raise();
        frameRcStatus->raise();

        retranslateUi(Window);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Window);
    } // setupUi

    void retranslateUi(QWidget *Window)
    {
        Window->setWindowTitle(QCoreApplication::translate("Window", "PHOST", nullptr));
#if QT_CONFIG(tooltip)
        creatProject->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        creatProject->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(whatsthis)
        creatProject->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        creatProject->setText(QCoreApplication::translate("Window", "Create project", nullptr));
        programmName->setText(QCoreApplication::translate("Window", "Phost", nullptr));
        Start->setText(QCoreApplication::translate("Window", "Start", nullptr));
        rcLink->setText(QCoreApplication::translate("Window", "Link RealityCapture", nullptr));
        Hide->setText(QString());
        Close->setText(QString());
        miniProgrammName->setText(QCoreApplication::translate("Window", "Phost", nullptr));
        saveMask->setText(QCoreApplication::translate("Window", "Save mask", nullptr));
        drawMask->setText(QCoreApplication::translate("Window", "Draw mask", nullptr));
        label_2->setText(QCoreApplication::translate("Window", "Photometric Stereo Set", nullptr));
        eight->setText(QCoreApplication::translate("Window", "8", nullptr));
        four->setText(QCoreApplication::translate("Window", "4", nullptr));
        twelve->setText(QCoreApplication::translate("Window", "12", nullptr));
        sixteen->setText(QCoreApplication::translate("Window", "16", nullptr));
        label_3->setText(QCoreApplication::translate("Window", "Normal Orientation", nullptr));
        DirectX->setText(QCoreApplication::translate("Window", "DirectX", nullptr));
        OpenGL->setText(QCoreApplication::translate("Window", "OpenGL", nullptr));
        TopLeft->setText(QString());
        icon->setText(QString());
        Workflow->setText(QCoreApplication::translate("Window", "Workflow", nullptr));
        Editor->setText(QCoreApplication::translate("Window", "Editor", nullptr));
        mainView->setText(QString());
        statusText->setText(QString());
        estimationText->setText(QString());
        TopRight->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Window: public Ui_Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
