//#ifndef WIDGET_H
//#define WIDGET_H

//#include <QWidget>
//#include <QPushButton>
//#include <QLayout>
//#include <QString>
//#include <QList>
//#include <QDebug>
//#include <iostream>
//#include <vector>
//#include <QtCore>
//#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/opencv.hpp>
//#include <QScrollBar>
//#include <QLayout>
//#include "thumbnail.h"

//#include <QListWidget>
//#include <QListWidgetItem>

//#define W_ICONSIZE 150
//#define H_ICONSIZE 150
//#define H_ITEMSIZE 100

//QT_BEGIN_NAMESPACE
//namespace Ui { class Widget; }
//QT_END_NAMESPACE

//class Widget : public QWidget
//{
//    Q_OBJECT

//public:
//    Widget(QWidget *parent = nullptr);
//    ~Widget();

//    /**
//     * @brief initImgDir    初始化图片文件目录
//     * @param imgDir        图片目录，默认为可执行程序下的img/
//     * @return bool         成功则为true，失败则为false
//     */
//    bool initImgDir(QString imgDir = "");

//    /**
//     * @brief readImgPath       读取图片路径
//     * @return vector<QString>   返回一个包含所有图片路径的容器
//     */
//    std::vector<QString> readImgPath();

//    /**
//     * @brief loadThumbnail     加载缩略图
//     */
//    void loadThumbnail();




//    void init();    // 初始化
//private:
//    Ui::Widget *ui;

//    QString m_imgDir;       //图片文件目录
//    std::string m_imgDir_std;

//    std::vector<QString> m_imgNames;    //图片文件目录下每张图片的名字

//    Thumbnail *m_thumbnail;

//    QGridLayout *m_gridlayout;


//    QStringList m_imgList;      // 文件目录下所有的图像文件名
//    QListWidget *m_listWidget;  // 预览窗口
//    QString m_strPath;          // 文件夹路径
//    QLabel m_showWidget;        // 图像显示窗口








//};
//#endif // WIDGET_H








#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include <QString>
#include <QList>
#include <QDebug>
#include <iostream>
#include <vector>
#include <QtCore>
#include <QScrollBar>
#include <QLayout>
#include "thumbnail.h"

#include <QListWidget>
#include <QListWidgetItem>
#include <QSize>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    /**
     * @brief setListWidgetAttr 设置ListWidget的属性
     */
    void initListWidget();
    /**
     * @brief initImgDir    初始化图片文件目录
     * @param imgDir        图片目录，默认为可执行程序下的img/
     * @return bool         成功则为true，失败则为false
     */
    bool initImgDir(QString imgDir = "");

    /**
     * @brief readImgPath       读取图片路径
     * @return vector<QString>   返回一个包含所有图片路径的容器
     */
    bool readImgPath();

    /**
     * @brief loadThumbnail     加载缩略图
     */
    void loadThumbnail();

    /**
     * @brief displayImg    展示图片
     */
    void displayImg(QListWidgetItem *item);

    /**
     * @brief removeImg     删除图片
     */
    void removeImg();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;

    QString m_imgDir;               //图片文件目录
    QStringList m_imgList;          // 文件目录下所有的图像文件名
    QListWidget *m_listWidget;      // 预览窗口
    QLabel *m_showWidget;            // 图像显示窗口

    QSize m_imgSize, m_itemSize;    //图片尺寸和item尺寸

};
#endif // WIDGET_H






