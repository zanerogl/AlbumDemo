//#include "widget.h"
//#include "ui_widget.h"




//Widget::Widget(QWidget *parent)
//    : QWidget(parent)
//    , ui(new Ui::Widget)
//{
//    ui->setupUi(this);

////    ui->scrollArea->horizontalScrollBar()->setEnabled(false);   //禁用水平滑杆
////    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   //隐藏滑杆

////    loadThumbnail();


//    m_listWidget = new QListWidget(this);
////    m_listWidget->setResizeMode(QListView::Adjust);
//    m_listWidget->setSpacing(8);
//}

//Widget::~Widget()
//{
//    delete ui;
//}

//bool Widget::initImgDir(QString imgDir)
//{
//    QDir Dir;
//    if(imgDir.isEmpty())
//    {
//        m_imgDir = QCoreApplication::applicationDirPath() + "/img";
//        return Dir.mkdir(m_imgDir);
//    }
//    else
//    {
//        m_imgDir = imgDir;  //保存图片文件目录
//        return Dir.mkdir(m_imgDir);
//    }
//}

//std::vector<QString> Widget::readImgPath()
//{
//    /*先清空容器*/
//    if(!m_imgNames.empty())
//    {
//        qDebug()<<"Not empty";
//        m_imgNames.clear();
//    }

//    initImgDir();

//    std::vector<std::string> fileNames;
//    std::string imgDir = m_imgDir.toStdString();
//    qDebug()<<__LINE__<<m_imgDir;
//    cv::glob(std::move(imgDir), fileNames); //这里用了CV的glob函数来获取图片路径

//    qDebug()<<__LINE__<<fileNames.size();

//    /*将每个图片名从string转为QString*/
//    for(std::vector<std::string>::iterator iter = fileNames.begin(); iter != fileNames.end(); iter++)
//    {
//        m_imgNames.push_back(QString::fromStdString(*iter));
//    }
//    return m_imgNames;   //返回图片名（不包含路径）
//}

//void Widget::loadThumbnail()
//{
//    readImgPath();
//    for(std::vector<QString>::iterator iter = m_imgNames.begin(); iter != m_imgNames.end(); iter++)
//    {
//        qDebug()<<*iter;
//    }

//    m_gridlayout = new QGridLayout();

//    int row = m_imgNames.size() / 3;    //行数
//    int remainder = m_imgNames.size() % 3;  //最后一行的缩略图数目
//    qDebug()<<__LINE__<<remainder;
//    if(remainder)   //有余数
//    {
//        row++;
//        qDebug()<<__LINE__<<row;
//    }
//    int num = 0;
//    std::vector<QString>::iterator iter = m_imgNames.begin();

//    for(int i = 0; i < row; i++)
//    {
//        if(i == row - 1 && remainder)   //最后一行且有余数
//        {
//            for(int j = 0; j < remainder; j++)
//            {
////                qDebug()<<m_imgNames.at(num);
//                m_thumbnail = new Thumbnail;
////                m_thumbnail->setImage(m_imgNames.at(num));
////                m_thumbnail->setImgname(m_imgNames.at(num));
//                m_thumbnail->setImage(*iter);
//                m_thumbnail->setImgname(*iter);
//                num++;
//                iter++;
//                m_gridlayout->addWidget(m_thumbnail, i, j);
//            }
//        }
//        else
//        {
//            for(int j = 0; j < 3; j++)
//            {
//                m_thumbnail = new Thumbnail;
//                m_thumbnail->setImage(m_imgNames.at(num));
//                m_thumbnail->setImgname(m_imgNames.at(num));
//                num++;
//                m_gridlayout->addWidget(m_thumbnail, i, j);
//            }
//        }
//    }

//    ui->scrollArea->widget()->setLayout(m_gridlayout);
//}


#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    initListWidget();
    initImgDir();
    loadThumbnail();



    QPushButton *btn = new QPushButton;
    btn->setText("reload");
    btn->setFixedSize(100, 40);
    btn->move(this->width()-100, this->height()-100);
    btn->setParent(this);

    connect(btn, &QPushButton::clicked, this, &Widget::removeImg);

    connect(m_listWidget, &QListWidget::itemClicked, this, [=](){
        qDebug()<<"sdf";
//        m_listWidget->hide();
//        displayImg(m_listWidget->currentItem());
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initListWidget()
{
    /*QListWidget基本设置*/
    m_listWidget = new QListWidget(this);
    m_listWidget->setIconSize(QSize(this->width()/3-30, this->width()/3-30));
    m_listWidget->setResizeMode(QListView::Adjust);
    m_listWidget->setViewMode(QListView::IconMode);
    m_listWidget->setMovement(QListView::Static);
    m_listWidget->setSpacing(8);
    /*放入主widget中*/
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_listWidget);
    mainLayout->setMargin(10);
    this->setLayout(mainLayout);
}

bool Widget::initImgDir(QString imgDir)
{
    QDir Dir;
    if(imgDir.isEmpty())
    {
        m_imgDir = QCoreApplication::applicationDirPath() + "/img";
        Dir.mkdir(m_imgDir);
        qDebug()<<__LINE__<<m_imgDir;
        return Dir.exists();     //若路径已经存在则会返回false
    }
    else
    {
        m_imgDir = imgDir;  //保存图片文件目录
        Dir.mkdir(m_imgDir);
        return Dir.exists();
    }
}

bool Widget::readImgPath()
{
    if(m_imgDir != "")
    {
        /*设置过滤器读取图片*/
        QDir dir(m_imgDir);
        dir.setFilter(QDir::Files | QDir::NoSymLinks);
        QStringList filters;
        filters << "*.png" << "*.jpg";
        dir.setNameFilters(filters);
        m_imgList = dir.entryList();    //读取文件名
        qDebug()<<m_imgList.count();
        return true;
    }
    else
    {
        return false;
    }
}

void Widget::loadThumbnail()
{
    m_listWidget->clear();  //先清空再加载

    if(!readImgPath())  //读取图片失败
    {
        return;
    }

    /*创建单元项*/
    const QSize IMAGE_SIZE(this->width()/3-30, this->width()/3-30);
    for (int i = 0; i<m_imgList.count(); ++i)
    {
        QPixmap pixmap(m_imgDir + "\\" + m_imgList.at(i));
        QListWidgetItem *listWidgetItem = new QListWidgetItem(QIcon(pixmap.scaled(IMAGE_SIZE)), m_imgList.at(i));
        listWidgetItem->setSizeHint(QSize(this->width()/3-20, this->width()/3-10));
        m_listWidget->insertItem(i, listWidgetItem);
    }
}

void Widget::displayImg(QListWidgetItem *item)
{
    m_showWidget = new QLabel(this);
//  m_showWidget->setPixmap(m_pixmap.scaled(m_imgLabel->width(),m_imgLabel->height(),Qt::KeepAspectRatio, Qt::SmoothTransformation));
    m_showWidget->setPixmap(QPixmap(m_imgDir + "\\" + m_imgList.at(m_listWidget->row(item))));
//    m_showWidget.showMaximized();
    m_showWidget->show();
}

void Widget::removeImg()
{
    /*删除缩略图*/
    QListWidgetItem *item = m_listWidget->currentItem();
    m_listWidget->removeItemWidget(item);
    /*删除文件*/
    QFileInfo fileInfo(m_imgDir + "\\" + item->text());
    if(fileInfo.isFile())
    {
        QFile::remove(m_imgDir + "\\" + item->text());
    }
    delete item;
}

void Widget::on_pushButton_clicked()
{
    QListWidgetItem *item = m_listWidget->currentItem();
    m_listWidget->removeItemWidget(item);
    delete item;
}
