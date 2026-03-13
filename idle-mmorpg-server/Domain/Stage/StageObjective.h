#ifndef STAGEOBJECTIVE_H
#define STAGEOBJECTIVE_H

#include <string>

#include <json/json.h>

namespace Domain {

class StageObjective {
public:
    StageObjective();
    ~StageObjective();

    Json::Value toJson();

    std::string type() const;
    void setType( const std::string& type );

    std::string target() const;
    void setTarget( const std::string& target );

    int amount() const;
    void setAmount( int amount );

private:
    std::string _type;
    std::string _target;
    int _amount;
};

} // namespace Domain

#endif // STAGEOBJECTIVE_H
