#include <vector>
#include <map>
#include <set>
#include "closure.h"
#include "eudplibGlobals.h"
#include <functional>

using std::string;

enum TableType {
    TABLE_FUNC,
    TABLE_VAR,
    TABLE_CONST
};

struct ClosureEntry {
    TableType type;
    string mappedString;
};

struct Closure {
    std::map<string, ClosureEntry> nameMap;
    std::set<string> mapValueSet;
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
    bool hasOutputName(const std::string& name) const;
    const Closure* findNearestNameContainer(const std::string &name) const;
    bool defTableValue(std::string& name, TableType table);
    bool getTableValue(std::string& name, TableType table, std::function<bool(std::string&)> fallback) const;

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
    return getTableValue(name, TABLE_FUNC, [](std::string& name) {
        return isBuiltinFunc(name);
    });
}

bool ClosureManagerImpl::getConstant(std::string& name) const {
    return getTableValue(name, TABLE_CONST, [](std::string& name) {
        return isBuiltinConst(name);
    });
}


bool ClosureManagerImpl::getVariable(std::string& name) const {
    return getTableValue(name, TABLE_VAR, [](std::string&) { return false; });
}

///////

const Closure* ClosureManagerImpl::findNearestNameContainer(const std::string &name) const {
    for(auto it = closures.rbegin() ; it != closures.rend() ; it++) {
        auto &map = it->nameMap;
        if (map.find(name) != map.end()) return &(*it);
    }
    return nullptr;
}

bool ClosureManagerImpl::getTableValue(std::string& name, TableType table, std::function<bool(std::string&)> fallback) const {
    auto closure = findNearestNameContainer(name);
    if (closure == nullptr) return fallback(name);
    const auto& cEntry = closure->nameMap.find(name)->second;
    if(cEntry.type == table) {
        name = cEntry.mappedString;
        return true;
    }
    else return false;
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
    auto& map = lastClosure.nameMap;
    if(map.find(name) != map.end()) return false; // Has duplicate name
    if(!hasOutputName(name)) {
        ClosureEntry entry = {table, name};
        map.insert(std::make_pair(name, entry));
        lastClosure.mapValueSet.insert(name);
        return true;
    }
    else {
        char postfix[30];
        int i;
        for(i = 1 ; ; i++) {
            sprintf(postfix, "_%d", i);
            std::string otherName = name + postfix;
            if(!hasOutputName(otherName)) {
                ClosureEntry entry = {table, otherName};
                map.insert(std::make_pair(name, entry));
                lastClosure.mapValueSet.insert(otherName);
                name = otherName;
                return true;
            }
        }
    }
}


bool ClosureManagerImpl::hasOutputName(const std::string& name) const {
    for(auto it = closures.rbegin() ; it != closures.rend() ; it++) {
        auto &set = it->mapValueSet;
        if (set.find(name) != set.end()) return true;
    }
    return false;
}
