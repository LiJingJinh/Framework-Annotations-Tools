/*
 * NSRunLoop.h
 * 白开水ln（https://github.com/CustomPBWaters）
 *
 * (c) 1994-2016
 * Created by 【Plain Boiled Water ln】 on Elegant programming.
 * Copyright © Unauthorized shall（https://custompbwaters.github.io）not be reproduced.
 *
 * @PBWLN_LICENSE_HEADER_END@
 */


#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>
#import <CoreFoundation/CFRunLoop.h>

@class NSTimer, NSPort, NSArray<ObjectType>, NSString;

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSRunLoopMode const NSDefaultRunLoopMode;// (默认):同一时间只能执行一个任务
FOUNDATION_EXPORT NSRunLoopMode const NSRunLoopCommonModes NS_AVAILABLE(10_5, 2_0); // (公用):可以分配一定的时间处理定时器

@interface NSRunLoop : NSObject {
@private
    id          _rl;
    id          _dperf;
    id          _perft;
    id          _info;
    id		_ports;
    void	*_reserved[6];
}

#if FOUNDATION_SWIFT_SDK_EPOCH_AT_LEAST(8)
@property (class, readonly, strong) NSRunLoop *currentRunLoop;
@property (class, readonly, strong) NSRunLoop *mainRunLoop NS_AVAILABLE(10_5, 2_0);
#endif

@property (nullable, readonly, copy) NSRunLoopMode currentMode;

- (CFRunLoopRef)getCFRunLoop CF_RETURNS_NOT_RETAINED;

- (void)addTimer:(NSTimer *)timer forMode:(NSRunLoopMode)mode;

- (void)addPort:(NSPort *)aPort forMode:(NSRunLoopMode)mode;
- (void)removePort:(NSPort *)aPort forMode:(NSRunLoopMode)mode;

- (nullable NSDate *)limitDateForMode:(NSRunLoopMode)mode;
- (void)acceptInputForMode:(NSRunLoopMode)mode beforeDate:(NSDate *)limitDate;

@end

@interface NSRunLoop (NSRunLoopConveniences)

- (void)run;
- (void)runUntilDate:(NSDate *)limitDate;
- (BOOL)runMode:(NSRunLoopMode)mode beforeDate:(NSDate *)limitDate;

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
- (void)configureAsServer NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);
#endif

/// Schedules the execution of a block on the target run loop in given modes.
/// - parameter: modes   An array of input modes for which the block may be executed.
/// - parameter: block   The block to execute
- (void)performInModes:(NSArray<NSRunLoopMode> *)modes block:(void (^)(void))block API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/// Schedules the execution of a block on the target run loop.
/// - parameter: block   The block to execute
- (void)performBlock:(void (^)(void))block API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

@end

/**************** 	Delayed perform	 ******************/

@interface NSObject (NSDelayedPerforming)

- (void)performSelector:(SEL)aSelector withObject:(nullable id)anArgument afterDelay:(NSTimeInterval)delay inModes:(NSArray<NSRunLoopMode> *)modes;
- (void)performSelector:(SEL)aSelector withObject:(nullable id)anArgument afterDelay:(NSTimeInterval)delay;
+ (void)cancelPreviousPerformRequestsWithTarget:(id)aTarget selector:(SEL)aSelector object:(nullable id)anArgument;
+ (void)cancelPreviousPerformRequestsWithTarget:(id)aTarget;

@end

@interface NSRunLoop (NSOrderedPerform)

- (void)performSelector:(SEL)aSelector target:(id)target argument:(nullable id)arg order:(NSUInteger)order modes:(NSArray<NSRunLoopMode> *)modes;
- (void)cancelPerformSelector:(SEL)aSelector target:(id)target argument:(nullable id)arg;
- (void)cancelPerformSelectorsWithTarget:(id)target;

@end

NS_ASSUME_NONNULL_END
