// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Curium developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "assert.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

//
// Main network
//

unsigned int pnSeed[] =
{
    0xb32b80ef, 0x807f6aeb, 0x259dfa0a, 0xa2d16323, 0x6c3dd236,
    0xacf50584, 0x2ea2420a, 0x4e6db2c3, 0x8a80a95e, 0x340b8de5,
    0x253b153a, 0x2e69760f, 0xb2217edd, 0x68ec1783, 0x6c3dd125,
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x7d;
        pchMessageStart[1] = 0x5d;
        pchMessageStart[2] = 0xa1;
        pchMessageStart[3] = 0xea;
        vAlertPubKey = ParseHex("048240a8748a80a286b270ba1abc25ced4f2ce5a7847b3610ea3c065131abe3de2a8512ed5ea86320824683fc081835ba019214973e677acd1244f6d0571fc5103");
        nDefaultPort = 9999;
        nRPCPort = 9645;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);  // Curium starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;

        // Genesis block
        const char* pszTimestamp = "Wired 12/Jan/2018 The Grand Experiment Goes Live: I ate my first yam";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("043384710fa689ad5023690c80f3addf8f13f8d45b8c8ab357c96ddae9fac46bd8996b10f4d4604fa08dce601aac4997abcedf92f1fabc21b179c45070ac7b03a9") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1515982333;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 113992;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000e784f88ffd07483e5e2786e002a780d35dfd4142c8e70c43fb7bb2af937"));
        assert(genesis.hashMerkleRoot == uint256("0x22f17ff105937d2914cfff2d213006a9327b8aff76ef59e3cbbe0293e453342e"));

        vSeeds.push_back(CDNSSeedData("curium1", "207.246.120.137"));
        vSeeds.push_back(CDNSSeedData("curium2", "45.32.214.107"));
        vSeeds.push_back(CDNSSeedData("1stdnsseedforcurium", "dnsseed.mrmetech.me"));
        

        base58Prefixes[PUBKEY_ADDRESS] = list_of( 28);                    // Curium addresses start with 'X'
        base58Prefixes[SCRIPT_ADDRESS] = list_of( 16);                    // Curium script addresses start with '7'
        base58Prefixes[SECRET_KEY] =     list_of(204);                    // Curium private keys start with '7' or 'X'
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x02)(0xFE)(0x52)(0xF8); // Curium BIP32 pubkeys start with 'drkv'
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x02)(0xFE)(0x52)(0xCC); // Curium BIP32 prvkeys start with 'drkp'
        base58Prefixes[EXT_COIN_TYPE]  = list_of(0x80000005);             // Curium BIP44 coin type is '5'

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' of between one and two
            // weeks ago.
            const int64_t nOneWeek = 7*24*60*60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
            vFixedSeeds.push_back(addr);
        }
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x1b;
        pchMessageStart[1] = 0x12;
        pchMessageStart[2] = 0xaa;
        pchMessageStart[3] = 0xee;

        vAlertPubKey = ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f");
        nDefaultPort = 19999;
        nRPCPort = 19998;
        strDataDir = "testnet3";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1520026653;
        genesis.nNonce = 1200555;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000049acfc15e46e990e890ed8263afa5b8ba9f106bfc277070a93117139be8"));

        vFixedSeeds.clear();
        vSeeds.clear();
        /*vSeeds.push_back(CDNSSeedData("curiumpay.io", "testnet-seed.curiumpay.io"));
        vSeeds.push_back(CDNSSeedData("curium.qa", "testnet-seed.curium.qa"));
        *///legacy seeders
        vSeeds.push_back(CDNSSeedData("darkcoin.io",  "testnet-seed.mrmetech.me"));
        

        base58Prefixes[PUBKEY_ADDRESS] = list_of(139);                    // Testnet curium addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = list_of( 19);                    // Testnet curium script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY]     = list_of(239);                    // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x3a)(0x80)(0x61)(0xa0); // Testnet curium BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x3a)(0x80)(0x58)(0x37); // Testnet curium BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_COIN_TYPE]  = list_of(0x80000001);             // Testnet curium BIP44 coin type is '5' (All coin's testnet default)
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xcc;
        pchMessageStart[1] = 0xb5;
        pchMessageStart[2] = 0xe9;
        pchMessageStart[3] = 0xfe;
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1520026653;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 0;
        nDefaultPort = 19994;
        strDataDir = "regtest";

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x1c39e4202d18fe0b8841e9282837378ae9b5e92711a5e942eb2f4b621c8c6253"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
