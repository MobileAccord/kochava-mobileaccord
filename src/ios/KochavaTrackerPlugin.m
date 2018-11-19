//
//  KochavaTrackerPlugin.m
//  KochavaTracker (PhoneGap)
//
//  Copyright (c) 2013 - 2017 Kochava, Inc. All rights reserved.
//
//  Description : This is the plugin class implementation file.
//

#pragma mark - IMPORT

#import "KochavaTrackerPlugin.h"

#pragma mark - CONST

NSString *const KVA_PARAM_IOS_APP_GUID_STRING_KEY = @"iOSAppGUIDString";

#pragma mark - IMPLEMENTATION

@implementation KochavaTrackerPlugin

#pragma mark - GENERAL

+ (void)invalidateKochava
{
    [KochavaTracker.shared performSelector:@selector(invalidate)];
}

+ (void)removeKochavaUserDefaults
{
    NSArray *keyArray = NSUserDefaults.standardUserDefaults.dictionaryRepresentation.allKeys;
    for (id key in keyArray)
    {
        NSRange kochavaPrefixRange = [key rangeOfString:@"com.kochava"];
        if ( kochavaPrefixRange.location != NSNotFound )
        {
            [NSUserDefaults.standardUserDefaults removeObjectForKey:key];
        }
    }
}

- (void)evaluateWindowAttributionNotificationCallbackWithParameterString:(nonnull NSString *)parameterString
{
    NSString *javaScriptString = [NSString stringWithFormat:@"window.attributionNotification.notificationCallback('%@');",parameterString];
    
    if ([self.webView isKindOfClass:[UIWebView class]])
    {
        UIWebView *webView = (UIWebView*)self.webView;
        dispatch_async(dispatch_get_main_queue(), ^{
            [webView stringByEvaluatingJavaScriptFromString:javaScriptString];
        });
    }
}

- (void)sendEventString:(CDVInvokedUrlCommand *)invokedUrlCommand
{
    NSString *nameString = nil;
    NSString *infoString = nil;

    id nameObject = [invokedUrlCommand.arguments objectAtIndex:0];
    id infoObject = [invokedUrlCommand.arguments objectAtIndex:1];

    if([nameObject isKindOfClass:NSString.class])
    {
        nameString = (NSString *)nameObject;
    }
    if([infoObject isKindOfClass:NSString.class])
    {
        infoString = (NSString *)infoObject;
    }
    
    [KochavaTracker.shared sendEventWithNameString:nameString infoString:infoString];
    
    // Respond with Result
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@""];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:invokedUrlCommand.callbackId];
}

- (void)sendEventMapObject:(CDVInvokedUrlCommand *)invokedUrlCommand
{
    NSString *nameString = nil;
    NSDictionary *infoDictionary = nil;

    id nameObject = [invokedUrlCommand.arguments objectAtIndex:0];
    id infoObject = [invokedUrlCommand.arguments objectAtIndex:1];

    if([nameObject isKindOfClass:NSString.class])
    {
        nameString = (NSString *)nameObject;
    }
    if([infoObject isKindOfClass:NSDictionary.class])
    {
        infoDictionary = (NSDictionary *)infoObject;
    }
    
    [KochavaTracker.shared sendEventWithNameString:nameString infoDictionary:infoDictionary];
    
    // Respond with Result
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@""];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:invokedUrlCommand.callbackId];
}

- (void)sendEventAppleAppStoreReceipt:(CDVInvokedUrlCommand *)invokedUrlCommand
{
    id nameObject = [invokedUrlCommand.arguments objectAtIndex:0];
    id infoObject = [invokedUrlCommand.arguments objectAtIndex:1];
    id appStoreReceiptObject = [invokedUrlCommand.arguments objectAtIndex:2];

    NSString *nameString = nil;
    NSDictionary *infoDictionary = nil;
    NSString *appStoreReceiptBase64EncodedString = nil;

    if([nameObject isKindOfClass:NSString.class])
    {
        nameString = (NSString *)nameObject;
    }
    if([infoObject isKindOfClass:NSDictionary.class])
    {
        infoDictionary = (NSDictionary *)infoObject;
    }
    if([appStoreReceiptObject isKindOfClass:NSString.class])
    {
        appStoreReceiptBase64EncodedString = (NSString *)appStoreReceiptObject;
    }
    
    // Build the Event
    KochavaEvent *event = [KochavaEvent eventWithEventTypeEnum:KochavaEventTypeEnumCustom];
    event.customEventNameString = nameString;
    event.infoDictionary = infoDictionary;
    event.appStoreReceiptBase64EncodedString = appStoreReceiptBase64EncodedString;
    
    [KochavaTracker.shared sendEvent:event];
     
    // Respond with Result
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@""];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:invokedUrlCommand.callbackId];
}

- (void)sendEventGooglePlayReceipt:(CDVInvokedUrlCommand *)invokedUrlCommand
{
    NSLog(@"KOCHAVA - sendEventWithGooglePlayReceiptButton does not apply to this OS");
}

- (void)sendDeepLink:(CDVInvokedUrlCommand *)invokedUrlCommand
{
    id deepLinkObject = [invokedUrlCommand.arguments objectAtIndex:0];
    id sourceApplicationObject = [invokedUrlCommand.arguments objectAtIndex:1];

    NSString *deepLinkURLString = nil;
    NSString *sourceApplicationString = nil;

    if([deepLinkObject isKindOfClass:NSString.class])
    {
        deepLinkURLString = (NSString *)deepLinkObject;
    }
    if([sourceApplicationObject isKindOfClass:NSString.class])
    {
        sourceApplicationString = (NSString *)sourceApplicationObject;
    }
    
    NSURL *deeplinkURL = nil;
    
    if(deepLinkURLString != nil) 
    {
        deeplinkURL = [NSURL URLWithString:[deepLinkURLString stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding]];
    }
    
    [KochavaTracker.shared sendDeepLinkWithOpenURL:deeplinkURL sourceApplicationString:sourceApplicationString];
    
    // Respond with Result
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@""];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:invokedUrlCommand.callbackId];
}

- (void)setAppLimitAdTracking:(CDVInvokedUrlCommand *)invokedUrlCommand
{
    BOOL appLimitAdTrackingBool = [[invokedUrlCommand.arguments objectAtIndex:0] boolValue];

    [KochavaTracker.shared setAppLimitAdTrackingBool:appLimitAdTrackingBool];
    
    // Respond with Result
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@""];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:invokedUrlCommand.callbackId];
}

- (void)setIdentityLink:(CDVInvokedUrlCommand *)invokedUrlCommand
{
    id dictionaryObject = [invokedUrlCommand.arguments objectAtIndex:0];
    
    NSDictionary *dictionary = nil;
    
    if([dictionaryObject isKindOfClass:NSDictionary.class])
    {
        dictionary = (NSDictionary *)dictionaryObject;
    }
    
    [KochavaTracker.shared sendIdentityLinkWithDictionary:dictionary];

    // Respond with Result
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@""];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:invokedUrlCommand.callbackId];
}

- (void)getAttribution:(CDVInvokedUrlCommand *)invokedUrlCommand
{
    NSDictionary *attributionDictionary = KochavaTracker.shared.attributionDictionary;
    
    NSString *resultMessageString = @"";

    if (attributionDictionary != nil)
    {
        NSError *error = nil;
        NSData *attributionDictionaryJSONData = [NSJSONSerialization dataWithJSONObject:attributionDictionary options:0 error:&error];
        
        NSString *attributionDictionaryJSONString = nil;
        if (attributionDictionaryJSONData != nil)
        {
            attributionDictionaryJSONString = [[NSString alloc] initWithData:attributionDictionaryJSONData encoding:NSUTF8StringEncoding];
        }
        
        if (attributionDictionaryJSONString != nil)
        {
            resultMessageString = attributionDictionaryJSONString;
        }
    }
    
    // Respond with Result
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:resultMessageString];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:invokedUrlCommand.callbackId];
}
    
- (void)getDeviceId:(CDVInvokedUrlCommand *)invokedUrlCommand
{
    NSString *deviceIdString = KochavaTracker.shared.deviceIdString;
    if(deviceIdString == nil)
    {
        deviceIdString = @"";
    }
    
    // Respond with Result
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:deviceIdString];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:invokedUrlCommand.callbackId];
}

- (void)getVersion:(CDVInvokedUrlCommand *)invokedUrlCommand
{
    NSString *sdkVersionString = KochavaTracker.shared.sdkVersionString;
    if(sdkVersionString == nil)
    {
        sdkVersionString = @"";
    }
    
    // Respond with Result
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:sdkVersionString];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:invokedUrlCommand.callbackId];
}

- (void)addPushToken:(nullable CDVInvokedUrlCommand *)invokedUrlCommand
{
    id tokenObject = [invokedUrlCommand.arguments objectAtIndex:0];

    NSString *tokenString = nil;

    if([tokenObject isKindOfClass:NSString.class])
    {
        tokenString = (NSString *)tokenObject;
    }

    NSData *tokenData = nil;
    
    if(tokenString.length > 0)
    {
        tokenData = [self.class dataWithHexString:tokenString];
    }
    
    [KochavaTracker.shared addRemoteNotificationsDeviceToken:tokenData];
    
    // Respond with Result
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@""];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:invokedUrlCommand.callbackId];
}

- (void)removePushToken:(nullable CDVInvokedUrlCommand *)invokedUrlCommand
{
    id tokenObject = [invokedUrlCommand.arguments objectAtIndex:0];

    NSString *tokenString = nil;

    if([tokenObject isKindOfClass:NSString.class])
    {
        tokenString = (NSString *)tokenObject;
    }

    NSData *tokenData = nil;
    
    if(tokenString.length > 0)
    {
        tokenData = [self.class dataWithHexString:tokenString];
    }
    
    [KochavaTracker.shared removeRemoteNotificationsDeviceToken:tokenData];
    
    // Respond with Result
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@""];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:invokedUrlCommand.callbackId];
}

- (void)setConsentGranted:(nullable CDVInvokedUrlCommand *)invokedUrlCommand
{
    id consentGrantedObject = [invokedUrlCommand.arguments objectAtIndex:0];
    
    NSNumber *consentGranted = nil;
    
    if([consentGrantedObject isKindOfClass:NSNumber.class])
    {
        consentGranted = (NSNumber *)consentGrantedObject;
    }

    if(consentGranted != nil)
    {
        [KochavaTracker.shared.consent didPromptWithDidGrantBoolNumber:consentGranted];
    }

    // Respond with Result
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@""];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:invokedUrlCommand.callbackId];
}

- (void)setConsentPrompted:(nullable CDVInvokedUrlCommand *)invokedUrlCommand
{
    [KochavaTracker.shared.consent willPrompt];

    // Respond with Result
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@""];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:invokedUrlCommand.callbackId];
}

- (void)getConsentStatus:(nullable CDVInvokedUrlCommand *)invokedUrlCommand
{
    NSString *consentStatusString = nil;
    
    NSObject *consentAsForContextObject = [KochavaTracker.shared.consent kva_asForContextObjectWithContext:KVAContext.sdkWrapper];

    if (consentAsForContextObject != nil)
    {
        NSError *error = nil;
        NSData *consentStatusJSONData = [NSJSONSerialization dataWithJSONObject:consentAsForContextObject options:0 error:&error];
        
        if (consentStatusJSONData != nil)
        {
            consentStatusString = [[NSString alloc] initWithData:consentStatusJSONData encoding:NSUTF8StringEncoding];
        }
    }
    
    if(consentStatusString == nil)
    {
        consentStatusString = @"{}";
    }

    // Respond with Result
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:consentStatusString];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:invokedUrlCommand.callbackId];
}

#pragma mark - LIFECYCLE
    
- (void)configure:(CDVInvokedUrlCommand *)invokedUrlCommand
{
    // Discussion:  Configures the shared tracker.

    id receivedParametersDictionaryObject = [invokedUrlCommand.arguments objectAtIndex:0];

    NSDictionary *receivedParametersDictionary = nil;

    if ([receivedParametersDictionaryObject isKindOfClass:NSDictionary.class])
    {
        receivedParametersDictionary = (NSDictionary *)receivedParametersDictionaryObject;
    }
    
    // VALIDATION (RETURN)
    if (receivedParametersDictionary == nil)
    {
        NSLog(@"KochavaTrackerPlugin.configure parameter 0 is not an NSDictionary.  iOS native cannot initialize.");
        return;
    }

    // Check for the existence of the hidden unconfigure key.
    if ([receivedParametersDictionary objectForKey:@"INTERNAL_UNCONFIGURE"]) {
        NSLog(@"KochavaTrackerPlugin.configure UnConfigure.");
        [KochavaTrackerPlugin invalidateKochava];
        return;
    }

    // Check for the existence of the hidden reset key.
    if ([receivedParametersDictionary objectForKey:@"INTERNAL_RESET"]) {
        NSLog(@"KochavaTrackerPlugin.configure Reset.");
        [KochavaTrackerPlugin removeKochavaUserDefaults];
        return;
    }

    NSLog(@"KochavaTrackerPlugin.configure.");
    
    // PARSE SPECIFIC PARAMETERS FROM RECEIVEDPARAMETERSDICTIONARY
    // appGUIDStringObject
    id appGUIDStringObject = receivedParametersDictionary[KVA_PARAM_IOS_APP_GUID_STRING_KEY];
    
    // CONFIGURE TRACKER
    // trackerParametersDictionary
    NSMutableDictionary *trackerParametersDictionary = receivedParametersDictionary.mutableCopy;

    // ... kKVAParamAppGUIDStringKey
    if (appGUIDStringObject != nil)
    {
        trackerParametersDictionary[kKVAParamAppGUIDStringKey] = appGUIDStringObject;
        
        trackerParametersDictionary[KVA_PARAM_IOS_APP_GUID_STRING_KEY] = nil;
    }

    // kochavaTracker
    // this cannot be run in background or will crash trying to collect user agent
    [KochavaTracker.shared configureWithParametersDictionary:trackerParametersDictionary delegate:self];

    //Check if intelligent consent management is on and apply as necessary.
    BOOL intelligentManagementBool = [[receivedParametersDictionary objectForKey:@"consentIntelligentManagement"] boolValue];
    if(intelligentManagementBool) {
        KochavaTracker.shared.consent.didUpdateBlock = ^(KVAConsent * _Nonnull consent)
        {
            // javaScriptString
            NSString *javaScriptString = [NSString stringWithFormat:@"window.consentStatusChangeNotification.notificationCallback('');"];
            
            // webView
            if ([self.webView isKindOfClass:[UIWebView class]])
            {
                UIWebView *webView = (UIWebView*)self.webView;
                
                dispatch_async(dispatch_get_main_queue(), ^{
                    
                    [webView stringByEvaluatingJavaScriptFromString:javaScriptString];
                    
                });
            }
        };
    }
    
}
    
#pragma mark - DELEGATE CALLBACKS
#pragma mark KochavaTrackerDelegate
     
- (void)tracker:(nonnull KochavaTracker *)tracker didRetrieveAttributionDictionary:(nonnull NSDictionary *)attributionDictionary
{
    NSError *error = nil;
    NSData *attributionDictionaryJSONData = [NSJSONSerialization dataWithJSONObject:attributionDictionary options:0 error:&error];
    
    if (error != nil)
    {
        NSLog(@"error: %@", error);
    }
    
    // attributionDictionaryJSONString
    NSString *attributionDictionaryJSONString = nil;
    
    if (attributionDictionaryJSONData != nil)
    {
        attributionDictionaryJSONString = [[NSString alloc] initWithData:attributionDictionaryJSONData encoding:NSUTF8StringEncoding];
    }
    
    // resolvedAttributionDictionaryJSONString
    NSString *resolvedAttributionDictionaryJSONString = nil;
    
    if (attributionDictionaryJSONString != nil)
    {
        resolvedAttributionDictionaryJSONString = attributionDictionaryJSONString;
    }

    // resolvedAttributionDictionaryJSONStringData
    NSData *resolvedAttributionDictionaryJSONStringData = [resolvedAttributionDictionaryJSONString dataUsingEncoding:NSUTF8StringEncoding];
    
    // resolvedAttributionDictionaryJSONStringDataBase64EncodedString
    NSString *resolvedAttributionDictionaryJSONStringDataBase64EncodedString = nil;
    
    if (resolvedAttributionDictionaryJSONStringData != nil)
    {
        resolvedAttributionDictionaryJSONStringDataBase64EncodedString = [resolvedAttributionDictionaryJSONStringData base64EncodedStringWithOptions:0];
    }
    
    // evaluateWindowAttributionNotificationCallbackWithParameterString
    if (resolvedAttributionDictionaryJSONStringDataBase64EncodedString != nil)
    {
        [self evaluateWindowAttributionNotificationCallbackWithParameterString:resolvedAttributionDictionaryJSONStringDataBase64EncodedString];
    }
}

#pragma mark - CLASS METHODS

+(id)dataWithHexString:(NSString *)hexString
{
    // Discussion:  This is being employed to take the output of an NSData description (which is a hex string, such as is the case with a push notification token) and turn it back into an NSData.  This was sourced from the web and then optimized.

    // VALIDATION (RETURN)
    // hexString
    // ... must not be nil
    if (hexString == nil)
    {
        return nil;
    }
    
    // hexStringLength
    // ... must be an even number of digits
    NSUInteger hexStringLength = hexString.length;
    
    if (hexStringLength % 2 > 0)
    {
        NSLog(@"Warning:  func dataWithHexString(_:) - parameter hexString was passed a value which does not have an even number of digits.  hexString = %@", hexString);
        
        return nil;
    }
    
    // MAIN
    // bytes and bytesPointer
    // ... default to point to some newly allocated memory
    unsigned char *bytes = (unsigned char *)malloc(hexStringLength / 2);

    unsigned char *bytesPointer = bytes;

    // ... fill with long(s) converted from two-digit strings containing base-16 representations of numbers
    for (CFIndex index = 0; index < hexStringLength; index += 2)
    {
        // buffer
        // ... set to the two-digit base 16 number located at index
        char buffer[3];
        buffer[0] = (char)[hexString characterAtIndex:index];
        buffer[1] = (char)[hexString characterAtIndex:index + 1];
        buffer[2] = '\0';

        // longInt and endPointer
        // ... set longInt to buffer converted to a long, and set endPointer to the next character in buffer after the numerical value.
        char *endPointer = NULL;
        
        long int longInt = strtol(buffer, &endPointer, 16);

        // bytesPointer
        // ... update with longInt
        *bytesPointer = (unsigned char)longInt;

        // ... advance to next position
        bytesPointer++;
    }
    
    // return
    return [NSData dataWithBytesNoCopy:bytes length:(hexStringLength / 2) freeWhenDone:YES];
}

@end
