#include <iostream>
#include <memory>
#include <map>
#include <geometry.h>

void DrawPoints(std::vector<Point>::iterator start, std::vector<Point>::iterator end)
{
    for (auto i = start; i != end; i++) {
        std::cout << *i << " ";
    }
    std::cout << "\n";
}

struct LineToPointAdapter
{
    typedef std::vector<Point> Points;

    LineToPointAdapter(Line const& line) {
        static std::hash<Line> hash;
        line_hash = hash(line);
        if (cache.find(line_hash) != cache.end()) {
            // cut down on the number of conversion
            return;
        }

        Points points;
        int left = std::min(line.start.x, line.end.x);
        int right = std::max(line.start.x, line.end.x);
        int top = std::min(line.start.y, line.end.y);
        int bottom = std::max(line.start.y, line.end.y);
        int dx = right - left;
        int dy = line.end.y - line.start.y;

        if (dx == 0) {
            // vertical
            for (int y = top; y <= bottom; y++) {
                points.emplace_back(Point{ left, y });
            }
        }
        else if (dy == 0) {
            // horizontal
            for (int x = left; x <= right; x++) {
                points.emplace_back(Point{ x, top });
            }
        }
        cache[line_hash] = points;
    }

    virtual Points::iterator begin() { return cache[line_hash].begin(); }
    virtual Points::iterator end() { return cache[line_hash].end(); }

private:
    size_t line_hash;
    static std::map<size_t, Points> cache;
};

std::map<size_t, LineToPointAdapter::Points> LineToPointAdapter::cache{};

int main(int argc, char** argv)
{
    std::vector<std::shared_ptr<VectorObject>> vectorObjects{
        std::make_shared<VectorRectangle>(10, 10, 5, 5),
        std::make_shared<VectorRectangle>(10, 10, 5, 5),
        std::make_shared<VectorRectangle>(30, 30, 10, 10)
    };

    // predefine all the points
    std::vector<Point> points;
    for (auto const& obj : vectorObjects) {
        for (auto const& line : *obj) {
            LineToPointAdapter lpo{ line };
            for (auto const& p : lpo) {
                points.push_back(p);
            }
        }
    }

    std::cout << "Draw points:\n";
    DrawPoints(points.begin(), points.end());

    return 0;
}