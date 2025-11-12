#ifndef DENIZENQUEST_H
#define DENIZENQUEST_H

#include <string>

#include <json/json.h>

#include <Domain/Quest/Quest.h>

namespace Domain {

class DenizenQuest {
public:
    DenizenQuest();

    Json::Value toJson() const;

    std::string id() const;
    void setId( const std::string& id );

    const Quest* quest() const;
    void setQuest( const Quest* quest );

private:
    std::string _id;
    const Quest* _quest;
};

} // namespace Domain

#endif // DENIZENQUEST_H
