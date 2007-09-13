//
//  CKTableBasedBrowser.h
//  Connection
//
//  Created by Greg Hulands on 8/09/07.
//  Copyright 2007 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface CKTableBasedBrowser : NSView
{
	id myDataSource; // not retained
	id myDelegate; // not retained
	Class myCellClass;
	id myCellPrototype;
	NSMutableArray *myColumns;
	NSMutableArray *mySelection;
	
	IBOutlet NSTextField *oPath;
	
	float myMinColumnWidth;
	float myMaxColumnWidth;
	float myRowHeight;
	
	NSString *myAutosaveName;
	
	SEL myAction;
	SEL myDoubleAction;
	id myTarget; // not retained
	
	NSString *myCurrentPath;
	NSString *myPathSeparator;
	
	NSView *myLeafView; // not retained
	
	struct __cktbb_flags {
		unsigned allowsMultipleSelection: 1;
		unsigned allowsResizing: 1;
		unsigned isEditable: 1;
		unsigned isEnabled: 1;
		unsigned unused: 28;
	} myFlags;
	
	struct __cktbb_ds_flags {
		unsigned numberOfChildrenOfItem: 1;
		unsigned childOfItem: 1;
		unsigned isItemExpandable: 1;
		unsigned objectValueByItem: 1;
		unsigned setObjectValueByItem: 1;
		unsigned acceptDrop: 1;
		unsigned validateDrop: 1;
		unsigned writeItemsToPasteboard: 1;
		unsigned pathForItem: 1;
		unsigned itemForPath: 1;
		unsigned unused: 22;
	} myDataSourceFlags;
	
	struct __cktbb_del_flags {
		unsigned shouldExpandItem: 1;
		unsigned shouldSelectItem: 1;
		unsigned willDisplayCell: 1;
		unsigned tooltipForCell: 1;
		unsigned shouldEditItem: 1;
		unsigned leafViewWithItem: 1;
		unsigned contextMenuWithItem: 1;
		unsigned unused: 25;
	} myDelegateFlags;
}

+ (Class)cellClass;
- (void)setCellClass:(Class)aClass;
- (id)cellPrototype;
- (void)setCellPrototype:(id)prototype;

- (void)setEnabled:(BOOL)flag;
- (BOOL)isEnabled;

- (void)setAllowsMultipleSelection:(BOOL)flag;
- (BOOL)allowsMultipleSelection;
- (void)setAllowsColumnResizing:(BOOL)flag;
- (BOOL)allowsColumnResizing;
- (void)setEditable:(BOOL)flag;
- (BOOL)isEditable;

- (void)setRowHeight:(float)height;
- (float)rowHeight;
- (void)setMinColumnWidth:(float)size;
- (float)minColumnWidth;
- (void)setMaxColumnWidth:(float)size;
- (float)maxColumnWidth;

- (void)selectAll:(id)sender;
- (void)selectItem:(id)item;
- (void)selectItems:(NSArray *)items; //array of items

- (void)setPath:(NSString *)path;
- (NSString *)path;
- (NSString *)pathToColumn:(unsigned)column;
- (unsigned)columnToItem:(id)item;

- (NSArray *)selectedItems;

- (void)setTarget:(id)target;
- (id)target;
- (void)setAction:(SEL)anAction;
- (SEL)action;
- (void)setDoubleAction:(SEL)anAction;
- (SEL)doubleAction;

- (void)setDataSource:(id)ds;
- (id)dataSource;
- (void)setDelegate:(id)delegate;
- (id)delegate;

- (BOOL)isExpandable:(id)item;
- (void)expandItem:(id)item;

- (void)reloadData;
- (void)reloadItem:(id)item;
- (void)reloadItem:(id)item reloadChildren:(BOOL)flag;

- (id)itemAtColumn:(unsigned)column row:(unsigned)row;
- (void)column:(unsigned *)column row:(unsigned *)row forItem:(id)item;

- (void)setAutosaveName:(NSString *)name;
- (NSString *)autosaveName;

- (void)scrollItemToVisible:(id)item;

- (NSRect)frameOfColumnContainingItem:(id)item;

@end

@interface NSObject (CKTableBasedBrowserDataSource)

- (unsigned)tableBrowser:(CKTableBasedBrowser *)browser numberOfChildrenOfItem:(id)item;
- (id)tableBrowser:(CKTableBasedBrowser *)browser child:(unsigned)index ofItem:(id)item;
- (BOOL)tableBrowser:(CKTableBasedBrowser *)browser isItemExpandable:(id)item;
- (id)tableBrowser:(CKTableBasedBrowser *)browser objectValueByItem:(id)item;
- (void)tableBrowser:(CKTableBasedBrowser *)browser setObjectValue:(id)object byItem:(id)item;
- (NSString *)tableBrowser:(CKTableBasedBrowser *)browser pathForItem:(id)item;
- (id)tableBrowser:(CKTableBasedBrowser *)browser itemForPath:(NSString *)path;

- (BOOL)tableBrowser:(CKTableBasedBrowser *)browser acceptDrop:(id <NSDraggingInfo>)info item:(id)item childIndex:(unsigned)index;
- (NSDragOperation)tableBrowser:(CKTableBasedBrowser *)browser validateDrop:(id <NSDraggingInfo>)info proposedItem:(id)item proposedChildIndex:(int)index;
- (BOOL)tableBrowser:(CKTableBasedBrowser *)browser writeItems:(NSArray *)items toPasteboard:(NSPasteboard *)pboard;

@end

@interface NSObject (CKTableBasedBrowserDelegate)

// navigation
- (BOOL)tableBrowser:(CKTableBasedBrowser *)browser shouldExpandItem:(id)item;
- (BOOL)tableBrowser:(CKTableBasedBrowser *)browser shouldSelectItem:(id)item;

// display
- (void)tableBrowser:(CKTableBasedBrowser *)browser willDisplayCell:(id)cell item:(id)item;
- (NSString *)tableBrowser:(CKTableBasedBrowser *)browser toolTipForCell:(NSCell *)cell rect:(NSRectPointer)rect item:(id)item mouseLocation:(NSPoint)mouseLocation;

// editing
- (BOOL)tableBrowser:(CKTableBasedBrowser *)browser shouldEditItem:(id)item;

// custom leaf view
- (NSView *)tableBrowser:(CKTableBasedBrowser *)browser leafViewWithItem:(id)item;

// context menu
- (NSMenu *)tableBrowser:(CKTableBasedBrowser *)browser contextMenuWithItem:(id)item;

@end