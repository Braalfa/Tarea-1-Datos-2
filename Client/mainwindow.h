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
    void askPath();
    void addEdge();
    void firstClick();
    void sendMessage(QString header,QString message);
    void restart();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
