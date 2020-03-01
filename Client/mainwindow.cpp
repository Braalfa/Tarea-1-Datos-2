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
/**
 * Mainwindow shown to the user
 * @param parent
 */
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

/**
 * Exit method
 */
MainWindow::~MainWindow()
{
    delete ui;
    end();
}

/**
 * Method to show user a message
 */
void MainWindow::sendMessage(QString header, QString message){
    QMessageBox msgBox;
    msgBox.setText(header);
    msgBox.setInformativeText(message);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();

}
/**
 * On click action for calculate create graph button
 */
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

/**
 * On click action for calculate add edge button
 */
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

/**
 * On click action for calculate button, shows shortest path
 */
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

/**
 * On click action for restart button
 */
void MainWindow::restart(){
    sendStrMessage("restart");
    initiateBtn->setDisabled(false);
    addEdgeBtn->setDisabled(true);
    calculateBtn->setDisabled(true);
}
