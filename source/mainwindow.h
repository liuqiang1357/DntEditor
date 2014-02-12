#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QDataStream>
#include <QFile>
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>
#include <QInputDialog>
#include <QDomDocument>
#include <QXmlStreamReader>
#include <iostream>

using namespace std;

namespace Ui {
class MainWindow;
}

class Biaotou
{
public:
    qint16 lieshu;
    qint32 hangshu;
    void dubiaotou(QDataStream &input);
    void xiebiaotou(QDataStream &output);
    void clear()
    {
        lieshu=0;
        hangshu=0;
    }

};

class Liexinxi
{
public:
    QVector<qint16> liebiaotizishu;
    QVector<QString> liebiaoti;
    QVector<qint8> lieleixing;

    void duliexinxi(QDataStream &input,Biaotou &biaotou,Ui::MainWindow *ui);
    void xieliexinxi(QDataStream &output,Biaotou &biaotou);
    void clear()
    {
        liebiaotizishu.clear();
        liebiaoti.clear();
        lieleixing.clear();
    }
};

class Shujuti
{
public:
    void dushujuti(QDataStream &input,Biaotou &biaotou,Liexinxi &liexinxi,Ui::MainWindow *ui,bool &stopflag);
    void xieshujuti(QDataStream &output,Biaotou &biaotou,Liexinxi &liexinxi,Ui::MainWindow *ui);
};



class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void clear();

    bool jiazaixml();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void pipeibiaoqian();

    void on_pushButton_6_clicked();

    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_action_5_triggered();

    void on_action_6_triggered();

    void on_lineEdit_returnPressed();

    void show_contextmenu();

    void show_contextmenuh();

    void show_contextmenuv();

    void on_action_edit_triggered();

    void on_action_addrow_triggered();

    void on_action_deleterow_triggered();

    void on_action_addcolumn_triggered();

    void on_action_deletecolumn_triggered();

private:
    Ui::MainWindow *ui;

    QMenu * cmenu;

    QMenu * cmenuh;

    QMenu * cmenuv;

    QString fileNameOpenedDir;

    QString fileNameSavedDir;

    QString programDir;

    class Biaotou biaotou;

    class Liexinxi liexinxi;

    class Shujuti shujuti;

    QLabel *label1 ;

    QDomDocument *dom;

    QVector<int> suoyin;

    bool stopflag;

    bool yunxing;

    bool jiazai;

    bool opened;
};

#endif // MAINWINDOW_H
