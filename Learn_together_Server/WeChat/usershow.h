#ifndef USERSHOW_H
#define USERSHOW_H

#include <QWidget>
#include <QPaintEvent>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <QTime>
namespace Ui {
class UserShow;
}

class UserShow : public QWidget
{
    Q_OBJECT

public:
    explicit UserShow(QWidget *parent = nullptr);
    ~UserShow();
signals:
    void SIG_itemClicked(int id,QString name);

public slots:
    //设置基本信息
    void slot_setInfo(int id,QString name);
    //重绘事件
    void paintEvent(QPaintEvent* event);
    //设置图片
    void slot_setImage(QImage& img);
    //鼠标点击用户，预览窗口进行显示
    void mousePressEvent(QMouseEvent * event);
    void slot_checkTimer();

private:
    Ui::UserShow *ui;
public:
    int m_id;
    QString m_userName;
    QImage m_img;
    friend class RoomDialg;
    QImage m_defaultImg;
    QTimer m_timer;
    QTime m_lastTime;
};

#endif // USERSHOW_H
