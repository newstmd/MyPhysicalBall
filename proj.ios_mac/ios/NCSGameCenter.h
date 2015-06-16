//
//  NCSGameCenter.h
//  MyPhysicalBall
//
//  Created by 唐鑫 on 15/6/16.
//
//

#ifndef __MyPhysicalBall__NCSGameCenter__
#define __MyPhysicalBall__NCSGameCenter__

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <GameKit/GameKit.h>

@interface NCSGameCenter : NSObject < GKLeaderboardViewControllerDelegate, GKAchievementViewControllerDelegate, GKMatchmakerViewControllerDelegate, GKMatchDelegate> {
    BOOL gameCenterAvailable;
    BOOL userAuthenticated;
}

@property (assign, readonly) BOOL gameCenterAvailable;
@property (nonatomic, copy) NSString* leaderboardName;
//本地成就字典，用来保存已经下载下来的成就，以避免重复从gamecenter获取成就状态
@property (nonatomic, retain) NSMutableDictionary* achievementDictionary;

+ (NCSGameCenter *)sharedGameCenter;
- (void) authenticateLocalUser;
- (void) registerForAuthenticationNotification;

- (void) showLeaderboard;
- (void) leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController;
//上传分数到Gamecenter
- (void) reportScore:(int64_t)score forCategory:(NSString*)category;
//从gamecenter下载前X个分数
- (void) retrieveTopXScores:(int)number;

- (void) showAchievementboard;
- (void) achievementViewControllerDidFinish:(GKAchievementViewController *)achievementController;
- (void) loadAchievement;
- (void) clearAchievements;
- (void) reportAchievement:(NSString*)id percent:(float)percent;
- (void) unlockAchievement:(GKAchievement*)achievement percent:(float)percent;
- (GKAchievement*) getAchievementForID:(NSString*)id;

@end

#endif /* defined(__MyPhysicalBall__NCSGameCenter__) */
