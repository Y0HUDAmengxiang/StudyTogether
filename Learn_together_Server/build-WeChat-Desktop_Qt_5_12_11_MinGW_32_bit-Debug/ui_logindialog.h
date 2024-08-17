/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QTabWidget *tw_page;
    QWidget *page_1;
    QPushButton *pb_commit;
    QPushButton *pb_clear;
    QLabel *lb_tel;
    QLabel *lb_password;
    QLineEdit *le_tel;
    QLineEdit *le_password;
    QWidget *page_3;
    QPushButton *pb_commit_register;
    QPushButton *pb_clear_register;
    QLabel *lb_name_register;
    QLabel *lb_tel_register;
    QLabel *lb_password_register;
    QLineEdit *le_name_register;
    QLineEdit *le_tel_register;
    QLineEdit *le_password_register;
    QLineEdit *le_confirm_register;
    QLabel *lb_confirm_register;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->resize(358, 271);
        LoginDialog->setMinimumSize(QSize(358, 271));
        LoginDialog->setMaximumSize(QSize(358, 271));
        tw_page = new QTabWidget(LoginDialog);
        tw_page->setObjectName(QString::fromUtf8("tw_page"));
        tw_page->setGeometry(QRect(0, 0, 361, 271));
        tw_page->setMinimumSize(QSize(361, 271));
        tw_page->setMaximumSize(QSize(361, 271));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(9);
        tw_page->setFont(font);
        page_1 = new QWidget();
        page_1->setObjectName(QString::fromUtf8("page_1"));
        pb_commit = new QPushButton(page_1);
        pb_commit->setObjectName(QString::fromUtf8("pb_commit"));
        pb_commit->setGeometry(QRect(30, 110, 81, 21));
        pb_commit->setFont(font);
        pb_clear = new QPushButton(page_1);
        pb_clear->setObjectName(QString::fromUtf8("pb_clear"));
        pb_clear->setGeometry(QRect(190, 110, 81, 21));
        pb_clear->setFont(font);
        lb_tel = new QLabel(page_1);
        lb_tel->setObjectName(QString::fromUtf8("lb_tel"));
        lb_tel->setGeometry(QRect(10, 30, 61, 16));
        lb_tel->setFont(font);
        lb_password = new QLabel(page_1);
        lb_password->setObjectName(QString::fromUtf8("lb_password"));
        lb_password->setGeometry(QRect(10, 70, 61, 16));
        lb_password->setFont(font);
        le_tel = new QLineEdit(page_1);
        le_tel->setObjectName(QString::fromUtf8("le_tel"));
        le_tel->setGeometry(QRect(70, 30, 211, 21));
        le_tel->setFont(font);
        le_password = new QLineEdit(page_1);
        le_password->setObjectName(QString::fromUtf8("le_password"));
        le_password->setGeometry(QRect(70, 70, 211, 21));
        le_password->setFont(font);
        le_password->setEchoMode(QLineEdit::Password);
        le_password->setClearButtonEnabled(true);
        tw_page->addTab(page_1, QString());
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        pb_commit_register = new QPushButton(page_3);
        pb_commit_register->setObjectName(QString::fromUtf8("pb_commit_register"));
        pb_commit_register->setGeometry(QRect(50, 180, 81, 21));
        pb_commit_register->setFont(font);
        pb_clear_register = new QPushButton(page_3);
        pb_clear_register->setObjectName(QString::fromUtf8("pb_clear_register"));
        pb_clear_register->setGeometry(QRect(200, 180, 81, 21));
        pb_clear_register->setFont(font);
        lb_name_register = new QLabel(page_3);
        lb_name_register->setObjectName(QString::fromUtf8("lb_name_register"));
        lb_name_register->setGeometry(QRect(10, 30, 61, 16));
        lb_name_register->setFont(font);
        lb_tel_register = new QLabel(page_3);
        lb_tel_register->setObjectName(QString::fromUtf8("lb_tel_register"));
        lb_tel_register->setGeometry(QRect(10, 70, 61, 16));
        lb_tel_register->setFont(font);
        lb_password_register = new QLabel(page_3);
        lb_password_register->setObjectName(QString::fromUtf8("lb_password_register"));
        lb_password_register->setGeometry(QRect(10, 110, 61, 16));
        lb_password_register->setFont(font);
        le_name_register = new QLineEdit(page_3);
        le_name_register->setObjectName(QString::fromUtf8("le_name_register"));
        le_name_register->setGeometry(QRect(80, 30, 211, 21));
        le_name_register->setFont(font);
        le_tel_register = new QLineEdit(page_3);
        le_tel_register->setObjectName(QString::fromUtf8("le_tel_register"));
        le_tel_register->setGeometry(QRect(80, 70, 211, 21));
        le_tel_register->setFont(font);
        le_password_register = new QLineEdit(page_3);
        le_password_register->setObjectName(QString::fromUtf8("le_password_register"));
        le_password_register->setGeometry(QRect(80, 110, 211, 21));
        le_password_register->setFont(font);
        le_password_register->setEchoMode(QLineEdit::Password);
        le_password_register->setClearButtonEnabled(true);
        le_confirm_register = new QLineEdit(page_3);
        le_confirm_register->setObjectName(QString::fromUtf8("le_confirm_register"));
        le_confirm_register->setGeometry(QRect(80, 150, 211, 21));
        le_confirm_register->setFont(font);
        le_confirm_register->setEchoMode(QLineEdit::Password);
        le_confirm_register->setClearButtonEnabled(true);
        lb_confirm_register = new QLabel(page_3);
        lb_confirm_register->setObjectName(QString::fromUtf8("lb_confirm_register"));
        lb_confirm_register->setGeometry(QRect(10, 150, 61, 16));
        lb_confirm_register->setFont(font);
        tw_page->addTab(page_3, QString());
        QWidget::setTabOrder(le_name_register, le_tel_register);
        QWidget::setTabOrder(le_tel_register, le_password_register);
        QWidget::setTabOrder(le_password_register, le_confirm_register);
        QWidget::setTabOrder(le_confirm_register, pb_clear_register);
        QWidget::setTabOrder(pb_clear_register, pb_commit_register);
        QWidget::setTabOrder(pb_commit_register, tw_page);
        QWidget::setTabOrder(tw_page, le_tel);
        QWidget::setTabOrder(le_tel, le_password);
        QWidget::setTabOrder(le_password, pb_commit);
        QWidget::setTabOrder(pb_commit, pb_clear);

        retranslateUi(LoginDialog);

        tw_page->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "Dialog", nullptr));
        pb_commit->setText(QApplication::translate("LoginDialog", "\347\231\273\345\275\225", nullptr));
        pb_clear->setText(QApplication::translate("LoginDialog", "\346\270\205\351\231\244", nullptr));
        lb_tel->setText(QApplication::translate("LoginDialog", "\350\264\246\345\217\267\357\274\232", nullptr));
        lb_password->setText(QApplication::translate("LoginDialog", "\345\257\206\347\240\201", nullptr));
        le_tel->setText(QApplication::translate("LoginDialog", "15765453925", nullptr));
        le_password->setText(QApplication::translate("LoginDialog", "2308221223.fan", nullptr));
        tw_page->setTabText(tw_page->indexOf(page_1), QApplication::translate("LoginDialog", "\347\231\273\345\275\225", nullptr));
        pb_commit_register->setText(QApplication::translate("LoginDialog", "\346\263\250\345\206\214", nullptr));
        pb_clear_register->setText(QApplication::translate("LoginDialog", "\346\270\205\347\251\272", nullptr));
        lb_name_register->setText(QApplication::translate("LoginDialog", "\346\230\265\347\247\260\357\274\232", nullptr));
        lb_tel_register->setText(QApplication::translate("LoginDialog", "\346\211\213\346\234\272\345\217\267\357\274\232", nullptr));
        lb_password_register->setText(QApplication::translate("LoginDialog", "\345\257\206\347\240\201\357\274\232", nullptr));
#ifndef QT_NO_TOOLTIP
        le_name_register->setToolTip(QApplication::translate("LoginDialog", "<html><head/><body><p>\350\257\267\350\276\223\345\205\24510\344\275\215\344\273\245\345\206\205\346\230\265\347\247\260</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        le_tel_register->setToolTip(QApplication::translate("LoginDialog", "<html><head/><body><p>\350\257\267\350\276\223\345\205\2458-11\344\275\215\346\211\213\346\234\272\345\217\267</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        le_password_register->setToolTip(QApplication::translate("LoginDialog", "<html><head/><body><p>\350\257\267\350\276\223\345\205\24520\344\275\215\344\273\245\345\206\205\345\257\206\347\240\201\357\274\214\345\214\205\345\220\253\345\244\247\345\260\217\345\206\231\345\255\227\346\257\215\345\217\212\346\225\260\345\255\227</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        le_confirm_register->setToolTip(QApplication::translate("LoginDialog", "<html><head/><body><p>\350\257\267\350\276\223\345\205\24520\344\275\215\344\273\245\345\206\205\345\257\206\347\240\201\357\274\214\345\214\205\345\220\253\345\244\247\345\260\217\345\206\231\345\255\227\346\257\215\345\217\212\346\225\260\345\255\227</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        lb_confirm_register->setText(QApplication::translate("LoginDialog", "\347\241\256\350\256\244\345\257\206\347\240\201\357\274\232", nullptr));
        tw_page->setTabText(tw_page->indexOf(page_3), QApplication::translate("LoginDialog", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
