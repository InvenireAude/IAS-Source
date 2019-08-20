/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemFmt-MQPCF/src/qs/fmt/pcf/Dictionary.cpp 
 *
 * Licensed under the Invenire Aude Commercial License (the "License");
 * you may not use this file except in compliance with the License. 
 * You may find the license terms and conditions in the LICENSE.txt file.
 * or at http://www.invenireaude.com/licenses/license.txt
 * 
 * This file and any derived form, including but not limited to object
 * executable, represents the Confidential Materials.
 * 
 */
#include "Dictionary.h"
#include <qs/log/LogLevel.h>
#include <cmqc.h>
#include <cmqcfc.h>
#include <cmqxc.h>

namespace IAS {
namespace QS {
namespace Fmt {
namespace PCF {

/*************************************************************************/
Dictionary::Dictionary(){
	IAS_TRACER;
	initializeCommandID2Name();
	initializeParameterID2Name();
	initializeType2NS();
	initializeMQSCNames();
	initializeQType2Name();
	initializeChlType2Name();
	initializeChlStatus2Name();
	initializeEventOriginName();
	initializeReasonName();
	initializeCompCodeName();
}
/*************************************************************************/
Dictionary::~Dictionary() throw(){
	IAS_TRACER;
}
/*************************************************************************/
const String& Dictionary::getTypeNS(MQLONG iType)const{

	IAS_TRACER;
	if(hmType2NS.count(iType) == 0)
		IAS_THROW(ItemNotFoundException("MQ PCF Type:")<<iType)

	return hmType2NS.at(iType);
}
/*************************************************************************/
const String& Dictionary::getQTypeName(MQLONG iType)const{

	IAS_TRACER;
	if(hmQType2Name.count(iType) == 0)
		IAS_THROW(ItemNotFoundException("MQ Queue Type:")<<iType)

	return hmQType2Name.at(iType);
}
/*************************************************************************/
const String& Dictionary::getChlTypeName(MQLONG iType)const{

	IAS_TRACER;
	if(hmChlType2Name.count(iType) == 0)
		IAS_THROW(ItemNotFoundException("MQ Channel Type:")<<iType)

	return hmChlType2Name.at(iType);
}
/*************************************************************************/
const String& Dictionary::getChlStatusName(MQLONG iType)const{

	IAS_TRACER;
	if(hmChlStatus2Name.count(iType) == 0)
		IAS_THROW(ItemNotFoundException("MQ Channel Status:")<<iType)

	return hmChlStatus2Name.at(iType);
}
/*************************************************************************/
const String& Dictionary::getParameterName(MQLONG iParameter)const{

	IAS_TRACER;
	if(hmParameterID2Name.count(iParameter) == 0)
		IAS_THROW(ItemNotFoundException("Missing MQ PCF Parameter:")<<iParameter)

	return hmParameterID2Name.at(iParameter);
}
/*************************************************************************/
const String& Dictionary::getCommandName(MQLONG iCommand)const{
	IAS_TRACER;
	if(hmCommandID2Name.count(iCommand) == 0)
		IAS_THROW(ItemNotFoundException("MQ PCF Command:")<<iCommand)

	return hmCommandID2Name.at(iCommand);
}
/*************************************************************************/
const MQLONG Dictionary::getTypeID(const String& strNS)const{
	IAS_TRACER;

	if(hmNS2Type.count(strNS) == 0)
		IAS_THROW(ItemNotFoundException("MQ PCF Type:" + strNS));

	return hmNS2Type.at(strNS);
}
/*************************************************************************/
const MQLONG Dictionary::getQTypeID(const String& strName)const{
	IAS_TRACER;

	if(hmName2QType.count(strName) == 0)
		IAS_THROW(ItemNotFoundException("MQ Queue Type:" + strName));

	return hmName2QType.at(strName);
}
/*************************************************************************/
const MQLONG Dictionary::getChlTypeID(const String& strName)const{
	IAS_TRACER;

	if(hmName2ChlType.count(strName) == 0)
		IAS_THROW(ItemNotFoundException("MQ Channel Type:" + strName));

	return hmName2ChlType.at(strName);
}
/*************************************************************************/
const MQLONG Dictionary::getChlStatusID(const String& strName)const{
	IAS_TRACER;

	if(hmName2ChlStatus.count(strName) == 0)
		IAS_THROW(ItemNotFoundException("MQ Channel Status:" + strName));

	return hmName2ChlStatus.at(strName);
}
/*************************************************************************/
const MQLONG Dictionary::getParameterID(const String& strParameter)const{
	IAS_TRACER;

	if(hmParameterName2ID.count(strParameter) == 0)
		IAS_THROW(ItemNotFoundException("Missing MQ PCF Parameter:" + strParameter));

	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"getParameterID: "<<strParameter<<"="<<hmParameterName2ID.at(strParameter))

	return hmParameterName2ID.at(strParameter);
}
/*************************************************************************/
const MQLONG Dictionary::getCommandID(const String& strCommand)const{
	IAS_TRACER;

	if(hmCommandName2ID.count(strCommand) == 0)
		IAS_THROW(ItemNotFoundException("MQ PCF Command:" + strCommand));


	return hmCommandName2ID.at(strCommand);
}
/*************************************************************************/
const String& Dictionary::getMQSCName(MQLONG iCommand)const{
	IAS_TRACER;
	if(hmMQSCNames.count(iCommand) == 0)
		IAS_THROW(ItemNotFoundException("MQSC Command:")<<iCommand)

	return hmMQSCNames.at(iCommand);
}
/*************************************************************************/
const String& Dictionary::getEventOriginName(MQLONG iOrigin)const{
	IAS_TRACER;
	if(hmEventOriginName.count(iOrigin) == 0)
		IAS_THROW(ItemNotFoundException("Event Origin:")<<iOrigin)

	return hmEventOriginName.at(iOrigin);
}
/*************************************************************************/
const String& Dictionary::getCompCode(MQLONG iCompCode)const{

	if(hmCompCodeName.count(iCompCode) == 0)
		IAS_THROW(ItemNotFoundException("Missing Completion Code: ")<<iCompCode)

	return hmCompCodeName.at(iCompCode);
}
/*************************************************************************/
const String& Dictionary::getReason(MQLONG iReason)const{

	if(hmReasonName.count(iReason) == 0)
		IAS_THROW(ItemNotFoundException("Missing Reason Code: ")<<iReason)

	return hmReasonName.at(iReason);
}
/*************************************************************************/
const String& Dictionary::getChannelStopMode(MQLONG iMode)const{
	IAS_TRACER;

	static const String strQuiesce("QUIESCE");
	static const String strForce("FORCE");
	static const String strTerminate("TERMINATE");

	switch(iMode){
		case MQMODE_QUIESCE:
			return strQuiesce;
		case MQMODE_FORCE:
			return strForce;
		case MQMODE_TERMINATE:
			return strTerminate;
		default:
			IAS_THROW(ItemNotFoundException("Mode: ")<<iMode)
		}

}
/*************************************************************************/
MQLONG Dictionary::getChannelStopModeID(const String& strMode)const{
	IAS_TRACER;

	if(strMode.compare("QUIESCE")){
		return MQMODE_QUIESCE;
	}else if(strMode.compare("FORCE")){
		return MQMODE_FORCE;
	}else if(strMode.compare("TERMINATE")){
		return MQMODE_TERMINATE;
	}else
		IAS_THROW(ItemNotFoundException("Mode: "+strMode));

}
/*************************************************************************/
const String& Dictionary::getChannelInDoubt(MQLONG iStatus)const{
	IAS_TRACER;

	static const String strCommit("COMMIT");
	static const String strRollback("ROLLBACK");

	switch(iStatus) {
		case MQMODE_QUIESCE:
			return strCommit;
		case MQIDO_BACKOUT:
			return strRollback;
		default:
		IAS_THROW(ItemNotFoundException("Mode: ")<<iStatus)
	}
}
/*************************************************************************/
MQLONG Dictionary::getChannelInDoubtID(const String& strStatus)const{
	IAS_TRACER;

	if(strStatus.compare("COMMIT")){
		return MQIDO_COMMIT;
	}else if(strStatus.compare("BACKOUT")){
		return MQIDO_BACKOUT;
	}else
		IAS_THROW(ItemNotFoundException("Mode: "+strStatus));
}
/*************************************************************************/
void Dictionary::initializeType2NS(){
	IAS_TRACER;

	hmType2NS[MQCFT_ACCOUNTING] = "http://www.invenireaude.com/qsystem/fmt/pcf/accounting/cmd";
	hmType2NS[MQCFT_COMMAND]    = "http://www.invenireaude.com/qsystem/fmt/pcf/admin/cmd";
	hmType2NS[MQCFT_RESPONSE]   = "http://www.invenireaude.com/qsystem/fmt/pcf/adminresp/cmd";
	hmType2NS[MQCFT_EVENT]      = "http://www.invenireaude.com/qsystem/fmt/pcf/event/cmd";
	hmType2NS[MQCFT_STATISTICS] = "http://www.invenireaude.com/qsystem/fmt/pcf/statistics/cmd";

	for(HashMap::const_iterator it=hmType2NS.begin();
			it != hmType2NS.end(); it++){
			hmNS2Type[it->second]=it->first;
		}
}
/*************************************************************************/
void Dictionary::initializeQType2Name(){
	IAS_TRACER;

	hmQType2Name[MQQT_LOCAL]   = "LOCAL";
	hmQType2Name[MQQT_MODEL]   = "MODEL";
	hmQType2Name[MQQT_ALIAS]   = "ALIAS";
	hmQType2Name[MQQT_REMOTE]  = "REMOTE";
	hmQType2Name[MQQT_CLUSTER] = "CLUSTER";
	hmQType2Name[MQQT_ALL]     = "ALL";

	for(HashMap::const_iterator it=hmQType2Name.begin();
		it != hmQType2Name.end(); it++){
		hmName2QType[it->second]=it->first;
	}
}
/*************************************************************************/
void Dictionary::initializeChlType2Name(){
	IAS_TRACER;


	hmChlType2Name[MQCHT_SENDER]   = "SENDER";
	hmChlType2Name[MQCHT_SERVER]   = "SERVER";
	hmChlType2Name[MQCHT_RECEIVER]   = "RECEIVER";
	hmChlType2Name[MQCHT_REQUESTER]   = "REQUESTER";
	hmChlType2Name[MQCHT_SVRCONN]   = "SVRCONN";
	hmChlType2Name[MQCHT_CLNTCONN]   = "CLNTCONN";
	hmChlType2Name[MQCHT_CLUSRCVR]   = "CLUSRCVR";
	hmChlType2Name[MQCHT_CLUSSDR]   = "CLUSSDR";
	hmChlType2Name[MQCHT_MQTT]   = "MQTT";
	hmChlType2Name[/*MQCHT_AMQP*/11]   = "AMQP";
	hmChlType2Name[MQCHT_ALL]   = "ALL";

	for(HashMap::const_iterator it=hmChlType2Name.begin();
		it != hmChlType2Name.end(); it++){
		hmName2ChlType[it->second]=it->first;
	}
}
/*************************************************************************/
void Dictionary::initializeChlStatus2Name(){
	IAS_TRACER;

	hmChlStatus2Name[MQCHS_INACTIVE]="INACTIVE";
	hmChlStatus2Name[MQCHS_BINDING]="BINDING";
	hmChlStatus2Name[MQCHS_STARTING]="STARTING";
	hmChlStatus2Name[MQCHS_RUNNING]="RUNNING";
	hmChlStatus2Name[MQCHS_STOPPING]="STOPPING";
	hmChlStatus2Name[MQCHS_RETRYING]="RETRYING";
	hmChlStatus2Name[MQCHS_STOPPED]="STOPPED";
	hmChlStatus2Name[MQCHS_REQUESTING]="REQUESTING";
	hmChlStatus2Name[MQCHS_PAUSED]="PAUSED";
	hmChlStatus2Name[MQCHS_DISCONNECTED]="DISCONNECTED";
	hmChlStatus2Name[MQCHS_INITIALIZING]="INITIALIZING";
	hmChlStatus2Name[MQCHS_SWITCHING]="SWITCHING";

	for(HashMap::const_iterator it=hmChlStatus2Name.begin();
		it != hmChlStatus2Name.end(); it++){
		hmName2ChlStatus[it->second]=it->first;
	}
}
/*************************************************************************/
void Dictionary::initializeEventOriginName(){
	IAS_TRACER;

	hmEventOriginName[MQEVO_CONSOLE]   = "CONSOLE";
	hmEventOriginName[MQEVO_INIT]      = "INIT";
	hmEventOriginName[MQEVO_MSG]       = "MSG";
	hmEventOriginName[MQEVO_INTERNAL]  = "INTERNAL";
	hmEventOriginName[MQEVO_OTHER]     = "OTHER";

}
/*************************************************************************/
void Dictionary::initializeCommandID2Name(){
	IAS_TRACER;

	hmCommandID2Name[MQCMD_CHANGE_Q_MGR]       = "ChangeQMgr";
	hmCommandID2Name[MQCMD_CLEAR_Q]            = "ClearQ";

	hmCommandID2Name[MQCMD_RESET_CHANNEL]      = "ResetChannel";
	hmCommandID2Name[MQCMD_RESOLVE_CHANNEL]    = "ResolveChannel";
	hmCommandID2Name[MQCMD_PING_CHANNEL]       = "PingChannel";
	hmCommandID2Name[MQCMD_START_CHANNEL]      = "StartChannel";
	hmCommandID2Name[MQCMD_STOP_CHANNEL]       = "StopChannel";

	hmCommandID2Name[MQCMD_INQUIRE_Q]              = "InquireQ";
	hmCommandID2Name[MQCMD_INQUIRE_CHANNEL]        = "InquireChannel";
	hmCommandID2Name[MQCMD_INQUIRE_CHANNEL_STATUS] = "InquireChannelStatus";

	hmCommandID2Name[MQCMD_INQUIRE_Q_MGR]          = "InquireQMgr";
	hmCommandID2Name[MQCMD_INQUIRE_Q_MGR_STATUS]   = "InquireQMgrStatus";

	hmCommandID2Name[MQCMD_ACCOUNTING_MQI]     = "AccountingMQI";
	hmCommandID2Name[MQCMD_ACCOUNTING_Q]       = "AccountingQueue";

	hmCommandID2Name[MQCMD_COMMAND_EVENT]      = "CommandEvent";

	hmCommandID2Name[MQCMD_STATISTICS_MQI]     = "StatisticsMQI";
	hmCommandID2Name[MQCMD_STATISTICS_Q]       = "StatisticsQueue";
	hmCommandID2Name[MQCMD_STATISTICS_CHANNEL] = "StatisticsChannel";


	for(HashMap::const_iterator it=hmCommandID2Name.begin();
		it != hmCommandID2Name.end(); it++){
		hmCommandName2ID[it->second]=it->first;
	}
}
/*************************************************************************/
void Dictionary::initializeParameterID2Name(){
	IAS_TRACER;

	hmParameterID2Name[MQIA_ACCOUNTING_CONN_OVERRIDE]="AccountingConnOverride";
	hmParameterID2Name[MQIA_ACCOUNTING_INTERVAL]="AccountingInterval";
	hmParameterID2Name[MQIA_ACCOUNTING_MQI]="AccountingMqi";
	hmParameterID2Name[MQIA_ACCOUNTING_Q]="AccountingQ";
	hmParameterID2Name[MQIA_ACTIVE_CHANNELS]="ActiveChannels";
	hmParameterID2Name[MQIA_ACTIVITY_RECORDING]="ActivityRecording";
	hmParameterID2Name[MQIA_ADOPTNEWMCA_CHECK]="AdoptnewmcaCheck";
	hmParameterID2Name[MQIA_ADOPTNEWMCA_TYPE]="AdoptnewmcaType";
	hmParameterID2Name[MQIA_ADOPTNEWMCA_INTERVAL]="AdoptnewmcaInterval";
	hmParameterID2Name[MQIA_APPL_TYPE]="ApplType";
	hmParameterID2Name[MQIA_ARCHIVE]="Archive";
	hmParameterID2Name[MQIA_AUTH_INFO_TYPE]="AuthInfoType";
	hmParameterID2Name[MQIA_AUTHORITY_EVENT]="AuthorityEvent";
	hmParameterID2Name[MQIA_AUTO_REORG_INTERVAL]="AutoReorgInterval";
	hmParameterID2Name[MQIA_AUTO_REORGANIZATION]="AutoReorganization";
	hmParameterID2Name[MQIA_BACKOUT_THRESHOLD]="BackoutThreshold";
	hmParameterID2Name[MQIA_BASE_TYPE]="BaseType";
	hmParameterID2Name[MQIA_BATCH_INTERFACE_AUTO]="BatchInterfaceAuto";
	hmParameterID2Name[MQIA_BRIDGE_EVENT]="BridgeEvent";
	hmParameterID2Name[MQIA_CERT_VAL_POLICY]="CertValPolicy";
	hmParameterID2Name[MQIA_CF_CFCONLOS]="CfCfconlos";
	hmParameterID2Name[MQIA_CF_LEVEL]="CfLevel";
	hmParameterID2Name[MQIA_CF_OFFLOAD]="CfOffload";
	hmParameterID2Name[MQIA_CF_OFFLOAD_THRESHOLD1]="CfOffloadThreshold1";
	hmParameterID2Name[MQIA_CF_OFFLOAD_THRESHOLD2]="CfOffloadThreshold2";
	hmParameterID2Name[MQIA_CF_OFFLOAD_THRESHOLD3]="CfOffloadThreshold3";
	hmParameterID2Name[MQIA_CF_OFFLDUSE]="CfOfflduse";
	hmParameterID2Name[MQIA_CF_RECOVER]="CfRecover";
	hmParameterID2Name[MQIA_CF_RECAUTO]="CfRecauto";
	hmParameterID2Name[MQIA_CF_SMDS_BUFFERS]="CfSmdsBuffers";
	hmParameterID2Name[MQIA_CHANNEL_AUTO_DEF]="ChannelAutoDef";
	hmParameterID2Name[MQIA_CHANNEL_AUTO_DEF_EVENT]="ChannelAutoDefEvent";
	hmParameterID2Name[MQIA_CHANNEL_EVENT]="ChannelEvent";
	hmParameterID2Name[MQIA_CHINIT_ADAPTERS]="ChinitAdapters";
	hmParameterID2Name[MQIA_CHINIT_CONTROL]="ChinitControl";
	hmParameterID2Name[MQIA_CHINIT_DISPATCHERS]="ChinitDispatchers";
	hmParameterID2Name[MQIA_CHINIT_TRACE_AUTO_START]="ChinitTraceAutoStart";
	hmParameterID2Name[MQIA_CHINIT_TRACE_TABLE_SIZE]="ChinitTraceTableSize";
	hmParameterID2Name[MQIA_CLUSTER_Q_TYPE]="ClusterQType";
	hmParameterID2Name[MQIA_CLUSTER_WORKLOAD_LENGTH]="ClusterWorkloadLength";
	hmParameterID2Name[MQIA_CLWL_MRU_CHANNELS]="ClwlMruChannels";
	hmParameterID2Name[MQIA_CLWL_Q_RANK]="ClwlQRank";
	hmParameterID2Name[MQIA_CLWL_Q_PRIORITY]="ClwlQPriority";
	hmParameterID2Name[MQIA_CLWL_USEQ]="ClwlUseq";
	hmParameterID2Name[MQIA_CMD_SERVER_AUTO]="CmdServerAuto";
	hmParameterID2Name[MQIA_CMD_SERVER_CONTROL]="CmdServerControl";
	hmParameterID2Name[MQIA_CMD_SERVER_CONVERT_MSG]="CmdServerConvertMsg";
	hmParameterID2Name[MQIA_CMD_SERVER_DLQ_MSG]="CmdServerDlqMsg";
	hmParameterID2Name[MQIA_CODED_CHAR_SET_ID]="CodedCharSetId";
	hmParameterID2Name[MQIA_COMMAND_EVENT]="CommandEvent";
	hmParameterID2Name[MQIA_COMMAND_LEVEL]="CommandLevel";
	hmParameterID2Name[MQIA_CONFIGURATION_EVENT]="ConfigurationEvent";
	hmParameterID2Name[MQIA_CPI_LEVEL]="CpiLevel";
	hmParameterID2Name[MQIA_CURRENT_Q_DEPTH]="CurrentQDepth";
	hmParameterID2Name[MQIA_DEF_BIND]="DefBind";
	hmParameterID2Name[MQIA_DEF_INPUT_OPEN_OPTION]="DefInputOpenOption";
	hmParameterID2Name[MQIA_DEF_PERSISTENCE]="DefPersistence";
	hmParameterID2Name[MQIA_DEF_PRIORITY]="DefPriority";
	hmParameterID2Name[MQIA_DEF_PUT_RESPONSE_TYPE]="DefPutResponseType";
	hmParameterID2Name[MQIA_DEF_READ_AHEAD]="DefReadAhead";
	hmParameterID2Name[MQIA_DEFINITION_TYPE]="DefinitionType";
	hmParameterID2Name[MQIA_DIST_LISTS]="DistLists";
	hmParameterID2Name[MQIA_DNS_WLM]="DnsWlm";
	hmParameterID2Name[MQIA_DURABLE_SUB]="DurableSub";
	hmParameterID2Name[MQIA_EXPIRY_INTERVAL]="ExpiryInterval";
	hmParameterID2Name[MQIA_FIRST]="First";
	hmParameterID2Name[MQIA_GROUP_UR]="GroupUr";
	hmParameterID2Name[MQIA_HARDEN_GET_BACKOUT]="HardenGetBackout";
	hmParameterID2Name[MQIA_HIGH_Q_DEPTH]="HighQDepth";
	hmParameterID2Name[MQIA_IGQ_PUT_AUTHORITY]="IgqPutAuthority";
	hmParameterID2Name[MQIA_INDEX_TYPE]="IndexType";
	hmParameterID2Name[MQIA_INHIBIT_EVENT]="InhibitEvent";
	hmParameterID2Name[MQIA_INHIBIT_GET]="InhibitGet";
	hmParameterID2Name[MQIA_INHIBIT_PUB]="InhibitPub";
	hmParameterID2Name[MQIA_INHIBIT_PUT]="InhibitPut";
	hmParameterID2Name[MQIA_INHIBIT_SUB]="InhibitSub";
	hmParameterID2Name[MQIA_INTRA_GROUP_QUEUING]="IntraGroupQueuing";
	hmParameterID2Name[MQIA_IP_ADDRESS_VERSION]="IpAddressVersion";
	hmParameterID2Name[MQIA_LISTENER_PORT_NUMBER]="ListenerPortNumber";
	hmParameterID2Name[MQIA_LISTENER_TIMER]="ListenerTimer";
	hmParameterID2Name[MQIA_LOGGER_EVENT]="LoggerEvent";
	hmParameterID2Name[MQIA_LU62_CHANNELS]="Lu62Channels";
	hmParameterID2Name[MQIA_LOCAL_EVENT]="LocalEvent";
	hmParameterID2Name[MQIA_MSG_MARK_BROWSE_INTERVAL]="MsgMarkBrowseInterval";
	hmParameterID2Name[MQIA_MASTER_ADMIN]="MasterAdmin";
	hmParameterID2Name[MQIA_MAX_CHANNELS]="MaxChannels";
	hmParameterID2Name[MQIA_MAX_CLIENTS]="MaxClients";
	hmParameterID2Name[MQIA_MAX_GLOBAL_LOCKS]="MaxGlobalLocks";
	hmParameterID2Name[MQIA_MAX_HANDLES]="MaxHandles";
	hmParameterID2Name[MQIA_MAX_LOCAL_LOCKS]="MaxLocalLocks";
	hmParameterID2Name[MQIA_MAX_MSG_LENGTH]="MaxMsgLength";
	hmParameterID2Name[MQIA_MAX_OPEN_Q]="MaxOpenQ";
	hmParameterID2Name[MQIA_MAX_PRIORITY]="MaxPriority";
	hmParameterID2Name[MQIA_MAX_PROPERTIES_LENGTH]="MaxPropertiesLength";
	hmParameterID2Name[MQIA_MAX_Q_DEPTH]="MaxQDepth";
	hmParameterID2Name[MQIA_MAX_Q_TRIGGERS]="MaxQTriggers";
	hmParameterID2Name[MQIA_MAX_RECOVERY_TASKS]="MaxRecoveryTasks";
	hmParameterID2Name[MQIA_MAX_RESPONSES]="MaxResponses";
	hmParameterID2Name[MQIA_MAX_UNCOMMITTED_MSGS]="MaxUncommittedMsgs";
	hmParameterID2Name[MQIA_MONITOR_INTERVAL]="MonitorInterval";
	hmParameterID2Name[MQIA_MONITORING_AUTO_CLUSSDR]="MonitoringAutoClussdr";
	hmParameterID2Name[MQIA_MONITORING_CHANNEL]="MonitoringChannel";
	hmParameterID2Name[MQIA_MONITORING_Q]="MonitoringQ";
	hmParameterID2Name[MQIA_MSG_DELIVERY_SEQUENCE]="MsgDeliverySequence";
	hmParameterID2Name[MQIA_MSG_DEQ_COUNT]="MsgDeqCount";
	hmParameterID2Name[MQIA_MSG_ENQ_COUNT]="MsgEnqCount";
	hmParameterID2Name[MQIA_NAME_COUNT]="NameCount";
	hmParameterID2Name[MQIA_NAMELIST_TYPE]="NamelistType";
	hmParameterID2Name[MQIA_NPM_CLASS]="NpmClass";
	hmParameterID2Name[MQIA_NPM_DELIVERY]="NpmDelivery";
	hmParameterID2Name[MQIA_OPEN_INPUT_COUNT]="OpenInputCount";
	hmParameterID2Name[MQIA_OPEN_OUTPUT_COUNT]="OpenOutputCount";
	hmParameterID2Name[MQIA_OUTBOUND_PORT_MAX]="OutboundPortMax";
	hmParameterID2Name[MQIA_OUTBOUND_PORT_MIN]="OutboundPortMin";
	hmParameterID2Name[MQIA_PAGESET_ID]="PagesetId";
	hmParameterID2Name[MQIA_PERFORMANCE_EVENT]="PerformanceEvent";
	hmParameterID2Name[MQIA_PLATFORM]="Platform";
	hmParameterID2Name[MQIA_PM_DELIVERY]="PmDelivery";
	hmParameterID2Name[MQIA_PROPERTY_CONTROL]="PropertyControl";
	hmParameterID2Name[MQIA_PROXY_SUB]="ProxySub";
	hmParameterID2Name[MQIA_PUB_COUNT]="PubCount";
	hmParameterID2Name[MQIA_PUB_SCOPE]="PubScope";
	hmParameterID2Name[MQIA_PUBSUB_CLUSTER]="PubsubCluster";
	hmParameterID2Name[MQIA_PUBSUB_MAXMSG_RETRY_COUNT]="PubsubMaxmsgRetryCount";
	hmParameterID2Name[MQIA_PUBSUB_MODE]="PubsubMode";
	hmParameterID2Name[MQIA_PUBSUB_NP_MSG]="PubsubNpMsg";
	hmParameterID2Name[MQIA_PUBSUB_NP_RESP]="PubsubNpResp";
	hmParameterID2Name[MQIA_PUBSUB_SYNC_PT]="PubsubSyncPt";
	hmParameterID2Name[MQIA_Q_DEPTH_HIGH_EVENT]="QDepthHighEvent";
	hmParameterID2Name[MQIA_Q_DEPTH_HIGH_LIMIT]="QDepthHighLimit";
	hmParameterID2Name[MQIA_Q_DEPTH_LOW_EVENT]="QDepthLowEvent";
	hmParameterID2Name[MQIA_Q_DEPTH_LOW_LIMIT]="QDepthLowLimit";
	hmParameterID2Name[MQIA_Q_DEPTH_MAX_EVENT]="QDepthMaxEvent";
	hmParameterID2Name[MQIA_Q_SERVICE_INTERVAL]="QServiceInterval";
	hmParameterID2Name[MQIA_Q_SERVICE_INTERVAL_EVENT]="QServiceIntervalEvent";
	hmParameterID2Name[MQIA_Q_TYPE]="QType";
	hmParameterID2Name[MQIA_Q_USERS]="QUsers";
	hmParameterID2Name[MQIA_QMGR_CFCONLOS]="QmgrCfconlos";
	hmParameterID2Name[MQIA_QMOPT_CONS_COMMS_MSGS]="QmoptConsCommsMsgs";
	hmParameterID2Name[MQIA_QMOPT_CONS_CRITICAL_MSGS]="QmoptConsCriticalMsgs";
	hmParameterID2Name[MQIA_QMOPT_CONS_ERROR_MSGS]="QmoptConsErrorMsgs";
	hmParameterID2Name[MQIA_QMOPT_CONS_INFO_MSGS]="QmoptConsInfoMsgs";
	hmParameterID2Name[MQIA_QMOPT_CONS_REORG_MSGS]="QmoptConsReorgMsgs";
	hmParameterID2Name[MQIA_QMOPT_CONS_SYSTEM_MSGS]="QmoptConsSystemMsgs";
	hmParameterID2Name[MQIA_QMOPT_CONS_WARNING_MSGS]="QmoptConsWarningMsgs";
	hmParameterID2Name[MQIA_QMOPT_CSMT_ON_ERROR]="QmoptCsmtOnError";
	hmParameterID2Name[MQIA_QMOPT_INTERNAL_DUMP]="QmoptInternalDump";
	hmParameterID2Name[MQIA_QMOPT_LOG_COMMS_MSGS]="QmoptLogCommsMsgs";
	hmParameterID2Name[MQIA_QMOPT_LOG_CRITICAL_MSGS]="QmoptLogCriticalMsgs";
	hmParameterID2Name[MQIA_QMOPT_LOG_ERROR_MSGS]="QmoptLogErrorMsgs";
	hmParameterID2Name[MQIA_QMOPT_LOG_INFO_MSGS]="QmoptLogInfoMsgs";
	hmParameterID2Name[MQIA_QMOPT_LOG_REORG_MSGS]="QmoptLogReorgMsgs";
	hmParameterID2Name[MQIA_QMOPT_LOG_SYSTEM_MSGS]="QmoptLogSystemMsgs";
	hmParameterID2Name[MQIA_QMOPT_LOG_WARNING_MSGS]="QmoptLogWarningMsgs";
	hmParameterID2Name[MQIA_QMOPT_TRACE_COMMS]="QmoptTraceComms";
	hmParameterID2Name[MQIA_QMOPT_TRACE_CONVERSION]="QmoptTraceConversion";
	hmParameterID2Name[MQIA_QMOPT_TRACE_REORG]="QmoptTraceReorg";
	hmParameterID2Name[MQIA_QMOPT_TRACE_MQI_CALLS]="QmoptTraceMqiCalls";
	hmParameterID2Name[MQIA_QMOPT_TRACE_SYSTEM]="QmoptTraceSystem";
	hmParameterID2Name[MQIA_QSG_DISP]="QsgDisp";
	hmParameterID2Name[MQIA_READ_AHEAD]="ReadAhead";
	hmParameterID2Name[MQIA_RECEIVE_TIMEOUT]="ReceiveTimeout";
	hmParameterID2Name[MQIA_RECEIVE_TIMEOUT_MIN]="ReceiveTimeoutMin";
	hmParameterID2Name[MQIA_RECEIVE_TIMEOUT_TYPE]="ReceiveTimeoutType";
	hmParameterID2Name[MQIA_REMOTE_EVENT]="RemoteEvent";
	hmParameterID2Name[MQIA_RETENTION_INTERVAL]="RetentionInterval";
	hmParameterID2Name[MQIA_RESPONSE_RESTART_POINT]="ResponseRestartPoint";
	hmParameterID2Name[MQIA_SCOPE]="Scope";
	hmParameterID2Name[MQIA_SECURITY_CASE]="SecurityCase";
	hmParameterID2Name[MQIA_SERVICE_CONTROL]="ServiceControl";
	hmParameterID2Name[MQIA_SERVICE_TYPE]="ServiceType";
	hmParameterID2Name[MQIA_SHAREABILITY]="Shareability";
	hmParameterID2Name[MQIA_SHARED_Q_Q_MGR_NAME]="SharedQQMgrNameName";
	hmParameterID2Name[MQIA_SSL_EVENT]="SslEvent";
	hmParameterID2Name[MQIA_SSL_FIPS_REQUIRED]="SslFipsRequired";
	hmParameterID2Name[MQIA_SSL_RESET_COUNT]="SslResetCount";
	hmParameterID2Name[MQIA_SSL_TASKS]="SslTasks";
	hmParameterID2Name[MQIA_START_STOP_EVENT]="StartStopEvent";
	hmParameterID2Name[MQIA_STATISTICS_CHANNEL]="StatisticsChannel";
	hmParameterID2Name[MQIA_STATISTICS_AUTO_CLUSSDR]="StatisticsAutoClussdr";
	hmParameterID2Name[MQIA_STATISTICS_INTERVAL]="StatisticsInterval";
	hmParameterID2Name[MQIA_STATISTICS_MQI]="StatisticsMqi";
	hmParameterID2Name[MQIA_STATISTICS_Q]="StatisticsQ";
	hmParameterID2Name[MQIA_SUB_COUNT]="SubCount";
	hmParameterID2Name[MQIA_SUB_SCOPE]="SubScope";
	hmParameterID2Name[MQIA_SYNCPOINT]="Syncpoint";
	hmParameterID2Name[MQIA_TCP_CHANNELS]="TcpChannels";
	hmParameterID2Name[MQIA_TCP_KEEP_ALIVE]="TcpKeepAlive";
	hmParameterID2Name[MQIA_TCP_STACK_TYPE]="TcpStackType";
	hmParameterID2Name[MQIA_TIME_SINCE_RESET]="TimeSinceReset";
	hmParameterID2Name[MQIA_TOPIC_DEF_PERSISTENCE]="TopicDefPersistence";
	hmParameterID2Name[MQIA_TOPIC_TYPE]="TopicType";
	hmParameterID2Name[MQIA_TRACE_ROUTE_RECORDING]="TraceRouteRecording";
	hmParameterID2Name[MQIA_TREE_LIFE_TIME]="TreeLifeTime";
	hmParameterID2Name[MQIA_TRIGGER_CONTROL]="TriggerControl";
	hmParameterID2Name[MQIA_TRIGGER_DEPTH]="TriggerDepth";
	hmParameterID2Name[MQIA_TRIGGER_INTERVAL]="TriggerInterval";
	hmParameterID2Name[MQIA_TRIGGER_MSG_PRIORITY]="TriggerMsgPriority";
	hmParameterID2Name[MQIA_TRIGGER_TYPE]="TriggerType";
	hmParameterID2Name[MQIA_TRIGGER_RESTART]="TriggerRestart";
	hmParameterID2Name[MQIA_UR_DISP]="UrDisp";
	hmParameterID2Name[MQIA_USAGE]="Usage";
	hmParameterID2Name[MQIA_USER_LIST]="UserList";
	hmParameterID2Name[MQIA_MULTICAST]="Multicast";
	hmParameterID2Name[MQIA_WILDCARD_OPERATION]="WildcardOperation";
	hmParameterID2Name[MQIA_COMM_INFO_TYPE]="CommInfoType";
	hmParameterID2Name[MQIA_COMM_EVENT]="CommEvent";
	hmParameterID2Name[MQIA_MCAST_BRIDGE]="MCAstBridge";
	hmParameterID2Name[MQIA_USE_DEAD_LETTER_Q]="UseDeadLetterQ";
	hmParameterID2Name[MQIA_TOLERATE_UNPROTECTED]="TolerateUnprotected";
	hmParameterID2Name[MQIA_SIGNATURE_ALGORITHM]="SignatureAlgorithm";
	hmParameterID2Name[MQIA_ENCRYPTION_ALGORITHM]="EncryptionAlgorithm";
	hmParameterID2Name[MQIA_POLICY_VERSION]="PolicyVersion";
	hmParameterID2Name[MQIA_ACTIVITY_CONN_OVERRIDE]="ActivityConnOverride";
	hmParameterID2Name[MQIA_ACTIVITY_TRACE]="ActivityTrace";
	hmParameterID2Name[MQIA_SUB_CONFIGURATION_EVENT]="SubConfigurationEvent";
	hmParameterID2Name[MQIA_XR_CAPABILITY]="XrCapability";
	hmParameterID2Name[MQIA_SUITE_B_STRENGTH]="SuiteBStrength";
	hmParameterID2Name[MQIA_CHLAUTH_RECORDS]="ChlauthRecords";
	hmParameterID2Name[MQIA_DEF_CLUSTER_XMIT_Q_TYPE]="DefClusterXmitQTypeType";
	hmParameterID2Name[MQIA_PROT_POLICY_CAPABILITY]="ProtPolicyCapability";
	hmParameterID2Name[MQIA_LAST_USED]="LastUsed";
	hmParameterID2Name[MQIAV_NOT_APPLICABLE]="NotApplicable";
	hmParameterID2Name[MQIAV_UNDEFINED]="Undefined";



	hmParameterID2Name[MQCADSD_SEND]="Send";
	hmParameterID2Name[MQCADSD_RECV]="Recv";
	hmParameterID2Name[MQCADSD_MSGFORMAT]="Msgformat";
	hmParameterID2Name[MQCAP_NOT_SUPPORTED]="NotSupported";
	hmParameterID2Name[MQCAP_SUPPORTED]="Supported";
	hmParameterID2Name[MQCAP_EXPIRED]="Expired";
	hmParameterID2Name[MQCA_ADMIN_TOPIC_NAME]="AdminTopicName";
	hmParameterID2Name[MQCA_ALTERATION_DATE]="AlterationDate";
	hmParameterID2Name[MQCA_ALTERATION_TIME]="AlterationTime";
	hmParameterID2Name[MQCA_APPL_ID]="ApplId";
	hmParameterID2Name[MQCA_AUTH_INFO_CONN_NAME]="AuthInfoConnName";
	hmParameterID2Name[MQCA_AUTH_INFO_DESC]="AuthInfoDesc";
	hmParameterID2Name[MQCA_AUTH_INFO_NAME]="AuthInfoName";
	hmParameterID2Name[MQCA_AUTH_INFO_OCSP_URL]="AuthInfoOcspUrl";
	hmParameterID2Name[MQCA_AUTO_REORG_CATALOG]="AutoReorgCatalog";
	hmParameterID2Name[MQCA_AUTO_REORG_START_TIME]="AutoReorgStartTime";
	hmParameterID2Name[MQCA_BACKOUT_REQ_Q_NAME]="BackoutReqQName";
	hmParameterID2Name[MQCA_BASE_OBJECT_NAME]="BaseObjectName";
	hmParameterID2Name[MQCA_BASE_Q_NAME]="BaseQName";
	hmParameterID2Name[MQCA_BATCH_INTERFACE_ID]="BatchInterfaceId";
	hmParameterID2Name[MQCA_CF_STRUC_DESC]="CfStrucDesc";
	hmParameterID2Name[MQCA_CF_STRUC_NAME]="CfStrucName";
	hmParameterID2Name[MQCA_CHANNEL_AUTO_DEF_EXIT]="ChannelAutoDefExit";
	hmParameterID2Name[MQCA_CHILD]="Child";
	hmParameterID2Name[MQCA_CHINIT_SERVICE_PARM]="ChinitServiceParm";
	hmParameterID2Name[MQCA_CICS_FILE_NAME]="CicsFileName";
	hmParameterID2Name[MQCA_CLUSTER_DATE]="ClusterDate";
	hmParameterID2Name[MQCA_CLUSTER_NAME]="ClusterName";
	hmParameterID2Name[MQCA_CLUSTER_NAMELIST]="ClusterNamelist";
	hmParameterID2Name[MQCA_CLUSTER_Q_MGR_NAME]="ClusterQMgrName";
	hmParameterID2Name[MQCA_CLUSTER_TIME]="ClusterTime";
	hmParameterID2Name[MQCA_CLUSTER_WORKLOAD_DATA]="ClusterWorkloadData";
	hmParameterID2Name[MQCA_CLUSTER_WORKLOAD_EXIT]="ClusterWorkloadExit";
	hmParameterID2Name[MQCA_COMMAND_INPUT_Q_NAME]="CommandInputQName";
	hmParameterID2Name[MQCA_COMMAND_REPLY_Q_NAME]="CommandReplyQName";
	hmParameterID2Name[MQCA_CREATION_DATE]="CreationDate";
	hmParameterID2Name[MQCA_CREATION_TIME]="CreationTime";
	hmParameterID2Name[MQCA_DEAD_LETTER_Q_NAME]="DeadLetterQName";
	hmParameterID2Name[MQCA_DEF_XMIT_Q_NAME]="DefXmitQName";
	hmParameterID2Name[MQCA_DNS_GROUP]="DnsGroup";
	hmParameterID2Name[MQCA_ENV_DATA]="EnvData";
	hmParameterID2Name[MQCA_IGQ_USER_ID]="IgqUserId";
	hmParameterID2Name[MQCA_INITIATION_Q_NAME]="InitiationQName";
	hmParameterID2Name[MQCA_LAST]="Last";
	hmParameterID2Name[MQCA_LDAP_PASSWORD]="LdapPassword";
	hmParameterID2Name[MQCA_LDAP_USER_NAME]="LdapUserName";
	hmParameterID2Name[MQCA_LU_GROUP_NAME]="LuGroupName";
	hmParameterID2Name[MQCA_LU_NAME]="LuName";
	hmParameterID2Name[MQCA_LU62_ARM_SUFFIX]="Lu62ArmSuffix";
	hmParameterID2Name[MQCA_MODEL_DURABLE_Q]="ModelDurableQ";
	hmParameterID2Name[MQCA_MODEL_NON_DURABLE_Q]="ModelNonDurableQ";
	hmParameterID2Name[MQCA_MONITOR_Q_NAME]="MonitorQName";
	hmParameterID2Name[MQCA_NAMELIST_DESC]="NamelistDesc";
	hmParameterID2Name[MQCA_NAMELIST_NAME]="NamelistName";
	hmParameterID2Name[MQCA_NAMES]="Names";
	hmParameterID2Name[MQCA_PARENT]="Parent";
	hmParameterID2Name[MQCA_PASS_TICKET_APPL]="PassTicketAppl";
	hmParameterID2Name[MQCA_PROCESS_DESC]="ProcessDesc";
	hmParameterID2Name[MQCA_PROCESS_NAME]="ProcessName";
	hmParameterID2Name[MQCA_Q_DESC]="QDesc";
	hmParameterID2Name[MQCA_Q_MGR_DESC]="QMgrDesc";
	hmParameterID2Name[MQCA_Q_MGR_IDENTIFIER]="QMgrIdentifier";
	hmParameterID2Name[MQCA_Q_MGR_NAME]="QMgrName";
	hmParameterID2Name[MQCA_Q_NAME]="QName";
	hmParameterID2Name[MQCA_QSG_NAME]="QsgName";
	hmParameterID2Name[MQCA_REMOTE_Q_MGR_NAME]="RemoteQMgrName";
	hmParameterID2Name[MQCA_REMOTE_Q_NAME]="RemoteQName";
	hmParameterID2Name[MQCA_REPOSITORY_NAME]="RepositoryName";
	hmParameterID2Name[MQCA_REPOSITORY_NAMELIST]="RepositoryNamelist";
	hmParameterID2Name[MQCA_RESUME_DATE]="ResumeDate";
	hmParameterID2Name[MQCA_RESUME_TIME]="ResumeTime";
	hmParameterID2Name[MQCA_SERVICE_DESC]="ServiceDesc";
	hmParameterID2Name[MQCA_SERVICE_NAME]="ServiceName";
	hmParameterID2Name[MQCA_SERVICE_START_ARGS]="ServiceStartArgs";
	hmParameterID2Name[MQCA_SERVICE_START_COMMAND]="ServiceStartCommand";
	hmParameterID2Name[MQCA_SERVICE_STOP_ARGS]="ServiceStopArgs";
	hmParameterID2Name[MQCA_SERVICE_STOP_COMMAND]="ServiceStopCommand";
	hmParameterID2Name[MQCA_STDERR_DESTINATION]="StderrDestination";
	hmParameterID2Name[MQCA_STDOUT_DESTINATION]="StdoutDestination";
	hmParameterID2Name[MQCA_SSL_CRL_NAMELIST]="SslCrlNamelist";
	hmParameterID2Name[MQCA_SSL_CRYPTO_HARDWARE]="SslCryptoHardware";
	hmParameterID2Name[MQCA_SSL_KEY_LIBRARY]="SslKeyLibrary";
	hmParameterID2Name[MQCA_SSL_KEY_MEMBER]="SslKeyMember";
	hmParameterID2Name[MQCA_SSL_KEY_REPOSITORY]="SslKeyRepository";
	hmParameterID2Name[MQCA_STORAGE_CLASS]="StorageClass";
	hmParameterID2Name[MQCA_STORAGE_CLASS_DESC]="StorageClassDesc";
	hmParameterID2Name[MQCA_SYSTEM_LOG_Q_NAME]="SystemLogQName";
	hmParameterID2Name[MQCA_TCP_NAME]="TcpName";
	hmParameterID2Name[MQCA_TOPIC_DESC]="TopicDesc";
	hmParameterID2Name[MQCA_TOPIC_NAME]="TopicName";
	hmParameterID2Name[MQCA_TOPIC_STRING]="TopicString";
	hmParameterID2Name[MQCA_TOPIC_STRING_FILTER]="TopicStringFilter";
	hmParameterID2Name[MQCA_TPIPE_NAME]="TpipeName";
	hmParameterID2Name[MQCA_TRIGGER_CHANNEL_NAME]="TriggerChannelName";
	hmParameterID2Name[MQCA_TRIGGER_DATA]="TriggerData";
	hmParameterID2Name[MQCA_TRIGGER_PROGRAM_NAME]="TriggerProgramName";
	hmParameterID2Name[MQCA_TRIGGER_TERM_ID]="TriggerTermId";
	hmParameterID2Name[MQCA_TRIGGER_TRANS_ID]="TriggerTransId";
	hmParameterID2Name[MQCA_USER_DATA]="UserData";
	hmParameterID2Name[MQCA_USER_LIST]="UserList";
	hmParameterID2Name[MQCA_VERSION]="Version";
	hmParameterID2Name[MQCA_XCF_GROUP_NAME]="XcfGroupName";
	hmParameterID2Name[MQCA_XCF_MEMBER_NAME]="XcfMemberName";
	hmParameterID2Name[MQCA_XMIT_Q_NAME]="XmitQName";
	hmParameterID2Name[MQCA_COMM_INFO_NAME]="CommInfoName";
	hmParameterID2Name[MQCA_COMM_INFO_DESC]="CommInfoDesc";
	hmParameterID2Name[MQCA_POLICY_NAME]="PolicyName";
	hmParameterID2Name[MQCA_SIGNER_DN]="SignerDn";
	hmParameterID2Name[MQCA_RECIPIENT_DN]="RecipientDn";
	hmParameterID2Name[MQCA_INSTALLATION_DESC]="InstallationDesc";
	hmParameterID2Name[MQCA_INSTALLATION_NAME]="InstallationName";
	hmParameterID2Name[MQCA_INSTALLATION_PATH]="InstallationPath";
	hmParameterID2Name[MQCA_CHLAUTH_DESC]="ChlauthDesc";
	hmParameterID2Name[MQCA_CUSTOM]="Custom";
	hmParameterID2Name[MQCA_XR_VERSION]="XrVersion";
	hmParameterID2Name[MQCA_XR_SSL_CIPHER_SUITES]="XrSslCipherSuites";
	hmParameterID2Name[MQCA_CLUS_CHL_NAME]="ClusChlName";
	hmParameterID2Name[MQCA_LAST_USED]="LastUsed";

	hmParameterID2Name[MQIACH_XMIT_PROTOCOL_TYPE]="XmitProtocolType";
	hmParameterID2Name[MQIACH_BATCH_SIZE]="BatchSize";
	hmParameterID2Name[MQIACH_DISC_INTERVAL]="DiscInterval";
	hmParameterID2Name[MQIACH_SHORT_TIMER]="ShortTimer";
	hmParameterID2Name[MQIACH_SHORT_RETRY]="ShortRetry";
	hmParameterID2Name[MQIACH_LONG_TIMER]="LongTimer";
	hmParameterID2Name[MQIACH_LONG_RETRY]="LongRetry";
	hmParameterID2Name[MQIACH_PUT_AUTHORITY]="PutAuthority";
	hmParameterID2Name[MQIACH_SEQUENCE_NUMBER_WRAP]="SequenceNumberWrap";
	hmParameterID2Name[MQIACH_MAX_MSG_LENGTH]="MaxMsgLength";
	hmParameterID2Name[MQIACH_CHANNEL_TYPE]="ChannelType";
	hmParameterID2Name[MQIACH_DATA_COUNT]="DataCount";
	hmParameterID2Name[MQIACH_NAME_COUNT]="NameCount";
	hmParameterID2Name[MQIACH_MSG_SEQUENCE_NUMBER]="MsgSequenceNumber";
	hmParameterID2Name[MQIACH_DATA_CONVERSION]="DataConversion";
	hmParameterID2Name[MQIACH_IN_DOUBT]="InDoubt";
	hmParameterID2Name[MQIACH_MCA_TYPE]="MCAType";
	hmParameterID2Name[MQIACH_SESSION_COUNT]="SessionCount";
	hmParameterID2Name[MQIACH_ADAPTER]="Adapter";
	hmParameterID2Name[MQIACH_COMMAND_COUNT]="CommandCount";
	hmParameterID2Name[MQIACH_SOCKET]="Socket";
	hmParameterID2Name[MQIACH_PORT]="Port";
	hmParameterID2Name[MQIACH_CHANNEL_INSTANCE_TYPE]="ChannelInstanceType";
	hmParameterID2Name[MQIACH_CHANNEL_INSTANCE_ATTRS]="ChannelInstanceAttrs";
	hmParameterID2Name[MQIACH_CHANNEL_ERROR_DATA]="ChannelErrorData";
	hmParameterID2Name[MQIACH_CHANNEL_TABLE]="ChannelTable";
	hmParameterID2Name[MQIACH_CHANNEL_STATUS]="ChannelStatus";
	hmParameterID2Name[MQIACH_INDOUBT_STATUS]="IndoubtStatus";
	hmParameterID2Name[MQIACH_LAST_SEQ_NUMBER]="LastSeqNumber";
	hmParameterID2Name[MQIACH_LAST_SEQUENCE_NUMBER]="LastSequenceNumber";
	hmParameterID2Name[MQIACH_CURRENT_MSGS]="CurrentMsgs";
	hmParameterID2Name[MQIACH_CURRENT_SEQ_NUMBER]="CurrentSeqNumber";
	hmParameterID2Name[MQIACH_CURRENT_SEQUENCE_NUMBER]="CurrentSequenceNumber";
	hmParameterID2Name[MQIACH_SSL_RETURN_CODE]="SslReturnCode";
	hmParameterID2Name[MQIACH_MSGS]="Msgs";
	hmParameterID2Name[MQIACH_BYTES_SENT]="BytesSent";
	hmParameterID2Name[MQIACH_BYTES_RCVD]="BytesRcvd";
	hmParameterID2Name[MQIACH_BYTES_RECEIVED]="BytesReceived";
	hmParameterID2Name[MQIACH_BATCHES]="Batches";
	hmParameterID2Name[MQIACH_BUFFERS_SENT]="BuffersSent";
	hmParameterID2Name[MQIACH_BUFFERS_RCVD]="BuffersRcvd";
	hmParameterID2Name[MQIACH_BUFFERS_RECEIVED]="BuffersReceived";
	hmParameterID2Name[MQIACH_LONG_RETRIES_LEFT]="LongRetriesLeft";
	hmParameterID2Name[MQIACH_SHORT_RETRIES_LEFT]="ShortRetriesLeft";
	hmParameterID2Name[MQIACH_MCA_STATUS]="MCAStatus";
	hmParameterID2Name[MQIACH_STOP_REQUESTED]="StopRequested";
	hmParameterID2Name[MQIACH_MR_COUNT]="MrCount";
	hmParameterID2Name[MQIACH_MR_INTERVAL]="MrInterval";
	hmParameterID2Name[MQIACH_NPM_SPEED]="NpmSpeed";
	hmParameterID2Name[MQIACH_HB_INTERVAL]="HbInterval";
	hmParameterID2Name[MQIACH_BATCH_INTERVAL]="BatchInterval";
	hmParameterID2Name[MQIACH_NETWORK_PRIORITY]="NetworkPriority";
	hmParameterID2Name[MQIACH_KEEP_ALIVE_INTERVAL]="KeepAliveInterval";
	hmParameterID2Name[MQIACH_BATCH_HB]="BatchHb";
	hmParameterID2Name[MQIACH_SSL_CLIENT_AUTH]="SslClientAuth";
	hmParameterID2Name[MQIACH_ALLOC_RETRY]="AllocRetry";
	hmParameterID2Name[MQIACH_ALLOC_FAST_TIMER]="AllocFastTimer";
	hmParameterID2Name[MQIACH_ALLOC_SLOW_TIMER]="AllocSlowTimer";
	hmParameterID2Name[MQIACH_DISC_RETRY]="DiscRetry";
	hmParameterID2Name[MQIACH_PORT_NUMBER]="PortNumber";
	hmParameterID2Name[MQIACH_HDR_COMPRESSION]="HdrCompression";
	hmParameterID2Name[MQIACH_MSG_COMPRESSION]="MsgCompression";
	hmParameterID2Name[MQIACH_CLWL_CHANNEL_RANK]="ClwlChannelRank";
	hmParameterID2Name[MQIACH_CLWL_CHANNEL_PRIORITY]="ClwlChannelPriority";
	hmParameterID2Name[MQIACH_CLWL_CHANNEL_WEIGHT]="ClwlChannelWeight";
	hmParameterID2Name[MQIACH_CHANNEL_DISP]="ChannelDisp";
	hmParameterID2Name[MQIACH_INBOUND_DISP]="InboundDisp";
	hmParameterID2Name[MQIACH_CHANNEL_TYPES]="ChannelTypes";
	hmParameterID2Name[MQIACH_ADAPS_STARTED]="AdapsStarted";
	hmParameterID2Name[MQIACH_ADAPS_MAX]="AdapsMax";
	hmParameterID2Name[MQIACH_DISPS_STARTED]="DispsStarted";
	hmParameterID2Name[MQIACH_DISPS_MAX]="DispsMax";
	hmParameterID2Name[MQIACH_SSLTASKS_STARTED]="SsltasksStarted";
	hmParameterID2Name[MQIACH_SSLTASKS_MAX]="SsltasksMax";
	hmParameterID2Name[MQIACH_CURRENT_CHL]="CurrentChl";
	hmParameterID2Name[MQIACH_CURRENT_CHL_MAX]="CurrentChlMax";
	hmParameterID2Name[MQIACH_CURRENT_CHL_TCP]="CurrentChlTcp";
	hmParameterID2Name[MQIACH_CURRENT_CHL_LU62]="CurrentChlLu62";
	hmParameterID2Name[MQIACH_ACTIVE_CHL]="ActiveChl";
	hmParameterID2Name[MQIACH_ACTIVE_CHL_MAX]="ActiveChlMax";
	hmParameterID2Name[MQIACH_ACTIVE_CHL_PAUSED]="ActiveChlPaused";
	hmParameterID2Name[MQIACH_ACTIVE_CHL_STARTED]="ActiveChlStarted";
	hmParameterID2Name[MQIACH_ACTIVE_CHL_STOPPED]="ActiveChlStopped";
	hmParameterID2Name[MQIACH_ACTIVE_CHL_RETRY]="ActiveChlRetry";
	hmParameterID2Name[MQIACH_LISTENER_STATUS]="ListenerStatus";
	hmParameterID2Name[MQIACH_SHARED_CHL_RESTART]="SharedChlRestart";
	hmParameterID2Name[MQIACH_LISTENER_CONTROL]="ListenerControl";
	hmParameterID2Name[MQIACH_BACKLOG]="Backlog";
	hmParameterID2Name[MQIACH_XMITQ_TIME_INDICATOR]="XmitqTimeIndicator";
	hmParameterID2Name[MQIACH_NETWORK_TIME_INDICATOR]="NetworkTimeIndicator";
	hmParameterID2Name[MQIACH_EXIT_TIME_INDICATOR]="ExitTimeIndicator";
	hmParameterID2Name[MQIACH_BATCH_SIZE_INDICATOR]="BatchSizeIndicator";
	hmParameterID2Name[MQIACH_XMITQ_MSGS_AVAILABLE]="XmitqMsgsAvailable";
	hmParameterID2Name[MQIACH_CHANNEL_SUBSTATE]="ChannelSubstate";
	hmParameterID2Name[MQIACH_SSL_KEY_RESETS]="SslKeyResets";
	hmParameterID2Name[MQIACH_COMPRESSION_RATE]="CompressionRate";
	hmParameterID2Name[MQIACH_COMPRESSION_TIME]="CompressionTime";
	hmParameterID2Name[MQIACH_MAX_XMIT_SIZE]="MaxXmitSize";
	hmParameterID2Name[MQIACH_DEF_CHANNEL_DISP]="DefChannelDisp";
	hmParameterID2Name[MQIACH_SHARING_CONVERSATIONS]="SharingConversations";
	hmParameterID2Name[MQIACH_MAX_SHARING_CONVS]="MaxSharingConvs";
	hmParameterID2Name[MQIACH_CURRENT_SHARING_CONVS]="CurrentSharingConvs";
	hmParameterID2Name[MQIACH_MAX_INSTANCES]="MaxInstances";
	hmParameterID2Name[MQIACH_MAX_INSTS_PER_CLIENT]="MaxInstsPerClient";
	hmParameterID2Name[MQIACH_CLIENT_CHANNEL_WEIGHT]="ClientChannelWeight";
	hmParameterID2Name[MQIACH_CONNECTION_AFFINITY]="ConnectionAffinity";
	hmParameterID2Name[MQIACH_RESET_REQUESTED]="ResetRequested";
	hmParameterID2Name[MQIACH_BATCH_DATA_LIMIT]="BatchDataLimit";
	hmParameterID2Name[MQIACH_MSG_HISTORY]="MsgHistory";
	hmParameterID2Name[MQIACH_MULTICAST_PROPERTIES]="MulticastProperties";
	hmParameterID2Name[MQIACH_NEW_SUBSCRIBER_HISTORY]="NewSubscriberHistory";
	hmParameterID2Name[MQIACH_MC_HB_INTERVAL]="McHbInterval";
	hmParameterID2Name[MQIACH_USE_CLIENT_ID]="UseClientId";
	hmParameterID2Name[MQIACH_MQTT_KEEP_ALIVE]="MqttKeepAlive";
	hmParameterID2Name[MQIACH_IN_DOUBT_IN]="InDoubtIn";
	hmParameterID2Name[MQIACH_IN_DOUBT_OUT]="InDoubtOut";
	hmParameterID2Name[MQIACH_MSGS_SENT]="MsgsSent";
	hmParameterID2Name[MQIACH_MSGS_RECEIVED]="MsgsReceived";
	hmParameterID2Name[MQIACH_MSGS_RCVD]="MsgsRcvd";
	hmParameterID2Name[MQIACH_PENDING_OUT]="PendingOut";
	hmParameterID2Name[MQIACH_AVAILABLE_CIPHERSPECS]="AvailableCipherspecs";
	hmParameterID2Name[MQIACH_MATCH]="Match";
	hmParameterID2Name[MQIACH_USER_SOURCE]="UserSource";
	hmParameterID2Name[MQIACH_WARNING]="Warning";
	hmParameterID2Name[MQIACH_DEF_RECONNECT]="DefReconnect";
	hmParameterID2Name[MQIACH_CHANNEL_SUMMARY_ATTRS]="ChannelSummaryAttrs";
	hmParameterID2Name[MQCACH_CHANNEL_NAME]="ChannelName";
	hmParameterID2Name[MQCACH_DESC]="Desc";
	hmParameterID2Name[MQCACH_MODE_NAME]="ModeName";
	hmParameterID2Name[MQCACH_TP_NAME]="TpName";
	hmParameterID2Name[MQCACH_XMIT_Q_NAME]="XmitQName";
	hmParameterID2Name[MQCACH_CONNECTION_NAME]="ConnectionName";
	hmParameterID2Name[MQCACH_MCA_NAME]="MCAName";
	hmParameterID2Name[MQCACH_SEC_EXIT_NAME]="SecExitName";
	hmParameterID2Name[MQCACH_MSG_EXIT_NAME]="MsgExitName";
	hmParameterID2Name[MQCACH_SEND_EXIT_NAME]="SendExitName";
	hmParameterID2Name[MQCACH_RCV_EXIT_NAME]="RcvExitName";
	hmParameterID2Name[MQCACH_CHANNEL_NAMES]="ChannelNames";
	hmParameterID2Name[MQCACH_SEC_EXIT_USER_DATA]="SecExitUserData";
	hmParameterID2Name[MQCACH_MSG_EXIT_USER_DATA]="MsgExitUserData";
	hmParameterID2Name[MQCACH_SEND_EXIT_USER_DATA]="SendExitUserData";
	hmParameterID2Name[MQCACH_RCV_EXIT_USER_DATA]="RcvExitUserData";
	hmParameterID2Name[MQCACH_USER_ID]="UserId";
	hmParameterID2Name[MQCACH_PASSWORD]="Password";
	hmParameterID2Name[MQCACH_LOCAL_ADDRESS]="LocalAddress";
	hmParameterID2Name[MQCACH_LOCAL_NAME]="LocalName";
	hmParameterID2Name[MQCACH_LAST_MSG_TIME]="LastMsgTime";
	hmParameterID2Name[MQCACH_LAST_MSG_DATE]="LastMsgDate";
	hmParameterID2Name[MQCACH_MCA_USER_ID]="MCAUserId";
	hmParameterID2Name[MQCACH_CHANNEL_START_TIME]="ChannelStartTime";
	hmParameterID2Name[MQCACH_CHANNEL_START_DATE]="ChannelStartDate";
	hmParameterID2Name[MQCACH_MCA_JOB_NAME]="MCAJobName";
	hmParameterID2Name[MQCACH_LAST_LUWID]="LastLuwid";
	hmParameterID2Name[MQCACH_CURRENT_LUWID]="CurrentLuwid";
	hmParameterID2Name[MQCACH_FORMAT_NAME]="FormatName";
	hmParameterID2Name[MQCACH_MR_EXIT_NAME]="MrExitName";
	hmParameterID2Name[MQCACH_MR_EXIT_USER_DATA]="MrExitUserData";
	hmParameterID2Name[MQCACH_SSL_CIPHER_SPEC]="SslCipherSpec";
	hmParameterID2Name[MQCACH_SSL_PEER_NAME]="SslPeerName";
	hmParameterID2Name[MQCACH_SSL_HANDSHAKE_STAGE]="SslHandshakeStage";
	hmParameterID2Name[MQCACH_SSL_SHORT_PEER_NAME]="SslShortPeerName";
	hmParameterID2Name[MQCACH_REMOTE_APPL_TAG]="RemoteApplTag";
	hmParameterID2Name[MQCACH_SSL_CERT_USER_ID]="SslCertUserId";
	hmParameterID2Name[MQCACH_SSL_CERT_ISSUER_NAME]="SslCertIssuerName";
	hmParameterID2Name[MQCACH_LU_NAME]="LuName";
	hmParameterID2Name[MQCACH_IP_ADDRESS]="IpAddress";
	hmParameterID2Name[MQCACH_TCP_NAME]="TcpName";
	hmParameterID2Name[MQCACH_LISTENER_NAME]="ListenerName";
	hmParameterID2Name[MQCACH_LISTENER_DESC]="ListenerDesc";
	hmParameterID2Name[MQCACH_LISTENER_START_DATE]="ListenerStartDate";
	hmParameterID2Name[MQCACH_LISTENER_START_TIME]="ListenerStartTime";
	hmParameterID2Name[MQCACH_SSL_KEY_RESET_DATE]="SslKeyResetDate";
	hmParameterID2Name[MQCACH_SSL_KEY_RESET_TIME]="SslKeyResetTime";
	hmParameterID2Name[MQCACH_REMOTE_VERSION]="RemoteVersion";
	hmParameterID2Name[MQCACH_REMOTE_PRODUCT]="RemoteProduct";
	hmParameterID2Name[MQCACH_GROUP_ADDRESS]="GroupAddress";
	hmParameterID2Name[MQCACH_JAAS_CONFIG]="JaasConfig";
	hmParameterID2Name[MQCACH_CLIENT_ID]="ClientId";
	hmParameterID2Name[MQCACH_SSL_KEY_PASSPHRASE]="SslKeyPassphrase";
	hmParameterID2Name[MQCACH_CONNECTION_NAME_LIST]="ConnectionNameList";
	hmParameterID2Name[MQCACH_CLIENT_USER_ID]="ClientUserId";
	hmParameterID2Name[MQCACH_MCA_USER_ID_LIST]="MCAUserIdList";
	hmParameterID2Name[MQCACH_SSL_CIPHER_SUITE]="SslCipherSuite";


	hmParameterID2Name[MQIACF_Q_MGR_ATTRS]="QMgrAttrs";
	hmParameterID2Name[MQIACF_Q_ATTRS]="QAttrs";
	hmParameterID2Name[MQIACF_PROCESS_ATTRS]="ProcessAttrs";
	hmParameterID2Name[MQIACF_NAMELIST_ATTRS]="NamelistAttrs";
	hmParameterID2Name[MQIACF_FORCE]="Force";
	hmParameterID2Name[MQIACF_REPLACE]="Replace";
	hmParameterID2Name[MQIACF_PURGE]="Purge";
	hmParameterID2Name[MQIACF_QUIESCE]="Quiesce";
	hmParameterID2Name[MQIACF_MODE]="Mode";
	hmParameterID2Name[MQIACF_ALL]="All";
	hmParameterID2Name[MQIACF_EVENT_APPL_TYPE]="EventApplType";
	hmParameterID2Name[MQIACF_EVENT_ORIGIN]="EventOrigin";
	hmParameterID2Name[MQIACF_PARAMETER_ID]="ParameterId";
	hmParameterID2Name[MQIACF_ERROR_ID]="ErrorId";
	hmParameterID2Name[MQIACF_ERROR_IDENTIFIER]="ErrorIdentifier";
	hmParameterID2Name[MQIACF_SELECTOR]="Selector";
	hmParameterID2Name[MQIACF_CHANNEL_ATTRS]="ChannelAttrs";
	hmParameterID2Name[MQIACF_OBJECT_TYPE]="ObjectType";
	hmParameterID2Name[MQIACF_ESCAPE_TYPE]="EscapeType";
	hmParameterID2Name[MQIACF_ERROR_OFFSET]="ErrorOffset";
	hmParameterID2Name[MQIACF_AUTH_INFO_ATTRS]="AuthInfoAttrs";
	hmParameterID2Name[MQIACF_REASON_QUALIFIER]="ReasonQualifier";
	hmParameterID2Name[MQIACF_COMMAND]="Command";
	hmParameterID2Name[MQIACF_OPEN_OPTIONS]="OpenOptions";
	hmParameterID2Name[MQIACF_OPEN_TYPE]="OpenType";
	hmParameterID2Name[MQIACF_PROCESS_ID]="ApplicationPid";
	hmParameterID2Name[MQIACF_THREAD_ID]="ApplicationTid";
	hmParameterID2Name[MQIACF_Q_STATUS_ATTRS]="QStatusAttrs";
	hmParameterID2Name[MQIACF_UNCOMMITTED_MSGS]="UncommittedMsgs";
	hmParameterID2Name[MQIACF_HANDLE_STATE]="HandleState";
	hmParameterID2Name[MQIACF_AUX_ERROR_DATA_INT_1]="AuxErrorDataInt11";
	hmParameterID2Name[MQIACF_AUX_ERROR_DATA_INT_2]="AuxErrorDataInt22";
	hmParameterID2Name[MQIACF_CONV_REASON_CODE]="ConvReasonCode";
	hmParameterID2Name[MQIACF_BRIDGE_TYPE]="BridgeType";
	hmParameterID2Name[MQIACF_INQUIRY]="Inquiry";
	hmParameterID2Name[MQIACF_WAIT_INTERVAL]="WaitInterval";
	hmParameterID2Name[MQIACF_OPTIONS]="Options";
	hmParameterID2Name[MQIACF_BROKER_OPTIONS]="BrokerOptions";
	hmParameterID2Name[MQIACF_REFRESH_TYPE]="RefreshType";
	hmParameterID2Name[MQIACF_SEQUENCE_NUMBER]="SeqNumber";
	hmParameterID2Name[MQIACF_INTEGER_DATA]="IntegerData";
	hmParameterID2Name[MQIACF_REGISTRATION_OPTIONS]="RegistrationOptions";
	hmParameterID2Name[MQIACF_PUBLICATION_OPTIONS]="PublicationOptions";
	hmParameterID2Name[MQIACF_CLUSTER_INFO]="ClusterInfo";
	hmParameterID2Name[MQIACF_Q_MGR_DEFINITION_TYPE]="QMgrDefinitionType";
	hmParameterID2Name[MQIACF_Q_MGR_TYPE]="QMgrType";
	hmParameterID2Name[MQIACF_ACTION]="Action";
	hmParameterID2Name[MQIACF_SUSPEND]="Suspend";
	hmParameterID2Name[MQIACF_BROKER_COUNT]="BrokerCount";
	hmParameterID2Name[MQIACF_APPL_COUNT]="ApplCount";
	hmParameterID2Name[MQIACF_ANONYMOUS_COUNT]="AnonymousCount";
	hmParameterID2Name[MQIACF_REG_REG_OPTIONS]="RegRegOptions";
	hmParameterID2Name[MQIACF_DELETE_OPTIONS]="DeleteOptions";
	hmParameterID2Name[MQIACF_CLUSTER_Q_MGR_ATTRS]="ClusterQMgrAttrs";
	hmParameterID2Name[MQIACF_REFRESH_INTERVAL]="RefreshInterval";
	hmParameterID2Name[MQIACF_REFRESH_REPOSITORY]="RefreshRepository";
	hmParameterID2Name[MQIACF_REMOVE_QUEUES]="RemoveQueues";
	hmParameterID2Name[MQIACF_OPEN_INPUT_TYPE]="OpenInputType";
	hmParameterID2Name[MQIACF_OPEN_OUTPUT]="OpenOutput";
	hmParameterID2Name[MQIACF_OPEN_SET]="OpenSet";
	hmParameterID2Name[MQIACF_OPEN_INQUIRE]="OpenInquire";
	hmParameterID2Name[MQIACF_OPEN_BROWSE]="OpenBrowse";
	hmParameterID2Name[MQIACF_Q_STATUS_TYPE]="QStatusType";
	hmParameterID2Name[MQIACF_Q_HANDLE]="QHandle";
	hmParameterID2Name[MQIACF_Q_STATUS]="QStatus";
	hmParameterID2Name[MQIACF_SECURITY_TYPE]="SecurityType";
	hmParameterID2Name[MQIACF_CONNECTION_ATTRS]="ConnectionAttrs";
	hmParameterID2Name[MQIACF_CONNECT_OPTIONS]="ConnectOptions";
	hmParameterID2Name[MQIACF_CONN_INFO_TYPE]="ConnInfoType";
	hmParameterID2Name[MQIACF_CONN_INFO_CONN]="ConnInfoConn";
	hmParameterID2Name[MQIACF_CONN_INFO_HANDLE]="ConnInfoHandle";
	hmParameterID2Name[MQIACF_CONN_INFO_ALL]="ConnInfoAll";
	hmParameterID2Name[MQIACF_AUTH_PROFILE_ATTRS]="AuthProfileAttrs";
	hmParameterID2Name[MQIACF_AUTHORIZATION_LIST]="AuthorizationList";
	hmParameterID2Name[MQIACF_AUTH_ADD_AUTHS]="AuthAddAuths";
	hmParameterID2Name[MQIACF_AUTH_REMOVE_AUTHS]="AuthRemoveAuths";
	hmParameterID2Name[MQIACF_ENTITY_TYPE]="EntityType";
	hmParameterID2Name[MQIACF_COMMAND_INFO]="CommandInfo";
	hmParameterID2Name[MQIACF_CMDSCOPE_Q_MGR_COUNT]="CmdscopeQMgrCount";
	hmParameterID2Name[MQIACF_Q_MGR_SYSTEM]="QMgrSystem";
	hmParameterID2Name[MQIACF_Q_MGR_EVENT]="QMgrEvent";
	hmParameterID2Name[MQIACF_Q_MGR_DQM]="QMgrDqm";
	hmParameterID2Name[MQIACF_Q_MGR_CLUSTER]="QMgrCluster";
	hmParameterID2Name[MQIACF_QSG_DISPS]="QsgDisps";
	hmParameterID2Name[MQIACF_UOW_STATE]="UowState";
	hmParameterID2Name[MQIACF_SECURITY_ITEM]="SecurityItem";
	hmParameterID2Name[MQIACF_CF_STRUC_STATUS]="CfStrucStatus";
	hmParameterID2Name[MQIACF_UOW_TYPE]="UowType";
	hmParameterID2Name[MQIACF_CF_STRUC_ATTRS]="CfStrucAttrs";
	hmParameterID2Name[MQIACF_EXCLUDE_INTERVAL]="ExcludeInterval";
	hmParameterID2Name[MQIACF_CF_STATUS_TYPE]="CfStatusType";
	hmParameterID2Name[MQIACF_CF_STATUS_SUMMARY]="CfStatusSummary";
	hmParameterID2Name[MQIACF_CF_STATUS_CONNECT]="CfStatusConnect";
	hmParameterID2Name[MQIACF_CF_STATUS_BACKUP]="CfStatusBackup";
	hmParameterID2Name[MQIACF_CF_STRUC_TYPE]="CfStrucType";
	hmParameterID2Name[MQIACF_CF_STRUC_SIZE_MAX]="CfStrucSizeMax";
	hmParameterID2Name[MQIACF_CF_STRUC_SIZE_USED]="CfStrucSizeUsed";
	hmParameterID2Name[MQIACF_CF_STRUC_ENTRIES_MAX]="CfStrucEntriesMax";
	hmParameterID2Name[MQIACF_CF_STRUC_ENTRIES_USED]="CfStrucEntriesUsed";
	hmParameterID2Name[MQIACF_CF_STRUC_BACKUP_SIZE]="CfStrucBackupSize";
	hmParameterID2Name[MQIACF_MOVE_TYPE]="MoveType";
	hmParameterID2Name[MQIACF_MOVE_TYPE_MOVE]="MoveTypeMove";
	hmParameterID2Name[MQIACF_MOVE_TYPE_ADD]="MoveTypeAdd";
	hmParameterID2Name[MQIACF_Q_MGR_NUMBER]="QMgrNumber";
	hmParameterID2Name[MQIACF_Q_MGR_STATUS]="QMgrStatus";
	hmParameterID2Name[MQIACF_DB2_CONN_STATUS]="Db2ConnStatus";
	hmParameterID2Name[MQIACF_SECURITY_ATTRS]="SecurityAttrs";
	hmParameterID2Name[MQIACF_SECURITY_TIMEOUT]="SecurityTimeout";
	hmParameterID2Name[MQIACF_SECURITY_INTERVAL]="SecurityInterval";
	hmParameterID2Name[MQIACF_SECURITY_SWITCH]="SecuritySwitch";
	hmParameterID2Name[MQIACF_SECURITY_SETTING]="SecuritySetting";
	hmParameterID2Name[MQIACF_STORAGE_CLASS_ATTRS]="StorageClassAttrs";
	hmParameterID2Name[MQIACF_USAGE_TYPE]="UsageType";
	hmParameterID2Name[MQIACF_BUFFER_POOL_ID]="BufferPoolId";
	hmParameterID2Name[MQIACF_USAGE_TOTAL_PAGES]="UsageTotalPages";
	hmParameterID2Name[MQIACF_USAGE_UNUSED_PAGES]="UsageUnusedPages";
	hmParameterID2Name[MQIACF_USAGE_PERSIST_PAGES]="UsagePersistPages";
	hmParameterID2Name[MQIACF_USAGE_NONPERSIST_PAGES]="UsageNonpersistPages";
	hmParameterID2Name[MQIACF_USAGE_RESTART_EXTENTS]="UsageRestartExtents";
	hmParameterID2Name[MQIACF_USAGE_EXPAND_COUNT]="UsageExpandCount";
	hmParameterID2Name[MQIACF_PAGESET_STATUS]="PagesetStatus";
	hmParameterID2Name[MQIACF_USAGE_TOTAL_BUFFERS]="UsageTotalBuffers";
	hmParameterID2Name[MQIACF_USAGE_DATA_SET_TYPE]="UsageDataSetType";
	hmParameterID2Name[MQIACF_USAGE_PAGESET]="UsagePageset";
	hmParameterID2Name[MQIACF_USAGE_DATA_SET]="UsageDataSet";
	hmParameterID2Name[MQIACF_USAGE_BUFFER_POOL]="UsageBufferPool";
	hmParameterID2Name[MQIACF_MOVE_COUNT]="MoveCount";
	hmParameterID2Name[MQIACF_EXPIRY_Q_COUNT]="ExpiryQCount";
	hmParameterID2Name[MQIACF_CONFIGURATION_OBJECTS]="ConfigurationObjects";
	hmParameterID2Name[MQIACF_CONFIGURATION_EVENTS]="ConfigurationEvents";
	hmParameterID2Name[MQIACF_SYSP_TYPE]="SyspType";
	hmParameterID2Name[MQIACF_SYSP_DEALLOC_INTERVAL]="SyspDeallocInterval";
	hmParameterID2Name[MQIACF_SYSP_MAX_ARCHIVE]="SyspMaxArchive";
	hmParameterID2Name[MQIACF_SYSP_MAX_READ_TAPES]="SyspMaxReadTapes";
	hmParameterID2Name[MQIACF_SYSP_IN_BUFFER_SIZE]="SyspInBufferSize";
	hmParameterID2Name[MQIACF_SYSP_OUT_BUFFER_SIZE]="SyspOutBufferSize";
	hmParameterID2Name[MQIACF_SYSP_OUT_BUFFER_COUNT]="SyspOutBufferCount";
	hmParameterID2Name[MQIACF_SYSP_ARCHIVE]="SyspArchive";
	hmParameterID2Name[MQIACF_SYSP_DUAL_ACTIVE]="SyspDualActive";
	hmParameterID2Name[MQIACF_SYSP_DUAL_ARCHIVE]="SyspDualArchive";
	hmParameterID2Name[MQIACF_SYSP_DUAL_BSDS]="SyspDualBsds";
	hmParameterID2Name[MQIACF_SYSP_MAX_CONNS]="SyspMaxConns";
	hmParameterID2Name[MQIACF_SYSP_MAX_CONNS_FORE]="SyspMaxConnsFore";
	hmParameterID2Name[MQIACF_SYSP_MAX_CONNS_BACK]="SyspMaxConnsBack";
	hmParameterID2Name[MQIACF_SYSP_EXIT_INTERVAL]="SyspExitInterval";
	hmParameterID2Name[MQIACF_SYSP_EXIT_TASKS]="SyspExitTasks";
	hmParameterID2Name[MQIACF_SYSP_CHKPOINT_COUNT]="SyspChkpointCount";
	hmParameterID2Name[MQIACF_SYSP_OTMA_INTERVAL]="SyspOtmaInterval";
	hmParameterID2Name[MQIACF_SYSP_Q_INDEX_DEFER]="SyspQIndexDefer";
	hmParameterID2Name[MQIACF_SYSP_DB2_TASKS]="SyspDb2Tasks";
	hmParameterID2Name[MQIACF_SYSP_RESLEVEL_AUDIT]="SyspReslevelAudit";
	hmParameterID2Name[MQIACF_SYSP_ROUTING_CODE]="SyspRoutingCode";
	hmParameterID2Name[MQIACF_SYSP_SMF_ACCOUNTING]="SyspSmfAccounting";
	hmParameterID2Name[MQIACF_SYSP_SMF_STATS]="SyspSmfStats";
	hmParameterID2Name[MQIACF_SYSP_SMF_INTERVAL]="SyspSmfInterval";
	hmParameterID2Name[MQIACF_SYSP_TRACE_CLASS]="SyspTraceClass";
	hmParameterID2Name[MQIACF_SYSP_TRACE_SIZE]="SyspTraceSize";
	hmParameterID2Name[MQIACF_SYSP_WLM_INTERVAL]="SyspWlmInterval";
	hmParameterID2Name[MQIACF_SYSP_ALLOC_UNIT]="SyspAllocUnit";
	hmParameterID2Name[MQIACF_SYSP_ARCHIVE_RETAIN]="SyspArchiveRetain";
	hmParameterID2Name[MQIACF_SYSP_ARCHIVE_WTOR]="SyspArchiveWtor";
	hmParameterID2Name[MQIACF_SYSP_BLOCK_SIZE]="SyspBlockSize";
	hmParameterID2Name[MQIACF_SYSP_CATALOG]="SyspCatalog";
	hmParameterID2Name[MQIACF_SYSP_COMPACT]="SyspCompact";
	hmParameterID2Name[MQIACF_SYSP_ALLOC_PRIMARY]="SyspAllocPrimary";
	hmParameterID2Name[MQIACF_SYSP_ALLOC_SECONDARY]="SyspAllocSecondary";
	hmParameterID2Name[MQIACF_SYSP_PROTECT]="SyspProtect";
	hmParameterID2Name[MQIACF_SYSP_QUIESCE_INTERVAL]="SyspQuiesceInterval";
	hmParameterID2Name[MQIACF_SYSP_TIMESTAMP]="SyspTimestamp";
	hmParameterID2Name[MQIACF_SYSP_UNIT_ADDRESS]="SyspUnitAddress";
	hmParameterID2Name[MQIACF_SYSP_UNIT_STATUS]="SyspUnitStatus";
	hmParameterID2Name[MQIACF_SYSP_LOG_COPY]="SyspLogCopy";
	hmParameterID2Name[MQIACF_SYSP_LOG_USED]="SyspLogUsed";
	hmParameterID2Name[MQIACF_SYSP_LOG_SUSPEND]="SyspLogSuspend";
	hmParameterID2Name[MQIACF_SYSP_OFFLOAD_STATUS]="SyspOffloadStatus";
	hmParameterID2Name[MQIACF_SYSP_TOTAL_LOGS]="SyspTotalLogs";
	hmParameterID2Name[MQIACF_SYSP_FULL_LOGS]="SyspFullLogs";
	hmParameterID2Name[MQIACF_LISTENER_ATTRS]="ListenerAttrs";
	hmParameterID2Name[MQIACF_LISTENER_STATUS_ATTRS]="ListenerStatusAttrs";
	hmParameterID2Name[MQIACF_SERVICE_ATTRS]="ServiceAttrs";
	hmParameterID2Name[MQIACF_SERVICE_STATUS_ATTRS]="ServiceStatusAttrs";
	hmParameterID2Name[MQIACF_Q_TIME_INDICATOR]="QTimeIndicator";
	hmParameterID2Name[MQIACF_OLDEST_MSG_AGE]="OldestMsgAge";
	hmParameterID2Name[MQIACF_AUTH_OPTIONS]="AuthOptions";
	hmParameterID2Name[MQIACF_Q_MGR_STATUS_ATTRS]="QMgrStatusAttrs";
	hmParameterID2Name[MQIACF_CONNECTION_COUNT]="ConnectionCount";
	hmParameterID2Name[MQIACF_Q_MGR_FACILITY]="QMgrFacility";
	hmParameterID2Name[MQIACF_CHINIT_STATUS]="ChinitStatus";
	hmParameterID2Name[MQIACF_CMD_SERVER_STATUS]="CmdServerStatus";
	hmParameterID2Name[MQIACF_ROUTE_DETAIL]="RouteDetail";
	hmParameterID2Name[MQIACF_RECORDED_ACTIVITIES]="RecordedActivities";
	hmParameterID2Name[MQIACF_MAX_ACTIVITIES]="MaxActivities";
	hmParameterID2Name[MQIACF_DISCONTINUITY_COUNT]="DiscontinuityCount";
	hmParameterID2Name[MQIACF_ROUTE_ACCUMULATION]="RouteAccumulation";
	hmParameterID2Name[MQIACF_ROUTE_DELIVERY]="RouteDelivery";
	hmParameterID2Name[MQIACF_OPERATION_TYPE]="OperationType";
	hmParameterID2Name[MQIACF_BACKOUT_COUNT]="BackoutCount";
	hmParameterID2Name[MQIACF_COMP_CODE]="CompCode";
	hmParameterID2Name[MQIACF_ENCODING]="Encoding";
	hmParameterID2Name[MQIACF_EXPIRY]="Expiry";
	hmParameterID2Name[MQIACF_FEEDBACK]="Feedback";
	hmParameterID2Name[MQIACF_MSG_FLAGS]="MsgFlags";
	hmParameterID2Name[MQIACF_MSG_LENGTH]="MsgLength";
	hmParameterID2Name[MQIACF_MSG_TYPE]="MsgType";
	hmParameterID2Name[MQIACF_OFFSET]="Offset";
	hmParameterID2Name[MQIACF_ORIGINAL_LENGTH]="OriginalLength";
	hmParameterID2Name[MQIACF_PERSISTENCE]="Persistence";
	hmParameterID2Name[MQIACF_PRIORITY]="Priority";
	hmParameterID2Name[MQIACF_REASON_CODE]="ReasonCode";
	hmParameterID2Name[MQIACF_REPORT]="Report";
	hmParameterID2Name[MQIACF_VERSION]="Version";
	hmParameterID2Name[MQIACF_UNRECORDED_ACTIVITIES]="UnrecordedActivities";
	hmParameterID2Name[MQIACF_MONITORING]="Monitoring";
	hmParameterID2Name[MQIACF_ROUTE_FORWARDING]="RouteForwarding";
	hmParameterID2Name[MQIACF_SERVICE_STATUS]="ServiceStatus";
	hmParameterID2Name[MQIACF_Q_TYPES]="QTypes";
	hmParameterID2Name[MQIACF_USER_ID_SUPPORT]="UserIdSupport";
	hmParameterID2Name[MQIACF_INTERFACE_VERSION]="InterfaceVersion";
	hmParameterID2Name[MQIACF_AUTH_SERVICE_ATTRS]="AuthServiceAttrs";
	hmParameterID2Name[MQIACF_USAGE_EXPAND_TYPE]="UsageExpandType";
	hmParameterID2Name[MQIACF_SYSP_CLUSTER_CACHE]="SyspClusterCache";
	hmParameterID2Name[MQIACF_SYSP_DB2_BLOB_TASKS]="SyspDb2BlobTasks";
	hmParameterID2Name[MQIACF_SYSP_WLM_INT_UNITS]="SyspWlmIntUnits";
	hmParameterID2Name[MQIACF_TOPIC_ATTRS]="TopicAttrs";
	hmParameterID2Name[MQIACF_PUBSUB_PROPERTIES]="PubsubProperties";
	hmParameterID2Name[MQIACF_DESTINATION_CLASS]="DestinationClass";
	hmParameterID2Name[MQIACF_DURABLE_SUBSCRIPTION]="DurableSubscription";
	hmParameterID2Name[MQIACF_SUBSCRIPTION_SCOPE]="SubscriptionScope";
	hmParameterID2Name[MQIACF_VARIABLE_USER_ID]="VariableUserId";
	hmParameterID2Name[MQIACF_REQUEST_ONLY]="RequestOnly";
	hmParameterID2Name[MQIACF_PUB_PRIORITY]="PubPriority";
	hmParameterID2Name[MQIACF_SUB_ATTRS]="SubAttrs";
	hmParameterID2Name[MQIACF_WILDCARD_SCHEMA]="WildcardSchema";
	hmParameterID2Name[MQIACF_SUB_TYPE]="SubType";
	hmParameterID2Name[MQIACF_MESSAGE_COUNT]="MessageCount";
	hmParameterID2Name[MQIACF_Q_MGR_PUBSUB]="QMgrPubsub";
	hmParameterID2Name[MQIACF_Q_MGR_VERSION]="QMgrVersion";
	hmParameterID2Name[MQIACF_SUB_STATUS_ATTRS]="SubStatusAttrs";
	hmParameterID2Name[MQIACF_TOPIC_STATUS]="TopicStatus";
	hmParameterID2Name[MQIACF_TOPIC_SUB]="TopicSub";
	hmParameterID2Name[MQIACF_TOPIC_PUB]="TopicPub";
	hmParameterID2Name[MQIACF_RETAINED_PUBLICATION]="RetainedPublication";
	hmParameterID2Name[MQIACF_TOPIC_STATUS_ATTRS]="TopicStatusAttrs";
	hmParameterID2Name[MQIACF_TOPIC_STATUS_TYPE]="TopicStatusType";
	hmParameterID2Name[MQIACF_SUB_OPTIONS]="SubOptions";
	hmParameterID2Name[MQIACF_PUBLISH_COUNT]="PublishCount";
	hmParameterID2Name[MQIACF_CLEAR_TYPE]="ClearType";
	hmParameterID2Name[MQIACF_CLEAR_SCOPE]="ClearScope";
	hmParameterID2Name[MQIACF_SUB_LEVEL]="SubLevel";
	hmParameterID2Name[MQIACF_ASYNC_STATE]="AsyncState";
	hmParameterID2Name[MQIACF_SUB_SUMMARY]="SubSummary";
	hmParameterID2Name[MQIACF_OBSOLETE_MSGS]="ObsoleteMsgs";
	hmParameterID2Name[MQIACF_PUBSUB_STATUS]="PubsubStatus";
	hmParameterID2Name[MQIACF_PS_STATUS_TYPE]="PsStatusType";
	hmParameterID2Name[MQIACF_PUBSUB_STATUS_ATTRS]="PubsubStatusAttrs";
	hmParameterID2Name[MQIACF_SELECTOR_TYPE]="SelectorType";
	hmParameterID2Name[MQIACF_LOG_COMPRESSION]="LogCompression";
	hmParameterID2Name[MQIACF_GROUPUR_CHECK_ID]="GroupurCheckId";
	hmParameterID2Name[MQIACF_MULC_CAPTURE]="MulcCapture";
	hmParameterID2Name[MQIACF_PERMIT_STANDBY]="PermitStandby";
	hmParameterID2Name[MQIACF_OPERATION_MODE]="OperationMode";
	hmParameterID2Name[MQIACF_COMM_INFO_ATTRS]="CommInfoAttrs";
	hmParameterID2Name[MQIACF_CF_SMDS_BLOCK_SIZE]="CfSmdsBlockSize";
	hmParameterID2Name[MQIACF_CF_SMDS_EXPAND]="CfSmdsExpand";
	hmParameterID2Name[MQIACF_USAGE_FREE_BUFF]="UsageFreeBuff";
	hmParameterID2Name[MQIACF_USAGE_FREE_BUFF_PERC]="UsageFreeBuffPerc";
	hmParameterID2Name[MQIACF_CF_STRUC_ACCESS]="CfStrucAccess";
	hmParameterID2Name[MQIACF_CF_STATUS_SMDS]="CfStatusSmds";
	hmParameterID2Name[MQIACF_SMDS_ATTRS]="SmdsAttrs";
	hmParameterID2Name[MQIACF_USAGE_SMDS]="UsageSmds";
	hmParameterID2Name[MQIACF_USAGE_BLOCK_SIZE]="UsageBlockSize";
	hmParameterID2Name[MQIACF_USAGE_DATA_BLOCKS]="UsageDataBlocks";
	hmParameterID2Name[MQIACF_USAGE_EMPTY_BUFFERS]="UsageEmptyBuffers";
	hmParameterID2Name[MQIACF_USAGE_INUSE_BUFFERS]="UsageInuseBuffers";
	hmParameterID2Name[MQIACF_USAGE_LOWEST_FREE]="UsageLowestFree";
	hmParameterID2Name[MQIACF_USAGE_OFFLOAD_MSGS]="UsageOffloadMsgs";
	hmParameterID2Name[MQIACF_USAGE_READS_SAVED]="UsageReadsSaved";
	hmParameterID2Name[MQIACF_USAGE_SAVED_BUFFERS]="UsageSavedBuffers";
	hmParameterID2Name[MQIACF_USAGE_TOTAL_BLOCKS]="UsageTotalBlocks";
	hmParameterID2Name[MQIACF_USAGE_USED_BLOCKS]="UsageUsedBlocks";
	hmParameterID2Name[MQIACF_USAGE_USED_RATE]="UsageUsedRate";
	hmParameterID2Name[MQIACF_USAGE_WAIT_RATE]="UsageWaitRate";
	hmParameterID2Name[MQIACF_SMDS_OPENMODE]="SmdsOpenmode";
	hmParameterID2Name[MQIACF_SMDS_STATUS]="SmdsStatus";
	hmParameterID2Name[MQIACF_SMDS_AVAIL]="SmdsAvail";
	hmParameterID2Name[MQIACF_MCAST_REL_INDICATOR]="McastRelIndicator";
	hmParameterID2Name[MQIACF_CHLAUTH_TYPE]="ChlauthType";
	hmParameterID2Name[MQIACF_MQXR_DIAGNOSTICS_TYPE]="MqxrDiagnosticsType";
	hmParameterID2Name[MQIACF_CHLAUTH_ATTRS]="ChlauthAttrs";
	hmParameterID2Name[MQIACF_OPERATION_ID]="OperationId";
	hmParameterID2Name[MQIACF_API_CALLER_TYPE]="ApiCallerType";
	hmParameterID2Name[MQIACF_API_ENVIRONMENT]="ApiEnvironment";
	hmParameterID2Name[MQIACF_TRACE_DETAIL]="TraceDetail";
	hmParameterID2Name[MQIACF_HOBJ]="Hobj";
	hmParameterID2Name[MQIACF_CALL_TYPE]="CallType";
	hmParameterID2Name[MQIACF_MQCB_OPERATION]="MqcbOperation";
	hmParameterID2Name[MQIACF_MQCB_TYPE]="MqcbType";
	hmParameterID2Name[MQIACF_MQCB_OPTIONS]="MqcbOptions";
	hmParameterID2Name[MQIACF_CLOSE_OPTIONS]="CloseOptions";
	hmParameterID2Name[MQIACF_CTL_OPERATION]="CtlOperation";
	hmParameterID2Name[MQIACF_GET_OPTIONS]="GetOptions";
	hmParameterID2Name[MQIACF_RECS_PRESENT]="RecsPresent";
	hmParameterID2Name[MQIACF_KNOWN_DEST_COUNT]="KnownDestCount";
	hmParameterID2Name[MQIACF_UNKNOWN_DEST_COUNT]="UnknownDestCount";
	hmParameterID2Name[MQIACF_INVALID_DEST_COUNT]="InvalidDestCount";
	hmParameterID2Name[MQIACF_RESOLVED_TYPE]="ResolvedType";
	hmParameterID2Name[MQIACF_PUT_OPTIONS]="PutOptions";
	hmParameterID2Name[MQIACF_BUFFER_LENGTH]="BufferLength";
	hmParameterID2Name[MQIACF_TRACE_DATA_LENGTH]="TraceDataLength";
	hmParameterID2Name[MQIACF_SMDS_EXPANDST]="SmdsExpandst";
	hmParameterID2Name[MQIACF_STRUC_LENGTH]="StrucLength";
	hmParameterID2Name[MQIACF_ITEM_COUNT]="ItemCount";
	hmParameterID2Name[MQIACF_EXPIRY_TIME]="ExpiryTime";
	hmParameterID2Name[MQIACF_CONNECT_TIME]="ConnectTime";
	hmParameterID2Name[MQIACF_DISCONNECT_TIME]="DisconnectTime";
	hmParameterID2Name[MQIACF_HSUB]="Hsub";
	hmParameterID2Name[MQIACF_SUBRQ_OPTIONS]="SubrqOptions";
	hmParameterID2Name[MQIACF_XA_RMID]="XaRmid";
	hmParameterID2Name[MQIACF_XA_FLAGS]="XaFlags";
	hmParameterID2Name[MQIACF_XA_RETCODE]="XaRetcode";
	hmParameterID2Name[MQIACF_XA_HANDLE]="XaHandle";
	hmParameterID2Name[MQIACF_XA_RETVAL]="XaRetval";
	hmParameterID2Name[MQIACF_STATUS_TYPE]="StatusType";
	hmParameterID2Name[MQIACF_XA_COUNT]="XaCount";
	hmParameterID2Name[MQIACF_SELECTOR_COUNT]="SelectorCount";
	hmParameterID2Name[MQIACF_SELECTORS]="Selectors";
	hmParameterID2Name[MQIACF_INTATTR_COUNT]="IntattrCount";
	hmParameterID2Name[MQIACF_INT_ATTRS]="IntAttrs";
	hmParameterID2Name[MQIACF_SUBRQ_ACTION]="SubrqAction";
	hmParameterID2Name[MQIACF_NUM_PUBS]="NumPubs";
	hmParameterID2Name[MQIACF_POINTER_SIZE]="PointerSize";
	hmParameterID2Name[MQIACF_REMOVE_AUTHREC]="RemoveAuthrec";
	hmParameterID2Name[MQIACF_XR_ATTRS]="XrAttrs";
	hmParameterID2Name[MQIACF_APPL_FUNCTION_TYPE]="ApplFunctionType";
	hmParameterID2Name[MQIACF_EXPORT_TYPE]="ExportType";
	hmParameterID2Name[MQIACF_EXPORT_ATTRS]="ExportAttrs";
	hmParameterID2Name[MQIACF_SYSTEM_OBJECTS]="SystemObjects";

	hmParameterID2Name[MQCACF_FROM_Q_NAME]="FromQName";
	hmParameterID2Name[MQCACF_TO_Q_NAME]="ToQName";
	hmParameterID2Name[MQCACF_FROM_PROCESS_NAME]="FromProcessName";
	hmParameterID2Name[MQCACF_TO_PROCESS_NAME]="ToProcessName";
	hmParameterID2Name[MQCACF_FROM_NAMELIST_NAME]="FromNamelistName";
	hmParameterID2Name[MQCACF_TO_NAMELIST_NAME]="ToNamelistName";
	hmParameterID2Name[MQCACF_FROM_CHANNEL_NAME]="FromChannelName";
	hmParameterID2Name[MQCACF_TO_CHANNEL_NAME]="ToChannelName";
	hmParameterID2Name[MQCACF_FROM_AUTH_INFO_NAME]="FromAuthInfoName";
	hmParameterID2Name[MQCACF_TO_AUTH_INFO_NAME]="ToAuthInfoName";
	hmParameterID2Name[MQCACF_Q_NAMES]="QNames";
	hmParameterID2Name[MQCACF_PROCESS_NAMES]="ProcessNames";
	hmParameterID2Name[MQCACF_NAMELIST_NAMES]="NamelistNames";
	hmParameterID2Name[MQCACF_ESCAPE_TEXT]="EscapeText";
	hmParameterID2Name[MQCACF_LOCAL_Q_NAMES]="LocalQNames";
	hmParameterID2Name[MQCACF_MODEL_Q_NAMES]="ModelQNames";
	hmParameterID2Name[MQCACF_ALIAS_Q_NAMES]="AliasQNames";
	hmParameterID2Name[MQCACF_REMOTE_Q_NAMES]="RemoteQNames";
	hmParameterID2Name[MQCACF_SENDER_CHANNEL_NAMES]="SenderChannelNames";
	hmParameterID2Name[MQCACF_SERVER_CHANNEL_NAMES]="ServerChannelNames";
	hmParameterID2Name[MQCACF_REQUESTER_CHANNEL_NAMES]="RequesterChannelNames";
	hmParameterID2Name[MQCACF_RECEIVER_CHANNEL_NAMES]="ReceiverChannelNames";
	hmParameterID2Name[MQCACF_OBJECT_Q_MGR_NAME]="ObjectQMgrName";
	hmParameterID2Name[MQCACF_APPL_NAME]="ApplicationName";
	hmParameterID2Name[MQCACF_USER_IDENTIFIER]="UserIdentifier";
	hmParameterID2Name[MQCACF_AUX_ERROR_DATA_STR_1]="AuxErrorDataStr11";
	hmParameterID2Name[MQCACF_AUX_ERROR_DATA_STR_2]="AuxErrorDataStr22";
	hmParameterID2Name[MQCACF_AUX_ERROR_DATA_STR_3]="AuxErrorDataStr33";
	hmParameterID2Name[MQCACF_BRIDGE_NAME]="BridgeName";
	hmParameterID2Name[MQCACF_STREAM_NAME]="StreamName";
	hmParameterID2Name[MQCACF_TOPIC]="Topic";
	hmParameterID2Name[MQCACF_PARENT_Q_MGR_NAME]="ParentQMgrName";
	hmParameterID2Name[MQCACF_CORREL_ID]="CorrelId";
	hmParameterID2Name[MQCACF_PUBLISH_TIMESTAMP]="PublishTimestamp";
	hmParameterID2Name[MQCACF_STRING_DATA]="StringData";
	hmParameterID2Name[MQCACF_SUPPORTED_STREAM_NAME]="SupportedStreamName";
	hmParameterID2Name[MQCACF_REG_TOPIC]="RegTopic";
	hmParameterID2Name[MQCACF_REG_TIME]="RegTime";
	hmParameterID2Name[MQCACF_REG_USER_ID]="RegUserId";
	hmParameterID2Name[MQCACF_CHILD_Q_MGR_NAME]="ChildQMgrName";
	hmParameterID2Name[MQCACF_REG_STREAM_NAME]="RegStreamName";
	hmParameterID2Name[MQCACF_REG_Q_MGR_NAME]="RegQMgrName";
	hmParameterID2Name[MQCACF_REG_Q_NAME]="RegQName";
	hmParameterID2Name[MQCACF_REG_CORREL_ID]="RegCorrelId";
	hmParameterID2Name[MQCACF_EVENT_USER_ID]="EventUserId";
	hmParameterID2Name[MQCACF_OBJECT_NAME]="ObjectName";
	hmParameterID2Name[MQCACF_EVENT_Q_MGR]="EventQMgr";
	hmParameterID2Name[MQCACF_AUTH_INFO_NAMES]="AuthInfoNames";
	hmParameterID2Name[MQCACF_EVENT_APPL_IDENTITY]="EventIdentityData";
	hmParameterID2Name[MQCACF_EVENT_APPL_NAME]="EventApplName";
	hmParameterID2Name[MQCACF_EVENT_APPL_ORIGIN]="EventApplOrigin";
	hmParameterID2Name[MQCACF_SUBSCRIPTION_NAME]="SubscriptionName";
	hmParameterID2Name[MQCACF_REG_SUB_NAME]="RegSubName";
	hmParameterID2Name[MQCACF_SUBSCRIPTION_IDENTITY]="SubscriptionIdentity";
	hmParameterID2Name[MQCACF_REG_SUB_IDENTITY]="RegSubIdentity";
	hmParameterID2Name[MQCACF_SUBSCRIPTION_USER_DATA]="SubscriptionUserData";
	hmParameterID2Name[MQCACF_REG_SUB_USER_DATA]="RegSubUserData";
	hmParameterID2Name[MQCACF_APPL_TAG]="ApplTag";
	hmParameterID2Name[MQCACF_DATA_SET_NAME]="DataSetName";
	hmParameterID2Name[MQCACF_UOW_START_DATE]="UowStartDate";
	hmParameterID2Name[MQCACF_UOW_START_TIME]="UowStartTime";
	hmParameterID2Name[MQCACF_UOW_LOG_START_DATE]="UowLogStartDate";
	hmParameterID2Name[MQCACF_UOW_LOG_START_TIME]="UowLogStartTime";
	hmParameterID2Name[MQCACF_UOW_LOG_EXTENT_NAME]="UowLogExtentName";
	hmParameterID2Name[MQCACF_PRINCIPAL_ENTITY_NAMES]="PrincipalEntityNames";
	hmParameterID2Name[MQCACF_GROUP_ENTITY_NAMES]="GroupEntityNames";
	hmParameterID2Name[MQCACF_AUTH_PROFILE_NAME]="AuthProfileName";
	hmParameterID2Name[MQCACF_ENTITY_NAME]="EntityName";
	hmParameterID2Name[MQCACF_SERVICE_COMPONENT]="ServiceComponent";
	hmParameterID2Name[MQCACF_RESPONSE_Q_MGR_NAME]="ResponseQMgrName";
	hmParameterID2Name[MQCACF_CURRENT_LOG_EXTENT_NAME]="CurrentLogExtentName";
	hmParameterID2Name[MQCACF_RESTART_LOG_EXTENT_NAME]="RestartLogExtentName";
	hmParameterID2Name[MQCACF_MEDIA_LOG_EXTENT_NAME]="MediaLogExtentName";
	hmParameterID2Name[MQCACF_LOG_PATH]="LogPath";
	hmParameterID2Name[MQCACF_COMMAND_MQSC]="CommandMqsc";
	hmParameterID2Name[MQCACF_Q_MGR_CPF]="QMgrCpf";
	hmParameterID2Name[MQCACF_USAGE_LOG_RBA]="UsageLogRba";
	hmParameterID2Name[MQCACF_USAGE_LOG_LRSN]="UsageLogLrsn";
	hmParameterID2Name[MQCACF_COMMAND_SCOPE]="CommandScope";
	hmParameterID2Name[MQCACF_ASID]="Asid";
	hmParameterID2Name[MQCACF_PSB_NAME]="PsbName";
	hmParameterID2Name[MQCACF_PST_ID]="PstId";
	hmParameterID2Name[MQCACF_TASK_NUMBER]="TaskNumber";
	hmParameterID2Name[MQCACF_TRANSACTION_ID]="TransactionId";
	hmParameterID2Name[MQCACF_Q_MGR_UOW_ID]="QMgrUowId";
	hmParameterID2Name[MQCACF_ORIGIN_NAME]="OriginName";
	hmParameterID2Name[MQCACF_ENV_INFO]="EnvInfo";
	hmParameterID2Name[MQCACF_SECURITY_PROFILE]="SecurityProfile";
	hmParameterID2Name[MQCACF_CONFIGURATION_DATE]="ConfigurationDate";
	hmParameterID2Name[MQCACF_CONFIGURATION_TIME]="ConfigurationTime";
	hmParameterID2Name[MQCACF_FROM_CF_STRUC_NAME]="FromCfStrucName";
	hmParameterID2Name[MQCACF_TO_CF_STRUC_NAME]="ToCfStrucName";
	hmParameterID2Name[MQCACF_CF_STRUC_NAMES]="CfStrucNames";
	hmParameterID2Name[MQCACF_FAIL_DATE]="FailDate";
	hmParameterID2Name[MQCACF_FAIL_TIME]="FailTime";
	hmParameterID2Name[MQCACF_BACKUP_DATE]="BackupDate";
	hmParameterID2Name[MQCACF_BACKUP_TIME]="BackupTime";
	hmParameterID2Name[MQCACF_SYSTEM_NAME]="SystemName";
	hmParameterID2Name[MQCACF_CF_STRUC_BACKUP_START]="CfStrucBackupStart";
	hmParameterID2Name[MQCACF_CF_STRUC_BACKUP_END]="CfStrucBackupEnd";
	hmParameterID2Name[MQCACF_CF_STRUC_LOG_Q_MGRS]="CfStrucLogQMgrsMgrs";
	hmParameterID2Name[MQCACF_FROM_STORAGE_CLASS]="FromStorageClass";
	hmParameterID2Name[MQCACF_TO_STORAGE_CLASS]="ToStorageClass";
	hmParameterID2Name[MQCACF_STORAGE_CLASS_NAMES]="StorageClassNames";
	hmParameterID2Name[MQCACF_DSG_NAME]="DsgName";
	hmParameterID2Name[MQCACF_DB2_NAME]="Db2Name";
	hmParameterID2Name[MQCACF_SYSP_CMD_USER_ID]="SyspCmdUserId";
	hmParameterID2Name[MQCACF_SYSP_OTMA_GROUP]="SyspOtmaGroup";
	hmParameterID2Name[MQCACF_SYSP_OTMA_MEMBER]="SyspOtmaMember";
	hmParameterID2Name[MQCACF_SYSP_OTMA_DRU_EXIT]="SyspOtmaDruExit";
	hmParameterID2Name[MQCACF_SYSP_OTMA_TPIPE_PFX]="SyspOtmaTpipePfx";
	hmParameterID2Name[MQCACF_SYSP_ARCHIVE_PFX1]="SyspArchivePfx1";
	hmParameterID2Name[MQCACF_SYSP_ARCHIVE_UNIT1]="SyspArchiveUnit1";
	hmParameterID2Name[MQCACF_SYSP_LOG_CORREL_ID]="SyspLogCorrelId";
	hmParameterID2Name[MQCACF_SYSP_UNIT_VOLSER]="SyspUnitVolser";
	hmParameterID2Name[MQCACF_SYSP_Q_MGR_TIME]="SyspQMgrTime";
	hmParameterID2Name[MQCACF_SYSP_Q_MGR_DATE]="SyspQMgrDate";
	hmParameterID2Name[MQCACF_SYSP_Q_MGR_RBA]="SyspQMgrRba";
	hmParameterID2Name[MQCACF_SYSP_LOG_RBA]="SyspLogRba";
	hmParameterID2Name[MQCACF_SYSP_SERVICE]="SyspService";
	hmParameterID2Name[MQCACF_FROM_LISTENER_NAME]="FromListenerName";
	hmParameterID2Name[MQCACF_TO_LISTENER_NAME]="ToListenerName";
	hmParameterID2Name[MQCACF_FROM_SERVICE_NAME]="FromServiceName";
	hmParameterID2Name[MQCACF_TO_SERVICE_NAME]="ToServiceName";
	hmParameterID2Name[MQCACF_LAST_PUT_DATE]="LastPutDate";
	hmParameterID2Name[MQCACF_LAST_PUT_TIME]="LastPutTime";
	hmParameterID2Name[MQCACF_LAST_GET_DATE]="LastGetDate";
	hmParameterID2Name[MQCACF_LAST_GET_TIME]="LastGetTime";
	hmParameterID2Name[MQCACF_OPERATION_DATE]="OperationDate";
	hmParameterID2Name[MQCACF_OPERATION_TIME]="OperationTime";
	hmParameterID2Name[MQCACF_ACTIVITY_DESC]="ActivityDesc";
	hmParameterID2Name[MQCACF_APPL_IDENTITY_DATA]="ApplIdentityData";
	hmParameterID2Name[MQCACF_APPL_ORIGIN_DATA]="ApplOriginData";
	hmParameterID2Name[MQCACF_PUT_DATE]="PutDate";
	hmParameterID2Name[MQCACF_PUT_TIME]="PutTime";
	hmParameterID2Name[MQCACF_REPLY_TO_Q]="ReplyToQ";
	hmParameterID2Name[MQCACF_REPLY_TO_Q_MGR]="ReplyToQMgr";
	hmParameterID2Name[MQCACF_RESOLVED_Q_NAME]="ResolvedQName";
	hmParameterID2Name[MQCACF_STRUC_ID]="StrucId";
	hmParameterID2Name[MQCACF_VALUE_NAME]="ValueName";
	hmParameterID2Name[MQCACF_SERVICE_START_DATE]="ServiceStartDate";
	hmParameterID2Name[MQCACF_SERVICE_START_TIME]="ServiceStartTime";
	hmParameterID2Name[MQCACF_SYSP_OFFLINE_RBA]="SyspOfflineRba";
	hmParameterID2Name[MQCACF_SYSP_ARCHIVE_PFX2]="SyspArchivePfx2";
	hmParameterID2Name[MQCACF_SYSP_ARCHIVE_UNIT2]="SyspArchiveUnit2";
	hmParameterID2Name[MQCACF_TO_TOPIC_NAME]="ToTopicName";
	hmParameterID2Name[MQCACF_FROM_TOPIC_NAME]="FromTopicName";
	hmParameterID2Name[MQCACF_TOPIC_NAMES]="TopicNames";
	hmParameterID2Name[MQCACF_SUB_NAME]="SubName";
	hmParameterID2Name[MQCACF_DESTINATION_Q_MGR]="DestinationQMgr";
	hmParameterID2Name[MQCACF_DESTINATION]="Destination";
	hmParameterID2Name[MQCACF_SUB_USER_ID]="SubUserId";
	hmParameterID2Name[MQCACF_SUB_USER_DATA]="SubUserData";
	hmParameterID2Name[MQCACF_SUB_SELECTOR]="SubSelector";
	hmParameterID2Name[MQCACF_LAST_PUB_DATE]="LastPubDate";
	hmParameterID2Name[MQCACF_LAST_PUB_TIME]="LastPubTime";
	hmParameterID2Name[MQCACF_FROM_SUB_NAME]="FromSubName";
	hmParameterID2Name[MQCACF_TO_SUB_NAME]="ToSubName";
	hmParameterID2Name[MQCACF_LAST_MSG_TIME]="LastMsgTime";
	hmParameterID2Name[MQCACF_LAST_MSG_DATE]="LastMsgDate";
	hmParameterID2Name[MQCACF_SUBSCRIPTION_POINT]="SubscriptionPoint";
	hmParameterID2Name[MQCACF_FILTER]="Filter";
	hmParameterID2Name[MQCACF_NONE]="None";
	hmParameterID2Name[MQCACF_ADMIN_TOPIC_NAMES]="AdminTopicNames";
	hmParameterID2Name[MQCACF_ROUTING_FINGER_PRINT]="RoutingFingerPrint";
	hmParameterID2Name[MQCACF_APPL_DESC]="ApplDesc";
	hmParameterID2Name[MQCACF_Q_MGR_START_DATE]="QMgrStartDate";
	hmParameterID2Name[MQCACF_Q_MGR_START_TIME]="QMgrStartTime";
	hmParameterID2Name[MQCACF_FROM_COMM_INFO_NAME]="FromCommInfoName";
	hmParameterID2Name[MQCACF_TO_COMM_INFO_NAME]="ToCommInfoName";
	hmParameterID2Name[MQCACF_CF_OFFLOAD_SIZE1]="CfOffloadSize1";
	hmParameterID2Name[MQCACF_CF_OFFLOAD_SIZE2]="CfOffloadSize2";
	hmParameterID2Name[MQCACF_CF_OFFLOAD_SIZE3]="CfOffloadSize3";
	hmParameterID2Name[MQCACF_CF_SMDS_GENERIC_NAME]="CfSmdsGenericName";
	hmParameterID2Name[MQCACF_CF_SMDS]="CfSmds";
	hmParameterID2Name[MQCACF_RECOVERY_DATE]="RecoveryDate";
	hmParameterID2Name[MQCACF_RECOVERY_TIME]="RecoveryTime";
	hmParameterID2Name[MQCACF_CF_SMDSCONN]="CfSmdsconn";
	hmParameterID2Name[MQCACF_CF_STRUC_NAME]="CfStrucName";
	hmParameterID2Name[MQCACF_ALTERNATE_USERID]="AlternateUserid";
	hmParameterID2Name[MQCACF_CHAR_ATTRS]="CharAttrs";
	hmParameterID2Name[MQCACF_DYNAMIC_Q_NAME]="DynamicQName";
	hmParameterID2Name[MQCACF_HOST_NAME]="HostName";
	hmParameterID2Name[MQCACF_MQCB_NAME]="MqcbName";
	hmParameterID2Name[MQCACF_OBJECT_STRING]="ObjectString";
	hmParameterID2Name[MQCACF_RESOLVED_LOCAL_Q_MGR]="ResolvedLocalQMgr";
	hmParameterID2Name[MQCACF_RESOLVED_LOCAL_Q_NAME]="ResolvedLocalQName";
	hmParameterID2Name[MQCACF_RESOLVED_OBJECT_STRING]="ResolvedObjectString";
	hmParameterID2Name[MQCACF_RESOLVED_Q_MGR]="ResolvedQMgr";
	hmParameterID2Name[MQCACF_SELECTION_STRING]="SelectionString";
	hmParameterID2Name[MQCACF_XA_INFO]="XaInfo";
	hmParameterID2Name[MQCACF_APPL_FUNCTION]="ApplFunction";
	hmParameterID2Name[MQCACF_XQH_REMOTE_Q_NAME]="XqhRemoteQName";
	hmParameterID2Name[MQCACF_XQH_REMOTE_Q_MGR]="XqhRemoteQMgr";
	hmParameterID2Name[MQCACF_XQH_PUT_TIME]="XqhPutTime";
	hmParameterID2Name[MQCACF_XQH_PUT_DATE]="XqhPutDate";




	hmParameterID2Name[MQGACF_COMMAND_CONTEXT]="CommandContext";
	hmParameterID2Name[MQBACF_EVENT_ACCOUNTING_TOKEN]="EventAccountingToken";
	hmParameterID2Name[MQGACF_COMMAND_DATA]="CommandData";


	hmParameterID2Name[MQGACF_Q_ACCOUNTING_DATA]="QueueAccounting";
	hmParameterID2Name[MQGACF_Q_STATISTICS_DATA]="QueueStatistics";
	hmParameterID2Name[MQGACF_CHL_STATISTICS_DATA]="ChannelStatistics";

	hmParameterID2Name[MQIAMO_AVG_Q_TIME]="AvgQTime";
	hmParameterID2Name[MQIAMO_Q_MAX_DEPTH]="MinQDepthDetected";
	hmParameterID2Name[MQIAMO_Q_MIN_DEPTH]="MaxQDepthDetected";
	hmParameterID2Name[MQIAMO_MSGS_NOT_QUEUED]="MsgNotQueued";

	hmParameterID2Name[MQBACF_CONNECTION_ID]="ConnectionId";
	hmParameterID2Name[MQCACH_CHANNEL_NAME]="ChannelName";
	hmParameterID2Name[MQCACH_CONNECTION_NAME]="ConnectionName";
	hmParameterID2Name[MQCAMO_CLOSE_DATE]="CloseDate";
	hmParameterID2Name[MQCAMO_CLOSE_TIME]="CloseTime";
	hmParameterID2Name[MQCAMO_CONN_DATE]="ConnDate";
	hmParameterID2Name[MQCAMO_CONN_TIME]="ConnTime";
	hmParameterID2Name[MQCAMO_DISC_DATE]="DiscDate";
	hmParameterID2Name[MQCAMO_DISC_TIME]="DiscTime";
	hmParameterID2Name[MQCAMO_END_DATE]="IntervalEndDate";
	hmParameterID2Name[MQCAMO_END_TIME]="IntervalEndTime";
	hmParameterID2Name[MQCAMO_OPEN_DATE]="OpenDate";
	hmParameterID2Name[MQCAMO_OPEN_TIME]="OpenTime";
	hmParameterID2Name[MQCAMO_START_DATE]="IntervalStartDate";
	hmParameterID2Name[MQCAMO_START_TIME]="IntervalStartTime";
	hmParameterID2Name[MQGACF_CHL_STATISTICS_DATA]="ChlStatisticsData";
	hmParameterID2Name[MQGACF_Q_ACCOUNTING_DATA]="QAccountingData";
	hmParameterID2Name[MQIACH_CHANNEL_TYPE]="ChannelType";
	hmParameterID2Name[MQIAMO64_BROWSE_BYTES]="BrowseBytes";
	hmParameterID2Name[MQIAMO64_BYTES]="TotalBytes";
	hmParameterID2Name[MQIAMO64_GET_BYTES]="GetBytes";
	hmParameterID2Name[MQIAMO64_PUBLISH_MSG_BYTES]="PublishMsgBytes";
	hmParameterID2Name[MQIAMO_PUBLISH_MSG_COUNT]="PublishMsgCount";
	hmParameterID2Name[MQIAMO64_PUT_BYTES]="PutBytes";
	hmParameterID2Name[MQIAMO64_Q_TIME_AVG]="TimeOnQAvg";
	hmParameterID2Name[MQIAMO64_Q_TIME_MAX]="TimeOnQMax";
	hmParameterID2Name[MQIAMO64_Q_TIME_MIN]="TimeOnQMin";
	hmParameterID2Name[MQIAMO64_TOPIC_PUT_BYTES]="PutTopicBytes";
	hmParameterID2Name[MQIAMO_AVG_BATCH_SIZE]="AverageBatchSize";
	hmParameterID2Name[MQIAMO_BACKOUTS]="BackCount";
	hmParameterID2Name[MQIAMO_BROWSE_MAX_BYTES]="BrowseMaxBytes";
	hmParameterID2Name[MQIAMO_BROWSE_MIN_BYTES]="BrowseMinBytes";
	hmParameterID2Name[MQIAMO_BROWSES]="BrowseCount";
	hmParameterID2Name[MQIAMO_BROWSES_FAILED]="BrowseFailCount";
	hmParameterID2Name[MQIAMO_CBS]="CBCount";
	hmParameterID2Name[MQIAMO_CBS_FAILED]="CBFailCount";
	hmParameterID2Name[MQIAMO_CLOSES]="CloseCount";
	hmParameterID2Name[MQIAMO_CLOSES_FAILED]="CloseFailCount";
	hmParameterID2Name[MQIAMO_COMMITS]="CommitCount";
	hmParameterID2Name[MQIAMO_COMMITS_FAILED]="CommitFailCount";
	hmParameterID2Name[MQIAMO_CONNS]="ConnCount";
	hmParameterID2Name[MQIAMO_CONNS_FAILED]="ConnFailCount";
	hmParameterID2Name[MQIAMO_CONNS_MAX]="ConnsMax";
	hmParameterID2Name[MQIAMO_CTLS]="CtlCount";
	hmParameterID2Name[MQIAMO_CTLS_FAILED]="CtlFailCount";
	hmParameterID2Name[MQIAMO_DISCS]="DiscCount";
	hmParameterID2Name[MQIAMO_DISC_TYPE]="DiscType";
	hmParameterID2Name[MQIAMO_EXIT_TIME_AVG]="ExitTimeAvg";
	hmParameterID2Name[MQIAMO_EXIT_TIME_MAX]="ExitTimeMax";
	hmParameterID2Name[MQIAMO_EXIT_TIME_MIN]="ExitTimeMin";
	hmParameterID2Name[MQIAMO_FULL_BATCHES]="FullBatchCount";
	hmParameterID2Name[MQIAMO_GENERATED_MSGS]="GeneratedMsgCount";
	hmParameterID2Name[MQIAMO_GET_MAX_BYTES]="GetMaxBytes";
	hmParameterID2Name[MQIAMO_GET_MIN_BYTES]="GetMinBytes";
	hmParameterID2Name[MQIAMO_GETS_FAILED]="GetFailCount";
	hmParameterID2Name[MQIAMO_GETS]="GetCount";
	hmParameterID2Name[MQIAMO_INCOMPLETE_BATCHES]="IncmplBatchCount";
	hmParameterID2Name[MQIAMO_INQS_FAILED]="InqFailCount";
	hmParameterID2Name[MQIAMO_INQS]="InqCount";
	hmParameterID2Name[MQIAMO_MSGS_EXPIRED]="ExpiredMsgCount";
	hmParameterID2Name[MQIAMO_MSGS]="MsgCount";
	hmParameterID2Name[MQIAMO_MSGS_PURGED]="PurgeCount";
	hmParameterID2Name[MQIAMO_NET_TIME_AVG]="NetTimeAvg";
	hmParameterID2Name[MQIAMO_NET_TIME_MAX]="NetTimeMax";
	hmParameterID2Name[MQIAMO_NET_TIME_MIN]="NetTimeMin";
	hmParameterID2Name[MQIAMO_OBJECT_COUNT]="ObjectCount";
	hmParameterID2Name[MQIAMO_OPENS_FAILED]="OpenFailCount";
	hmParameterID2Name[MQIAMO_OPENS]="OpenCount";
	hmParameterID2Name[MQIAMO_PUT1S_FAILED]="Put1FailCount";
	hmParameterID2Name[MQIAMO_PUT1S]="Put1Count";
	hmParameterID2Name[MQIAMO_PUT_MAX_BYTES]="PutMaxBytes";
	hmParameterID2Name[MQIAMO_PUT_MIN_BYTES]="PutMinBytes";
	hmParameterID2Name[MQIAMO_PUT_RETRIES]="PutRetryCount";
	hmParameterID2Name[MQIAMO_PUTS_FAILED]="PutFailCount";
	hmParameterID2Name[MQIAMO_PUTS]="PutCount";
	hmParameterID2Name[MQIAMO_SETS_FAILED]="SetFailCount";
	hmParameterID2Name[MQIAMO_SETS]="SetCount";
	hmParameterID2Name[MQIAMO_STATS_FAILED]="StatFailCount";
	hmParameterID2Name[MQIAMO_STATS]="StatCount";
	hmParameterID2Name[MQIAMO_SUB_DUR_HIGHWATER]="SubCountDurHighWater";
	hmParameterID2Name[MQIAMO_SUB_DUR_LOWWATER]="SubCountDurLowWater";
	hmParameterID2Name[MQIAMO_SUB_NDUR_HIGHWATER]="SubCountNDurHighWater";
	hmParameterID2Name[MQIAMO_SUB_NDUR_LOWWATER]="SubCountNDurLowWater";
	hmParameterID2Name[MQIAMO_SUBRQS_FAILED]="SubRqFailCount";
	hmParameterID2Name[MQIAMO_SUBRQS]="SubRqCount";
	hmParameterID2Name[MQIAMO_SUBS_DUR]="SubCountDur";
	hmParameterID2Name[MQIAMO_SUBS_FAILED]="SubFailCount";
	hmParameterID2Name[MQIAMO_SUBS_NDUR]="SubCountNDur";
	hmParameterID2Name[MQIAMO_TOPIC_PUT1S_FAILED]="Put1TopicFailCount";
	hmParameterID2Name[MQIAMO_TOPIC_PUT1S]="Put1TopicCount";
	hmParameterID2Name[MQIAMO_TOPIC_PUTS_FAILED]="PutTopicFailCount";
	hmParameterID2Name[MQIAMO_TOPIC_PUTS]="PutTopicCount";
	hmParameterID2Name[MQIAMO_UNSUBS_DUR]="UnsubCountDur";
	hmParameterID2Name[MQIAMO_UNSUBS_FAILED]="UnsubFailCount";
	hmParameterID2Name[MQIAMO_UNSUBS_NDUR]="UnsubCountNDur";


	for(HashMap::const_iterator it=hmParameterID2Name.begin();
		it != hmParameterID2Name.end(); it++){
		hmParameterName2ID[it->second]=it->first;
		IAS_LOG(false,it->first<<"="<<it->second);
	}

}
/*************************************************************************/
void Dictionary::initializeMQSCNames(){
	IAS_TRACER;
	hmMQSCNames[MQCMD_BACKUP_CF_STRUC]="BACKUP_CF_STRUC";
	hmMQSCNames[MQCMD_CHANGE_AUTH_INFO]="CHANGE_AUTH_INFO";
	hmMQSCNames[MQCMD_CHANGE_BUFFER_POOL]="CHANGE_BUFFER_POOL";
	hmMQSCNames[MQCMD_CHANGE_CF_STRUC]="CHANGE_CF_STRUC";
	hmMQSCNames[MQCMD_CHANGE_CHANNEL]="CHANGE_CHANNEL";
	hmMQSCNames[MQCMD_CHANGE_COMM_INFO]="CHANGE_COMM_INFO";
	hmMQSCNames[MQCMD_CHANGE_LISTENER]="CHANGE_LISTENER";
	hmMQSCNames[MQCMD_CHANGE_NAMELIST]="CHANGE_NAMELIST";
	hmMQSCNames[MQCMD_CHANGE_PAGE_SET]="CHANGE_PAGE_SET";
	hmMQSCNames[MQCMD_CHANGE_PROCESS]="CHANGE_PROCESS";
	hmMQSCNames[MQCMD_CHANGE_Q]="CHANGE_Q";
	hmMQSCNames[MQCMD_CHANGE_Q_MGR]="CHANGE_Q_MGR";
	hmMQSCNames[MQCMD_CHANGE_SECURITY]="CHANGE_SECURITY";
	hmMQSCNames[MQCMD_CHANGE_SERVICE]="CHANGE_SERVICE";
	hmMQSCNames[MQCMD_CHANGE_STG_CLASS]="CHANGE_STG_CLASS";
	hmMQSCNames[MQCMD_CHANGE_SUBSCRIPTION]="CHANGE_SUBSCRIPTION";
	hmMQSCNames[MQCMD_CHANGE_TOPIC]="CHANGE_TOPIC";
	hmMQSCNames[MQCMD_CHANGE_TRACE]="CHANGE_TRACE";
	hmMQSCNames[MQCMD_CLEAR_Q]="CLEAR_Q";
	hmMQSCNames[MQCMD_CLEAR_TOPIC_STRING]="CLEAR_TOPIC_STRING";
	hmMQSCNames[MQCMD_CREATE_AUTH_INFO]="CREATE_AUTH_INFO";
	hmMQSCNames[MQCMD_CREATE_BUFFER_POOL]="CREATE_BUFFER_POOL";
	hmMQSCNames[MQCMD_CREATE_CF_STRUC]="CREATE_CF_STRUC";
	hmMQSCNames[MQCMD_CREATE_CHANNEL]="CREATE_CHANNEL";
	hmMQSCNames[MQCMD_CREATE_COMM_INFO]="CREATE_COMM_INFO";
	hmMQSCNames[MQCMD_CREATE_LISTENER]="CREATE_LISTENER";
	hmMQSCNames[MQCMD_CREATE_NAMELIST]="CREATE_NAMELIST";
	hmMQSCNames[MQCMD_CREATE_PAGE_SET]="CREATE_PAGE_SET";
	hmMQSCNames[MQCMD_CREATE_PROCESS]="CREATE_PROCESS";
	hmMQSCNames[MQCMD_CREATE_Q]="CREATE_Q";
	hmMQSCNames[MQCMD_CREATE_SERVICE]="CREATE_SERVICE";
	hmMQSCNames[MQCMD_CREATE_STG_CLASS]="CREATE_STG_CLASS";
	hmMQSCNames[MQCMD_CREATE_SUBSCRIPTION]="CREATE_SUBSCRIPTION";
	hmMQSCNames[MQCMD_CREATE_TOPIC]="CREATE_TOPIC";
	hmMQSCNames[MQCMD_DELETE_AUTH_INFO]="DELETE_AUTH_INFO";
	hmMQSCNames[MQCMD_DELETE_CF_STRUC]="DELETE_CF_STRUC";
	hmMQSCNames[MQCMD_DELETE_CHANNEL]="DELETE_CHANNEL";
	hmMQSCNames[MQCMD_DELETE_COMM_INFO]="DELETE_COMM_INFO";
	hmMQSCNames[MQCMD_DELETE_LISTENER]="DELETE_LISTENER";
	hmMQSCNames[MQCMD_DELETE_NAMELIST]="DELETE_NAMELIST";
	hmMQSCNames[MQCMD_DELETE_PAGE_SET]="DELETE_PAGE_SET";
	hmMQSCNames[MQCMD_DELETE_PROCESS]="DELETE_PROCESS";
	hmMQSCNames[MQCMD_DELETE_Q]="DELETE_Q";
	hmMQSCNames[MQCMD_DELETE_SERVICE]="DELETE_SERVICE";
	hmMQSCNames[MQCMD_DELETE_STG_CLASS]="DELETE_STG_CLASS";
	hmMQSCNames[MQCMD_DELETE_SUBSCRIPTION]="DELETE_SUBSCRIPTION";
	hmMQSCNames[MQCMD_DELETE_TOPIC]="DELETE_TOPIC";
	hmMQSCNames[MQCMD_INQUIRE_ARCHIVE]="INQUIRE_ARCHIVE";
	hmMQSCNames[MQCMD_INQUIRE_AUTH_INFO]="INQUIRE_AUTH_INFO";
	hmMQSCNames[MQCMD_INQUIRE_CF_STRUC]="INQUIRE_CF_STRUC";
	hmMQSCNames[MQCMD_INQUIRE_CF_STRUC_STATUS]="INQUIRE_CF_STRUC_STATUS";
	hmMQSCNames[MQCMD_INQUIRE_CHANNEL]="INQUIRE_CHANNEL";
	hmMQSCNames[MQCMD_INQUIRE_CHANNEL_INIT]="INQUIRE_CHANNEL_INIT";
	hmMQSCNames[MQCMD_INQUIRE_CHANNEL_STATUS]="INQUIRE_CHANNEL_STATUS";
	hmMQSCNames[MQCMD_INQUIRE_CHLAUTH_RECS]="INQUIRE_CHLAUTH_RECS";
	hmMQSCNames[MQCMD_INQUIRE_CLUSTER_Q_MGR]="INQUIRE_CLUSTER_Q_MGR";
	hmMQSCNames[MQCMD_INQUIRE_CMD_SERVER]="INQUIRE_CMD_SERVER";
	hmMQSCNames[MQCMD_INQUIRE_COMM_INFO]="INQUIRE_COMM_INFO";
	hmMQSCNames[MQCMD_INQUIRE_CONNECTION]="INQUIRE_CONNECTION";
	hmMQSCNames[MQCMD_INQUIRE_LISTENER]="INQUIRE_LISTENER";
	hmMQSCNames[MQCMD_INQUIRE_LOG]="INQUIRE_LOG";
	hmMQSCNames[MQCMD_INQUIRE_NAMELIST]="INQUIRE_NAMELIST";
	hmMQSCNames[MQCMD_INQUIRE_PROCESS]="INQUIRE_PROCESS";
	hmMQSCNames[MQCMD_INQUIRE_PUBSUB_STATUS]="INQUIRE_PUBSUB_STATUS";
	hmMQSCNames[MQCMD_INQUIRE_Q]="INQUIRE_Q";
	hmMQSCNames[MQCMD_INQUIRE_Q_MGR]="INQUIRE_Q_MGR";
	hmMQSCNames[MQCMD_INQUIRE_QSG]="INQUIRE_QSG";
	hmMQSCNames[MQCMD_INQUIRE_Q_STATUS]="INQUIRE_Q_STATUS";
	hmMQSCNames[MQCMD_INQUIRE_SECURITY]="INQUIRE_SECURITY";
	hmMQSCNames[MQCMD_INQUIRE_SERVICE]="INQUIRE_SERVICE";
	hmMQSCNames[MQCMD_INQUIRE_STG_CLASS]="INQUIRE_STG_CLASS";
	hmMQSCNames[MQCMD_INQUIRE_SUBSCRIPTION]="INQUIRE_SUBSCRIPTION";
	hmMQSCNames[MQCMD_INQUIRE_SUB_STATUS]="INQUIRE_SUB_STATUS";
	hmMQSCNames[MQCMD_INQUIRE_SYSTEM]="INQUIRE_SYSTEM";
	hmMQSCNames[MQCMD_INQUIRE_THREAD]="INQUIRE_THREAD";
	hmMQSCNames[MQCMD_INQUIRE_TOPIC]="INQUIRE_TOPIC";
	hmMQSCNames[MQCMD_INQUIRE_TOPIC_STATUS]="INQUIRE_TOPIC_STATUS";
	hmMQSCNames[MQCMD_INQUIRE_TRACE]="INQUIRE_TRACE";
	hmMQSCNames[MQCMD_INQUIRE_USAGE]="INQUIRE_USAGE";
	hmMQSCNames[MQCMD_MOVE_Q]="MOVE_Q";
	hmMQSCNames[MQCMD_PING_CHANNEL]="PING_CHANNEL";
	hmMQSCNames[MQCMD_RECOVER_BSDS]="RECOVER_BSDS";
	hmMQSCNames[MQCMD_RECOVER_CF_STRUC]="RECOVER_CF_STRUC";
	hmMQSCNames[MQCMD_REFRESH_CLUSTER]="REFRESH_CLUSTER";
	hmMQSCNames[MQCMD_REFRESH_Q_MGR]="REFRESH_Q_MGR";
	hmMQSCNames[MQCMD_REFRESH_SECURITY]="REFRESH_SECURITY";
	hmMQSCNames[MQCMD_RESET_CHANNEL]="RESET_CHANNEL";
	hmMQSCNames[MQCMD_RESET_CLUSTER]="RESET_CLUSTER";
	hmMQSCNames[MQCMD_RESET_Q_MGR]="RESET_Q_MGR";
	hmMQSCNames[MQCMD_RESET_Q_STATS]="RESET_Q_STATS";
	hmMQSCNames[MQCMD_RESET_TPIPE]="RESET_TPIPE";
	hmMQSCNames[MQCMD_RESOLVE_CHANNEL]="RESOLVE_CHANNEL";
	hmMQSCNames[MQCMD_RESOLVE_INDOUBT]="RESOLVE_INDOUBT";
	hmMQSCNames[MQCMD_RESUME_Q_MGR]="RESUME_Q_MGR";
	hmMQSCNames[MQCMD_RESUME_Q_MGR_CLUSTER]="RESUME_Q_MGR_CLUSTER";
	hmMQSCNames[MQCMD_REVERIFY_SECURITY]="REVERIFY_SECURITY";
	hmMQSCNames[MQCMD_SET_ARCHIVE]="SET_ARCHIVE";
	hmMQSCNames[MQCMD_SET_CHLAUTH_REC]="SET_CHLAUTH_REC";
	hmMQSCNames[MQCMD_SET_LOG]="SET_LOG";
	hmMQSCNames[MQCMD_SET_SYSTEM]="SET_SYSTEM";
	hmMQSCNames[MQCMD_START_CHANNEL]="START_CHANNEL";
	hmMQSCNames[MQCMD_START_CHANNEL_INIT]="START_CHANNEL_INIT";
	hmMQSCNames[MQCMD_START_CHANNEL_LISTENER]="START_CHANNEL_LISTENER";
	hmMQSCNames[MQCMD_START_CMD_SERVER]="START_CMD_SERVER";
	hmMQSCNames[MQCMD_START_SERVICE]="START_SERVICE";
	hmMQSCNames[MQCMD_START_TRACE]="START_TRACE";
	hmMQSCNames[MQCMD_STOP_CHANNEL]="STOP_CHANNEL";
	hmMQSCNames[MQCMD_STOP_CHANNEL_INIT]="STOP_CHANNEL_INIT";
	hmMQSCNames[MQCMD_STOP_CHANNEL_LISTENER]="STOP_CHANNEL_LISTENER";
	hmMQSCNames[MQCMD_STOP_CMD_SERVER]="STOP_CMD_SERVER";
	hmMQSCNames[MQCMD_STOP_CONNECTION]="STOP_CONNECTION";
	hmMQSCNames[MQCMD_STOP_SERVICE]="STOP_SERVICE";
	hmMQSCNames[MQCMD_STOP_TRACE]="STOP_TRACE";
	hmMQSCNames[MQCMD_SUSPEND_Q_MGR]="SUSPEND_Q_MGR";
	hmMQSCNames[MQCMD_SUSPEND_Q_MGR_CLUSTER]="SUSPEND_Q_MGR_CLUSTER";


}
/*************************************************************************/
void Dictionary::initializeCompCodeName(){
	IAS_TRACER;

	hmCompCodeName[MQCC_OK]         = "OK";
	hmCompCodeName[MQCC_WARNING]    = "WARNING";
	hmCompCodeName[MQCC_FAILED]     = "FAILED";
	hmCompCodeName[MQCC_UNKNOWN]    = "UNKNOWN";

}
/*************************************************************************/
void Dictionary::initializeReasonName(){
	IAS_TRACER;


	hmReasonName[MQRC_NONE]="None";
	hmReasonName[MQRC_APPL_FIRST]="ApplFirst";
	hmReasonName[MQRC_APPL_LAST]="ApplLast";
	hmReasonName[MQRC_ALIAS_BASE_Q_TYPE_ERROR]="AliasBaseQTypeErrorError";
	hmReasonName[MQRC_ALREADY_CONNECTED]="AlreadyConnected";
	hmReasonName[MQRC_BACKED_OUT]="BackedOut";
	hmReasonName[MQRC_BUFFER_ERROR]="BufferError";
	hmReasonName[MQRC_BUFFER_LENGTH_ERROR]="BufferLengthError";
	hmReasonName[MQRC_CHAR_ATTR_LENGTH_ERROR]="CharAttrLengthError";
	hmReasonName[MQRC_CHAR_ATTRS_ERROR]="CharAttrsError";
	hmReasonName[MQRC_CHAR_ATTRS_TOO_SHORT]="CharAttrsTooShort";
	hmReasonName[MQRC_CONNECTION_BROKEN]="ConnectionBroken";
	hmReasonName[MQRC_DATA_LENGTH_ERROR]="DataLengthError";
	hmReasonName[MQRC_DYNAMIC_Q_NAME_ERROR]="DynamicQNameError";
	hmReasonName[MQRC_ENVIRONMENT_ERROR]="EnvironmentError";
	hmReasonName[MQRC_EXPIRY_ERROR]="ExpiryError";
	hmReasonName[MQRC_FEEDBACK_ERROR]="FeedbackError";
	hmReasonName[MQRC_GET_INHIBITED]="GetInhibited";
	hmReasonName[MQRC_HANDLE_NOT_AVAILABLE]="HandleNotAvailable";
	hmReasonName[MQRC_HCONN_ERROR]="HconnError";
	hmReasonName[MQRC_HOBJ_ERROR]="HobjError";
	hmReasonName[MQRC_INHIBIT_VALUE_ERROR]="InhibitValueError";
	hmReasonName[MQRC_INT_ATTR_COUNT_ERROR]="IntAttrCountError";
	hmReasonName[MQRC_INT_ATTR_COUNT_TOO_SMALL]="IntAttrCountTooSmallSmall";
	hmReasonName[MQRC_INT_ATTRS_ARRAY_ERROR]="IntAttrsArrayError";
	hmReasonName[MQRC_SYNCPOINT_LIMIT_REACHED]="SyncpointLimitReached";
	hmReasonName[MQRC_MAX_CONNS_LIMIT_REACHED]="MaxConnsLimitReached";
	hmReasonName[MQRC_MD_ERROR]="MdError";
	hmReasonName[MQRC_MISSING_REPLY_TO_Q]="MissingReplyToQ";
	hmReasonName[MQRC_MSG_TYPE_ERROR]="MsgTypeError";
	hmReasonName[MQRC_MSG_TOO_BIG_FOR_Q]="MsgTooBigForQQ";
	hmReasonName[MQRC_MSG_TOO_BIG_FOR_Q_MGR]="MsgTooBigForQQ";
	hmReasonName[MQRC_NO_MSG_AVAILABLE]="NoMsgAvailable";
	hmReasonName[MQRC_NO_MSG_UNDER_CURSOR]="NoMsgUnderCursor";
	hmReasonName[MQRC_NOT_AUTHORIZED]="NotAuthorized";
	hmReasonName[MQRC_NOT_OPEN_FOR_BROWSE]="NotOpenForBrowse";
	hmReasonName[MQRC_NOT_OPEN_FOR_INPUT]="NotOpenForInput";
	hmReasonName[MQRC_NOT_OPEN_FOR_INQUIRE]="NotOpenForInquire";
	hmReasonName[MQRC_NOT_OPEN_FOR_OUTPUT]="NotOpenForOutput";
	hmReasonName[MQRC_NOT_OPEN_FOR_SET]="NotOpenForSet";
	hmReasonName[MQRC_OBJECT_CHANGED]="ObjectChanged";
	hmReasonName[MQRC_OBJECT_IN_USE]="ObjectInUse";
	hmReasonName[MQRC_OBJECT_TYPE_ERROR]="ObjectTypeError";
	hmReasonName[MQRC_OD_ERROR]="OdError";
	hmReasonName[MQRC_OPTION_NOT_VALID_FOR_TYPE]="OptionNotValidForTypeType";
	hmReasonName[MQRC_OPTIONS_ERROR]="OptionsError";
	hmReasonName[MQRC_PERSISTENCE_ERROR]="PersistenceError";
	hmReasonName[MQRC_PERSISTENT_NOT_ALLOWED]="PersistentNotAllowed";
	hmReasonName[MQRC_PRIORITY_EXCEEDS_MAXIMUM]="PriorityExceedsMaximum";
	hmReasonName[MQRC_PRIORITY_ERROR]="PriorityError";
	hmReasonName[MQRC_PUT_INHIBITED]="PutInhibited";
	hmReasonName[MQRC_Q_DELETED]="QDeleted";
	hmReasonName[MQRC_Q_FULL]="QFull";
	hmReasonName[MQRC_Q_NOT_EMPTY]="QNotEmpty";
	hmReasonName[MQRC_Q_SPACE_NOT_AVAILABLE]="QSpaceNotAvailable";
	hmReasonName[MQRC_Q_TYPE_ERROR]="QTypeError";
	hmReasonName[MQRC_Q_MGR_NAME_ERROR]="QMgrNameError";
	hmReasonName[MQRC_Q_MGR_NOT_AVAILABLE]="QMgrNotAvailable";
	hmReasonName[MQRC_REPORT_OPTIONS_ERROR]="ReportOptionsError";
	hmReasonName[MQRC_SECOND_MARK_NOT_ALLOWED]="SecondMarkNotAllowed";
	hmReasonName[MQRC_SECURITY_ERROR]="SecurityError";
	hmReasonName[MQRC_SELECTOR_COUNT_ERROR]="SelectorCountError";
	hmReasonName[MQRC_SELECTOR_LIMIT_EXCEEDED]="SelectorLimitExceeded";
	hmReasonName[MQRC_SELECTOR_ERROR]="SelectorError";
	hmReasonName[MQRC_SELECTOR_NOT_FOR_TYPE]="SelectorNotForType";
	hmReasonName[MQRC_SIGNAL_OUTSTANDING]="SignalOutstanding";
	hmReasonName[MQRC_SIGNAL_REQUEST_ACCEPTED]="SignalRequestAccepted";
	hmReasonName[MQRC_STORAGE_NOT_AVAILABLE]="StorageNotAvailable";
	hmReasonName[MQRC_SYNCPOINT_NOT_AVAILABLE]="SyncpointNotAvailable";
	hmReasonName[MQRC_TRIGGER_CONTROL_ERROR]="TriggerControlError";
	hmReasonName[MQRC_TRIGGER_DEPTH_ERROR]="TriggerDepthError";
	hmReasonName[MQRC_TRIGGER_MSG_PRIORITY_ERR]="TriggerMsgPriorityErr";
	hmReasonName[MQRC_TRIGGER_TYPE_ERROR]="TriggerTypeError";
	hmReasonName[MQRC_TRUNCATED_MSG_ACCEPTED]="TruncatedMsgAccepted";
	hmReasonName[MQRC_TRUNCATED_MSG_FAILED]="TruncatedMsgFailed";
	hmReasonName[MQRC_UNKNOWN_ALIAS_BASE_Q]="UnknownAliasBaseQ";
	hmReasonName[MQRC_UNKNOWN_OBJECT_NAME]="UnknownObjectName";
	hmReasonName[MQRC_UNKNOWN_OBJECT_Q_MGR]="UnknownObjectQMgr";
	hmReasonName[MQRC_UNKNOWN_REMOTE_Q_MGR]="UnknownRemoteQMgr";
	hmReasonName[MQRC_WAIT_INTERVAL_ERROR]="WaitIntervalError";
	hmReasonName[MQRC_XMIT_Q_TYPE_ERROR]="XmitQTypeError";
	hmReasonName[MQRC_XMIT_Q_USAGE_ERROR]="XmitQUsageError";
	hmReasonName[MQRC_NOT_OPEN_FOR_PASS_ALL]="NotOpenForPassAllAll";
	hmReasonName[MQRC_NOT_OPEN_FOR_PASS_IDENT]="NotOpenForPassIdentIdent";
	hmReasonName[MQRC_NOT_OPEN_FOR_SET_ALL]="NotOpenForSetAllAll";
	hmReasonName[MQRC_NOT_OPEN_FOR_SET_IDENT]="NotOpenForSetIdentIdent";
	hmReasonName[MQRC_CONTEXT_HANDLE_ERROR]="ContextHandleError";
	hmReasonName[MQRC_CONTEXT_NOT_AVAILABLE]="ContextNotAvailable";
	hmReasonName[MQRC_SIGNAL1_ERROR]="Signal1Error";
	hmReasonName[MQRC_OBJECT_ALREADY_EXISTS]="ObjectAlreadyExists";
	hmReasonName[MQRC_OBJECT_DAMAGED]="ObjectDamaged";
	hmReasonName[MQRC_RESOURCE_PROBLEM]="ResourceProblem";
	hmReasonName[MQRC_ANOTHER_Q_MGR_CONNECTED]="AnotherQMgrConnected";
	hmReasonName[MQRC_UNKNOWN_REPORT_OPTION]="UnknownReportOption";
	hmReasonName[MQRC_STORAGE_CLASS_ERROR]="StorageClassError";
	hmReasonName[MQRC_COD_NOT_VALID_FOR_XCF_Q]="CodNotValidForXcfXcf";
	hmReasonName[MQRC_XWAIT_CANCELED]="XwaitCanceled";
	hmReasonName[MQRC_XWAIT_ERROR]="XwaitError";
	hmReasonName[MQRC_SUPPRESSED_BY_EXIT]="SuppressedByExit";
	hmReasonName[MQRC_FORMAT_ERROR]="FormatError";
	hmReasonName[MQRC_SOURCE_CCSID_ERROR]="SourceCcsidError";
	hmReasonName[MQRC_SOURCE_INTEGER_ENC_ERROR]="SourceIntegerEncError";
	hmReasonName[MQRC_SOURCE_DECIMAL_ENC_ERROR]="SourceDecimalEncError";
	hmReasonName[MQRC_SOURCE_FLOAT_ENC_ERROR]="SourceFloatEncError";
	hmReasonName[MQRC_TARGET_CCSID_ERROR]="TargetCcsidError";
	hmReasonName[MQRC_TARGET_INTEGER_ENC_ERROR]="TargetIntegerEncError";
	hmReasonName[MQRC_TARGET_DECIMAL_ENC_ERROR]="TargetDecimalEncError";
	hmReasonName[MQRC_TARGET_FLOAT_ENC_ERROR]="TargetFloatEncError";
	hmReasonName[MQRC_NOT_CONVERTED]="NotConverted";
	hmReasonName[MQRC_CONVERTED_MSG_TOO_BIG]="ConvertedMsgTooBig";
	hmReasonName[MQRC_TRUNCATED]="Truncated";
	hmReasonName[MQRC_NO_EXTERNAL_PARTICIPANTS]="NoExternalParticipants";
	hmReasonName[MQRC_PARTICIPANT_NOT_AVAILABLE]="ParticipantNotAvailable";
	hmReasonName[MQRC_OUTCOME_MIXED]="OutcomeMixed";
	hmReasonName[MQRC_OUTCOME_PENDING]="OutcomePending";
	hmReasonName[MQRC_BRIDGE_STARTED]="BridgeStarted";
	hmReasonName[MQRC_BRIDGE_STOPPED]="BridgeStopped";
	hmReasonName[MQRC_ADAPTER_STORAGE_SHORTAGE]="AdapterStorageShortage";
	hmReasonName[MQRC_UOW_IN_PROGRESS]="UowInProgress";
	hmReasonName[MQRC_ADAPTER_CONN_LOAD_ERROR]="AdapterConnLoadError";
	hmReasonName[MQRC_ADAPTER_SERV_LOAD_ERROR]="AdapterServLoadError";
	hmReasonName[MQRC_ADAPTER_DEFS_ERROR]="AdapterDefsError";
	hmReasonName[MQRC_ADAPTER_DEFS_LOAD_ERROR]="AdapterDefsLoadError";
	hmReasonName[MQRC_ADAPTER_CONV_LOAD_ERROR]="AdapterConvLoadError";
	hmReasonName[MQRC_BO_ERROR]="BoError";
	hmReasonName[MQRC_DH_ERROR]="DhError";
	hmReasonName[MQRC_MULTIPLE_REASONS]="MultipleReasons";
	hmReasonName[MQRC_OPEN_FAILED]="OpenFailed";
	hmReasonName[MQRC_ADAPTER_DISC_LOAD_ERROR]="AdapterDiscLoadError";
	hmReasonName[MQRC_CNO_ERROR]="CnoError";
	hmReasonName[MQRC_CICS_WAIT_FAILED]="CicsWaitFailed";
	hmReasonName[MQRC_DLH_ERROR]="DlhError";
	hmReasonName[MQRC_HEADER_ERROR]="HeaderError";
	hmReasonName[MQRC_SOURCE_LENGTH_ERROR]="SourceLengthError";
	hmReasonName[MQRC_TARGET_LENGTH_ERROR]="TargetLengthError";
	hmReasonName[MQRC_SOURCE_BUFFER_ERROR]="SourceBufferError";
	hmReasonName[MQRC_TARGET_BUFFER_ERROR]="TargetBufferError";
	hmReasonName[MQRC_IIH_ERROR]="IihError";
	hmReasonName[MQRC_PCF_ERROR]="PcfError";
	hmReasonName[MQRC_DBCS_ERROR]="DbcsError";
	hmReasonName[MQRC_OBJECT_NAME_ERROR]="ObjectNameError";
	hmReasonName[MQRC_OBJECT_Q_MGR_NAME_ERROR]="ObjectQMgrNameErrorError";
	hmReasonName[MQRC_RECS_PRESENT_ERROR]="RecsPresentError";
	hmReasonName[MQRC_OBJECT_RECORDS_ERROR]="ObjectRecordsError";
	hmReasonName[MQRC_RESPONSE_RECORDS_ERROR]="ResponseRecordsError";
	hmReasonName[MQRC_ASID_MISMATCH]="AsidMismatch";
	hmReasonName[MQRC_PMO_RECORD_FLAGS_ERROR]="PmoRecordFlagsError";
	hmReasonName[MQRC_PUT_MSG_RECORDS_ERROR]="PutMsgRecordsError";
	hmReasonName[MQRC_CONN_ID_IN_USE]="ConnIdInUse";
	hmReasonName[MQRC_Q_MGR_QUIESCING]="QMgrQuiescing";
	hmReasonName[MQRC_Q_MGR_STOPPING]="QMgrStopping";
	hmReasonName[MQRC_DUPLICATE_RECOV_COORD]="DuplicateRecovCoord";
	hmReasonName[MQRC_PMO_ERROR]="PmoError";
	hmReasonName[MQRC_API_EXIT_NOT_FOUND]="ApiExitNotFound";
	hmReasonName[MQRC_API_EXIT_LOAD_ERROR]="ApiExitLoadError";
	hmReasonName[MQRC_REMOTE_Q_NAME_ERROR]="RemoteQNameError";
	hmReasonName[MQRC_INCONSISTENT_PERSISTENCE]="InconsistentPersistence";
	hmReasonName[MQRC_GMO_ERROR]="GmoError";
	hmReasonName[MQRC_CICS_BRIDGE_RESTRICTION]="CicsBridgeRestriction";
	hmReasonName[MQRC_STOPPED_BY_CLUSTER_EXIT]="StoppedByClusterExit";
	hmReasonName[MQRC_CLUSTER_RESOLUTION_ERROR]="ClusterResolutionError";
	hmReasonName[MQRC_CONVERTED_STRING_TOO_BIG]="ConvertedStringTooBig";
	hmReasonName[MQRC_TMC_ERROR]="TmcError";
	hmReasonName[MQRC_PAGESET_FULL]="PagesetFull";
	hmReasonName[MQRC_STORAGE_MEDIUM_FULL]="StorageMediumFull";
	hmReasonName[MQRC_PAGESET_ERROR]="PagesetError";
	hmReasonName[MQRC_NAME_NOT_VALID_FOR_TYPE]="NameNotValidForTypeType";
	hmReasonName[MQRC_UNEXPECTED_ERROR]="UnexpectedError";
	hmReasonName[MQRC_UNKNOWN_XMIT_Q]="UnknownXmitQ";
	hmReasonName[MQRC_UNKNOWN_DEF_XMIT_Q]="UnknownDefXmitQ";
	hmReasonName[MQRC_DEF_XMIT_Q_TYPE_ERROR]="DefXmitQTypeErrorError";
	hmReasonName[MQRC_DEF_XMIT_Q_USAGE_ERROR]="DefXmitQUsageErrorError";
	hmReasonName[MQRC_MSG_MARKED_BROWSE_CO_OP]="MsgMarkedBrowseCoOpOp";
	hmReasonName[MQRC_NAME_IN_USE]="NameInUse";
	hmReasonName[MQRC_CONNECTION_QUIESCING]="ConnectionQuiescing";
	hmReasonName[MQRC_CONNECTION_STOPPING]="ConnectionStopping";
	hmReasonName[MQRC_ADAPTER_NOT_AVAILABLE]="AdapterNotAvailable";
	hmReasonName[MQRC_MSG_ID_ERROR]="MsgIdError";
	hmReasonName[MQRC_CORREL_ID_ERROR]="CorrelIdError";
	hmReasonName[MQRC_FILE_SYSTEM_ERROR]="FileSystemError";
	hmReasonName[MQRC_NO_MSG_LOCKED]="NoMsgLocked";
	hmReasonName[MQRC_SOAP_DOTNET_ERROR]="SoapDotnetError";
	hmReasonName[MQRC_SOAP_AXIS_ERROR]="SoapAxisError";
	hmReasonName[MQRC_SOAP_URL_ERROR]="SoapUrlError";
	hmReasonName[MQRC_FILE_NOT_AUDITED]="FileNotAudited";
	hmReasonName[MQRC_CONNECTION_NOT_AUTHORIZED]="ConnectionNotAuthorized";
	hmReasonName[MQRC_MSG_TOO_BIG_FOR_CHANNEL]="MsgTooBigForChannelChannel";
	hmReasonName[MQRC_CALL_IN_PROGRESS]="CallInProgress";
	hmReasonName[MQRC_RMH_ERROR]="RmhError";
	hmReasonName[MQRC_Q_MGR_ACTIVE]="QMgrActive";
	hmReasonName[MQRC_Q_MGR_NOT_ACTIVE]="QMgrNotActive";
	hmReasonName[MQRC_Q_DEPTH_HIGH]="QDepthHigh";
	hmReasonName[MQRC_Q_DEPTH_LOW]="QDepthLow";
	hmReasonName[MQRC_Q_SERVICE_INTERVAL_HIGH]="QServiceIntervalHigh";
	hmReasonName[MQRC_Q_SERVICE_INTERVAL_OK]="QServiceIntervalOk";
	hmReasonName[MQRC_RFH_HEADER_FIELD_ERROR]="RfhHeaderFieldError";
	hmReasonName[MQRC_RAS_PROPERTY_ERROR]="RasPropertyError";
	hmReasonName[MQRC_UNIT_OF_WORK_NOT_STARTED]="UnitOfWorkNotStartedStarted";
	hmReasonName[MQRC_CHANNEL_AUTO_DEF_OK]="ChannelAutoDefOk";
	hmReasonName[MQRC_CHANNEL_AUTO_DEF_ERROR]="ChannelAutoDefError";
	hmReasonName[MQRC_CFH_ERROR]="CfhError";
	hmReasonName[MQRC_CFIL_ERROR]="CfilError";
	hmReasonName[MQRC_CFIN_ERROR]="CfinError";
	hmReasonName[MQRC_CFSL_ERROR]="CfslError";
	hmReasonName[MQRC_CFST_ERROR]="CfstError";
	hmReasonName[MQRC_INCOMPLETE_GROUP]="IncompleteGroup";
	hmReasonName[MQRC_INCOMPLETE_MSG]="IncompleteMsg";
	hmReasonName[MQRC_INCONSISTENT_CCSIDS]="InconsistentCcsids";
	hmReasonName[MQRC_INCONSISTENT_ENCODINGS]="InconsistentEncodings";
	hmReasonName[MQRC_INCONSISTENT_UOW]="InconsistentUow";
	hmReasonName[MQRC_INVALID_MSG_UNDER_CURSOR]="InvalidMsgUnderCursor";
	hmReasonName[MQRC_MATCH_OPTIONS_ERROR]="MatchOptionsError";
	hmReasonName[MQRC_MDE_ERROR]="MdeError";
	hmReasonName[MQRC_MSG_FLAGS_ERROR]="MsgFlagsError";
	hmReasonName[MQRC_MSG_SEQ_NUMBER_ERROR]="MsgSeqNumberError";
	hmReasonName[MQRC_OFFSET_ERROR]="OffsetError";
	hmReasonName[MQRC_ORIGINAL_LENGTH_ERROR]="OriginalLengthError";
	hmReasonName[MQRC_SEGMENT_LENGTH_ZERO]="SegmentLengthZero";
	hmReasonName[MQRC_UOW_NOT_AVAILABLE]="UowNotAvailable";
	hmReasonName[MQRC_WRONG_GMO_VERSION]="WrongGmoVersion";
	hmReasonName[MQRC_WRONG_MD_VERSION]="WrongMdVersion";
	hmReasonName[MQRC_GROUP_ID_ERROR]="GroupIdError";
	hmReasonName[MQRC_INCONSISTENT_BROWSE]="InconsistentBrowse";
	hmReasonName[MQRC_XQH_ERROR]="XqhError";
	hmReasonName[MQRC_SRC_ENV_ERROR]="SrcEnvError";
	hmReasonName[MQRC_SRC_NAME_ERROR]="SrcNameError";
	hmReasonName[MQRC_DEST_ENV_ERROR]="DestEnvError";
	hmReasonName[MQRC_DEST_NAME_ERROR]="DestNameError";
	hmReasonName[MQRC_TM_ERROR]="TmError";
	hmReasonName[MQRC_CLUSTER_EXIT_ERROR]="ClusterExitError";
	hmReasonName[MQRC_CLUSTER_EXIT_LOAD_ERROR]="ClusterExitLoadError";
	hmReasonName[MQRC_CLUSTER_PUT_INHIBITED]="ClusterPutInhibited";
	hmReasonName[MQRC_CLUSTER_RESOURCE_ERROR]="ClusterResourceError";
	hmReasonName[MQRC_NO_DESTINATIONS_AVAILABLE]="NoDestinationsAvailable";
	hmReasonName[MQRC_CONN_TAG_IN_USE]="ConnTagInUse";
	hmReasonName[MQRC_PARTIALLY_CONVERTED]="PartiallyConverted";
	hmReasonName[MQRC_CONNECTION_ERROR]="ConnectionError";
	hmReasonName[MQRC_OPTION_ENVIRONMENT_ERROR]="OptionEnvironmentError";
	hmReasonName[MQRC_CD_ERROR]="CdError";
	hmReasonName[MQRC_CLIENT_CONN_ERROR]="ClientConnError";
	hmReasonName[MQRC_CHANNEL_STOPPED_BY_USER]="ChannelStoppedByUser";
	hmReasonName[MQRC_HCONFIG_ERROR]="HconfigError";
	hmReasonName[MQRC_FUNCTION_ERROR]="FunctionError";
	hmReasonName[MQRC_CHANNEL_STARTED]="ChannelStarted";
	hmReasonName[MQRC_CHANNEL_STOPPED]="ChannelStopped";
	hmReasonName[MQRC_CHANNEL_CONV_ERROR]="ChannelConvError";
	hmReasonName[MQRC_SERVICE_NOT_AVAILABLE]="ServiceNotAvailable";
	hmReasonName[MQRC_INITIALIZATION_FAILED]="InitializationFailed";
	hmReasonName[MQRC_TERMINATION_FAILED]="TerminationFailed";
	hmReasonName[MQRC_UNKNOWN_Q_NAME]="UnknownQName";
	hmReasonName[MQRC_SERVICE_ERROR]="ServiceError";
	hmReasonName[MQRC_Q_ALREADY_EXISTS]="QAlreadyExists";
	hmReasonName[MQRC_USER_ID_NOT_AVAILABLE]="UserIdNotAvailable";
	hmReasonName[MQRC_UNKNOWN_ENTITY]="UnknownEntity";
	hmReasonName[MQRC_UNKNOWN_AUTH_ENTITY]="UnknownAuthEntity";
	hmReasonName[MQRC_UNKNOWN_REF_OBJECT]="UnknownRefObject";
	hmReasonName[MQRC_CHANNEL_ACTIVATED]="ChannelActivated";
	hmReasonName[MQRC_CHANNEL_NOT_ACTIVATED]="ChannelNotActivated";
	hmReasonName[MQRC_UOW_CANCELED]="UowCanceled";
	hmReasonName[MQRC_FUNCTION_NOT_SUPPORTED]="FunctionNotSupported";
	hmReasonName[MQRC_SELECTOR_TYPE_ERROR]="SelectorTypeError";
	hmReasonName[MQRC_COMMAND_TYPE_ERROR]="CommandTypeError";
	hmReasonName[MQRC_MULTIPLE_INSTANCE_ERROR]="MultipleInstanceError";
	hmReasonName[MQRC_SYSTEM_ITEM_NOT_ALTERABLE]="SystemItemNotAlterable";
	hmReasonName[MQRC_BAG_CONVERSION_ERROR]="BagConversionError";
	hmReasonName[MQRC_SELECTOR_OUT_OF_RANGE]="SelectorOutOfRange";
	hmReasonName[MQRC_SELECTOR_NOT_UNIQUE]="SelectorNotUnique";
	hmReasonName[MQRC_INDEX_NOT_PRESENT]="IndexNotPresent";
	hmReasonName[MQRC_STRING_ERROR]="StringError";
	hmReasonName[MQRC_ENCODING_NOT_SUPPORTED]="EncodingNotSupported";
	hmReasonName[MQRC_SELECTOR_NOT_PRESENT]="SelectorNotPresent";
	hmReasonName[MQRC_OUT_SELECTOR_ERROR]="OutSelectorError";
	hmReasonName[MQRC_STRING_TRUNCATED]="StringTruncated";
	hmReasonName[MQRC_SELECTOR_WRONG_TYPE]="SelectorWrongType";
	hmReasonName[MQRC_INCONSISTENT_ITEM_TYPE]="InconsistentItemType";
	hmReasonName[MQRC_INDEX_ERROR]="IndexError";
	hmReasonName[MQRC_SYSTEM_BAG_NOT_ALTERABLE]="SystemBagNotAlterable";
	hmReasonName[MQRC_ITEM_COUNT_ERROR]="ItemCountError";
	hmReasonName[MQRC_FORMAT_NOT_SUPPORTED]="FormatNotSupported";
	hmReasonName[MQRC_SELECTOR_NOT_SUPPORTED]="SelectorNotSupported";
	hmReasonName[MQRC_ITEM_VALUE_ERROR]="ItemValueError";
	hmReasonName[MQRC_HBAG_ERROR]="HbagError";
	hmReasonName[MQRC_PARAMETER_MISSING]="ParameterMissing";
	hmReasonName[MQRC_CMD_SERVER_NOT_AVAILABLE]="CmdServerNotAvailable";
	hmReasonName[MQRC_STRING_LENGTH_ERROR]="StringLengthError";
	hmReasonName[MQRC_INQUIRY_COMMAND_ERROR]="InquiryCommandError";
	hmReasonName[MQRC_NESTED_BAG_NOT_SUPPORTED]="NestedBagNotSupported";
	hmReasonName[MQRC_BAG_WRONG_TYPE]="BagWrongType";
	hmReasonName[MQRC_ITEM_TYPE_ERROR]="ItemTypeError";
	hmReasonName[MQRC_SYSTEM_BAG_NOT_DELETABLE]="SystemBagNotDeletable";
	hmReasonName[MQRC_SYSTEM_ITEM_NOT_DELETABLE]="SystemItemNotDeletable";
	hmReasonName[MQRC_CODED_CHAR_SET_ID_ERROR]="CodedCharSetIdErrorError";
	hmReasonName[MQRC_MSG_TOKEN_ERROR]="MsgTokenError";
	hmReasonName[MQRC_MISSING_WIH]="MissingWih";
	hmReasonName[MQRC_WIH_ERROR]="WihError";
	hmReasonName[MQRC_RFH_ERROR]="RfhError";
	hmReasonName[MQRC_RFH_STRING_ERROR]="RfhStringError";
	hmReasonName[MQRC_RFH_COMMAND_ERROR]="RfhCommandError";
	hmReasonName[MQRC_RFH_PARM_ERROR]="RfhParmError";
	hmReasonName[MQRC_RFH_DUPLICATE_PARM]="RfhDuplicateParm";
	hmReasonName[MQRC_RFH_PARM_MISSING]="RfhParmMissing";
	hmReasonName[MQRC_CHAR_CONVERSION_ERROR]="CharConversionError";
	hmReasonName[MQRC_UCS2_CONVERSION_ERROR]="Ucs2ConversionError";
	hmReasonName[MQRC_DB2_NOT_AVAILABLE]="Db2NotAvailable";
	hmReasonName[MQRC_OBJECT_NOT_UNIQUE]="ObjectNotUnique";
	hmReasonName[MQRC_CONN_TAG_NOT_RELEASED]="ConnTagNotReleased";
	hmReasonName[MQRC_CF_NOT_AVAILABLE]="CfNotAvailable";
	hmReasonName[MQRC_CF_STRUC_IN_USE]="CfStrucInUse";
	hmReasonName[MQRC_CF_STRUC_LIST_HDR_IN_USE]="CfStrucListHdrInIn";
	hmReasonName[MQRC_CF_STRUC_AUTH_FAILED]="CfStrucAuthFailed";
	hmReasonName[MQRC_CF_STRUC_ERROR]="CfStrucError";
	hmReasonName[MQRC_CONN_TAG_NOT_USABLE]="ConnTagNotUsable";
	hmReasonName[MQRC_GLOBAL_UOW_CONFLICT]="GlobalUowConflict";
	hmReasonName[MQRC_LOCAL_UOW_CONFLICT]="LocalUowConflict";
	hmReasonName[MQRC_HANDLE_IN_USE_FOR_UOW]="HandleInUseForUowUow";
	hmReasonName[MQRC_UOW_ENLISTMENT_ERROR]="UowEnlistmentError";
	hmReasonName[MQRC_UOW_MIX_NOT_SUPPORTED]="UowMixNotSupported";
	hmReasonName[MQRC_WXP_ERROR]="WxpError";
	hmReasonName[MQRC_CURRENT_RECORD_ERROR]="CurrentRecordError";
	hmReasonName[MQRC_NEXT_OFFSET_ERROR]="NextOffsetError";
	hmReasonName[MQRC_NO_RECORD_AVAILABLE]="NoRecordAvailable";
	hmReasonName[MQRC_OBJECT_LEVEL_INCOMPATIBLE]="ObjectLevelIncompatible";
	hmReasonName[MQRC_NEXT_RECORD_ERROR]="NextRecordError";
	hmReasonName[MQRC_BACKOUT_THRESHOLD_REACHED]="BackoutThresholdReached";
	hmReasonName[MQRC_MSG_NOT_MATCHED]="MsgNotMatched";
	hmReasonName[MQRC_JMS_FORMAT_ERROR]="JmsFormatError";
	hmReasonName[MQRC_SEGMENTS_NOT_SUPPORTED]="SegmentsNotSupported";
	hmReasonName[MQRC_WRONG_CF_LEVEL]="WrongCfLevel";
	hmReasonName[MQRC_CONFIG_CREATE_OBJECT]="ConfigCreateObject";
	hmReasonName[MQRC_CONFIG_CHANGE_OBJECT]="ConfigChangeObject";
	hmReasonName[MQRC_CONFIG_DELETE_OBJECT]="ConfigDeleteObject";
	hmReasonName[MQRC_CONFIG_REFRESH_OBJECT]="ConfigRefreshObject";
	hmReasonName[MQRC_CHANNEL_SSL_ERROR]="ChannelSslError";
	hmReasonName[MQRC_PARTICIPANT_NOT_DEFINED]="ParticipantNotDefined";
	hmReasonName[MQRC_CF_STRUC_FAILED]="CfStrucFailed";
	hmReasonName[MQRC_API_EXIT_ERROR]="ApiExitError";
	hmReasonName[MQRC_API_EXIT_INIT_ERROR]="ApiExitInitError";
	hmReasonName[MQRC_API_EXIT_TERM_ERROR]="ApiExitTermError";
	hmReasonName[MQRC_EXIT_REASON_ERROR]="ExitReasonError";
	hmReasonName[MQRC_RESERVED_VALUE_ERROR]="ReservedValueError";
	hmReasonName[MQRC_NO_DATA_AVAILABLE]="NoDataAvailable";
	hmReasonName[MQRC_SCO_ERROR]="ScoError";
	hmReasonName[MQRC_KEY_REPOSITORY_ERROR]="KeyRepositoryError";
	hmReasonName[MQRC_CRYPTO_HARDWARE_ERROR]="CryptoHardwareError";
	hmReasonName[MQRC_AUTH_INFO_REC_COUNT_ERROR]="AuthInfoRecCountErrorError";
	hmReasonName[MQRC_AUTH_INFO_REC_ERROR]="AuthInfoRecError";
	hmReasonName[MQRC_AIR_ERROR]="AirError";
	hmReasonName[MQRC_AUTH_INFO_TYPE_ERROR]="AuthInfoTypeError";
	hmReasonName[MQRC_AUTH_INFO_CONN_NAME_ERROR]="AuthInfoConnNameErrorError";
	hmReasonName[MQRC_LDAP_USER_NAME_ERROR]="LdapUserNameError";
	hmReasonName[MQRC_LDAP_USER_NAME_LENGTH_ERR]="LdapUserNameLengthErrErr";
	hmReasonName[MQRC_LDAP_PASSWORD_ERROR]="LdapPasswordError";
	hmReasonName[MQRC_SSL_ALREADY_INITIALIZED]="SslAlreadyInitialized";
	hmReasonName[MQRC_SSL_CONFIG_ERROR]="SslConfigError";
	hmReasonName[MQRC_SSL_INITIALIZATION_ERROR]="SslInitializationError";
	hmReasonName[MQRC_Q_INDEX_TYPE_ERROR]="QIndexTypeError";
	hmReasonName[MQRC_CFBS_ERROR]="CfbsError";
	hmReasonName[MQRC_SSL_NOT_ALLOWED]="SslNotAllowed";
	hmReasonName[MQRC_JSSE_ERROR]="JsseError";
	hmReasonName[MQRC_SSL_PEER_NAME_MISMATCH]="SslPeerNameMismatch";
	hmReasonName[MQRC_SSL_PEER_NAME_ERROR]="SslPeerNameError";
	hmReasonName[MQRC_UNSUPPORTED_CIPHER_SUITE]="UnsupportedCipherSuite";
	hmReasonName[MQRC_SSL_CERTIFICATE_REVOKED]="SslCertificateRevoked";
	hmReasonName[MQRC_SSL_CERT_STORE_ERROR]="SslCertStoreError";
	hmReasonName[MQRC_CLIENT_EXIT_LOAD_ERROR]="ClientExitLoadError";
	hmReasonName[MQRC_CLIENT_EXIT_ERROR]="ClientExitError";
	hmReasonName[MQRC_UOW_COMMITTED]="UowCommitted";
	hmReasonName[MQRC_SSL_KEY_RESET_ERROR]="SslKeyResetError";
	hmReasonName[MQRC_UNKNOWN_COMPONENT_NAME]="UnknownComponentName";
	hmReasonName[MQRC_LOGGER_STATUS]="LoggerStatus";
	hmReasonName[MQRC_COMMAND_MQSC]="CommandMqsc";
	hmReasonName[MQRC_COMMAND_PCF]="CommandPcf";
	hmReasonName[MQRC_CFIF_ERROR]="CfifError";
	hmReasonName[MQRC_CFSF_ERROR]="CfsfError";
	hmReasonName[MQRC_CFGR_ERROR]="CfgrError";
	hmReasonName[MQRC_MSG_NOT_ALLOWED_IN_GROUP]="MsgNotAllowedInGroupGroup";
	hmReasonName[MQRC_FILTER_OPERATOR_ERROR]="FilterOperatorError";
	hmReasonName[MQRC_NESTED_SELECTOR_ERROR]="NestedSelectorError";
	hmReasonName[MQRC_EPH_ERROR]="EphError";
	hmReasonName[MQRC_RFH_FORMAT_ERROR]="RfhFormatError";
	hmReasonName[MQRC_CFBF_ERROR]="CfbfError";
	hmReasonName[MQRC_CLIENT_CHANNEL_CONFLICT]="ClientChannelConflict";
	hmReasonName[MQRC_SD_ERROR]="SdError";
	hmReasonName[MQRC_TOPIC_STRING_ERROR]="TopicStringError";
	hmReasonName[MQRC_STS_ERROR]="StsError";
	hmReasonName[MQRC_NO_SUBSCRIPTION]="NoSubscription";
	hmReasonName[MQRC_SUBSCRIPTION_IN_USE]="SubscriptionInUse";
	hmReasonName[MQRC_STAT_TYPE_ERROR]="StatTypeError";
	hmReasonName[MQRC_SUB_USER_DATA_ERROR]="SubUserDataError";
	hmReasonName[MQRC_SUB_ALREADY_EXISTS]="SubAlreadyExists";
	hmReasonName[MQRC_IDENTITY_MISMATCH]="IdentityMismatch";
	hmReasonName[MQRC_ALTER_SUB_ERROR]="AlterSubError";
	hmReasonName[MQRC_DURABILITY_NOT_ALLOWED]="DurabilityNotAllowed";
	hmReasonName[MQRC_NO_RETAINED_MSG]="NoRetainedMsg";
	hmReasonName[MQRC_SRO_ERROR]="SroError";
	hmReasonName[MQRC_SUB_NAME_ERROR]="SubNameError";
	hmReasonName[MQRC_OBJECT_STRING_ERROR]="ObjectStringError";
	hmReasonName[MQRC_PROPERTY_NAME_ERROR]="PropertyNameError";
	hmReasonName[MQRC_SEGMENTATION_NOT_ALLOWED]="SegmentationNotAllowed";
	hmReasonName[MQRC_CBD_ERROR]="CbdError";
	hmReasonName[MQRC_CTLO_ERROR]="CtloError";
	hmReasonName[MQRC_NO_CALLBACKS_ACTIVE]="NoCallbacksActive";
	hmReasonName[MQRC_CALLBACK_NOT_REGISTERED]="CallbackNotRegistered";
	hmReasonName[MQRC_OPTIONS_CHANGED]="OptionsChanged";
	hmReasonName[MQRC_READ_AHEAD_MSGS]="ReadAheadMsgs";
	hmReasonName[MQRC_SELECTOR_SYNTAX_ERROR]="SelectorSyntaxError";
	hmReasonName[MQRC_HMSG_ERROR]="HmsgError";
	hmReasonName[MQRC_CMHO_ERROR]="CmhoError";
	hmReasonName[MQRC_DMHO_ERROR]="DmhoError";
	hmReasonName[MQRC_SMPO_ERROR]="SmpoError";
	hmReasonName[MQRC_IMPO_ERROR]="ImpoError";
	hmReasonName[MQRC_PROPERTY_NAME_TOO_BIG]="PropertyNameTooBig";
	hmReasonName[MQRC_PROP_VALUE_NOT_CONVERTED]="PropValueNotConverted";
	hmReasonName[MQRC_PROP_TYPE_NOT_SUPPORTED]="PropTypeNotSupported";
	hmReasonName[MQRC_PROPERTY_VALUE_TOO_BIG]="PropertyValueTooBig";
	hmReasonName[MQRC_PROP_CONV_NOT_SUPPORTED]="PropConvNotSupported";
	hmReasonName[MQRC_PROPERTY_NOT_AVAILABLE]="PropertyNotAvailable";
	hmReasonName[MQRC_PROP_NUMBER_FORMAT_ERROR]="PropNumberFormatError";
	hmReasonName[MQRC_PROPERTY_TYPE_ERROR]="PropertyTypeError";
	hmReasonName[MQRC_PROPERTIES_TOO_BIG]="PropertiesTooBig";
	hmReasonName[MQRC_PUT_NOT_RETAINED]="PutNotRetained";
	hmReasonName[MQRC_ALIAS_TARGTYPE_CHANGED]="AliasTargtypeChanged";
	hmReasonName[MQRC_DMPO_ERROR]="DmpoError";
	hmReasonName[MQRC_PD_ERROR]="PdError";
	hmReasonName[MQRC_CALLBACK_TYPE_ERROR]="CallbackTypeError";
	hmReasonName[MQRC_CBD_OPTIONS_ERROR]="CbdOptionsError";
	hmReasonName[MQRC_MAX_MSG_LENGTH_ERROR]="MaxMsgLengthError";
	hmReasonName[MQRC_CALLBACK_ROUTINE_ERROR]="CallbackRoutineError";
	hmReasonName[MQRC_CALLBACK_LINK_ERROR]="CallbackLinkError";
	hmReasonName[MQRC_OPERATION_ERROR]="OperationError";
	hmReasonName[MQRC_BMHO_ERROR]="BmhoError";
	hmReasonName[MQRC_UNSUPPORTED_PROPERTY]="UnsupportedProperty";
	hmReasonName[MQRC_PROP_NAME_NOT_CONVERTED]="PropNameNotConverted";
	hmReasonName[MQRC_GET_ENABLED]="GetEnabled";
	hmReasonName[MQRC_MODULE_NOT_FOUND]="ModuleNotFound";
	hmReasonName[MQRC_MODULE_INVALID]="ModuleInvalid";
	hmReasonName[MQRC_MODULE_ENTRY_NOT_FOUND]="ModuleEntryNotFound";
	hmReasonName[MQRC_MIXED_CONTENT_NOT_ALLOWED]="MixedContentNotAllowed";
	hmReasonName[MQRC_MSG_HANDLE_IN_USE]="MsgHandleInUse";
	hmReasonName[MQRC_HCONN_ASYNC_ACTIVE]="HconnAsyncActive";
	hmReasonName[MQRC_MHBO_ERROR]="MhboError";
	hmReasonName[MQRC_PUBLICATION_FAILURE]="PublicationFailure";
	hmReasonName[MQRC_SUB_INHIBITED]="SubInhibited";
	hmReasonName[MQRC_SELECTOR_ALWAYS_FALSE]="SelectorAlwaysFalse";
	hmReasonName[MQRC_XEPO_ERROR]="XepoError";
	hmReasonName[MQRC_DURABILITY_NOT_ALTERABLE]="DurabilityNotAlterable";
	hmReasonName[MQRC_TOPIC_NOT_ALTERABLE]="TopicNotAlterable";
	hmReasonName[MQRC_SUBLEVEL_NOT_ALTERABLE]="SublevelNotAlterable";
	hmReasonName[MQRC_PROPERTY_NAME_LENGTH_ERR]="PropertyNameLengthErr";
	hmReasonName[MQRC_DUPLICATE_GROUP_SUB]="DuplicateGroupSub";
	hmReasonName[MQRC_GROUPING_NOT_ALTERABLE]="GroupingNotAlterable";
	hmReasonName[MQRC_SELECTOR_INVALID_FOR_TYPE]="SelectorInvalidForType";
	hmReasonName[MQRC_HOBJ_QUIESCED]="HobjQuiesced";
	hmReasonName[MQRC_HOBJ_QUIESCED_NO_MSGS]="HobjQuiescedNoMsgs";
	hmReasonName[MQRC_SELECTION_STRING_ERROR]="SelectionStringError";
	hmReasonName[MQRC_RES_OBJECT_STRING_ERROR]="ResObjectStringError";
	hmReasonName[MQRC_CONNECTION_SUSPENDED]="ConnectionSuspended";
	hmReasonName[MQRC_INVALID_DESTINATION]="InvalidDestination";
	hmReasonName[MQRC_INVALID_SUBSCRIPTION]="InvalidSubscription";
	hmReasonName[MQRC_SELECTOR_NOT_ALTERABLE]="SelectorNotAlterable";
	hmReasonName[MQRC_RETAINED_MSG_Q_ERROR]="RetainedMsgQError";
	hmReasonName[MQRC_RETAINED_NOT_DELIVERED]="RetainedNotDelivered";
	hmReasonName[MQRC_RFH_RESTRICTED_FORMAT_ERR]="RfhRestrictedFormatErr";
	hmReasonName[MQRC_CONNECTION_STOPPED]="ConnectionStopped";
	hmReasonName[MQRC_ASYNC_UOW_CONFLICT]="AsyncUowConflict";
	hmReasonName[MQRC_ASYNC_XA_CONFLICT]="AsyncXaConflict";
	hmReasonName[MQRC_PUBSUB_INHIBITED]="PubsubInhibited";
	hmReasonName[MQRC_MSG_HANDLE_COPY_FAILURE]="MsgHandleCopyFailure";
	hmReasonName[MQRC_DEST_CLASS_NOT_ALTERABLE]="DestClassNotAlterable";
	hmReasonName[MQRC_OPERATION_NOT_ALLOWED]="OperationNotAllowed";
	hmReasonName[MQRC_ACTION_ERROR]="ActionError";
	hmReasonName[MQRC_CHANNEL_NOT_AVAILABLE]="ChannelNotAvailable";
	hmReasonName[MQRC_HOST_NOT_AVAILABLE]="HostNotAvailable";
	hmReasonName[MQRC_CHANNEL_CONFIG_ERROR]="ChannelConfigError";
	hmReasonName[MQRC_UNKNOWN_CHANNEL_NAME]="UnknownChannelName";
	hmReasonName[MQRC_LOOPING_PUBLICATION]="LoopingPublication";
	hmReasonName[MQRC_ALREADY_JOINED]="AlreadyJoined";
	hmReasonName[MQRC_STANDBY_Q_MGR]="StandbyQMgr";
	hmReasonName[MQRC_RECONNECTING]="Reconnecting";
	hmReasonName[MQRC_RECONNECTED]="Reconnected";
	hmReasonName[MQRC_RECONNECT_QMID_MISMATCH]="ReconnectQmidMismatch";
	hmReasonName[MQRC_RECONNECT_INCOMPATIBLE]="ReconnectIncompatible";
	hmReasonName[MQRC_RECONNECT_FAILED]="ReconnectFailed";
	hmReasonName[MQRC_CALL_INTERRUPTED]="CallInterrupted";
	hmReasonName[MQRC_NO_SUBS_MATCHED]="NoSubsMatched";
	hmReasonName[MQRC_SELECTION_NOT_AVAILABLE]="SelectionNotAvailable";
	hmReasonName[MQRC_CHANNEL_SSL_WARNING]="ChannelSslWarning";
	hmReasonName[MQRC_OCSP_URL_ERROR]="OcspUrlError";
	hmReasonName[MQRC_CONTENT_ERROR]="ContentError";
	hmReasonName[MQRC_RECONNECT_Q_MGR_REQD]="ReconnectQMgrReqd";
	hmReasonName[MQRC_RECONNECT_TIMED_OUT]="ReconnectTimedOut";
	hmReasonName[MQRC_PUBLISH_EXIT_ERROR]="PublishExitError";
	hmReasonName[MQRC_COMMINFO_ERROR]="ComminfoError";
	hmReasonName[MQRC_DEF_SYNCPOINT_INHIBITED]="DefSyncpointInhibited";
	hmReasonName[MQRC_MULTICAST_ONLY]="MulticastOnly";
	hmReasonName[MQRC_DATA_SET_NOT_AVAILABLE]="DataSetNotAvailable";
	hmReasonName[MQRC_GROUPING_NOT_ALLOWED]="GroupingNotAllowed";
	hmReasonName[MQRC_GROUP_ADDRESS_ERROR]="GroupAddressError";
	hmReasonName[MQRC_MULTICAST_CONFIG_ERROR]="MulticastConfigError";
	hmReasonName[MQRC_MULTICAST_INTERFACE_ERROR]="MulticastInterfaceError";
	hmReasonName[MQRC_MULTICAST_SEND_ERROR]="MulticastSendError";
	hmReasonName[MQRC_MULTICAST_INTERNAL_ERROR]="MulticastInternalError";
	hmReasonName[MQRC_CONNECTION_NOT_AVAILABLE]="ConnectionNotAvailable";
	hmReasonName[MQRC_SYNCPOINT_NOT_ALLOWED]="SyncpointNotAllowed";
	hmReasonName[MQRC_SSL_ALT_PROVIDER_REQUIRED]="SslAltProviderRequired";
	hmReasonName[MQRC_MCAST_PUB_STATUS]="McastPubStatus";
	hmReasonName[MQRC_MCAST_SUB_STATUS]="McastSubStatus";
	hmReasonName[MQRC_PRECONN_EXIT_LOAD_ERROR]="PreconnExitLoadError";
	hmReasonName[MQRC_PRECONN_EXIT_NOT_FOUND]="PreconnExitNotFound";
	hmReasonName[MQRC_PRECONN_EXIT_ERROR]="PreconnExitError";
	hmReasonName[MQRC_CD_ARRAY_ERROR]="CdArrayError";
	hmReasonName[MQRC_CHANNEL_BLOCKED]="ChannelBlocked";
	hmReasonName[MQRC_CHANNEL_BLOCKED_WARNING]="ChannelBlockedWarning";
	hmReasonName[MQRC_SUBSCRIPTION_CREATE]="SubscriptionCreate";
	hmReasonName[MQRC_SUBSCRIPTION_DELETE]="SubscriptionDelete";
	hmReasonName[MQRC_SUBSCRIPTION_CHANGE]="SubscriptionChange";
	hmReasonName[MQRC_SUBSCRIPTION_REFRESH]="SubscriptionRefresh";
	hmReasonName[MQRC_INSTALLATION_MISMATCH]="InstallationMismatch";
	hmReasonName[MQRC_NOT_PRIVILEGED]="NotPrivileged";
	hmReasonName[MQRC_PROPERTIES_DISABLED]="PropertiesDisabled";
	hmReasonName[MQRC_HMSG_NOT_AVAILABLE]="HmsgNotAvailable";
	hmReasonName[MQRC_EXIT_PROPS_NOT_SUPPORTED]="ExitPropsNotSupported";
	hmReasonName[MQRC_INSTALLATION_MISSING]="InstallationMissing";
	hmReasonName[MQRC_FASTPATH_NOT_AVAILABLE]="FastpathNotAvailable";
	hmReasonName[MQRC_CIPHER_SPEC_NOT_SUITE_B]="CipherSpecNotSuiteBB";
	hmReasonName[MQRC_SUITE_B_ERROR]="SuiteBError";
	hmReasonName[MQRC_CERT_VAL_POLICY_ERROR]="CertValPolicyError";
	hmReasonName[MQRC_REOPEN_EXCL_INPUT_ERROR]="ReopenExclInputError";
	hmReasonName[MQRC_REOPEN_INQUIRE_ERROR]="ReopenInquireError";
	hmReasonName[MQRC_REOPEN_SAVED_CONTEXT_ERR]="ReopenSavedContextErr";
	hmReasonName[MQRC_REOPEN_TEMPORARY_Q_ERROR]="ReopenTemporaryQError";
	hmReasonName[MQRC_ATTRIBUTE_LOCKED]="AttributeLocked";
	hmReasonName[MQRC_CURSOR_NOT_VALID]="CursorNotValid";
	hmReasonName[MQRC_ENCODING_ERROR]="EncodingError";
	hmReasonName[MQRC_STRUC_ID_ERROR]="StrucIdError";
	hmReasonName[MQRC_NULL_POINTER]="NullPointer";
	hmReasonName[MQRC_NO_CONNECTION_REFERENCE]="NoConnectionReference";
	hmReasonName[MQRC_NO_BUFFER]="NoBuffer";
	hmReasonName[MQRC_BINARY_DATA_LENGTH_ERROR]="BinaryDataLengthError";
	hmReasonName[MQRC_BUFFER_NOT_AUTOMATIC]="BufferNotAutomatic";
	hmReasonName[MQRC_INSUFFICIENT_BUFFER]="InsufficientBuffer";
	hmReasonName[MQRC_INSUFFICIENT_DATA]="InsufficientData";
	hmReasonName[MQRC_DATA_TRUNCATED]="DataTruncated";
	hmReasonName[MQRC_ZERO_LENGTH]="ZeroLength";
	hmReasonName[MQRC_NEGATIVE_LENGTH]="NegativeLength";
	hmReasonName[MQRC_NEGATIVE_OFFSET]="NegativeOffset";
	hmReasonName[MQRC_INCONSISTENT_FORMAT]="InconsistentFormat";
	hmReasonName[MQRC_INCONSISTENT_OBJECT_STATE]="InconsistentObjectState";
	hmReasonName[MQRC_CONTEXT_OBJECT_NOT_VALID]="ContextObjectNotValid";
	hmReasonName[MQRC_CONTEXT_OPEN_ERROR]="ContextOpenError";
	hmReasonName[MQRC_STRUC_LENGTH_ERROR]="StrucLengthError";
	hmReasonName[MQRC_NOT_CONNECTED]="NotConnected";
	hmReasonName[MQRC_NOT_OPEN]="NotOpen";
	hmReasonName[MQRC_DISTRIBUTION_LIST_EMPTY]="DistributionListEmpty";
	hmReasonName[MQRC_INCONSISTENT_OPEN_OPTIONS]="InconsistentOpenOptions";
	hmReasonName[MQRC_WRONG_VERSION]="WrongVersion";
	hmReasonName[MQRC_REFERENCE_ERROR]="ReferenceError";
	hmReasonName[MQRC_XR_NOT_AVAILABLE]="XrNotAvailable";

	hmReasonName[MQRCCF_CFH_TYPE_ERROR]="CfhTypeError";
	hmReasonName[MQRCCF_CFH_LENGTH_ERROR]="CfhLengthError";
	hmReasonName[MQRCCF_CFH_VERSION_ERROR]="CfhVersionError";
	hmReasonName[MQRCCF_CFH_MSG_SEQ_NUMBER_ERR]="CfhMsgSeqNumberErrErr";
	hmReasonName[MQRCCF_CFH_CONTROL_ERROR]="CfhControlError";
	hmReasonName[MQRCCF_CFH_PARM_COUNT_ERROR]="CfhParmCountError";
	hmReasonName[MQRCCF_CFH_COMMAND_ERROR]="CfhCommandError";
	hmReasonName[MQRCCF_COMMAND_FAILED]="CommandFailed";
	hmReasonName[MQRCCF_CFIN_LENGTH_ERROR]="CfinLengthError";
	hmReasonName[MQRCCF_CFST_LENGTH_ERROR]="CfstLengthError";
	hmReasonName[MQRCCF_CFST_STRING_LENGTH_ERR]="CfstStringLengthErr";
	hmReasonName[MQRCCF_FORCE_VALUE_ERROR]="ForceValueError";
	hmReasonName[MQRCCF_STRUCTURE_TYPE_ERROR]="StructureTypeError";
	hmReasonName[MQRCCF_CFIN_PARM_ID_ERROR]="CfinParmIdError";
	hmReasonName[MQRCCF_CFST_PARM_ID_ERROR]="CfstParmIdError";
	hmReasonName[MQRCCF_MSG_LENGTH_ERROR]="MsgLengthError";
	hmReasonName[MQRCCF_CFIN_DUPLICATE_PARM]="CfinDuplicateParm";
	hmReasonName[MQRCCF_CFST_DUPLICATE_PARM]="CfstDuplicateParm";
	hmReasonName[MQRCCF_PARM_COUNT_TOO_SMALL]="ParmCountTooSmall";
	hmReasonName[MQRCCF_PARM_COUNT_TOO_BIG]="ParmCountTooBig";
	hmReasonName[MQRCCF_Q_ALREADY_IN_CELL]="QAlreadyInCell";
	hmReasonName[MQRCCF_Q_TYPE_ERROR]="QTypeError";
	hmReasonName[MQRCCF_MD_FORMAT_ERROR]="MdFormatError";
	hmReasonName[MQRCCF_CFSL_LENGTH_ERROR]="CfslLengthError";
	hmReasonName[MQRCCF_REPLACE_VALUE_ERROR]="ReplaceValueError";
	hmReasonName[MQRCCF_CFIL_DUPLICATE_VALUE]="CfilDuplicateValue";
	hmReasonName[MQRCCF_CFIL_COUNT_ERROR]="CfilCountError";
	hmReasonName[MQRCCF_CFIL_LENGTH_ERROR]="CfilLengthError";
	hmReasonName[MQRCCF_QUIESCE_VALUE_ERROR]="QuiesceValueError";
	hmReasonName[MQRCCF_MODE_VALUE_ERROR]="ModeValueError";
	hmReasonName[MQRCCF_MSG_SEQ_NUMBER_ERROR]="MsgSeqNumberError";
	hmReasonName[MQRCCF_PING_DATA_COUNT_ERROR]="PingDataCountError";
	hmReasonName[MQRCCF_PING_DATA_COMPARE_ERROR]="PingDataCompareError";
	hmReasonName[MQRCCF_CFSL_PARM_ID_ERROR]="CfslParmIdError";
	hmReasonName[MQRCCF_CHANNEL_TYPE_ERROR]="ChannelTypeError";
	hmReasonName[MQRCCF_PARM_SEQUENCE_ERROR]="ParmSequenceError";
	hmReasonName[MQRCCF_XMIT_PROTOCOL_TYPE_ERR]="XmitProtocolTypeErr";
	hmReasonName[MQRCCF_BATCH_SIZE_ERROR]="BatchSizeError";
	hmReasonName[MQRCCF_DISC_INT_ERROR]="DiscIntError";
	hmReasonName[MQRCCF_SHORT_RETRY_ERROR]="ShortRetryError";
	hmReasonName[MQRCCF_SHORT_TIMER_ERROR]="ShortTimerError";
	hmReasonName[MQRCCF_LONG_RETRY_ERROR]="LongRetryError";
	hmReasonName[MQRCCF_LONG_TIMER_ERROR]="LongTimerError";
	hmReasonName[MQRCCF_SEQ_NUMBER_WRAP_ERROR]="SeqNumberWrapError";
	hmReasonName[MQRCCF_MAX_MSG_LENGTH_ERROR]="MaxMsgLengthError";
	hmReasonName[MQRCCF_PUT_AUTH_ERROR]="PutAuthError";
	hmReasonName[MQRCCF_PURGE_VALUE_ERROR]="PurgeValueError";
	hmReasonName[MQRCCF_CFIL_PARM_ID_ERROR]="CfilParmIdError";
	hmReasonName[MQRCCF_MSG_TRUNCATED]="MsgTruncated";
	hmReasonName[MQRCCF_CCSID_ERROR]="CcsidError";
	hmReasonName[MQRCCF_ENCODING_ERROR]="EncodingError";
	hmReasonName[MQRCCF_QUEUES_VALUE_ERROR]="QueuesValueError";
	hmReasonName[MQRCCF_DATA_CONV_VALUE_ERROR]="DataConvValueError";
	hmReasonName[MQRCCF_INDOUBT_VALUE_ERROR]="IndoubtValueError";
	hmReasonName[MQRCCF_ESCAPE_TYPE_ERROR]="EscapeTypeError";
	hmReasonName[MQRCCF_REPOS_VALUE_ERROR]="ReposValueError";
	hmReasonName[MQRCCF_CHANNEL_TABLE_ERROR]="ChannelTableError";
	hmReasonName[MQRCCF_MCA_TYPE_ERROR]="MCATypeError";
	hmReasonName[MQRCCF_CHL_INST_TYPE_ERROR]="ChlInstTypeError";
	hmReasonName[MQRCCF_CHL_STATUS_NOT_FOUND]="ChlStatusNotFound";
	hmReasonName[MQRCCF_CFSL_DUPLICATE_PARM]="CfslDuplicateParm";
	hmReasonName[MQRCCF_CFSL_TOTAL_LENGTH_ERROR]="CfslTotalLengthError";
	hmReasonName[MQRCCF_CFSL_COUNT_ERROR]="CfslCountError";
	hmReasonName[MQRCCF_CFSL_STRING_LENGTH_ERR]="CfslStringLengthErr";
	hmReasonName[MQRCCF_BROKER_DELETED]="BrokerDeleted";
	hmReasonName[MQRCCF_STREAM_ERROR]="StreamError";
	hmReasonName[MQRCCF_TOPIC_ERROR]="TopicError";
	hmReasonName[MQRCCF_NOT_REGISTERED]="NotRegistered";
	hmReasonName[MQRCCF_Q_MGR_NAME_ERROR]="QMgrNameError";
	hmReasonName[MQRCCF_INCORRECT_STREAM]="IncorrectStream";
	hmReasonName[MQRCCF_Q_NAME_ERROR]="QNameError";
	hmReasonName[MQRCCF_NO_RETAINED_MSG]="NoRetainedMsg";
	hmReasonName[MQRCCF_DUPLICATE_IDENTITY]="DuplicateIdentity";
	hmReasonName[MQRCCF_INCORRECT_Q]="IncorrectQ";
	hmReasonName[MQRCCF_CORREL_ID_ERROR]="CorrelIdError";
	hmReasonName[MQRCCF_NOT_AUTHORIZED]="NotAuthorized";
	hmReasonName[MQRCCF_UNKNOWN_STREAM]="UnknownStream";
	hmReasonName[MQRCCF_REG_OPTIONS_ERROR]="RegOptionsError";
	hmReasonName[MQRCCF_PUB_OPTIONS_ERROR]="PubOptionsError";
	hmReasonName[MQRCCF_UNKNOWN_BROKER]="UnknownBroker";
	hmReasonName[MQRCCF_Q_MGR_CCSID_ERROR]="QMgrCcsidError";
	hmReasonName[MQRCCF_DEL_OPTIONS_ERROR]="DelOptionsError";
	hmReasonName[MQRCCF_CLUSTER_NAME_CONFLICT]="ClusterNameConflict";
	hmReasonName[MQRCCF_REPOS_NAME_CONFLICT]="ReposNameConflict";
	hmReasonName[MQRCCF_CLUSTER_Q_USAGE_ERROR]="ClusterQUsageError";
	hmReasonName[MQRCCF_ACTION_VALUE_ERROR]="ActionValueError";
	hmReasonName[MQRCCF_COMMS_LIBRARY_ERROR]="CommsLibraryError";
	hmReasonName[MQRCCF_NETBIOS_NAME_ERROR]="NetbiosNameError";
	hmReasonName[MQRCCF_BROKER_COMMAND_FAILED]="BrokerCommandFailed";
	hmReasonName[MQRCCF_CFST_CONFLICTING_PARM]="CfstConflictingParm";
	hmReasonName[MQRCCF_PATH_NOT_VALID]="PathNotValid";
	hmReasonName[MQRCCF_PARM_SYNTAX_ERROR]="ParmSyntaxError";
	hmReasonName[MQRCCF_PWD_LENGTH_ERROR]="PwdLengthError";
	hmReasonName[MQRCCF_FILTER_ERROR]="FilterError";
	hmReasonName[MQRCCF_WRONG_USER]="WrongUser";
	hmReasonName[MQRCCF_DUPLICATE_SUBSCRIPTION]="DuplicateSubscription";
	hmReasonName[MQRCCF_SUB_NAME_ERROR]="SubNameError";
	hmReasonName[MQRCCF_SUB_IDENTITY_ERROR]="SubIdentityError";
	hmReasonName[MQRCCF_SUBSCRIPTION_IN_USE]="SubscriptionInUse";
	hmReasonName[MQRCCF_SUBSCRIPTION_LOCKED]="SubscriptionLocked";
	hmReasonName[MQRCCF_ALREADY_JOINED]="AlreadyJoined";
	hmReasonName[MQRCCF_OBJECT_IN_USE]="ObjectInUse";
	hmReasonName[MQRCCF_UNKNOWN_FILE_NAME]="UnknownFileName";
	hmReasonName[MQRCCF_FILE_NOT_AVAILABLE]="FileNotAvailable";
	hmReasonName[MQRCCF_DISC_RETRY_ERROR]="DiscRetryError";
	hmReasonName[MQRCCF_ALLOC_RETRY_ERROR]="AllocRetryError";
	hmReasonName[MQRCCF_ALLOC_SLOW_TIMER_ERROR]="AllocSlowTimerError";
	hmReasonName[MQRCCF_ALLOC_FAST_TIMER_ERROR]="AllocFastTimerError";
	hmReasonName[MQRCCF_PORT_NUMBER_ERROR]="PortNumberError";
	hmReasonName[MQRCCF_CHL_SYSTEM_NOT_ACTIVE]="ChlSystemNotActive";
	hmReasonName[MQRCCF_ENTITY_NAME_MISSING]="EntityNameMissing";
	hmReasonName[MQRCCF_PROFILE_NAME_ERROR]="ProfileNameError";
	hmReasonName[MQRCCF_AUTH_VALUE_ERROR]="AuthValueError";
	hmReasonName[MQRCCF_AUTH_VALUE_MISSING]="AuthValueMissing";
	hmReasonName[MQRCCF_OBJECT_TYPE_MISSING]="ObjectTypeMissing";
	hmReasonName[MQRCCF_CONNECTION_ID_ERROR]="ConnectionIdError";
	hmReasonName[MQRCCF_LOG_TYPE_ERROR]="LogTypeError";
	hmReasonName[MQRCCF_PROGRAM_NOT_AVAILABLE]="ProgramNotAvailable";
	hmReasonName[MQRCCF_PROGRAM_AUTH_FAILED]="ProgramAuthFailed";
	hmReasonName[MQRCCF_NONE_FOUND]="NoneFound";
	hmReasonName[MQRCCF_SECURITY_SWITCH_OFF]="SecuritySwitchOff";
	hmReasonName[MQRCCF_SECURITY_REFRESH_FAILED]="SecurityRefreshFailed";
	hmReasonName[MQRCCF_PARM_CONFLICT]="ParmConflict";
	hmReasonName[MQRCCF_COMMAND_INHIBITED]="CommandInhibited";
	hmReasonName[MQRCCF_OBJECT_BEING_DELETED]="ObjectBeingDeleted";
	hmReasonName[MQRCCF_STORAGE_CLASS_IN_USE]="StorageClassInUse";
	hmReasonName[MQRCCF_OBJECT_NAME_RESTRICTED]="ObjectNameRestricted";
	hmReasonName[MQRCCF_OBJECT_LIMIT_EXCEEDED]="ObjectLimitExceeded";
	hmReasonName[MQRCCF_OBJECT_OPEN_FORCE]="ObjectOpenForce";
	hmReasonName[MQRCCF_DISPOSITION_CONFLICT]="DispositionConflict";
	hmReasonName[MQRCCF_Q_MGR_NOT_IN_QSG]="QMgrNotInQsgQsg";
	hmReasonName[MQRCCF_ATTR_VALUE_FIXED]="AttrValueFixed";
	hmReasonName[MQRCCF_NAMELIST_ERROR]="NamelistError";
	hmReasonName[MQRCCF_NO_CHANNEL_INITIATOR]="NoChannelInitiator";
	hmReasonName[MQRCCF_CHANNEL_INITIATOR_ERROR]="ChannelInitiatorError";
	hmReasonName[MQRCCF_COMMAND_LEVEL_CONFLICT]="CommandLevelConflict";
	hmReasonName[MQRCCF_Q_ATTR_CONFLICT]="QAttrConflict";
	hmReasonName[MQRCCF_EVENTS_DISABLED]="EventsDisabled";
	hmReasonName[MQRCCF_COMMAND_SCOPE_ERROR]="CommandScopeError";
	hmReasonName[MQRCCF_COMMAND_REPLY_ERROR]="CommandReplyError";
	hmReasonName[MQRCCF_FUNCTION_RESTRICTED]="FunctionRestricted";
	hmReasonName[MQRCCF_PARM_MISSING]="ParmMissing";
	hmReasonName[MQRCCF_PARM_VALUE_ERROR]="ParmValueError";
	hmReasonName[MQRCCF_COMMAND_LENGTH_ERROR]="CommandLengthError";
	hmReasonName[MQRCCF_COMMAND_ORIGIN_ERROR]="CommandOriginError";
	hmReasonName[MQRCCF_LISTENER_CONFLICT]="ListenerConflict";
	hmReasonName[MQRCCF_LISTENER_STARTED]="ListenerStarted";
	hmReasonName[MQRCCF_LISTENER_STOPPED]="ListenerStopped";
	hmReasonName[MQRCCF_CHANNEL_ERROR]="ChannelError";
	hmReasonName[MQRCCF_CF_STRUC_ERROR]="CfStrucError";
	hmReasonName[MQRCCF_UNKNOWN_USER_ID]="UnknownUserId";
	hmReasonName[MQRCCF_UNEXPECTED_ERROR]="UnexpectedError";
	hmReasonName[MQRCCF_NO_XCF_PARTNER]="NoXcfPartner";
	hmReasonName[MQRCCF_CFGR_PARM_ID_ERROR]="CfgrParmIdError";
	hmReasonName[MQRCCF_CFIF_LENGTH_ERROR]="CfifLengthError";
	hmReasonName[MQRCCF_CFIF_OPERATOR_ERROR]="CfifOperatorError";
	hmReasonName[MQRCCF_CFIF_PARM_ID_ERROR]="CfifParmIdError";
	hmReasonName[MQRCCF_CFSF_FILTER_VAL_LEN_ERR]="CfsfFilterValLenErrErr";
	hmReasonName[MQRCCF_CFSF_LENGTH_ERROR]="CfsfLengthError";
	hmReasonName[MQRCCF_CFSF_OPERATOR_ERROR]="CfsfOperatorError";
	hmReasonName[MQRCCF_CFSF_PARM_ID_ERROR]="CfsfParmIdError";
	hmReasonName[MQRCCF_TOO_MANY_FILTERS]="TooManyFilters";
	hmReasonName[MQRCCF_LISTENER_RUNNING]="ListenerRunning";
	hmReasonName[MQRCCF_LSTR_STATUS_NOT_FOUND]="LstrStatusNotFound";
	hmReasonName[MQRCCF_SERVICE_RUNNING]="ServiceRunning";
	hmReasonName[MQRCCF_SERV_STATUS_NOT_FOUND]="ServStatusNotFound";
	hmReasonName[MQRCCF_SERVICE_STOPPED]="ServiceStopped";
	hmReasonName[MQRCCF_CFBS_DUPLICATE_PARM]="CfbsDuplicateParm";
	hmReasonName[MQRCCF_CFBS_LENGTH_ERROR]="CfbsLengthError";
	hmReasonName[MQRCCF_CFBS_PARM_ID_ERROR]="CfbsParmIdError";
	hmReasonName[MQRCCF_CFBS_STRING_LENGTH_ERR]="CfbsStringLengthErr";
	hmReasonName[MQRCCF_CFGR_LENGTH_ERROR]="CfgrLengthError";
	hmReasonName[MQRCCF_CFGR_PARM_COUNT_ERROR]="CfgrParmCountError";
	hmReasonName[MQRCCF_CONN_NOT_STOPPED]="ConnNotStopped";
	hmReasonName[MQRCCF_SERVICE_REQUEST_PENDING]="ServiceRequestPending";
	hmReasonName[MQRCCF_NO_START_CMD]="NoStartCmd";
	hmReasonName[MQRCCF_NO_STOP_CMD]="NoStopCmd";
	hmReasonName[MQRCCF_CFBF_LENGTH_ERROR]="CfbfLengthError";
	hmReasonName[MQRCCF_CFBF_PARM_ID_ERROR]="CfbfParmIdError";
	hmReasonName[MQRCCF_CFBF_OPERATOR_ERROR]="CfbfOperatorError";
	hmReasonName[MQRCCF_CFBF_FILTER_VAL_LEN_ERR]="CfbfFilterValLenErrErr";
	hmReasonName[MQRCCF_LISTENER_STILL_ACTIVE]="ListenerStillActive";
	hmReasonName[MQRCCF_DEF_XMIT_Q_CLUS_ERROR]="DefXmitQClusErrorError";
	hmReasonName[MQRCCF_TOPICSTR_ALREADY_EXISTS]="TopicstrAlreadyExists";
	hmReasonName[MQRCCF_SHARING_CONVS_ERROR]="SharingConvsError";
	hmReasonName[MQRCCF_SHARING_CONVS_TYPE]="SharingConvsType";
	hmReasonName[MQRCCF_SECURITY_CASE_CONFLICT]="SecurityCaseConflict";
	hmReasonName[MQRCCF_TOPIC_TYPE_ERROR]="TopicTypeError";
	hmReasonName[MQRCCF_MAX_INSTANCES_ERROR]="MaxInstancesError";
	hmReasonName[MQRCCF_MAX_INSTS_PER_CLNT_ERR]="MaxInstsPerClntErrErr";
	hmReasonName[MQRCCF_TOPIC_STRING_NOT_FOUND]="TopicStringNotFound";
	hmReasonName[MQRCCF_SUBSCRIPTION_POINT_ERR]="SubscriptionPointErr";
	hmReasonName[MQRCCF_SUB_ALREADY_EXISTS]="SubAlreadyExists";
	hmReasonName[MQRCCF_UNKNOWN_OBJECT_NAME]="UnknownObjectName";
	hmReasonName[MQRCCF_REMOTE_Q_NAME_ERROR]="RemoteQNameError";
	hmReasonName[MQRCCF_DURABILITY_NOT_ALLOWED]="DurabilityNotAllowed";
	hmReasonName[MQRCCF_HOBJ_ERROR]="HobjError";
	hmReasonName[MQRCCF_DEST_NAME_ERROR]="DestNameError";
	hmReasonName[MQRCCF_INVALID_DESTINATION]="InvalidDestination";
	hmReasonName[MQRCCF_PUBSUB_INHIBITED]="PubsubInhibited";
	hmReasonName[MQRCCF_GROUPUR_CHECKS_FAILED]="GroupurChecksFailed";
	hmReasonName[MQRCCF_COMM_INFO_TYPE_ERROR]="CommInfoTypeError";
	hmReasonName[MQRCCF_USE_CLIENT_ID_ERROR]="UseClientIdError";
	hmReasonName[MQRCCF_CLIENT_ID_NOT_FOUND]="ClientIdNotFound";
	hmReasonName[MQRCCF_CLIENT_ID_ERROR]="ClientIdError";
	hmReasonName[MQRCCF_PORT_IN_USE]="PortInUse";
	hmReasonName[MQRCCF_SSL_ALT_PROVIDER_REQD]="SslAltProviderReqd";
	hmReasonName[MQRCCF_CHLAUTH_TYPE_ERROR]="ChlauthTypeError";
	hmReasonName[MQRCCF_CHLAUTH_ACTION_ERROR]="ChlauthActionError";
	hmReasonName[MQRCCF_POLICY_NOT_FOUND]="PolicyNotFound";
	hmReasonName[MQRCCF_ENCRYPTION_ALG_ERROR]="EncryptionAlgError";
	hmReasonName[MQRCCF_SIGNATURE_ALG_ERROR]="SignatureAlgError";
	hmReasonName[MQRCCF_TOLERATION_POL_ERROR]="TolerationPolError";
	hmReasonName[MQRCCF_POLICY_VERSION_ERROR]="PolicyVersionError";
	hmReasonName[MQRCCF_RECIPIENT_DN_MISSING]="RecipientDnMissing";
	hmReasonName[MQRCCF_POLICY_NAME_MISSING]="PolicyNameMissing";
	hmReasonName[MQRCCF_CHLAUTH_USERSRC_ERROR]="ChlauthUsersrcError";
	hmReasonName[MQRCCF_WRONG_CHLAUTH_TYPE]="WrongChlauthType";
	hmReasonName[MQRCCF_CHLAUTH_ALREADY_EXISTS]="ChlauthAlreadyExists";
	hmReasonName[MQRCCF_CHLAUTH_NOT_FOUND]="ChlauthNotFound";
	hmReasonName[MQRCCF_WRONG_CHLAUTH_ACTION]="WrongChlauthAction";
	hmReasonName[MQRCCF_WRONG_CHLAUTH_USERSRC]="WrongChlauthUsersrc";
	hmReasonName[MQRCCF_CHLAUTH_WARN_ERROR]="ChlauthWarnError";
	hmReasonName[MQRCCF_WRONG_CHLAUTH_MATCH]="WrongChlauthMatch";
	hmReasonName[MQRCCF_IPADDR_RANGE_CONFLICT]="IpaddrRangeConflict";
	hmReasonName[MQRCCF_CHLAUTH_MAX_EXCEEDED]="ChlauthMaxExceeded";
	hmReasonName[MQRCCF_IPADDR_ERROR]="IpaddrError";
	hmReasonName[MQRCCF_IPADDR_RANGE_ERROR]="IpaddrRangeError";
	hmReasonName[MQRCCF_PROFILE_NAME_MISSING]="ProfileNameMissing";
	hmReasonName[MQRCCF_CHLAUTH_CLNTUSER_ERROR]="ChlauthClntuserError";
	hmReasonName[MQRCCF_CHLAUTH_NAME_ERROR]="ChlauthNameError";
	hmReasonName[MQRCCF_CHLAUTH_RUNCHECK_ERROR]="ChlauthRuncheckError";
	hmReasonName[MQRCCF_CF_STRUC_ALREADY_FAILED]="CfStrucAlreadyFailed";
	hmReasonName[MQRCCF_CFCONLOS_CHECKS_FAILED]="CfconlosChecksFailed";
	hmReasonName[MQRCCF_SUITE_B_ERROR]="SuiteBError";
	hmReasonName[MQRCCF_CHANNEL_NOT_STARTED]="ChannelNotStarted";
	hmReasonName[MQRCCF_CUSTOM_ERROR]="CustomError";
	hmReasonName[MQRCCF_BACKLOG_OUT_OF_RANGE]="BacklogOutOfRange";
	hmReasonName[MQRCCF_CHLAUTH_DISABLED]="ChlauthDisabled";
	hmReasonName[MQRCCF_SMDS_REQUIRES_DSGROUP]="SmdsRequiresDsgroup";
	hmReasonName[MQRCCF_PSCLUS_DISABLED_TOPDEF]="PsclusDisabledTopdef";
	hmReasonName[MQRCCF_PSCLUS_TOPIC_EXISTS]="PsclusTopicExists";
	hmReasonName[MQRCCF_SSL_CIPHER_SUITE_ERROR]="SslCipherSuiteError";
	hmReasonName[MQRCCF_SOCKET_ERROR]="SocketError";
	hmReasonName[MQRCCF_CLUS_XMIT_Q_USAGE_ERROR]="ClusXmitQUsageErrorError";
	hmReasonName[MQRCCF_CERT_VAL_POLICY_ERROR]="CertValPolicyError";
	hmReasonName[MQRCCF_OBJECT_ALREADY_EXISTS]="ObjectAlreadyExists";
	hmReasonName[MQRCCF_OBJECT_WRONG_TYPE]="ObjectWrongType";
	hmReasonName[MQRCCF_LIKE_OBJECT_WRONG_TYPE]="LikeObjectWrongType";
	hmReasonName[MQRCCF_OBJECT_OPEN]="ObjectOpen";
	hmReasonName[MQRCCF_ATTR_VALUE_ERROR]="AttrValueError";
	hmReasonName[MQRCCF_UNKNOWN_Q_MGR]="UnknownQMgr";
	hmReasonName[MQRCCF_Q_WRONG_TYPE]="QWrongType";
	hmReasonName[MQRCCF_OBJECT_NAME_ERROR]="ObjectNameError";
	hmReasonName[MQRCCF_ALLOCATE_FAILED]="AllocateFailed";
	hmReasonName[MQRCCF_HOST_NOT_AVAILABLE]="HostNotAvailable";
	hmReasonName[MQRCCF_CONFIGURATION_ERROR]="ConfigurationError";
	hmReasonName[MQRCCF_CONNECTION_REFUSED]="ConnectionRefused";
	hmReasonName[MQRCCF_ENTRY_ERROR]="EntryError";
	hmReasonName[MQRCCF_SEND_FAILED]="SendFailed";
	hmReasonName[MQRCCF_RECEIVED_DATA_ERROR]="ReceivedDataError";
	hmReasonName[MQRCCF_RECEIVE_FAILED]="ReceiveFailed";
	hmReasonName[MQRCCF_CONNECTION_CLOSED]="ConnectionClosed";
	hmReasonName[MQRCCF_NO_STORAGE]="NoStorage";
	hmReasonName[MQRCCF_NO_COMMS_MANAGER]="NoCommsManager";
	hmReasonName[MQRCCF_LISTENER_NOT_STARTED]="ListenerNotStarted";
	hmReasonName[MQRCCF_BIND_FAILED]="BindFailed";
	hmReasonName[MQRCCF_CHANNEL_INDOUBT]="ChannelIndoubt";
	hmReasonName[MQRCCF_MQCONN_FAILED]="MqconnFailed";
	hmReasonName[MQRCCF_MQOPEN_FAILED]="MqopenFailed";
	hmReasonName[MQRCCF_MQGET_FAILED]="MqgetFailed";
	hmReasonName[MQRCCF_MQPUT_FAILED]="MqputFailed";
	hmReasonName[MQRCCF_PING_ERROR]="PingError";
	hmReasonName[MQRCCF_CHANNEL_IN_USE]="ChannelInUse";
	hmReasonName[MQRCCF_CHANNEL_NOT_FOUND]="ChannelNotFound";
	hmReasonName[MQRCCF_UNKNOWN_REMOTE_CHANNEL]="UnknownRemoteChannel";
	hmReasonName[MQRCCF_REMOTE_QM_UNAVAILABLE]="RemoteQmUnavailable";
	hmReasonName[MQRCCF_REMOTE_QM_TERMINATING]="RemoteQmTerminating";
	hmReasonName[MQRCCF_MQINQ_FAILED]="MqinqFailed";
	hmReasonName[MQRCCF_NOT_XMIT_Q]="NotXmitQ";
	hmReasonName[MQRCCF_CHANNEL_DISABLED]="ChannelDisabled";
	hmReasonName[MQRCCF_USER_EXIT_NOT_AVAILABLE]="UserExitNotAvailable";
	hmReasonName[MQRCCF_COMMIT_FAILED]="CommitFailed";
	hmReasonName[MQRCCF_WRONG_CHANNEL_TYPE]="WrongChannelType";
	hmReasonName[MQRCCF_CHANNEL_ALREADY_EXISTS]="ChannelAlreadyExists";
	hmReasonName[MQRCCF_DATA_TOO_LARGE]="DataTooLarge";
	hmReasonName[MQRCCF_CHANNEL_NAME_ERROR]="ChannelNameError";
	hmReasonName[MQRCCF_XMIT_Q_NAME_ERROR]="XmitQNameError";
	hmReasonName[MQRCCF_MCA_NAME_ERROR]="MCANameError";
	hmReasonName[MQRCCF_SEND_EXIT_NAME_ERROR]="SendExitNameError";
	hmReasonName[MQRCCF_SEC_EXIT_NAME_ERROR]="SecExitNameError";
	hmReasonName[MQRCCF_MSG_EXIT_NAME_ERROR]="MsgExitNameError";
	hmReasonName[MQRCCF_RCV_EXIT_NAME_ERROR]="RcvExitNameError";
	hmReasonName[MQRCCF_XMIT_Q_NAME_WRONG_TYPE]="XmitQNameWrongTypeType";
	hmReasonName[MQRCCF_MCA_NAME_WRONG_TYPE]="MCANameWrongType";
	hmReasonName[MQRCCF_DISC_INT_WRONG_TYPE]="DiscIntWrongType";
	hmReasonName[MQRCCF_SHORT_RETRY_WRONG_TYPE]="ShortRetryWrongType";
	hmReasonName[MQRCCF_SHORT_TIMER_WRONG_TYPE]="ShortTimerWrongType";
	hmReasonName[MQRCCF_LONG_RETRY_WRONG_TYPE]="LongRetryWrongType";
	hmReasonName[MQRCCF_LONG_TIMER_WRONG_TYPE]="LongTimerWrongType";
	hmReasonName[MQRCCF_PUT_AUTH_WRONG_TYPE]="PutAuthWrongType";
	hmReasonName[MQRCCF_KEEP_ALIVE_INT_ERROR]="KeepAliveIntError";
	hmReasonName[MQRCCF_MISSING_CONN_NAME]="MissingConnName";
	hmReasonName[MQRCCF_CONN_NAME_ERROR]="ConnNameError";
	hmReasonName[MQRCCF_MQSET_FAILED]="MqsetFailed";
	hmReasonName[MQRCCF_CHANNEL_NOT_ACTIVE]="ChannelNotActive";
	hmReasonName[MQRCCF_TERMINATED_BY_SEC_EXIT]="TerminatedBySecExit";
	hmReasonName[MQRCCF_DYNAMIC_Q_SCOPE_ERROR]="DynamicQScopeError";
	hmReasonName[MQRCCF_CELL_DIR_NOT_AVAILABLE]="CellDirNotAvailable";
	hmReasonName[MQRCCF_MR_COUNT_ERROR]="MrCountError";
	hmReasonName[MQRCCF_MR_COUNT_WRONG_TYPE]="MrCountWrongType";
	hmReasonName[MQRCCF_MR_EXIT_NAME_ERROR]="MrExitNameError";
	hmReasonName[MQRCCF_MR_EXIT_NAME_WRONG_TYPE]="MrExitNameWrongTypeType";
	hmReasonName[MQRCCF_MR_INTERVAL_ERROR]="MrIntervalError";
	hmReasonName[MQRCCF_MR_INTERVAL_WRONG_TYPE]="MrIntervalWrongType";
	hmReasonName[MQRCCF_NPM_SPEED_ERROR]="NpmSpeedError";
	hmReasonName[MQRCCF_NPM_SPEED_WRONG_TYPE]="NpmSpeedWrongType";
	hmReasonName[MQRCCF_HB_INTERVAL_ERROR]="HbIntervalError";
	hmReasonName[MQRCCF_HB_INTERVAL_WRONG_TYPE]="HbIntervalWrongType";
	hmReasonName[MQRCCF_CHAD_ERROR]="ChadError";
	hmReasonName[MQRCCF_CHAD_WRONG_TYPE]="ChadWrongType";
	hmReasonName[MQRCCF_CHAD_EVENT_ERROR]="ChadEventError";
	hmReasonName[MQRCCF_CHAD_EVENT_WRONG_TYPE]="ChadEventWrongType";
	hmReasonName[MQRCCF_CHAD_EXIT_ERROR]="ChadExitError";
	hmReasonName[MQRCCF_CHAD_EXIT_WRONG_TYPE]="ChadExitWrongType";
	hmReasonName[MQRCCF_SUPPRESSED_BY_EXIT]="SuppressedByExit";
	hmReasonName[MQRCCF_BATCH_INT_ERROR]="BatchIntError";
	hmReasonName[MQRCCF_BATCH_INT_WRONG_TYPE]="BatchIntWrongType";
	hmReasonName[MQRCCF_NET_PRIORITY_ERROR]="NetPriorityError";
	hmReasonName[MQRCCF_NET_PRIORITY_WRONG_TYPE]="NetPriorityWrongType";
	hmReasonName[MQRCCF_CHANNEL_CLOSED]="ChannelClosed";
	hmReasonName[MQRCCF_Q_STATUS_NOT_FOUND]="QStatusNotFound";
	hmReasonName[MQRCCF_SSL_CIPHER_SPEC_ERROR]="SslCipherSpecError";
	hmReasonName[MQRCCF_SSL_PEER_NAME_ERROR]="SslPeerNameError";
	hmReasonName[MQRCCF_SSL_CLIENT_AUTH_ERROR]="SslClientAuthError";
	hmReasonName[MQRCCF_RETAINED_NOT_SUPPORTED]="RetainedNotSupported";
}
/*************************************************************************/
}
}
}
}
