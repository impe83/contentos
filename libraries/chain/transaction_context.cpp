#include <eosio/chain/apply_context.hpp>
#include <eosio/chain/transaction_context.hpp>
#include <eosio/chain/authorization_manager.hpp>
#include <eosio/chain/exceptions.hpp>
#include <eosio/chain/resource_limits.hpp>
#include <eosio/chain/generated_transaction_object.hpp>
#include <eosio/chain/transaction_object.hpp>
#include <eosio/chain/global_property_object.hpp>

namespace eosio { namespace chain {

   transaction_context::transaction_context( controller& c,
                                             const signed_transaction& t,
                                             const transaction_id_type& trx_id,
                                             fc::time_point s )
   :control(c)
   ,trx(t)
   ,id(trx_id)
   ,undo_session(c.db().start_undo_session(true))
   ,start(s)
   {
      FC_ASSERT( trx.extensions.size() == 0, "we don't support any extensions yet" );
   }

   void transaction_context::init( )
   {
      is_initialized = true;
   }

   void transaction_context::exec() {
      FC_ASSERT( is_initialized, "must first initialize" );

         for( const auto& act : trx.actions ) {
            trace->action_traces.emplace_back();
            dispatch_action( trace->action_traces.back(), act );
         }
   }

   void transaction_context::finalize() {
      FC_ASSERT( is_initialized, "must first initialize" );
   }

   void transaction_context::squash() {
      undo_session.squash();
   }


   void transaction_context::check_net_usage()const {
   }

   void transaction_context::checktime()const {
    //   auto now = fc::time_point::now();
    //   if( BOOST_UNLIKELY( now > _deadline ) ) {
    //      // edump((now-start)(now-pseudo_start));
    //      if( billed_cpu_time_us > 0 || deadline_exception_code == deadline_exception::code_value ) {
    //         EOS_THROW( deadline_exception, "deadline exceeded", ("now", now)("deadline", _deadline)("start", start) );
    //      } else if( deadline_exception_code == block_cpu_usage_exceeded::code_value ) {
    //         EOS_THROW( block_cpu_usage_exceeded,
    //                    "not enough time left in block to complete executing transaction",
    //                    ("now", now)("deadline", _deadline)("start", start)("billing_timer", now - pseudo_start) );
    //      } else if( deadline_exception_code == tx_cpu_usage_exceeded::code_value ) {
    //         EOS_THROW( tx_cpu_usage_exceeded,
    //                    "transaction was executing for too long",
    //                    ("now", now)("deadline", _deadline)("start", start)("billing_timer", now - pseudo_start) );
    //      } else if( deadline_exception_code == leeway_deadline_exception::code_value ) {
    //         EOS_THROW( leeway_deadline_exception,
    //                    "the transaction was unable to complete by deadline, "
    //                    "but it is possible it could have succeeded if it were allowed to run to completion",
    //                    ("now", now)("deadline", _deadline)("start", start)("billing_timer", now - pseudo_start) );
    //      }
    //      FC_ASSERT( false, "unexpected deadline exception code" );
    //   }
   }

   void transaction_context::pause_billing_timer() {
   }

   void transaction_context::resume_billing_timer() {
   }

   void transaction_context::validate_cpu_usage_to_bill( int64_t billed_us, bool check_minimum )const {
      
   }

   void transaction_context::add_ram_usage( account_name account, int64_t ram_delta ) {
      
   }

   void transaction_context::dispatch_action( action_trace& trace, const action& a, account_name receiver, bool context_free, uint32_t recurse_depth ) {
      apply_context  acontext( control, *this, a, recurse_depth );
      acontext.context_free = context_free;
      acontext.receiver     = receiver;

      try {
         acontext.exec();
      } catch( ... ) {
         trace = move(acontext.trace);
         throw;
      }

      trace = move(acontext.trace);
   }

} } /// eosio::chain