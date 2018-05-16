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

   result["SBD_SYMBOL"] = SBD_SYMBOL;
   result["STEEMIT_100_PERCENT"] = STEEMIT_100_PERCENT;
   result["STEEMIT_1_PERCENT"] = STEEMIT_1_PERCENT;
   result["STEEMIT_1_TENTH_PERCENT"] = STEEMIT_1_TENTH_PERCENT;
   result["STEEMIT_ACCOUNT_RECOVERY_REQUEST_EXPIRATION_PERIOD"] = STEEMIT_ACCOUNT_RECOVERY_REQUEST_EXPIRATION_PERIOD;
   result["STEEMIT_ACTIVE_CHALLENGE_COOLDOWN"] = STEEMIT_ACTIVE_CHALLENGE_COOLDOWN;
   result["STEEMIT_ACTIVE_CHALLENGE_FEE"] = STEEMIT_ACTIVE_CHALLENGE_FEE;
   result["STEEMIT_ADDRESS_PREFIX"] = STEEMIT_ADDRESS_PREFIX;
   result["STEEMIT_APR_PERCENT_MULTIPLY_PER_BLOCK"] = STEEMIT_APR_PERCENT_MULTIPLY_PER_BLOCK;
   result["STEEMIT_APR_PERCENT_MULTIPLY_PER_HOUR"] = STEEMIT_APR_PERCENT_MULTIPLY_PER_HOUR;
   result["STEEMIT_APR_PERCENT_MULTIPLY_PER_ROUND"] = STEEMIT_APR_PERCENT_MULTIPLY_PER_ROUND;
   result["STEEMIT_APR_PERCENT_SHIFT_PER_BLOCK"] = STEEMIT_APR_PERCENT_SHIFT_PER_BLOCK;
   result["STEEMIT_APR_PERCENT_SHIFT_PER_HOUR"] = STEEMIT_APR_PERCENT_SHIFT_PER_HOUR;
   result["STEEMIT_APR_PERCENT_SHIFT_PER_ROUND"] = STEEMIT_APR_PERCENT_SHIFT_PER_ROUND;
   result["STEEMIT_BANDWIDTH_AVERAGE_WINDOW_SECONDS"] = STEEMIT_BANDWIDTH_AVERAGE_WINDOW_SECONDS;
   result["STEEMIT_BANDWIDTH_PRECISION"] = STEEMIT_BANDWIDTH_PRECISION;
   result["STEEMIT_BLOCKCHAIN_PRECISION"] = STEEMIT_BLOCKCHAIN_PRECISION;
   result["STEEMIT_BLOCKCHAIN_PRECISION_DIGITS"] = STEEMIT_BLOCKCHAIN_PRECISION_DIGITS;
   result["STEEMIT_BLOCKCHAIN_HARDFORK_VERSION"] = STEEMIT_BLOCKCHAIN_HARDFORK_VERSION;
   result["STEEMIT_BLOCKCHAIN_VERSION"] = STEEMIT_BLOCKCHAIN_VERSION;
   result["STEEMIT_BLOCK_INTERVAL"] = STEEMIT_BLOCK_INTERVAL;
   result["STEEMIT_BLOCKS_PER_DAY"] = STEEMIT_BLOCKS_PER_DAY;
   result["STEEMIT_BLOCKS_PER_HOUR"] = STEEMIT_BLOCKS_PER_HOUR;
   result["STEEMIT_BLOCKS_PER_YEAR"] = STEEMIT_BLOCKS_PER_YEAR;
   result["STEEMIT_CASHOUT_WINDOW_SECONDS"] = STEEMIT_CASHOUT_WINDOW_SECONDS;
   result["STEEMIT_CASHOUT_WINDOW_SECONDS_PRE_HF12"] = STEEMIT_CASHOUT_WINDOW_SECONDS_PRE_HF12;
   result["STEEMIT_CASHOUT_WINDOW_SECONDS_PRE_HF17"] = STEEMIT_CASHOUT_WINDOW_SECONDS_PRE_HF17;
   result["STEEMIT_CHAIN_ID"] = STEEMIT_CHAIN_ID;
   result["STEEMIT_COMMENT_REWARD_FUND_NAME"] = STEEMIT_COMMENT_REWARD_FUND_NAME;
   result["STEEMIT_CONTENT_APR_PERCENT"] = STEEMIT_CONTENT_APR_PERCENT;
   result["STEEMIT_CONTENT_CONSTANT_HF0"] = STEEMIT_CONTENT_CONSTANT_HF0;
   result["STEEMIT_CONTENT_REWARD_PERCENT"] = STEEMIT_CONTENT_REWARD_PERCENT;
   result["STEEMIT_CONVERSION_DELAY"] = STEEMIT_CONVERSION_DELAY;
   result["STEEMIT_CONVERSION_DELAY_PRE_HF_16"] = STEEMIT_CONVERSION_DELAY_PRE_HF_16;
   result["STEEMIT_CREATE_ACCOUNT_DELEGATION_RATIO"] = STEEMIT_CREATE_ACCOUNT_DELEGATION_RATIO;
   result["STEEMIT_CREATE_ACCOUNT_DELEGATION_TIME"] = STEEMIT_CREATE_ACCOUNT_DELEGATION_TIME;
   result["STEEMIT_CREATE_ACCOUNT_WITH_STEEM_MODIFIER"] = STEEMIT_CREATE_ACCOUNT_WITH_STEEM_MODIFIER;
   result["STEEMIT_CURATE_APR_PERCENT"] = STEEMIT_CURATE_APR_PERCENT;
   result["STEEMIT_DEFAULT_SBD_INTEREST_RATE"] = STEEMIT_DEFAULT_SBD_INTEREST_RATE;
   result["STEEMIT_EQUIHASH_K"] = STEEMIT_EQUIHASH_K;
   result["STEEMIT_EQUIHASH_N"] = STEEMIT_EQUIHASH_N;
   result["STEEMIT_FEED_HISTORY_WINDOW"] = STEEMIT_FEED_HISTORY_WINDOW;
   result["STEEMIT_FEED_HISTORY_WINDOW_PRE_HF_16"] = STEEMIT_FEED_HISTORY_WINDOW_PRE_HF_16;
   result["STEEMIT_FEED_INTERVAL_BLOCKS"] = STEEMIT_FEED_INTERVAL_BLOCKS;
   result["STEEMIT_FREE_TRANSACTIONS_WITH_NEW_ACCOUNT"] = STEEMIT_FREE_TRANSACTIONS_WITH_NEW_ACCOUNT;
   result["STEEMIT_GENESIS_TIME"] = STEEMIT_GENESIS_TIME;
   result["STEEMIT_HARDFORK_REQUIRED_WITNESSES"] = STEEMIT_HARDFORK_REQUIRED_WITNESSES;
   result["STEEMIT_INFLATION_NARROWING_PERIOD"] = STEEMIT_INFLATION_NARROWING_PERIOD;
   result["STEEMIT_INFLATION_RATE_START_PERCENT"] = STEEMIT_INFLATION_RATE_START_PERCENT;
   result["STEEMIT_INFLATION_RATE_STOP_PERCENT"] = STEEMIT_INFLATION_RATE_STOP_PERCENT;
   result["STEEMIT_INIT_MINER_NAME"] = STEEMIT_INIT_MINER_NAME;
   result["STEEMIT_INIT_PUBLIC_KEY_STR"] = STEEMIT_INIT_PUBLIC_KEY_STR;
#if 0
   // do not expose private key, period.
   // we need this line present but inactivated so CI check for all constants in config.hpp doesn't complain.
   result["STEEMIT_INIT_PRIVATE_KEY"] = STEEMIT_INIT_PRIVATE_KEY;
#endif
   result["STEEMIT_INIT_SUPPLY"] = STEEMIT_INIT_SUPPLY;
   result["STEEMIT_INIT_TIME"] = STEEMIT_INIT_TIME;
   result["STEEMIT_IRREVERSIBLE_THRESHOLD"] = STEEMIT_IRREVERSIBLE_THRESHOLD;
   result["STEEMIT_LIQUIDITY_APR_PERCENT"] = STEEMIT_LIQUIDITY_APR_PERCENT;
   result["STEEMIT_LIQUIDITY_REWARD_BLOCKS"] = STEEMIT_LIQUIDITY_REWARD_BLOCKS;
   result["STEEMIT_LIQUIDITY_REWARD_PERIOD_SEC"] = STEEMIT_LIQUIDITY_REWARD_PERIOD_SEC;
   result["STEEMIT_LIQUIDITY_TIMEOUT_SEC"] = STEEMIT_LIQUIDITY_TIMEOUT_SEC;
   result["STEEMIT_MAX_ACCOUNT_NAME_LENGTH"] = STEEMIT_MAX_ACCOUNT_NAME_LENGTH;
   result["STEEMIT_MAX_ACCOUNT_WITNESS_VOTES"] = STEEMIT_MAX_ACCOUNT_WITNESS_VOTES;
   result["STEEMIT_MAX_ASSET_WHITELIST_AUTHORITIES"] = STEEMIT_MAX_ASSET_WHITELIST_AUTHORITIES;
   result["STEEMIT_MAX_AUTHORITY_MEMBERSHIP"] = STEEMIT_MAX_AUTHORITY_MEMBERSHIP;
   result["STEEMIT_MAX_BLOCK_SIZE"] = STEEMIT_MAX_BLOCK_SIZE;
   result["STEEMIT_MAX_CASHOUT_WINDOW_SECONDS"] = STEEMIT_MAX_CASHOUT_WINDOW_SECONDS;
   result["STEEMIT_MAX_COMMENT_DEPTH"] = STEEMIT_MAX_COMMENT_DEPTH;
   result["STEEMIT_MAX_COMMENT_DEPTH_PRE_HF17"] = STEEMIT_MAX_COMMENT_DEPTH_PRE_HF17;
   result["STEEMIT_MAX_FEED_AGE_SECONDS"] = STEEMIT_MAX_FEED_AGE_SECONDS;
   result["STEEMIT_MAX_INSTANCE_ID"] = STEEMIT_MAX_INSTANCE_ID;
   result["STEEMIT_MAX_MEMO_SIZE"] = STEEMIT_MAX_MEMO_SIZE;
   result["STEEMIT_MAX_WITNESSES"] = STEEMIT_MAX_WITNESSES;
   result["STEEMIT_MAX_MINER_WITNESSES_HF0"] = STEEMIT_MAX_MINER_WITNESSES_HF0;
   result["STEEMIT_MAX_MINER_WITNESSES_HF17"] = STEEMIT_MAX_MINER_WITNESSES_HF17;
   result["STEEMIT_MAX_PERMLINK_LENGTH"] = STEEMIT_MAX_PERMLINK_LENGTH;
   result["STEEMIT_MAX_PROXY_RECURSION_DEPTH"] = STEEMIT_MAX_PROXY_RECURSION_DEPTH;
   result["STEEMIT_MAX_RATION_DECAY_RATE"] = STEEMIT_MAX_RATION_DECAY_RATE;
   result["STEEMIT_MAX_RESERVE_RATIO"] = STEEMIT_MAX_RESERVE_RATIO;
   result["STEEMIT_MAX_RUNNER_WITNESSES_HF0"] = STEEMIT_MAX_RUNNER_WITNESSES_HF0;
   result["STEEMIT_MAX_RUNNER_WITNESSES_HF17"] = STEEMIT_MAX_RUNNER_WITNESSES_HF17;
   result["STEEMIT_MAX_SHARE_SUPPLY"] = STEEMIT_MAX_SHARE_SUPPLY;
   result["STEEMIT_MAX_SIG_CHECK_DEPTH"] = STEEMIT_MAX_SIG_CHECK_DEPTH;
   result["STEEMIT_MAX_TIME_UNTIL_EXPIRATION"] = STEEMIT_MAX_TIME_UNTIL_EXPIRATION;
   result["STEEMIT_MAX_TRANSACTION_SIZE"] = STEEMIT_MAX_TRANSACTION_SIZE;
   result["STEEMIT_MAX_UNDO_HISTORY"] = STEEMIT_MAX_UNDO_HISTORY;
   result["STEEMIT_MAX_URL_LENGTH"] = STEEMIT_MAX_URL_LENGTH;
   result["STEEMIT_MAX_VOTE_CHANGES"] = STEEMIT_MAX_VOTE_CHANGES;
   result["STEEMIT_MAX_VOTED_WITNESSES_HF0"] = STEEMIT_MAX_VOTED_WITNESSES_HF0;
   result["STEEMIT_MAX_VOTED_WITNESSES_HF17"] = STEEMIT_MAX_VOTED_WITNESSES_HF17;
   result["STEEMIT_MAX_WITHDRAW_ROUTES"] = STEEMIT_MAX_WITHDRAW_ROUTES;
   result["STEEMIT_MAX_WITNESS_URL_LENGTH"] = STEEMIT_MAX_WITNESS_URL_LENGTH;
   result["STEEMIT_MIN_ACCOUNT_CREATION_FEE"] = STEEMIT_MIN_ACCOUNT_CREATION_FEE;
   result["STEEMIT_MIN_ACCOUNT_NAME_LENGTH"] = STEEMIT_MIN_ACCOUNT_NAME_LENGTH;
   result["STEEMIT_MIN_BLOCK_SIZE"] = STEEMIT_MIN_BLOCK_SIZE;
   result["STEEMIT_MIN_BLOCK_SIZE_LIMIT"] = STEEMIT_MIN_BLOCK_SIZE_LIMIT;
   result["STEEMIT_MIN_CONTENT_REWARD"] = STEEMIT_MIN_CONTENT_REWARD;
   result["STEEMIT_MIN_CURATE_REWARD"] = STEEMIT_MIN_CURATE_REWARD;
   result["STEEMIT_MIN_PERMLINK_LENGTH"] = STEEMIT_MIN_PERMLINK_LENGTH;
   result["STEEMIT_MIN_REPLY_INTERVAL"] = STEEMIT_MIN_REPLY_INTERVAL;
   result["STEEMIT_MIN_ROOT_COMMENT_INTERVAL"] = STEEMIT_MIN_ROOT_COMMENT_INTERVAL;
   result["STEEMIT_MIN_VOTE_INTERVAL_SEC"] = STEEMIT_MIN_VOTE_INTERVAL_SEC;
   result["STEEMIT_MINER_ACCOUNT"] = STEEMIT_MINER_ACCOUNT;
   result["STEEMIT_MINER_PAY_PERCENT"] = STEEMIT_MINER_PAY_PERCENT;
   result["STEEMIT_MIN_FEEDS"] = STEEMIT_MIN_FEEDS;
   result["STEEMIT_MINING_REWARD"] = STEEMIT_MINING_REWARD;
   result["STEEMIT_MINING_TIME"] = STEEMIT_MINING_TIME;
   result["STEEMIT_MIN_LIQUIDITY_REWARD"] = STEEMIT_MIN_LIQUIDITY_REWARD;
   result["STEEMIT_MIN_LIQUIDITY_REWARD_PERIOD_SEC"] = STEEMIT_MIN_LIQUIDITY_REWARD_PERIOD_SEC;
   result["STEEMIT_MIN_PAYOUT_SBD"] = STEEMIT_MIN_PAYOUT_SBD;
   result["STEEMIT_MIN_POW_REWARD"] = STEEMIT_MIN_POW_REWARD;
   result["STEEMIT_MIN_PRODUCER_REWARD"] = STEEMIT_MIN_PRODUCER_REWARD;
   result["STEEMIT_MIN_RATION"] = STEEMIT_MIN_RATION;
   result["STEEMIT_MIN_TRANSACTION_EXPIRATION_LIMIT"] = STEEMIT_MIN_TRANSACTION_EXPIRATION_LIMIT;
   result["STEEMIT_MIN_TRANSACTION_SIZE_LIMIT"] = STEEMIT_MIN_TRANSACTION_SIZE_LIMIT;
   result["STEEMIT_MIN_UNDO_HISTORY"] = STEEMIT_MIN_UNDO_HISTORY;
   result["STEEMIT_NULL_ACCOUNT"] = STEEMIT_NULL_ACCOUNT;
   result["STEEMIT_NUM_INIT_MINERS"] = STEEMIT_NUM_INIT_MINERS;
   result["STEEMIT_ORIGINAL_MIN_ACCOUNT_CREATION_FEE"] = STEEMIT_ORIGINAL_MIN_ACCOUNT_CREATION_FEE;
   result["STEEMIT_OWNER_AUTH_HISTORY_TRACKING_START_BLOCK_NUM"] = STEEMIT_OWNER_AUTH_HISTORY_TRACKING_START_BLOCK_NUM;
   result["STEEMIT_OWNER_AUTH_RECOVERY_PERIOD"] = STEEMIT_OWNER_AUTH_RECOVERY_PERIOD;
   result["STEEMIT_OWNER_CHALLENGE_COOLDOWN"] = STEEMIT_OWNER_CHALLENGE_COOLDOWN;
   result["STEEMIT_OWNER_CHALLENGE_FEE"] = STEEMIT_OWNER_CHALLENGE_FEE;
   result["STEEMIT_OWNER_UPDATE_LIMIT"] = STEEMIT_OWNER_UPDATE_LIMIT;
   result["STEEMIT_POST_AVERAGE_WINDOW"] = STEEMIT_POST_AVERAGE_WINDOW;
   result["STEEMIT_POST_MAX_BANDWIDTH"] = STEEMIT_POST_MAX_BANDWIDTH;
   result["STEEMIT_POST_REWARD_FUND_NAME"] = STEEMIT_POST_REWARD_FUND_NAME;
   result["STEEMIT_POST_WEIGHT_CONSTANT"] = STEEMIT_POST_WEIGHT_CONSTANT;
   result["STEEMIT_POW_APR_PERCENT"] = STEEMIT_POW_APR_PERCENT;
   result["STEEMIT_PRODUCER_APR_PERCENT"] = STEEMIT_PRODUCER_APR_PERCENT;
   result["STEEMIT_PROXY_TO_SELF_ACCOUNT"] = STEEMIT_PROXY_TO_SELF_ACCOUNT;
   result["STEEMIT_SBD_INTEREST_COMPOUND_INTERVAL_SEC"] = STEEMIT_SBD_INTEREST_COMPOUND_INTERVAL_SEC;
   result["STEEMIT_SECONDS_PER_YEAR"] = STEEMIT_SECONDS_PER_YEAR;
   result["STEEMIT_RECENT_RSHARES_DECAY_RATE_HF19"] = STEEMIT_RECENT_RSHARES_DECAY_RATE_HF19;
   result["STEEMIT_RECENT_RSHARES_DECAY_RATE_HF17"] = STEEMIT_RECENT_RSHARES_DECAY_RATE_HF17;
   result["STEEMIT_REVERSE_AUCTION_WINDOW_SECONDS"] = STEEMIT_REVERSE_AUCTION_WINDOW_SECONDS;
   result["STEEMIT_ROOT_POST_PARENT"] = STEEMIT_ROOT_POST_PARENT;
   result["STEEMIT_SAVINGS_WITHDRAW_REQUEST_LIMIT"] = STEEMIT_SAVINGS_WITHDRAW_REQUEST_LIMIT;
   result["STEEMIT_SAVINGS_WITHDRAW_TIME"] = STEEMIT_SAVINGS_WITHDRAW_TIME;
   result["STEEMIT_SBD_START_PERCENT"] = STEEMIT_SBD_START_PERCENT;
   result["STEEMIT_SBD_STOP_PERCENT"] = STEEMIT_SBD_STOP_PERCENT;
   result["STEEMIT_SECOND_CASHOUT_WINDOW"] = STEEMIT_SECOND_CASHOUT_WINDOW;
   result["STEEMIT_SOFT_MAX_COMMENT_DEPTH"] = STEEMIT_SOFT_MAX_COMMENT_DEPTH;
   result["STEEMIT_START_MINER_VOTING_BLOCK"] = STEEMIT_START_MINER_VOTING_BLOCK;
   result["STEEMIT_START_VESTING_BLOCK"] = STEEMIT_START_VESTING_BLOCK;
   result["STEEMIT_SYMBOL"] = STEEMIT_SYMBOL;
   result["STEEMIT_TEMP_ACCOUNT"] = STEEMIT_TEMP_ACCOUNT;
   result["STEEMIT_UPVOTE_LOCKOUT_HF7"] = STEEMIT_UPVOTE_LOCKOUT_HF7;
   result["STEEMIT_UPVOTE_LOCKOUT_HF17"] = STEEMIT_UPVOTE_LOCKOUT_HF17;
   result["STEEMIT_VESTING_FUND_PERCENT"] = STEEMIT_VESTING_FUND_PERCENT;
   result["STEEMIT_VESTING_WITHDRAW_INTERVALS"] = STEEMIT_VESTING_WITHDRAW_INTERVALS;
   result["STEEMIT_VESTING_WITHDRAW_INTERVALS_PRE_HF_16"] = STEEMIT_VESTING_WITHDRAW_INTERVALS_PRE_HF_16;
   result["STEEMIT_VESTING_WITHDRAW_INTERVAL_SECONDS"] = STEEMIT_VESTING_WITHDRAW_INTERVAL_SECONDS;
   result["STEEMIT_VOTE_CHANGE_LOCKOUT_PERIOD"] = STEEMIT_VOTE_CHANGE_LOCKOUT_PERIOD;
   result["STEEMIT_VOTE_DUST_THRESHOLD"] = STEEMIT_VOTE_DUST_THRESHOLD;
   result["STEEMIT_VOTE_REGENERATION_SECONDS"] = STEEMIT_VOTE_REGENERATION_SECONDS;
   result["STEEM_SYMBOL"] = STEEM_SYMBOL;
   result["STMD_SYMBOL"] = STMD_SYMBOL;
   result["VESTS_SYMBOL"] = VESTS_SYMBOL;
   result["VIRTUAL_SCHEDULE_LAP_LENGTH"] = VIRTUAL_SCHEDULE_LAP_LENGTH;
   result["VIRTUAL_SCHEDULE_LAP_LENGTH2"] = VIRTUAL_SCHEDULE_LAP_LENGTH2;

   return result;
}

} } // contento::protocol
