/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#include <contento/protocol/chain_id_type.hpp>
#include <fc/exception/exception.hpp>

namespace contento { namespace protocol {

   void chain_id_type::reflector_verify()const {
      FC_ASSERT( *reinterpret_cast<const fc::sha256*>(this) != fc::sha256(), "chain_id_type cannot be zero" );
   }

} }  // namespace contento::protocol

namespace fc {

   void to_variant(const contento::protocol::chain_id_type& cid, fc::variant& v) {
      to_variant( static_cast<const fc::sha256&>(cid), v);
   }

   void from_variant(const fc::variant& v, contento::protocol::chain_id_type& cid) {
      from_variant( v, static_cast<fc::sha256&>(cid) );
   }

} // fc
