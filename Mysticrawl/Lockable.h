#include <functional>
#include <vector>

using namespace std;

class Lockable {
private:
	vector<function<bool()>> lockStatusFunctions;
public:
	Lockable(vector<function<bool()>> lockStatusFunctions = {}) : lockStatusFunctions(lockStatusFunctions) {}

	bool isLocked() const;
	void addLock(function<bool()> lock) { lockStatusFunctions.push_back(lock); };
};