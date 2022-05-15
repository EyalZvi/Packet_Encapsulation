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

#ifndef __SECONDLAB_ETH_H_
#define __SECONDLAB_ETH_H_

#include <omnetpp.h>
#include "Eth_m.h"
#include "IPv4_m.h"

#include "ARP_Struct.h"
#include <string>

using namespace omnetpp;

class Eth : public cSimpleModule
{
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
//    virtual void finish() override;

  public:
    int src_MAC;
    std::map<int,ARPEntry> ArpTable;

  private:
    int my_ip;

    // Collecting data:
    simsignal_t interval_signal;
    simsignal_t delay_signal;


//    cDoubleHistogram pck_histogram;
//    cDoubleHistogram delay_histogram;
//    cOutVector data_packet_vector;
    simtime_t last_pck_arrival;
//    long data_packet_counter;
    //

};

EthMsg* generateMessage(int src_MAC,int dest_MAC,int Ether,int src_ip,int dest_ip);

#endif
