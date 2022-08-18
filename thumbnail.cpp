#include "thumbnail.h"

Thumbnail::Thumbnail(QWidget *parent) : QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(170, 210);

    /*实例化成员变量*/
    m_gridLayout = new QGridLayout;
    m_imgLabel = new QLabel(this);
    m_nameLabel = new QLabel(this);

    /*设置成员变量属性*/
    m_imgLabel->setFixedSize(150, 150);
    m_imgLabel->setFrameShape(QFrame::Box);
    m_imgLabel->setAlignment(Qt::AlignCenter);
    m_nameLabel->setWordWrap(true);
    m_nameLabel->setFrameShape(QFrame::Box);
    m_nameLabel->setAlignment(Qt::AlignTop);

    /*添加到布局，布局添加到widget*/
    m_gridLayout->addWidget(m_imgLabel, 0, 0, 1, 1);
    m_gridLayout->addWidget(m_nameLabel, 1, 0, 1, 1);

    this->setLayout(m_gridLayout);
}

void Thumbnail::setImage(QString imgPath)
{
    m_imgPath = imgPath;    //保存图片地址
//    imgPath = "D:/Project/C++/Qt/Demo/build-AlbumDemo-Desktop_Qt_5_14_2_MinGW_64_bit-Debug/debug/img/aom.png";
    QPixmap pixmap;
    if(!pixmap.load(imgPath)){
        qDebug()<<"Error! Can not load the image.";

    }
    else
    {

        m_imgLabel->setPixmap(pixmap.scaled(m_imgLabel->width(),m_imgLabel->height(),Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void Thumbnail::setImgname(QString imgPath)
{
    /*拆分图片路径和图片名*/
    for(int i = imgPath.size()-1; i>=0; i--)
    {
        if(imgPath.at(i)=='/')
        {
            break;
        }
        m_imgName.push_front(imgPath.at(i));
    }
    if(m_imgName.isEmpty())
        qDebug()<<"Is empty";
    m_nameLabel->setText(m_imgName);
}

void Thumbnail::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug()<<"mousePressEvent";
}

void Thumbnail::test()
{
    qDebug()<<"sd";
}
