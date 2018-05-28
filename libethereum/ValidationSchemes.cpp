/*
    This file is part of cpp-ethereum.

    cpp-ethereum is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    cpp-ethereum is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with cpp-ethereum.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <string>
#include <libdevcore/JsonUtils.h>
#include "ValidationSchemes.h"

using namespace std;
using namespace dev;
namespace js = json_spirit;

namespace dev {
namespace eth {
namespace validation {

string const c_sealEngine = "sealEngine";
string const c_params = "params";
string const c_genesis = "genesis";
string const c_accounts = "accounts";
string const c_balance = "balance";
string const c_wei = "wei";
string const c_finney = "finney";
string const c_author = "author";
string const c_coinbase = "coinbase";
string const c_nonce = "nonce";
string const c_gasLimit = "gasLimit";
string const c_timestamp = "timestamp";
string const c_difficulty = "difficulty";
string const c_extraData = "extraData";
string const c_mixHash = "mixHash";
string const c_parentHash = "parentHash";
string const c_precompiled = "precompiled";
string const c_code = "code";
string const c_storage = "storage";
string const c_gasUsed = "gasUsed";
string const c_codeFromFile = "codeFromFile";  ///< A file containg a code as bytes.
string const c_shouldnotexist = "shouldnotexist";

string const c_minGasLimit = "minGasLimit";
string const c_maxGasLimit = "maxGasLimit";
string const c_gasLimitBoundDivisor = "gasLimitBoundDivisor";
string const c_homesteadForkBlock = "homesteadForkBlock";
string const c_daoHardforkBlock = "daoHardforkBlock";
string const c_EIP150ForkBlock = "EIP150ForkBlock";
string const c_EIP158ForkBlock = "EIP158ForkBlock";
string const c_byzantiumForkBlock = "byzantiumForkBlock";
string const c_eWASMForkBlock = "eWASMForkBlock";
string const c_constantinopleForkBlock = "constantinopleForkBlock";
string const c_accountStartNonce = "accountStartNonce";
string const c_maximumExtraDataSize = "maximumExtraDataSize";
string const c_tieBreakingGas = "tieBreakingGas";
string const c_blockReward = "blockReward";
string const c_difficultyBoundDivisor = "difficultyBoundDivisor";
string const c_minimumDifficulty = "minimumDifficulty";
string const c_durationLimit = "durationLimit";
string const c_chainID = "chainID";
string const c_networkID = "networkID";
string const c_allowFutureBlocks = "allowFutureBlocks";

void validateConfigJson(js::mObject const& _obj)
{
    requireJsonFields(_obj, "ChainParams::loadConfig",
        {{c_sealEngine, {json_spirit::str_type}},
         {c_params, {json_spirit::obj_type}},
         {c_genesis, {json_spirit::obj_type}},
         {c_accounts, {json_spirit::obj_type}}});

    requireJsonFields(_obj.at(c_genesis).get_obj(), "ChainParams::loadConfig::genesis",
        {{c_author, {json_spirit::str_type}},
         {c_nonce, {json_spirit::str_type}},
         {c_gasLimit, {json_spirit::str_type}},
         {c_timestamp, {json_spirit::str_type}},
         {c_difficulty, {json_spirit::str_type}},
         {c_extraData, {json_spirit::str_type}},
         {c_mixHash, {json_spirit::str_type}}},
         {c_parentHash});   // allowed field, but not required

    js::mObject const& accounts = _obj.at(c_accounts).get_obj();
    for (auto const& acc : accounts)
        validateAccountObj(acc.second.get_obj());
}

void validateAccountMapObj(js::mObject const& _obj)
{
    // A map object with possibly defined fields
    requireJsonFields(_obj, "validateAccountMapObj", {},
            {c_storage, c_balance, c_nonce, c_code, c_precompiled, c_shouldnotexist, c_wei});
}

void validateAccountObj(js::mObject const& _obj)
{
    if (_obj.count(c_precompiled))
    {
        // A precompiled contract
        requireJsonFields(_obj, "validateAccountObj",
            {{c_precompiled, {json_spirit::obj_type}}},
            {c_wei});
    }
    else if (_obj.size() == 1)
    {
        // A genesis account with only balance set
        if (_obj.count(c_balance))
            requireJsonFields(_obj, "validateAccountObj", {{c_balance, {json_spirit::str_type}}});
        else
            requireJsonFields(_obj, "validateAccountObj", {{c_wei, {json_spirit::str_type}}});
    }
    else
    {
        // A standart account with all fields
        requireJsonFields(_obj, "validateAccountObj",
            {{c_code, {json_spirit::str_type}},
             {c_nonce, {json_spirit::str_type}},
             {c_storage, {json_spirit::obj_type}},
             {c_balance, {json_spirit::str_type}}});
    }
}

}}}
