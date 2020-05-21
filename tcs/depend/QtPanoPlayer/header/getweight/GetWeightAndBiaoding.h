//
//  GetWeightAndBiaoding.h
//  GetWeightAndBiaoding
//
//  Created by zhangjing on 2017/10/23.
//  Copyright © 2017年 detu. All rights reserved.
//

#import <Foundation/Foundation.h>



typedef struct WeightAndMaskDataWrapper
{
    int width;
    int height;
    char biaoding[512];
    uint8_t *data;
} WeightAndMaskDataWrapper;

@interface GetWeightAndBiaoding : NSObject
- (BOOL) GetWeight :(NSString*) path out:(WeightAndMaskDataWrapper*) outData resultpath :(NSArray<NSString*>*) urls;
@end
