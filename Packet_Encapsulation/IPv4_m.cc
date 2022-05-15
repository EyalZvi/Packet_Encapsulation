//
// Generated file, do not edit! Created by nedtool 5.6 from IPv4.msg.
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
#include "IPv4_m.h"

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

Register_Class(IPv4Msg)

IPv4Msg::IPv4Msg(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->protocol_version = 0;
    this->IHL = 0;
    this->DSCP = 0;
    this->ECN = 0;
    this->Total_length = 0;
    this->identification = 0;
    this->flags = 0;
    this->fragment_offset = 0;
    this->TTL = 0;
    this->upper_protocol = 0;
    this->header_checksum = 0;
    this->src_ip = 0;
    this->dest_ip = 0;
}

IPv4Msg::IPv4Msg(const IPv4Msg& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

IPv4Msg::~IPv4Msg()
{
}

IPv4Msg& IPv4Msg::operator=(const IPv4Msg& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void IPv4Msg::copy(const IPv4Msg& other)
{
    this->protocol_version = other.protocol_version;
    this->IHL = other.IHL;
    this->DSCP = other.DSCP;
    this->ECN = other.ECN;
    this->Total_length = other.Total_length;
    this->identification = other.identification;
    this->flags = other.flags;
    this->fragment_offset = other.fragment_offset;
    this->TTL = other.TTL;
    this->upper_protocol = other.upper_protocol;
    this->header_checksum = other.header_checksum;
    this->src_ip = other.src_ip;
    this->dest_ip = other.dest_ip;
}

void IPv4Msg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->protocol_version);
    doParsimPacking(b,this->IHL);
    doParsimPacking(b,this->DSCP);
    doParsimPacking(b,this->ECN);
    doParsimPacking(b,this->Total_length);
    doParsimPacking(b,this->identification);
    doParsimPacking(b,this->flags);
    doParsimPacking(b,this->fragment_offset);
    doParsimPacking(b,this->TTL);
    doParsimPacking(b,this->upper_protocol);
    doParsimPacking(b,this->header_checksum);
    doParsimPacking(b,this->src_ip);
    doParsimPacking(b,this->dest_ip);
}

void IPv4Msg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->protocol_version);
    doParsimUnpacking(b,this->IHL);
    doParsimUnpacking(b,this->DSCP);
    doParsimUnpacking(b,this->ECN);
    doParsimUnpacking(b,this->Total_length);
    doParsimUnpacking(b,this->identification);
    doParsimUnpacking(b,this->flags);
    doParsimUnpacking(b,this->fragment_offset);
    doParsimUnpacking(b,this->TTL);
    doParsimUnpacking(b,this->upper_protocol);
    doParsimUnpacking(b,this->header_checksum);
    doParsimUnpacking(b,this->src_ip);
    doParsimUnpacking(b,this->dest_ip);
}

int IPv4Msg::getProtocol_version() const
{
    return this->protocol_version;
}

void IPv4Msg::setProtocol_version(int protocol_version)
{
    this->protocol_version = protocol_version;
}

int IPv4Msg::getIHL() const
{
    return this->IHL;
}

void IPv4Msg::setIHL(int IHL)
{
    this->IHL = IHL;
}

int IPv4Msg::getDSCP() const
{
    return this->DSCP;
}

void IPv4Msg::setDSCP(int DSCP)
{
    this->DSCP = DSCP;
}

int IPv4Msg::getECN() const
{
    return this->ECN;
}

void IPv4Msg::setECN(int ECN)
{
    this->ECN = ECN;
}

int IPv4Msg::getTotal_length() const
{
    return this->Total_length;
}

void IPv4Msg::setTotal_length(int Total_length)
{
    this->Total_length = Total_length;
}

int IPv4Msg::getIdentification() const
{
    return this->identification;
}

void IPv4Msg::setIdentification(int identification)
{
    this->identification = identification;
}

int IPv4Msg::getFlags() const
{
    return this->flags;
}

void IPv4Msg::setFlags(int flags)
{
    this->flags = flags;
}

int IPv4Msg::getFragment_offset() const
{
    return this->fragment_offset;
}

void IPv4Msg::setFragment_offset(int fragment_offset)
{
    this->fragment_offset = fragment_offset;
}

int IPv4Msg::getTTL() const
{
    return this->TTL;
}

void IPv4Msg::setTTL(int TTL)
{
    this->TTL = TTL;
}

int IPv4Msg::getUpper_protocol() const
{
    return this->upper_protocol;
}

void IPv4Msg::setUpper_protocol(int upper_protocol)
{
    this->upper_protocol = upper_protocol;
}

int IPv4Msg::getHeader_checksum() const
{
    return this->header_checksum;
}

void IPv4Msg::setHeader_checksum(int header_checksum)
{
    this->header_checksum = header_checksum;
}

int IPv4Msg::getSrc_ip() const
{
    return this->src_ip;
}

void IPv4Msg::setSrc_ip(int src_ip)
{
    this->src_ip = src_ip;
}

int IPv4Msg::getDest_ip() const
{
    return this->dest_ip;
}

void IPv4Msg::setDest_ip(int dest_ip)
{
    this->dest_ip = dest_ip;
}

class IPv4MsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    IPv4MsgDescriptor();
    virtual ~IPv4MsgDescriptor();

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

Register_ClassDescriptor(IPv4MsgDescriptor)

IPv4MsgDescriptor::IPv4MsgDescriptor() : omnetpp::cClassDescriptor("IPv4Msg", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

IPv4MsgDescriptor::~IPv4MsgDescriptor()
{
    delete[] propertynames;
}

bool IPv4MsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<IPv4Msg *>(obj)!=nullptr;
}

const char **IPv4MsgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *IPv4MsgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int IPv4MsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 13+basedesc->getFieldCount() : 13;
}

unsigned int IPv4MsgDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<13) ? fieldTypeFlags[field] : 0;
}

const char *IPv4MsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "protocol_version",
        "IHL",
        "DSCP",
        "ECN",
        "Total_length",
        "identification",
        "flags",
        "fragment_offset",
        "TTL",
        "upper_protocol",
        "header_checksum",
        "src_ip",
        "dest_ip",
    };
    return (field>=0 && field<13) ? fieldNames[field] : nullptr;
}

int IPv4MsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "protocol_version")==0) return base+0;
    if (fieldName[0]=='I' && strcmp(fieldName, "IHL")==0) return base+1;
    if (fieldName[0]=='D' && strcmp(fieldName, "DSCP")==0) return base+2;
    if (fieldName[0]=='E' && strcmp(fieldName, "ECN")==0) return base+3;
    if (fieldName[0]=='T' && strcmp(fieldName, "Total_length")==0) return base+4;
    if (fieldName[0]=='i' && strcmp(fieldName, "identification")==0) return base+5;
    if (fieldName[0]=='f' && strcmp(fieldName, "flags")==0) return base+6;
    if (fieldName[0]=='f' && strcmp(fieldName, "fragment_offset")==0) return base+7;
    if (fieldName[0]=='T' && strcmp(fieldName, "TTL")==0) return base+8;
    if (fieldName[0]=='u' && strcmp(fieldName, "upper_protocol")==0) return base+9;
    if (fieldName[0]=='h' && strcmp(fieldName, "header_checksum")==0) return base+10;
    if (fieldName[0]=='s' && strcmp(fieldName, "src_ip")==0) return base+11;
    if (fieldName[0]=='d' && strcmp(fieldName, "dest_ip")==0) return base+12;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *IPv4MsgDescriptor::getFieldTypeString(int field) const
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
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<13) ? fieldTypeStrings[field] : nullptr;
}

const char **IPv4MsgDescriptor::getFieldPropertyNames(int field) const
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

const char *IPv4MsgDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int IPv4MsgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    IPv4Msg *pp = (IPv4Msg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *IPv4MsgDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    IPv4Msg *pp = (IPv4Msg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string IPv4MsgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    IPv4Msg *pp = (IPv4Msg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getProtocol_version());
        case 1: return long2string(pp->getIHL());
        case 2: return long2string(pp->getDSCP());
        case 3: return long2string(pp->getECN());
        case 4: return long2string(pp->getTotal_length());
        case 5: return long2string(pp->getIdentification());
        case 6: return long2string(pp->getFlags());
        case 7: return long2string(pp->getFragment_offset());
        case 8: return long2string(pp->getTTL());
        case 9: return long2string(pp->getUpper_protocol());
        case 10: return long2string(pp->getHeader_checksum());
        case 11: return long2string(pp->getSrc_ip());
        case 12: return long2string(pp->getDest_ip());
        default: return "";
    }
}

bool IPv4MsgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    IPv4Msg *pp = (IPv4Msg *)object; (void)pp;
    switch (field) {
        case 0: pp->setProtocol_version(string2long(value)); return true;
        case 1: pp->setIHL(string2long(value)); return true;
        case 2: pp->setDSCP(string2long(value)); return true;
        case 3: pp->setECN(string2long(value)); return true;
        case 4: pp->setTotal_length(string2long(value)); return true;
        case 5: pp->setIdentification(string2long(value)); return true;
        case 6: pp->setFlags(string2long(value)); return true;
        case 7: pp->setFragment_offset(string2long(value)); return true;
        case 8: pp->setTTL(string2long(value)); return true;
        case 9: pp->setUpper_protocol(string2long(value)); return true;
        case 10: pp->setHeader_checksum(string2long(value)); return true;
        case 11: pp->setSrc_ip(string2long(value)); return true;
        case 12: pp->setDest_ip(string2long(value)); return true;
        default: return false;
    }
}

const char *IPv4MsgDescriptor::getFieldStructName(int field) const
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

void *IPv4MsgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    IPv4Msg *pp = (IPv4Msg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


