/********************************************************************************
** Form generated from reading UI file 'wechatdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WECHATDIALOG_H
#define UI_WECHATDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WeChatDialog
{
public:
    QPushButton *pb_icon;
    QPushButton *pb_set;
    QLabel *lb_name;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QToolButton *pb_join;
    QToolButton *pb_create;
    QToolButton *pb_history;

    void setupUi(QDialog *WeChatDialog)
    {
        if (WeChatDialog->objectName().isEmpty())
            WeChatDialog->setObjectName(QString::fromUtf8("WeChatDialog"));
        WeChatDialog->resize(360, 576);
        WeChatDialog->setMinimumSize(QSize(360, 576));
        WeChatDialog->setMaximumSize(QSize(360, 576));
        pb_icon = new QPushButton(WeChatDialog);
        pb_icon->setObjectName(QString::fromUtf8("pb_icon"));
        pb_icon->setGeometry(QRect(5, 5, 51, 61));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/tx/11.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_icon->setIcon(icon);
        pb_icon->setIconSize(QSize(60, 60));
        pb_icon->setFlat(true);
        pb_set = new QPushButton(WeChatDialog);
        pb_set->setObjectName(QString::fromUtf8("pb_set"));
        pb_set->setGeometry(QRect(320, 20, 30, 30));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/sett.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_set->setIcon(icon1);
        pb_set->setIconSize(QSize(30, 30));
        lb_name = new QLabel(WeChatDialog);
        lb_name->setObjectName(QString::fromUtf8("lb_name"));
        lb_name->setGeometry(QRect(80, 20, 191, 31));
        scrollArea = new QScrollArea(WeChatDialog);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(0, 169, 351, 391));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 351, 391));
        scrollArea->setWidget(scrollAreaWidgetContents);
        layoutWidget = new QWidget(WeChatDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 90, 341, 71));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(70);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pb_join = new QToolButton(layoutWidget);
        pb_join->setObjectName(QString::fromUtf8("pb_join"));
        pb_join->setMinimumSize(QSize(60, 60));
        pb_join->setMaximumSize(QSize(60, 60));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(9);
        pb_join->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/searchbox_button.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_join->setIcon(icon2);
        pb_join->setIconSize(QSize(60, 60));
        pb_join->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout->addWidget(pb_join);

        pb_create = new QToolButton(layoutWidget);
        pb_create->setObjectName(QString::fromUtf8("pb_create"));
        pb_create->setMinimumSize(QSize(60, 60));
        pb_create->setMaximumSize(QSize(60, 60));
        pb_create->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/color.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_create->setIcon(icon3);
        pb_create->setIconSize(QSize(60, 60));
        pb_create->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout->addWidget(pb_create);

        pb_history = new QToolButton(layoutWidget);
        pb_history->setObjectName(QString::fromUtf8("pb_history"));
        pb_history->setMinimumSize(QSize(60, 60));
        pb_history->setMaximumSize(QSize(60, 60));
        pb_history->setFont(font);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/send.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_history->setIcon(icon4);
        pb_history->setIconSize(QSize(60, 60));
        pb_history->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout->addWidget(pb_history);


        retranslateUi(WeChatDialog);

        QMetaObject::connectSlotsByName(WeChatDialog);
    } // setupUi

    void retranslateUi(QDialog *WeChatDialog)
    {
        WeChatDialog->setWindowTitle(QApplication::translate("WeChatDialog", "WeChatDialog", nullptr));
        pb_icon->setText(QString());
        pb_set->setText(QString());
        lb_name->setText(QApplication::translate("WeChatDialog", "\346\265\213\350\257\225\347\224\250\346\210\267", nullptr));
        pb_join->setText(QApplication::translate("WeChatDialog", "\345\212\240\345\205\245\344\274\232\350\256\256", nullptr));
        pb_create->setText(QApplication::translate("WeChatDialog", "\345\210\233\345\273\272\344\274\232\350\256\256", nullptr));
        pb_history->setText(QApplication::translate("WeChatDialog", "\345\216\206\345\217\262\344\274\232\350\256\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WeChatDialog: public Ui_WeChatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WECHATDIALOG_H
