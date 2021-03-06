//
//  Popup.h
//  iTerm
//
//  Created by George Nachman on 11/4/10.
//  Copyright 2010 George Nachman. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class PopupModel;
@class PopupEntry;
@class PTYTextView;
@class VT100Screen;

@protocol PopupDelegate <NSObject>

- (NSWindowController *)popupWindowController;
- (VT100Screen *)popupVT100Screen;
- (PTYTextView *)popupVT100TextView;
- (void)popupInsertText:(NSString *)text;
// Return YES if the delegate handles it, NO if Popup should handle it.
- (BOOL)popupKeyDown:(NSEvent *)event currentValue:(NSString *)value;

@end

@interface Popup : NSWindowController

@property(nonatomic, assign) id<PopupDelegate> delegate;

- (id)initWithWindowNibName:(NSString*)nibName tablePtr:(NSTableView**)table model:(PopupModel*)model;
- (void)dealloc;

// Call this after initWithWindowNibName:tablePtr:model: if table was nil.
- (void)setTableView:(NSTableView *)table;

// Turn off focus follows mouse while this window is key.
- (BOOL)disableFocusFollowsMouse;

// Called by clients to open window.
- (void)popWithDelegate:(id<PopupDelegate>)delegate;

// Safely shut down the popup when the parent is about to be dealloced. Clients must call this from
// dealloc. It removes possible pending timers.
- (void)shutdown;

// Subclasses may override these methods.
// Begin populating the unfiltered model.
- (void)refresh;

// Notify that a row was selected. Call this method when subclass has accepted
// the selection.
- (void)rowSelected:(id)sender;

// Handle key presses.
- (void)keyDown:(NSEvent*)event;

// Window is closing. Call this method when subclass is done.
- (void)onClose;

// Window is opening. -[refresh] will be called immediately after this returns.
- (void)onOpen;

// Get a value for a table cell. Always returns a value from the model.
- (id)tableView:(NSTableView *)aTableView objectValueForTableColumn:(NSTableColumn *)aTableColumn row:(NSInteger)rowIndex;
- (void)tableViewSelectionDidChange:(NSNotification *)aNotification;

- (void)setOnTop:(BOOL)onTop;
- (PopupModel*)unfilteredModel;
- (PopupModel*)model;
- (void)setPosition:(BOOL)canChangeSide;
- (void)reloadData:(BOOL)canChangeSide;
- (void)_setClearFilterOnNextKeyDownFlag:(id)sender;
- (int)convertIndex:(int)i;
- (NSAttributedString*)attributedStringForEntry:(PopupEntry*)entry isSelected:(BOOL)isSelected;
- (void)windowDidResignKey:(NSNotification *)aNotification;
- (void)windowDidBecomeKey:(NSNotification *)aNotification;
- (NSInteger)numberOfRowsInTableView:(NSTableView *)aTableView;
- (BOOL)_word:(NSString*)temp matchesFilter:(NSString*)filter;


@end
