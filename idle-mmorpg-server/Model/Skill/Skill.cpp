#include "Skill.h"

namespace Model {

Skill::Skill() {}

std::string Skill::id() const {
    return _id;
}

void Skill::setId( const std::string& id ) {
    _id = id;
}

std::string Skill::name() const {
    return _name;
}

void Skill::setName( const std::string& name ) {
    _name = name;
}

std::string Skill::description() const {
    return _description;
}

void Skill::setDescription( const std::string& description ) {
    _description = description;
}

std::string Skill::type() const {
    return _type;
}

void Skill::setType( const std::string& type ) {
    _type = type;
}

std::vector<SkillMilestone> Skill::millestones() const {
    return _millestones;
}

void Skill::setMillestones( const std::vector<SkillMilestone>& millestones ) {
    _millestones = millestones;
}

void Skill::addMilestone( const SkillMilestone& milestone ) {
    _millestones.push_back( milestone );
}

} // namespace Model
