//
// Generated file, do not edit! Created by nedtool 5.6 from Eth.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "Eth_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(EthMsg)

EthMsg::EthMsg(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->preamble = 0;
    this->SFD = 0;
    this->payload_len = 0;
    this->FCS = 0;
    this->src_MAC = 0;
    this->dest_MAC = 0;
    this->EtherType = 0;
    this->port = 0;
    this->src_ip = 0;
    this->dest_ip = 0;
    this->sending_time = 0;
}

EthMsg::EthMsg(const EthMsg& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

EthMsg::~EthMsg()
{
}

EthMsg& EthMsg::operator=(const EthMsg& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void EthMsg::copy(const EthMsg& other)
{
    this->preamble = other.preamble;
    this->SFD = other.SFD;
    this->payload_len = other.payload_len;
    this->FCS = other.FCS;
    this->src_MAC = other.src_MAC;
    this->dest_MAC = other.dest_MAC;
    this->EtherType = other.EtherType;
    this->port = other.port;
    this->src_ip = other.src_ip;
    this->dest_ip = other.dest_ip;
    this->sending_time = other.sending_time;
}

void EthMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->preamble);
    doParsimPacking(b,this->SFD);
    doParsimPacking(b,this->payload_len);
    doParsimPacking(b,this->FCS);
    doParsimPacking(b,this->src_MAC);
    doParsimPacking(b,this->dest_MAC);
    doParsimPacking(b,this->EtherType);
    doParsimPacking(b,this->port);
    doParsimPacking(b,this->src_ip);
    doParsimPacking(b,this->dest_ip);
    doParsimPacking(b,this->sending_time);
}

void EthMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->preamble);
    doParsimUnpacking(b,this->SFD);
    doParsimUnpacking(b,this->payload_len);
    doParsimUnpacking(b,this->FCS);
    doParsimUnpacking(b,this->src_MAC);
    doParsimUnpacking(b,this->dest_MAC);
    doParsimUnpacking(b,this->EtherType);
    doParsimUnpacking(b,this->port);
    doParsimUnpacking(b,this->src_ip);
    doParsimUnpacking(b,this->dest_ip);
    doParsimUnpacking(b,this->sending_time);
}

int EthMsg::getPreamble() const
{
    return this->preamble;
}

void EthMsg::setPreamble(int preamble)
{
    this->preamble = preamble;
}

int EthMsg::getSFD() const
{
    return this->SFD;
}

void EthMsg::setSFD(int SFD)
{
    this->SFD = SFD;
}

int EthMsg::getPayload_len() const
{
    return this->payload_len;
}

void EthMsg::setPayload_len(int payload_len)
{
    this->payload_len = payload_len;
}

int EthMsg::getFCS() const
{
    return this->FCS;
}

void EthMsg::setFCS(int FCS)
{
    this->FCS = FCS;
}

int EthMsg::getSrc_MAC() const
{
    return this->src_MAC;
}

void EthMsg::setSrc_MAC(int src_MAC)
{
    this->src_MAC = src_MAC;
}

int EthMsg::getDest_MAC() const
{
    return this->dest_MAC;
}

void EthMsg::setDest_MAC(int dest_MAC)
{
    this->dest_MAC = dest_MAC;
}

int EthMsg::getEtherType() const
{
    return this->EtherType;
}

void EthMsg::setEtherType(int EtherType)
{
    this->EtherType = EtherType;
}

int EthMsg::getPort() const
{
    return this->port;
}

void EthMsg::setPort(int port)
{
    this->port = port;
}

int EthMsg::getSrc_ip() const
{
    return this->src_ip;
}

void EthMsg::setSrc_ip(int src_ip)
{
    this->src_ip = src_ip;
}

int EthMsg::getDest_ip() const
{
    return this->dest_ip;
}

void EthMsg::setDest_ip(int dest_ip)
{
    this->dest_ip = dest_ip;
}

::omnetpp::simtime_t EthMsg::getSending_time() const
{
    return this->sending_time;
}

void EthMsg::setSending_time(::omnetpp::simtime_t sending_time)
{
    this->sending_time = sending_time;
}

class EthMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    EthMsgDescriptor();
    virtual ~EthMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(EthMsgDescriptor)

EthMsgDescriptor::EthMsgDescriptor() : omnetpp::cClassDescriptor("EthMsg", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

EthMsgDescriptor::~EthMsgDescriptor()
{
    delete[] propertynames;
}

bool EthMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EthMsg *>(obj)!=nullptr;
}

const char **EthMsgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *EthMsgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int EthMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 11+basedesc->getFieldCount() : 11;
}

unsigned int EthMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<11) ? fieldTypeFlags[field] : 0;
}

const char *EthMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "preamble",
        "SFD",
        "payload_len",
        "FCS",
        "src_MAC",
        "dest_MAC",
        "EtherType",
        "port",
        "src_ip",
        "dest_ip",
        "sending_time",
    };
    return (field>=0 && field<11) ? fieldNames[field] : nullptr;
}

int EthMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "preamble")==0) return base+0;
    if (fieldName[0]=='S' && strcmp(fieldName, "SFD")==0) return base+1;
    if (fieldName[0]=='p' && strcmp(fieldName, "payload_len")==0) return base+2;
    if (fieldName[0]=='F' && strcmp(fieldName, "FCS")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "src_MAC")==0) return base+4;
    if (fieldName[0]=='d' && strcmp(fieldName, "dest_MAC")==0) return base+5;
    if (fieldName[0]=='E' && strcmp(fieldName, "EtherType")==0) return base+6;
    if (fieldName[0]=='p' && strcmp(fieldName, "port")==0) return base+7;
    if (fieldName[0]=='s' && strcmp(fieldName, "src_ip")==0) return base+8;
    if (fieldName[0]=='d' && strcmp(fieldName, "dest_ip")==0) return base+9;
    if (fieldName[0]=='s' && strcmp(fieldName, "sending_time")==0) return base+10;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *EthMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "simtime_t",
    };
    return (field>=0 && field<11) ? fieldTypeStrings[field] : nullptr;
}

const char **EthMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *EthMsgDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int EthMsgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    EthMsg *pp = (EthMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *EthMsgDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EthMsg *pp = (EthMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EthMsgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EthMsg *pp = (EthMsg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getPreamble());
        case 1: return long2string(pp->getSFD());
        case 2: return long2string(pp->getPayload_len());
        case 3: return long2string(pp->getFCS());
        case 4: return long2string(pp->getSrc_MAC());
        case 5: return long2string(pp->getDest_MAC());
        case 6: return long2string(pp->getEtherType());
        case 7: return long2string(pp->getPort());
        case 8: return long2string(pp->getSrc_ip());
        case 9: return long2string(pp->getDest_ip());
        case 10: return simtime2string(pp->getSending_time());
        default: return "";
    }
}

bool EthMsgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    EthMsg *pp = (EthMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setPreamble(string2long(value)); return true;
        case 1: pp->setSFD(string2long(value)); return true;
        case 2: pp->setPayload_len(string2long(value)); return true;
        case 3: pp->setFCS(string2long(value)); return true;
        case 4: pp->setSrc_MAC(string2long(value)); return true;
        case 5: pp->setDest_MAC(string2long(value)); return true;
        case 6: pp->setEtherType(string2long(value)); return true;
        case 7: pp->setPort(string2long(value)); return true;
        case 8: pp->setSrc_ip(string2long(value)); return true;
        case 9: pp->setDest_ip(string2long(value)); return true;
        case 10: pp->setSending_time(string2simtime(value)); return true;
        default: return false;
    }
}

const char *EthMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *EthMsgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    EthMsg *pp = (EthMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


