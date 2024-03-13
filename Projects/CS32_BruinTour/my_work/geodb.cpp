//
//  geodb.cpp
//  BruinTour
//
//  Created by Avi Swain on 3/9/24.
//

#include "geodb.h"
#include "geopoint.h"
#include "geotools.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

GeoDatabase::GeoDatabase() {}

GeoDatabase::~GeoDatabase() {}

bool GeoDatabase::load(const std::string& map_data_file) {
    // Open the file for input
    ifstream inf(map_data_file);
    if (!inf) {
        cerr << "Error: Cannot open " << map_data_file << endl;
        return false;
    }
    
    // Read each line.  The return value of getline is treated
    // as true if a line was read, false otherwise (e.g., because
    // the end of the file was reached).
    string line;
    while(getline(inf, line)) {
        
        // street name data from first line
        string street = line;
        
        // endpoint data from second line
        string endpointsLine;
        getline(inf, endpointsLine);
        istringstream endpointStream(endpointsLine);
        string start_lat, start_lon, end_lat, end_lon;
        endpointStream >> start_lat >> start_lon >> end_lat >> end_lon;
        
        /*
         For each street segment (that starts on a GeoPoint and ends on a GeoPoint) in the map
         data file, ensure that the get_connected_points() and get_street_name() can recognize
         the GeoPoints and produce the correct results.
         */
        updateGeoPointsToLineName(start_lat, start_lon, end_lat, end_lon, street);
        updateAdjList_two_way(start_lat, start_lon, end_lat, end_lon);
    
        
        string numPoILine;
        getline(inf, numPoILine);
        istringstream numPoIstream(numPoILine);
        int numPoI;
        numPoIstream >> numPoI;
        
        
        /*
         If a street segment S which connects GeoPoints S1 and S2 has one or more points of
         interest on it, then you must do the following:
         */
        if (numPoI >= 1) {
            /*
             Determine the midpoint of street segment S using the midpoint() function found in
             the provided geotools.h file. You must use midpoint() to determine the midpoint.
             */
            GeoPoint midpt = midpoint(GeoPoint(start_lat, start_lon), GeoPoint(end_lat, end_lon));
            
            
            /*
             Update your internal GeoDatabase data structures to ensure that there is a
             bidirectional connection between Si and the computed midpoint, and assign it a
             street name that matches the street name of the segment S.
             */
            updateGeoPointsToLineName(midpt.sLatitude, midpt.sLongitude, start_lat, start_lon, street);
            updateGeoPointsToLineName(midpt.sLatitude, midpt.sLongitude, end_lat, end_lon, street);
            
            updateAdjList_two_way(midpt.sLatitude, midpt.sLongitude, start_lat, start_lon);
            updateAdjList_two_way(midpt.sLatitude, midpt.sLongitude, end_lat, end_lon);
            
            // For each point of interest on that segment:
            for (int i = 0; i < numPoI; i++) {
                getline(inf, line);
                istringstream poistream(line);
                string PoI_name;
                string PoI_lat, PoI_lon;
                getline(poistream, PoI_name, '|');
                poistream >> PoI_lat >> PoI_lon;
                
                // Update PoI location database
                m_PoInameToLocation.insert(PoI_name, GeoPoint(PoI_lat, PoI_lon));
                
                /*
                 Update internal GeoDatabase data structures to ensure that there is
                 a bi-directional connection between the GeoPoint of the point of interest
                 and the computed midpoint GeoPoint which has a street name called "a
                 path".
                 */
                updateGeoPointsToLineName(midpt.sLatitude, midpt.sLongitude, PoI_lat, PoI_lon, "a path");
                updateAdjList_two_way(midpt.sLatitude, midpt.sLongitude, PoI_lat, PoI_lon);
            }
        }
    }

    return true;
}

bool GeoDatabase::get_poi_location(const std::string &poi, GeoPoint &point) const {
    const GeoPoint* ptr = m_PoInameToLocation.find(poi);
    
    if (ptr != nullptr) {
        point = *ptr;
        return true;
    }
    
    return false;
}

std::vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint& pt) const {
    
    const vector<GeoPoint>* ptr = m_GeoPointAdjList.find(pt.sLatitude + pt.sLongitude);
    vector<GeoPoint> connectingPts;
    
    if (ptr != nullptr) {
        connectingPts = *ptr;
    }
    
    return connectingPts;
}

std::string GeoDatabase::get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const {
    // Decide key
    string key;
    if (pt1.sLatitude <= pt2.sLatitude) {
        key = pt1.sLatitude + pt1.sLongitude + pt2.sLatitude + pt2.sLongitude;
    } else {
        key = pt2.sLatitude + pt2.sLongitude + pt1.sLatitude + pt1.sLongitude;
    }
    
    const string* ptr = m_GeoPointsToLineName.find(key);
    string name = "";
    
    if (ptr != nullptr) {
        name = *ptr;
    }
    
    return name;
}

void GeoDatabase::updateGeoPointsToLineName(string p1_lat, string p1_lon, string p2_lat, string p2_lon, string name) {
    string key;
    
    if (p1_lat <= p2_lat) {
        key = p1_lat + p1_lon + p2_lat + p2_lon;
    } else {
        key = p2_lat + p2_lon + p1_lat + p1_lon;
    }
    
    m_GeoPointsToLineName.insert(key, name);
}

void GeoDatabase::updateAdjList_two_way(string start_lat, string start_lon, string end_lat, string end_lon) {
    string key;
    
    key = start_lat + start_lon;
    vector<GeoPoint>* geoptr = m_GeoPointAdjList.find(key);
    
    if (geoptr != nullptr) {
        geoptr->push_back(GeoPoint(end_lat,end_lon));
    } else {
        vector<GeoPoint> pts;
        pts.push_back(GeoPoint(end_lat,end_lon));
        m_GeoPointAdjList.insert(key, pts);
    }
    
    key = end_lat + end_lon;
    geoptr = m_GeoPointAdjList.find(key);
    
    if (geoptr != nullptr) {
        geoptr->push_back(GeoPoint(start_lat,start_lon));
    } else {
        vector<GeoPoint> pts;
        pts.push_back(GeoPoint(start_lat,start_lon));
        m_GeoPointAdjList.insert(key, pts);
    }
        
}

void GeoDatabase::updateAdjList_one_way(string receiver_lat, string receiver_lon, string p1_lat, string p1_lon, std::string p2_lat, std::string p2_lon) {
    string key = receiver_lat + receiver_lon;
    
    // Assuming there are no matching midpoints....
    vector<GeoPoint> pts;
    pts.push_back(GeoPoint(p1_lat,p1_lon));
    pts.push_back(GeoPoint(p2_lat,p2_lon));
    m_GeoPointAdjList.insert(key, pts);
}
