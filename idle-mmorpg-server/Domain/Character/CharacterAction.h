#ifndef CHARACTERACTION_H
#define CHARACTERACTION_H

#include <json/json.h>

#include <string>

#include <Domain/Action/ActionType.h>

#include "CharacterActionOption.h"

namespace Domain {

class CharacterAction {
public:
    CharacterAction();

    Json::Value toJson() const;

    ActionType type() const;
    void setType( ActionType type );

    std::string description() const;
    void setDescription( const std::string& description );

    CharacterActionOption selectedOption() const;
    void setSelectedOption( const CharacterActionOption& selectedOption );

    std::vector<CharacterActionOption> options() const;
    void setOptions( const std::vector<CharacterActionOption>& options );

private:
    ActionType _type;
    std::string _description;
    CharacterActionOption _selectedOption;
    std::vector<CharacterActionOption> _options;
};

} // namespace Domain

#endif // CHARACTERACTION_H
