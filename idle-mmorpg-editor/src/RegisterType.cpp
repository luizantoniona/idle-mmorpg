#include "RegisterType.h"

#include <QQmlContext>

#include <Control/CreatureControl.h>

void RegisterType::registerAll( QQmlApplicationEngine& engine ) {
    qmlRegisterType<CreatureControl>( "IdleMMO", 1, 0, "CreatureControl" );
}
