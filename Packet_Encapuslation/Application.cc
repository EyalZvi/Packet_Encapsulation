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

#include "Application.h"

Define_Module(Application);

void Application::initialize()
{
    double next_event = par("next_event_par");  // get the mean of the exponential distr of the wait time between generating new messages
    int pck_len_mean = par("pck_len_mean");     // get the mean packet length of packets to generate
    int pck_len_stddev = par("pck_len_stddev"); // get the standard deviation of the generated packets length
    int pck_len_min = par("pck_len_min");       // get the minimum length possible for generated packet
    int pck_len_max = par("pck_len_max");       // get the maximum length possible for generated packet
    // generate new Application type message
    AppMsg *App_pck = generateMessage((int)normal(pck_len_mean,pck_len_stddev),pck_len_min,pck_len_max);
    cMessage *self_msg = new cMessage();        // generate new message to send to self to create the next app msg generation event
    send(App_pck,"gate$o");                     // send first app messgae
    simtime_t next_event_rand = exponential(next_event) + simTime();    // calculate the next simulation time to create new app message
    if(next_event_rand <= par("sim_time"))      // check that we are not over our time limit
        scheduleAt(next_event_rand,self_msg);   // schedule next event
    else delete self_msg;
}

void Application::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage())    // if self message => we need to create a new app message
    {
        // same as in initialize
        double next_event = par("next_event_par");
        int pck_len_mean =  par("pck_len_mean");
        int pck_len_stddev =  par("pck_len_stddev");
        int pck_len_min = par("pck_len_min");
        int pck_len_max = par("pck_len_max");
        AppMsg *App_pck = generateMessage((int)normal(pck_len_mean,pck_len_stddev),pck_len_min,pck_len_max);
        cMessage *self_msg = msg;
        send(App_pck,"gate$o");
        simtime_t next_event_rand = exponential(next_event) +simTime();
        if(next_event_rand <= par("sim_time"))
            scheduleAt(next_event_rand,self_msg);
        else delete self_msg;
    }
    else    // else this is a message forwarded from the IP layer
    {
        AppMsg* app_packet = check_and_cast<AppMsg*> (msg);     // receive that data YEAH...
        delete app_packet;
    }

}

AppMsg* generateMessage(int pck_len,int pck_len_min,int pck_len_max)
{
    /* Generates a new Application type message using given length */
    int len;
    AppMsg *App_pck = new AppMsg();
    if(pck_len < pck_len_min){  // checks that the the length is not too little
        len = pck_len_min;
    }
    else
    {
        if(pck_len > pck_len_max)   // or too big ;)
        {
            len = pck_len_max;
        }
        else
        {
            len = pck_len;
        }
    }

    App_pck->setByteLength(len);                // set the length of the packet for the simulations sake(by Bytes)
    App_pck->setPayload("Data data data!");     // set the data we are transmitting
    return App_pck;
}
