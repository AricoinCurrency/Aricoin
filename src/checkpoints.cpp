// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Copyright (c) 2014 Aricoin Developers
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

	// no checkpoint now, can be added in later releases
    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
            (     0, uint256("0x6df743739be39a62277fb5f95dd9bb25c68ac03fd1293183f000315bd1c87e0f"))
            (  1000, uint256("0xb471022e6ecb336a3d0327f00ef417fa1bc79652299f3015f553f6c0086861ac"))
            ( 10000, uint256("0x8bbdc0e43fffeb9dfb2fdd2b590236e3a5693c8a125a689263bf84244899d6e5"))
            ( 20000, uint256("0x27a654d36a38c84f2458f6f6945016a64b7742b805868ea27a87d22635c9a743"))
            ( 30000, uint256("0x0e5f4c07df09950a3e6dff3a88e457bdf665362b9f0efd7959fd74e20a0e0b1b"))
            ( 40000, uint256("0x25b857bcd89ec65bc175d321541ee6f2927d510d5c9c00486ab539d1b50c1a1e"))
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
