#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>
#include <cmath>


using namespace std;
using namespace eosio;

CONTRACT precise : public contract {
  public:
    using contract::contract;

    ACTION precision(name from, asset amount);
    

  private:
    TABLE convert {
      name    user;
      asset amount = asset(0, symbol("VIG", 4));
      asset _amt = asset(0, symbol("VIG", 10));
      auto primary_key() const { return user.value; }
    };
    typedef multi_index<"convert"_n, convert> _convert;
};
