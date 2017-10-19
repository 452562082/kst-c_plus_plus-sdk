// test_rpc.cpp : 定义控制台应用程序的入口点。
//

#include "gen-cpp/kvpService.h"
#include "thrift/transport/TSocket.h"
#include "thrift/transport/TBufferTransports.h"
#include "thrift/protocol/TBinaryProtocol.h"
#include <iostream>
#include "test_rpc.h"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using boost::shared_ptr;
using namespace std;

typedef unsigned char byte;

#define DLL_EXPORTS
#ifdef DLL_EXPORTS
#define DLL_EXPORTS __declspec(dllexport)
#else
#define DLL_EXPORTS __declspec(dllimport)
#endif

extern "C" DLL_EXPORTS void* CreateTransport(const char* ip,int port)
{
	boost::shared_ptr<TSocket> socket(new TSocket(ip, port));
    boost::shared_ptr<TTransport> *transport = new boost::shared_ptr<TTransport>(new TFramedTransport(socket));
	return static_cast<void*>(transport);
}

extern "C" DLL_EXPORTS void* CreateKvpServiceClient(void* transport_ptr)
{	
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(*static_cast<boost::shared_ptr<TTransport>*>(transport_ptr)));
	kvpServiceClient* client = new kvpServiceClient(protocol);	
	return static_cast<void*>(client);
}

extern "C" DLL_EXPORTS void DeleteKvpServiceClient(void* client_ptr)
{
	delete static_cast<kvpServiceClient*>(client_ptr);
	client_ptr = nullptr;
}

extern "C" DLL_EXPORTS void TransportOpen(void* transport_ptr)
{
	boost::shared_ptr<TTransport> *transport = static_cast<boost::shared_ptr<TTransport>*>(transport_ptr); 
	(*transport)->open();
}

extern "C" DLL_EXPORTS void TransportClose(void* transport_ptr)
{
	boost::shared_ptr<TTransport> *transport = static_cast<boost::shared_ptr<TTransport>*>(transport_ptr); 
	(*transport)->close();
}

extern "C" DLL_EXPORTS void DeleteTransport(void* transport_ptr)
{
	delete static_cast<boost::shared_ptr<TTransport>*>(transport_ptr);
	transport_ptr = nullptr;
}

extern "C" DLL_EXPORTS int32_t KvpInsertNode(void* client_ptr, const char* node_name)
{
	try{
		kvpServiceClient* client = static_cast<kvpServiceClient*>(client_ptr);
		if(client == nullptr){
			return -1;
		}
		return client->kvpInsertNode(node_name);
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() <<std::endl;
	}
}

extern "C" DLL_EXPORTS int32_t KvpDeleteNode(void* client_ptr, const char* node_name)
{
	try{
		kvpServiceClient* client = static_cast<kvpServiceClient*>(client_ptr);
		if(client == nullptr){
			return -1;
		}
		return client->kvpDeleteNode(node_name);
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() <<std::endl;
	}
}

extern "C" DLL_EXPORTS void KvpRegisterSpeakerByStream(void* client_ptr, _Rpc_ModelInfo* ret, int16_t* utt, int utt_size, const char* vp_node, const char* vp_dir, const char* spk_id)
{
	try{
		kvpServiceClient* client = static_cast<kvpServiceClient*>(client_ptr);
		if(client == nullptr){
			return;
		}

		std::vector<short> utt_vec;
		for (int i=0; i<utt_size; i++) {
			utt_vec.push_back(utt[i]);
		}

		Rpc_ModelInfo _mdlinfo;
		client->kvpRegisterSpeakerByStream(_mdlinfo, utt_vec, vp_node, vp_dir, spk_id);

		if(_mdlinfo.Utt.length() > 0){
			ret->Utt = new char[_mdlinfo.Utt.length() + 1];
			strcpy(ret->Utt,_mdlinfo.Utt.c_str());
		}
		if(_mdlinfo.Spkid.length() > 0){
			ret->Spkid = new char[_mdlinfo.Spkid.length() + 1];
			strcpy(ret->Spkid,_mdlinfo.Spkid.c_str());
		}
		ret->Size = _mdlinfo.Size;
		if(_mdlinfo.Language.length() > 0){
			ret->Language = new char[_mdlinfo.Language.length() + 1];
			strcpy(ret->Language,_mdlinfo.Language.c_str());
		}
		if(_mdlinfo.Gender.length() > 0){
			ret->Gender = new char[_mdlinfo.Gender.length() + 1];
			strcpy(ret->Gender,_mdlinfo.Gender.c_str());
		}
		if(_mdlinfo.Channeltype.length() > 0){
			ret->Channeltype = new char[_mdlinfo.Channeltype.length() + 1];
			strcpy(ret->Channeltype,_mdlinfo.Channeltype.c_str());
		}

		ret->SampRate = _mdlinfo.SampRate;
		ret->Duration = _mdlinfo.Duration;
		ret->ValidDuration = _mdlinfo.ValidDuration;
		if(_mdlinfo.IvFile.length() > 0){
			ret->IvFile = new char[_mdlinfo.IvFile.length() + 1];
			strcpy(ret->IvFile,_mdlinfo.IvFile.c_str());
		}
		ret->ErrCode = _mdlinfo.ErrCode;
		if(_mdlinfo.ErrMsg.length() > 0){
			ret->ErrMsg = new char[_mdlinfo.ErrMsg.length() + 1];
			strcpy(ret->ErrMsg, _mdlinfo.ErrMsg.c_str());
		}
		ret->RetCode = _mdlinfo.ErrCode;

		return;
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() <<std::endl;
	}
}

extern "C" DLL_EXPORTS void KvpIdentifyTopSpeakerByStream(void* client_ptr, _Rpc_TopSpeakerInfo* ret, int16_t* utt, int utt_size, const char** vp_node_arr, int vp_node_arr_size, int node_num, int top_n, int utt_type)
{
	try{
		kvpServiceClient* client = static_cast<kvpServiceClient*>(client_ptr);
		if(client == nullptr) {
			return;
		}

		std::vector<std::string> vp_node_arr_vec;
		for (int i=0; i<vp_node_arr_size; i++) {
			vp_node_arr_vec.push_back(vp_node_arr[i]);
		}

		std::vector<short> utt_vec;
		for (int i=0; i<utt_size; i++) {
			utt_vec.push_back(utt[i]);
		}

		Rpc_TopSpeakerInfo _tsinfo;
		client->kvpIdentifyTopSpeakerByStream(_tsinfo, utt_vec, vp_node_arr_vec, node_num, top_n, utt_type);

		if(_tsinfo.Utt.length() > 0){
			ret->Utt = new char[_tsinfo.Utt.length() + 1];
			strcpy(ret->Utt,_tsinfo.Utt.c_str());
		}
		if(_tsinfo.Scores.size() > 0){
			ret->Scores = new _Rpc_SpeakerScore[_tsinfo.Scores.size()];
			for(int i = 0;i < _tsinfo.Scores.size();++i)
			{
				if(_tsinfo.Scores[i].Spkid.length() > 0){
					ret->Scores[i].Spkid = new char[_tsinfo.Scores[i].Spkid.length() + 1];
					strcpy(ret->Scores[i].Spkid, _tsinfo.Scores[i].Spkid.c_str());
				}
				ret->Scores[i].Score = _tsinfo.Scores[i].Score;
				ret->Scores[i].__isset = new _Rpc_SpeakerScore__isset;
				ret->Scores[i].__isset->Score = _tsinfo.Scores[i].__isset.Score;
				ret->Scores[i].__isset->Spkid = _tsinfo.Scores[i].__isset.Spkid;
			}
		}
		ret->Scores_size = _tsinfo.Scores.size();
		ret->Top = _tsinfo.Top;
		ret->SampRate = _tsinfo.SampRate;
		ret->Duration = _tsinfo.Duration;
		ret->ValidDuration = _tsinfo.ValidDuration;
		ret->ErrCode = _tsinfo.ErrCode;
		if(_tsinfo.ErrMsg.length() > 0){
			ret->ErrMsg = new char[_tsinfo.ErrMsg.length() + 1];
			strcpy(ret->ErrMsg, _tsinfo.ErrMsg.c_str());
		}
		ret->RetCode = _tsinfo.RetCode;

		ret->__isset = new _Rpc_TopSpeakerInfo__isset;
		ret->__isset->Duration = _tsinfo.__isset.Duration;
		ret->__isset->ErrCode = _tsinfo.__isset.ErrCode;
		ret->__isset->ErrMsg = _tsinfo.__isset.ErrMsg;
		ret->__isset->RetCode = _tsinfo.__isset.RetCode;
		ret->__isset->SampRate = _tsinfo.__isset.SampRate;
		ret->__isset->Scores = _tsinfo.__isset.Scores;
		ret->__isset->Top = _tsinfo.__isset.Top;
		ret->__isset->Utt = _tsinfo.__isset.Utt;
		ret->__isset->ValidDuration = _tsinfo.__isset.ValidDuration;
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() <<std::endl;
	}
}

extern "C" DLL_EXPORTS int32_t KvpModelRemoveBySpkid(void* client_ptr, const char* vp_node, const char* vp_dir, const char* spk_id)
{
	try{
		kvpServiceClient* client = static_cast<kvpServiceClient*>(client_ptr);
		if(client == nullptr) {
			return -1;
		}
		return client->kvpModelRemoveBySpkid(vp_node,vp_dir,spk_id);
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() <<std::endl;
	}
}

extern "C" DLL_EXPORTS void KvpGetFingerprint(void* client_ptr, char* fingerprint)
{
	try{
		kvpServiceClient* client = static_cast<kvpServiceClient*>(client_ptr);
		if(client == nullptr) {
			return;
		}
		std::string fingerprint_str;
		client->kvpGetFingerprint(fingerprint_str);
		fingerprint = new char[fingerprint_str.length()];
		strcpy(fingerprint,fingerprint_str.c_str());
		return;
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() <<std::endl;
	}
}

extern "C" DLL_EXPORTS bool KvpIsLicenceValid(void* client_ptr)
{
	try{
		kvpServiceClient* client = static_cast<kvpServiceClient*>(client_ptr);
		if(client == nullptr) {
			return false;
		}
		return client->kvpIsLicenceValid();
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() <<std::endl;
	}
}

extern "C" DLL_EXPORTS void KvpGetLicenceInfo(void* client_ptr,_Rpc_LicenceInfo* ret)
{
	try{
		kvpServiceClient* client = static_cast<kvpServiceClient*>(client_ptr);
		if(client == nullptr) {
			return;
		}
		Rpc_LicenceInfo info;
		client->KvpGetLicenceInfo(info);

		ret->dateStr = new char[info.dateStr.length()];
		strcpy(ret->dateStr, info.dateStr.c_str());
		ret->fingerprint = new char[info.fingerprint.length()];
		strcpy(ret->fingerprint,info.fingerprint.c_str());
		ret->maxOccurs = info.maxOccurs;
		ret->RetCode = info.RetCode;
		ret->__isset = new _Rpc_LicenceInfo__isset;
		ret->__isset->dateStr = info.__isset.dateStr;
		ret->__isset->fingerprint = info.__isset.fingerprint;
		ret->__isset->maxOccurs = info.__isset.maxOccurs;
		ret->__isset->RetCode = info.__isset.RetCode;
		return;
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() <<std::endl;
	}
}

extern "C" DLL_EXPORTS int32_t KvpSetLicence(void *client_ptr, const char* licence)
{
	try{
		kvpServiceClient* client = static_cast<kvpServiceClient*>(client_ptr);
		if(client == nullptr) {
			return -1;
		}

		return client->kvpSetLicence(licence);
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() <<std::endl;
	}
}

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