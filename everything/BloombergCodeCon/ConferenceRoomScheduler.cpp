// ConferenceRoomScheduler.cpp

#include "ConferenceRoomScheduler.h"
#include "Common.h"

using namespace std;

string
Scheduler::booking( int roomId, int timeSlot, int nSlots )
{
}

string
Scheduler::query( int timeSlot, int nSlots )
{
}

void
conference_room_scheduler()
{
    int N = 3;
    string booking{ "1-1-4" };
    string query{ "1-2" };

    Scheduler scheduler( N );
    cout << scheduler.booking( 1, 1, 4 ).c_str() << endl;
    cout << scheduler.query( 1, 2 ).c_str() << endl;
}