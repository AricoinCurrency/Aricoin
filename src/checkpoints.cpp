// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Copyright (c) 2014-2020 Aricoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

	// Genesis - https://chainz.cryptoid.info/ari/tx.dws?1.htm
	// Reference - https://chainz.cryptoid.info/ari/block.dws?1.htm
    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
        (     0, uint256("0x6df743739be39a62277fb5f95dd9bb25c68ac03fd1293183f000315bd1c87e0f"))
    (  1000, uint256("0xb471022e6ecb336a3d0327f00ef417fa1bc79652299f3015f553f6c0086861ac"))
    ( 10000, uint256("0x8bbdc0e43fffeb9dfb2fdd2b590236e3a5693c8a125a689263bf84244899d6e5"))
    ( 20000, uint256("0x27a654d36a38c84f2458f6f6945016a64b7742b805868ea27a87d22635c9a743"))
    ( 30000, uint256("0x0e5f4c07df09950a3e6dff3a88e457bdf665362b9f0efd7959fd74e20a0e0b1b"))
    ( 60000, uint256("0x7367e3019962b923d93b1c356a434caf645a1b9a641c16435bd53dc68d0af051"))
    ( 100000, uint256("0x20478e6baeea384c9466750149cd1e1acca0a5b9f5c6af73e5e220680f3cf62c"))
    ( 200000, uint256("0x45464baa2f397324f666a4b44a72d6aaa61597f6838aa26900cbee736a8ef4d0"))
    ( 300000, uint256("0xb89ad628aee7f15446377e468231021dcb4b4b71e1732cce6d5cdc29b11c562b"))
    ( 400000, uint256("0xd3f8a5b103975b40fc0e819ff892ecca6de8271ab55e0237d15f1fce16c02a34"))
    ( 500000, uint256("0x6b8f3e10370a9f3c141d0c1c765e30f2c8bc20d358c0c0bfc47a8f437ce16730"))
    ( 600000, uint256("0x40f33ccf4f7cf79970d253675dee0fa782ad88a9f24db886c45b069085d24d01"))
    ( 700000, uint256("0x84c6884f04b41837bf0cd19bf5bba2138169a5e17a43c5757f874e64fd3d3b69"))
    ( 800000, uint256("0xd7708fb16e97d5bc8c86c092c7fff65e781d045d65901932951a3defeaaee2eb"))
    ( 888000, uint256("0x747f233739b5e2cb09958db98691f24a865473ae4fc88f50278405d6a7f99c49"))
    ( 888100, uint256("0xcabf41533c9b70b3091cd4a94dd0a2b84b13020840ab4b2303762598daf8d483"))
;


    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
	
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;
	
        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
		
        return NULL;
    }
}
