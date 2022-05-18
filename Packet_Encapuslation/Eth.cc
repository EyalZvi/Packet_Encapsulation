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
    src_MAC = par("MAC_addr");                      // set Hosts MAC address
    interval_signal = registerSignal("interval");   // set signal to collect time between arrive messages statistics
    delay_signal = registerSignal("delay");         // set signal to collect statistics about time it takes to send a messsage in the network
    last_pck_arrival = 0;
}

void Eth::handleMessage(cMessage *msg)
{
    /* WooHoo a new messgae arrived! let's check it out */

    cGate *arrive = msg->getArrivalGate();              // get the gate from which the new message arrived
    std::map<int,ARPEntry>::iterator it;                // iterator that will hold found entry in ARP table
    bool delete_header = true;  // flag that is set when we need to delete pointer of message header after decapsulation

    if (strcmp(arrive->getName(),"ip$i") == 0 ){        // check if message arrived from IP layer
        IPv4Msg* rcv = check_and_cast<IPv4Msg*>(msg);
        my_ip = rcv->getSrc_ip();                       // get Hosts IP address for other checks later
        EthMsg* Eth_pck;
        it = ArpTable.find(rcv->getDest_ip());          // try to find destination IP of message in ARP table

        if(it != ArpTable.end())                        // if dest IP in table
        {
            if(it->second.expire >= simTime())          // if found entry check if the entry is not expired yet
            {
                /* Generate EtherType: >> IP << */
                Eth_pck = generateMessage(src_MAC,it->second.MAC,0,0,0);
                Eth_pck->encapsulate(rcv);
                Eth_pck->setSending_time(simTime());
            }
            else
            {
                /* Generate EtherType: >> ARP Request << AND >> Refresh entry << */
                ArpTable.erase(it);     // if entry expired in table => delete it
                Eth_pck = generateMessage(src_MAC,-1,1,rcv->getSrc_ip(),rcv->getDest_ip()); // generate ARP request for dest IP
                delete rcv;
            }

        }

        else    // entry not found in table
        {
            /* Generate EtherType: >> ARP Request << */
            Eth_pck = generateMessage(src_MAC,-1,1,rcv->getSrc_ip(),rcv->getDest_ip());
            delete rcv;
        }
        // Now we try to send the newly created message
        cGate* exit_gate = gate("switch$o");                        // get gate that sends to the network
        cChannel* channel = exit_gate->getTransmissionChannel();    // get the channel to which we will try to send msg
        if(channel->isBusy())                                       // check if channel is already sending a packet
        {
            // if busy schedule event of sending packet when the channel is free
            sendDelayed(Eth_pck,channel->getTransmissionFinishTime() - simTime(),"switch$o");
        }
        else send(Eth_pck,"switch$o");
    }


    if (strcmp(arrive->getName(),"switch$i") == 0 )
    {
        /* If the new message is from the network */
        EthMsg* rcv = check_and_cast<EthMsg*>(msg);

        if(rcv->getEtherType() == 0)                    // IF Receive EtherType: IP
        {                                               // THEN Decapsulate

            if(rcv->getDest_MAC() == src_MAC)
            {
                // Collecting data:
                emit(interval_signal,simTime() - last_pck_arrival);     // collect time waited between arrival of packets
                emit(delay_signal,simTime() - rcv->getSendingTime());   // collect time it took the message to send

                last_pck_arrival = simTime();                           // update time last packet arrived
                //
                IPv4Msg* IP_pck;
                IP_pck = (IPv4Msg*) rcv->decapsulate(); // decapsulate header
                send(IP_pck,"ip$o");                    // send packet to next layer
            }
        }

        if(rcv->getEtherType() == 1)                    // IF Receive EtherType: ARP Request
        {                                               // THEN Generate EtherType: ARP Reply
            if(rcv->getDest_ip() == my_ip)              // message arrived to correct destination by IP
            {
                delete_header = false;
                rcv->setEtherType(2);                   // set message type to ARP Replay
                rcv->setDest_MAC(rcv->getSrc_MAC());    // set destination to requester(?)
                rcv->setSrc_MAC(src_MAC);               // set source MAC as Hosts MAC address
                int new_src = rcv->getDest_ip();
                rcv->setDest_ip(rcv->getSrc_ip());      // set dest IP as senders IP
                rcv->setSrc_ip(new_src);                // set Hosts IP as Source IP

                send(rcv,"switch$o");

            }
        }

        if(rcv->getEtherType() == 2)                    // Receive EtherType: ARP Reply
        {
            if(rcv->getDest_MAC() == src_MAC)   // check if looking for Host(correct MAC dest)
            {
                it = ArpTable.find(rcv->getSrc_ip());   // check if Host knows senders IP
                if(it != ArpTable.end()){               // if senders IP is in ARP table
                    it->second.expire = simTime() + par("arp_ttl"); // update TTL
                }
                else
                {
                    // if senders IP not in table => add to table
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
    /* generate Ethernet type message */
    EthMsg *Eth_pck = new EthMsg();

    Eth_pck->setSrc_MAC(src_MAC);
    Eth_pck->setEtherType(Ether);


    if(Ether == 0)                      // IP EtherType:
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
