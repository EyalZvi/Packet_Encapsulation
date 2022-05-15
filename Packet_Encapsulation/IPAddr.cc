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

#include "IPAddr.h"

Define_Module(IPAddr);

void IPAddr::initialize()
{
    int num_of_hosts = par("num_of_hosts");
    ip_addr = par("IP_addr");
}

void IPAddr::handleMessage(cMessage *msg)
{
    cGate *arrive = msg->getArrivalGate();
    IPv4Msg* IP_pck;
    AppMsg* App_pck;
    if (strcmp(arrive->getName(),"app$i") == 0 ){
        AppMsg* rcv_app_pck = check_and_cast<AppMsg*>(msg);
        int dest_ip;
        int num_of_hosts = par("num_of_hosts");
        do
        {
            dest_ip = intuniform(0,num_of_hosts - 1);
        }
            while(dest_ip == ip_addr);
//        EV << "In IPAddr, my ip is: " << ip_addr << " and i chose to send to ip: " << dest_ip << "\n";

        IP_pck = generateMessage(dest_ip,ip_addr);
        IP_pck->encapsulate(rcv_app_pck);
        send(IP_pck,"eth$o");
    }
    if (strcmp(arrive->getName(),"eth$i") == 0 ){
        IPv4Msg* rcv_packet = check_and_cast<IPv4Msg*>(msg);
        if(rcv_packet->getDest_ip() == ip_addr)
        {
            App_pck = (AppMsg*) rcv_packet->decapsulate();
            send(App_pck,"app$o");
            delete rcv_packet;

        }
        else return;
    }
}

IPv4Msg* generateMessage(int dest_ip,int src_ip)
{
    IPv4Msg *IP_pck = new IPv4Msg();
    IP_pck->setByteLength(20);
    IP_pck->setSrc_ip(src_ip);
    IP_pck->setDest_ip(dest_ip);
    return IP_pck;
}
