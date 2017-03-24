/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2013-2017 Inviwo Foundation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 *********************************************************************************/

#ifndef IVW_TIMER_H
#define IVW_TIMER_H

#include <inviwo/core/common/inviwocoredefine.h>
#include <inviwo/core/common/inviwoapplication.h>

#include <iostream>
#include <warn/push>
#include <warn/ignore/all>
#include <chrono>
#include <condition_variable>
#include <thread>
#include <future>
#include <mutex>
#include <memory>
#include <utility>
#include <atomic>
#include <warn/pop>

namespace inviwo {

/** \class Timer
 *
 * A Timer class. Will evaluate it's callback in the front thread.
 */

class IVW_CORE_API Timer {
public:
    using Milliseconds = std::chrono::milliseconds;

    Timer(size_t interval, std::function<void()> callback);
    Timer(Milliseconds interval, std::function<void()> callback);
    ~Timer();

    void start();
    void start(size_t interval);
    void start(Milliseconds interval);

    void setInterval(size_t interval);
    void setInterval(Milliseconds interval);
    Milliseconds getInterval() const;
    
    void stop();

private:
    struct Callback {
        Callback(std::function<void()>&& fun) : callback(std::move(fun)), enabled(false) {}
        std::function<void()> callback;
        
        // Mutex needed to make sure we never evaluate the callback after stop has been called
        std::recursive_mutex mutex; 
        std::condition_variable_any cvar;
        std::atomic<bool> enabled;
        std::thread thread;
    };

    void timer();

    std::shared_ptr<Callback> callback_;
    std::future<void> result_;
    Milliseconds interval_;
};

class IVW_CORE_API Delay {
public:
    using duration_t = std::chrono::milliseconds;
    Delay(size_t interval, std::function<void()> callback);
    Delay(duration_t interval, std::function<void()> callback);
    ~Delay();

    void start();
    void stop();

private:
    void delay();

    std::shared_ptr<std::function<void()>> callback_;
    const duration_t interval_;

    bool enabled_;
    std::thread thread_;
    std::mutex mutex_;
    std::condition_variable cvar_;
};

}  // namespace inviwo

#endif // IVW_TIMER_H