#include <bits/stdc++.h>
using namespace std;
typedef long double LD;

const LD eps = 1e-100;
int sgn(LD x) {
	return x > eps ? 1 : (x < -eps ? -1 : 0);
}
LD sqr(LD x) { return x * x; }

struct p2 {
	LD x, y;
	p2 operator + (const p2 &o) const { return {x + o.x, y + o.y}; }
	p2 operator - (const p2 &o) const { return {x - o.x, y - o.y}; }
	p2 operator * (LD a) const { return {x * a, y * a}; }
	p2 operator / (LD a) const { return {x / a, y / a}; }
	bool operator == (const p2 &o) const {
		return sgn(x - o.x) == 0 && sgn(y - o.y) == 0;
	}
	p2 unit() const {
		LD d = sqrt(x * x + y * y);
		return {x / d, y / d};
	}
	p2 rot90() const { return p2(-y, x); }
};

LD dis(const p2 &a, const p2 &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

struct circle {
	p2 c;
	LD r;
};

vector <p2> circle_inter (circle a, circle b) { // 圆交点
	if (a.c == b.c || sgn (dis (a.c, b.c) - a.r - b.r) > 0
		|| sgn (dis (a.c, b.c) - abs (a.r - b.r)) < 0)
		return {};
	p2 r = (b.c - a.c).unit();
	LD d = dis (a.c, b.c);
	LD x = ((sqr (a.r) - sqr (b.r)) / d + d) / 2;
	LD h = sqrt (sqr (a.r) - sqr (x));
	if (sgn (h) == 0) return {a.c + r * x};
	return {a.c + r * x + r.rot90 () * h,
	        a.c + r * x - r.rot90 () * h}; }

pair <LD, LD> circie_line_inter (const circle &a, const LD x) {
	if (abs(a.c.x - x) > a.r) return {1e9, -1e9};
	LD h = sqrt(a.r * a.r - (a.c.x - x) * (a.c.x - x));
	return {a.c.y - h, a.c.y + h};
}

int n;
void work () {
	cin >> n;
	vector < pair <p2, LD> > ball;
	LD zl = 0, zr = 1e9;
	for (int i = 0; i < n; i++) {
		int x, y, l;
		cin >> x >> y >> l;
		ball.push_back({{x, y}, l});
		zr = min(zr, (LD)l);
	}
	LD xx, yy;
	auto solve = [&](LD z) {
		vector <circle> cir;
		LD xl = -1e9, xr = 1e9;
		for (auto i : ball) {
			cir.push_back({i.first, sqrt(i.second - z)});
		}
		for (auto [c, r] : cir) {
			xl = max(xl, c.x - r);
			xr = min(xr, c.x + r);
		}
		for (int _ = 0; _ < 45; _++) {
			LD x = (xl + xr) / 2;
// 			cerr << "x = " << x << '\n';
			LD ymin = -1e9, ymax = 1e9;
			circle left, right;
			bool early_exit = false;
			for (auto [c, r] : cir) {
				auto [y1, y2] = circie_line_inter({c, r}, x);
				if (y1 > y2) {
					if (c.x > x) xl = x;
					else xr = x;
					early_exit = true;
					break;
				}
				if (y1 > ymin) ymin = y1, left = {c, r};
				if (y2 < ymax) ymax = y2, right = {c, r};
			}
			if (early_exit) continue;
// 			cerr << "ymin = " << ymin << ", ymax = " << ymax << '\n';
			if (ymin > ymax) {
				auto ps = circle_inter (left, right);
				if (ps.empty()) {
					return false;
				}
				// cerr << "Circles: " << "Circle1((" << left.c.x << "," << left.c.y << ")," << left.r << ") "
				//      << "Circle2((" << right.c.x << "," << right.c.y << ")," << right.r << ")\n";
				// cerr << "Intersection points: ";
				// for (const auto &p : ps) {
				// 	cerr << "(" << p.x << ", " << p.y << ") ";
				// }
				// cerr << '\n';
				auto interx = ps.front().x;
				if (interx > x) xl = x;
				else xr = x;
			} else {
				xx = x; yy = (ymin + ymax) / 2;
				return true;
			}
		}
		return false;
	};
	for (int _ = 45; _; _--) {
		LD z = (zl + zr) / 2;
// 		cerr << "z = " << sqrt(z) << endl;
		if (solve(z))
			zl = z; 
		else
			zr = z;
	}
	cout << fixed << setprecision(9) << xx << " " << yy << " " << -sqrt(zl) << '\n';
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	int T = 1;
//	cin >> T;
	for (int ca = 1; ca <= T; ca ++)
		work();
}