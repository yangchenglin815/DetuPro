#ifndef PANO_PLAYER_DEF_H
#define PANO_PLAYER_DEF_H

namespace DetuPanoPlayer {

typedef enum PanoPlayerPlatform {
    PanoPlayerPlatform_ANDROID,
    PanoPlayerPlatform_IOS,
    PanoPlayerPlatform_WINDOWS,
    PanoPlayerPlatform_MAC,
    PanoPlayerPlatform_LINUX,
} PanoPlayerPlatform;

typedef enum PanoLogLevel {
    PanoLogLevel_UNKNOWN = 0,
    PanoLogLevel_DEFAULT = 1,
    PanoLogLevel_VERBOSE = 2,
    PanoLogLevel_DEBUG   = 3,
    PanoLogLevel_INFO    = 4,
    PanoLogLevel_WARN    = 5,
    PanoLogLevel_ERROR   = 6,
    PanoLogLevel_FATAL   = 7,
    PanoLogLevel_SILENT  = 8,
} PanoLogLevel;

typedef enum EaseTypes {
	BackEaseIns = 0,
	BackEaseOuts = 1,
	BackEaseInOuts = 2,
	BounceEaseIns = 3,
	BounceEaseOuts = 4,
	BounceEaseInOuts = 5,
	CircEaseIns = 6,
	CircEaseOuts = 7,
	CircEaseInOuts = 8,
	CubicEaseIns = 9,
	CubicEaseOuts = 10,
	CubicEaseInOuts = 11,
	ElasticEaseIns = 12,
	ElasticEaseOuts = 13,
	ElasticEaseInOuts = 14,
	ExpoEaseIns = 15,
	ExpoEaseOuts = 16,
	ExpoEaseInOuts = 17,
	LinearEaseIns = 18,
	LinearEaseOuts = 19,
	LinearEaseInOuts = 20,
	QuadEaseIns = 21,
	QuadEaseOuts = 22,
	QuadEaseInOuts = 23,
	QuartEaseIns = 24,
	QuartEaseOuts = 25,
	QuartEaseInOuts = 26,
	QuintEaseIns = 27,
	QuintEaseOuts = 28,
	QuintEaseInOuts = 29,
	SineEaseIns = 30,
	SineEaseOuts = 31,
	SineEaseInOuts = 32,

} EaseTypes;

}
#endif // !PANO_PLAYER_DEF_H
