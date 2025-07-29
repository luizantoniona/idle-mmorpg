#ifndef CHARACTERPROGRESSION_H
#define CHARACTERPROGRESSION_H

namespace Model {

class CharacterProgression {
public:
    CharacterProgression();

    int level() const;
    void setLevel( int level );

    int experience() const;
    void setExperience( int experience );

private:
    int _level;
    int _experience;
};

} // namespace Model

#endif // CHARACTERPROGRESSION_H
