/**
You are tasked with a new assignment where you need to build a content management system (CMS). Consumers must be able to create, read, update and delete content. The content is meant to be versioned and each version is meant to be immutable. Deletion can happen only at the content-level. Consumers should be able to read the latest or any specific version of a content.

Based on the above requirements, create a working in-memory prototype

**/
#include <iostream>
#include <string>
#include <unordered_map>
#include <random>
#include <sstream>

using namespace std;

namespace uuid {
static std::random_device              rd;
static std::mt19937                    gen(rd());
static std::uniform_int_distribution<> dis(0, 15);
static std::uniform_int_distribution<> dis2(8, 11);

std::string generate_uuid_v4() {
  std::stringstream ss;
  int i;
  ss << std::hex;
  for (i = 0; i < 8; i++) {
    ss << dis(gen);
  }
  ss << "-";
  for (i = 0; i < 4; i++) {
    ss << dis(gen);
  }
  ss << "-4";
  for (i = 0; i < 3; i++) {
    ss << dis(gen);
  }
  ss << "-";
  ss << dis2(gen);
  for (i = 0; i < 3; i++) {
    ss << dis(gen);
  }
  ss << "-";
  for (i = 0; i < 12; i++) {
    ss << dis(gen);
  };
  return ss.str();
}
}

// Versioning 1.11,1.2,1.3
// 1,2,3,...n
// Key: (uuid) -> strings
// When you're deleting the content , we have ot wipe out all of the versions of the content
//

struct UpsertResult {
  string uuid;
  int version;
};


struct StatusCode {
  int status;
  string error;
};
struct UpsertResultOrErr {
  UpsertResult result;
  StatusCode status_code;
};

struct Data {
  string content;
  int version;
};

struct DataResultOrErr {
  Data data;
  StatusCode status_code;
};

class CMS {
public:
  CMS() {
    /* Create a piece of contnt and reutrn a unique identifier */
  }
  UpsertResultOrErr create(string content) {
    // Return a unique identifier for the content  and then store teh content
    // TODO: Check if the UIUD is present first . Iterate until we find one that's not present here
    auto uuid = uuid::generate_uuid_v4();
    m_data[uuid].push_back(content);
     UpsertResultOrErr resultOrErr ;
    resultOrErr.result.uuid = uuid;
    resultOrErr.result.version = m_data[uuid].size();
    resultOrErr.status_code.status = 0;

     return resultOrErr;
  }
  /* Reads the content at a specific uuid. if version is specified, use that, otherwise , just read the latest version */
  DataResultOrErr read(string uuid, int version = -1) {
    DataResultOrErr resultOrErr;
    // not found
    if (m_data.find(uuid) == m_data.end()) {
      resultOrErr.status_code.status = -1;
    } else {
      // no version was specified
      if (version == -1 ) {
        version = m_data[uuid].size();
      }
      // otherwise it's found
      // TODO: check if the version is valid or not
      resultOrErr.data.content = m_data[uuid][version - 1];
      resultOrErr.data.version = version;
      resultOrErr.status_code.status = 0;
    }
    return resultOrErr;

  }
  /* Updates the content and returns the latest version uuid*/
  UpsertResultOrErr update(string uuid, string content) {
    UpsertResultOrErr resultOrErr;

    // Only update if we found content
    if (m_data.find(uuid) != m_data.end()) {
      m_data[uuid].push_back(content);
      resultOrErr.result.uuid = uuid;
      resultOrErr.result.version = m_data[uuid].size();
      resultOrErr.status_code.status = 0;
    } else {
      resultOrErr.status_code.status = -1;
    }
    return resultOrErr;

  }
  /* Deletes the content at the specified uuid and then returns a success code*/
  StatusCode deleteContent(string uuid) {
    // Not found
    StatusCode code;
    if (m_data.find(uuid) == m_data.end()) {
      code.status = -1;
      return code;
    }
    m_data.erase(uuid);
    code.status = 0;
    return code;
  }

private:
  unordered_map<string,  vector<string> > m_data;
};


int main() {
  std::cout << "Hello world" << std::endl;
  cout << uuid::generate_uuid_v4() << std::endl;

  CMS cms;
  UpsertResultOrErr res = cms.create("a");
  /*
     resultOrErr.result.uuid = uuid;
          resultOrErr.result.version = m_data[uuid].size();
       resultOrErr.status_code.status = 0;
  */
  cout << "create  uuid " << res.result.uuid << endl;
  cout << "create version " << res.result.version << endl;
  cout << "create status " << res.status_code.status << endl;

  /*
  resultOrErr.data.content = m_data[uuid][version - 1];
      resultOrErr.data.version = version;
      resultOrErr.status_code.status = 0;
  */
  auto readRes = cms.read(res.result.uuid);
  cout << "read uuid " << readRes.data.content << endl;
  cout << "read version " << readRes.data.version << endl;
  cout << "read status " << readRes.status_code.status << endl;
  return 0;
}
