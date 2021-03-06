#include <contento/protocol/get_config.hpp>
#include <contento/protocol/config.hpp>
#include <contento/protocol/asset.hpp>
#include <contento/protocol/types.hpp>
#include <contento/protocol/version.hpp>

namespace contento { namespace protocol {

fc::variant_object get_config()
{
   fc::mutable_variant_object result;

#ifdef IS_TEST_NET
   result[ "IS_TEST_NET" ] = true;
#else
   result[ "IS_TEST_NET" ] = false;
#endif

   result["CONTENTO_100_PERCENT"] = CONTENTO_100_PERCENT;
   result["CONTENTO_1_PERCENT"] = CONTENTO_1_PERCENT;
   result["CONTENTO_1_TENTH_PERCENT"] = CONTENTO_1_TENTH_PERCENT;
   result["CONTENTO_ACCOUNT_RECOVERY_REQUEST_EXPIRATION_PERIOD"] = CONTENTO_ACCOUNT_RECOVERY_REQUEST_EXPIRATION_PERIOD;
   result["CONTENTO_ACTIVE_CHALLENGE_COOLDOWN"] = CONTENTO_ACTIVE_CHALLENGE_COOLDOWN;
   result["CONTENTO_ACTIVE_CHALLENGE_FEE"] = CONTENTO_ACTIVE_CHALLENGE_FEE;
   result["CONTENTO_ADDRESS_PREFIX"] = CONTENTO_ADDRESS_PREFIX;
   result["CONTENTO_APR_PERCENT_MULTIPLY_PER_BLOCK"] = CONTENTO_APR_PERCENT_MULTIPLY_PER_BLOCK;
   result["CONTENTO_APR_PERCENT_MULTIPLY_PER_HOUR"] = CONTENTO_APR_PERCENT_MULTIPLY_PER_HOUR;
   result["CONTENTO_APR_PERCENT_MULTIPLY_PER_ROUND"] = CONTENTO_APR_PERCENT_MULTIPLY_PER_ROUND;
   result["CONTENTO_APR_PERCENT_SHIFT_PER_BLOCK"] = CONTENTO_APR_PERCENT_SHIFT_PER_BLOCK;
   result["CONTENTO_APR_PERCENT_SHIFT_PER_HOUR"] = CONTENTO_APR_PERCENT_SHIFT_PER_HOUR;
   result["CONTENTO_APR_PERCENT_SHIFT_PER_ROUND"] = CONTENTO_APR_PERCENT_SHIFT_PER_ROUND;
   result["CONTENTO_BANDWIDTH_AVERAGE_WINDOW_SECONDS"] = CONTENTO_BANDWIDTH_AVERAGE_WINDOW_SECONDS;
   result["CONTENTO_BANDWIDTH_PRECISION"] = CONTENTO_BANDWIDTH_PRECISION;
   result["CONTENTO_BLOCKCHAIN_PRECISION"] = CONTENTO_BLOCKCHAIN_PRECISION;
   result["CONTENTO_BLOCKCHAIN_PRECISION_DIGITS"] = CONTENTO_BLOCKCHAIN_PRECISION_DIGITS;
   result["CONTENTO_BLOCKCHAIN_HARDFORK_VERSION"] = CONTENTO_BLOCKCHAIN_HARDFORK_VERSION;
   result["CONTENTO_BLOCKCHAIN_VERSION"] = CONTENTO_BLOCKCHAIN_VERSION;
   result["CONTENTO_BLOCK_INTERVAL"] = CONTENTO_BLOCK_INTERVAL;
   result["CONTENTO_BLOCKS_PER_DAY"] = CONTENTO_BLOCKS_PER_DAY;
   result["CONTENTO_BLOCKS_PER_HOUR"] = CONTENTO_BLOCKS_PER_HOUR;
   result["CONTENTO_BLOCKS_PER_YEAR"] = CONTENTO_BLOCKS_PER_YEAR;
   result["CONTENTO_CASHOUT_WINDOW_SECONDS"] = CONTENTO_CASHOUT_WINDOW_SECONDS;
   result["CONTENTO_CASHOUT_WINDOW_SECONDS_PRE_HF12"] = CONTENTO_CASHOUT_WINDOW_SECONDS_PRE_HF12;
   result["CONTENTO_CASHOUT_WINDOW_SECONDS_PRE_HF17"] = CONTENTO_CASHOUT_WINDOW_SECONDS_PRE_HF17;
   result["CONTENTO_CHAIN_ID"] = CONTENTO_CHAIN_ID;
   result["CONTENTO_COMMENT_REWARD_FUND_NAME"] = CONTENTO_COMMENT_REWARD_FUND_NAME;
   result["CONTENTO_CONTENT_APR_PERCENT"] = CONTENTO_CONTENT_APR_PERCENT;
   result["CONTENTO_CONTENT_CONSTANT_HF0"] = CONTENTO_CONTENT_CONSTANT_HF0;
   result["CONTENTO_CONTENT_REWARD_PERCENT"] = CONTENTO_CONTENT_REWARD_PERCENT;
   result["CONTENTO_CONVERSION_DELAY"] = CONTENTO_CONVERSION_DELAY;
   result["CONTENTO_CONVERSION_DELAY_PRE_HF_16"] = CONTENTO_CONVERSION_DELAY_PRE_HF_16;
   result["CONTENTO_CREATE_ACCOUNT_DELEGATION_RATIO"] = CONTENTO_CREATE_ACCOUNT_DELEGATION_RATIO;
   result["CONTENTO_CREATE_ACCOUNT_DELEGATION_TIME"] = CONTENTO_CREATE_ACCOUNT_DELEGATION_TIME;
   result["CONTENTO_CREATE_ACCOUNT_WITH_STEEM_MODIFIER"] = CONTENTO_CREATE_ACCOUNT_WITH_STEEM_MODIFIER;
   result["CONTENTO_CURATE_APR_PERCENT"] = CONTENTO_CURATE_APR_PERCENT;
   result["CONTENTO_DEFAULT_SBD_INTEREST_RATE"] = CONTENTO_DEFAULT_SBD_INTEREST_RATE;
   result["CONTENTO_EQUIHASH_K"] = CONTENTO_EQUIHASH_K;
   result["CONTENTO_EQUIHASH_N"] = CONTENTO_EQUIHASH_N;
   result["CONTENTO_FEED_HISTORY_WINDOW"] = CONTENTO_FEED_HISTORY_WINDOW;
   result["CONTENTO_FEED_HISTORY_WINDOW_PRE_HF_16"] = CONTENTO_FEED_HISTORY_WINDOW_PRE_HF_16;
   result["CONTENTO_FEED_INTERVAL_BLOCKS"] = CONTENTO_FEED_INTERVAL_BLOCKS;
   result["CONTENTO_FREE_TRANSACTIONS_WITH_NEW_ACCOUNT"] = CONTENTO_FREE_TRANSACTIONS_WITH_NEW_ACCOUNT;
   result["CONTENTO_GENESIS_TIME"] = CONTENTO_GENESIS_TIME;
   result["CONTENTO_HARDFORK_REQUIRED_WITNESSES"] = CONTENTO_HARDFORK_REQUIRED_WITNESSES;
   result["CONTENTO_INFLATION_NARROWING_PERIOD"] = CONTENTO_INFLATION_NARROWING_PERIOD;
   result["CONTENTO_INFLATION_RATE_START_PERCENT"] = CONTENTO_INFLATION_RATE_START_PERCENT;
   result["CONTENTO_INFLATION_RATE_STOP_PERCENT"] = CONTENTO_INFLATION_RATE_STOP_PERCENT;
   result["CONTENTO_INIT_MINER_NAME"] = CONTENTO_INIT_MINER_NAME;
   result["CONTENTO_INIT_PUBLIC_KEY_STR"] = CONTENTO_INIT_PUBLIC_KEY_STR;
#if 0
   // do not expose private key, period.
   // we need this line present but inactivated so CI check for all constants in config.hpp doesn't complain.
   result["CONTENTO_INIT_PRIVATE_KEY"] = CONTENTO_INIT_PRIVATE_KEY;
#endif
   result["CONTENTO_INIT_SUPPLY"] = CONTENTO_INIT_SUPPLY;
   result["CONTENTO_INIT_TIME"] = CONTENTO_INIT_TIME;
   result["CONTENTO_IRREVERSIBLE_THRESHOLD"] = CONTENTO_IRREVERSIBLE_THRESHOLD;
   result["CONTENTO_LIQUIDITY_APR_PERCENT"] = CONTENTO_LIQUIDITY_APR_PERCENT;
   result["CONTENTO_LIQUIDITY_REWARD_BLOCKS"] = CONTENTO_LIQUIDITY_REWARD_BLOCKS;
   result["CONTENTO_LIQUIDITY_REWARD_PERIOD_SEC"] = CONTENTO_LIQUIDITY_REWARD_PERIOD_SEC;
   result["CONTENTO_LIQUIDITY_TIMEOUT_SEC"] = CONTENTO_LIQUIDITY_TIMEOUT_SEC;
   result["CONTENTO_MAX_ACCOUNT_NAME_LENGTH"] = CONTENTO_MAX_ACCOUNT_NAME_LENGTH;
   result["CONTENTO_MAX_ACCOUNT_WITNESS_VOTES"] = CONTENTO_MAX_ACCOUNT_WITNESS_VOTES;
   result["CONTENTO_MAX_ASSET_WHITELIST_AUTHORITIES"] = CONTENTO_MAX_ASSET_WHITELIST_AUTHORITIES;
   result["CONTENTO_MAX_AUTHORITY_MEMBERSHIP"] = CONTENTO_MAX_AUTHORITY_MEMBERSHIP;
   result["CONTENTO_MAX_BLOCK_SIZE"] = CONTENTO_MAX_BLOCK_SIZE;
   result["CONTENTO_MAX_CASHOUT_WINDOW_SECONDS"] = CONTENTO_MAX_CASHOUT_WINDOW_SECONDS;
   result["CONTENTO_MAX_COMMENT_DEPTH"] = CONTENTO_MAX_COMMENT_DEPTH;
   result["CONTENTO_MAX_COMMENT_DEPTH_PRE_HF17"] = CONTENTO_MAX_COMMENT_DEPTH_PRE_HF17;
   result["CONTENTO_MAX_FEED_AGE_SECONDS"] = CONTENTO_MAX_FEED_AGE_SECONDS;
   result["CONTENTO_MAX_INSTANCE_ID"] = CONTENTO_MAX_INSTANCE_ID;
   result["CONTENTO_MAX_MEMO_SIZE"] = CONTENTO_MAX_MEMO_SIZE;
   result["CONTENTO_MAX_WITNESSES"] = CONTENTO_MAX_WITNESSES;
   result["CONTENTO_MAX_MINER_WITNESSES_HF0"] = CONTENTO_MAX_MINER_WITNESSES_HF0;
   result["CONTENTO_MAX_MINER_WITNESSES_HF17"] = CONTENTO_MAX_MINER_WITNESSES_HF17;
   result["CONTENTO_MAX_PERMLINK_LENGTH"] = CONTENTO_MAX_PERMLINK_LENGTH;
   result["CONTENTO_MAX_PROXY_RECURSION_DEPTH"] = CONTENTO_MAX_PROXY_RECURSION_DEPTH;
   result["CONTENTO_MAX_RATION_DECAY_RATE"] = CONTENTO_MAX_RATION_DECAY_RATE;
   result["CONTENTO_MAX_RESERVE_RATIO"] = CONTENTO_MAX_RESERVE_RATIO;
   result["CONTENTO_MAX_RUNNER_WITNESSES_HF0"] = CONTENTO_MAX_RUNNER_WITNESSES_HF0;
   result["CONTENTO_MAX_RUNNER_WITNESSES_HF17"] = CONTENTO_MAX_RUNNER_WITNESSES_HF17;
   result["CONTENTO_MAX_SHARE_SUPPLY"] = CONTENTO_MAX_SHARE_SUPPLY;
   result["CONTENTO_MAX_SIG_CHECK_DEPTH"] = CONTENTO_MAX_SIG_CHECK_DEPTH;
   result["CONTENTO_MAX_TIME_UNTIL_EXPIRATION"] = CONTENTO_MAX_TIME_UNTIL_EXPIRATION;
   result["CONTENTO_MAX_TRANSACTION_SIZE"] = CONTENTO_MAX_TRANSACTION_SIZE;
   result["CONTENTO_MAX_UNDO_HISTORY"] = CONTENTO_MAX_UNDO_HISTORY;
   result["CONTENTO_MAX_URL_LENGTH"] = CONTENTO_MAX_URL_LENGTH;
   result["CONTENTO_MAX_VOTE_CHANGES"] = CONTENTO_MAX_VOTE_CHANGES;
   result["CONTENTO_MAX_VOTED_WITNESSES_HF0"] = CONTENTO_MAX_VOTED_WITNESSES_HF0;
   result["CONTENTO_MAX_VOTED_WITNESSES_HF17"] = CONTENTO_MAX_VOTED_WITNESSES_HF17;
   result["CONTENTO_MAX_WITHDRAW_ROUTES"] = CONTENTO_MAX_WITHDRAW_ROUTES;
   result["CONTENTO_MAX_WITNESS_URL_LENGTH"] = CONTENTO_MAX_WITNESS_URL_LENGTH;
   result["CONTENTO_MIN_ACCOUNT_CREATION_FEE"] = CONTENTO_MIN_ACCOUNT_CREATION_FEE;
   result["CONTENTO_MIN_ACCOUNT_NAME_LENGTH"] = CONTENTO_MIN_ACCOUNT_NAME_LENGTH;
   result["CONTENTO_MIN_BLOCK_SIZE"] = CONTENTO_MIN_BLOCK_SIZE;
   result["CONTENTO_MIN_BLOCK_SIZE_LIMIT"] = CONTENTO_MIN_BLOCK_SIZE_LIMIT;
   result["CONTENTO_MIN_CONTENT_REWARD"] = CONTENTO_MIN_CONTENT_REWARD;
   result["CONTENTO_MIN_CURATE_REWARD"] = CONTENTO_MIN_CURATE_REWARD;
   result["CONTENTO_MIN_PERMLINK_LENGTH"] = CONTENTO_MIN_PERMLINK_LENGTH;
   result["CONTENTO_MIN_REPLY_INTERVAL"] = CONTENTO_MIN_REPLY_INTERVAL;
   result["CONTENTO_MIN_ROOT_COMMENT_INTERVAL"] = CONTENTO_MIN_ROOT_COMMENT_INTERVAL;
   result["CONTENTO_MIN_VOTE_INTERVAL_SEC"] = CONTENTO_MIN_VOTE_INTERVAL_SEC;
   result["CONTENTO_MINER_ACCOUNT"] = CONTENTO_MINER_ACCOUNT;
   result["CONTENTO_MINER_PAY_PERCENT"] = CONTENTO_MINER_PAY_PERCENT;
   result["CONTENTO_MIN_FEEDS"] = CONTENTO_MIN_FEEDS;
   result["CONTENTO_MINING_REWARD"] = CONTENTO_MINING_REWARD;
   result["CONTENTO_MINING_TIME"] = CONTENTO_MINING_TIME;
   result["CONTENTO_MIN_LIQUIDITY_REWARD"] = CONTENTO_MIN_LIQUIDITY_REWARD;
   result["CONTENTO_MIN_LIQUIDITY_REWARD_PERIOD_SEC"] = CONTENTO_MIN_LIQUIDITY_REWARD_PERIOD_SEC;
//   result["CONTENTO_MIN_PAYOUT_SBD"] = CONTENTO_MIN_PAYOUT_SBD;
   result["CONTENTO_MIN_POW_REWARD"] = CONTENTO_MIN_POW_REWARD;
   result["CONTENTO_MIN_PRODUCER_REWARD"] = CONTENTO_MIN_PRODUCER_REWARD;
   result["CONTENTO_MIN_RATION"] = CONTENTO_MIN_RATION;
   result["CONTENTO_MIN_TRANSACTION_EXPIRATION_LIMIT"] = CONTENTO_MIN_TRANSACTION_EXPIRATION_LIMIT;
   result["CONTENTO_MIN_TRANSACTION_SIZE_LIMIT"] = CONTENTO_MIN_TRANSACTION_SIZE_LIMIT;
   result["CONTENTO_MIN_UNDO_HISTORY"] = CONTENTO_MIN_UNDO_HISTORY;
   result["CONTENTO_NULL_ACCOUNT"] = CONTENTO_NULL_ACCOUNT;
   result["CONTENTO_NUM_INIT_MINERS"] = CONTENTO_NUM_INIT_MINERS;
   result["CONTENTO_ORIGINAL_MIN_ACCOUNT_CREATION_FEE"] = CONTENTO_ORIGINAL_MIN_ACCOUNT_CREATION_FEE;
   result["CONTENTO_OWNER_AUTH_HISTORY_TRACKING_START_BLOCK_NUM"] = CONTENTO_OWNER_AUTH_HISTORY_TRACKING_START_BLOCK_NUM;
   result["CONTENTO_OWNER_AUTH_RECOVERY_PERIOD"] = CONTENTO_OWNER_AUTH_RECOVERY_PERIOD;
   result["CONTENTO_OWNER_CHALLENGE_COOLDOWN"] = CONTENTO_OWNER_CHALLENGE_COOLDOWN;
   result["CONTENTO_OWNER_CHALLENGE_FEE"] = CONTENTO_OWNER_CHALLENGE_FEE;
   result["CONTENTO_OWNER_UPDATE_LIMIT"] = CONTENTO_OWNER_UPDATE_LIMIT;
   result["CONTENTO_POST_AVERAGE_WINDOW"] = CONTENTO_POST_AVERAGE_WINDOW;
   result["CONTENTO_POST_MAX_BANDWIDTH"] = CONTENTO_POST_MAX_BANDWIDTH;
   result["CONTENTO_POST_REWARD_FUND_NAME"] = CONTENTO_POST_REWARD_FUND_NAME;
   result["CONTENTO_POST_WEIGHT_CONSTANT"] = CONTENTO_POST_WEIGHT_CONSTANT;
   result["CONTENTO_POW_APR_PERCENT"] = CONTENTO_POW_APR_PERCENT;
   result["CONTENTO_PRODUCER_APR_PERCENT"] = CONTENTO_PRODUCER_APR_PERCENT;
   result["CONTENTO_PROXY_TO_SELF_ACCOUNT"] = CONTENTO_PROXY_TO_SELF_ACCOUNT;
   result["CONTENTO_SBD_INTEREST_COMPOUND_INTERVAL_SEC"] = CONTENTO_SBD_INTEREST_COMPOUND_INTERVAL_SEC;
   result["CONTENTO_SECONDS_PER_YEAR"] = CONTENTO_SECONDS_PER_YEAR;
   result["CONTENTO_RECENT_RSHARES_DECAY_RATE_HF19"] = CONTENTO_RECENT_RSHARES_DECAY_RATE_HF19;
   result["CONTENTO_RECENT_RSHARES_DECAY_RATE_HF17"] = CONTENTO_RECENT_RSHARES_DECAY_RATE_HF17;
   result["CONTENTO_REVERSE_AUCTION_WINDOW_SECONDS"] = CONTENTO_REVERSE_AUCTION_WINDOW_SECONDS;
   result["CONTENTO_ROOT_POST_PARENT"] = CONTENTO_ROOT_POST_PARENT;
   result["CONTENTO_SAVINGS_WITHDRAW_REQUEST_LIMIT"] = CONTENTO_SAVINGS_WITHDRAW_REQUEST_LIMIT;
   result["CONTENTO_SAVINGS_WITHDRAW_TIME"] = CONTENTO_SAVINGS_WITHDRAW_TIME;
//   result["CONTENTO_SBD_START_PERCENT"] = CONTENTO_SBD_START_PERCENT;
//   result["CONTENTO_SBD_STOP_PERCENT"] = CONTENTO_SBD_STOP_PERCENT;
   result["CONTENTO_SECOND_CASHOUT_WINDOW"] = CONTENTO_SECOND_CASHOUT_WINDOW;
   result["CONTENTO_SOFT_MAX_COMMENT_DEPTH"] = CONTENTO_SOFT_MAX_COMMENT_DEPTH;
   result["CONTENTO_START_MINER_VOTING_BLOCK"] = CONTENTO_START_MINER_VOTING_BLOCK;
   result["CONTENTO_START_VESTING_BLOCK"] = CONTENTO_START_VESTING_BLOCK;
   result["CONTENTO_SYMBOL"] = CONTENTO_SYMBOL;
   result["CONTENTO_TEMP_ACCOUNT"] = CONTENTO_TEMP_ACCOUNT;
//    result["CONTENTO_UPVOTE_LOCKOUT_HF7"] = CONTENTO_UPVOTE_LOCKOUT_HF7;
   result["CONTENTO_UPVOTE_LOCKOUT_HF17"] = CONTENTO_UPVOTE_LOCKOUT_HF17;
   result["CONTENTO_VESTING_FUND_PERCENT"] = CONTENTO_VESTING_FUND_PERCENT;
   result["CONTENTO_VESTING_WITHDRAW_INTERVALS"] = CONTENTO_VESTING_WITHDRAW_INTERVALS;
   result["CONTENTO_VESTING_WITHDRAW_INTERVALS_PRE_HF_16"] = CONTENTO_VESTING_WITHDRAW_INTERVALS_PRE_HF_16;
   result["CONTENTO_VESTING_WITHDRAW_INTERVAL_SECONDS"] = CONTENTO_VESTING_WITHDRAW_INTERVAL_SECONDS;
   result["CONTENTO_VOTE_CHANGE_LOCKOUT_PERIOD"] = CONTENTO_VOTE_CHANGE_LOCKOUT_PERIOD;
   result["CONTENTO_VOTE_DUST_THRESHOLD"] = CONTENTO_VOTE_DUST_THRESHOLD;
   result["CONTENTO_VOTE_REGENERATION_SECONDS"] = CONTENTO_VOTE_REGENERATION_SECONDS;
   result["COS_SYMBOL"] = COS_SYMBOL;
//   result["STMD_SYMBOL"] = STMD_SYMBOL;
   result["VESTS_SYMBOL"] = VESTS_SYMBOL;
   result["VIRTUAL_SCHEDULE_LAP_LENGTH"] = VIRTUAL_SCHEDULE_LAP_LENGTH;
   result["VIRTUAL_SCHEDULE_LAP_LENGTH2"] = VIRTUAL_SCHEDULE_LAP_LENGTH2;
   result["PER_BLOCK_PRODUCT_COS"] = PER_BLOCK_PRODUCT_COS;
   result["MAX_UNCOMPRESSION_SIZE"] = MAX_UNCOMPRESSION_SIZE;

   return result;
}

} } // contento::protocol
