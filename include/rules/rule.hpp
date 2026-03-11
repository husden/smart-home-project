#ifndef RULE_HPP
#define RULE_HPP

#include <string>

class Rule {
protected:
    std::string name;
    bool isActive;

public:
    Rule(const std::string& ruleName) : name(ruleName), isActive(true) {}
    virtual ~Rule() = default;

    virtual bool checkCondition() = 0;
    virtual void execute() = 0;

    std::string getName() const { return name; }
    void activate() { isActive = true; }
    void deactivate() { isActive = false; }
    bool isActiveRule() const { return isActive; }
};

#endif