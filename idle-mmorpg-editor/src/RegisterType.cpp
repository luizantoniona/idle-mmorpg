#include "RegisterType.h"

#include <QQmlContext>

#include <Control/CreatureControl.h>
#include <Control/ItemControl.h>
#include <Control/SpellControl.h>

void RegisterType::registerAll( QQmlApplicationEngine& engine ) {
    qmlRegisterType<CreatureControl>( "IdleMMOControls", 1, 0, "CreatureControl" );
    qmlRegisterType<ItemControl>( "IdleMMOControls", 1, 0, "ItemControl" );
    qmlRegisterType<SpellControl>( "IdleMMOControls", 1, 0, "SpellControl" );
}
