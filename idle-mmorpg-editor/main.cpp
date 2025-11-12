#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "RegisterType.h"

int main( int argc, char* argv[] ) {
    QGuiApplication app( argc, argv );

    QQmlApplicationEngine engine;

    RegisterType::registerAll( engine );

    QObject::connect( &engine, &QQmlApplicationEngine::objectCreationFailed, &app, []() {
        QCoreApplication::exit( -1 );
    }, Qt::QueuedConnection );

    engine.loadFromModule( "editor", "Main" );

    return app.exec();
}
