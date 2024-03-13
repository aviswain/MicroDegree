//
//  router.cpp
//  BruinTour
//
//  Created by Avi Swain on 3/11/24.
//

#include "router.h"
#include <vector>
#include "geotools.h"
#include <queue>
#include <algorithm>
#include "HashMap.h"


using namespace std;

Router::Router(const GeoDatabaseBase& geo_db) {
    m_database = &geo_db; // IS THIS BEST PRACTICE?
}

Router::~Router() {
    // no dynamic allocation being done here, so nothing to delete
}

vector<GeoPoint> Router::route(const GeoPoint &pt1, const GeoPoint &pt2) const {
    HashMap<GeoPoint> came_from;
    HashMap<double> cost_so_far;
    a_star_search(pt1, pt2, came_from, cost_so_far);
    vector<GeoPoint> path = reconstruct_path(pt1, pt2, came_from);
    return path;
}

void Router::a_star_search(const GeoPoint &start, const GeoPoint &target, HashMap<GeoPoint>& came_from, HashMap<double>& cost_so_far) const {
    PriorityQueue nodeQueue;
    
    nodeQueue.put(start, 0);
    
    came_from[key(start)] = start;
    cost_so_far[key(start)] = 0;
    
    while (!nodeQueue.empty()) {
        GeoPoint current = nodeQueue.get();
        
        if (nodesMatch(current,target)) {
            break;
        }
        
        vector<GeoPoint> adjacentNodes = m_database->get_connected_points(current);
        for (GeoPoint adjacentNode : adjacentNodes) {
            double new_cost = cost_so_far[key(current)] + distance_earth_miles(current, adjacentNode);
            if (cost_so_far.find(key(adjacentNode)) == nullptr || new_cost < cost_so_far[key(adjacentNode)]) {
                cost_so_far[key(adjacentNode)] = new_cost;
                double priority = new_cost + heuristic(adjacentNode, target);
                nodeQueue.put(adjacentNode, priority);
                came_from[key(adjacentNode)] = current;
            }
        }
    }
}

double Router::heuristic(const GeoPoint &pt, const GeoPoint &target) const {
    return distance_earth_miles(pt, target);
}

vector<GeoPoint> Router::reconstruct_path(const GeoPoint &start, const GeoPoint &target, HashMap<GeoPoint>& came_from) const {
    vector<GeoPoint> path;
    GeoPoint current = target;
    
    if(came_from.find(key(target)) == nullptr) {
        return path;
    } else if (nodesMatch(start,target)) {
        path.push_back(target);
        return path;
    }
    
    while (!nodesMatch(current,start)) {
        path.push_back(current);
        current = came_from[key(current)];
    }
    
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}
string Router::key(const GeoPoint &pt) const{
    return (pt.sLatitude + pt.sLongitude);
}

bool Router::nodesMatch(const GeoPoint &pt1, const GeoPoint &pt2) const {
    return ((pt1.latitude == pt2.latitude) && (pt1.longitude == pt2.longitude));
}

