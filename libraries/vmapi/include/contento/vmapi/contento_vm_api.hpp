#pragma once

#include <contento/chain/contento_object_types.hpp>
#include "vm_obj.hpp"
#include <contento/chain/database.hpp>
#include <contento/chain/contento_objects.hpp>
#include <contento/app/api_context.hpp>


#include <fc/api.hpp>
#include <fc/optional.hpp>
#include <fc/variant_object.hpp>
#include <fc/rpc/binary_api_connection.hpp>

#include <fc/network/ip.hpp>

#include <boost/container/flat_set.hpp>

#include <functional>
#include <map>
#include <memory>
#include <vector>

namespace contento { namespace vmi {

using namespace contento::chain;
using namespace contento::protocol;
using namespace contento::app;

using namespace std;


class contento_vm_api_impl;


/**
 * @brief The contento_vm_api class implements the RPC API for the vm-chain about content.
 *
 */
class contento_vm_api
{
   public:
      contento_vm_api(const contento::app::api_context& ctx);
      ~contento_vm_api();


      //////////////
      // Accounts //
      //////////////

      vector< account_obj_vmi > get_accounts( vector< string > names ) const;
      account_obj_vmi get_account( string name ) const;

      /**
       * @brief Get the total number of accounts registered with the blockchain
       */
      uint64_t get_account_count()const;

      ////////////////////////////
      // Handlers - not exposed //
      ////////////////////////////
      void on_api_startup();

   private:

      std::shared_ptr< contento_vm_api_impl >   my;
};

} }

FC_API(contento::vmi::contento_vm_api,
      (get_accounts)
      (get_account)
      (get_account_count)
)


