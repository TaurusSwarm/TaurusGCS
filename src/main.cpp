#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFile>
#include <QDebug>
#include "TaurusGCS.h"
#include <QQmlContext>

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    const char *severity;
    switch (type) {
    case QtDebugMsg:
        severity = "Debug: ";
        break;
    case QtInfoMsg:
        severity = "Info: ";
        break;
    case QtWarningMsg:
        severity = "Warning: ";
        break;
    case QtCriticalMsg:
        severity = "Critical: ";
        break;
    case QtFatalMsg:
        severity = "Fatal: ";
        abort();
    default:
        severity = "Unknown: ";
        break;
    }

    fprintf(stderr, "%s%s\n", severity, localMsg.constData());
    fflush(stderr);
}

int main(int argc, char *argv[])
{
    QGuiApplication::setOrganizationName("Taurus");
    QGuiApplication::setOrganizationDomain("taurus.com");
    QGuiApplication::setApplicationName("TaurusGCS");

    TaurusGCS app(argc, argv);

    // Install custom message handler
    qInstallMessageHandler(messageHandler);

    // Get the root context
    QQmlApplicationEngine& engine = app.getEngine();
    QQmlContext* context = engine.rootContext();

    // Set the TaurusGCS instance as a context property BEFORE loading the QML
    context->setContextProperty("taurusGCS", &app);

    engine.load(QUrl(QStringLiteral("qrc:/qml/Main.qml")));

    return app.exec();
}
