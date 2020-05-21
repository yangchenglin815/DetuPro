 #ifndef Tween_h_H
 #define Tween_h_H
 
#ifdef __cplusplus
extern "C" {
#endif

#include "Easing.h"
#include <stdbool.h>

typedef struct TweenTimer  {
		int state;
		float time;
		float duration;
		int loop;
	} TweenTimer;

	typedef struct Tween{
		TweenTimer tweentime;
		float result;
		float percent;

		float start;
		float change;
		Ease Ease; 
	}Tween;

	void tick(TweenTimer *tweentimer);
	void runEasing(Tween *tween);
	void tween_setup(Tween *tween, int duration, float start, float change, EaseType type);
	void setTween(Tween *tween[], int duration, float start[], float end[], EaseType type,int num);
	void tween_play(Tween *tween );
	void tween_pause(Tween *tween);
	void tween_stop(Tween *tween);
	bool tween_finished(Tween *tween);
	void update(Tween *tween);
	void tween_update(Tween *tween[],int num);


#ifdef __cplusplus
}
#endif


#endif Tween_h_H

