#include "RegisterType.h"

#include <QQmlContext>

#include <Control/CreatureControl.h>
#include <Control/ItemControl.h>
#include <Control/SpellControl.h>

void RegisterType::registerAll( QQmlApplicationEngine& engine ) {
    qmlRegisterType<CreatureControl>( "IdleMMO", 1, 0, "CreatureControl" );
    qmlRegisterType<ItemControl>( "IdleMMO", 1, 0, "ItemControl" );
    qmlRegisterType<SpellControl>( "IdleMMO", 1, 0, "SpellControl" );
}
