#pragma once
#ifndef _CCSDS_FILE_DELIVERY_PROTOCOL_H
#define _CCSDS_FILE_DELIVERY_PROTOCOL_H

typedef enum
{
    CfdpCreateFile = 0,
    CfdpDeleteFile,
    CfdpRenameFile,
    CfdpAppendFile,
    CfdpReplaceFile,
    CfdpCreateDirectory,
    CfdpRemoveDirectory,
    CfdpDenyFile,
    CfdpDenyDirectory
}CfdpAction;

typedef enum
{
    CfdpProxyPutRequest = 0,
    CfdpProxyMsgToUser,
    CfdpProxyFilestoreRequest,
    CfdpProxyFaultHandlerOverride,
    CfdpProxyTransmissionMode,
    CfdpProxyFlowLabel,
    CfdpProxySegmentationControl,
    CfdpProxyPutResponse,
    CfdpProxyFilestoreResponse,
    CfdpProxyPutCancel,
    CfdpDirectoryListingRequest = 0x10,
    CfdpDirectoryListingResponse,
    CfdpRemoteStatusReportRequest = 0x20,
    CfdpRemoteStatusReportResponse,
    CfdpRemoteSuspendRequest = 0x30,
    CfdpRemoteSuspendResponse,
    CfdpRemoteResumeRequest = 0x38,
    CfdpRemoteResumeResponse,
    CfdpSFORequest = 0x40,
    CfdpSFOMsgToUser,
    CfdpSFOFlowLabel,
    CfdpSFOFaultHandlerOverride,
    CfdpSFOFilestoreRequest,
    CfdpSFOReport,
    CfdpSFOFileStoreResponse
}CfdpUserMsgType;

typedef enum
{
    CfdpNoError = 0,
    CfdpAckLimitReached,
    CfdpKeepaliveLimitReached,
    CfdpInvalidTransmissionMode,
    CfdpFilestoreRejection,
    CfdpChecksumFailure,
    CfdpFileSizeError,
    CfdpNakLimitReached,
    CfdpInactivityDetected,
    CfdpInvalidFileStructure,
    CfdpCheckLimitReached,
    CfdpSuspendRequestReceived = 0x1110,
    CfdpCancelRequestReceived
}CfdpCondition;

typedef enum
{
    CfdpNoHandler = 0,
    CfdpCancel,
    CfdpSuspend,
    CfdpIgnore,
    CfdpAbandon
}CfdpHandler;

typedef enum
{
    CfdpFileDiscarded = 0,
    CfdpFileRejected,
    CfdpFileRetained,
    CfdpFileStatusUnreported
}CfdpFileStatus;

#endif