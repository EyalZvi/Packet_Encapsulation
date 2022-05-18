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

module Host
{
    @display("bgb=291,184");
    gates:
        inout host_gate;
    types:
    submodules:
        application: Application {
            @display("p=67,102");
        }
        ipAddr: IPAddr {
            @display("p=151,102");
        }
        eth: Eth {
            @display("p=240,102");
        }
    connections:
        application.gate <--> ipAddr.app;
        ipAddr.eth <--> eth.ip;
        eth.switch <--> host_gate;
}
