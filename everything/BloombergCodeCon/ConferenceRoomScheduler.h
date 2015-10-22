// ConferenceRoomScheduler.h

#pragma once
#ifndef CONFERENCEROOMSCHEDULER_H
#define CONFERENCEROOMSCHEDULER_H

#include <string>

class Scheduler
{
public:
    Scheduler( int N ) : _N{ N } {}
    std::string booking( int roomId, int timeSlot, int nSlots );
    std::string query( int timeSlot, int nSlots );

private:
    int _N = 0;
};

void conference_room_scheduler();

#endif // CONFERENCEROOMSCHEDULER_H

