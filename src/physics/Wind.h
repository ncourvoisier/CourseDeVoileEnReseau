#ifndef SAILINSANE_WIND_H
#define SAILINSANE_WIND_H

#include <cmath>
#include <cstdlib>

namespace sail {

    class Wind {
    public:
        Wind();
        Wind(double speed, double direction);
        double getSpeed() const;
        void setSpeed(double speed);
        double getDirection() const;
        void setDirection(double direction);

    private:
        double m_speed;
        double m_direction;
    };

}


#endif //SAILINSANE_WIND_H
