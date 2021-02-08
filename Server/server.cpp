#include "server.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{

}

int Server::count()
{
    return m_list.count();
}

void Server::close()
{
    foreach (QTcpSocket *socket, m_list)
    {
        socket->close();
    }
    qDeleteAll(m_list);
    m_list.clear();

    emit changed();

    QTcpServer::close();
}

void Server::disconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if(!socket)return;

    m_list.removeAll(socket);
    disconnect(socket,&QTcpSocket::disconnected,this,&Server::disconnected);
    disconnect(socket,&QTcpSocket::readyRead,this,&Server::readyRead);
    socket->deleteLater();
    //delete socket;

    emit changed();
}

void Server::readyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if(!socket)return;

    QByteArray data = socket->readAll();
    foreach(QTcpSocket *socket, m_list)
    {
        socket->write(data);
    }
}

void Server::incomingConnection(qintptr handle)
{
    QTcpSocket *socket = new QTcpSocket();
    socket->setSocketDescriptor(handle);

    if(!socket->waitForConnected(3000))
    {
        delete socket;
        return;
    }

    m_list.append(socket);
    connect(socket,&QTcpSocket::disconnected,this,&Server::disconnected);
    connect(socket,&QTcpSocket::readyRead,this,&Server::readyRead);

    emit changed();
    socket->write(m_message.toLatin1());

}

QString Server::message() const
{
    return m_message;
}

void Server::setMessage(const QString &message)
{
    m_message = message;
}
