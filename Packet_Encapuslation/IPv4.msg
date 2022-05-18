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

message IPv4Msg extends omnetpp::cPacket
{
    // IPv4 packet: 
    
    // For the protocol:
    int protocol_version;
    int IHL;
    int DSCP;   
    int ECN;
    int Total_length;
    int identification;
    int flags;
    int fragment_offset;
    int TTL;
    int upper_protocol;
    int header_checksum;
    
    // Useful Variables:
    int src_ip;
    int dest_ip;
    
    // Note: As this is a simulation only useful variables are being initialized
}