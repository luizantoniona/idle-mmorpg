#include "DecimalHelper.h"

#include <cmath>

namespace Commons {

double DecimalHelper::roundDecimals( double value, int precision ) {
    double factor = std::pow( 10.0, precision );
    return std::round( value * factor ) / factor;
}

} // namespace Commons
