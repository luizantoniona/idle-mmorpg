#ifndef AUTHFILTER_H
#define AUTHFILTER_H

#include <drogon/HttpFilter.h>

namespace Network {

class AuthFilter : public drogon::HttpFilter<AuthFilter> {
public:
    void doFilter( const drogon::HttpRequestPtr& request, drogon::FilterCallback&& callback, drogon::FilterChainCallback&& chainCallback ) override;
};

} // namespace Network

#endif // AUTHFILTER_H
