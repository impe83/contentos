#include <eosio/testing/tester.hpp>

#include "eosio.token.wast.hpp"
#include "eosio.token.abi.hpp"

#include "benchmark.hpp"

using namespace eosio::chain;
using namespace eosio::testing;

transaction_trace_ptr create_currency( tester& tester, name contract, name manager, asset maxsupply ) {
    auto act =  mutable_variant_object()
    ("issuer",       manager )
    ("maximum_supply", maxsupply );
    
    return tester.push_action(contract, N(create), contract, act );
}

transaction_trace_ptr issue( tester& tester, name to, const asset& amount, name manager = config::system_account_name ) {
    return tester.push_action( N(eosio.token), N(issue), manager, mutable_variant_object()
                             ("to",      to )
                             ("quantity", amount )
                             ("memo", "")
                             );
}

transaction_trace_ptr transfer( tester& tester, name from, name to, const string& amount, name manager = config::system_account_name ) {
    return tester.push_action( N(eosio.token), N(transfer), manager, mutable_variant_object()
                             ("from",    from)
                             ("to",      to )
                             ("quantity", asset::from_string(amount) )
                             ("memo", "")
                             );
}

transaction_trace_ptr test_compiler_builtins( tester& tester, name foo ) {
    return tester.push_action( N(eosio.token), N(testcb), foo, mutable_variant_object()
                              ("name",    foo)
                              );
}

transaction_trace_ptr test_chain( tester& tester, name foo ) {
    return tester.push_action( N(eosio.token), N(testchain), foo, mutable_variant_object()
                              ("name",    foo)
                              );
}

transaction_trace_ptr test_float( tester& tester, name foo ) {
    return tester.push_action( N(eosio.token), N(testfloat), foo, mutable_variant_object()
                              ("name",    foo)
                              );
}

transaction_trace_ptr test_crypto( tester& tester, name foo ) {
    return tester.push_action( N(eosio.token), N(testcrypto), foo, mutable_variant_object()
                              ("name",    foo)
                              );
}

transaction_trace_ptr test_print( tester& tester, name foo ) {
    return tester.push_action( N(eosio.token), N(testprint), foo, mutable_variant_object()
                              ("name",    foo)
                              );
}

transaction_trace_ptr test_systemapi( tester& tester, name foo ) {
    return tester.push_action( N(eosio.token), N(testsystemapi), foo, mutable_variant_object()
                              ("name",    foo)
                              );
}

transaction_trace_ptr test_mem( tester& tester, name foo ) {
    return tester.push_action( N(eosio.token), N(testmem), foo, mutable_variant_object()
                              ("name",    foo)
                              );
}

transaction_trace_ptr test_db( tester& tester, name foo ) {
    return tester.push_action( N(eosio.token), N(testdb), foo, mutable_variant_object()
                              ("name",    foo)
                              );
}

transaction_trace_ptr test_trxauth( tester& tester, name foo ) {
    return tester.push_action( N(eosio.token), N(testtrxauth), foo, mutable_variant_object()
                              ("name",    foo)
                              );
}


#define CORE_AMOUNT(s)  (s " " CORE_SYMBOL_NAME)

void test_eosio() {
    tester tester;
    
    // create account for eos.token, alice & bob
    tester.create_accounts( { N(eosio.token), N(alice), N(bob), N(tom) } );
    
    // push eosio.token contract
    tester.set_code( N(eosio.token), eosio_token_wast );
    tester.set_abi( N(eosio.token), eosio_token_abi );
    
    transaction_trace_ptr trace_ptr = nullptr;
    
    // create system token with max supply limit of 10 billion
    trace_ptr = create_currency( tester, N(eosio.token), config::system_account_name, core_from_string("10000000000.0000") );
    
    // eosio issues 1 billion tokens to tom
    trace_ptr = issue( tester, N(tom), core_from_string("1000000000.0000"));
    
    // tom -> alice: 10k
    trace_ptr = transfer( tester, N(tom), N(alice), CORE_AMOUNT("10000.0000"), N(tom) );
    
    // alice -> bob: 3k
    // bob -> alice: 2.5k
    trace_ptr = transfer( tester, N(alice), N(bob), CORE_AMOUNT("3000.0000"), N(alice) );
    trace_ptr = transfer( tester, N(bob), N(alice), CORE_AMOUNT("2500.0000"), N(bob) );
    
    trace_ptr = test_compiler_builtins( tester, N(alice) );
    trace_ptr = test_chain( tester, N(alice) );
    trace_ptr = test_float( tester, N(alice) );
    trace_ptr = test_crypto( tester, N(alice) );
    trace_ptr = test_print( tester, N(alice) );
    trace_ptr = test_systemapi( tester, N(alice) );
    trace_ptr = test_mem( tester, N(alice) );
    
    trace_ptr = test_db( tester, N(alice) );
    trace_ptr = test_trxauth( tester, N(alice) );
}

int main(int argc, char** argv) {
    wasm_benchmark_init();
    test_eosio();
    wasm_benchmark_show_result();
    return 0;
}


