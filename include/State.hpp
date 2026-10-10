#ifndef STATE_HPP
#define STATE_HPP

#include <string>

// Forward declaration agar tidak circular dependency
class Striker;

class State {
public:
    virtual ~State() = default;
    virtual void execute(Striker* striker) = 0;
    virtual std::string getName() const = 0;
};

class SearchState : public State {
public:
    void execute(Striker* striker) override;
    std::string getName() const override { return "SEARCH_BALL"; }
};

class ApproachState : public State {
public:
    void execute(Striker* striker) override;
    std::string getName() const override { return "APPROACH_BALL"; }
};

class AlignState : public State {
public:
    void execute(Striker* striker) override;
    std::string getName() const override { return "ALIGN_TO_GOAL"; }
};

class KickState : public State {
public:
    void execute(Striker* striker) override;
    std::string getName() const override { return "KICK"; }
};

#endif // STATE_HPP