//
//  KochavaTracker.h
//  KochavaTracker
//
//  Created by John Bushnell on 9/26/16.
//  Copyright (c) 2013 - 2018 Kochava, Inc. All rights reserved.
//



#ifndef KVATracker_h
#define KVATracker_h



#pragma mark - IMPORT



#import <Foundation/Foundation.h>

#if TARGET_OS_TV
#import <JavaScriptCore/JavaScriptCore.h>
#endif



#import "KVAContext.h"

#import "KVAFromObjectProtocol.h"

#import "KVAAsForContextObjectProtocol.h"

#import "KVAConsent.h"

#import "KVAPartner.h"

#import "KochavaEvent.h"



#pragma mark - DEFINE



#if KVA_REVEAL_TARGET == 1

#define KOCHAVA_DEPRECATED(MSG) /*__attribute__((deprecated(MSG)))*/

#else

#define KOCHAVA_DEPRECATED(MSG) __attribute__((deprecated(MSG)))

#endif



#define KVATracker KochavaTracker

#define KVATrackerDelegate KochavaTrackerDelegate



#pragma mark - CLASS



@class KochavaTracker;

@class KochavaEvent;

@class KVAConsent;



#pragma mark - PROTOCOL



@protocol KochavaTrackerDelegate <NSObject>

@optional



/*!
 @method - tracker:didRetrieveAttributionDictionary:
 
 @brief A method which is called when attribution has been requested and returned to the app.
 */
- (void)tracker:(nonnull KochavaTracker *)tracker didRetrieveAttributionDictionary:(nonnull NSDictionary *)attributionDictionary;



/*!
 @method - Kochava_attributionResult:
 
 @brief A method which is called when attribution has been requested and returned to the app.
 
 @discussion This method has been deprecated and is scheduled to be permanently removed in v4.0 of this SDK.  Please instead implement tracker:didRetrieveAttributionDictionary:.
 */
- (void)Kochava_attributionResult:(nullable NSDictionary *)attributionResult KOCHAVA_DEPRECATED("Please instead use tracker:didRetrieveAttributionDictionary:");



@end



#if TARGET_OS_TV

@protocol KochavaTrackerJSExport <JSExport>

@property (class, readonly, strong, nonnull) KochavaTracker *shared;

- (void)configureWithParametersDictionary:(nonnull NSDictionary *)parametersDictionary delegate:(nullable id<KochavaTrackerDelegate>)delegate;

- (nullable id)initWithParametersDictionary:(nonnull NSDictionary *)parametersDictionary delegate:(nullable id<KochavaTrackerDelegate>)delegate;

- (void)invalidate;

- (void)sendEvent:(nonnull KochavaEvent *)event;

- (void)sendEventWithNameString:(nonnull NSString *)nameString infoDictionary:(nullable NSDictionary *)infoDictionary;

- (void)sendEventWithNameString:(nonnull NSString *)nameString infoString:(nullable NSString *)infoString;

- (void)sendEventWithNameString:(nonnull NSString *)nameString infoString:(nullable NSString *)infoString appStoreReceiptBase64EncodedString:(nonnull NSString *)appStoreReceiptBase64EncodedString;

- (void)sendIdentityLinkWithDictionary:(nonnull NSDictionary *)dictionary;

- (void)setAppLimitAdTrackingBool:(BOOL)appLimitAdTrackingBool;

- (nullable NSDictionary *)attributionDictionary;

- (void)sendDeepLinkWithOpenURL:(nullable NSURL *)openURL sourceApplicationString:(nullable NSString *)sourceApplicationString;

- (nullable NSString *)deviceIdString;

- (void)handleWatchEvents;

- (void)handleWatchEventsWithWatchIdString:(nullable NSString *)watchIdString;

- (void)sendWatchEventWithNameString:(nonnull NSString *)nameString infoString:(nullable NSString *)infoString;

- (nullable NSString *)sdkVersionString;

- (void)addRemoteNotificationsDeviceToken:(nonnull NSData *)deviceToken;

- (void)removeRemoteNotificationsDeviceToken:(nonnull NSData *)deviceToken;

@property BOOL sleepBool;

@end

#endif



#pragma mark - CONST



/*!
 @constant kKVAParamAppGUIDStringKey
 
 @brief A constant to be used as a key in a key/value pair, where the corresponding value is a Kochava App GUID (String).
 
 @discussion A valid Kochava App GUID String.  The Kochava Server assigns a globally-unique identifier for each app.  This identifier is used to associate post-install events and other data together.  This parameter is required, and must be provided at the time the tracker is configured.
 */
extern NSString * _Nonnull const kKVAParamAppGUIDStringKey;



/*!
 @constant kKVAParamAppLimitAdTrackingBoolKey
 
 @brief A constant to be used as a key in a key/value pair, where the corresponding value is a boolean indicating if advertising tracking should be limited.
 
 @discussion A boolean which when true will limit advertising tracking.  The default state of this feature is false.  This means that by default there is no limit of advertising tracking from the application.  There may still separately be a limit of ad tracking from the operating system, which is a similar but distinct feature of the operating system.  The associated tracker method, and its associated feature, may be used to supplement the operating system feature with application level support.  The app can present the user with a switch-like user interface to “Limit Ad Tracking” similar to the feature provided by the operating system in privacy settings.  When this switch is changed, this method can be used to report the new state.  The purpose of this feature is not to replace the operating system feature, which is ever-present, but to offer another level of privacy which can be integrated within the app’s user interface.
 */
extern NSString * _Nonnull const kKVAParamAppLimitAdTrackingBoolKey;



/*!
 @constant kKVAParamConsentIntelligentManagementBoolKey
 
 @brief A constant to be used as a key in a key/value pair, where the corresponding value is a boolean, wrapped in an NSNumber, indicating if Intelligent Consent Management is enabled.
 
 @discussion The corresponding value should be a boolean wrapped in an NSNumber.  The default is false.  Intelligent Consent Management (ICM) is a feature whereby the SDK will provide information as to when the the requirements for consent have been updated.  When an update occurs, an instance of class KVAConsent can provide a list of partners, as well as the means to know if the host should prompt the user.
 */
extern NSString * _Nonnull const kKVAParamConsentIntelligentManagementBoolKey;



/*!
 @constant kKVAParamConsentManualManagedRequirementsBoolKey
 
 @brief A constant to be used as a key in a key/value pair, where the corresponding value is a boolean, wrapped in an NSNumber, indicating if the Manual Management of Consent Requirements is enabled.
 
 @discussion The corresponding value should be a boolean wrapped in an NSNumber.  The default is false.  This property is optionally used in conjunction with Intelligent Consent Management (ICM).  By default the requirements for consent are determined automatically by Kochava’s servers.  Setting this parameter to true enables you to manage the requirements for consent yourself manually.  When enabled, it is your responsibility to manually manage of the state of var requiredBool, which you would subsequently set to indicate if consent is required for the region in which the device is currently operating.

 */
extern NSString * _Nonnull const kKVAParamConsentManualManagedRequirementsBoolKey;



/*!
 @constant kKVAParamCustomIdStringKey
 
 @brief A constant to use for the key when passing the parameter to the tracker to set the custom id string.
 
 @discussion The corresponding value should be a String.
 */
extern NSString * _Nonnull const kKVAParamCustomIdStringKey KOCHAVA_DEPRECATED("Please instead use the constant string 'custom_id'");



/*!
 @constant kKVAParamIdentityLinkDictionaryKey
 
 @brief A constant to be used as a key in a key/value pair, where the corresponding value is a dictionary providing identity information.
 
 @discussion The corresponding value should be a dictionary containing one or more key/value pairs providing some form of identification.  The key(s) represent a kind of identification and the corresponding value(s) represent an identifying value.  Identity Link provides the opportunity to “link different identities” together.  For example, you may have assigned each user of your app an internal userid which you want to connect to a user’s service identifier.  Using this method, you can send both your internal id and their service identifier and connect them in the Kochava database.  Kochava reports can be output to show additional identity information for devices in the Kochava database so that you can supplement your reports with internal identifiers that are useful to you and your application.
 */
extern NSString * _Nonnull const kKVAParamIdentityLinkDictionaryKey;



/*!
 @constant kKVAParamLogLevelEnumKey
 
 @brief A constant to be used as a key in a key/value pair, where the corresponding value is an enumeration indicating the types of information to be printed to the log.
 
 @discussion The corresponding value should be an NSString matching one of the defined constants for log levels.  Logging is controlled by two parameters.  The first is kKVAParamLogLevelEnumKey, which specifies the types of information to be printed to the log.  The second is kKVAParamLogMultiLineBoolKey, which specifies whether that information prints in a multi-line or continuous format.
 */
extern NSString * _Nonnull const kKVAParamLogLevelEnumKey;



/*!
 @constant kKVAParamLogMultiLineBoolKey
 
 @brief A constant to be used as a key in a key/value pair, where the corresponding value is a boolean indicating if multi-line printing should be used in log entries.
 
 @discussion A boolean.  A value of true will print log entries in a multi-line format.  A value of false will print continuously, wrapping to the next line when needed.  The default value is true.  Logging is controlled by two parameters.  The first is kKVAParamLogLevelEnumKey, which specifies the types of information to be printed to the log.  The second is kKVAParamLogMultiLineBoolKey, which specifies whether that information prints in a multi-line or continuous format.
 */
extern NSString * _Nonnull const kKVAParamLogMultiLineBoolKey;



/*!
 @constant kKVAParamRetrieveAttributionBoolKey
 
 @brief A constant to be used as a key in a key/value pair, where the corresponding value is a boolean indicating if attribution information should be retrieved from the Kochava Server.
 
 @discussion The corresponding value should be a boolean wrapped in an NSNumber.  When true this will cause the tracker to retrieve attribution information from the Kochava Server.  The default value is false.  Note:  This should only be done if your app makes use of this information, otherwise it causes needless network communication.  Attribution will be performed server-side regardless of the application requesting the results.  The tracker will retrieve attribution information if the kKVAParamRetrieveAttributionBoolKey parameter is passed with a value of true during its configuration.  It does this usually within about 10 seconds from the initial launch, although it is subject to a variety of conditions which can cause this time interval to be longer.  Once attribution information has been retrieved, the result is cached locally.  If the KochavaTrackerDelegate instance method tracker(_:didRetrieveAttributionDictionary:) is implemented, it will then also be called.  The attribution information is passed as a parameter.
 */
extern NSString * _Nonnull const kKVAParamRetrieveAttributionBoolKey;



/*!
 @constant kKVAParamStorageIdStringKey
 
 @brief A constant to be used as a key in a key/value pair, where the corresponding value is a storage identifier (String).
 
 @discussion The corresponding value should be a string containing a storage identifier.  The default value is nil.  Typically this key does not need to be configured, and the tracker will operate within a default (unqualified) storage location.  However, if multiple trackers are desired then you must specify a different storage identification string for each so that they can maintain persisted data independently.  Typically one tracker is sufficient.  One example use-case for having multiple trackers is when there are two different companies developing a product jointly, such as when a software development house develops an app under contract for an established brand.  Each organization may want independent control of their own analytics, reporting to different Kochava Accounts.  The value you provide will be appended to the names of keys stored within NSUserDefaults standard user defaults, so it should be a simple string and not too verbose.  Examples: “Developer”, “Principal”, etc.
 */
extern NSString * _Nonnull const kKVAParamStorageIdStringKey;



/*!
 @constant kKVALogLevelEnumNone
 
 @brief A LogLevelEnum of None.
 
 @discussion The None log level generally logs nothing.  It is intended to be an off switch.
 */
extern NSString * _Nonnull const kKVALogLevelEnumNone;



/*!
 @constant kKVALogLevelEnumError
 
 @brief A LogLevelEnum of Error.
 
 @discussion The Error log level generally logs the most severe of exceptions, where the attention of the developer is considered to be required.
 */
extern NSString * _Nonnull const kKVALogLevelEnumError;



/*!
 @constant kKVALogLevelEnumWarn
 
 @brief A LogLevelEnum of Warn (Warning).
 
 @discussion The Warn (Warning) log level generally only logs exceptions that occur outside of normal operation.  With the Warning log level there will be no log entries unless there is something unusual to report, such as an invalid parameter.
 */
extern NSString * _Nonnull const kKVALogLevelEnumWarn;



/*!
 @constant kKVALogLevelEnumInfo
 
 @brief A LogLevelEnum of Info (default).
 
 @discussion The Info log level generally only logs key highlights.  Primarily this includes exceptions that occur outside of normal operation, but it also includes a few key moments such as when an instance of class KVATracker is initialized or deallocated.  Beyond that, with the Info log level there will generally be no log entries unless there is something unusual to report, such as an invalid parameter.
 */
extern NSString * _Nonnull const kKVALogLevelEnumInfo;



/*!
 @constant kKVALogLevelEnumDebug
 
 @brief A LogLevelEnum of Debug.
 
 @discussion The Debug log level expands the logging of the tracker to include details about the internal tasks and NetTransaction(s) occurring within the tracker.  It is useful for diagnostic purposes.  The Debug log level is higher than is recommended for a released app.
 */
extern NSString * _Nonnull const kKVALogLevelEnumDebug;



/*!
 @constant kKVALogLevelEnumTrace
 
 @brief A LogLevelEnum of Trace.
 
 @discussion The Trace log level expands the logging of the tracker to include finite details useful to trace down where something is occurring in the tracker.  It is useful for diagnostic purposes and is generally used by the SDK Developer.  The Trace log level is higher than is recommended for a released app.
 */
extern NSString * _Nonnull const kKVALogLevelEnumTrace;



/*!
 @constant kKVAMessagesAppViewControllerDidBecomeActiveNotificationNameString
 
 @brief A string to use as the name for a notification that a MessagesAppViewController did become active.
 */
extern NSString * _Nonnull const kKVAMessagesAppViewControllerDidBecomeActiveNotificationNameString;



/*!
 @constant kKVAMessagesAppViewControllerDidResignActiveNotificationNameString
 
 @brief A string to use as the name for a notification that a MessagesAppViewController did resign active.
 */
extern NSString * _Nonnull const kKVAMessagesAppViewControllerDidResignActiveNotificationNameString;



#pragma mark - INTERFACE



/*!
 @class KochavaTracker
 
 @brief The class KochavaTracker provides an interface between a host application and Kochava’s Attribution and Analytics Servers.  A tracker manages the exchange of data between these two entities, along with the associated tasks and network transactions.

 @discussion The class KochavaTracker is the main interface for the KochavaTracker SDK.  If you have not already integrated a KochavaTracker SDK into your project, refer to our KochavaTracker iOS SDK support documentation.
 
 You rarely create instances of the KochavaTracker class.  Instead, you configure a provided shared instance using the designated configuration instance method configure(withParametersDictionary:delegate:).
 
 From there, the tracker proceeds to initialize immediately and perform its various tasks.  This is typically done during the earliest phases of the host’s life-cycle, so that installation attribution can be quickly established and post-install events may immediately begin to be queued.
 
 You may alternately create an instance of the KochavaTracker class.  If you do, it is your responsibility to maintain a strong reference.  And if you create multiple instances, it is your responsibility to configure each with a unique storage identifier.
 
 @author Kochava, Inc.
 
 @copyright 2013 - 2018 Kochava, Inc.
 */
#if TARGET_OS_TV
@interface KochavaTracker : NSObject <KochavaTrackerJSExport>
#else
@interface KochavaTracker : NSObject
#endif



#pragma mark - CLASS PROPERTIES
#pragma mark KochavaTracker.shared (Singleton Shared Instance)



/*!
 @property shared
 
 @brief A shared instance, for convenience.
 
 @discussion This is the preferred way of using a tracker.  To complete the integration you must call configureWithParametersDictionary:delegate:.  You may alternatively use the designated initializer to create your own tracker.  The shared instance provides a few benefits.  First, it simplifies your implementation as you do not need to store an instance to the tracker somewhere in a public location in your own code.  Second, it ensures that if your code unintentionally tries to make use of the shared instance prior to configuration that you can receive a warning in the log from the tracker.  If you use your own property to store the tracker, and it is nil, then this provision would not be automatically available to you.
 */
@property (class, readonly, strong, nonnull) KochavaTracker *shared;



#pragma mark - LIFECYCLE



/*!
 @method - configureWithParametersDictionary:delegate:
 
 @brief The main configuration method for use with the shared instance.  This method configures (or reconfigures) a tracker with a parametersDictionary.  When using the shared this method must be called prior to using the tracker.
 
 @discussion This method configures the tracker with parameters passed in a parametersDictionary.  It is intended for use with the shared instance only.  By calling the KochavaTracker configuration method, you have completed the basic integration with the KochavaTracker SDK.  The call to the configuration method should be located in the logic of your application where things first start up, such as your App Delegate's application:didFinishLaunchingWithOptions: method.

 @param parametersDictionary a dictionary containing any number of parameters with which to configure the tracker.
 
 @param delegate A delegate which can be used to return attribution information along with other information (optional).
 
 @code
 NSMutableDictionary *parametersDictionary = NSMutableDictionary.dictionary;
 parametersDictionary[kKVAParamAppGUIDStringKey] = @"_YOUR_KOCHAVA_APP_GUID_";
 parametersDictionary[kKVAParamLogLevelEnumKey] = kKVALogLevelEnumInfo;
 [KochavaTracker.shared configureWithParametersDictionary:parametersDictionary delegate:self];
 @endcode
*/
- (void)configureWithParametersDictionary:(nonnull NSDictionary *)parametersDictionary delegate:(nullable id<KochavaTrackerDelegate>)delegate;



/*!
 @method - initWithParametersDictionary:delegate:
 
 @brief The designated initializer for a Kochava Tracker.
 
 @discussion This method initializes a tracker with parameters passed in a parametersDictionary.  By calling the KochavaTracker initializer, you have completed the basic integration with the KochavaTracker SDK.  The call to the initializer should be located in the logic of your application where things first start up, such as your App Delegate's application:didFinishLaunchingWithOptions: method.
 
 @param parametersDictionary A dictionary containing the tracker's parameters.
 
 @param delegate A delegate which can be used to return attribution information along with other information (optional).
 
 @return A tracker, or possibly nil if the dictionary did not contain valid properties to form one.
 
 @code
 NSMutableDictionary *parametersDictionary = NSMutableDictionary.dictionary;
 parametersDictionary[kKVAParamAppGUIDStringKey] = @"_YOUR_KOCHAVA_APP_GUID_";
 parametersDictionary[kKVAParamLogLevelEnumKey] = kKVALogLevelEnumInfo;
 KochavaTracker *kochavaTracker = [[KochavaTracker alloc] initWithParametersDictionary:parametersDictionary delegate:self];
 @endcode
 */
- (nullable id)initWithParametersDictionary:(nonnull NSDictionary *)parametersDictionary delegate:(nullable id<KochavaTrackerDelegate>)delegate;



/*!
 @method - invalidate
 
 @brief Invalidates an instance of class KochavaTracker.
 
 @discussion This is similar to allowing an instance of the tracker deallocate, but it can also be used on the shared instance.  It will additionally signal certain sub-systems to invalidate themselves, which can result in a more assured and immediate halt.  The scope of this invalidation is not absolute.  Certain sub-systems will continue to run for a period of time until they may gracefully complete.  When using this method with the shared instance, you are guaranteed to be re-defaulted a new instance the next time it is referenced, and you may immediately move forward to re-configure it.
 
 When you are not using Intelligent Consent Management, this method can be used to signal that the tracker may no longer run following consent having been denied.  When used this way, you may re-configure a tracker if/when consent is granted.
 */
- (void)invalidate;



#pragma mark - PROPERTIES



/*!
 @property consent
 
 @brief A master instance of class KVAConsent.
 
 @discussion Data sharing privacy laws such as GDPR require consent to be obtained before certain kinds of personal data may be calculated or gathered, kept in memory, persisted or retained in persistent storage, and/or shared with partners.  During the natural lifecycle, there are times where partners may be added and cause the consent status to fall back to an unknown state.  Later the user may again be prompted and the consent status may (or may not) again come to be known.  All of this is predicated upon whether or not consent is required, which is governed by a variety of factors such as location.
 */
@property (strong, nonatomic, nonnull, readonly) KVAConsent *consent;



/*!
 @property sleepBool
 
 @brief A boolean which when true (YES) causes the tracker to sleep.
 
 @discussion The default is false (NO).  When set to true (YES), this causes tasks to effectively be suspended until this condition is lifted.  While this is set to true, tasks are not lost per-say;  however, if a task may have otherwise occurred multiple times, it may be represented only once once the condition is lifted.
 */
@property BOOL sleepBool;



#pragma mark - GENERAL



/*!
 @method - sendEvent:
 
 @brief A method to queue an event with standardized parameters to be sent to the server.
 
 @param event A KochavaEvent configured with the values you want to associate with the event.
 */
- (void)sendEvent:(nonnull KochavaEvent *)event;



/*!
 @method - sendEventWithNameString:infoDictionary:
 
 @brief A method to queue an event with custom parameters to be sent to server.
 
 @param nameString String containing event title or key of key/value pair.
 
 @param infoDictionary Dictionary (single dimensional) containing any number of values with keys.
 */
- (void)sendEventWithNameString:(nonnull NSString *)nameString infoDictionary:(nullable NSDictionary *)infoDictionary;



/*!
 @method - sendEventWithNameString:infoString:
 
 @brief A method to queue an event with custom parameters to be sent to server.
 
 @param nameString String containing event title or key of key/value pair.
 
 @param infoString String containing event value or value of key/value pair.  It may be an unnested (single dimensional) dictionary converted to a JSON formatted string.
 */
- (void)sendEventWithNameString:(nonnull NSString *)nameString infoString:(nullable NSString *)infoString;



/*!
 @method - sendIdentityLinkWithDictionary:
 
 @brief A method to queue an Identity Link event to be sent to server.
 
 @param dictionary A dictionary containing key/value pairs to be associated with the app install.  The keys may be any string value.  The values may be any string or numeric value.
 
    Important Note:  When possible, Identity Link information should be provided using the kKVAParamIdentityLinkDictionaryKey when the tracker is being configured, as opposed to using instance method sendIdentityLinkWithDictionary:, to ensure that your identity values are always associated with your install.
 */
- (void)sendIdentityLinkWithDictionary:(nonnull NSDictionary *)dictionary;



/*!
 @method - setAppLimitAdTrackingBool:
 
 @brief A method to limit ad tracking at the application level.
 
 @discussion This feature is related to the Limit Ad Tracking feature which is typically found on an Apple device under Settings, Privacy, Advertising.  In the same way that you can limit ad tracking through that setting, this feature provides a second and independent means for the host app to limit ad tracking by asking the user directly.  A value of NO (false) from either feature (this or Apple's) will result in the limiting of ad tracking.
 
 @param appLimitAdTrackingBool A boolean toggling app level limit ad tracking on (YES) or off (NO).
 */
- (void)setAppLimitAdTrackingBool:(BOOL)appLimitAdTrackingBool;



/*!
 @method - attributionDictionary
 
 @brief A method to return the attribution information previously retrieved from the server (if any).
 
 @discussion The use of this method assumes that the tracker was previously requested to retrieve attribution during its configuration.  It is intended that this information be passed automatically back to the parent through delegation.  This method can be used to re-retrieve the same information, but if it is called before attribution information has been retrieved then the result will be nil.
 
 @return a dictionary containing attribution information (or nil).
 */
- (nullable NSDictionary *)attributionDictionary;



/*!
 @method - sendDeepLinkWithOpenURL:sourceApplicationString:
 
 @brief A method to queue a deep-link and its associated data to be sent to server.
 
 @param openURL The url received by the openURL application delegate method.
 
 @param sourceApplicationString The sourceApplication string received by the openURL application delegate method.
 */
- (void)sendDeepLinkWithOpenURL:(nullable NSURL *)openURL sourceApplicationString:(nullable NSString *)sourceApplicationString;



/*!
 @method - deviceIdString
 
 @brief A method to return the unique device ID that was generated when the tracker was first initialized on the current device.
 */
- (nullable NSString *)deviceIdString;



/*!
 @method - handleWatchEvents
 
 @brief A method to tell the server that an Apple Watch has been used with this app.
 
 @discussion If you have a unique identifier to associate with the Apple Watch, you should instead call handleWatchEventsWithWatchIdString:.
 */
- (void)handleWatchEvents;



/*!
 @method - handleWatchEventsWithWatchIdString:
 
 @brief A method to tell the server that a specific, identifiable Apple Watch has been used with this app.
 
 @param watchIdString The name or identifier of watch used with the app.
 */
- (void)handleWatchEventsWithWatchIdString:(nullable NSString *)watchIdString;



/*!
 @method - sendWatchEventWithNameString:infoString:
 
 @brief A method to queue an Apple Watch event to be sent to server.
 
 @param nameString String containing event title or key of key/value pair.
 
 @param infoString String containing event value or value of key/value pair.  Value may be an unnested (single dimensional) dictionary converted to a JSON formatted string.
 */
- (void)sendWatchEventWithNameString:(nonnull NSString *)nameString infoString:(nullable NSString *)infoString;



/*!
 @method - sdkVersionString
 
 @brief A method to return the sdk version string.
 
 @discussion The returned value includes the name of the SDK, followed by its semantic version.
 */
- (nullable NSString *)sdkVersionString;



/*!
 @method - addRemoteNotificationsDeviceToken:
 
 @brief A method which adds a remote notifications device token.
 
 @param deviceToken The device token as provided in NSData.
 */
- (void)addRemoteNotificationsDeviceToken:(nonnull NSData *)deviceToken;



/*!
 @method - removeRemoteNotificationsDeviceToken:
 
 @brief A method which removes any assocation for this device with any previously registered remote notifications device token.
 
 @param deviceToken The device token as provided in NSData.
 */
- (void)removeRemoteNotificationsDeviceToken:(nonnull NSData *)deviceToken;



#pragma mark - DEPRECATED



/*!
 @brief An initializer for a Kochava Tracker (Constructor).
 
 @discussion This method has been deprecated and is scheduled to be permanently removed in v4.0 of this SDK.  Please initialize a tracker either using the shared, or else using initWithParametersDictionary:delegate:.  In Swift: init(parametersDictionary:delegate:)
 */
- (nullable id)initKochavaWithParams:(nonnull NSDictionary *)parametersDictionary KOCHAVA_DEPRECATED("Please initialize a tracker either using the shared, or else using initWithParametersDictionary:delegate:.  In Swift: init(parametersDictionary:delegate:)");



/*!
 @method - identityLinkEvent:
 
 @brief A method to queue an Identity Link event to be sent to server.
 
 @param dictionary A dictionary containing key/value pairs to be associated with the app install.
 
 @discussion This method has been deprecated and is scheduled to be permanently removed in v4.0 of this SDK.  Please instead use sendIdentityLinkWithDictionary:.  In Swift: sendIdentityLink(with:)
 */
- (void)identityLinkEvent:(nonnull NSDictionary *)dictionary KOCHAVA_DEPRECATED("Please instead use sendIdentityLinkWithDictionary:.  In Swift: sendIdentityLink(with:)");



/*!
 @method - trackEvent:value:
 
 @brief A method to queue an event with custom parameters to be sent to server.
 
 @param titleString String containing event title or key of key/value pair.
 
 @param valueString String containing event value or value of key/value pair.  Value may be an unnested (single dimensional) dictionary converted to a JSON formatted string.
 
 @discussion This method has been deprecated and is scheduled to be permanently removed in v4.0 of this SDK.  Please instead use sendEventWithNameString:infoString:.  In Swift: sendEvent(withNameString:infoString:)
 */
- (void)trackEvent:(nonnull NSString *)titleString value:(nullable NSString *)valueString KOCHAVA_DEPRECATED("Please instead use sendEventWithNameString:infoString:.  In Swift: sendEvent(withNameString:infoString:)");



/*!
 @method - trackEvent:withValue:andReceipt:
 
 @brief A method to queue an event with a receipt to be sent to server.
 
 @param titleString String containing event title or key of key/value pair.
 
 @param valueString String containing event value or value of key/value pair.  Value may be an unnested (single dimensional) dictionary converted to a JSON formatted string.
 
 @param appStoreReceiptBase64EncodedString String containing an App Store base64 encoded receipt.
 
 @discussion This method has been deprecated and is scheduled to be permanently removed in v4.0 of this SDK.  Please instead use sendEventWithNameString:infoString:appStoreReceiptBase64EncodedString.  In Swift: sendEvent(withNameString:infoString:appStoreReceiptBase64EncodedString:)
 */
- (void)trackEvent:(nonnull NSString *)titleString withValue:(nullable NSString *)valueString andReceipt:(nonnull NSString *)appStoreReceiptBase64EncodedString KOCHAVA_DEPRECATED("Please instead use sendEventWithNameString:infoString:appStoreReceiptBase64EncodedString.  In Swift: sendEvent(withNameString:infoString:appStoreReceiptBase64EncodedString:)");



/*!
 @method - setLimitAdTracking:
 
 @brief A method to limit ad tracking at the application level.
 
 @discussion This feature is related to the Limit Ad Tracking feature which is typically found on an Apple device under Settings, Privacy, Advertising.  In the same way that you can limit ad tracking through that setting, this feature provides a second and independent means for the host app to limit ad tracking by asking the user directly.  A value of NO (false) from either feature (this or Apple's) will result in the limiting of ad tracking.
 
 @param limitAdTrackingBool A boolean toggling app level limit ad tracking on (YES) or off (NO).
 
 @discussion This method has been deprecated and is scheduled to be permanently removed in v4.0 of this SDK.  Please instead use setAppLimitAdTrackingBool:
 */
- (void)setLimitAdTracking:(BOOL)limitAdTrackingBool KOCHAVA_DEPRECATED("Please instead use setAppLimitAdTrackingBool:");



/*!
 @method - sendDeepLink:sourceApplication:
 
 @brief A method to queue a deep-link and its associated data to be sent to server.
 
 @param url The url received by the openURL application delegate method.
 
 @param sourceApplication The sourceApplication string received by the openURL application delegate method.
 
 @discussion This method has been deprecated and is scheduled to be permanently removed in v4.0 of this SDK.  Please instead use sendDeepLinkWithOpenURL:sourceApplicationString:.  In Swift: sendDeepLink(withOpen:sourceApplicationString:)
 */
- (void)sendDeepLink:(nullable NSURL *)url sourceApplication:(nullable NSString *)sourceApplication KOCHAVA_DEPRECATED("Please instead use sendDeepLinkWithOpenURL:sourceApplicationString:.  In Swift: sendDeepLink(withOpen:sourceApplicationString:)");



/*!
 @method - getKochavaDeviceId
 
 @brief A method to return the device ID generated when the tracker was initialized.
 
 @discussion This method has been deprecated and is scheduled to be permanently removed in v4.0 of this SDK.  Please instead use deviceIdString.
 */
- (nullable NSString *)getKochavaDeviceId KOCHAVA_DEPRECATED("Please instead use deviceIdString");



/*!
 @method - retrieveAttribution
 
 @brief A method to return the attribution information previously retrieved from the server (if any).
 
 @discussion The use of this method assumes that the tracker was previously requested to retrieve attribution during its configuration.  It is intended that this information be passed automatically back to the parent through delegation.  This method can be used to re-retrieve the same information, but if it is called before attribution information has been retrieved then the result will be nil.
 
 This method has been deprecated and is scheduled to be permanently removed in v4.0 of this SDK.  Please instead use attributionDictionary.
 
 @return a dictionary containing attribution information (or nil).
 */
- (nullable id)retrieveAttribution KOCHAVA_DEPRECATED("Please instead use attributionDictionary");



/*!
 @method - handleWatchEvents:
 
 @brief A method to tell the server that a specific, identifiable Apple Watch has been used with this app.
 
 @param watchIdString The name or identifier of watch used with the app.
 
 @discussion This method has been deprecated and is scheduled to be permanently removed in v4.0 of this SDK.  Please instead use handleWatchEventsWithWatchIdString:
 */
- (void)handleWatchEvents:(nullable NSString *)watchIdString KOCHAVA_DEPRECATED("Please instead use handleWatchEventsWithWatchIdString:");



/*!
 @method - trackWatchEvent:value:
 
 @brief A method to queue an Apple Watch event to be sent to server.
 
 @param titleString String containing event title or key of key/value pair.
 
 @param valueString String containing event value or value of key/value pair.  Value may be an unnested (single dimensional) dictionary converted to a JSON formatted string.
 
 @discussion This method has been deprecated and is scheduled to be permanently removed in v4.0 of this SDK.  Please instead use sendWatchEventWithNameString:infoString:.  In Swift: sendWatchEvent(withNameString:infoString:)
 */
- (void)trackWatchEvent:(nonnull NSString *)titleString valueString:(nullable NSString *)valueString KOCHAVA_DEPRECATED("Please instead use sendWatchEventWithNameString:infoString:.  In Swift: sendWatchEvent(withNameString:infoString:)");



- (void)trackEvent:(nonnull NSString *)titleString :(nullable NSString *)valueString
KOCHAVA_DEPRECATED("Please instead use sendEventWithNameString:infoString:.  In Swift: sendEvent(withNameString:infoString:)");

- (void)sendDeepLink:(nullable NSURL *)url :(nullable NSString *)sourceApplication
KOCHAVA_DEPRECATED("Please instead use sendDeepLinkWithOpenURL:sourceApplicationString:.  In Swift: sendDeepLink(withOpen:sourceApplicationString:)");

- (void)trackWatchEvent:(nonnull NSString *)titleString :(nullable NSString *)valueString
KOCHAVA_DEPRECATED("Please instead use sendWatchEventWithNameString:infoString:.  In Swift: sendWatchEvent(withNameString:infoString:)");



/*!
 @method - sendEventWithEventStandardParameters:
 
 @brief A method to queue an event with standardized parameters to be sent to the server.
 
 @param eventStandardParameters EventStandardParameters configured with the values you want to associate with the event.

 @discussion This method has been deprecated and is scheduled to be permanently removed in v4.0 of this SDK.  Please instead use sendEvent:.  In Swift: send(_ event:)
 */
- (void)sendEventWithEventStandardParameters:(nonnull KochavaEvent *)eventStandardParameters KOCHAVA_DEPRECATED("The class EventStandardParameters has been renamed to KochavaEvent.  Please instead use sendEvent: , and also rename the class EventStandardParameters to KochavaEvent wherever you have used it.");



/*!
 @method - sendEventWithNameString:infoString:appStoreReceiptBase64EncodedString:
 
 @brief A method to queue an event with a receipt to be sent to server.
 
 @param nameString String containing event title or key of key/value pair.
 
 @param infoString String containing event value or value of key/value pair.  It may be an unnested (single dimensional) dictionary converted to a JSON formatted string.
 
 @param appStoreReceiptBase64EncodedString String containing an App Store base64 encoded receipt.

 @discussion This method has been deprecated and is scheduled to be permanently removed in v4.0 of this SDK.  Please instead use sendEvent:.  In Swift: send(_ event:)
 */
- (void)sendEventWithNameString:(nonnull NSString *)nameString infoString:(nullable NSString *)infoString appStoreReceiptBase64EncodedString:(nonnull NSString *)appStoreReceiptBase64EncodedString KOCHAVA_DEPRECATED("Please instead use sendEvent:.  In Swift: send(_ event:).  Create a KochavaEvent and pass the appStoreReceiptBase64EncodedString using the standard parameter.  You may use KochavaEventTypeEnumPurchase, and set any of the other applicable standard parameters.");



@end



#endif



