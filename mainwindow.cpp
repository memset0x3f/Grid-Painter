#include "mainwindow.h"
#include "qpainter.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QPixmap *pixmap;

void MainWindow::on_choose_clicked()
{
    QString curPath=QDir::currentPath();//获取当前路径
    QString str=QFileDialog::getOpenFileName(this,"打开文件",curPath);
   // QString str=QFileDialog::getOpenFileName(this,"打开文件",".");//"." 代表程序运行目录
   // QString str=QFileDialog::getOpenFileName(this,"打开文件","/");//"/" 代表当前盘符的根目录
    //show图片
    pixmap = new QPixmap(str);
    *pixmap = pixmap->scaled(ui->img->width(), ui->img->height(),Qt::KeepAspectRatio);

    ui->img->setPixmap(*pixmap);
}


void MainWindow::on_process_clicked()
{
    if(pixmap == nullptr || pixmap->isNull()){
        QFont ft;
        ft.setPointSize(20);
        ui->img->setFont(ft);
        ui->img->setText("未选择图片");
        return;
    }
    QPixmap pix = *pixmap;
    QPainter painter(&pix);
    double w = pixmap->width(), h = pixmap->height();
    QString str = ui->mode->currentText();
    QString line = ui->lineBox->currentText();

    QPen pen(QColor(255, 0, 0), 1.5);
    if(line == "虚线"){
//        pen.setWidth(1.5);
        pen.setStyle(Qt::DashLine);
    }
    painter.setPen(pen);

    if(str == "米字格"){
        painter.drawLine(0, 0, w, h);
        painter.drawLine(w, 0, 0, h);
        painter.drawLine(w/2, 0, w/2, h);
        painter.drawLine(0, h/2, w, h/2);
    }
    else if(str == "九宫格"){
        painter.drawLine(0, h/3, w, h/3);
        painter.drawLine(0, h/3*2, w, h/3*2);
        painter.drawLine(w/3, 0, w/3, h);
        painter.drawLine(w/3*2, 0, w/3*2, h);
    }
    else if(str == "田字格"){
        painter.drawLine(w/2, 0, w/2, h);
        painter.drawLine(0, h/2, w, h/2);
    }
    ui->img->setPixmap(pix);
}

