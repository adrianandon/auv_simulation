#include "MissionPlan.hpp"
#include <stdexcept>

std::pair<MissionOperation, double> MissionPlan::getNextMissionOperation() {
    if (operations.empty()) {
        throw std::runtime_error("No more operations in the mission plan");
    }
    auto operation = operations.front();
    operations.pop();
    return operation;
}

void MissionPlan::addMissionOperation(MissionOperation operation, double value) {
    operations.emplace(operation, value);
}

bool MissionPlan::isEmpty() const {
    return operations.empty();
}