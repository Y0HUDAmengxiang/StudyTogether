/********************************************************************************
** Form generated from reading UI file 'roomdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROOMDIALOG_H
#define UI_ROOMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <usershow.h>

QT_BEGIN_NAMESPACE

class Ui_RoomDialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *wdg_title;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lb_title;
    QSpacerItem *horizontalSpacer;
    QPushButton *pb_min;
    QPushButton *pb_max;
    QPushButton *pb_close;
    QHBoxLayout *horizontalLayout;
    QWidget *wdg_left;
    QHBoxLayout *horizontalLayout_4;
    UserShow *wdg_userShow;
    QWidget *wdg_right;
    QVBoxLayout *verticalLayout_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_2;
    QWidget *wdg_list;
    QSpacerItem *verticalSpacer;
    QWidget *wdg_bottom;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *cb_vedio;
    QCheckBox *cb_audio;
    QCheckBox *cb_desk;
    QComboBox *cb_moji;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pb_quit;

    void setupUi(QDialog *RoomDialog)
    {
        if (RoomDialog->objectName().isEmpty())
            RoomDialog->setObjectName(QString::fromUtf8("RoomDialog"));
        RoomDialog->resize(1205, 902);
        RoomDialog->setMinimumSize(QSize(1205, 902));
        RoomDialog->setMaximumSize(QSize(1205, 902));
        RoomDialog->setSizeGripEnabled(true);
        verticalLayout = new QVBoxLayout(RoomDialog);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        wdg_title = new QWidget(RoomDialog);
        wdg_title->setObjectName(QString::fromUtf8("wdg_title"));
        wdg_title->setMinimumSize(QSize(1200, 40));
        wdg_title->setMaximumSize(QSize(16777215, 40));
        wdg_title->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_2 = new QHBoxLayout(wdg_title);
        horizontalLayout_2->setSpacing(5);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 10, 0);
        lb_title = new QLabel(wdg_title);
        lb_title->setObjectName(QString::fromUtf8("lb_title"));
        lb_title->setEnabled(true);
        lb_title->setMinimumSize(QSize(300, 40));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(9);
        lb_title->setFont(font);

        horizontalLayout_2->addWidget(lb_title);

        horizontalSpacer = new QSpacerItem(1100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pb_min = new QPushButton(wdg_title);
        pb_min->setObjectName(QString::fromUtf8("pb_min"));
        pb_min->setMinimumSize(QSize(30, 30));
        pb_min->setMaximumSize(QSize(30, 30));

        horizontalLayout_2->addWidget(pb_min);

        pb_max = new QPushButton(wdg_title);
        pb_max->setObjectName(QString::fromUtf8("pb_max"));
        pb_max->setMinimumSize(QSize(30, 30));
        pb_max->setMaximumSize(QSize(30, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        pb_max->setFont(font1);

        horizontalLayout_2->addWidget(pb_max);

        pb_close = new QPushButton(wdg_title);
        pb_close->setObjectName(QString::fromUtf8("pb_close"));
        pb_close->setMinimumSize(QSize(30, 30));
        pb_close->setMaximumSize(QSize(30, 30));

        horizontalLayout_2->addWidget(pb_close);


        verticalLayout->addWidget(wdg_title);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        wdg_left = new QWidget(RoomDialog);
        wdg_left->setObjectName(QString::fromUtf8("wdg_left"));
        wdg_left->setMinimumSize(QSize(900, 820));
        wdg_left->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_4 = new QHBoxLayout(wdg_left);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        wdg_userShow = new UserShow(wdg_left);
        wdg_userShow->setObjectName(QString::fromUtf8("wdg_userShow"));
        wdg_userShow->setFont(font);

        horizontalLayout_4->addWidget(wdg_userShow);


        horizontalLayout->addWidget(wdg_left);

        wdg_right = new QWidget(RoomDialog);
        wdg_right->setObjectName(QString::fromUtf8("wdg_right"));
        wdg_right->setMinimumSize(QSize(300, 820));
        wdg_right->setMaximumSize(QSize(300, 16777215));
        wdg_right->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_3 = new QVBoxLayout(wdg_right);
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 3, 0, 0);
        scrollArea = new QScrollArea(wdg_right);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 298, 815));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        wdg_list = new QWidget(scrollAreaWidgetContents_2);
        wdg_list->setObjectName(QString::fromUtf8("wdg_list"));
        wdg_list->setMinimumSize(QSize(289, 0));

        verticalLayout_2->addWidget(wdg_list);

        verticalSpacer = new QSpacerItem(20, 958, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_3->addWidget(scrollArea);


        horizontalLayout->addWidget(wdg_right);


        verticalLayout->addLayout(horizontalLayout);

        wdg_bottom = new QWidget(RoomDialog);
        wdg_bottom->setObjectName(QString::fromUtf8("wdg_bottom"));
        wdg_bottom->setMinimumSize(QSize(1200, 40));
        wdg_bottom->setMaximumSize(QSize(16777215, 40));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font2.setPointSize(14);
        wdg_bottom->setFont(font2);
        wdg_bottom->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_3 = new QHBoxLayout(wdg_bottom);
        horizontalLayout_3->setSpacing(40);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 30, 0);
        cb_vedio = new QCheckBox(wdg_bottom);
        cb_vedio->setObjectName(QString::fromUtf8("cb_vedio"));
        cb_vedio->setFont(font);

        horizontalLayout_3->addWidget(cb_vedio);

        cb_audio = new QCheckBox(wdg_bottom);
        cb_audio->setObjectName(QString::fromUtf8("cb_audio"));
        cb_audio->setFont(font);

        horizontalLayout_3->addWidget(cb_audio);

        cb_desk = new QCheckBox(wdg_bottom);
        cb_desk->setObjectName(QString::fromUtf8("cb_desk"));
        cb_desk->setFont(font);

        horizontalLayout_3->addWidget(cb_desk);

        cb_moji = new QComboBox(wdg_bottom);
        cb_moji->addItem(QString());
        cb_moji->addItem(QString());
        cb_moji->addItem(QString());
        cb_moji->setObjectName(QString::fromUtf8("cb_moji"));
        cb_moji->setMinimumSize(QSize(100, 30));
        cb_moji->setFont(font);

        horizontalLayout_3->addWidget(cb_moji);

        horizontalSpacer_2 = new QSpacerItem(793, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        pb_quit = new QPushButton(wdg_bottom);
        pb_quit->setObjectName(QString::fromUtf8("pb_quit"));
        pb_quit->setMinimumSize(QSize(150, 30));
        pb_quit->setFont(font);

        horizontalLayout_3->addWidget(pb_quit);


        verticalLayout->addWidget(wdg_bottom);


        retranslateUi(RoomDialog);

        QMetaObject::connectSlotsByName(RoomDialog);
    } // setupUi

    void retranslateUi(QDialog *RoomDialog)
    {
        RoomDialog->setWindowTitle(QApplication::translate("RoomDialog", "Dialog", nullptr));
        lb_title->setText(QApplication::translate("RoomDialog", "\346\210\277\351\227\264\345\217\267\357\274\232123456789", nullptr));
        pb_min->setText(QApplication::translate("RoomDialog", "\344\270\200", nullptr));
        pb_max->setText(QApplication::translate("RoomDialog", "\345\217\243", nullptr));
        pb_close->setText(QApplication::translate("RoomDialog", "X", nullptr));
        cb_vedio->setText(QApplication::translate("RoomDialog", "\350\247\206\351\242\221", nullptr));
        cb_audio->setText(QApplication::translate("RoomDialog", "\351\237\263\351\242\221", nullptr));
        cb_desk->setText(QApplication::translate("RoomDialog", "\346\241\214\351\235\242", nullptr));
        cb_moji->setItemText(0, QApplication::translate("RoomDialog", "\346\227\240\346\273\244\351\225\234", nullptr));
        cb_moji->setItemText(1, QApplication::translate("RoomDialog", "\345\234\243\350\257\236\350\200\201\344\272\272", nullptr));
        cb_moji->setItemText(2, QApplication::translate("RoomDialog", "\345\205\224\345\245\263\351\203\216", nullptr));

        pb_quit->setText(QApplication::translate("RoomDialog", "\351\200\200\345\207\272\346\210\277\351\227\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RoomDialog: public Ui_RoomDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROOMDIALOG_H
