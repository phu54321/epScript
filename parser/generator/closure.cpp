#include <vector>
#include <map>
#include <set>
#include "closure.h"
#include "eudplibGlobals.h"

using std::string;

enum TableType {
    TABLE_FUNC,
    TABLE_VAR,
    TABLE_CONST
};

struct Closure {
    std::map<string, string> nameMap[3];
    std::set<string> mapValueSet[3];
};

class ClosureManagerImpl {
public:
    ClosureManagerImpl();
    ~ClosureManagerImpl();

    // Scoping
    void pushScope();
    void popScope();

    // Defining variables
    bool defFunction(std::string& name);
    bool defVariable(std::string& name);
    bool defConstant(std::string& name);

    // These function returns possibility. For example, Kills can be both
    // constant and function, so both function will return true to "Kills".
    bool getFunction(std::string& name) const;
    bool getConstant(std::string& name) const;
    bool getVariable(std::string& name) const;

private:
    Closure& lastClosure() { return closures[closures.size() - 1]; }
    bool hasOutputName(const std::string& name, TableType table) const;
    const Closure* findNearestKeyContainer(const std::string& name, TableType key) const;
    bool defTableValue(std::string& name, TableType table);
    bool getTableValue(std::string& name, TableType table) const;

private:
    std::vector<Closure> closures;
};


ClosureManager::ClosureManager() : impl(new ClosureManagerImpl) {}
ClosureManager::~ClosureManager() { delete impl; }

void ClosureManager::pushScope() { impl->pushScope(); }
void ClosureManager::popScope() { impl->popScope(); }

bool ClosureManager::defFunction(std::string& name) { return impl->defFunction(name); }
bool ClosureManager::defVariable(std::string& name) { return impl->defVariable(name); }
bool ClosureManager::defConstant(std::string& name) { return impl->defConstant(name); }

bool ClosureManager::getFunction(std::string& name) const { return impl->getFunction(name); }
bool ClosureManager::getConstant(std::string& name) const { return impl->getConstant(name); }
bool ClosureManager::getVariable(std::string& name) const { return impl->getVariable(name); }

///////

ClosureManagerImpl::ClosureManagerImpl() {
    closures.push_back(Closure()); // Empty, default closure
}
ClosureManagerImpl::~ClosureManagerImpl() {}


bool ClosureManagerImpl::defFunction(std::string &name) {
    return defTableValue(name, TABLE_FUNC);
}

bool ClosureManagerImpl::defVariable(std::string &name) {
    return defTableValue(name, TABLE_VAR);
}

bool ClosureManagerImpl::defConstant(std::string &name) {
    return defTableValue(name, TABLE_CONST);
}

bool ClosureManagerImpl::getFunction(std::string& name) const {
    if(getTableValue(name, TABLE_FUNC)) return true;
    return isBuiltinFunc(name);
}

bool ClosureManagerImpl::getConstant(std::string& name) const {
    if(getTableValue(name, TABLE_CONST)) return true;
    return isBuiltinConst(name);
}

bool ClosureManagerImpl::getVariable(std::string& name) const {
    return getTableValue(name, TABLE_VAR);
}

///////

const Closure* ClosureManagerImpl::findNearestKeyContainer(const std::string& name, TableType key) const {
    for(auto it = closures.rbegin() ; it != closures.rend() ; it++) {
        auto &map = it->nameMap[key];
        if (map.find(name) != map.end()) return &(*it);
    }
    return nullptr;
}

bool ClosureManagerImpl::getTableValue(std::string& name, TableType table) const {
    auto closure = findNearestKeyContainer(name, table);
    if (closure == nullptr) return false;
    name = closure->nameMap[table].find(name)->second;
    return true;
}

///////

void ClosureManagerImpl::pushScope() {
    closures.push_back(Closure());
}

void ClosureManagerImpl::popScope() {
    if(closures.size() == 1) throw std::logic_error("Cannot pop beyond default closure");
    closures.pop_back();
}

bool ClosureManagerImpl::defTableValue(std::string &name, TableType table) {
    auto& lastClosure = this->lastClosure();
    auto& map = lastClosure.nameMap[table];
    if(map.find(name) != map.end()) return false; // Has duplicate
    if(!hasOutputName(name, table)) {
        map.insert(std::make_pair(name, name));
        lastClosure.mapValueSet[table].insert(name);
        return true;
    }
    else {
        char postfix[30];
        int i;
        for(i = 1 ; ; i++) {
            sprintf(postfix, "_%d", i);
            std::string otherName = name + postfix;
            if(!hasOutputName(otherName, table)) {
                map.insert(std::make_pair(name, otherName));
                lastClosure.mapValueSet[table].insert(otherName);
                name = otherName;
                return true;
            }
        }
    }
}


bool ClosureManagerImpl::hasOutputName(const std::string& name, TableType table) const {
    for(auto it = closures.rbegin() ; it != closures.rend() ; it++) {
        auto &set = it->mapValueSet[table];
        if (set.find(name) != set.end()) return true;
    }
    return false;
}
