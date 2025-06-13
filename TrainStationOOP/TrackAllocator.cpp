#include "TrackAllocator.h"

bool TrackAllocator::allocateTracks(Station& origin, Station& destination, size_t& departingTrack, size_t& arrivingTrack)
{
	if (!origin.reserveTrack(departingTrack)) {
		return false;
	}

	if (!destination.reserveTrack(arrivingTrack)) {
		origin.releaseTrack(departingTrack);
		return false;
	}

	return true;
}

void TrackAllocator::releaseDepartingTrack(Station& origin, size_t departingTrack)
{
	origin.releaseTrack(departingTrack);
}

void TrackAllocator::releaseArrivingingTrack(Station& destination, size_t arrivingTrack)
{
	destination.reserveTrack(arrivingTrack);
}
