#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFile>
#include <QDebug>

#include "Core/connection.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/Main.qml")));

    Connection conn = Connection();
    conn.connect();

    return app.exec();
}
