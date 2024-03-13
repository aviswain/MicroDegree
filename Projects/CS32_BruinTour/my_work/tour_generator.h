//
//  tour_generator.h
//  BruinTour
//
//  Created by Avi Swain on 3/12/24.
//

#ifndef tour_generator_h
#define tour_generator_h

#include "base_classes.h"
#include "stops.h"
#include <string>

class TourGenerator: public TourGeneratorBase
{
public:
    TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router);
    virtual ~TourGenerator();
    virtual std::vector<TourCommand> generate_tour(const Stops& stops) const;
private:
    
    std::string getDirectionForProceed(double angle) const;
    std::string getDirectionForTurn(double angle) const;
    const GeoDatabaseBase* m_database;
    const RouterBase* m_router;
    
};



#endif /* tour_generator_h */
