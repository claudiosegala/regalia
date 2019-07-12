#include <pch.h>
#include <Util.h>
#include <CollisionMap.h>

int CollisionMap::cols = 0;

int CollisionMap::rows = 0;

std::vector<std::vector<int>> CollisionMap::map;

unsigned long CollisionMap::FindMaxDelta(const Rect& box, const Vec2& velocity, const unsigned long dt) {
	unsigned long ans = 0;
	unsigned long min_delta = 0;
	auto max_delta = dt;

	bool collision = false;
	while (min_delta <= max_delta) {
		const auto delta = (max_delta + min_delta) / 2;
		const auto p = box + velocity * float(delta) / 1000.0f;
		const auto ul = p.GetUpperLeft();
		const auto dr = p.GetLowerRight();

		// TODO: Get tile width and height this from TileMap
		const auto x1 = int(ul.x / 24.0f);
		const auto y1 = int(ul.y / 24.0f);
		const auto x2 = int(dr.x / 24.0f);
		const auto y2 = int(dr.y / 24.0f);

		collision = false;

		if (x1 < 0 || x1 >= cols || y1 < 0 || y1 >= rows || x2 < 0 || x2 >= cols || y2 < 0 || y2 >= rows) {
			collision = true;
		} else {
			collision = [&]() {
				for (int j = y1; j <= y2; j++) {
					for (int k = x1; k <= x2; k++) {
						if (map[j][k]) {
							return true;
						}
					}
				}
				return false;
			}();
		}

		if (!collision) {
			ans = delta;
			min_delta = delta + 1;
		} else {
			max_delta = delta - 1;
		}
	}

	return ans;
}

void CollisionMap::SetMap(std::vector<int> _map, int _rows, int _cols) {
	rows = _rows;
	cols = _cols;

	map.resize(rows);

	for (long long i = 0; i < rows; i++) {
		map[i].resize(cols);
		
		for (int j = 0; j < cols; j++) {
			map[i][j] = (_map[i * cols + j] > 0);
		}
	}
}
