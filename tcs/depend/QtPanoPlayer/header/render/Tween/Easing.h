#ifndef Easing_h_H
#define Easing_h_H
#ifdef __cplusplus
extern "C" {
#endif
// back

typedef enum EaseType {
    BackEaseIn = 0,
    BackEaseOut = 1,
    BackEaseInOut = 2,
    BounceEaseIn = 3,
    BounceEaseOut = 4,
    BounceEaseInOut = 5,
    CircEaseIn = 6,
    CircEaseOut = 7,
    CircEaseInOut = 8,
    CubicEaseIn = 9,
    CubicEaseOut = 10,
    CubicEaseInOut = 11,
    ElasticEaseIn = 12,
    ElasticEaseOut = 13,
    ElasticEaseInOut = 14,
    ExpoEaseIn = 15,
    ExpoEaseOut = 16,
    ExpoEaseInOut = 17,
    LinearEaseIn = 18,
    LinearEaseOut = 19,
    LinearEaseInOut = 20,
    QuadEaseIn = 21,
    QuadEaseOut = 22,
    QuadEaseInOut = 23,
    QuartEaseIn = 24,
    QuartEaseOut = 25,
    QuartEaseInOut = 26,
    QuintEaseIn = 27,
    QuintEaseOut = 28,
    QuintEaseInOut = 29,
    SineEaseIn = 30,
    SineEaseOut = 31,
    SineEaseInOut = 32,

} EaseType;
typedef struct Ease {
    float start;
    float time;
    float duration;
    float change;
    EaseType easetype;
} Ease;

float getEasedata(Ease *ease);

#ifdef __cplusplus
}
#endif
#endif //Easing_h_H
 