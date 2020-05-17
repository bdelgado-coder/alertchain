#include <eosio/eosio.hpp>
#include <eosio/print.hpp>

using namespace eosio;

class hello : public contract
{
public:
  using contract::contract;

  [[eosio::action]] 
  void hi(name user) {
    print("Hello and welcome to the future ", user);
  }
};

EOSIO_DISPATCH(hello, (hi))