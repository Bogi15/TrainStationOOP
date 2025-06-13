#pragma once
#include "Station.h"

class TrackAllocator
{
public:
	static bool allocateTracks(Station& origin, Station& destination, size_t& departingTrack, size_t& arrivingTrack);
	static void releaseDepartingTrack(Station& origin, size_t departingTrack);
	static void releaseArrivingingTrack(Station& destination, size_t arrivingTrack);
};
