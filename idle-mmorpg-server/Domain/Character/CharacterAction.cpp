#include "CharacterAction.h"

namespace Domain {

CharacterAction::CharacterAction() :
    _type( ActionType::UNKNOWN ),
    _description( "" ),
    _options(),
    _selectedOption() {
}

Json::Value CharacterAction::toJson() const {
    Json::Value values;
    values[ "type" ] = static_cast<int>( _type );
    values[ "description" ] = _description;

    if ( !_options.empty() ) {
        Json::Value optionsJson;

        for ( const auto& option : _options ) {
            Json::Value optionJson;
            optionJson[ "stage" ] = option.stage();
            optionJson[ "duration" ] = option.duration();
            optionJson[ "experience" ] = option.experience();
            optionJson[ "skill" ] = static_cast<int>( option.skill() );

            if ( !option.itemId().empty() ) {
                optionJson[ "item" ] = option.itemId();
            }

            optionsJson.append( optionJson );
        }
        values[ "options" ] = optionsJson;
    }

    if ( _selectedOption.duration() > 0 ) {
        Json::Value selectedJson;
        selectedJson[ "stage" ] = _selectedOption.stage();
        selectedJson[ "duration" ] = _selectedOption.duration();
        selectedJson[ "experience" ] = _selectedOption.experience();
        selectedJson[ "skill" ] = static_cast<int>( _selectedOption.skill() );

        if ( !_selectedOption.itemId().empty() ) {
            selectedJson[ "item" ] = _selectedOption.itemId();
        }

        values[ "selectedOption" ] = selectedJson;
    }

    return values;
}

ActionType CharacterAction::type() const {
    return _type;
}

void CharacterAction::setType( ActionType type ) {
    _type = type;
}

std::string CharacterAction::description() const {
    return _description;
}

void CharacterAction::setDescription( const std::string& description ) {
    _description = description;
}

CharacterActionOption CharacterAction::selectedOption() const {
    return _selectedOption;
}

void CharacterAction::setSelectedOption( const CharacterActionOption& selectedOption ) {
    _selectedOption = selectedOption;
}

std::vector<CharacterActionOption> CharacterAction::options() const {
    return _options;
}

void CharacterAction::setOptions( const std::vector<CharacterActionOption>& options ) {
    _options = options;
}

} // namespace Domain
