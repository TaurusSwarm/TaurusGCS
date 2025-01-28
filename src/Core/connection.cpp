#include "connection.hpp"

#include <QDebug>

#define SYSTEM_ID       1
#define COMP_ID         1
#define HEARTBEAT       1

using namespace mavsdk;

Connection::Connection(QObject *parent)
    : QObject{parent}
{

}

void Connection::connect()
{
    _mavsdk = new Mavsdk(Mavsdk::Configuration(SYSTEM_ID, COMP_ID, HEARTBEAT));
    ConnectionResult connection_result;
    connection_result = _mavsdk->add_any_connection("path");

    if (connection_result == ConnectionResult::Success) {
        qInfo() << "[ Info] -- Adding MAVSDK connection successful";
    } else {
        qDebug() << "[Error] -- Adding MAVSDK connection failed";
    }
}