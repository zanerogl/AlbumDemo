#ifndef THUMBNAIL_H
#define THUMBNAIL_H

#include <QWidget>
#include <QLabel>
#include <QFrame>
#include <QLayout>
#include <QDebug>
#include <QPixmap>

class Thumbnail : public QWidget
{
    Q_OBJECT
public:
    explicit Thumbnail(QWidget *parent = nullptr);

    /**
     * @brief setImage  读取图片
     * @param imgPath   图片路径
     */
    void setImage(QString imgPath);

    /**
     * @brief 在Label上设置图片名字
     * @param 图片路径
     */
    void setImgname(QString imgPath);

    /**
     * @brief mousePressEvent   重写鼠标事件，
     * @param event
     */
    void mousePressEvent(QMouseEvent *event) override;


    void test();

signals:


private:
    QLabel *m_imgLabel, *m_nameLabel;   //图片label和图片名label
    QGridLayout *m_gridLayout;  //删格化布局

    QString m_imgPath, m_imgName;  //用于保存图片路径和名称的label


};

#endif // THUMBNAIL_H
