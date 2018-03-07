#include "asv_types_pack.h"

_Rpc_UttInfo* asv_types_pack::Rpc_UttInfo__extract(const Rpc_UttInfo& info)
{
	_Rpc_UttInfo* ret = new _Rpc_UttInfo;

	ret->Utt = info.Utt;
	ret->Duration = info.Duration;
	ret->ValidDuration = info.ValidDuration;
	ret->Channels = info.Channels;
	ret->SampRate = info.SampRate;
	ret->ErrCode = info.ErrCode;
	ret->ErrMsg = info.ErrMsg;
	ret->RetCode = info.RetCode;
	__Rpc_UttInfo__isset __isset;
	__isset.Utt = info.__isset.Utt;
	__isset.Duration = info.__isset.Duration;
	__isset.ValidDuration = info.__isset.ValidDuration;
	__isset.Channels = info.__isset.Channels;
	__isset.SampRate = info.__isset.SampRate;
	__isset.ErrCode = info.__isset.ErrCode;
	__isset.ErrMsg = info.__isset.ErrMsg;
	__isset.RetCode = info.__isset.RetCode;
	ret->__isset = __isset;
	return ret;
}

_Rpc_ModelInfo* asv_types_pack::Rpc_ModelInfo__extract(const Rpc_ModelInfo& info)
{
	_Rpc_ModelInfo* ret = new _Rpc_ModelInfo;

	ret->Utt = info.Utt;
	ret->Spkid = info.Spkid;
	ret->Size = info.Size;
	ret->Language = info.Language;
	ret->Gender = info.Gender;
	ret->Channeltype = info.Channeltype;
	ret->SampRate = info.SampRate;
	ret->Duration = info.Duration;
	ret->ValidDuration = info.ValidDuration;
	ret->IvFile = info.IvFile;
	ret->ErrCode = info.ErrCode;
	ret->ErrMsg = info.ErrMsg;
	ret->RetCode = info.ErrCode;
	return ret;
}

_Rpc_ScoreInfo* asv_types_pack::Rpc_ScoreInfo__extract(const Rpc_ScoreInfo& info)
{
	_Rpc_ScoreInfo* ret = new _Rpc_ScoreInfo;

	ret->Utt = info.Utt;
	ret->Spkid = info.Spkid;
	ret->Score = info.Score;
	ret->SampRate = info.SampRate;
	ret->Duration = info.Duration;
	ret->ValidDuration = info.ValidDuration;
	ret->ErrCode = info.ErrCode;
	ret->ErrMsg = info.ErrMsg;
	ret->RetCode = info.RetCode;
	__Rpc_ScoreInfo__isset __isset;
	__isset.Utt = info.__isset.Utt;
	__isset.Spkid = info.__isset.Spkid;
	__isset.Score = info.__isset.Score;
	__isset.SampRate = info.__isset.SampRate;
	__isset.Duration = info.__isset.Duration;
	__isset.ValidDuration = info.__isset.ValidDuration;
	__isset.ErrCode = info.__isset.ErrCode;
	__isset.ErrMsg = info.__isset.ErrMsg;
	__isset.RetCode = info.__isset.RetCode;
	ret->__isset = __isset;
	return ret;
}

_Rpc_SpeakerScore* asv_types_pack::Rpc_SpeakerScore__extract(const Rpc_SpeakerScore& info)
{
	_Rpc_SpeakerScore* ret = new _Rpc_SpeakerScore;

	ret->Spkid = info.Spkid;
	ret->Score = info.Score;
	__Rpc_SpeakerScore__isset __isset;
	__isset.Spkid = info.__isset.Spkid;
	__isset.Score = info.__isset.Score;
	ret->__isset = __isset;
	return ret;
}

_Rpc_TopSpeakerInfo* asv_types_pack::Rpc_TopSpeakerInfo__extract(const Rpc_TopSpeakerInfo& info)
{
	_Rpc_TopSpeakerInfo* ret = new _Rpc_TopSpeakerInfo;

	ret->Utt = info.Utt;
	if(info.Scores.size() > 0){
		for(int i = 0;i < info.Scores.size();++i)
		{
			_Rpc_SpeakerScore score;
			score.Spkid = info.Scores[i].Spkid;
			score.Score = info.Scores[i].Score;
			__Rpc_SpeakerScore__isset __isset;
			__isset.Score = info.Scores[i].__isset.Score;
			__isset.Spkid = info.Scores[i].__isset.Spkid;
			score.__isset = __isset;
			ret->Scores.push_back(score);
		}
	}
	ret->Top = info.Top;
	ret->SampRate = info.SampRate;
	ret->Duration = info.Duration;
	ret->ValidDuration = info.ValidDuration;
	ret->ErrCode = info.ErrCode;
	ret->ErrMsg = info.ErrMsg;
	ret->RetCode = info.RetCode;

	__Rpc_TopSpeakerInfo__isset __isset;
	__isset.Duration = info.__isset.Duration;
	__isset.ErrCode = info.__isset.ErrCode;
	__isset.ErrMsg = info.__isset.ErrMsg;
	__isset.RetCode = info.__isset.RetCode;
	__isset.SampRate = info.__isset.SampRate;
	__isset.Scores = info.__isset.Scores;
	__isset.Top = info.__isset.Top;
	__isset.Utt = info.__isset.Utt;
	__isset.ValidDuration = info.__isset.ValidDuration;
	ret->__isset = __isset;
	return ret;
}

_Rpc_LicenceInfo* asv_types_pack::Rpc_LicenceInfo__extract(const Rpc_LicenceInfo& info)
{
	_Rpc_LicenceInfo* ret = new _Rpc_LicenceInfo;

	ret->dateStr = info.dateStr;
	ret->maxOccurs = info.maxOccurs;
	ret->fingerprint = info.fingerprint;
	ret->RetCode = info.RetCode;

	__Rpc_LicenceInfo__isset __isset;
	__isset.dateStr = info.__isset.dateStr;
	__isset.fingerprint = info.__isset.fingerprint;
	__isset.maxOccurs = info.__isset.maxOccurs;
	__isset.RetCode = info.__isset.RetCode;
	ret->__isset = __isset;
	return ret;
}

void asv_types_pack::_Asv_Type__delete(_Asv_Type type,void* ptr)
{
	if(!ptr){
		return;
	}

	switch(type){
	case _RPC_UttInfo:
		delete static_cast<_Rpc_UttInfo*>(ptr);
		ptr = nullptr;
		break;
	case _RPC_ModelInfo:
		delete static_cast<_Rpc_ModelInfo*>(ptr);
		ptr = nullptr;
		break;
	case _RPC_ScoreInfo:
		delete static_cast<_Rpc_ScoreInfo*>(ptr);
		ptr = nullptr;
		break;
	case _RPC_SpeakerScore:
		delete static_cast<_Rpc_SpeakerScore*>(ptr);
		ptr = nullptr;
		break;
	case _RPC_TopSpeakerInfo:
		delete static_cast<_Rpc_TopSpeakerInfo*>(ptr);
		ptr = nullptr;
		break;
	case _RPC_LicenceInfo:
		delete static_cast<_Rpc_LicenceInfo*>(ptr);
		ptr = nullptr;
		break;
	default:
		break;
	}
}