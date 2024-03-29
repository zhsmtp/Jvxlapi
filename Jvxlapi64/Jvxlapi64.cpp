// Jvxlapi64.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "vxlapi.h"
#include "can_interfaces_vector_jni_Jvxlapi.h"


#ifdef __cplusplus
extern "C" {
#endif

	JNIEXPORT jint JNICALL Java_can_interfaces_vector_jni_Jvxlapi_xlOpenDriver
	(JNIEnv *, jclass) {
		return xlOpenDriver();
	}

	JNIEXPORT jint JNICALL Java_can_interfaces_vector_jni_Jvxlapi_xlCloseDriver
	(JNIEnv *, jclass) {
		return xlCloseDriver();
	}

	JNIEXPORT jint JNICALL Java_can_interfaces_vector_jni_Jvxlapi_xlGetDriverConfig
	(JNIEnv *env, jclass, jobject jDriverConfig) {
		XLdriverConfig pDriverConfig;
		jint ret = xlGetDriverConfig(&pDriverConfig);
		jclass jc = env->GetObjectClass(jDriverConfig);


		jfieldID fieldID = env->GetFieldID(jc, "channelCount", "I");
		env->SetIntField(jDriverConfig, fieldID, pDriverConfig.channelCount);

		fieldID = env->GetFieldID(jc, "dllVersion", "I");
		env->SetIntField(jDriverConfig, fieldID, pDriverConfig.dllVersion);

		//read channel info Lcan/interfaces/vector/jni/XLdriverConfig
		fieldID = env->GetFieldID(jc, "channel", "[Lcan/interfaces/vector/jni/XLchannelConfig;");
		jobject channels = env->GetObjectField(jDriverConfig, fieldID);
		jclass jcXLchannelConfig = env->FindClass("Lcan/interfaces/vector/jni/XLchannelConfig;");

		for (unsigned int i = 0; i < pDriverConfig.channelCount; i++) {
			
			jobject chi = env->GetObjectArrayElement((jobjectArray)channels, i);

			fieldID = env->GetFieldID(jcXLchannelConfig, "hwType", "I");
			env->SetIntField(chi, fieldID, pDriverConfig.channel[i].hwType);

			fieldID = env->GetFieldID(jcXLchannelConfig, "hwIndex", "I");
			env->SetIntField(chi, fieldID, pDriverConfig.channel[i].hwIndex);

			fieldID = env->GetFieldID(jcXLchannelConfig, "hwChannel", "I");
			env->SetIntField(chi, fieldID, pDriverConfig.channel[i].hwChannel);

			fieldID = env->GetFieldID(jcXLchannelConfig, "transceiverType", "I");
			env->SetIntField(chi, fieldID, pDriverConfig.channel[i].transceiverType);

			fieldID = env->GetFieldID(jcXLchannelConfig, "configError", "I");
			env->SetIntField(chi, fieldID, pDriverConfig.channel[i].configError);

			fieldID = env->GetFieldID(jcXLchannelConfig, "channelIndex", "I");
			env->SetIntField(chi, fieldID, pDriverConfig.channel[i].channelIndex);

			fieldID = env->GetFieldID(jcXLchannelConfig, "channelMask", "J");
			env->SetLongField(chi, fieldID, pDriverConfig.channel[i].channelMask);

			fieldID = env->GetFieldID(jcXLchannelConfig, "channelCapabilities", "I");
			env->SetIntField(chi, fieldID, pDriverConfig.channel[i].channelCapabilities);

			fieldID = env->GetFieldID(jcXLchannelConfig, "channelBusCapabilities", "I");
			env->SetIntField(chi, fieldID, pDriverConfig.channel[i].channelBusCapabilities);

			fieldID = env->GetFieldID(jcXLchannelConfig, "isOnBus", "I");
			env->SetIntField(chi, fieldID, pDriverConfig.channel[i].isOnBus);

			fieldID = env->GetFieldID(jcXLchannelConfig, "connectedBusType", "I");
			env->SetIntField(chi, fieldID, pDriverConfig.channel[i].connectedBusType);

			jclass jcXLbusParamsCan = env->FindClass("Lcan/interfaces/vector/jni/XLbusParamsCan;");
			fieldID = env->GetFieldID(jcXLchannelConfig, "busParams", "Lcan/interfaces/vector/jni/XLbusParamsCan;");
			jobject busParamsCan = env->GetObjectField(chi, fieldID);

			fieldID = env->GetFieldID(jcXLbusParamsCan, "bitRate", "I");
			env->SetIntField(busParamsCan, fieldID, pDriverConfig.channel[i].busParams.data.can.bitRate);
			fieldID = env->GetFieldID(jcXLbusParamsCan, "sjw", "I");
			env->SetIntField(busParamsCan, fieldID, pDriverConfig.channel[i].busParams.data.can.sjw);
			fieldID = env->GetFieldID(jcXLbusParamsCan, "tseg1", "I");
			env->SetIntField(busParamsCan, fieldID, pDriverConfig.channel[i].busParams.data.can.tseg1);
			fieldID = env->GetFieldID(jcXLbusParamsCan, "tseg2", "I");
			env->SetIntField(busParamsCan, fieldID, pDriverConfig.channel[i].busParams.data.can.tseg2);
			fieldID = env->GetFieldID(jcXLbusParamsCan, "sam", "I");
			env->SetIntField(busParamsCan, fieldID, pDriverConfig.channel[i].busParams.data.can.sam);
			fieldID = env->GetFieldID(jcXLbusParamsCan, "outputMode", "I");
			env->SetIntField(busParamsCan, fieldID, pDriverConfig.channel[i].busParams.data.can.outputMode);
			fieldID = env->GetFieldID(jcXLbusParamsCan, "canOpMode", "I");
			env->SetIntField(busParamsCan, fieldID, pDriverConfig.channel[i].busParams.data.can.canOpMode);

		}




		return ret;
	}

	JNIEXPORT jint JNICALL Java_can_interfaces_vector_jni_Jvxlapi_xlGetApplConfig
	(JNIEnv *env, jclass obj, jstring appName, jint appChannel, jintArray pHwType, jintArray pHwIndex, jintArray pHwChannel, jint busType) {
		jint ret;
		const char *str = env->GetStringUTFChars(appName, 0);
		unsigned int hwType;
		unsigned int hwIndex;
		unsigned int hwChannel;
		ret = xlGetApplConfig((char*)str, appChannel, &hwType, &hwIndex, &hwChannel, busType);
		env->SetIntArrayRegion(pHwType, 0,1, (const jint*)&hwType);
		env->SetIntArrayRegion(pHwIndex, 0, 1, (const jint*)&hwIndex);
		env->SetIntArrayRegion(pHwChannel, 0, 1, (const jint*)&hwChannel);
		env->ReleaseStringUTFChars(appName, str);
		return ret;
	}

	JNIEXPORT jint JNICALL Java_can_interfaces_vector_jni_Jvxlapi_xlGetChannelIndex
	(JNIEnv *, jclass, jint hwType, jint hwIndex, jint hwChannel) {
		return xlGetChannelIndex(hwType, hwIndex, hwChannel);
	}

	JNIEXPORT jint JNICALL Java_can_interfaces_vector_jni_Jvxlapi_xlOpenPort
	(JNIEnv *env, jclass, jlongArray portHandle, jstring userName, jlong accessMask, jlongArray permissionMask, jint rxQueueSize, jint xlInterfaceVersion, jint busType) {
		jint ret;
		XLportHandle pHandle= XL_INVALID_PORTHANDLE;
		jlong pmj;
		env->GetLongArrayRegion(permissionMask, 0, 1, &pmj);
		XLaccess Mask= pmj;
		const char *str = env->GetStringUTFChars(userName, 0);

		ret = xlOpenPort(&pHandle, (char*)str, accessMask, &Mask, rxQueueSize, xlInterfaceVersion, busType);

		env->SetLongArrayRegion(portHandle, 0, 1, (const jlong*)&pHandle);
		env->SetLongArrayRegion(permissionMask, 0, 1, (const jlong*)&Mask);

		env->ReleaseStringUTFChars(userName, str);
		return ret;
	}

	JNIEXPORT jint JNICALL Java_can_interfaces_vector_jni_Jvxlapi_xlGetSyncTime
	(JNIEnv *env, jclass, jlong portHandle, jlongArray time) {
		jint ret;
		XLuint64 retTime;
		ret = xlGetSyncTime((XLportHandle)portHandle, &retTime);
		env->SetLongArrayRegion(time, 0, 1, (const jlong*)&retTime);
		return ret;
	}

	JNIEXPORT jint JNICALL Java_can_interfaces_vector_jni_Jvxlapi_xlClosePort
	(JNIEnv *, jclass, jlong portHandle) {
		return xlClosePort((XLportHandle)portHandle);
	}

	JNIEXPORT jint JNICALL Java_can_interfaces_vector_jni_Jvxlapi_xlSetNotification
	(JNIEnv *env, jclass, jlong portHandle, jlongArray handle, jint queueLevel) {
		jint ret;
		XLhandle pHandle;
		ret = xlSetNotification((XLportHandle)portHandle, &pHandle, queueLevel);
		env->SetLongArrayRegion(handle, 0, 1, (const jlong*)&pHandle);
		return ret;
	}

	JNIEXPORT jint JNICALL Java_can_interfaces_vector_jni_Jvxlapi_xlCanSetChannelMode
	(JNIEnv *, jclass, jlong portHandle, jlong accessMask, jint tx, jint txrq) {
		return xlCanSetChannelMode((XLportHandle)portHandle, accessMask, tx, txrq);
	}

	JNIEXPORT jint JNICALL Java_can_interfaces_vector_jni_Jvxlapi_xlActivateChannel
	(JNIEnv *, jclass, jlong portHandle, jlong accessMask, jint busType, jint flags) {
		return xlActivateChannel((XLportHandle)portHandle, accessMask, busType, flags);
	}

	JNIEXPORT jint JNICALL Java_can_interfaces_vector_jni_Jvxlapi_xlDeactivateChannel
	(JNIEnv *, jclass, jlong portHandle, jlong accessMask) {
		return xlDeactivateChannel((XLportHandle)portHandle, accessMask);
	}

	JNIEXPORT jint JNICALL Java_can_interfaces_vector_jni_Jvxlapi_xlCanFdSetConfiguration
	(JNIEnv *env, jclass, jlong portHandle, jlong accessMask, jobject pCanFdConf) {
		XLcanFdConf CanFdConf;
		jclass jc = env->FindClass("Lcan/interfaces/vector/jni/XLcanFdConf;");
		jfieldID fid = env->GetFieldID(jc, "arbitrationBitRate", "I");
		CanFdConf.arbitrationBitRate = env->GetIntField(pCanFdConf, fid);

		fid = env->GetFieldID(jc, "dataBitRate", "I");
		CanFdConf.dataBitRate = env->GetIntField(pCanFdConf, fid);
		fid = env->GetFieldID(jc, "sjwAbr", "I");
		CanFdConf.sjwAbr = env->GetIntField(pCanFdConf, fid);
		fid = env->GetFieldID(jc, "sjwDbr", "I");
		CanFdConf.sjwDbr = env->GetIntField(pCanFdConf, fid);
		fid = env->GetFieldID(jc, "tseg1Abr", "I");
		CanFdConf.tseg1Abr = env->GetIntField(pCanFdConf, fid);
		fid = env->GetFieldID(jc, "tseg1Dbr", "I");
		CanFdConf.tseg1Dbr = env->GetIntField(pCanFdConf, fid);
		fid = env->GetFieldID(jc, "tseg2Abr", "I");
		CanFdConf.tseg2Abr = env->GetIntField(pCanFdConf, fid);
		fid = env->GetFieldID(jc, "tseg2Dbr", "I");
		CanFdConf.tseg2Dbr = env->GetIntField(pCanFdConf, fid);

		return xlCanFdSetConfiguration((XLportHandle)portHandle, accessMask, &CanFdConf);
	}
	
	JNIEXPORT jint JNICALL Java_can_interfaces_vector_jni_Jvxlapi_xlReceive
	(JNIEnv *env, jclass, jlong portHandle, jintArray pEventCount, jobjectArray pEventList) {
		jint ret;		
		jint ecj;
		env->GetIntArrayRegion(pEventCount, 0, 1, &ecj);
		unsigned int ec = ecj;
		XLevent *Events = new XLevent[ec];

		ret = xlReceive((XLportHandle)portHandle, &ec, Events);

		env->SetIntArrayRegion(pEventCount, 0, 1, (const jint*)&ec);
		jclass jcEvent = env->FindClass("Lcan/interfaces/vector/jni/XLevent;");
		jclass jcs_xl_can_msg = env->FindClass("Lcan/interfaces/vector/jni/s_xl_can_msg;");
		jmethodID jmcEvent = env->GetMethodID(jcEvent, "<init>", "()V");
		jfieldID fieldID;
		if (ec > 1)printf("!!!!!!receive more than 1 msg\n");
		for (unsigned int i = 0; i < ec; i++) {
			//create a new object Ev
			jobject Ev = env->NewObject(jcEvent, jmcEvent);
			//assign values from Events[i] to Ev
			fieldID = env->GetFieldID(jcEvent, "tag", "I");
			env->SetIntField(Ev, fieldID, Events->tag);
			fieldID = env->GetFieldID(jcEvent, "chanIndex", "I");
			env->SetIntField(Ev, fieldID, Events->chanIndex);
			fieldID = env->GetFieldID(jcEvent, "transId", "I");
			env->SetIntField(Ev, fieldID, Events->transId);
			fieldID = env->GetFieldID(jcEvent, "portHandle", "I");
			env->SetIntField(Ev, fieldID, Events->portHandle);
			fieldID = env->GetFieldID(jcEvent, "flags", "I");
			env->SetIntField(Ev, fieldID, Events->flags);
			fieldID = env->GetFieldID(jcEvent, "timeStamp", "J");
			env->SetLongField(Ev, fieldID, Events->timeStamp);

			fieldID = env->GetFieldID(jcEvent, "tagData", "Lcan/interfaces/vector/jni/s_xl_can_msg;");
			jobject ev_tagData = env->GetObjectField(Ev, fieldID);
			fieldID = env->GetFieldID(jcs_xl_can_msg, "id", "J");
			env->SetLongField(ev_tagData, fieldID, Events->tagData.msg.id);
			fieldID = env->GetFieldID(jcs_xl_can_msg, "flags", "I");
			env->SetIntField(ev_tagData, fieldID, Events->tagData.msg.flags);
			fieldID = env->GetFieldID(jcs_xl_can_msg, "dlc", "I");
			env->SetIntField(ev_tagData, fieldID, Events->tagData.msg.dlc);

			fieldID = env->GetFieldID(jcs_xl_can_msg, "data", "[B");
			jbyteArray jba = (jbyteArray)env->GetObjectField(ev_tagData, fieldID);
			env->SetByteArrayRegion(jba, 0, 8, (const jbyte*)Events->tagData.msg.data);

			// let pEventList[i] = Ev;
			env->SetObjectArrayElement(pEventList, i, Ev);
			//Events++;
		}

		delete[] Events;
		return ret;
	}

	JNIEXPORT jint JNICALL Java_can_interfaces_vector_jni_Jvxlapi_xlCanReceive
	(JNIEnv *env, jclass, jlong portHandle, jobject pXlCanRxEvt) {
		jint ret=0;
		XLcanRxEvent *XlCanRxEvt=new XLcanRxEvent;

		//once xlCanReceive or xlCanTransmitEx called, Java will report
		// Exception in thread "main" java.lang.UnsatisfiedLinkError: C:\zhou\java-canstack\j-can\Jvxlapi64.dll: The specified procedure could not be found
		//ret = xlCanReceive((XLportHandle)portHandle, XlCanRxEvt);
/*
		jclass jc = env->FindClass("Lcan/interfaces/vector/jni/XLcanRxEvent;");
		jmethodID jmc = env->GetMethodID(jc, "<init>", "()V");
		pXlCanRxEvt = env->NewObject(jc, jmc);

		jfieldID fieldID;
		fieldID = env->GetFieldID(jc, "size", "I");
		env->SetIntField(pXlCanRxEvt, fieldID, XlCanRxEvt->size);
		fieldID = env->GetFieldID(jc, "tag", "I");
		env->SetIntField(pXlCanRxEvt, fieldID, XlCanRxEvt->tag);
		fieldID = env->GetFieldID(jc, "channelIndex", "I");
		env->SetIntField(pXlCanRxEvt, fieldID, XlCanRxEvt->channelIndex);
		fieldID = env->GetFieldID(jc, "userHandle", "I");
		env->SetIntField(pXlCanRxEvt, fieldID, XlCanRxEvt->userHandle);
		fieldID = env->GetFieldID(jc, "flagsChip", "I");
		env->SetIntField(pXlCanRxEvt, fieldID, XlCanRxEvt->flagsChip);
		fieldID = env->GetFieldID(jc, "timeStampSync", "J");
		env->SetLongField(pXlCanRxEvt, fieldID, XlCanRxEvt->timeStampSync);

		jclass jcMsg = env->FindClass("Lcan/interfaces/vector/jni/XL_CAN_EV_RX_MSG;");
		fieldID = env->GetFieldID(jc, "timeStampSync", "J");
		jobject msg = env->GetObjectField(pXlCanRxEvt, fieldID);

		if (XL_CAN_EV_TAG_RX_OK == XlCanRxEvt->tag || XL_CAN_EV_TAG_TX_OK == XlCanRxEvt->tag) {
			fieldID = env->GetFieldID(jcMsg, "canId", "I");
			env->SetIntField(msg, fieldID, XlCanRxEvt->tagData.canRxOkMsg.canId);
			fieldID = env->GetFieldID(jcMsg, "msgFlags", "I");
			env->SetIntField(msg, fieldID, XlCanRxEvt->tagData.canRxOkMsg.msgFlags);
			fieldID = env->GetFieldID(jcMsg, "crc", "I");
			env->SetIntField(msg, fieldID, XlCanRxEvt->tagData.canRxOkMsg.crc);
			fieldID = env->GetFieldID(jcMsg, "totalBitCnt", "I");
			env->SetIntField(msg, fieldID, XlCanRxEvt->tagData.canRxOkMsg.totalBitCnt);
			fieldID = env->GetFieldID(jcMsg, "dlc", "I");
			env->SetIntField(msg, fieldID, XlCanRxEvt->tagData.canRxOkMsg.dlc);

			fieldID = env->GetFieldID(jcMsg, "data", "[B");
			jbyteArray jba = (jbyteArray)env->GetObjectField(msg, fieldID);
			env->SetByteArrayRegion(jba, 0, 8, (const jbyte*)XlCanRxEvt->tagData.canRxOkMsg.data);
		}
		delete XlCanRxEvt;*/
		return ret;
	}

	JNIEXPORT jstring JNICALL Java_can_interfaces_vector_jni_Jvxlapi_xlGetErrorString
	(JNIEnv *env, jclass, jint err) {
		XLstringType retStr;
		retStr = xlGetErrorString(err);
		jclass strClass = (env)->FindClass("Ljava/lang/String;");
		jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([B)V");
		jbyteArray bytes = (env)->NewByteArray(strlen(retStr));
		(env)->SetByteArrayRegion(bytes, 0, strlen(retStr), (jbyte*)retStr);
		return (jstring)(env)->NewObject(strClass, ctorID, bytes);
	}

	JNIEXPORT jint JNICALL Java_can_interfaces_vector_jni_Jvxlapi_xlCanSetChannelBitrate
	(JNIEnv *, jclass, jlong portHandle, jlong accessMask, jlong bitrate) {
		return xlCanSetChannelBitrate(portHandle, accessMask, bitrate);
	}
	
	JNIEXPORT jint JNICALL Java_can_interfaces_vector_jni_Jvxlapi_xlCanTransmit
	(JNIEnv *env, jclass, jlong portHandle, jlong accessMask, jintArray messageCount, jobjectArray pMessages) {
		jint ret;
		jfieldID fieldID;
		jint ecj;
		env->GetIntArrayRegion(messageCount, 0, 1, &ecj);
		unsigned int msgCnt=ecj;		
		if (env->GetArrayLength(pMessages) != msgCnt)
			return -1;
		XLevent* pEvents = (XLevent*) new XLevent[msgCnt];
		jclass jcXlevent = env->FindClass("Lcan/interfaces/vector/jni/XLevent;");
		jmethodID jmcXlevent = env->GetMethodID(jcXlevent, "<init>", "()V");
		jclass jcs_xl_can_msg = env->FindClass("Lcan/interfaces/vector/jni/s_xl_can_msg;");
		for (unsigned int i = 0; i < msgCnt; i++) {
			jobject msg = env->GetObjectArrayElement(pMessages, i);
			fieldID = env->GetFieldID(jcXlevent, "tag", "I");
			pEvents[i].tag = env->GetIntField(msg, fieldID);
			fieldID = env->GetFieldID(jcXlevent, "chanIndex", "I");
			pEvents[i].chanIndex = env->GetIntField(msg, fieldID);
			fieldID = env->GetFieldID(jcXlevent, "transId", "I");
			pEvents[i].transId = env->GetIntField(msg, fieldID);
			fieldID = env->GetFieldID(jcXlevent, "portHandle", "I");
			pEvents[i].portHandle = env->GetIntField(msg, fieldID);
			fieldID = env->GetFieldID(jcXlevent, "flags", "I");
			pEvents[i].flags = env->GetIntField(msg, fieldID);
			fieldID = env->GetFieldID(jcXlevent, "timeStamp", "J");
			pEvents[i].timeStamp = env->GetLongField(msg, fieldID);
			fieldID = env->GetFieldID(jcXlevent, "tagData", "Lcan/interfaces/vector/jni/s_xl_can_msg;");
			jobject tagData = env->GetObjectField(msg, fieldID);
			fieldID = env->GetFieldID(jcs_xl_can_msg, "id", "J");
			pEvents[i].tagData.msg.id = env->GetLongField(tagData, fieldID);
			fieldID = env->GetFieldID(jcs_xl_can_msg, "flags", "I");
			pEvents[i].tagData.msg.flags = env->GetIntField(tagData, fieldID);
			fieldID = env->GetFieldID(jcs_xl_can_msg, "dlc", "I");
			pEvents[i].tagData.msg.dlc = env->GetIntField(tagData, fieldID);
			fieldID = env->GetFieldID(jcs_xl_can_msg, "data", "[B");
			jbyteArray jba = (jbyteArray)env->GetObjectField(tagData, fieldID);			
			env->GetByteArrayRegion(jba, 0, 8, (jbyte*)pEvents[i].tagData.msg.data);
		}

		ret = xlCanTransmit(portHandle, accessMask, &msgCnt, pEvents);
		env->SetIntArrayRegion(messageCount, 0, 1, (const jint*)&msgCnt);
		if (msgCnt > 0) {
			pMessages = env->NewObjectArray(msgCnt, jcXlevent, NULL);
			for (unsigned int i = 0; i < msgCnt; i++) {
				jobject Ev = env->NewObject(jcXlevent, jmcXlevent);

				fieldID = env->GetFieldID(jcXlevent, "tag", "I");
				env->SetIntField(Ev, fieldID, pEvents[i].tag);
				fieldID = env->GetFieldID(jcXlevent, "chanIndex", "I");
				env->SetIntField(Ev, fieldID, pEvents[i].chanIndex);
				fieldID = env->GetFieldID(jcXlevent, "transId", "I");
				env->SetIntField(Ev, fieldID, pEvents[i].transId);
				fieldID = env->GetFieldID(jcXlevent, "portHandle", "I");
				env->SetIntField(Ev, fieldID, pEvents[i].portHandle);
				fieldID = env->GetFieldID(jcXlevent, "flags", "I");
				env->SetIntField(Ev, fieldID, pEvents[i].flags);
				fieldID = env->GetFieldID(jcXlevent, "timeStamp", "J");
				env->SetLongField(Ev, fieldID, pEvents[i].timeStamp);

				fieldID = env->GetFieldID(jcXlevent, "tagData", "Lcan/interfaces/vector/jni/s_xl_can_msg;");
				jobject ev_tagData = env->GetObjectField(Ev, fieldID);
				fieldID = env->GetFieldID(jcs_xl_can_msg, "id", "J");
				env->SetLongField(ev_tagData, fieldID, pEvents[i].tagData.msg.id);
				fieldID = env->GetFieldID(jcs_xl_can_msg, "flags", "I");
				env->SetIntField(ev_tagData, fieldID, pEvents[i].tagData.msg.flags);
				fieldID = env->GetFieldID(jcs_xl_can_msg, "dlc", "I");
				env->SetIntField(ev_tagData, fieldID, pEvents[i].tagData.msg.dlc);

				fieldID = env->GetFieldID(jcs_xl_can_msg, "data", "[B");
				jbyteArray jba = (jbyteArray)env->GetObjectField(ev_tagData, fieldID);
				env->SetByteArrayRegion(jba, 0, 8, (const jbyte*)pEvents[i].tagData.msg.data);

				env->SetObjectArrayElement(pMessages, i, Ev);
			}
		}
		else
		{
			pMessages = NULL;
		}



		delete[] pEvents;

		return ret;
	}

	JNIEXPORT jint JNICALL Java_can_interfaces_vector_jni_Jvxlapi_xlCanTransmitEx
	(JNIEnv *env, jclass, jlong portHandle, jlong accessMask, jint msgCnt, jintArray pMsgCntSent, jobjectArray pXlCanTxEvt) {
		jint ret;
		jfieldID fieldID;
		unsigned int MsgCntSent;
		XLcanTxEvent* XlCanTxEvt = new XLcanTxEvent[msgCnt];
		//ret = xlCanTransmitEx(portHandle, accessMask, msgCnt, &MsgCntSent, XlCanTxEvt);
	/*
		env->SetIntArrayRegion(pMsgCntSent, 0, 1, (const jint*)&MsgCntSent);

		jclass jcXlevent = env->FindClass("Lcan/interfaces/vector/jni/XLcanTxEvent;");
		jmethodID jmcXlevent = env->GetMethodID(jcXlevent, "<init>", "()V");
		jclass jcs_xl_can_msg = env->FindClass("Lcan/interfaces/vector/jni/XL_CAN_TX_MSG;");
		if (msgCnt > 0) {
			pXlCanTxEvt = env->NewObjectArray(msgCnt, jcXlevent, NULL);
			for (unsigned int i = 0; i < msgCnt; i++) {
				jobject Ev = env->NewObject(jcXlevent, jmcXlevent);

				fieldID = env->GetFieldID(jcXlevent, "tag", "I");
				env->SetIntField(Ev, fieldID, XlCanTxEvt[i].tag);
				fieldID = env->GetFieldID(jcXlevent, "channelIndex", "I");
				env->SetIntField(Ev, fieldID, XlCanTxEvt[i].channelIndex);
				fieldID = env->GetFieldID(jcXlevent, "transId", "I");
				env->SetIntField(Ev, fieldID, XlCanTxEvt[i].transId);

				fieldID = env->GetFieldID(jcXlevent, "tagData", "Lcan/interfaces/vector/jni/XL_CAN_TX_MSG;");
				jobject ev_tagData = env->GetObjectField(Ev, fieldID);
				fieldID = env->GetFieldID(jcXlevent, "id", "J");
				env->SetLongField(ev_tagData, fieldID, XlCanTxEvt[i].tagData.canMsg.canId);
				fieldID = env->GetFieldID(jcXlevent, "flags", "I");
				env->SetIntField(ev_tagData, fieldID, XlCanTxEvt[i].tagData.canMsg.msgFlags);
				fieldID = env->GetFieldID(jcXlevent, "dlc", "I");
				env->SetIntField(ev_tagData, fieldID, XlCanTxEvt[i].tagData.canMsg.dlc);

				fieldID = env->GetFieldID(jcXlevent, "data", "[B");
				jbyteArray jba = (jbyteArray)env->GetObjectField(jcXlevent, fieldID);
				env->SetByteArrayRegion(jba, 0, 8, (const jbyte*)XlCanTxEvt[i].tagData.canMsg.data);

				env->SetObjectArrayElement(pXlCanTxEvt, i, Ev);
			}
		}
		else
		{
			pXlCanTxEvt = NULL;
		}

		delete[] XlCanTxEvt;*/
		return ret;
	}

	JNIEXPORT jint JNICALL Java_can_interfaces_vector_jni_Jvxlapi_xlCanFlushTransmitQueue
	(JNIEnv *, jclass, jlong portHandle, jlong accessMask) {
		return xlCanFlushTransmitQueue(portHandle, accessMask);
	}

	JNIEXPORT jint JNICALL Java_can_interfaces_vector_jni_Jvxlapi_xlCanSetChannelAcceptance
	(JNIEnv *, jclass, jlong portHandle, jlong accessMask, jlong code, jlong mask, jint idRange) {
		return xlCanSetChannelAcceptance(portHandle, accessMask, code, mask, idRange);
	}

	JNIEXPORT jint JNICALL Java_can_interfaces_vector_jni_Jvxlapi_xlCanResetAcceptance
	(JNIEnv *, jclass, jlong portHandle, jlong accessMask, jint idRange) {
		return xlCanResetAcceptance(portHandle, accessMask, idRange);
	}

	JNIEXPORT jint JNICALL Java_can_interfaces_vector_jni_Jvxlapi_WaitForSingleObject
	(JNIEnv *, jclass, jlong handle, jlong time_left_ms) {
		return WaitForSingleObject((HANDLE)handle, (DWORD)time_left_ms);
	}

#ifdef __cplusplus
}
#endif