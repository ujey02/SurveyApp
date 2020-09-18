#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "time.h"
#include <cstdlib>
#include <algorithm>
#include <QtDebug>
#include <QStringList>
#include <QFile>

QButtonGroup* rbGroup = new QButtonGroup();
QButtonGroup* rbGroup2 = new QButtonGroup();
QStringList part1Comb = QStringList();
QStringList part2Comb = QStringList();
QString path;
QString part;
QString frameNum;
QString pair;
QString method;
QString methodPair;
QStringList methods;
QString userName;

int numShot1 = 168;
int numShot2 = 168;

clock_t start,end;

int count = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    path = qApp->applicationDirPath() + "/data/";

    srand(time(0));

    rbGroup->addButton((ui->rb1));
    rbGroup->addButton((ui->rb2));
    rbGroup->addButton((ui->rb3));
    rbGroup->addButton((ui->rb4));
    rbGroup->addButton((ui->rb5));

    rbGroup2->addButton((ui->rb_left));
    rbGroup2->addButton((ui->rb_right));

    QStringList shotNum = QString("01_02_03_04_05_06_07_08_09_10_11_12_13_14").split("_");
    QStringList targetPairs = QString("T1_T2_T3_T4").split("_");
    QStringList methodTypes = QString("M1_M2_M3").split("_");
    QStringList methodPairs = QString("M1:M2_M1:M3_M2:M3").split("_");

    for (int i =0; i<4; i++)
    {
        for (int j =0; j<3; j++)
        {
            for (int k =0; k<14; k++)
            {
                QString name1 =  targetPairs.at(i) + "_" + shotNum.at(k) + "_" + methodTypes.at(j);
                part1Comb << name1;

                QString name2 = targetPairs.at(i) + "_" + shotNum.at(k) + "_" + methodPairs.at(j);
                part2Comb << name2;
            }
        }
    }
    std::random_shuffle(part1Comb.begin(),part1Comb.end());
    std::random_shuffle(part2Comb.begin(),part2Comb.end());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadNewImage(QString name)
{
    QStringList names = name.split("_");
    frameNum = names.at(1);
    pair = names.at(0);
    method = names.at(2);

    QString refFile = path+"ref/"+frameNum+".jpg";
    QString targetFile = path + pair + "/" + method + "/" + frameNum + ".jpg";

    QImage imageRef;
    bool valid = imageRef.load(refFile);
    if(valid)
    {
        ui->refImage->setPixmap(QPixmap::fromImage(imageRef.scaled(320,180)));
    }
    else
    {
        qDebug() << "Error";
    }

    QImage imageTarget;
    bool valid2 = imageTarget.load(targetFile);
    if(valid2)
    {
        ui->targetImage->setPixmap(QPixmap::fromImage(imageTarget.scaled(320,180)));
    }
    else
    {
        qDebug() << "Error";
    }
}

void MainWindow::loadNewImages(QString name)
{
    QStringList names = name.split("_");
    frameNum = names.at(1);
    pair = names.at(0);
    methodPair = names.at(2);
    methods = methodPair.split(":");
    std::random_shuffle(methods.begin(),methods.end());

    QString refFile = path+"ref/"+frameNum+".jpg";
    QString targetFile1 = path + pair + "/" + methods.at(0) + "/" + frameNum + ".jpg";
    QString targetFile2 = path + pair + "/" + methods.at(1) + "/" + frameNum + ".jpg";

    QImage imageRef;
    bool valid = imageRef.load(refFile);
    if(valid)
    {
        ui->refImage_2->setPixmap(QPixmap::fromImage(imageRef.scaled(320,180)));
    }
    else
    {
        qDebug() << "Error";
    }

    QImage imageTarget1;
    bool valid2 = imageTarget1.load(targetFile1);
    if(valid2)
    {
        ui->targetImage1->setPixmap(QPixmap::fromImage(imageTarget1.scaled(320,180)));
    }
    else
    {
        qDebug() << "Error";
    }

    QImage imageTarget2;
    bool valid3 = imageTarget2.load(targetFile2);
    if(valid3)
    {
        ui->targetImage2->setPixmap(QPixmap::fromImage(imageTarget2.scaled(320,180)));
    }
    else
    {
        qDebug() << "Error";
    }
}


void MainWindow::on_pushButton_clicked()
{
    int val = 0;
    if (ui->rb1->isChecked()) val = 1;
    if (ui->rb2->isChecked()) val = 2;
    if (ui->rb3->isChecked()) val = 3;
    if (ui->rb4->isChecked()) val = 4;
    if (ui->rb5->isChecked()) val = 5;

    if (val == 0){
        qDebug() << "cannot proceed";
    }
    else
    {
        qDebug() << val;
        QFile file(path + userName + "_Part1_result.txt");
        file.open(QIODevice::WriteOnly|QIODevice::Append|QIODevice::Text);
        QTextStream out(&file);
        // part,character pair type, frame num, method, value
        out << part << "," << pair << "," << frameNum <<"," << method << "," << val << "\n";

        if (count == numShot1-1)
        {
            end = clock();
            out << (double)(end-start) << "\n";
            ui->stackedWidget->setCurrentIndex(2);
        }
        else
        {
            rbGroup->setExclusive(false);
            rbGroup->checkedButton()->setChecked(false);
            rbGroup->setExclusive(true);
            count++;
            loadNewImage(part1Comb.at(count));
            ui->count1->setText(QString::number(count+1)+QString("/168"));
        }
        file.close();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    userName = ui->nameInput->text();
    if (userName == "") userName = "Anonymous";
    qDebug() << "Part 1 Started";
    part = "part1";
    count = 0;
    QFile file(path + userName + "_Part1_result.txt");
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&file);
    out << "Part 1 started\n";
    file.close();

    start = clock();
    ui->stackedWidget->setCurrentIndex(1);
    loadNewImage(part1Comb.at(count));
    ui->count1->setText(QString::number(count+1)+QString("/168"));
}

void MainWindow::on_pushButton_4_clicked()
{
    qDebug() << "Part 2 Started";
    part = "part2";
    count = 0;
    QFile file(path + userName + "_Part2_result.txt");
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&file);
    out << "Part 2 started\n";
    file.close();

    start = clock();
    ui->stackedWidget->setCurrentIndex(3);
    loadNewImages(part2Comb.at(count));
     ui->count2->setText(QString::number(count+1)+QString("/168"));
}

//part2 next button
void MainWindow::on_pushButton_2_clicked()
{
    QString val = "None";
    if (ui->rb_left->isChecked()) val = methods.at(0);
    if (ui->rb_right->isChecked()) val = methods.at(1);

    if (val == "None"){
        qDebug() << "cannot proceed";
    }
    else
    {
        qDebug() << val;
        QFile file(path + userName + "_Part2_result.txt");
        file.open(QIODevice::WriteOnly|QIODevice::Append|QIODevice::Text);
        QTextStream out(&file);
        // part,character pair type, frame num, method, value
        out << part << "," << pair << "," << frameNum <<"," << methodPair << "," << val << "\n";
        if (count == numShot2-1)
        {
            end = clock();
            out << (double)(end-start) << "\n";
            ui->stackedWidget->setCurrentIndex(4);
        }
        else
        {
            rbGroup2->setExclusive(false);
            rbGroup2->checkedButton()->setChecked(false);
            rbGroup2->setExclusive(true);
            count++;
            loadNewImages(part2Comb.at(count));
            ui->count2->setText(QString::number(count+1)+QString("/168"));
        }
        file.close();
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    qDebug() << "Done";
    this->close();
}
