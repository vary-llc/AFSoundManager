//
//  AFSoundItem.h
//  AFSoundManager-Demo
//
//  Created by Alvaro Franco on 20/01/15.
//  Copyright (c) 2015 AlvaroFranco. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

@interface AFSoundItem : NSObject

typedef NS_ENUM(NSInteger, AFSoundItemType) {
    
    AFSoundItemTypeLocal,
    AFSoundItemTypeStreaming
};

-(id)initWithLocalResource:(NSString *)name atPath:(NSString *)path;
-(id)initWithStreamingURL:(NSURL *)URL;

@property (nonatomic) NSString *title;
@property (nonatomic) NSString *album;
@property (nonatomic) NSString *artist;
@property (nonatomic) UIImage *artwork;

@property (nonatomic, readonly) NSURL *URL;
@property (nonatomic, readonly) NSInteger type;

@property (nonatomic) NSInteger duration;
@property (nonatomic) NSInteger timePlayed;

-(void)setInfoFromItem:(AVPlayerItem *)item;

@end
