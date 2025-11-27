#ifndef CREATURECONTROL_H
#define CREATURECONTROL_H

#include <QJsonArray>
#include <QObject>

class CreatureControl : public QObject {
    Q_OBJECT
    Q_PROPERTY( QJsonArray creatureTypes READ creatureTypes NOTIFY creatureTypesChanged )
    Q_PROPERTY( QJsonArray creatures READ creatures NOTIFY creaturesChanged )

public:
    explicit CreatureControl( QObject* parent = nullptr );

    QJsonArray creatureTypes() const;
    QJsonArray creatures() const;

public slots:
    void loadCreatures();

signals:
    void creatureTypesChanged();
    void creaturesChanged();

private:
    QJsonArray _creatureTypes;
    QJsonArray _creatures;
};

#endif // CREATURECONTROL_H
