//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Eth.h"

Define_Module(Eth);

void Eth::initialize()
{
    src_MAC = par("MAC_addr");
    interval_signal = registerSignal("interval");
    delay_signal = registerSignal("delay");
    last_pck_arrival = 0;
}

void Eth::handleMessage(cMessage *msg)
{
    cGate *arrive = msg->getArrivalGate();
    std::map<int,ARPEntry>::iterator it;
    bool delete_header = true;



    if (strcmp(arrive->getName(),"ip$i") == 0 ){
        IPv4Msg* rcv = check_and_cast<IPv4Msg*>(msg);
        my_ip = rcv->getSrc_ip();
        EthMsg* Eth_pck;
        it = ArpTable.find(rcv->getDest_ip());

        if(it != ArpTable.end())
        {
            if(it->second.expire >= simTime())  // Generate EtherType: IP
            {
                Eth_pck = generateMessage(src_MAC,it->second.MAC,0,0,0);
                Eth_pck->encapsulate(rcv);
                Eth_pck->setSending_time(simTime());
//                EV << "My MAC is " << src_MAC << " and i'm sending IPMsg to " << it->second.MAC << "\n";
            }
            else                                // Generate EtherType: ARP Request AND Refresh entry
            {
                ArpTable.erase(it);
                Eth_pck = generateMessage(src_MAC,-1,1,rcv->getSrc_ip(),rcv->getDest_ip());
//                EV << "My MAC is " << src_MAC << " and i'm sending ARP Request to ip: " << rcv->getDest_ip() << "\n";
                delete rcv;
            }

        }

        else                                    // Generate EtherType: ARP Request
        {
            Eth_pck = generateMessage(src_MAC,-1,1,rcv->getSrc_ip(),rcv->getDest_ip());
//            EV << "My MAC is " << src_MAC << " and i'm sending ARP Request to ip: " << rcv->getDest_ip() << " (No refresh)\n";
            delete rcv;
        }
            cGate* exit_gate = gate("switch$o");
            cChannel* channel = exit_gate->getTransmissionChannel();
            if(channel->isBusy())
            {
                sendDelayed(Eth_pck,channel->getTransmissionFinishTime() - simTime(),"switch$o");
            }
            else send(Eth_pck,"switch$o");
    }


    if (strcmp(arrive->getName(),"switch$i") == 0 )
    {
        EthMsg* rcv = check_and_cast<EthMsg*>(msg);

        if(rcv->getEtherType() == 0)                    // IF Receive EtherType: IP
        {                                               // THEN Decapsulate

            if(rcv->getDest_MAC() == src_MAC)
            {

                // Collecting data:

                emit(interval_signal,simTime() - last_pck_arrival);
                emit(delay_signal,simTime() - rcv->getSendingTime());

//                data_packet_counter ++;
//                data_packet_vector.record(data_packet_counter);
//
//                EV << "My MAC is: " << src_MAC << ", time from last arrival: " << simTime() - last_pck_arrival << endl;
//
//                pck_histogram.collect(simTime() - last_pck_arrival);
//                delay_histogram.collect(simTime() - rcv->getSendingTime());
                last_pck_arrival = simTime();
                //

                IPv4Msg* IP_pck;
                IP_pck = (IPv4Msg*) rcv->decapsulate();
                send(IP_pck,"ip$o");
            }
        }

        if(rcv->getEtherType() == 1)                    // IF Receive EtherType: ARP Request
        {                                               // THEN Generate EtherType: ARP Reply
            if(rcv->getDest_ip() == my_ip)
            {
                delete_header = false;
                rcv->setEtherType(2);
                rcv->setDest_MAC(rcv->getSrc_MAC());
                rcv->setSrc_MAC(src_MAC);
                int new_src = rcv->getDest_ip();
                rcv->setDest_ip(rcv->getSrc_ip());
                rcv->setSrc_ip(new_src);
//                EV << "My MAC is " << src_MAC << " and i'm sending ARP Reply to ip: " << rcv->getDest_ip() << "\n";
                send(rcv,"switch$o");

            }
        }

        if(rcv->getEtherType() == 2)                    // Receive EtherType: ARP Reply
        {
            if(rcv->getDest_MAC() == src_MAC)
            {
                it = ArpTable.find(rcv->getSrc_ip());
                if(it != ArpTable.end()){
                    it->second.expire = simTime() + par("arp_ttl");
                }
                else
                {
                    ARPEntry new_entry = {rcv->getSrc_MAC(),simTime() + par("arp_ttl")};
                    ArpTable.insert(std::pair<int,ARPEntry>(rcv->getSrc_ip(),new_entry));
                }
            }
        }
       if(delete_header) delete rcv;
    }
}

EthMsg* generateMessage(int src_MAC,int dest_MAC,int Ether,int src_ip,int dest_ip)
{
    EthMsg *Eth_pck = new EthMsg();

    Eth_pck->setSrc_MAC(src_MAC);
    Eth_pck->setEtherType(Ether);


    if(Ether == 0)                  // IP EtherType:
    {
        Eth_pck->setDest_MAC(dest_MAC);
    }
    if(Ether == 1)                   // ARP Request EtherType:
    {
        Eth_pck->setSrc_ip(src_ip);
        Eth_pck->setDest_ip(dest_ip);
    }
    return Eth_pck;
}

//void Eth::finish()
//{
//
//    // This function is called by OMNeT++ at the end of the simulation.
//    EV << "=============== Host "<< src_MAC + 1 <<" ===============\n";
//    EV << "Messages Received:     " << pck_histogram.getCount() << endl << endl;
//
//    EV << "Time differences , min:    " << pck_histogram.getMin() << endl;
//    EV << "Time differences , max:    " << pck_histogram.getMax() << endl;
//    EV << "Time differences , mean:   " << pck_histogram.getMean() << endl;
//    EV << "Time differences , stddev: " << pck_histogram.getStddev() << endl;
//    EV << "--------------------------------------\n";
//    EV << "Sending Time , min:    " << delay_histogram.getMin() << endl;
//    EV << "Sending Time , max:    " << delay_histogram.getMax() << endl;
//    EV << "Sending Time , mean:   " << delay_histogram.getMean() << endl;
//    EV << "Sending Time , stddev: " << delay_histogram.getStddev() << endl << endl;
//
//    recordScalar("#sent", data_packet_counter);
//
//    pck_histogram.recordAs("hop count");
//}
