#include "pch.h"
#include "Timer.h"

#pragma region sdl_timer
Empaerior::SDL_Timer::SDL_Timer()
{
	//Initialize the variables
	mStartTicks = 0;
	mPausedTicks = 0;

	mPaused = false;
	mStarted = false;
}

void Empaerior::SDL_Timer::start()
{
	//Start the timer
	mStarted = true;

	//Unpause the timer
	mPaused = false;

	//Get the current clock time
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void Empaerior::SDL_Timer::stop()
{
	//Stop the timer
	mStarted = false;

	//Unpause the timer
	mPaused = false;

	//Clear tick variables
	mStartTicks = 0;
	mPausedTicks = 0;
}

void Empaerior::SDL_Timer::pause()
{
	//If the timer is running and isn't already paused
	if (mStarted && !mPaused)
	{
		//Pause the timer
		mPaused = true;

		//Calculate the paused ticks
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

void Empaerior::SDL_Timer::unpause()
{
	//If the timer is running and paused
	if (mStarted && mPaused)
	{
		//Unpause the timer
		mPaused = false;

		//Reset the starting ticks
		mStartTicks = SDL_GetTicks() - mPausedTicks;

		//Reset the paused ticks
		mPausedTicks = 0;
	}
}

Empaerior::u_int Empaerior::SDL_Timer::getTicks()
{
	//The actual timer time
	Empaerior::u_int time = 0;

	//If the timer is running
	if (mStarted)
	{
		//If the timer is paused
		if (mPaused)
		{
			//Return the number of ticks when the timer was paused
			time = mPausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - mStartTicks;
		}
	}

	return time;
}

bool Empaerior::SDL_Timer::isStarted()
{
	//Timer is running and paused or unpaused
	return mStarted;
}

bool Empaerior::SDL_Timer::isPaused()
{
	//Timer is running and paused
	return mPaused && mStarted;
}
#pragma endregion


