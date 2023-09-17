#include <database.h>

std::atomic<Database*> Database::_instance;
std::mutex Database::mtx;