#include "DataController.h"
#include "Queue.h"
#include <memory>
DataController::Room::Room(
    int rid_, 
    std::unique_ptr<Specialist> &spec)
    : rid{rid_}, specialist{std::move(spec)}, queue{new Queue{}}
{
} 