#ifndef _TIMER_H_
#define _TIMER_H_

#include <SDL.h>
#include <array>
#include <cstdint>
#include <iomanip>
#include <iostream>

class Timer {
public:
	Timer();
	void start();
	unsigned get_fps(unsigned long int frames);
	unsigned get_running_time() const;
	unsigned get_delta_time() const;
	void restart();
	void update();
	void stop();
	void pause();
	void unpause();
	bool is_counting();
	bool is_started() const;
	bool is_paused() const;
	bool is_stopped() const;
	unsigned get_ticks() const;
	unsigned get_seconds() const;
	void print_counter();

private:
	std::array<int, 10> frame_values;
	unsigned prev_frame_val = 0;
	unsigned frames_per_sec = 0;
	unsigned running_time = 0;
	bool started = false;
	bool paused = false;
	bool stopped = false;
	unsigned start_ticks = 0;
	unsigned pause_ticks = 0;
};

#endif // _TIMER_H_
