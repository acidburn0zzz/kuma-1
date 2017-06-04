#include "timer.h"

#include "SDL_timer.h"

Timer::Timer() { start(); }

unsigned Timer::get_running_time() const { return SDL_GetTicks(); }

unsigned Timer::get_ticks() const {
	if (paused) {
		return pause_ticks;
	} else {
		return SDL_GetTicks() - start_ticks;
	}
}

// This shit is useless, needs fix
unsigned Timer::get_delta_time() const {
	auto old = SDL_GetTicks() / 1000.00;
	auto current = get_seconds();
	auto delta = current;
	if (current > old) {
		delta = current - old;
	}
	return delta;
}

unsigned Timer::get_seconds() const { return (get_ticks() / 1000.00); }

unsigned Timer::get_fps(unsigned long frames) {
	frames_per_sec = 0.00;
	int count = 0;
	int index = frames % frame_values.size();

	frame_values[index] = get_ticks() - prev_frame_val;
	prev_frame_val = get_ticks();

	if (frames < frame_values.size()) {
		count = frames;
	} else {
		count = frame_values.size();
	}

	for (int i = 0; i < count; i++) {
		frames_per_sec += frame_values[i];
	}

	frames_per_sec /= count;
	frames_per_sec = 1000.00 / frames_per_sec;

	return frames_per_sec;
}

void Timer::print_counter() {
	// std::cout << "\rRunning Time: " << std::setw(6) <<
	// (get_running_time() / 1000.00) << " seconds.";
	std::cout << "\rCounter: " << std::setw(6) << (get_ticks() / 1000.00)
		  << " seconds";
	std::cout.flush();
}

void Timer::start() {
	started = true;
	paused = false;
	start_ticks = SDL_GetTicks();
	pause_ticks = 0.00;
}

void Timer::pause() {
	paused = true;
	pause_ticks = SDL_GetTicks() - start_ticks;
}

void Timer::unpause() {
	started = true;
	paused = false;
	pause_ticks = 0.00;
	start_ticks = pause_ticks;
}


bool Timer::is_started() const { return started; }

bool Timer::is_paused() const { return paused; }
