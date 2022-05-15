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
    double next_event = par("next_event_par");
    int pck_len_mean =  par("pck_len_mean");
    int pck_len_stddev =  par("pck_len_stddev");
    int pck_len_min = par("pck_len_min");
    int pck_len_max = par("pck_len_max");
    AppMsg *App_pck = generateMessage((int)normal(pck_len_mean,pck_len_stddev),pck_len_min,pck_len_max);
    cMessage *self_msg = new cMessage();
    send(App_pck,"gate$o");
    simtime_t next_event_rand = exponential(next_event) + simTime();
    if(next_event_rand <= par("sim_time"))
        scheduleAt(next_event_rand,self_msg);
    else delete self_msg;
}

void Application::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage())
    {
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
    else
    {
        AppMsg* app_packet = check_and_cast<AppMsg*> (msg);
//        EV << "Received app data: " << app_packet->getPayload() << " With length: "<< app_packet->getByteLength() << "\n";
        delete app_packet;
    }

}

AppMsg* generateMessage(int pck_len,int pck_len_min,int pck_len_max)
{
    int len;
    AppMsg *App_pck = new AppMsg();
    if(pck_len < pck_len_min){
        len = pck_len_min;
    }
    else
    {
        if(pck_len > pck_len_max)
        {
            len = pck_len_max;
        }
        else
        {
            len = pck_len;
        }
    }

    App_pck->setByteLength(len);
    App_pck->setPayload("Data data data!");
    return App_pck;
}
