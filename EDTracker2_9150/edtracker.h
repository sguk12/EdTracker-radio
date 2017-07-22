// SG: These structures and classes should substitute for the original EDTracker classes for joystick axis values


typedef struct TrackState 		
{
	int16_t		xAxis; 
	int16_t		yAxis;
	int16_t		zAxis;

} TrackState_t;

class Tracker_
{
public:
	Tracker_(){};

	void setState(TrackState_t *trackSt){};

};
extern Tracker_ Tracker;
