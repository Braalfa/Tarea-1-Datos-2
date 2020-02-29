#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QApplication>


#include <QMessageBox>
#include <QInputDialog>
#include <string>
#include <QIcon>


QLineEdit* nodesTxt;
QLineEdit* sourceTxt;
QLineEdit* destinyTxt;
QLineEdit* weigthTxt;
QLineEdit* startTxt;
QLineEdit* endTxt;

QPushButton* addEdgeBtn;
QPushButton* initiateBtn;
QPushButton* calculateBtn;
QPushButton* restartBtn;


int nodes;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initiateClient();

    nodesTxt = ui->nodesTxt;
    sourceTxt= ui->sourceTxt;
    destinyTxt=ui->destinyTxt;
    weigthTxt=ui->weigthTxt;
    startTxt=ui->startTxt;
    endTxt=ui->endTxt;
    addEdgeBtn=ui->addEdgeBtn;
    initiateBtn=ui->initiateBtn;
    calculateBtn=ui->calculateBtn;
    restartBtn=ui->restartBtn;

    addEdgeBtn->setDisabled(true);
    calculateBtn->setDisabled(true);

    connect(ui->initiateBtn, SIGNAL (clicked()),this, SLOT (firstClick()));
    connect(ui->addEdgeBtn, SIGNAL (clicked()),this, SLOT (addEdge()));
    connect(ui->calculateBtn, SIGNAL (clicked()),this, SLOT (askPath()));
    connect(ui->restartBtn, SIGNAL (clicked()),this, SLOT (restart()));

}

MainWindow::~MainWindow()
{
    delete ui;
    end();
}

void MainWindow::sendMessage(QString header, QString message){
    QMessageBox msgBox;
    msgBox.setText(header);
    msgBox.setInformativeText(message);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();

}

void MainWindow::firstClick(){
    QString text= nodesTxt->text();
    createGraph(text.toStdString());
    string state = askAnswer();
    if(state=="ok"){
        initiateBtn->setDisabled(true);
        addEdgeBtn->setDisabled(false);
    }else{
        sendMessage("Error", "No valid input");
    }

}

void MainWindow::addEdge(){
    QString src=sourceTxt->text();
    QString end=destinyTxt->text();
    QString weigth=weigthTxt->text();
    createEdge(src.toStdString(),end.toStdString(), weigth.toStdString());
    string state = askAnswer();
    if(state=="ok"){
        calculateBtn->setDisabled(false);
    }else{
        sendMessage("Error", "No valid input");
    }
}

void MainWindow::askPath(){
    QString src=startTxt->text();
    QString dest=endTxt->text();

    QString path= QString::fromStdString(getDijkstra(src.toStdString(), dest.toStdString()));
    if(path=="error"){
        sendMessage("Error","No valid input");
    }else{
        sendMessage("The path is", path);
        addEdgeBtn->setDisabled(true);
    }

}

void MainWindow::restart(){
    sendStrMessage("restart");
    initiateBtn->setDisabled(false);
    addEdgeBtn->setDisabled(true);
    calculateBtn->setDisabled(true);
}
