#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "xlsxdocument.h"

void Biaotou:: dubiaotou(QDataStream &input)
{
    input>>hangshu>>lieshu>>hangshu;
}

void Liexinxi:: duliexinxi(QDataStream &input,Biaotou &biaotou,Ui::MainWindow *ui)
{
    qint16 liebiaotizishu1;
    char liebiaoti1[4096];
    qint8 lieleixing1;
    int lieshu1=biaotou.lieshu;
    for(int i=0;i<lieshu1;i++)
    {
        input>>liebiaotizishu1;
        input.readRawData(liebiaoti1,int(liebiaotizishu1));
        liebiaoti1[liebiaotizishu1]='\0';
        input>>lieleixing1;
        liebiaotizishu.append(liebiaotizishu1);
        liebiaoti.append(liebiaoti1);
        lieleixing.append(lieleixing1);
    }
    ui->tableWidget->setColumnCount(biaotou.lieshu+1);
    ui->tableWidget->setRowCount(biaotou.hangshu);
    QList<QString> HorizontalHeaderLabels=liebiaoti.toList();
    HorizontalHeaderLabels.insert(0,QObject::tr("_nRow"));
    ui->tableWidget->setHorizontalHeaderLabels(HorizontalHeaderLabels);
    ui->tableWidget->resizeColumnsToContents();
    qApp->processEvents ();

}


void Shujuti::dushujuti(QDataStream &input,Biaotou &biaotou,Liexinxi &liexinxi,Ui::MainWindow *ui,bool &stopflag)
{
    qint32 geshi0;
    char geshi1[4096];
    qint16 tmp1;
    qint32 geshi2;
    qint32 geshi3;
    float geshi4;
    float geshi5;
    QTableWidgetItem *tmp2;
    int lieshu1=biaotou.lieshu;
    int hangshu1=biaotou.hangshu;
    QTableWidget*tableWidget1=ui->tableWidget;
    QVector<qint8>lieleixing1=liexinxi.lieleixing;
    ui->statusBar->showMessage(QObject::tr("正在载入文件."),600000);
    for (int i=0;i<hangshu1;i++)
    {
        if (i==50)
        {
            ui->tableWidget->resizeColumnsToContents();
            qApp->processEvents ();
        }
        else if ((i+1)%1000==0)
        {
            ui->statusBar->showMessage(QObject::tr("正在载入文件 ")+QString::number(int(double(i)*100/double(hangshu1)))+"%",600000);
            if (stopflag)
            {
                ui->statusBar->showMessage(QObject::tr("停止载入文件."),10000);
                return;
            }
            qApp->processEvents ();
        }

        input>>geshi0;
        tmp2=new QTableWidgetItem(QString::number(geshi0));
        tmp2->setTextAlignment(Qt::AlignRight);
        tableWidget1->setItem(i,0,tmp2);
        for(int j=0;j<lieshu1;j++)
        {
            if (lieleixing1.value(j)==1 )
            {
                input>>tmp1;
                input.readRawData(geshi1,int(tmp1));
                geshi1[tmp1]='\0';
                tmp2=new QTableWidgetItem(geshi1);
                tmp2->setTextAlignment(Qt::AlignLeft);
                tableWidget1->setItem(i,j+1,tmp2);
            }
            else if (lieleixing1.value(j)==2 )
            {
                input>>geshi2;
                tmp2=new QTableWidgetItem(QString::number(geshi2));
                tmp2->setTextAlignment(Qt::AlignRight);
                tableWidget1->setItem(i,j+1,tmp2);

            }
            else if (lieleixing1.value(j)==3 )
            {
                input>>geshi3;
                tmp2=new QTableWidgetItem(QString::number(geshi3));
                tmp2->setTextAlignment(Qt::AlignRight);
                tableWidget1->setItem(i,j+1,tmp2);
            }
            else if (lieleixing1.value(j)==4 )
            {
                input>>geshi4;
                tmp2=new QTableWidgetItem(QString::number(geshi4));
                tmp2->setTextAlignment(Qt::AlignRight);
                tableWidget1->setItem(i,j+1,tmp2);
            }
            else if (lieleixing1.value(j)==5 )
            {
                input>>geshi5;
                tmp2=new QTableWidgetItem(QString::number(geshi5));
                tmp2->setTextAlignment(Qt::AlignRight);
                tableWidget1->setItem(i,j+1,tmp2);
            }
            else
            {
                qDebug((QObject::tr("find new type:")+liexinxi.liebiaoti.value(j)+QObject::tr(" lieshu:")+QString::number(j)+QObject::tr(" leixing:")+QString::number(liexinxi.lieleixing.value(j))).toStdString().c_str());
            }
        }
    }
    ui->tableWidget->resizeColumnsToContents();
    ui->statusBar->showMessage(QObject::tr("载入文件成功."),10000);
}

bool MainWindow::jiazaixml()
{
    statusBar()->showMessage(tr("正在加载XML文件."),5000);
    qApp->processEvents ();

    programDir=qApp->arguments().value(0);
    QString xmlFileName=QFileInfo(programDir).absolutePath()+"/uistring.xml";
    QFile xmlFile(xmlFileName);
    if (!xmlFile.open(QIODevice::ReadOnly)){
        statusBar()->showMessage(tr("XML文件载入失败."),5000);
        jiazai=false;
        return false;
    }
    dom = new QDomDocument();
    QString errorStr;
    int errorLine;
    int errorColumn;
    if(!dom->setContent(&xmlFile,&errorStr,&errorLine,&errorColumn)){
        xmlFile.close();
        jiazai=false;
        statusBar()->showMessage(tr("XML文件载入失败."),5000);
        return false;
    }
    QDomNodeList messagelist=dom->elementsByTagName("message");
    for(int i=0;i<messagelist.count();i++)
    {
        suoyin.append(messagelist.at(i).toElement().attribute("mid").toInt());

    }
    xmlFile.close();

    jiazai=true;
    statusBar()->showMessage(tr("XML文件载入成功."),3000);
    return true;
}


void MainWindow::pipeibiaoqian()
{
    int _NameID=0;
    int _NameIDParam=0;

    QTableWidget*tableWidget1=ui->tableWidget;
    int lieshu1=tableWidget1->columnCount();;
    int hangshu1=tableWidget1->rowCount();

    int tmp1;
    QString tmp2;
    QStringList tmp3;
    int tmp4;

    for(int i=0;i<lieshu1;i++)
    {
        if (tableWidget1->horizontalHeaderItem(i)->text()==QString("_NameID"))
        {
            _NameID=i;
        }
        if (tableWidget1->horizontalHeaderItem(i)->text()==QString("_NameIDParam"))
        {
            _NameIDParam=i;
        }

    }

    if (_NameID!=0)
    {
        if (!jiazai)
        {
            if(!jiazaixml())
            {
                return;
            }
        }
        QDomNodeList messagelist=dom->elementsByTagName("message");
        statusBar()->showMessage(tr("正在匹配标签."),10000);
        qApp->processEvents ();
        for (int i=0;i<hangshu1;i++)
        {
            if (i%100==0)
            {
                if (stopflag)
                {
                    statusBar()->showMessage(tr("停止匹配标签."),10000);
                    return;
                }
                qApp->processEvents ();
            }


            tmp1=suoyin.indexOf(tableWidget1->item(i,_NameID)->text().toInt());
            if(tmp1>=0)
            {
                tmp2= messagelist.at(tmp1).toElement().text();
                if (tmp2.length()<30){
                    if (tmp2.contains("{0}"))
                    {
                        tmp3=tableWidget1->item(i,_NameIDParam)->text().split(',');
                        for(int j=0 ;j<30;j++)
                        {
                            if(tmp2.contains("{"+QString::number(j)+"}"))
                            {
                                if (tmp3.value(j).contains('{'))
                                {
                                    tmp4=suoyin.indexOf(tmp3.value(j).remove('{').remove('}').toInt());
                                    if (tmp4>=0)
                                    {
                                        tmp2.replace("{"+QString::number(j)+"}",messagelist.at(tmp4).toElement().text());
                                    }
                                }
                                else
                                {
                                    tmp2.replace("{"+QString::number(j)+"}",tmp3.value(j));
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                        tableWidget1->setVerticalHeaderItem(i,new QTableWidgetItem(tmp2));
                    }
                    else
                    {
                        tableWidget1->setVerticalHeaderItem(i,new QTableWidgetItem(tmp2));
                    }
                }
            }
        }
        ui->tableWidget->resizeColumnsToContents();
        statusBar()->showMessage(tr("匹配标签成功."),10000);
    }
}

void Biaotou::xiebiaotou(QDataStream &output)
{
    qint32 tmp=0;
    output<<tmp<<lieshu<<hangshu;
}

void Liexinxi:: xieliexinxi(QDataStream &output,Biaotou &biaotou)
{
    qint16 liebiaotizishu1;
    const char *liebiaoti1;
    qint8 lieleixing1;
    for(int i=0;i<biaotou.lieshu;i++)
    {
        liebiaotizishu1=liebiaotizishu.value(i);
        liebiaoti1=liebiaoti.value(i).toStdString().c_str();
        lieleixing1=lieleixing.value(i) ;
        output<<liebiaotizishu1;
        output.writeRawData(liebiaoti1,int(liebiaotizishu1));
        output<<lieleixing1;
    }
}

void Shujuti::xieshujuti(QDataStream &output,Biaotou &biaotou,Liexinxi &liexinxi,Ui::MainWindow *ui)
{
    qint32 geshi0;
    const char *geshi1=new char;
    qint16 tmp1;
    qint32 geshi2;
    qint32 geshi3;
    float geshi4;
    float geshi5;
    for (int i=0;i<biaotou.hangshu;i++)
    {
        if(ui->tableWidget->item(i,0)!=NULL)
        {
            geshi0=ui->tableWidget->item(i,0)->text().toInt();
        }
        else
        {
            geshi0=0;
        }
        output<<geshi0;
        for(int j=0;j<biaotou.lieshu;j++)
        {
            if (liexinxi.lieleixing.value(j)==1 )
            {
                if(ui->tableWidget->item(i,j+1)!=NULL)
                {
                    tmp1=ui->tableWidget->item(i,j+1)->text().length();
                    geshi1=ui->tableWidget->item(i,j+1)->text().toStdString().c_str();
                }
                else
                {
                    tmp1=0;
                }
                output<<tmp1;
                output.writeRawData(geshi1,int(tmp1));
            }
            else if (liexinxi.lieleixing.value(j)==2 )
            {
                if(ui->tableWidget->item(i,j+1)!=NULL)
                {
                    geshi2=ui->tableWidget->item(i,j+1)->text().toInt();
                }
                else
                {
                    geshi2=0;
                }
                output<<geshi2;
            }
            else if (liexinxi.lieleixing.value(j)==3 )
            {
                if(ui->tableWidget->item(i,j+1)!=NULL)
                {
                    geshi3=ui->tableWidget->item(i,j+1)->text().toInt();
                }
                else
                {
                    geshi3=0;
                }
                output<<geshi3;
            }
            else if (liexinxi.lieleixing.value(j)==4 )
            {
                if(ui->tableWidget->item(i,j+1)!=NULL)
                {
                    geshi4=ui->tableWidget->item(i,j+1)->text().toFloat();
                }
                else
                {
                    geshi4=0;
                }
                output<<geshi4;
            }
            else if (liexinxi.lieleixing.value(j)==5 )
            {
                if(ui->tableWidget->item(i,j+1)!=NULL)
                {
                    geshi5=ui->tableWidget->item(i,j+1)->text().toFloat();
                }
                else
                {
                    geshi5=0;
                }
                output<<geshi5;
            }
            else
            {
                qDebug((QObject::tr("find new type:")+liexinxi.liebiaoti.value(j)+QObject::tr(" lieshu:")+QString::number(j)+QObject::tr(" leixing:")+QString::number(liexinxi.lieleixing.value(j))).toStdString().c_str());
            }
        }
    }
    output<<qint32(0x45485405)<<qint16(0x444E);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    label1 = new QLabel;
    statusBar()->addPermanentWidget(label1);
    suoyin.clear();
    yunxing=false;
    jiazai =false;
    stopflag=false;

    if (qApp->arguments().value(1)!="")
    {
        opened=false;
        this->show();
        on_pushButton_clicked();
    }
    else
    {
        opened=true;
    }

}

void MainWindow::clear()
{
    ui->tableWidget->clear();
    stopflag=false;
    this->biaotou.clear();
    this->liexinxi.clear();
}
MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_pushButton_clicked()
{
    if(yunxing)
    {
        return;
    }
    else
    {
        yunxing= true;
    }
    if (opened)
    {
        QString dir=QFileInfo(fileNameOpenedDir).absolutePath();
        fileNameOpenedDir = QFileDialog::getOpenFileName(this,"",dir,"Dnt Files(*.dnt)");
    }
    else
    {
        fileNameOpenedDir=qApp->arguments().value(1);
        opened=true;
    }
    QFile fileNameOpened (fileNameOpenedDir);
    QString filename=QFileInfo(fileNameOpenedDir).fileName();
    if (!fileNameOpened.open(QIODevice::ReadOnly)){
        statusBar()->showMessage(tr("文件打开失败."),10000);
        yunxing= false;
        return;
    }
    else
    {
        this->clear();
    }
    QDataStream input(&fileNameOpened);
    input.setByteOrder(QDataStream::LittleEndian);
    input.setFloatingPointPrecision(QDataStream::SinglePrecision);
    this->biaotou.dubiaotou(input);
    label1->setText(filename+tr("     ")+QString::number(biaotou.hangshu)+tr("x")+QString::number(biaotou.lieshu)+tr("   "));
    this->liexinxi.duliexinxi(input,this->biaotou,this->ui);
    this->shujuti.dushujuti(input,this->biaotou,this->liexinxi,this->ui,stopflag);
    this->pipeibiaoqian();
    fileNameOpened.close();
    yunxing= false;
}

void MainWindow::on_pushButton_2_clicked()
{

    QTableWidget*tableWidget1=ui->tableWidget;
    int hangshu1=tableWidget1->rowCount();
    QString lookfor=ui->lineEdit->text();
    QList<QTableWidgetItem *>selects = tableWidget1->selectedItems();

    if(selects.count()==1)
    {
        int i;
        int curColumn = selects.value(0)->column();
        if (lookfor.contains(">>"))
        {
            lookfor.remove(">>");
            i=0;
        }
        else
        {
            i=selects.value(0)->row()+1;
        }
        for(;i<hangshu1;i++)
        {
            if(tableWidget1->item(i,curColumn)!=NULL)
            {
                if (tableWidget1->item(i,curColumn)->text().contains(lookfor))
                {
                    for (int j=0;j<selects.count();j++)
                    {
                        selects.value(j)->setSelected(false);
                    }
                    tableWidget1->item(i,curColumn)->setSelected(true);
                    tableWidget1->scrollToItem(tableWidget1->item(i,curColumn));
                    break;
                }
            }

        }
    }
    else
    {
        int i;
        if (lookfor.contains(">>"))
        {
            lookfor.remove(">>");
            i=0;
        }
        else
        {
            i=tableWidget1->currentRow()+1;
        }
        for(;i<hangshu1;i++)
        {
            if (i==lookfor.toInt()-1)
            {
                tableWidget1->selectRow(i);
                break;
            }
            if(tableWidget1->verticalHeaderItem(i)!=NULL)
            {
                if(tableWidget1->verticalHeaderItem(i)->text().contains(lookfor))
                {
                    tableWidget1->selectRow(i);
                    break;
                }
            }
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    fileNameSavedDir=fileNameOpenedDir;
    QFile fileNameSaved (fileNameSavedDir);
    if((!fileNameSaved.open(QIODevice::WriteOnly))){
        statusBar()->showMessage(tr("文件保存失败."),10000);
        return;
    }
    else
    {
        statusBar()->showMessage(tr("文件正在保存."),600000);
    }
    QDataStream output(&fileNameSaved);
    output.setByteOrder(QDataStream::LittleEndian);
    output.setFloatingPointPrecision(QDataStream::SinglePrecision);
    this->biaotou.xiebiaotou(output);
    this->liexinxi.xieliexinxi(output,this->biaotou);
    this->shujuti.xieshujuti(output,this->biaotou,this->liexinxi,this->ui);
    statusBar()->showMessage(tr("文件保存成功."),10000);
    fileNameSaved.close();
}

void MainWindow::on_pushButton_4_clicked()
{
    QString dir=QFileInfo(fileNameOpenedDir).absolutePath();
    fileNameSavedDir=QFileDialog::getSaveFileName(this,"",dir,"Dnt Files(*.dnt)");
    QFile fileNameSaved (fileNameSavedDir);
    if((!fileNameSaved.open(QIODevice::WriteOnly))){
        statusBar()->showMessage(tr("文件保存失败."),10000);
        return;
    }
    else
    {
        statusBar()->showMessage(tr("文件正在保存..."),600000);
    }
    QDataStream output(&fileNameSaved);
    output.setByteOrder(QDataStream::LittleEndian);
    output.setFloatingPointPrecision(QDataStream::SinglePrecision);
    this->biaotou.xiebiaotou(output);
    this->liexinxi.xieliexinxi(output,this->biaotou);
    this->shujuti.xieshujuti(output,this->biaotou,this->liexinxi,this->ui);
    statusBar()->showMessage(tr("文件保存成功."),10000);
    fileNameSaved.close();
}


void MainWindow::on_pushButton_5_clicked()
{
    stopflag=true;
}



void MainWindow::on_pushButton_6_clicked()
{
    if(yunxing)
    {
        return;
    }
    else
    {
        yunxing= true;
    }
    QXlsx::Document xlsx;
    QTableWidget*tableWidget1=ui->tableWidget;
    int hangshu1=tableWidget1->rowCount();
    int lieshu1= tableWidget1->columnCount();


    xlsx.write(1,1,"");
    for(int j=0;j<lieshu1;j++)
    {
        if(tableWidget1->horizontalHeaderItem(j)!=NULL)
        {
            xlsx.write(1,j+2,tableWidget1->horizontalHeaderItem(j)->text());
        }
        else
        {
            xlsx.write(1,j+2,QString::number(j+2));
        }
    }
    for (int i=0;i<hangshu1;i++)
    {
        if (i%1000==0)
        {
            ui->statusBar->showMessage(QObject::tr("正在生成xlsx ")+QString::number(int(double(i)*100/double(hangshu1)))+"%",600000);
            qApp->processEvents ();
        }
        if(tableWidget1->verticalHeaderItem(i)!=NULL)
        {
            xlsx.write(i+2,1,tableWidget1->verticalHeaderItem(i)->text());
        }
        else
        {
            xlsx.write(i+2,1,QString::number(i+1));
        }

        if(tableWidget1->item(i,0)!=NULL)
        {
            xlsx.write(i+2,2,tableWidget1->item(i,0)->text().toInt());
        }
        else
        {
            xlsx.write(i+2,2,"");
        }
        for(int j=1;j<lieshu1;j++)
        {
            if(tableWidget1->item(i,j)!=NULL)
            {
                if(liexinxi.lieleixing.value(j-1)==1)
                {
                    xlsx.write(i+2,j+2,tableWidget1->item(i,j)->text());
                }
                else if(liexinxi.lieleixing.value(j-1)<=3)
                {
                    xlsx.write(i+2,j+2,tableWidget1->item(i,j)->text().toInt());
                }
                else if(liexinxi.lieleixing.value(j-1)<=5)
                {
                    xlsx.write(i+2,j+2,tableWidget1->item(i,j)->text().toDouble());
                }
            }
            else
            {
                xlsx.write(i+2,j+2,"");
            }
        }
    }

    QString saveDir=QFileInfo(fileNameOpenedDir).absolutePath()+"\\"+QFileInfo(fileNameOpenedDir).baseName()+".xlsx";
    statusBar()->showMessage(tr("正在保存xlsx..."),10000);
    xlsx.saveAs(saveDir);
    statusBar()->showMessage(tr("成功导出xlsx."),10000);
    yunxing= false;

}

void MainWindow::on_pushButton_7_clicked()
{
    QString filename=QFileInfo(fileNameOpenedDir).fileName();
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
    biaotou.hangshu=ui->tableWidget->rowCount();
    label1->setText(filename+tr("     ")+QString::number(biaotou.hangshu)+tr("x")+QString::number(biaotou.lieshu)+tr("   "));
}
void MainWindow::on_pushButton_8_clicked()
{
    QString filename=QFileInfo(fileNameOpenedDir).fileName();
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
    biaotou.hangshu=ui->tableWidget->rowCount();
    label1->setText(filename+tr("     ")+QString::number(biaotou.hangshu)+tr("x")+QString::number(biaotou.lieshu)+tr("   "));
}

void MainWindow::on_action_triggered()
{
    on_pushButton_clicked();
}

void MainWindow::on_action_2_triggered()
{
    on_pushButton_3_clicked();
}

void MainWindow::on_action_3_triggered()
{
    on_pushButton_4_clicked();
}

void MainWindow::on_action_5_triggered()
{
    exit(0);
}

void MainWindow::on_action_6_triggered()
{
    QMessageBox::information(0,tr("关于"), tr("\n\"DntEditor v2.0\" -20130120\n"
                                            "---------------------\n"
                                            "Author:xiaot\tEmail:liuqiang1357@163.com\t\n"
                                            "Qt:5.0.2\t\tmingw:4.8.0\n"
                                            "on Microsoft Windows 7 (32-bit)\n"));
}


void MainWindow::on_lineEdit_returnPressed()
{
    on_pushButton_2_clicked();
}
