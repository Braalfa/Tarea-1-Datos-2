#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <QMainWindow>

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
    /**
    * On click action for calculate button, shows shortest path
    */
    void askPath();
    /**
    * On click action for calculate add edge button
    */
    void addEdge();
    /**
    * On click action for calculate create graph button
    */
    void firstClick();
    /**
    * Method to show user a message
    */
    void sendMessage(QString header,QString message);
    /**
    * On click action for restart button
    */
    void restart();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
