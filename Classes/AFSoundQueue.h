//
//  AFSoundQueue.h
//  AFSoundManager-Demo
//
//  Created by Alvaro Franco on 21/01/15.
//  Copyright (c) 2015 AlvaroFranco. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "AFSoundPlayback.h"
#import "AFSoundItem.h"

@class AFSoundItem;

@protocol AFSoundQueueDataSource <NSObject>
- (NSInteger)numberOfItems;
- (AFSoundItem *)itemAtIndex:(NSInteger)index;
- (NSInteger)indexOfItem:(AFSoundItem *)item;
@end

@protocol AFSoundQueueDelegate <NSObject>
-(void)queuePlayByRemote;
-(void)queuePauseByRemote;
-(void)queueNextByRemote;
-(void)queuePrevByRemote;
@end

@interface AFSoundQueue : NSObject

typedef void (^feedbackBlock)(AFSoundItem *item);
typedef void (^itemFinishedBlock)(AFSoundItem *nextItem);

-(id)initWithItems:(NSArray *)items;

@property (nonatomic) AFSoundStatus status;
@property (nonatomic, weak) id <AFSoundQueueDataSource> dataSource;
@property (nonatomic, weak) id <AFSoundQueueDelegate> delegate;

-(void)addItem:(AFSoundItem *)item;
-(void)addItem:(AFSoundItem *)item atIndex:(NSInteger)index;
-(void)removeItem:(AFSoundItem *)item;
-(void)removeItemAtIndex:(NSInteger)index;
-(void)clearQueue;

-(void)playCurrentItem;
-(void)pause;
-(void)playNextItem;
-(void)playPreviousItem;
-(void)playItem:(AFSoundItem *)item;
-(void)playItemAtIndex:(NSInteger)index;
-(void)playItem:(AFSoundItem *)item atSecond:(NSInteger)second;

-(AFSoundItem *)getCurrentItem;
-(NSInteger)indexOfCurrentItem;

-(void)listenFeedbackUpdatesWithBlock:(feedbackBlock)block andFinishedBlock:(itemFinishedBlock)finishedBlock;

@end
