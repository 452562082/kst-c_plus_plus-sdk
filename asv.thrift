namespace go asv
namespace java com.kuaishang.thrift.asv

struct Rpc_UttInfo {
    1: string Utt,
    2: i64 Duration,
    3: i64 ValidDuration,
    4: i32 Channels,
    5: i32 SampRate,
    6: i32 ErrCode,
    7: string ErrMsg,
	8: i32 RetCode
}

struct Rpc_ModelInfo {
	1: string Utt,
	2: string Spkid,
	3: i32 Size,
	4: string Language,
	5: string Gender,
	6: string Channeltype,
	7: i32 SampRate,
	8: i64 Duration,
	9: i64 ValidDuration,
	10: string IvFile,
    11: i32 ErrCode,
    12: string ErrMsg,
	13: i32 RetCode
}

struct Rpc_ScoreInfo {
	1: string Utt,
	2: string Spkid,
	3: double Score,
	4: i32 SampRate,
	5: i64 Duration,
	6: i64 ValidDuration,
    7: i32 ErrCode,
    8: string ErrMsg,
	9: i32 RetCode
}

struct Rpc_SpeakerScore {
    1: string Spkid,
    2: double Score,
    3: string Node
}

struct Rpc_TopSpeakerInfo {
	1: string Utt,
	2: list<Rpc_SpeakerScore> Scores,
    3: i32 Top,
	4: i32 SampRate,
	5: i64 Duration,
	6: i64 ValidDuration,
    7: i32 ErrCode,
    8: string ErrMsg,
	9: i32 RetCode
}

struct Rpc_LicenceInfo {
	1: string dateStr,
	2: i32 maxOccurs,
    3: string fingerprint,
	4: i32 RetCode
}

service kvpService {
	
    string kvpPing(),    

	/**
	 *	解析语音文件信息。
	 *
	 *	@param [in] wavpath 语音文件路径。
	 *
	 *	@return Rpc_UttInfo 返回语音信息。
	 */
    Rpc_UttInfo kvpGetUttInfo(1:string wavpath),

	/**
	 *	将某说话人ID从某个库节点中删除。
	 *
	 *	@param [in] vp_node 库节点名称。
	 *	@param [in] vp_dir 库节点本地路径。
	 *	@param [in] spk_id 说话人ID。
	 *	
	 *	@return KVP_CODE 
	 */	
    i32 kvpModelRemoveBySpkid(1:string vp_node, 2:string vp_dir, 3:string spk_id),

	/**
	 *	注册说话人。
	 *
	 *	@param [in] utt 语音路径。
	 *	@param [in] vp_node 说话人待注册库节点名称。
	 *	@param [in] vp_dir 声纹库路径。(--------该参数被废弃--------)
	 *	@param [in] spk_id 说话人ID。
	 *	@param [in] sp_chan 指定处理声道。
	 *
	 *	@return Rpc_ModelInfo 说话人模型信息。
	 */
    Rpc_ModelInfo kvpRegisterSpeakerByFile(1:string utt, 2:string vp_node, 3:string vp_dir, 4:string spk_id, 5:i32 sp_chan),

	/**
	 *	1:1验证。
	 *
	 *	@param [in] utt 语音路径。
	 *	@param [in] spk_id 说话人ID。
	 *	@param [in] vp_node 说话人所在库节点名称。
	 *	@param [in] utt_type 语音场景类型。
	 *	@param [in] sp_chan 指定处理声道。
	 *
	 *	@return Rpc_ScoreInfo 1:1验证信息。
	 */
    Rpc_ScoreInfo kvpVerifySpeakerByFile(1:string utt, 2:string spk_id, 3:string vp_node, 4:i32 utt_type, 5:i32 sp_chan),

	/**
	 *	1:1验证(给定2段语音进行比较)。
	 *
	 *	@param [in] utt1 第1段语音路径。
	 *	@oaram [in] sp_chan1 指定第1段语音声道。
	 *	@param [in] utt_type1 指定第1段语音场景类型。
	 *	@param [in] utt2  第2段语音路径。
	 *	@oaram [in] sp_chan2 指定第2段语音声道。
	 *	@param [in] utt_type2 指定第2段语音场景类型。
	 *
	 *	@return Rpc_ScoreInfo 验证得分信息
	 */	
    Rpc_ScoreInfo kvpTempVerifySpeakerByFile(1:string utt1, 2:i32 sp_chan1, 3:i32 utt_type1, 4:string utt2, 5:i32 sp_chan2, 6:i32 utt_type2),

	/**
	 *	说话人辨认。
	 *
	 *	@param [in] utt 语音文件路径。
	 *	@param [in] node_list 库节点列表。
	 *  @param [in] node_num 库节点数目。
	 *	@param [in] top_n Top n数目。
	 *	@param [in] utt_type 语音场景类型。
	 *	@param [in] sp_chan 指定处理声道，0：左声道，1：右声道。
	 *
	 *	@return Rpc_TopSpeakerInfo Top n得分信息
	 */
    Rpc_TopSpeakerInfo kvpIdentifyTopSpeakerByFile(1:string utt, 2:list<string> vp_node_arr, 3:i32 node_num, 4:i32 top_n, 5:i32 utt_type, 6:i32 sp_chan),

	/**
	 *	将说话人模型以文件的形式加载到内存某库节点中。
	 *	
	 *	@param [in] vp_node 库节点名称。
	 *	@param [in] iv_file 说话人模型文件路径。
	 *
	 *	@return KVP_CODE 
	 *
	 */
    i32 kvpIvectorLoadByFile(1:string vp_node, 2:string iv_file),

	/**
	 *	向总库中插入某个库节点。
	 *
	 *	@param vp_node 库节点名称。
	 *
	 *	@return KVP_CODE
	 */
    i32 kvpInsertNode(1:string vp_node),

	/**
	 *	从总库中删除某个库节点。
	 *
	 *	@param vp_node 库节点名称。
	 *
	 *	@return KVP_CODE
	 */
    i32 kvpDeleteNode(1:string vp_node),

    /**
     *      将说话人模型从一个库移到另一个库。
     *
     *      @param spk_id 说话人ID。
     *      @param origin 原始库。
     *      @param target 目标库。
     *
     *      @return KVP_CODE
     */
    i32 kvpMoveNode(1:string spk_id, 2:string origin, 3:string target),
			
	/**
	 *	获取机器指纹。
	 *
	 * @return 机器人指纹字符串。
	 */
	string kvpGetFingerprint(),
	
	/**
	 *	获取授权信息。
	 *
	 * @return Rpc_LicenceInfo 授权信息。
	 */
	Rpc_LicenceInfo KvpGetLicenceInfo(),
	
	/**
	 *	如果已经初始化成功，则直接返回KVP_CODE_SUCCEED，否则进行初始化。
	 *
	 *  @param licence 授权字符串。
	 *  
	 *  @return KVP_CODE
	 */
	i32 kvpSetLicence(1:string licence),
	
	/**
	 *	判断Licence是否有效。
	 *
	 * 	@return 授权标志。
	 */
	bool kvpIsLicenceValid(),

	/**
	 *	注册说话人（二进制流格式）。
	 *
	 *	@param [in] utt 语音路径。
	 *	@param [in] samp_rate 语音数据采样率。
	 *	@param [in] vp_node 说话人待注册库节点名称。
	 *	@param [in] vp_dir 声纹库路径。(--------该参数被废弃--------)
	 *	@param [in] spk_id 说话人ID。
	 *
	 *	@return Rpc_ModelInfo 说话人模型信息。
	 */
    Rpc_ModelInfo kvpRegisterSpeakerByStream(1:list<i16> utt, 2:i32 samp_rate, 3:string vp_node, 4:string vp_dir, 5:string spk_id),

	/**
	 *	说话人辨认（二进制流格式）。
	 *
	 *	@param [in] utt 语音流。
	 *	@param [in] samp_rate 语音数据采样率。
	 *	@param [in] node_list 库节点列表。
	 *  @param [in] node_num 库节点数目。
	 *	@param [in] top_n Top n数目。
	 *	@param [in] utt_type 语音场景类型。
	 *
	 *	@return Rpc_TopSpeakerInfo Top n得分信息
	 */
    Rpc_TopSpeakerInfo kvpIdentifyTopSpeakerByStream(1:list<i16> utt, 2:i32 samp_rate, 3:list<string> vp_node_arr, 4:i32 node_num, 5:i32 top_n, 6:i32 utt_type),

    /**
	 *	说话人确认（二进制流格式）。
	 *
	 *	@param [in] utt 语音流。
	 *	@param [in] samp_rate 语音数据采样率。
	 *  @param [in] spk_id 说话人ID。
	 *	@param [in] vp_node 库节点。
	 *	@param [in] utt_type 语音场景类型。
	 *
	 *	@return Rpc_ScoreInfo 得分信息
	 */
    Rpc_ScoreInfo kvpVerifySpeakerByStream(1:list<i16> utt, 2:i32 samp_rate, 3:string spk_id, 4:string vp_node, 5:i32 utt_type),

	/**
	 *	1:1验证(给定2段语音流进行比较)。
	 *
	 *	@param [in] utt1 第1段语音流。
	 *	@param [in] utt1 samp_rate_1 语音数据采样率。
	 *	@param [in] utt_type1 指定第1段语音场景类型。
	 *	@param [in] utt2  第2段语音流。
	 *	@param [in] utt2 samp_rate_2 语音数据采样率。
	 *	@param [in] utt_type2 指定第2段语音场景类型。
	 *
	 *	@return Rpc_ScoreInfo 验证得分信息
	 */	
    Rpc_ScoreInfo kvpTempVerifySpeakerByStream(1:list<i16> utt1, 2:i32 samp_rate_1, 3:i32 utt_type1, 4:list<i16> utt2, 5:i32 samp_rate_2, 6:i32 utt_type2),

    /**
	 *	获取某节点说话人ID列表。
	 *
	 *	@param [in] vp_node 节点名称。
	 *
	 *	@return 说话人ID列表
	 */
    list<string> kvpNodeGetList(1:string vp_node),
}
