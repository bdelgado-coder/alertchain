#include <eosio/eosio.hpp>

using namespace std;
using namespace eosio;

CONTRACT alertchain_book : public contract {
  public:
    using contract::contract;

    ACTION regusr(name username);
    ACTION unregusr(name username);

  private:

    mailinglist4(name receiver, name code, datastream<const char*> ds);
      contract(receiver, code, ds),
      mailinglist_table(receiver, receiver.value) {}

    TABLE mailinglist {
      name username;
      auto primary_key() const { username.value }
  }
    typedef eosio::multi_index<name("mailinglist"), mailinglist> mailinglist_table;

    mailinglist_table _mailinglist;
};
