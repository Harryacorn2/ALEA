#ifndef PROFILER_H
#define PROFILER_H

#include "global.h"
#include "bn_string.h"
#include "bn_timer.h"
#include "bn_unordered_map.h"
#include "bn_vector.h"


// Is defined in global.h
#ifdef PROFILING
#define PROFILE_CONTROL() Profiler::Control()
#define PROFILE_SCOPE(name) \
Profiler::ScopedTimer name##_scope(bn::string<32>(#name))

#else
#define PROFILE_CONTROL() Profiler::Control()
#define PROFILE_SCOPE(name)

#endif

enum class EVENT_TYPE {
    BEGIN,
    END
};

struct Event {
    bn::string<32> mName;
    int mTime;
    EVENT_TYPE mType;
};

class Profiler {
public:
    static void Control();
    static void StartCapture(); // Restarts Grand Timer, and tells events to start capturing data
    static void EndCapture(); // Tells events to stop capturing data, and logs trace file
    static void EndFrame();
    
    static void StartEvent(const bn::string<32>& name);
    static void EndEvent();
    
    class ScopedTimer {
    public:
        ScopedTimer(const bn::string<32>& name) { Profiler::StartEvent(name); }
        ~ScopedTimer() { Profiler::EndEvent(); }
    };
    
private:
    Profiler();
    ~Profiler();
    
    static bool mCurrentlyCapturing;
    static bn::timer mGrandTimer;
    static bn::vector<Event, MAX_PROFILED_EVENTS> mEvents;
    
    friend class ScopedTimer;
};

#endif
