#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTcpSocket>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractSocket>
#include <QInputDialog>

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
    void on_btnConnect_clicked();
    void on_btnDisconnect_clicked();
    void on_btnSend_clicked();
    void connected();
    void disconnected();
    void readyRead();
    void error(QAbstractSocket::SocketError socketError);

private:
    Ui::MainWindow *ui;

    QTcpSocket m_socket;
    QStringList m_list;
    QStringListModel m_model;
    QString m_name;
};
#endif // MAINWINDOW_H
