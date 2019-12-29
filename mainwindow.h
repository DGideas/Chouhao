#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QTimer>
#include <QTextStream>
#include <QTextCodec>
#include <vector>
using std::vector;
#include <random>
using std::random_device;
using std::default_random_engine;
using std::uniform_int_distribution;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAbout_triggered();
    void update();

    void on_pushButton_clicked();

    void on_actionLoad_Name_List_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    bool isRunning = false;
    int rndNumber = 0;
    int rndMaxSize = 0;
    QString fileName = "";
    vector<QString> nameList;
    random_device r;
    default_random_engine e1;
    uniform_int_distribution<int> uniform;
};
#endif // MAINWINDOW_H
