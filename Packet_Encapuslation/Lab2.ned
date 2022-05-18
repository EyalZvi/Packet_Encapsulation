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

network Lab2
{
    parameters:
        @signal[delay](type="double");
        @statistic[delay](title="delay";source="delay";record=stats,vector;interpolationmode=none);
        
    @display("bgb=93.45,66.15");
    types:
        channel Channel extends ned.DatarateChannel
        {
            datarate = 100000000bps;
        }
    submodules:
        host1: Host {
            @display("p=75.95,18.199999");
        }
        host2: Host {
            @display("p=19.949999,43.75");
        }
        host3: Host {
            @display("p=75.95,43.75");
        }
        host4: Host {
            @display("p=19.949999,18.199999");
        }
        switch: Switch {
            @display("p=47.6,30.099998");
        }
    connections:
        host1.host_gate <--> Channel <--> switch.gate[0];
        host2.host_gate <--> Channel <--> switch.gate[1];
        host3.host_gate <--> Channel <--> switch.gate[2];
        host4.host_gate <--> Channel <--> switch.gate[3];
}
