#ifndef CHARACTERINSTANCE_H
#define CHARACTERINSTANCE_H

#include <Domain/Character/Character.h>

#include "Controller/CharacterInventoryController.h"

namespace Engine {

class CharacterInstance {
public:
    explicit CharacterInstance( std::unique_ptr<Domain::Character> );

    std::string sessionId() const;
    void setSessionId( const std::string& sessionId );

    Domain::Character& character();

    void onEnterWorld();
    void onLeaveWorld();

    void tick();

private:
    std::string _sessionId;
    std::unique_ptr<Domain::Character> _character;

    std::unique_ptr<CharacterInventoryController> _inventoryController;

    // int _actionCounter;
    // int _actionDuration;

    // int _regenCounter;
    // int _regenDuration;

    /*
        Character.Action:
        int _actionDuration;
        int _actionCounter;

        int actionDuration() const;
        void setActionDuration( int actionDuration );

        int actionCounter() const;
        void setActionCounter( int actionCounter );

------------------------------------------------------

        Character.CharacterVitals:
        int _regenDuration;
        int _regenCounter;

        int regenDuration() const;
        void setRegenDuration( int regenDuration );

        int regenCounter() const;
        void setRegenCounter( int regenCounter );
     */
};

} // namespace Engine

#endif // CHARACTERINSTANCE_H
