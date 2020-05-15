#include <eosio/eosio.hpp>
#include <eosio/system.hpp>

using namespace std;
using namespace eosio;

CONTRACT alertchain_book : public contract {
  public:
    using contract::contract;

    ACTION upsert(name user, std::string first_name, std::string last_name, std::string county);
    ACTION erase(name user);

  private:

    alertchain_book(name receiver, name code, datastream<const char*> ds);
      contract(receiver, code, ds),
      mailinglist_table(receiver, receiver.value) {}

    TABLE person {
      name key;
			std::string first_name;
			std::string last_name;
			std::string county;
      std::int nominations;

			uint64_t primary_key() const { return key.value;}
  }
    typedef eosio::multi_index<name("mailinglist"), mailinglist> mailinglist_table;

    mailinglist_table _mailinglist;
};
