#include "Skill.h"

#include <cmath>

#include "SkillHelper.h"

namespace Domain {

Skill::Skill() :
    _type( SkillType::UNKNOWN ),
    // TODO: Create a enum for category?
    _category( "" ),
    _name( "" ),
    _description( "" ),
    _milestone(),
    _baseExperience( 0.0 ),
    _growthRate( 0.0 ) {}

Json::Value Skill::toJson() {
    Json::Value root;
    root[ "type" ] = SkillHelper::typeToString( _type );
    root[ "category" ] = _category;
    root[ "name" ] = _name;
    root[ "description" ] = _description;
    return root;
}

SkillType Skill::type() const {
    return _type;
}

void Skill::setType( SkillType type ) {
    _type = type;
}

std::string Skill::category() const {
    return _category;
}

void Skill::setCategory( const std::string& category ) {
    _category = category;
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

SkillMilestone Skill::milestone() const {
    return _milestone;
}

void Skill::setMilestone( const SkillMilestone& milestone ) {
    _milestone = milestone;
}

double Skill::baseExperience() const {
    return _baseExperience;
}

void Skill::setBaseExperience( double baseExperience ) {
    _baseExperience = baseExperience;
}

double Skill::growthRate() const {
    return _growthRate;
}

void Skill::setGrowthRate( double growthRate ) {
    _growthRate = growthRate;
}

int Skill::experienceForNextLevel( int currentLevel ) const {
    return static_cast<int>( _baseExperience * std::pow( _growthRate, currentLevel ) );
}

} // namespace Domain
