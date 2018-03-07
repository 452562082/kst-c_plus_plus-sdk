#ifndef asv_types_pack_H
#define asv_types_pack_H

#include "gen-cpp/asv_types.h"
#include "test_rpc.h"

class asv_types_pack {
public:
	static _Rpc_UttInfo* Rpc_UttInfo__extract(const Rpc_UttInfo& info);
	static _Rpc_ModelInfo* Rpc_ModelInfo__extract(const Rpc_ModelInfo& info);
	static _Rpc_ScoreInfo* Rpc_ScoreInfo__extract(const Rpc_ScoreInfo& info);
	static _Rpc_SpeakerScore* Rpc_SpeakerScore__extract(const Rpc_SpeakerScore& info);
	static _Rpc_TopSpeakerInfo* Rpc_TopSpeakerInfo__extract(const Rpc_TopSpeakerInfo& info);
	static _Rpc_LicenceInfo* Rpc_LicenceInfo__extract(const Rpc_LicenceInfo& info);
	static void _Asv_Type__delete(_Asv_Type type,void* ptr);
};

#endif