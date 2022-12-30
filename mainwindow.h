#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QContextMenuEvent>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "weatherdata.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QMenu *mExitMenu;     //右键退出的菜单
    QAction *mExitAct;    //退出的行为

    QPoint mOffset;       //窗口移动时，鼠标与窗口左上角的偏移

    QNetworkAccessManager *mNetAccessManager;

    Today mToday;
    Day mDay[6];

    //星期和日期
    QList<QLabel*> mWeekList;
    QList<QLabel*> mDateList;

    //天气和天气图标
    QList<QLabel*> mTypeList;
    QList<QLabel*> mTypeIconList;

    //天气污染指数
    QList<QLabel*> mAqiList;

    //风力和风向
    QList<QLabel*> mFxList;
    QList<QLabel*> mFlList;

    QMap<QString, QString> mTypeMap;

protected:
    void contextMenuEvent(QContextMenuEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void getWeatherInfo(QString cityCode);       //获取天气数据

    void parseJson(QByteArray& byteArray);
    void updateUI();

    //重写父类的eventfilter方法
    bool eventFilter(QObject* watched, QEvent* event);

    //绘制高低温曲线
    void painHighCurve();
    void painLowCurve();

private slots:

    void onReplied(QNetworkReply *reply);


    void on_btnSearch_clicked();
};
#endif // MAINWINDOW_H
