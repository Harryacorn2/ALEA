#ifndef PROFILER_CPP
#define PROFILER_CPP

#include "Profiler.h"
#include "Log.h"
#include "bn_keypad.h"

bool Profiler::mCurrentlyCapturing = false;
bn::timer Profiler::mGrandTimer = bn::timer();
bn::vector<Event, MAX_PROFILED_EVENTS> Profiler::mEvents = bn::vector<Event, MAX_PROFILED_EVENTS>();

void Profiler::Control() {
    EndFrame();
    
    if (bn::keypad::r_pressed()) {
        StartCapture();
    }
    
    if (bn::keypad::l_pressed()) {
        EndCapture();
    }
}

void Profiler::StartCapture() {
    mCurrentlyCapturing = true;
}

void Profiler::EndCapture() {
    EndFrame();
    mCurrentlyCapturing = false;
}

void Profiler::EndFrame() {
    for (Event e : mEvents) {
        switch (e.mType) {
            case EVENT_TYPE::BEGIN:
                Log::Format("{\"name\": \"%s\", \"pid\": 1, \"tid\": 1, \"ph\": \"B\", \"ts\": %d},", e.mName.c_str(), e.mTime);
                break;
                
            case EVENT_TYPE::END:
                Log::Format("{\"pid\": 1, \"tid\": 1, \"ph\": \"E\", \"ts\": %d},", e.mTime);
                break;
                
            default:
                break;
        }
    }
    
    mEvents.clear();
}

void Profiler::StartEvent(const bn::string<32>& name) {
    if (mCurrentlyCapturing) mEvents.push_back({name, mGrandTimer.elapsed_ticks(), EVENT_TYPE::BEGIN});
//    if (mCurrentlyCapturing) Log::Format("{\"name\": \"%s\", \"pid\": 1, \"tid\": 1, \"ph\": \"B\", \"ts\": %d},", name.c_str(), mGrandTimer.elapsed_ticks());
}

void Profiler::EndEvent() {
    if (mCurrentlyCapturing) mEvents.push_back({"", mGrandTimer.elapsed_ticks(), EVENT_TYPE::END});
//    if (mCurrentlyCapturing) Log::Format("{\"pid\": 1, \"tid\": 1, \"ph\": \"E\", \"ts\": %d},", mGrandTimer.elapsed_ticks());
}

#endif
