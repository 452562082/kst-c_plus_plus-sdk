// test_rpc.cpp : 定义控制台应用程序的入口点。
//

/*#include "gen-cpp/kvpService.h"
#include "thrift/transport/TSocket.h"
#include "thrift/transport/TBufferTransports.h"
#include "thrift/protocol/TBinaryProtocol.h"
#include <iostream>
#include "asv_types_pack.h"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using boost::shared_ptr;
using namespace std;

typedef unsigned char byte;

//#define DLL_EXPORTS
//#ifdef DLL_EXPORTS
//#define DLL_EXPORTS __declspec(dllexport)
//#else
//#define DLL_EXPORTS __declspec(dllimport)
//#endif

void* transport_ptr = nullptr;
kvpServiceClient* client = nullptr;

void TransportOpen(void* transport_ptr)
{
	boost::shared_ptr<TTransport> *transport = static_cast<boost::shared_ptr<TTransport>*>(transport_ptr); 
	(*transport)->open();
}

void TransportClose(void* transport_ptr)
{
	boost::shared_ptr<TTransport> *transport = static_cast<boost::shared_ptr<TTransport>*>(transport_ptr); 
	(*transport)->close();
}

extern "C" DLL_EXPORTS void KvpServiceClient_Open(const char* ip, int port)
{
	boost::shared_ptr<TSocket> socket(new TSocket(ip, port));
	boost::shared_ptr<TTransport> *transport = new boost::shared_ptr<TTransport>(new TFramedTransport(socket));
	transport_ptr = static_cast<void*>(transport);
	boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(*transport));
	client = new kvpServiceClient(protocol);
	TransportOpen(transport_ptr);
}

extern "C" DLL_EXPORTS void KvpServiceClient_close()
{
	if(transport_ptr != nullptr){
		TransportClose(transport_ptr);
		delete static_cast<boost::shared_ptr<TTransport>*>(transport_ptr);
		transport_ptr = nullptr;
	}
	if(client != nullptr){
		delete client;
		client = nullptr;
	}
}

extern "C" DLL_EXPORTS _Rpc_UttInfo* KvpGetUttInfo(const char* wav_path)
{
	try{
		if(client == nullptr){
			return nullptr;
		}

		Rpc_UttInfo info;
		client->kvpGetUttInfo(info, wav_path);
		return asv_types_pack::Rpc_UttInfo__extract(info);
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() << std::endl;
	}
}

extern "C" DLL_EXPORTS int32_t KvpModelRemoveBySpkid(const char* vp_node, const char* vp_dir, const char* spk_id)
{
	try{
		if(client == nullptr){
			return -1;
		}
		return client->kvpModelRemoveBySpkid(vp_node,vp_dir,spk_id);
	}catch(std::exception ex){
		std:;cout << "Error:" << ex.what() << std::endl;
	}
}

extern "C" DLL_EXPORTS _Rpc_ModelInfo* KvpRegisterSpeakerByFile(const char* utt, const char* vp_node, const char* vp_dir, const char* spk_id, int32_t sp_chan)
{
	try{
		if(client == nullptr){
			return nullptr;
		}
		Rpc_ModelInfo info;
		client->kvpRegisterSpeakerByFile(info, utt, vp_node, vp_dir, spk_id, sp_chan);
		return asv_types_pack::Rpc_ModelInfo__extract(info);
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() << std::endl;
	}
}

extern "C" DLL_EXPORTS _Rpc_ScoreInfo* KvpVerifySpeakerByFile(const char* utt, const char* spk_id, const char* vp_node, int32_t utt_type, int32_t sp_chan)
{
	try{
		if(client == nullptr){
			return nullptr;
		}
		Rpc_ScoreInfo info;
		client->kvpVerifySpeakerByFile(info, utt, spk_id, vp_node, utt_type, sp_chan);
		return asv_types_pack::Rpc_ScoreInfo__extract(info);
	}catch(std::exception ex){
		std:;cout << "Error:" << ex.what() << std::endl;
	}
}

extern "C" DLL_EXPORTS _Rpc_ScoreInfo* KvpTempVerifySpeakerByFile(const char* utt1, int32_t sp_chan1, int32_t utt_type1, const char* utt2, int32_t sp_chan2, int32_t utt_type2)
{
	try{
		if(client == nullptr){
			return nullptr;
		}
		Rpc_ScoreInfo info;
		client->kvpTempVerifySpeakerByFile(info, utt1, sp_chan1, utt_type1, utt2, sp_chan2, utt_type2);
		return asv_types_pack::Rpc_ScoreInfo__extract(info);
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() << std::endl;
	}
}

extern "C" DLL_EXPORTS _Rpc_TopSpeakerInfo* KvpIdentifyTopSpeakerByFile(const char* utt, const char** vp_node_arr, int32_t node_num, int32_t top_n, int32_t utt_type, int32_t sp_chan)
{
	try{
		if(client == nullptr){
			return nullptr;
		}
		Rpc_TopSpeakerInfo info;
		
		std::vector<std::string> vec;
		for(int i = 0;i < node_num;i++){
			vec.push_back(vp_node_arr[i]);
		}
		client->kvpIdentifyTopSpeakerByFile(info, utt, vec, node_num, top_n, utt_type, sp_chan);
		return asv_types_pack::Rpc_TopSpeakerInfo__extract(info);
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() << std::endl;
	}
}

extern "C" DLL_EXPORTS int32_t KvpIvectorLoadByFile(const char* vp_node, const char* iv_file)
{
	try{
		if(client == nullptr){
			return -1;
		}
		return client->kvpIvectorLoadByFile(vp_node,iv_file);
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() << std::endl;
	}
}

extern "C" DLL_EXPORTS int32_t KvpInsertNode(const char* vp_node)
{
	try{
		if(client == nullptr){
			return -1;
		}
		return client->kvpInsertNode(vp_node);
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() <<std::endl;
	}
}

extern "C" DLL_EXPORTS int32_t KvpDeleteNode(const char* vp_node)
{
	try{
		if(client == nullptr){
			return -1;
		}
		return client->kvpDeleteNode(vp_node);
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() <<std::endl;
	}
}

extern "C" DLL_EXPORTS const char* KvpGetFingerprint()
{
	try{
		if(client == nullptr) {
			return nullptr;
		}
		std::string fingerprint_str;
		client->kvpGetFingerprint(fingerprint_str);
		return fingerprint_str.c_str();
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() <<std::endl;
	}
}

extern "C" DLL_EXPORTS _Rpc_LicenceInfo* KvpGetLicenceInfo()
{
	try{
		if(client == nullptr) {
			return nullptr;
		}
		Rpc_LicenceInfo info;
		client->KvpGetLicenceInfo(info);
		return asv_types_pack::Rpc_LicenceInfo__extract(info);
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() <<std::endl;
	}
}

extern "C" DLL_EXPORTS int32_t KvpSetLicence(const char* licence)
{
	try{
		if(client == nullptr) {
			return -1;
		}
		return client->kvpSetLicence(licence);
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() << std::endl;
	}
}

extern "C" DLL_EXPORTS bool KvpIsLicenceValid()
{
	try{
		if(client == nullptr) {
			return false;
		}
		return client->kvpIsLicenceValid();
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() <<std::endl;
	}
}

extern "C" DLL_EXPORTS _Rpc_ModelInfo* KvpRegisterSpeakerByStream(int16_t* utt, int utt_size, const char* vp_node, const char* vp_dir, const char* spk_id)
{
	try{
		if(client == nullptr){
			return nullptr;
		}

		std::vector<short> utt_vec;
		for (int i=0; i<utt_size; i++) {
			utt_vec.push_back(utt[i]);
		}

		Rpc_ModelInfo info;
		client->kvpRegisterSpeakerByStream(info, utt_vec, vp_node, vp_dir, spk_id);
		return asv_types_pack::Rpc_ModelInfo__extract(info);
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() <<std::endl;
	}
}

extern "C" DLL_EXPORTS _Rpc_TopSpeakerInfo* KvpIdentifyTopSpeakerByStream(int16_t* utt, int utt_size, const char** vp_node_arr, int node_num, int top_n, int utt_type)
{
	try{
		if(client == nullptr) {
			return nullptr;
		}

		std::vector<std::string> vp_node_arr_vec;
		for (int i=0; i<node_num; i++) {
			vp_node_arr_vec.push_back(vp_node_arr[i]);
		}

		std::vector<short> utt_vec;
		for (int i=0; i<utt_size; i++) {
			utt_vec.push_back(utt[i]);
		}

		Rpc_TopSpeakerInfo info;
		client->kvpIdentifyTopSpeakerByStream(info, utt_vec, vp_node_arr_vec, node_num, top_n, utt_type);
		return asv_types_pack::Rpc_TopSpeakerInfo__extract(info);
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() <<std::endl;
	}
}

extern "C" DLL_EXPORTS void Delete_Asv_Type(_Asv_Type type,void* ptr)
{
	asv_types_pack::_Asv_Type__delete(type,ptr);
}*/

//extern "C" DLL_EXPORTS void Delete_Rpc_UttInfo(_Rpc_UttInfo *ptr) 
//{
//	asv_types_pack::_Rpc_UttInfo__delete(ptr);
//}
//
//extern "C" DLL_EXPORTS void Delete_Rpc_ModelInfo(_Rpc_ModelInfo* ptr)
//{
//	asv_types_pack::_Rpc_ModelInfo__delete(ptr);
//}
//
//extern "C" DLL_EXPORTS void Delete_Rpc_ScoreInfo(_Rpc_ScoreInfo* ptr)
//{
//	asv_types_pack::_Rpc_ScoreInfo__delete(ptr);
//}
//
//extern "C" DLL_EXPORTS void Delete_Rpc_SpeakerScore(_Rpc_SpeakerScore* ptr)
//{
//	asv_types_pack::_Rpc_SpeakerScore__delete(ptr);
//}
//
//extern "C" DLL_EXPORTS void Delete_Rpc_TopSpeakerInfo(_Rpc_TopSpeakerInfo* ptr)
//{
//	asv_types_pack::_Rpc_TopSpeakerInfo__delete(ptr);
//}
//
//extern "C" DLL_EXPORTS void Delete_Rpc_LicenceInfo(_Rpc_LicenceInfo* ptr)
//{
//	asv_types_pack::_Rpc_LicenceInfo__delete(ptr);
//}

/*int main(int argc, char **argv)
{
    boost::shared_ptr<TSocket> socket(new TSocket("192.168.1.16", 9191));
    boost::shared_ptr<TTransport> transport(new TFramedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
	kvpServiceClient client(protocol);

	try {
		transport->open();

		if (1 == client.kvpInsertNode("testnode")) ;
		
		std::vector<short> utt;
		for (int i=1; i<800000; i++) {
			utt.push_back((short)i);
		}
		Rpc_ModelInfo _mdlinfo;
		client.kvpRegisterSpeakerByStream(_mdlinfo, utt, "testnode", "/tmp/asv", "djsayrwq2ry7dehswjd7");
		if (_mdlinfo.RetCode == 1) std::cout << "Failed: " << _mdlinfo.ErrCode << "\t" << _mdlinfo.ErrMsg << std::endl;
		Rpc_TopSpeakerInfo rt;
		std::vector<std::string> vec;
		vec.push_back("testnode");
		client.kvpIdentifyTopSpeakerByStream(rt, utt, vec,1, 1, 0);
		if(rt.RetCode == 1) std::cout << "Failed: " << rt.ErrCode << "\t" << rt.ErrMsg << std::endl;

		// 获取机器指纹
		std::string fingerprint;
		client.kvpGetFingerprint(fingerprint);
		cout << "Fingerprint: " << fingerprint << endl;

		// 获取授权状态
		cout << "Auth Status: " << client.kvpIsLicenceValid() << endl;

		// 获取授权信息
		std::string dateStr;
		Rpc_LicenceInfo info;
		client.KvpGetLicenceInfo(info);
		if (info.RetCode == 0) {
			cout << "Licence Info:" << info.dateStr << " " << info.maxOccurs << " " << info.fingerprint << endl;
		} else {
			cout << "Licence Info: Failed to get!!!" << endl;
		}

		// 动态设置授权码
		std::string licence = "byxcOvH9lgm9N2G7Xseof/5sJzCdDC7PUMk4cJLKz0MP79Lt7xYjibqeBRx1p698otYlrlHp8qFNAePGeHNhm7k+Hv1da7NVdz8uU5YeItlDjxX1trTC2lUuU3fcL9DuC2dtBURZPOXW9Bn/ySGIEsdzA6dcQ8ZjHy3EcZPDjwM=";
		int ret = client.kvpSetLicence(licence);
		cout << "Set Licence: " << ret << endl;


		transport->close();
	} catch(TException& tx) {
		cout << "ERROR: " << tx.what() << endl;
	}

    return 0;
}*/