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

//
// TODO auto-generated module
//
simple Eth
{
    parameters:
        volatile double arp_ttl @unit(s);
        int MAC_addr;
        @signal[interval](type="double");
       	@statistic[interval](title="interval";source="interval";record=stats,vector;interpolationmode=none);


    gates:
        inout ip;
        inout switch;
}
