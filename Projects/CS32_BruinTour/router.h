//
//  router.hpp
//  BruinTour
//
//  Created by Avi Swain on 3/11/24.
//

#ifndef router_h
#define router_h

#include "base_classes.h"
#include <vector>
#include <queue>
#include <utility>
#include "HashMap.h"
#include <iostream>

class Router: public RouterBase
{
public:
    Router(const GeoDatabaseBase& geo_db);
    virtual ~Router();
    virtual std::vector<GeoPoint> route(const GeoPoint& pt1, const GeoPoint& pt2) const;
private:
    struct costNodePair {
        double priority;
        GeoPoint node;
        
        // Constructor
        costNodePair(double p, GeoPoint n) : priority(p), node(n) {}
        
    };
    
    struct compareCostNodePair {
        bool operator()(const costNodePair& a, const costNodePair& b) const {
            return a.priority > b.priority; // For min heap: lower priority values should come first
        }
    };
    
    struct PriorityQueue {
        std::priority_queue<costNodePair, std::vector<costNodePair>, compareCostNodePair> elements;
        
        bool empty() const {
            return elements.empty();
        }
        
        void put(const GeoPoint& pt, double priority) {
            elements.emplace(costNodePair(priority,pt));
        }
        
        GeoPoint get() {
            GeoPoint best_item = elements.top().node;
            elements.pop();
            return best_item;
        }
    };
    
    void a_star_search(const GeoPoint& start, const GeoPoint& target, HashMap<GeoPoint>& came_from, HashMap<double>& cost_so_far) const;
    double heuristic(const GeoPoint& pt, const GeoPoint& target) const;
    std::vector<GeoPoint> reconstruct_path(const GeoPoint& start, const GeoPoint& target, HashMap<GeoPoint>& came_from) const;
    std::string key(const GeoPoint& pt) const;
    bool nodesMatch(const GeoPoint& pt1, const GeoPoint& pt2) const;
    
    const GeoDatabaseBase* m_database;
};

#endif /* router_h */
