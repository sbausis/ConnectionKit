/*
Copyright (c) 2004-2006, Greg Hulands <ghulands@framedphotographics.com>
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list 
of conditions and the following disclaimer.

Redistributions in binary form must reproduce the above copyright notice, this 
list of conditions and the following disclaimer in the documentation and/or other 
materials provided with the distribution.

Neither the name of Greg Hulands nor the names of its contributors may be used to 
endorse or promote products derived from this software without specific prior 
written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED 
TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY 
WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
 
#import <Foundation/Foundation.h>
#import "StreamBasedConnection.h"

typedef enum {
	FTPTransferModeStream = 0,
	FTPTransferModeBlock,
	FTPTransferModeCompressed
} FTPTransferMode;

extern NSString *FTPErrorDomain;

enum { FTPErrorParsingDirectoryListing = 5000, FTPErrorStreamError, FTPDownloadFileExists, FTPErrorNoDataModes };

typedef enum {
	FTPSettingPassiveState = 100,
	FTPSettingEPSVState,
	FTPSettingActiveState,
	FTPSettingEPRTState,
	FTPDeterminingDataConnectionType,
	FTPAwaitingDataConnectionToOpen,
	FTPModeChangeState,
	FTPAwaitingRemoteSystemTypeState,
	FTPChangeDirectoryListingStyle
} FTPState;

@interface FTPConnection : StreamBasedConnection
{	
	NSMutableData		*_buffer;
	
	NSMutableString		*_commandBuffer;
	NSMutableData		*_dataBuffer;
	
	NSTimer				*_openStreamsTimeout;
	NSInputStream		*_dataReceiveStream;
	NSOutputStream		*_dataSendStream;
	BOOL				_received226;
	
	long long			_transferSize;
	long long			_transferSent;
	long long			_transferCursor;
	long long			_delegateSizeBuffer;
	int					_transferLastPercent;
	
	BOOL				_setTransferMode;
	
	NSFileHandle		*_writeHandle;
	NSFileHandle		*_readHandle;
	NSData				*_readData;
	NSString			*_currentPath;
	NSString			*_rootPath;
	
	NSDate				*_lastNotified;

	// Support for EPRT and PORT active connections
	CFSocketRef			_activeSocket;
	CFSocketNativeHandle _connectedActive;
	unsigned			_lastActivePort;
	
	//cache the server abilities
	struct __dataCon {
		unsigned canUseActive: 1;
		unsigned canUsePASV: 1;
		unsigned canUseEPSV: 1;
		unsigned canUseEPRT: 1;
		unsigned hasSize: 1;
		unsigned hasADAT: 1;
		unsigned hasAUTH: 1;
		unsigned hasCCC: 1;
		unsigned hasCONF: 1;
		unsigned hasENC: 1;
		unsigned hasMIC: 1;
		unsigned hasPBSZ: 1;
		unsigned hasPROT: 1;
		unsigned hasMDTM: 1;
		unsigned hasSITE: 1;
		unsigned isActiveDataConn: 1;
		unsigned loggedIn: 1;
		unsigned isMicrosoft: 1;
		unsigned unused: 14;
	} _serverSupport;
	
}

// TESTING
- (NSString *)scanBetweenQuotes:(NSString *)aString;

@end

