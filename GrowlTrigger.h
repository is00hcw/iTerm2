//
//  GrowlTrigger.h
//  iTerm
//
//  Created by George Nachman on 9/23/11.
//

#import <Cocoa/Cocoa.h>
#import "Trigger.h"

@interface GrowlTrigger : Trigger {

}

- (NSString *)title;
- (BOOL)takesParameter;
- (void)performActionWithValues:(NSArray *)values inSession:(PTYSession *)aSession;

@end