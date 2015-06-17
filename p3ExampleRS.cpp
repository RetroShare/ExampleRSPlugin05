/*
    This file is part of the Zero Reserve Plugin for Retroshare.

    Zero Reserve is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Zero Reserve is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Zero Reserve.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "p3ExampleRS.h"

#include "pqi/p3linkmgr.h"

#include <iostream>

// after getting data from 3 peers, we believe we're complete
static const int INIT_THRESHOLD = 3;

p3ExampleRS::p3ExampleRS(RsPluginHandler *pgHandler, RsPeers* peers ) :
		RsPQIService( RS_SERVICE_TYPE_EXAMPLE_PLUGIN, CONFIG_TYPE_EXAMPLE_PLUGIN, pgHandler )
		, mExampleMtx("p3Example")
		,m_peers(peers)
{
    addSerialType(new RsExampleSerialiser());
	mLinkMgr->addMonitor( this );
}


void p3ExampleRS::statusChange(const std::list< pqipeer > &plist)
{
	/*std::cerr << "Example: Status changed:" << std::endl;

    for (std::list< pqipeer >::const_iterator peerIt = plist.begin(); peerIt != plist.end(); peerIt++ ){
        if( RS_PEER_CONNECTED & (*peerIt).actions ){
            RsExampleItem * item = new RsExampleItem();
            item->PeerId( (*peerIt).id );
            sendItem( item );
        }
	}*/
}

RsServiceInfo p3ExampleRS::getServiceInfo()
{
	const std::string TURTLE_APP_NAME = "Example";
	const uint16_t TURTLE_APP_MAJOR_VERSION  =       1;
	const uint16_t TURTLE_APP_MINOR_VERSION  =       0;
	const uint16_t TURTLE_MIN_MAJOR_VERSION  =       1;
	const uint16_t TURTLE_MIN_MINOR_VERSION  =       0;

	return RsServiceInfo(RS_SERVICE_TYPE_EXAMPLE_PLUGIN,
						 TURTLE_APP_NAME,
						 TURTLE_APP_MAJOR_VERSION,
						 TURTLE_APP_MINOR_VERSION,
						 TURTLE_MIN_MAJOR_VERSION,
						 TURTLE_MIN_MINOR_VERSION);
}


int p3ExampleRS::tick()
{
	/*RsItem *item = NULL;
    while(NULL != (item = recvItem())){
        switch( item->PacketSubType() )
        {
        case RsExampleItem::EXAMPLE_ITEM:
            handleExampleItem( dynamic_cast<RsExampleItem*>( item ) );
            break;
        default:
            std::cerr << "Example: Received Item unknown" << std::endl;
        }
        delete item;
	}*/
    return 0;
}
bool	p3ExampleRS::recvItem(RsItem *item)
{
	/* pass to specific handler */
	bool keep = false ;

	switch(item->PacketSubType())
	{

		case RsExampleItem::EXAMPLE_ITEM:
			std::cout << "Example: Received Item Example Item" << std::endl;
			handleExampleItem( dynamic_cast<RsExampleItem*>( item ) );
			break;
		default:
		std::cout << "Example: Received Item unknown" << std::endl;
			break;
	}

	/* clean up */
	if(!keep)
		delete item;
	return true ;
}

void p3ExampleRS::on_timer(){
	std::cout << "Timer: sending init messages to all contacts!!" << std::endl;

	std::list< RsPeerId > plist;

    //RsStackMutex stack(mExampleMtx); /****** LOCKED MUTEX *******/
	rsPeers->getOnlineList(plist);

	for (std::list< RsPeerId >::const_iterator peerIt = plist.begin(); peerIt != plist.end(); peerIt++ ){
			RsExampleItem * item = new RsExampleItem();
			item->PeerId( (*peerIt) );
			sendItem( item );
	}
}


void p3ExampleRS::handleExampleItem( RsExampleItem * item )
{
	std::cout << "Example: Passed Item Example Item" << std::endl;
    std::cerr << item->PeerId() << " said: " << item->getMessage() << std::endl;
}


