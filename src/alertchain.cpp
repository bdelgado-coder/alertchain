#include <eosio/eosio/hpp>

using namespace eosio;

class [[eosio::contract("alertchain_book")]] alertchain_book : public eosio::contract
{
	public:
		alertchain_book(name receiver, name code, datastream<const char*> ds):
	contract(reciever, code, ds) {}
		
		[[eosio::action]]
		void upsert(name user, std::string first_name, std::string last_name, std::string county) {
			require_auth( user );
			address_index addresses(get_self(), get_first_receiver().value);
			auto iterator = addresses.find(user.value);
			// if user does not exist, add to table
            if( iterator == address.end() )
			{
				addresses.emplace(user, [&]( auto& row ) {
					row.key = user;
					row.first_name = first_name;
					row.last_name = last_name;
					row.county = county;
                    row.nominations = 0;
				});
			}
            // else user does exist and can modify their information 
            // user cannot modify their own nomination count
			else {
				addresses.modify(iterator, user, [&]( auto& row  ){
					row.key = user;
					row.first_name = first_name;
					row.last_name = last_name;
					row.county = county;
				});
			}
		}
		
		[[eosio::action]]
		void erase(name user){
			require_auth(user);
			address_index addresses(get_self(), get_first_receiver().value);
			auto iterator = addresses.find(user.value);
			check(iterator != addresses.end(), "User does note exist");
			addresses.erase(iterator);
		}

	private:
		struct [[eosio::table]] person {
			name key;
			std::string first_name;
			std::string last_name;
			std::string county;
            std::int nominations;

			uint64_t primary_key() const { return key.value;}
		};
		
		typedef eosio::multi_index<"people"_n, person> address_index;
};


