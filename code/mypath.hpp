#ifndef PATH_H
#define PATH_H
#include <list>
using namespace std;
class Path {
public:

	Path() : length(9999999) {}

	Path(const Path& path) {
		*this = path;
	}

	Path& operator=(const Path& path) {
		this->length = path.length;
		this->nodes = path.nodes;
		return *this;
	}

	Path operator+(const Path& path) const {
		Path res(*this);
		res.length += path.length;
		auto iter = path.nodes.begin();
		res.nodes.insert(res.nodes.end(), ++iter, path.nodes.end());
		return res;
	}

	bool operator>(const Path& path) const {
		return length > path.length;
	}

	void setDetail(int length, int start, int end) {
		this->length = length;
		nodes.clear();
		nodes.push_back(start);
		nodes.push_back(end);
	}

	int getLength() {
		return length;
	}

	list<int>& getNodes() {
		return nodes;
	}

private:
	int length;
	list<int> nodes;
};

#endif
