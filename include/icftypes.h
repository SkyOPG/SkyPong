/*** Autogenerated by WIDL 7.0 from include/icftypes.idl - Do not edit ***/

#ifdef _WIN32
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif
#include <rpc.h>
#include <rpcndr.h>
#endif

#ifndef COM_NO_WINDOWS_H
#include <windows.h>
#include <ole2.h>
#endif

#ifndef __icftypes_h__
#define __icftypes_h__

/* Forward declarations */

/* Headers for imported files */

#include <wtypes.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum NET_FW_PROFILE_TYPE_ {
    NET_FW_PROFILE_DOMAIN = 0,
    NET_FW_PROFILE_STANDARD = 1,
    NET_FW_PROFILE_CURRENT = 2,
    NET_FW_PROFILE_TYPE_MAX = 3
} NET_FW_PROFILE_TYPE;
typedef enum NET_FW_PROFILE_TYPE2_ {
    NET_FW_PROFILE2_DOMAIN = 0x1,
    NET_FW_PROFILE2_PRIVATE = 0x2,
    NET_FW_PROFILE2_PUBLIC = 0x4,
    NET_FW_PROFILE2_ALL = 0x7fffffff
} NET_FW_PROFILE_TYPE2;
typedef enum NET_FW_IP_VERSION_ {
    NET_FW_IP_VERSION_V4 = 0,
    NET_FW_IP_VERSION_V6 = 1,
    NET_FW_IP_VERSION_ANY = 2,
    NET_FW_IP_VERSION_MAX = 3
} NET_FW_IP_VERSION;
typedef enum NET_FW_POLICY_TYPE_ {
    NET_FW_POLICY_GROUP = 0,
    NET_FW_POLICY_LOCAL = 1,
    NET_FW_POLICY_EFFECTIVE = 2,
    NET_FW_POLICY_TYPE_MAX = 3
} NET_FW_POLICY_TYPE;
typedef enum NET_FW_SCOPE_ {
    NET_FW_SCOPE_ALL = 0,
    NET_FW_SCOPE_LOCAL_SUBNET = 1,
    NET_FW_SCOPE_CUSTOM = 2,
    NET_FW_SCOPE_MAX = 3
} NET_FW_SCOPE;
typedef enum NET_FW_SERVICE_TYPE_ {
    NET_FW_SERVICE_FILE_AND_PRINT = 0,
    NET_FW_SERVICE_UPNP = 1,
    NET_FW_SERVICE_REMOTE_DESKTOP = 2,
    NET_FW_SERVICE_NONE = 3,
    NET_FW_SERVICE_TYPE_MAX = 4
} NET_FW_SERVICE_TYPE;
typedef enum NET_FW_IP_PROTOCOL_ {
    NET_FW_IP_PROTOCOL_TCP = 6,
    NET_FW_IP_PROTOCOL_UDP = 17
} NET_FW_IP_PROTOCOL;
typedef enum NET_FW_RULE_DIRECTION_ {
    NET_FW_RULE_DIR_IN = 1,
    NET_FW_RULE_DIR_OUT = 2,
    NET_FW_RULE_DIR_MAX = 3
} NET_FW_RULE_DIRECTION;
typedef enum NET_FW_ACTION_ {
    NET_FW_ACTION_BLOCK = 0,
    NET_FW_ACTION_ALLOW = 1,
    NET_FW_ACTION_MAX = 2
} NET_FW_ACTION;
typedef enum NET_FW_MODIFY_STATE_ {
    NET_FW_MODIFY_STATE_OK = 0,
    NET_FW_MODIFY_STATE_GP_OVERRIDE = 1,
    NET_FW_MODIFY_STATE_INBOUND_BLOCKED = 2
} NET_FW_MODIFY_STATE;
/* Begin additional prototypes for all interfaces */


/* End additional prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __icftypes_h__ */