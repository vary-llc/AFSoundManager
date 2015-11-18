//
//  NSTimer+AFSoundManager.m
//  AFSoundManager-Demo
//
//  Created by Alvaro Franco on 10/02/15.
//  Copyright (c) 2015 AlvaroFranco. All rights reserved.
//

#import "NSTimer+AFSoundManager.h"
#import <objc/runtime.h>

@implementation NSTimer (AFSoundManager)

+(id)scheduledTimerWithTimeInterval:(NSTimeInterval)inTimeInterval block:(void (^)())inBlock repeats:(BOOL)inRepeats {
    
    void (^block)() = [inBlock copy];
    id ret = [self scheduledTimerWithTimeInterval:inTimeInterval target:self selector:@selector(jdExecuteSimpleBlock:) userInfo:block repeats:inRepeats];
    
    return ret;
}

+(id)timerWithTimeInterval:(NSTimeInterval)inTimeInterval block:(void (^)())inBlock repeats:(BOOL)inRepeats {
    
    void (^block)() = [inBlock copy];
    id ret = [self timerWithTimeInterval:inTimeInterval target:self selector:@selector(jdExecuteSimpleBlock:) userInfo:block repeats:inRepeats];
    
    return ret;
}

+(void)jdExecuteSimpleBlock:(NSTimer *)inTimer {
    
    if([inTimer userInfo]) {
        void (^block)() = (void (^)())[inTimer userInfo];
        block();
    }
}

static NSString *const NSTimerPauseDate = @"NSTimerPauseDate";
static NSString *const NSTimerPreviousFireDate = @"NSTimerPreviousFireDate";

-(void)pauseTimer {
    //NSLog(@"%s", __func__);
    if (self.timerPaused != nil && ![self.timerPaused boolValue]) {
        self.timerPaused = @(YES);
        
        objc_setAssociatedObject(self, (__bridge const void *)(NSTimerPauseDate), [NSDate date], OBJC_ASSOCIATION_RETAIN_NONATOMIC);
        objc_setAssociatedObject(self, (__bridge const void *)(NSTimerPreviousFireDate), self.fireDate, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
        
        self.fireDate = [NSDate distantFuture];
    }
}

-(void)resumeTimer {
    //NSLog(@"%s", __func__);
    if (self.timerPaused == nil || [self.timerPaused boolValue]) {
        NSDate *pauseDate = objc_getAssociatedObject(self, (__bridge const void *)NSTimerPauseDate);
        NSDate *previousFireDate = objc_getAssociatedObject(self, (__bridge const void *)NSTimerPreviousFireDate);
        
        const NSTimeInterval pauseTime = -[pauseDate timeIntervalSinceNow];
        self.fireDate = [NSDate dateWithTimeInterval:pauseTime sinceDate:previousFireDate];
    }
}

- (NSNumber *)timerPaused {
    return objc_getAssociatedObject(self, @selector(timerPaused));
}

- (void)setTimerPaused:(NSNumber *)value {
    objc_setAssociatedObject(self, @selector(timerPaused), value, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

@end
