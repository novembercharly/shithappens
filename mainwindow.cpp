#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>
#include <QString>
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{


        double a = -100; //Начало интервала, Ox
        double b =  100; //Конец интервала, Ox
        double h = 0.01; //Шаг

        int N=(b-a)/h + 2; //количество точек

        QString stra = ui->lineEdit->text();
        int A = stra.toInt();
        QString strd = ui->lineEdit_2->text();
        int D = strd.toInt();
        QString strla = ui->lineEdit_3->text();
        int La = strla.toInt();
        QVector<double> x(N), y(N);

        int i=0;
        const double pi = 3.14159265;
        for (double X=a; X<=b; X+=h)
        {
            x[i] = X;                                                    //а здесь должен был бы строиться график интерференции. Но он не строится, вероятнее всего потому что я не могу в координаты
            double delta = sqrt(double(D^2)+x[i]*x[i])-sqrt(double(D^2)+(x[i]+A)*(x[i]+A));
            y[i] = 2*(1/2)*(1+cos(2*pi*delta/La*1e-9));
            i++;
        }

        ui->widget->clearGraphs();
        //Добавляем график в widget
        ui->widget->addGraph();
        //Говорим, что отрисовать нужно график по нашим двум массивам x и y
        ui->widget->graph(0)->setData(x, y);


        ui->widget->xAxis->setLabel("x");
        ui->widget->yAxis->setLabel("E");

        //вычисляем границы по x и y
        ui->widget->xAxis->setRange(a, b);


        double minY = y[0], maxY = y[0];
        for (int i=1; i<N; i++)
        {
            if (y[i]<minY) minY = y[i];
            if (y[i]>maxY) maxY = y[i];
        }
        ui->widget->yAxis->setRange(minY, maxY);


        ui->widget->replot();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString stra = ui->lineEdit->text();
    int A = stra.toInt();
    QString strd = ui->lineEdit_2->text();
    int D = strd.toInt();
    QString strla = ui->lineEdit_3->text();
    int La = strla.toInt();

    double hi = La*(1e-9)*D/A;
    double a = 0;
    double b =  D;
    double h = 0.01;

    int N=(b-a)/h + 2;


    QVector<double> x(N), y1(N), y2(N);

    int i=0;

    // предполагалось что этот кусок должен рисовать направления лучей. Но он рисует что-то очень альтернативное. Я не имею ни малейшего понятия почему
    for (double X=a; X<=b; X+=h)
    {
        x[i] = X;
        y1[i] = (-(D*(A/2))-x[i]*(A/2-hi))/D;
        y2[i] = (-(D*(-A/2))-x[i]*(-A/2-hi))/D;
        i++;
    }

    ui->widget_1->clearGraphs();

    ui->widget_1->addGraph();

    ui->widget_1->graph(0)->setData(x, y1);
    ui->widget_1->addGraph();
    ui->widget_1->graph(1)->setData(x, y2);



    ui->widget_1->xAxis->setRange(0, D);


    double minY = y1[0], maxY = y1[0];
    for (int i=1; i<N; i++)
    {
        if (y1[i]<minY) minY = y1[i];
        if (y1[i]>maxY) maxY = y1[i];
    }
    ui->widget_1->yAxis->setRange(-A, hi);


    ui->widget_1->replot();
}


