#include "CreatureControl.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

namespace {
constexpr const char* CREATURE_DATA_PATH = "../../../idle-mmorpg-data/idle-mmorpg-creature/creatures.json";
}

CreatureControl::CreatureControl( QObject* parent ) :
    QObject( parent ) {

    loadCreatures();
}

QJsonArray CreatureControl::creatureTypes() const {
    return _creatureTypes;
}

QJsonArray CreatureControl::creatures() const {
    return _creatures;
}

void CreatureControl::loadCreatures() {
    QFile file( CREATURE_DATA_PATH );
    if ( !file.open( QIODevice::ReadOnly ) ) {
        qWarning() << "Failed to open:" << CREATURE_DATA_PATH;
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson( file.readAll() );
    auto obj = doc.object();

    if ( !obj.contains( "types" ) || !obj[ "types" ].isArray() ) {
        qWarning() << "Missing 'types' array";
        return;
    }

    _creatureTypes = obj[ "types" ].toArray();

    emit creatureTypesChanged();
}
