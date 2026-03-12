#ifndef RULE_HPP
#define RULE_HPP

#include <string>

class Rule {
protected:
    std::string name;
    bool isActive;
    std::string description;

public:
    Rule(const std::string& ruleName, const std::string& desc = "")
            : name(ruleName), description(desc), isActive(true) {}

    virtual bool checkCondition() = 0;
    virtual void execute() = 0;

    std::string getName() const { return name; }
    void activate() { isActive = true; }
    void deactivate() { isActive = false; }
    bool isActiveRule() const { return isActive; }

    virtual std::string toString() const { return name; }
};

#endif