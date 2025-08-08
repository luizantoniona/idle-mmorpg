#ifndef CHARACTERATTRIBUTES_H
#define CHARACTERATTRIBUTES_H

#include <json/json.h>

namespace Model {

class CharacterAttributes {
public:
    CharacterAttributes();

    Json::Value toJson() const;

    double Strength() const;
    double Dexterity() const;
    double Constitution() const;
    double Intelligence() const;
    double Wisdom() const;

    double baseStrength() const;
    void setBaseStrength( double baseStrength );

    double baseDexterity() const;
    void setBaseDexterity( double baseDexterity );

    double baseConstitution() const;
    void setBaseConstitution( double baseConstitution );

    double baseIntelligence() const;
    void setBaseIntelligence( double baseIntelligence );

    double baseWisdom() const;
    void setBaseWisdom( double baseWisdom );

    void modifyStrength( double modifier );
    void modifyDexterity( double modifier );
    void modifyConstitution( double modifier );
    void modifyIntelligence( double modifier );
    void modifyWisdom( double modifier );

private:
    double _baseStrength;
    double _baseDexterity;
    double _baseConstitution;
    double _baseIntelligence;
    double _baseWisdom;

    double _modifierStrength;
    double _modifierDexterity;
    double _modifierConstitution;
    double _modifierIntelligence;
    double _modifierWisdom;
};

} // namespace Model

#endif // CHARACTERATTRIBUTES_H
