#include <precise.hpp>

ACTION precise::precision(name from, asset amount) {
  require_auth(from);
  
  // getting the symbol of the assetin token
  auto _sym = amount.symbol.code();
  
  // --- create an asset with a precision of 10
  asset amt10 = asset(0, symbol(_sym, 10));
  
  // --- create an asset with a precision of 4
  asset amt4 = asset(0, symbol(_sym, 4));
  
  // find out the precision of asset amount
  if(amount.symbol.precision() == 4 || amount.symbol.precision() == 3)
  {
    int n = amount.symbol.precision();
    // assiging the value of the asset amount to the internal asset pf precision 10
    amt10.amount = amount.amount;
    
    // if the precison is four then calculate the difference between 10 and 4
    amt10.amount = amt10.amount * std::pow(10.0, (10 - n));
  }
  else if(amount.symbol.precision() == 10){
    
    // --- assign the asset amt4 the value ot truncated amt10
    // --- this truncates asset10 to asset4
    amt4.amount = int64_t(std::round(amt10.amount));
  }
  
  // Init the _convert table
  _convert _prespec(get_self(), from.value);

  // Find the payment record from _convert table
  auto itr = _prespec.find(from.value);
  if (itr == _prespec.end()) {
    // Create a payment record if it does not exist
    _prespec.emplace(from, [&](auto& spec) {
      spec.user = from;
      spec.amount = amount;
      spec._amt = amt10;
    });
  } else {
    // Modify the payment record if it exists
    _prespec.modify(itr, from, [&](auto& spec) {
      spec.amount = amount;
      spec._amt = amt10;
    });
  }
}


EOSIO_DISPATCH(precise, (precision))
