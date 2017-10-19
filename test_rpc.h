#ifndef TEST_RPC_H
#define TEST_RPC_H

struct _Rpc_ModelInfo{
	char* Utt;
	char* Spkid;
	int32_t Size;
	char* Language;
	char* Gender;
	char* Channeltype;
	int32_t SampRate;
	int64_t Duration;
	int64_t ValidDuration;
	char* IvFile;
	int32_t ErrCode;
	char* ErrMsg;
	int32_t RetCode;
};

struct _Rpc_SpeakerScore {
	char* Spkid;
	double Score;
	_Rpc_SpeakerScore__isset* __isset;
};

struct _Rpc_TopSpeakerInfo {
	char* Utt;
	_Rpc_SpeakerScore* Scores;
	int Scores_size;
	int32_t Top;
	int32_t SampRate;
	int64_t Duration;
	int64_t ValidDuration;
	int32_t ErrCode;
	char* ErrMsg;
	int32_t RetCode;
	_Rpc_TopSpeakerInfo__isset* __isset;
};

struct _Rpc_LicenceInfo {
	char* dateStr;
	int32_t maxOccurs;
	char* fingerprint;
	int32_t RetCode;
	_Rpc_LicenceInfo__isset* __isset;
};

#endif