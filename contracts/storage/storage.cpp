/**
 *  @file
 *  @copyright defined in contentos/LICENSE.txt
 */
#include <utility>
#include <vector>
#include <string>
#include <cosiolib/cosio.hpp>
#include <cosiolib/time.hpp>
#include <cosiolib/asset.hpp>
#include <cosiolib/contract.hpp>
#include <cosiolib/crypto.h>

using cosio::key256;
using cosio::indexed_by;
using cosio::const_mem_fun;
using cosio::asset;
using cosio::action;
using cosio::print;
using cosio::name;
using cosio::namex;

class storage : public cosio::contract {
   public:
      const uint32_t FIVE_MINUTES = 5*60;

      storage(account_name self)
      :cosio::contract(self),
       offers(_self, _self)
      {}
      
      //@abi action
      void placeoffer(const account_name owner, const asset& bet, const checksum256& commitment) {

         contento_assert( bet.symbol == CORE_SYMBOL, "only core token allowed" );
         contento_assert( bet.is_valid(), "invalid bet" );
         contento_assert( bet.amount > 0, "must bet positive quantity" );

         contento_assert( !has_offer( commitment ), "offer with this commitment already exist" );

         // Store new offer
         offers.emplace(_self, [&](auto& offer){
            offer.id         = offers.available_primary_key();
            offer.bet        = bet;
            offer.owner      = owner;
            offer.commitment = commitment;
            offer.gameid     = 0;
         });
         print( "[storage]-> ", namex{owner}, " placed 1 record in table \"offer\"");
      }

      //@abi action
      void canceloffer( const checksum256& commitment ) {

         auto idx = offers.template get_index<N(commitment)>();
         auto offer_itr = idx.find( offer::get_commitment(commitment) );

         contento_assert( offer_itr != idx.end(), "offer does not exists" );
         contento_assert( offer_itr->gameid == 0, "unable to cancel offer" );
         //require_auth( offer_itr->owner );
         idx.erase(offer_itr);
         print( "[storage]-> ", namex{offer_itr->owner}, " removed 1 record in table \"offer\"");
      }

      //@abi action
      void callhello() {
         auto caller = cosio::current_caller();
         print("[storage]-> inline action callhello called by ", namex{caller});

         action(
            caller,
            N16(hello),
            N(hi),
            N16(storage)//"[\"contento\"]"
         ).send();
      }

   private:
      //@abi table offer i64
      struct offer {
         uint64_t          id;
         account_name      owner;
         asset             bet;
         checksum256       commitment;
         uint64_t          gameid = 0;

         uint64_t primary_key()const { return id; }

         uint64_t by_bet()const { return (uint64_t)bet.amount; }

         key256 by_commitment()const { return get_commitment(commitment); }

         static key256 get_commitment(const checksum256& commitment) {
            const uint64_t *p64 = reinterpret_cast<const uint64_t *>(&commitment);
            return key256::make_from_word_sequence<uint64_t>(p64[0], p64[1], p64[2], p64[3]);
         }

         COSLIB_SERIALIZE( offer, (id)(owner)(bet)(commitment)(gameid) )
      };

      typedef cosio::multi_index< N(offer), offer,
         indexed_by< N(bet), const_mem_fun<offer, uint64_t, &offer::by_bet > >,
         indexed_by< N(commitment), const_mem_fun<offer, key256,  &offer::by_commitment> >
      > offer_index;

      offer_index       offers;

      bool has_offer( const checksum256& commitment )const {
         auto idx = offers.template get_index<N(commitment)>();
         auto itr = idx.find( offer::get_commitment(commitment) );
         return itr != idx.end();
      }

      bool is_equal(const checksum256& a, const checksum256& b)const {
         return memcmp((void *)&a, (const void *)&b, sizeof(checksum256)) == 0;
      }

      bool is_zero(const checksum256& a)const {
         const uint64_t *p64 = reinterpret_cast<const uint64_t*>(&a);
         return p64[0] == 0 && p64[1] == 0 && p64[2] == 0 && p64[3] == 0;
      }
};

COSIO_ABI( storage, (placeoffer)(canceloffer)(callhello) )

