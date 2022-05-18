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

#include "switch.h"

Define_Module(Switch);

void Switch::initialize()
{
}

void Switch::handleMessage(cMessage *msg)
{
    if(!msg->isSelfMessage())                      // Forwarding Latency
    {
        EthMsg* rcv = check_and_cast<EthMsg*>(msg);
        rcv->setPort(rcv->getArrivalGate()->getIndex());
        scheduleAt(simTime() + rcv->getBitLength()*3/1000000000,rcv);
    }
    else
    {
        /* if self message => message is delayed and ready to send */
        std::map<int,SwitchEntry>::iterator it;
        EthMsg* rcv_msg = check_and_cast <EthMsg*> (msg);
        int src_MAC = rcv_msg->getSrc_MAC();

        int port = rcv_msg->getPort();

        // UPDATE table entry

        it = SwitchTable.find(src_MAC);
        if(it != SwitchTable.end()) // check if received messages' SOURCE is in the forwarding table
        {
            // has entry => update TTL
            it->second.expire = simTime() + par("aging_time");
        }
        else
        {
            // no entry for dest => create new entry
            SwitchEntry new_entry = {port,simTime() + par("aging_time")};
            SwitchTable.insert(std::pair<int,SwitchEntry>(src_MAC,new_entry));
        }

        //////////

        it = SwitchTable.find(rcv_msg->getDest_MAC());
        if(it != SwitchTable.end() && rcv_msg->getEtherType() != 1) // check msg destination is in table and not ARPRequest
        {
            cGate* exit_gate = gate("gate$o",it->second.port);          // get gate we want to send from
            cChannel* channel = exit_gate->getTransmissionChannel();    // get channel the gate is sending to
            if(channel->isBusy())   // checking if no other message is transmitting right now
            {
                // if so, send message when channel is free
                sendDelayed(rcv_msg,channel->getTransmissionFinishTime() - simTime(),"gate$o",it->second.port);
            }
            else send(rcv_msg,"gate$o",it->second.port);
        }
        else
        {
            // no entry in forwarding table for destination => flood the network!
            for(int i=0; i<4; ++i)
            {
                if(i != port)   // don't flood to the port from which the message arrive
                {
                    cGate* exit_gate = gate("gate$o",i);
                    cChannel* channel = exit_gate->getTransmissionChannel();
                    EthMsg* send_msg =  new EthMsg();
                    memcpy(send_msg,rcv_msg,sizeof(EthMsg));
                    // check if channel is buys
                    if(channel->isBusy())
                    {
                        sendDelayed(send_msg,channel->getTransmissionFinishTime() - simTime(),"gate$o",i);
                    }
                    else send(send_msg,"gate$o",i);
                }
            }
            delete rcv_msg;
        }
    }
}












