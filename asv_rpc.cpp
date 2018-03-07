#define ASV_RPC_DLL

#include "asv_rpc.h"
#include "gen-cpp/kvpService.h"
#include "thrift/transport/TSocket.h"
#include "thrift/transport/TBufferTransports.h"
#include "thrift/protocol/TBinaryProtocol.h"
#include "asv_types_pack.h"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using boost::shared_ptr;

typedef unsigned char byte;

DWORD WINAPI run(LPVOID lpParam)
{
	AsvRpcEngine* engine = (AsvRpcEngine*)lpParam;
	while(true)
	{
		boost::shared_ptr<TSocket> socket(new TSocket(engine->getIp(), engine->getPort()));
		boost::shared_ptr<TTransport> transport(new TFramedTransport(socket));
		boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
		kvpServiceClient client(protocol);

		bool checkConnOK = false;
		try{
			transport->open();
			checkConnOK = true;
		}catch(TTransportException ex) {
			std::cout << "Error:" << ex.what() << std::endl;
			socket->close();
			transport->close();
		}

		int interval = engine->getInterval();
		while(!engine->IsConnect()){
			try{
				Sleep(interval);

				while(!checkConnOK)
				{
					boost::shared_ptr<TSocket> socket(new TSocket(engine->getIp(), engine->getPort()));
					boost::shared_ptr<TTransport> transport(new TFramedTransport(socket));
					boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
					kvpServiceClient client(protocol);
					transport->open();	
					checkConnOK = true;
					engine->reset();
				}

				string ret = engine->KvpPing();
				if(ret == ""){
					engine->reset();
				}
			}catch(TException ex){
				std::cout << "Error:" << ex.what() << std::endl;
				socket->close();
				transport->close();
				checkConnOK = false;
				engine->reset();
			}
		}
	}
}

AsvRpcEngine::AsvRpcEngine(const char* ip, int port, int interval) : m_isConnect(false)
{
	m_ip = ip;
	m_port = port;
	m_interval = interval;
	m_mutex = CreateMutex(nullptr, FALSE, nullptr);
	connect();
	HANDLE hThread = CreateThread(NULL,0,run,this,0,NULL);
}

AsvRpcEngine::~AsvRpcEngine()
{
	close();
	CloseHandle(m_mutex);
}

void AsvRpcEngine::connect()
{
	boost::shared_ptr<TSocket>* socket = new boost::shared_ptr<TSocket>(new TSocket(m_ip, m_port));
	m_socket_ptr = socket;
    boost::shared_ptr<TTransport> *transport = new boost::shared_ptr<TTransport>(new TFramedTransport(*socket));
	m_transport_ptr = transport;
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(*transport));
	kvpServiceClient *m_client = new kvpServiceClient(protocol);
	m_client_ptr = m_client;
	(*transport)->open();
	m_isConnect = true;
}

void AsvRpcEngine::close()
{
	if(m_transport_ptr){
		boost::shared_ptr<TTransport> *transport = static_cast<boost::shared_ptr<TTransport>*>(m_transport_ptr); 
		(*transport)->close();
		delete static_cast<boost::shared_ptr<TTransport>*>(transport);
		transport = nullptr;
	}
	if(m_socket_ptr)
	{
		boost::shared_ptr<TSocket> *socket = static_cast<boost::shared_ptr<TSocket>*>(m_socket_ptr);
		(*socket)->close();
		delete socket;
		socket = nullptr;
	}
	if(m_client_ptr)
	{
		delete static_cast<kvpServiceClient*>(m_client_ptr);
		m_client_ptr = nullptr;
	}
	m_isConnect = false;
}

string AsvRpcEngine::getIp()
{
	return m_ip;
}

int AsvRpcEngine::getPort()
{
	return m_port;
}

int AsvRpcEngine::getInterval()
{
	return m_interval;
}

bool AsvRpcEngine::IsConnect()
{
	return m_isConnect;
}

void AsvRpcEngine::reset()
{
	close();
	connect();
}

string AsvRpcEngine::KvpPing()
{
	WaitForSingleObject(m_mutex, INFINITE);
	if(m_client_ptr){
		string ret = "";
		static_cast<kvpServiceClient*>(m_client_ptr)->kvpPing(ret);
		return ret;
	}
	ReleaseMutex(m_mutex);
	return "";
}

_Rpc_UttInfo* AsvRpcEngine::KvpGetUttInfo(const std::string& wav_path)
{
	try{
		WaitForSingleObject(m_mutex, INFINITE);
		if(!m_client_ptr){
			throw new ClientNilException();
		}

		Rpc_UttInfo info;
		static_cast<kvpServiceClient*>(m_client_ptr)->kvpGetUttInfo(info, wav_path);
		ReleaseMutex(m_mutex);
		return asv_types_pack::Rpc_UttInfo__extract(info);
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() << std::endl;
	}
}

int32_t AsvRpcEngine::KvpModelRemoveBySpkid(const string& vp_node, const string& vp_dir, const string& spk_id)
{
	try{
		WaitForSingleObject(m_mutex, INFINITE);
		if(m_client_ptr == nullptr){
			throw new ClientNilException();
		}
		int32_t ret = static_cast<kvpServiceClient*>(m_client_ptr)->kvpModelRemoveBySpkid(vp_node,vp_dir,spk_id);
		ReleaseMutex(m_mutex);
		return ret;
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() << std::endl;
	}
}

_Rpc_ModelInfo* AsvRpcEngine::KvpRegisterSpeakerByFile(const string& utt, const string& vp_node, const string& vp_dir, const string& spk_id, int32_t sp_chan)
{
	try{
		WaitForSingleObject(m_mutex, INFINITE);
		if(m_client_ptr == nullptr){
			throw new ClientNilException();
		}
		Rpc_ModelInfo info;
		static_cast<kvpServiceClient*>(m_client_ptr)->kvpRegisterSpeakerByFile(info, utt, vp_node, vp_dir, spk_id, sp_chan);
		ReleaseMutex(m_mutex);
		return asv_types_pack::Rpc_ModelInfo__extract(info);
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() << std::endl;
	}
}

_Rpc_ScoreInfo* AsvRpcEngine::KvpVerifySpeakerByFile(const string& utt, const string& spk_id, const string& vp_node, int32_t utt_type, int32_t sp_chan)
{
	try{
		WaitForSingleObject(m_mutex, INFINITE);
		if(m_client_ptr == nullptr){
			throw new ClientNilException();
		}
		Rpc_ScoreInfo info;
		static_cast<kvpServiceClient*>(m_client_ptr)->kvpVerifySpeakerByFile(info, utt, spk_id, vp_node, utt_type, sp_chan);
		ReleaseMutex(m_mutex);
		return asv_types_pack::Rpc_ScoreInfo__extract(info);
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() << std::endl;
	}
}

_Rpc_ScoreInfo* AsvRpcEngine::KvpTempVerifySpeakerByFile(const string& utt1, int32_t sp_chan1, int32_t utt_type1, const string& utt2, int32_t sp_chan2, int32_t utt_type2)
{
	try{
		WaitForSingleObject(m_mutex, INFINITE);
		if(m_client_ptr == nullptr){
			throw new ClientNilException();
		}
		Rpc_ScoreInfo info;
		static_cast<kvpServiceClient*>(m_client_ptr)->kvpTempVerifySpeakerByFile(info, utt1, sp_chan1, utt_type1, utt2, sp_chan2, utt_type2);
		ReleaseMutex(m_mutex);
		return asv_types_pack::Rpc_ScoreInfo__extract(info);
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() << std::endl;
	}
}

_Rpc_TopSpeakerInfo* AsvRpcEngine::KvpIdentifyTopSpeakerByFile(const string& utt, const vector<string> vp_node_arr, int32_t node_num, int32_t top_n, int32_t utt_type, int32_t sp_chan)
{
	try{
		WaitForSingleObject(m_mutex, INFINITE);
		if(m_client_ptr == nullptr){
			throw new ClientNilException();
		}
		Rpc_TopSpeakerInfo info;
		
		static_cast<kvpServiceClient*>(m_client_ptr)->kvpIdentifyTopSpeakerByFile(info, utt, vp_node_arr, node_num, top_n, utt_type, sp_chan);
		ReleaseMutex(m_mutex);
		return asv_types_pack::Rpc_TopSpeakerInfo__extract(info);
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() << std::endl;
	}
}

int32_t AsvRpcEngine::KvpIvectorLoadByFile(const string& vp_node, const string& iv_file)
{
	try{
		WaitForSingleObject(m_mutex, INFINITE);
		if(m_client_ptr == nullptr){
			throw new ClientNilException();
		}
		int32_t ret = static_cast<kvpServiceClient*>(m_client_ptr)->kvpIvectorLoadByFile(vp_node,iv_file);
		ReleaseMutex(m_mutex);
		return ret;
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() << std::endl;
	}
}

int32_t AsvRpcEngine::KvpInsertNode(const string& vp_node)
{
	try{
		WaitForSingleObject(m_mutex, INFINITE);
		if(m_client_ptr == nullptr){
			throw new ClientNilException();
		}
		int32_t ret = static_cast<kvpServiceClient*>(m_client_ptr)->kvpInsertNode(vp_node);
		ReleaseMutex(m_mutex);
		return ret;
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() <<std::endl;
	}
}

int32_t AsvRpcEngine::KvpDeleteNode(const string& vp_node)
{
	try{
		WaitForSingleObject(m_mutex, INFINITE);
		if(m_client_ptr == nullptr){
			throw new ClientNilException();
		}
		int32_t ret = static_cast<kvpServiceClient*>(m_client_ptr)->kvpDeleteNode(vp_node);
		ReleaseMutex(m_mutex);
		return ret;
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() <<std::endl;
	}
}

string AsvRpcEngine::KvpGetFingerprint()
{
	try{
		WaitForSingleObject(m_mutex, INFINITE);
		if(m_client_ptr == nullptr) {
			throw new ClientNilException();
		}
		std::string fingerprint_str;
		static_cast<kvpServiceClient*>(m_client_ptr)->kvpGetFingerprint(fingerprint_str);
		ReleaseMutex(m_mutex);
		return fingerprint_str.c_str();
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() <<std::endl;
	}
}

_Rpc_LicenceInfo* AsvRpcEngine::KvpGetLicenceInfo()
{
	try{
		WaitForSingleObject(m_mutex, INFINITE);
		if(m_client_ptr == nullptr) {
			throw new ClientNilException();
		}
		Rpc_LicenceInfo info;
		static_cast<kvpServiceClient*>(m_client_ptr)->KvpGetLicenceInfo(info);
		ReleaseMutex(m_mutex);
		return asv_types_pack::Rpc_LicenceInfo__extract(info);
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() <<std::endl;
	}
}

int32_t AsvRpcEngine::KvpSetLicence(const string& licence)
{
	try{
		WaitForSingleObject(m_mutex, INFINITE);
		if(m_client_ptr == nullptr) {
			throw new ClientNilException();
		}
		int32_t ret = static_cast<kvpServiceClient*>(m_client_ptr)->kvpSetLicence(licence);
		ReleaseMutex(m_mutex);
		return ret;
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() << std::endl;
	}
}

bool AsvRpcEngine::KvpIsLicenceValid()
{
	try{
		WaitForSingleObject(m_mutex, INFINITE);
		if(m_client_ptr == nullptr) {
			throw new ClientNilException();
		}
		bool flag = static_cast<kvpServiceClient*>(m_client_ptr)->kvpIsLicenceValid();
		ReleaseMutex(m_mutex);
		return flag;
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() <<std::endl;
	}
}

_Rpc_ModelInfo* AsvRpcEngine::KvpRegisterSpeakerByStream(const std::vector<int16_t>& utt, const string& vp_node, const string& vp_dir, const string& spk_id)
{
	try{
		WaitForSingleObject(m_mutex, INFINITE);
		if(m_client_ptr == nullptr){
			throw new ClientNilException();
		}

		Rpc_ModelInfo info;
		static_cast<kvpServiceClient*>(m_client_ptr)->kvpRegisterSpeakerByStream(info, utt, vp_node, vp_dir, spk_id);
		ReleaseMutex(m_mutex);
		return asv_types_pack::Rpc_ModelInfo__extract(info);
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() <<std::endl;
	}
}

_Rpc_TopSpeakerInfo* AsvRpcEngine::KvpIdentifyTopSpeakerByStream(const std::vector<int16_t>& utt, const std::vector<std::string>& node_list, int node_num, int top_n, int utt_type)
{
	try{
		WaitForSingleObject(m_mutex, INFINITE);
		if(m_client_ptr == nullptr) {
			throw new ClientNilException();
		}

		Rpc_TopSpeakerInfo info;
		static_cast<kvpServiceClient*>(m_client_ptr)->kvpIdentifyTopSpeakerByStream(info, utt, node_list, node_num, top_n, utt_type);
		ReleaseMutex(m_mutex);
		return asv_types_pack::Rpc_TopSpeakerInfo__extract(info);
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() <<std::endl;
	}
}

_Rpc_ScoreInfo* AsvRpcEngine::KvpTempVerifySpeakerByStream(const std::vector<int16_t>& utt1, int32_t sp_chan1, int32_t utt_type1, std::vector<int16_t> utt2, int32_t sp_chan2, int32_t utt_type2)
{
	try{
		WaitForSingleObject(m_mutex, INFINITE);
		if(m_client_ptr == nullptr) {
			throw new ClientNilException();
		}

		Rpc_ScoreInfo info;
		static_cast<kvpServiceClient*>(m_client_ptr)->kvpTempVerifySpeakerByStream(info, utt1, sp_chan1, utt_type1, utt2,sp_chan2, utt_type2);
		ReleaseMutex(m_mutex);
		return asv_types_pack::Rpc_ScoreInfo__extract(info);
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() << std::endl;
	}
}

void AsvRpcEngine::Delete_Asv_Type(_Asv_Type type,void* ptr)
{
	try{
		asv_types_pack::_Asv_Type__delete(type, ptr);
	}catch(std::exception ex){
		std::cout << "Error:" << ex.what() << std::endl;
	}
}