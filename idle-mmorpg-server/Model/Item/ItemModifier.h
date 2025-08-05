#ifndef ITEMMODIFIER_H
#define ITEMMODIFIER_H

#include <string>

namespace Model {

class ItemModifier {
public:
    ItemModifier();

    std::string type() const;
    void setType( const std::string& type );

    std::string target() const;
    void setTarget( const std::string& target );

    double value() const;
    void setValue( double value );

private:
    std::string _type;
    std::string _target;
    double _value;
};

} // namespace Model

#endif // ITEMMODIFIER_H
