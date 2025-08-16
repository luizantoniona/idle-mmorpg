#include "QuestRequirement.h"

namespace Model {

QuestRequirement::QuestRequirement() {
}

std::string QuestRequirement::type() const {
    return _type;
}

void QuestRequirement::setType( const std::string& type ) {
    _type = type;
}

std::string QuestRequirement::requirementId() const {
    return _requirementId;
}

void QuestRequirement::setRequirementId( const std::string& requirementId ) {
    _requirementId = requirementId;
}

int QuestRequirement::amount() const {
    return _amount;
}

void QuestRequirement::setAmount( int amount ) {
    _amount = amount;
}

} // namespace Model
