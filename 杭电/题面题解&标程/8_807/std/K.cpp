#include <bits/stdc++.h>
using namespace std;

namespace ConvexHull3D {
#define ll long long
#define sz(x) ((int) (x).size())
#define all(x) (x).begin(), (x).end()
#define vi vector<int>
#define pii pair<int, int>
#define rep(i, a, b) for(int i = (a); i < (b); i++)
template<typename T>
using minpq = priority_queue<T, vector<T>, greater<T>>;

typedef long double ftype;

struct pt3 {
    ftype x, y, z;
    int id;
    pt3(ftype x = 0, ftype y = 0, ftype z = 0, int id = -1) : x(x), y(y), z(z), id(id) {}
    pt3 operator-(const pt3 &o) const {
        return pt3(x - o.x, y - o.y, z - o.z);
    }
    pt3 cross(const pt3 &o) const {
        return pt3(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
    }
    ftype dot(const pt3 &o) const {
        return x * o.x + y * o.y + z * o.z;
    }
    ftype abs() const {
        return sqrt(dot(*this));
    }
};

struct edge;

// The implementation becomes more challenging because we need information of adjacent faces.
// A face will have 3 edges for its adjacent faces
// e1 corresponds to the edge (a,b), e2 to (b,c), and e3 to (c,a)
// A face will store a list of future points that can see it.
// A face will also store "dead" - the index of the point responsible for deleting it (or 1e9 if alive)
struct face {
    int a, b, c;
    pt3 q;
    edge *e1, *e2, *e3;
    vi points;
    int dead;
    face(int a, int b, int c, pt3 q) : a(a), b(b), c(c), q(q), dead(1e9) {
        e1 = e2 = e3 = NULL;
    }
};

// an edge will store the face it leads to and a pointer to the reverse edge
struct edge {
    edge *rev;
    face *f;
};

// modify this to your liking
const ftype EPS = 0.5;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// shuffles the point-set p, making sure the first 4 points are not coplanar.
// if all points are coplanar, an assertion fails
void prepare(vector<pt3> &p) {
    int n = sz(p);
    shuffle(all(p), rng);
    vi ve;
    ve.push_back(0);
    rep(i, 1, n) {
        if(sz(ve) == 1) {
            if((p[ve[0]] - p[i]).abs() > EPS) ve.push_back(i);
        }else if(sz(ve) == 2) {
            if((p[ve[1]] - p[ve[0]]).cross(p[i] - p[ve[0]]).abs() > EPS) ve.push_back(i);
        }else if(abs((p[i] - p[ve[0]]).dot((p[ve[1]] - p[ve[0]]).cross(p[ve[2]] - p[ve[0]]))) > EPS) {
            ve.push_back(i);
            break;
        }
    }
    assert(sz(ve) == 4);
    vector<pt3> ve2;
    for(int i : ve) ve2.push_back(p[i]);
    reverse(all(ve));
    for(int i : ve) p.erase(p.begin() + i);
    p.insert(p.begin(), all(ve2));
}

vector<face*> hull3(vector<pt3> &p, deque<face> &face_pool, deque<edge> &edge_pool) {
    int n = sz(p);
    prepare(p);
    vector<face*> f, new_face(n, NULL);

    // for a point i, conflict[i] is the list of faces it can see.
    // It might contain faces that were deleted, and we should ignore them
    vector<vector<face*>> conflict(n);
    queue<face*> face_gc;
    auto add_face = [&](int a, int b, int c) {
        face *F = NULL;
        if(face_gc.empty()) {
            face_pool.emplace_back(a, b, c, (p[b] - p[a]).cross(p[c] - p[a]));
            F = &face_pool.back();
            f.push_back(F);
        }else {
            F = face_gc.front();
            face_gc.pop();
            *F = face(a, b, c, (p[b] - p[a]).cross(p[c] - p[a]));
        }
        return F;
    };

    // This function will glue two faces together
    // e1 is a reference to the F1 edge pointer, and e2 is a reference to the F2 edge pointer
    queue<edge*> edge_gc;
    auto add_edge = [&]() {
        edge *E = NULL;
        if(edge_gc.empty()) {
            edge_pool.emplace_back();
            E = &edge_pool.back();
        }else {
            E = edge_gc.front();
            edge_gc.pop();
        }
        return E;
    };
    auto glue = [&] (face *F1, face *F2, edge* &e1, edge* &e2) {
        if(!e1) e1 = add_edge();
        if(!e2) e2 = add_edge();
        e1->rev = e2;
        e2->rev = e1;
        e1->f = F2;
        e2->f = F1;
    };

    // initialize a triangular disk of the first 3 points.
    // The initial tetrahedron is handled automatically when we insert the 4th point
    face *F1 = add_face(0, 1, 2);
    face *F2 = add_face(0, 2, 1);
    glue(F1, F2, F1->e1, F2->e3);
    glue(F1, F2, F1->e2, F2->e2);
    glue(F1, F2, F1->e3, F2->e1);
    for(face *F : {F1, F2}) {
        rep(i, 3, n) {
            if((p[i] - p[F->a]).dot(F->q) > EPS) {
                conflict[i].push_back(F);
                break;
            }
        }
        rep(i, 3, n) {
            // making this second check is an ugly consequence of starting with a degenerate triangular disk.
            // We want to make sure each future point is considered visible to some initial face.
            if((p[i] - p[F->a]).dot(F->q) >= -EPS) F->points.push_back(i);
        }
        reverse(all(F->points));
    }

    rep(i, 3, n) {
        // mark all visible faces as dead
        for(face *F : conflict[i]) F->dead = min(F->dead, i);

        // If a dead face and alive face are adjacent, we have an exposed edge
        // Vertex v will be a vertex on some exposed edge
        int v = -1;
        for(face *F : conflict[i]) {
            if(F->dead != i) continue;
            int parr[3] = {F->a, F->b, F->c};
            edge* earr[3] = {F->e1, F->e2, F->e3};
            rep(j, 0, 3) {
                if(earr[j]->f->dead > i) {
                    // F is dead and earr[j]->f is alive.
                    // We should add a new face Fn, attach it to earr[j]->f,
                    // combine the point lists of the two faces into Fn,
                    // and store Fn in new_face[parr[j]] so we can glue all the new faces together in a cone.
                    face *Fn = new_face[parr[j]] = add_face(parr[j], parr[(j + 1) % 3], i);
                    while(sz(F->points) && F->points.back() <= i) F->points.pop_back();
                    while(sz(earr[j]->f->points) && earr[j]->f->points.back() <= i) earr[j]->f->points.pop_back();
                    set_union(all(F->points), all(earr[j]->f->points), back_inserter(Fn->points), greater<int>());
                    Fn->points.erase(stable_partition(all(Fn->points), [&](int k) {
                        return (p[k] - p[Fn->a]).dot(Fn->q) > EPS;
                    }), Fn->points.end());
                    if(sz(Fn->points)) conflict[Fn->points.back()].push_back(Fn);
                    glue(earr[j]->f, Fn, earr[j]->rev, Fn->e1);
                    v = parr[j];
                }
            }
        }

        for(face *F : conflict[i]) {
            if(F->dead != i) continue;
            if(F->e1) edge_gc.push(F->e1);
            if(F->e2) edge_gc.push(F->e2);
            if(F->e3) edge_gc.push(F->e3);
            face_gc.push(F);
        }

        // There are no exposed edges
        if(v == -1) continue;

        // Glue all the new cone faces together
        while(new_face[v]->e2 == NULL) {
            int u = new_face[v]->b;
            glue(new_face[v], new_face[u], new_face[v]->e2, new_face[u]->e3);
            v = u;
        }
    }

    // Remove dead faces
    f.erase(remove_if(all(f), [&](face *F) {
        return F->dead < n;
    }), f.end());
    return f;
}
} // namespace ConvexHull3D

typedef long double db;
const db inf=2e4;
const db eps=1e-9;
const db pi=acos(db(-1));
int sgn(db x)
{
    if(x>eps)return 1;
    if(x<-eps)return -1;
    return 0;
}
struct Point
{
    db x,y;
    Point(){}
    Point(db _x,db _y):x(_x),y(_y) {}
    Point operator + (const Point& t)const { return Point(x+t.x,y+t.y); }
    Point operator - (const Point& t)const { return Point(x-t.x,y-t.y); }
    Point operator * (const db& t)const { return Point(x*t,y*t); }
    Point operator / (const db& t)const { return Point(x/t,y/t); }
    db operator * (const Point& t)const { return x*t.y-y*t.x; }
    db operator ^ (const Point& t)const { return x*t.x+y*t.y; }
    bool operator == (const Point& t)const { return sgn(x-t.x)==0 && sgn(y-t.y)==0; }
    bool operator != (const Point& t)const { return !(*this==t); }
    db len()const { return sqrt(x*x+y*y); }
    Point rot90()const { return Point(-y,x); }
};
struct Line
{
    Point s,v;
    Line(){}
    Line(const Point& _s,const Point& _v):s(_s),v(_v){}
    bool left(const Point& p)const { return sgn((p-s)*v)<0; }
    Point operator & (const Line &t)const {
        db c=v*t.v;
        assert(sgn(c)!=0);
        return s+v*(((t.s-s)*t.v)/c);
    }
};
pair<vector<Point>,vector<Line>> halfplane_intersect(const vector<Line>& lines)
{
    vector<int> idx(lines.size());
    iota(idx.begin(),idx.end(),0);
    vector<db> ang(lines.size());
    for(size_t i=0;i<lines.size();i++)
        ang[i]=atan2(lines[i].v.y,lines[i].v.x);
    sort(idx.begin(),idx.end(),[&](int i, int j){
        return ang[i]<ang[j];
    });
    vector<Point> p(lines.size());
    vector<Line> hp(lines.size());
    hp[0]=lines[idx[0]];
    int h=0,t=0;
    for(size_t ii=1;ii<lines.size();ii++)
    {
        int i=idx[ii];
        while(h<t && !lines[i].left(p[t-1]))t--;
        while(h<t && !lines[i].left(p[h]))h++;
        if(sgn(lines[i].v*hp[t].v)!=0)hp[++t]=lines[i];
        else if(!lines[i].left(hp[t].s))hp[t]=lines[i];
        if(h<t)p[t-1]=hp[t]&hp[t-1];
    }
    while(h<t && !hp[h].left(p[t-1]))t--;
    if(h<t)p[t]=hp[t]&hp[h];
    db area=0;
    for(int i=0; i<=t-h; i++)
        area+=p[i+h]*p[(i+1)%(t-h+1)+h];
    if(sgn(area)<=0)return {};
    return {vector<Point>(p.begin()+h,p.begin()+t+1),
            vector<Line>(hp.begin()+h,hp.begin()+t+1)};
}
struct Circle
{
    Point o;
    db r;
    Circle() {}
    Circle(Point _o,db _r):o(_o),r(_r) {}
    vector<Point> operator & (const Line& t)const
    {
        Point v=t.v/t.v.len();
        Point m=t.s+v*((o-t.s)^v);
        db d=(m-o).len();
        if(sgn(d-r)>0)return {};
        if(sgn(d-r)==0)return {m};
        d=sqrt(max<db>(0,r*r-d*d));
        return {m-v*d,m+v*d};
    }
};
db polygon_circle_intersect(const vector<Point>& p, const Circle& c) {
    db res=0;
    for (size_t i=0;i<p.size();i++) {
        Point s=p[i],e=p[(i+1)%p.size()];
        vector<Point> key;
        key.push_back(s);
        for(auto& p : c&Line(s, e-s))
            if(sgn((p-s)^(e-s))>0 && sgn((p-e)^(s-e))>0)
                key.push_back(p);
        key.push_back(e);
        for(size_t j=0;j+1<key.size();j++) {
            Point m=(key[j]+key[j+1])/2;
            if(sgn((m-c.o).len()-c.r)<0) {
                res+=(key[j]-c.o)*(key[j+1]-c.o);
            } else {
                res+=atan2((key[j]-c.o)*(key[j+1]-c.o),(key[j]-c.o)^(key[j+1]-c.o))*c.r*c.r;
            }
        }
    }
    return res/2;
}
int solve()
{
    int n;
    scanf("%d",&n);
    vector<Circle> cir(n);
    for(int i=0;i<n;i++)
        scanf("%Lf%Lf%Lf",&cir[i].o.x,&cir[i].o.y,&cir[i].r);
    cir.emplace_back(Point(-inf,-inf),0);
    cir.emplace_back(Point(inf,-inf),0);
    cir.emplace_back(Point(inf,inf),0);
    cir.emplace_back(Point(-inf,inf),0);
    vector<ConvexHull3D::pt3> pts;
    for(size_t i=0;i<cir.size();i++)
        pts.emplace_back(-2*cir[i].o.x,-2*cir[i].o.y,cir[i].o.x*cir[i].o.x+cir[i].o.y*cir[i].o.y-cir[i].r*cir[i].r,i);
    deque<ConvexHull3D::face> face_pool;
    deque<ConvexHull3D::edge> edge_pool;
    auto faces=ConvexHull3D::hull3(pts,face_pool,edge_pool);
    vector<vector<int>> adj(pts.size());
    for(auto& f : faces)
        if(sgn(f->q.z)<0)
        {
            adj[pts[f->a].id].push_back(pts[f->b].id);
            adj[pts[f->b].id].push_back(pts[f->c].id);
            adj[pts[f->c].id].push_back(pts[f->a].id);
            adj[pts[f->a].id].push_back(pts[f->c].id);
            adj[pts[f->b].id].push_back(pts[f->a].id);
            adj[pts[f->c].id].push_back(pts[f->b].id);
        }
    db res=0;
    for(size_t i=0;i<cir.size();i++)
    {
        if(adj[i].empty())continue;
        vector<Line> cut;
        cut.emplace_back(Point(-inf,-inf),Point(1,0));
        cut.emplace_back(Point(inf,-inf),Point(0,1));
        cut.emplace_back(Point(inf,inf),Point(-1,0));
        cut.emplace_back(Point(-inf,inf),Point(0,-1));
        for(auto j : adj[i])
        {
            db d=(cir[j].o-cir[i].o).len();
            assert(sgn(d)>0);
            Point v=(cir[j].o-cir[i].o)/d;
            Point s=cir[i].o+v*((cir[i].r*cir[i].r-cir[j].r*cir[j].r+d*d)/(2*d));
            cut.emplace_back(s,(cir[j].o-cir[i].o).rot90());
        }
        vector<Point> cell=halfplane_intersect(cut).first;
        if(cell.size()>=3)res+=polygon_circle_intersect(cell,cir[i]);
    }
    return 0*printf("%.18Lf\n",res);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)solve();
    return 0;
}
