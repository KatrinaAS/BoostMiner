#ifndef BOOSTMINER_POW_CO_API
#define BOOSTMINER_POW_CO_API

#include <data/networking/HTTP_client.hpp>
#include <gigamonkey/boost/boost.hpp>

using namespace Gigamonkey;

struct pow_co : networking::HTTP_client {
    
    pow_co(networking::HTTP &http) : 
        networking::HTTP_client{http, networking::REST{"https", "pow.co"}, tools::rate_limiter{3, 1}} {}
    
    list<Boost::prevout> jobs();
    
    struct inpoint : Bitcoin::outpoint {
        using Bitcoin::outpoint::outpoint;
        bool valid() const {
            return this->Digest.valid();
        }
    };
    
    inpoint spends(const Bitcoin::outpoint &);
    
    void submit_proof(const Bitcoin::txid &);
    
};

#endif