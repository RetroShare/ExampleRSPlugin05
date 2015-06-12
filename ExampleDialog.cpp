

#include "ExampleDialog.h"

#include <QMenu>
#include <QStandardItem>
#include <list>

#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

#include <retroshare/rsfiles.h>
#include <retroshare/rspeers.h>

#include "RSExampleItems.h"
#include "p3ExampleRS.h"

#define IMAGE_FRIENDINFO ":/images/peerdetails_16x16.png"


ExampleDialog::ExampleDialog( QWidget *parent )
: MainPage(parent)
{
    ui.setupUi(this);



	timer=new QTimer(this);
	connect(timer,SIGNAL(timeout()),SLOT(on_timer()));
	timer->start(1500);

}

void ExampleDialog::on_timer(){
	p3service->on_timer();
	std::cout << "Timer: sending init messages to all contacts!!" << std::endl;

	std::list< RsPeerId > plist;
	rsPeers->getOnlineList(plist);

	for (std::list< RsPeerId >::const_iterator peerIt = plist.begin(); peerIt != plist.end(); peerIt++ ){
			RsExampleItem * item = new RsExampleItem();
			item->PeerId( (*peerIt) );
			p3service->sendItem( item );
	}
}
