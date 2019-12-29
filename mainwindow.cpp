#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      e1(r())
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));
    timer->start(50);
    ui->setupUi(this);
    this->setCentralWidget(ui->verticalLayoutWidget);
    ui->pushButton->setText("看看抽到谁");
    ui->label->setText("尚未选择人名单");
    this->setWindowTitle("抽号器");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "关于", "奇奇怪怪的抽号器\n作者:王万霖\ndgideas@outlook.com\n\n简洁得不像2019年写的软件= =");
}

void MainWindow::update()
{
    if (this->isRunning){
        this->rndNumber = this->uniform(e1);
        ui->label->setText(this->nameList[this->rndNumber]);
    }
    return;
}

void MainWindow::on_pushButton_clicked()
{
    if (!this->rndMaxSize){
        QMessageBox::information(this, "提示", "尚未加载人名单，无法抽号");
        return;
    }
    if (isRunning){
        isRunning = false;
        ui->pushButton->setText("看看抽到谁");
    }
    else
    {
        isRunning = true;
        ui->pushButton->setText("停！");
    }
}

void MainWindow::on_actionLoad_Name_List_triggered()
{
    this->fileName = QFileDialog::getOpenFileName();
    ui->label->setText(this->fileName);
    QFile fileHandle(this->fileName);

    if (!fileHandle.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::critical(this, "警告", "无法打开给定的文件:" + fileHandle.errorString());
    }

    QTextStream in(&fileHandle);
    in.setCodec(QTextCodec::codecForName("utf-8"));
    this->nameList.clear();
    while (!in.atEnd()){
        QString line = in.readLine();
        if (line != "" && line != "\r"){
            this->nameList.push_back(line);
        }
    }
    this->rndMaxSize = this->nameList.size();
    this->uniform = uniform_int_distribution<int>(0, this->rndMaxSize-1);
    ui->label->setText("共有" + QString::number(this->rndMaxSize) + "人");
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}
