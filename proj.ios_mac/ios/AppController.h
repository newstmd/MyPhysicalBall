#import <UIKit/UIKit.h>
#import "BaiduMobAdView.h"

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate,BaiduMobAdViewDelegate> {
    UIWindow *window;
    BaiduMobAdView* sharedAdView;
}

@property(nonatomic, readonly) RootViewController* viewController;

@end

