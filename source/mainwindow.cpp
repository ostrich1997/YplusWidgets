#include "mainwindow.h"
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


void MainWindow::on_pushButton_clicked()
{
        double u = 1;       //流速
        double mu = 0.000017894;      //动力粘度
        double L = 1;       //特征长度
        double rou = 1.225;     //密度
        double yPlus = 1;   //y+

        yPlus = ui->lineEdit->text().toDouble();
        rou = ui->lineEdit_3->text().toDouble();
        L = ui->lineEdit_2->text().toDouble();
        mu = ui->lineEdit_4->text().toDouble();
        u = ui->lineEdit_5->text().toDouble();

        double y = 0;       //第一层网格节点到壁面距离
        double ym = 0;
        double cf = 0;      //壁面摩擦系数
        double tempcf = 0;
        double nu = 0;      //运动粘度
        double uStar = 0;   //静壁面摩擦系数
        double touW = 0;    //壁面剪应力
        double Re = 0;      //雷诺数
        double func = 0;
        double dfunc = 0;
        double df = 0;
        double log10e = 0;

        log10e = log10(exp(1));



        Re = u * rou * L / mu;
        nu = mu / rou;

        //牛顿-拉夫逊（拉弗森）方法（Newton-Raphson method）迭代cf
        cf = 0.02;
        for (int i = 0; i < 1000; i++)
        {
            func = 4.15 * sqrt(cf) * log10(Re * cf) + 1.7 * sqrt(cf) - 1;
            dfunc = (4.15 * log10e + 0.5 * 4.15 * log10(Re * cf) + 0.5 * 1.7) / sqrt(cf);
            df = func / dfunc;
            if (df <= 0.0000001)
            {
                break;
            }
            tempcf = cf - df;
            if (tempcf < 0)
            {
                cf = cf / 2;
            }
            else
            {
                cf = tempcf;
            }
        }

        touW = rou * u * u * cf / 2;
        uStar = sqrt(touW / rou);
        y = yPlus * nu / uStar;
        ym = y * 1000;


        ui->textBrowser->setText(QString::number(y));
        ui->textBrowser_2->setText(QString::number(ym));
        ui->textBrowser_3->setText(QString::number(Re));
}


void MainWindow::on_pushButton_2_clicked()
{
    close();
}

