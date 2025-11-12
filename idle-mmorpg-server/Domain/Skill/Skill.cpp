#include "Skill.h"

namespace Domain {

Skill::Skill() :
    _type( SkillType::UNKNOWN ),
    _id( "" ),
    _name( "" ),
    _description( "" ),
    _category( "" ),
    _millestones( {} ) {
}

Json::Value Skill::toJson() {
    Json::Value root;
    root[ "id" ] = id();
    root[ "name" ] = name();
    root[ "description" ] = description();
    root[ "category" ] = category();
    return root;
}

SkillType Skill::type() const {
    return _type;
}

void Skill::setType( SkillType type ) {
    _type = type;
}

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

std::string Skill::category() const {
    return _category;
}

void Skill::setCategory( const std::string& category ) {
    _category = category;
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

} // namespace Domain
