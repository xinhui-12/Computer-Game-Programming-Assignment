#include "FrameTimer.h"

void FrameTimer::init(int fps) {
    requestedFPS = fps;
    QueryPerformanceFrequency(&timerFreq);
    QueryPerformanceCounter(&timeNow);
    QueryPerformanceCounter(&timePrevious);
    //init fps time info
    //The number of intervals in the given timer, per frame at the requested rate.
    intervalsPerFrame = ((float)timerFreq.QuadPart / requestedFPS);

}

int FrameTimer::framesToUpdate() {
    int framesToUpdate = 0;
    QueryPerformanceCounter(&timeNow);
    intervalsSinceLastUpdate = (float)timeNow.QuadPart - (float)timePrevious.QuadPart;
    framesToUpdate = (int)(intervalsSinceLastUpdate / intervalsPerFrame);
    //If we are not updating any frames, 
    //keep the old previous timer count 
    if (framesToUpdate != 0) {
        QueryPerformanceCounter(&timePrevious);
    }
    return framesToUpdate;
}

