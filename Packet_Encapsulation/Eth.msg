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

message EthMsg extends omnetpp::cPacket
{
    // Ethernet packet: 
    
    // For the protocol:
	int preamble;
	int SFD;
    int payload_len;
    int FCS;
    
    // Useful Variables:
    
    // IP EtherType:
    int src_MAC;
	int dest_MAC;
	int EtherType;  // Types: IP = 0 / Arp request = 1 / Arp reply = 2
	int port;
	
	// ARP EtherType: (When ARP type these are added)
	int src_ip;
	int dest_ip;
	
	// Sending Time - For data collection
	simtime_t sending_time;
	
    // Note: As this is a simulation only useful variables are being initialized
}