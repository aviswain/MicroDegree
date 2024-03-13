//
//  geodb.h
//  BruinTour
//
//  Created by Avi Swain on 3/9/24.
//

#ifndef geodb_h
#define geodb_h

#include "base_classes.h"
#include "HashMap.h"
#include "geopoint.h"
#include <vector>
#include <string>

class GeoDatabase: public GeoDatabaseBase
{
public:
    GeoDatabase();
    virtual ~GeoDatabase();
    virtual bool load(const std::string& map_data_file);
    
    virtual bool get_poi_location(const std::string& poi, GeoPoint& point) const;
    virtual std::vector<GeoPoint> get_connected_points(const GeoPoint& pt) const;
    virtual std::string get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const;
private:
    ////////////////////////////////////////////////////////////////////
    //  INTERNAL DATA STRUCTURES
    ////////////////////////////////////////////////////////////////////
    
    // Stores connected GeoPoints
    HashMap<std::vector<GeoPoint>> m_GeoPointAdjList;
    
    // Stores PoI GeoPoints
    HashMap<GeoPoint> m_PoInameToLocation;
    
    // Stores Street Names or "a path"
    HashMap<std::string> m_GeoPointsToLineName;
    
    // HELPER FUNCTIONS
    void updateGeoPointsToLineName(std::string p1_lat, std::string p1_lon, std::string p2_lat, std::string p2_lon, std::string name);
    void updateAdjList_two_way(std::string start_lat, std::string start_lon, std::string end_lat, std::string end_lon);
    
    void updateAdjList_one_way(std::string receiver_lat, std::string receiver_lon, std::string p1_lat, std::string p1_lon, std::string p2_lat, std::string p2_lon);
    
};

#endif /* geodb_h */
