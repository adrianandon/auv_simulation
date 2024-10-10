#ifndef MISSIONPLAN_HPP
#define MISSIONPLAN_HPP

#include <queue>
#include <utility> 
#include "MissionOperation.hpp"

class MissionPlan {
public:
    std::pair<MissionOperation, double> getNextMissionOperation();
    void addMissionOperation(MissionOperation operation, double value);
    bool isEmpty() const;
private:
    std::queue<std::pair<MissionOperation, double>> operations;
};

#endif // MISSIONPLAN_HPP