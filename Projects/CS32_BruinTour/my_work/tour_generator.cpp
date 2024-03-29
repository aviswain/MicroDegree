//
//  tour_generator.cpp
//  BruinTour
//
//  Created by Avi Swain on 3/12/24.
//

#include "tour_generator.h"
#include "stops.h"
#include <vector>
#include "tourcmd.h"
#include "geopoint.h"
#include "geotools.h"
#include <string>
#include <iostream>
using namespace std;

TourGenerator::TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router) : m_database(&geodb), m_router(&router){}

TourGenerator::~TourGenerator() {}

vector<TourCommand> TourGenerator::generate_tour(const Stops& stops) const {
    vector<TourCommand> instructions;
    vector<GeoPoint> route;
    
    for (int i = 0; i < stops.size(); i++) {
        /*
         Generate a commentary TourCommand object that specifies what
         should be said about the current point of interest P and add it to the end
         of the instructions result vector
         */
        string PoI;
        string comments;
        stops.get_poi_data(i, PoI, comments);
        
        GeoPoint P0;
        m_database->get_poi_location(PoI, P0);
        
        TourCommand commentary;
        commentary.init_commentary(PoI, comments);
        instructions.push_back(commentary);
        

        // If there is another point of interest following P then...
        if (i < stops.size()-1) {
            
            /*
             ...use your Router class to generate a point-to-point route
             between the GeoPoint associated with P and the GeoPoint of
             the next point of interest, and then…
             */
            string nextPoI;
            stops.get_poi_data(i+1, nextPoI, comments);
            
            GeoPoint P1;
            m_database->get_poi_location(nextPoI, P1);
            
            route = m_router->route(P0, P1);
            
            /*
             Using the path of GeoPoints generated by Router object in the previous
             step, generate a sequence of TourCommands representing proceed and
             turn instructions for the tour robot:
             */
            for (int k = 0; k < route.size(); k++) {
                if (k < route.size()-1) {
                    TourCommand proceed;
                    proceed.init_proceed(getDirectionForProceed(angle_of_line(route[k], route[k+1])), m_database->get_street_name(route[k], route[k+1]), distance_earth_miles(route[k], route[k+1]), route[k], route[k+1]);
                    instructions.push_back(proceed);
                    if (k < route.size()-2 && (m_database->get_street_name(route[k], route[k+1]) != m_database->get_street_name(route[k+1], route[k+2])) && (angle_of_turn(route[k], route[k+1], route[k+2]) != 0)) {
                        TourCommand turn;
                        turn.init_turn(getDirectionForTurn(angle_of_turn(route[k], route[k+1], route[k+2])), m_database->get_street_name(route[k+1], route[k+2]));
                        instructions.push_back(turn);
                        
                    }
                }
            }
        }
    }
    return instructions;
}

string TourGenerator::getDirectionForProceed(double angle) const {
    string dir;
    if (angle >= 0 && angle < 22.5) {
        dir = "east";
    } else if (angle >= 22.5 && angle < 67.5) {
        dir = "northeast";
    } else if (angle >= 67.5 && angle < 112.5) {
        dir = "north";
    } else if (angle >= 112.5 && angle < 157.5) {
        dir = "northwest";
    } else if (angle >= 157.5 && angle < 202.5) {
        dir = "west";
    } else if (angle >= 202.5 && angle < 247.5) {
        dir = "southwest";
    } else if (angle >= 247.5 && angle < 292.5) {
        dir = "south";
    } else if (angle >= 292.5 && angle < 337.5) {
        dir = "southeast";
    } else if (angle >= 337.5) {
        dir = "east";
    }
    return dir;
}

string TourGenerator::getDirectionForTurn(double angle) const {
    string dir;
    if (angle >= 1 && angle < 180)
        dir = "left";
    else if (angle >= 180 && angle <= 359)
        dir = "right";
    return dir;
}
